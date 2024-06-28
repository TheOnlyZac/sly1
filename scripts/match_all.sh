#!/bin/bash

# Set working dir to codematcher directory
project_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/.."
codematcher_path="$project_dir/tools/codematcher"
pushd $codematcher_path > /dev/null

# Invoke codematcher to compile and match source tree
echo "Matching source tree..."
source_tree_path="$project_dir/src/P2"
./codematcher may_proto.elf --compile $source_tree_path

# Done
popd > /dev/null
