#!/bin/bash

# Get the name of the source file as a parameter
source_file="$1"

# Check if the source file parameter is empty
if [ -z "$source_file" ]; then
    echo "No source file specified!"
    echo "    Usage: $0 <source_file>"
    exit 1
fi

# Strip the extension from the source file
source_basename="$(basename "$source_file" | cut -d. -f1)"

# Get the directory of the script
script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Move one level above the script
pushd "$script_dir/.." >/dev/null

# Call make to compile the object file
echo "Compiling $source_basename.o..."
make "obj/debug/$source_basename.o"

# Move to the script directory
popd >/dev/null
pushd "$script_dir" >/dev/null

# Invoke codematcher with the compiled object file
echo "Matching $source_basename.o..."
./codematcher may_proto.elf --match "../obj/debug/$source_basename.o"

# Move back to the original directory
popd >/dev/null
