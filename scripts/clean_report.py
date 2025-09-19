"""
Cleans an objdiff report.json by removing any functions starting with "junk_".
"""
import json
import os
import sys

def clean_report(input_path: str, output_path: str) -> None:
    """
    Iterate over each unit in the data, then iterate over each function in the unit.
    If the function name starts with "junk_":
        junk_code_percent = function[size] / unit[total_code].
        unit[matched_code_percent] += junk_code_percent
        unit[fuzzy_match_percent] += junk_code_percent
        unit[total_code] -= function[size]

        junk_function_percent = 1 / unit[total_functions].
        unit[matched_functions_percent] += junk_function_percent
        unit[total_functions] -= 1

        if unit[junk_code_percent], unit[fuzzy_match_percent], or unit[matched_functions_percent] is approx. 100:
            set them each to 100.0

        also apply all the above adjustments to the measures in unit[measures].

    Finally, write the cleaned data to output_path.
    """
    # Input validation
    if not os.path.exists(input_path):
        raise FileNotFoundError(f"Input file not found: {input_path}")

    try:
        with open(input_path, 'r', encoding='utf-8') as infile:
            data = json.load(infile)
    except json.JSONDecodeError as e:
        raise ValueError(f"Invalid JSON in {input_path}: {e}") from e
    except IOError as e:
        raise IOError(f"Error reading {input_path}: {e}") from e

    # Validate data structure
    if not isinstance(data, dict):
        raise ValueError("JSON root must be an object")

    if 'units' not in data:
        raise ValueError("JSON must contain 'units' field")

    if not isinstance(data['units'], list):
        raise ValueError("'units' field must be a list")

    # Track global changes for updating the main measures
    total_junk_code_removed = 0
    total_junk_functions_removed = 0

    # Track category changes for updating category measures
    category_junk_removals = {}  # category_id -> {'code': removed_code, 'functions': removed_functions}

    # Process each unit in the data
    for unit in data.get('units', []):
        functions = unit.get('functions', [])
        if not functions:
            continue

        # Get and normalize current unit measures
        measures = unit.get('measures', {})

        # Remember original types for consistent output
        total_code_orig = measures.get('total_code', 0)
        total_functions_orig = measures.get('total_functions', 0)
        matched_code_percent_orig = measures.get('matched_code_percent', 0.0)
        fuzzy_match_percent_orig = measures.get('fuzzy_match_percent', 0.0)
        matched_functions_percent_orig = measures.get('matched_functions_percent', 0.0)

        # Convert to working types
        total_code = int(total_code_orig) if isinstance(total_code_orig, str) else total_code_orig
        total_functions = int(total_functions_orig) if isinstance(total_functions_orig, str) else total_functions_orig
        matched_code_percent = float(matched_code_percent_orig) if isinstance(matched_code_percent_orig, str) else matched_code_percent_orig
        fuzzy_match_percent = float(fuzzy_match_percent_orig) if isinstance(fuzzy_match_percent_orig, str) else fuzzy_match_percent_orig
        matched_functions_percent = float(matched_functions_percent_orig) if isinstance(matched_functions_percent_orig, str) else matched_functions_percent_orig

        # Remember originals for correct percentage calculation
        orig_total_code = total_code
        orig_total_functions = total_functions

        # Validate that we have positive values
        if total_code < 0 or total_functions < 0:
            continue  # Skip units with invalid data

        # Process junk functions
        junk_functions = []
        unit_junk_code_removed = 0
        unit_junk_functions_removed = 0

        for i, function in enumerate(functions):
            if not isinstance(function, dict):
                continue  # Skip invalid function entries

            if function.get('name', '').startswith('junk_'):
                junk_functions.append(i)

                # Get function size with validation
                function_size = function.get('size', 0)
                if isinstance(function_size, str):
                    try:
                        function_size = int(function_size)
                    except ValueError:
                        function_size = 0

                # Ensure function size is non-negative
                if function_size < 0:
                    function_size = 0

                # Track removals for global measures
                unit_junk_code_removed += function_size
                unit_junk_functions_removed += 1

                # Update total_code and total_functions
                total_code -= function_size
                total_functions -= 1

        # Add unit removals to global totals
        total_junk_code_removed += unit_junk_code_removed
        total_junk_functions_removed += unit_junk_functions_removed

        # Add unit removals to category totals
        if junk_functions and unit_junk_code_removed > 0:  # Only if we actually removed junk
            unit_categories = unit.get('metadata', {}).get('progress_categories', [])
            for category_id in unit_categories:
                if category_id not in category_junk_removals:
                    category_junk_removals[category_id] = {'code': 0, 'functions': 0}
                category_junk_removals[category_id]['code'] += unit_junk_code_removed
                category_junk_removals[category_id]['functions'] += unit_junk_functions_removed

        # Remove junk functions from the functions list (in reverse order to maintain indices)
        for i in reversed(junk_functions):
            functions.pop(i)

        # Update measures with new values
        if junk_functions:  # Only update if we removed junk functions
            # Add aggregated junk percentages based on original totals
            if orig_total_code > 0 and unit_junk_code_removed > 0:
                pct = unit_junk_code_removed / orig_total_code * 100
                matched_code_percent += pct
                fuzzy_match_percent += pct
            if orig_total_functions > 0 and unit_junk_functions_removed > 0:
                pctf = unit_junk_functions_removed / orig_total_functions * 100
                matched_functions_percent += pctf

            # Clamp at 100%
            matched_code_percent = min(round(matched_code_percent, 7), 100.0)
            fuzzy_match_percent = min(round(fuzzy_match_percent, 7), 100.0)
            matched_functions_percent = min(round(matched_functions_percent, 7), 100.0)

            # Update the measures
            measures['total_code'] = str(total_code) if isinstance(measures.get('total_code'), str) else total_code
            measures['total_functions'] = total_functions
            measures['matched_code_percent'] = matched_code_percent
            measures['fuzzy_match_percent'] = fuzzy_match_percent
            measures['matched_functions_percent'] = matched_functions_percent

    # Update global measures if any junk was removed
    if total_junk_code_removed > 0 or total_junk_functions_removed > 0:
        global_measures = data.get('measures', {})

        # Remember original types for consistent output
        global_total_code_orig = global_measures.get('total_code', 0)
        global_total_functions_orig = global_measures.get('total_functions', 0)

        # Update global total_code and total_functions
        global_total_code = int(global_total_code_orig) if isinstance(global_total_code_orig, str) else global_total_code_orig
        global_total_code -= total_junk_code_removed

        global_total_functions = int(global_total_functions_orig) if isinstance(global_total_functions_orig, str) else global_total_functions_orig
        global_total_functions -= total_junk_functions_removed

        # Get current global percentages and add junk percentages to them
        global_matched_code_percent = global_measures.get('matched_code_percent', 0.0)
        if isinstance(global_matched_code_percent, str):
            global_matched_code_percent = float(global_matched_code_percent)
        global_fuzzy_match_percent = global_measures.get('fuzzy_match_percent', 0.0)
        if isinstance(global_fuzzy_match_percent, str):
            global_fuzzy_match_percent = float(global_fuzzy_match_percent)
        global_matched_functions_percent = global_measures.get('matched_functions_percent', 0.0)
        if isinstance(global_matched_functions_percent, str):
            global_matched_functions_percent = float(global_matched_functions_percent)

        # Calculate the original global total_code (before removing junk)
        original_global_total_code = global_total_code + total_junk_code_removed
        original_global_total_functions = global_total_functions + total_junk_functions_removed

        # Calculate global junk percentages and add them to existing percentages
        if original_global_total_code > 0:
            global_junk_code_percent = (total_junk_code_removed / original_global_total_code) * 100
            global_matched_code_percent += global_junk_code_percent
            global_fuzzy_match_percent += global_junk_code_percent

        if original_global_total_functions > 0:
            global_junk_function_percent = (total_junk_functions_removed / original_global_total_functions) * 100
            global_matched_functions_percent += global_junk_function_percent

        # Clamp global percentages at 100% after rounding
        global_matched_code_percent = min(round(global_matched_code_percent, 7), 100.0)
        global_fuzzy_match_percent = min(round(global_fuzzy_match_percent, 7), 100.0)
        global_matched_functions_percent = min(round(global_matched_functions_percent, 7), 100.0)

        # Update global measures
        global_measures['total_code'] = str(global_total_code) if isinstance(global_measures.get('total_code'), str) else global_total_code
        global_measures['total_functions'] = global_total_functions
        global_measures['matched_code_percent'] = global_matched_code_percent
        global_measures['fuzzy_match_percent'] = global_fuzzy_match_percent
        global_measures['matched_functions_percent'] = global_matched_functions_percent

    # Update category measures if any junk was removed from categories
    if category_junk_removals:
        categories = data.get('categories', [])

        for category in categories:
            category_id = category.get('id', '')
            if category_id not in category_junk_removals:
                continue

            removals = category_junk_removals[category_id]
            junk_code_removed = removals['code']
            junk_functions_removed = removals['functions']

            if junk_code_removed == 0 and junk_functions_removed == 0:
                continue

            category_measures = category.get('measures', {})

            # Remember original types for consistent output
            cat_total_code_orig = category_measures.get('total_code', 0)
            cat_total_functions_orig = category_measures.get('total_functions', 0)

            # Update category total_code and total_functions
            cat_total_code = int(cat_total_code_orig) if isinstance(cat_total_code_orig, str) else cat_total_code_orig
            cat_total_code -= junk_code_removed

            cat_total_functions = int(cat_total_functions_orig) if isinstance(cat_total_functions_orig, str) else cat_total_functions_orig
            cat_total_functions -= junk_functions_removed

            # Get current category percentages and add junk percentages to them
            cat_matched_code_percent = category_measures.get('matched_code_percent', 0.0)
            if isinstance(cat_matched_code_percent, str):
                cat_matched_code_percent = float(cat_matched_code_percent)
            cat_fuzzy_match_percent = category_measures.get('fuzzy_match_percent', 0.0)
            if isinstance(cat_fuzzy_match_percent, str):
                cat_fuzzy_match_percent = float(cat_fuzzy_match_percent)
            cat_matched_functions_percent = category_measures.get('matched_functions_percent', 0.0)
            if isinstance(cat_matched_functions_percent, str):
                cat_matched_functions_percent = float(cat_matched_functions_percent)

            # Calculate the original category totals (before removing junk)
            original_cat_total_code = cat_total_code + junk_code_removed
            original_cat_total_functions = cat_total_functions + junk_functions_removed

            # Calculate category junk percentages and add them to existing percentages
            if original_cat_total_code > 0:
                cat_junk_code_percent = (junk_code_removed / original_cat_total_code) * 100
                cat_matched_code_percent += cat_junk_code_percent
                cat_fuzzy_match_percent += cat_junk_code_percent

            if original_cat_total_functions > 0:
                cat_junk_function_percent = (junk_functions_removed / original_cat_total_functions) * 100
                cat_matched_functions_percent += cat_junk_function_percent

            # Clamp category percentages at 100% after rounding
            cat_matched_code_percent = min(round(cat_matched_code_percent, 7), 100.0)
            cat_fuzzy_match_percent = min(round(cat_fuzzy_match_percent, 7), 100.0)
            cat_matched_functions_percent = min(round(cat_matched_functions_percent, 7), 100.0)

            # Update category measures
            category_measures['total_code'] = str(cat_total_code) if isinstance(category_measures.get('total_code'), str) else cat_total_code
            category_measures['total_functions'] = cat_total_functions
            category_measures['matched_code_percent'] = cat_matched_code_percent
            category_measures['fuzzy_match_percent'] = cat_fuzzy_match_percent
            category_measures['matched_functions_percent'] = cat_matched_functions_percent

    # Write output file
    try:
        with open(output_path, 'w', encoding='utf-8') as outfile:
            json.dump(data, outfile, indent=4)
    except IOError as e:
        raise IOError(f"Error writing to {output_path}: {e}") from e

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <input_report.json> <output_report.json>")
        sys.exit(1)
    input_file = sys.argv[1]
    output_file = sys.argv[2]
    clean_report(input_file, output_file)
