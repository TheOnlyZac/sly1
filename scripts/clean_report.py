"""
Cleans an objdiff report.json by removing any functions starting with "junk_".
"""
import json

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
    with open(input_path, 'r', encoding='utf-8') as infile:
        data = json.load(infile)

    # Track global changes for updating the main measures
    total_junk_code_removed = 0
    total_junk_functions_removed = 0

    # Process each unit in the data
    for unit in data.get('units', []):
        functions = unit.get('functions', [])
        if not functions:
            continue

        # Get current unit measures
        measures = unit.get('measures', {})
        total_code = measures.get('total_code', 0)
        total_functions = measures.get('total_functions', 0)
        matched_code_percent = measures.get('matched_code_percent', 0.0)
        fuzzy_match_percent = measures.get('fuzzy_match_percent', 0.0)
        matched_functions_percent = measures.get('matched_functions_percent', 0.0)

        # Convert total_code to int if it's a string
        if isinstance(total_code, str):
            total_code = int(total_code)

        # Process junk functions
        junk_functions = []
        unit_junk_code_removed = 0
        unit_junk_functions_removed = 0

        for i, function in enumerate(functions):
            if function.get('name', '').startswith('junk_'):
                junk_functions.append(i)

                # Get function size
                function_size = function.get('size', 0)
                if isinstance(function_size, str):
                    function_size = int(function_size)

                # Track removals for global measures
                unit_junk_code_removed += function_size
                unit_junk_functions_removed += 1

                # Calculate percentages
                if total_code > 0:
                    junk_code_percent = (function_size / total_code) * 100
                    matched_code_percent += junk_code_percent
                    fuzzy_match_percent += junk_code_percent

                if total_functions > 0:
                    junk_function_percent = (1 / total_functions) * 100
                    matched_functions_percent += junk_function_percent

                # Update total_code and total_functions
                total_code -= function_size
                total_functions -= 1

        # Add unit removals to global totals
        total_junk_code_removed += unit_junk_code_removed
        total_junk_functions_removed += unit_junk_functions_removed

        # Remove junk functions from the functions list (in reverse order to maintain indices)
        for i in reversed(junk_functions):
            functions.pop(i)

        # Update measures with new values
        if junk_functions:  # Only update if we removed junk functions
            # Check for approximately 100% and set to exactly 100.0
            if abs(matched_code_percent - 100.0) < 0.001:
                matched_code_percent = 100.0
            if abs(fuzzy_match_percent - 100.0) < 0.001:
                fuzzy_match_percent = 100.0
            if abs(matched_functions_percent - 100.0) < 0.001:
                matched_functions_percent = 100.0

            # Round percentages to 7 decimal places
            matched_code_percent = round(matched_code_percent, 7)
            fuzzy_match_percent = round(fuzzy_match_percent, 7)
            matched_functions_percent = round(matched_functions_percent, 7)

            # Update the measures
            measures['total_code'] = str(total_code) if isinstance(measures.get('total_code'), str) else total_code
            measures['total_functions'] = total_functions
            measures['matched_code_percent'] = matched_code_percent
            measures['fuzzy_match_percent'] = fuzzy_match_percent
            measures['matched_functions_percent'] = matched_functions_percent

    # Update global measures if any junk was removed
    if total_junk_code_removed > 0 or total_junk_functions_removed > 0:
        global_measures = data.get('measures', {})

        # Update global total_code and total_functions
        global_total_code = global_measures.get('total_code', 0)
        if isinstance(global_total_code, str):
            global_total_code = int(global_total_code)
        global_total_code -= total_junk_code_removed

        global_total_functions = global_measures.get('total_functions', 0)
        global_total_functions -= total_junk_functions_removed

        # Get current global percentages and add junk percentages to them
        global_matched_code_percent = global_measures.get('matched_code_percent', 0.0)
        global_fuzzy_match_percent = global_measures.get('fuzzy_match_percent', 0.0)
        global_matched_functions_percent = global_measures.get('matched_functions_percent', 0.0)

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

        # Check for approximately 100% and set to exactly 100.0
        if abs(global_matched_code_percent - 100.0) < 0.001:
            global_matched_code_percent = 100.0
        if abs(global_fuzzy_match_percent - 100.0) < 0.001:
            global_fuzzy_match_percent = 100.0
        if abs(global_matched_functions_percent - 100.0) < 0.001:
            global_matched_functions_percent = 100.0

        # Round global percentages to 7 decimal places
        global_matched_code_percent = round(global_matched_code_percent, 7)
        global_fuzzy_match_percent = round(global_fuzzy_match_percent, 7)
        global_matched_functions_percent = round(global_matched_functions_percent, 7)

        # Update global measures
        global_measures['total_code'] = str(global_total_code) if isinstance(global_measures.get('total_code'), str) else global_total_code
        global_measures['total_functions'] = global_total_functions
        global_measures['matched_code_percent'] = global_matched_code_percent
        global_measures['fuzzy_match_percent'] = global_fuzzy_match_percent
        global_measures['matched_functions_percent'] = global_matched_functions_percent

    with open(output_path, 'w', encoding='utf-8') as outfile:
        json.dump(data, outfile, indent=4)

if __name__ == "__main__":
    clean_report('report.json', 'report.json')
