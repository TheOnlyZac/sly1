import json
import sys

try:
    with open("report.json", "r") as f:
        data = json.load(f)
except FileNotFoundError:
    print("Error: \"report.json\" not found. Please run \"./scripts/checks.sh --report\" first to generate the report file.")
    sys.exit(1)

for category in data["categories"]:
    name = category.get("name")
    if name != "Engine" and name != "Splice":
        continue
    
    measures = category.get("measures", {})

    fuzzy_match_percent = measures.get("fuzzy_match_percent", 0.0)
    total_code = int(measures.get("total_code", 0)) / 1024
    matched_code = int(measures.get("matched_code", 0)) / 1024
    matched_code_percent = measures.get("matched_code_percent", 0.0)

    total_data = int(measures.get("total_data", 0)) / 1024
    matched_data = int(measures.get("matched_data", 0)) / 1024
    matched_data_percent = measures.get("matched_data_percent", 0.0)

    total_functions = measures.get("total_functions")
    matched_functions = measures.get("matched_functions")
    
    print(f"{name}:")
    print(f"  - Fuzzy match:       {fuzzy_match_percent:.2f}%")
    print(f"  - Perfect match:     {matched_code_percent:.2f}% ({matched_code:.2f} KiB / {total_code:.2f} KiB)")
    print(f"  - Matched data:      {matched_data_percent:.2f}% ({matched_data:.2f} KiB / {total_data:.2f} KiB)")
    print(f"  - Matched functions: {matched_functions} / {total_functions}\n")