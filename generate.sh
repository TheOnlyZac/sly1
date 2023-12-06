#!/bin/bash

echo "Generating docs..."

# Delete old docs
rm -rf ./docs

# Init submodules
git submodule update --init --recursive

# Clone the codebase
git clone https://github.com/theonlyzac/sly1

# Generate docs
cd sly1
doxygen Doxyfile
mv docs/ ..

# Delete the codebase
cd ..
rm -rf sly1

echo Successfully generated docs in ./docs.
