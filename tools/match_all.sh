#!/bin/bash

# Source tree path is absolute path to ../src/P2
source_tree_path="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/../src/P2"

# Invoke codematcher to compile and match source tree
echo "Matching source tree..."
./codematcher may_proto.elf --compile $source_tree_path
