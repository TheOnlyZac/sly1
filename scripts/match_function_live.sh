#!/bin/bash

# Get name of source file and target function as parameters
source_file="$1"
target_function="$2"

# Check if the source file parameter is empty
if [ -z "$source_file" ]; then
    echo "No source file specified!"
    echo "    Usage: $0 <source_file> <target_function>"
    exit 1
fi

# Check if the target function parameter is empty
if [ -z "$target_function" ]; then
    echo "No target function specified!"
    echo "    Usage: $0 <source_file> <target_function>"
    exit 1
fi

# Strip the extension from the source file
source_basename="$(basename "$source_file" | cut -d. -f1)"

# Match command: match_file script grepped with relevant lines
match_cmd="./match_file.sh $source_file | grep -e'------------' -e'+' -e'$target_function'"

# Print command: ee-objdump grepped with regex matching everything from the function name to a blank line
objdump_cmd="wine ~/.wine/drive_c/usr/local/sce/ee/gcc/bin/ee-objdump.exe -d ../obj/debug/$source_basename.o | grep -e'$target_function' -A1000 -e'^$'"

# Watch the match_single script with the source file and dump file commands
watch -n 1 --color "( $match_cmd && $objdump_cmd )"
