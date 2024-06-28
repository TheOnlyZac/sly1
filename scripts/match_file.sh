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

# Set working dir to project dir and make object file
project_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/.."
codematcher_path="$project_dir/tools/codematcher"
pushd $project_dir > /dev/null
echo "Compiling $source_basename.o..."
make clean > /dev/null
make obj/debug/$source_basename.o > /dev/null

# CD to codematcher directory and invoke codematcher with the compiled object file
echo "Matching $source_basename.o..."
cd tools/codematcher >/dev/null
./codematcher may_proto.elf --match "$project_dir/obj/debug/$source_basename.o"

# Move back to the original directory
popd >/dev/null
popd >/dev/null
