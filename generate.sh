#!/bin/bash

OUTDIR=html

set -e
echo "Generating docs in ./$OUTDIR..."


# Delete old docs
rm -rf ./html

# Init submodules
git submodule update --init --recursive

# Clone the codebase
git clone https://github.com/theonlyzac/sly1

# Copy doxyfile into the codebase
cp Doxyfile sly1
cd sly1

# Delete "#include "common.h" from all hedaers in include/
for file in $(find include/ -name "*.h"); do
    sed -i '/#include "common.h"/d' $file
done

# Generate docs
doxygen Doxyfile
cp -r docs html
mv html/ ..

# Delete the codebase
cd ..
rm -rf sly1

echo Successfully generated docs in ./$OUTDIR.
