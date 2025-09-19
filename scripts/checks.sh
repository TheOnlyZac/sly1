#!/bin/bash

set -e

script_dir=$(dirname $0)
pushd $script_dir/.. > /dev/null

python3 configure.py --clean && ninja
python3 configure.py --clean --objects && ninja
./tools/objdiff/objdiff-cli report generate > /dev/null
