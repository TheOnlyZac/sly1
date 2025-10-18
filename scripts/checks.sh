#!/bin/bash

set -e

script_dir=$(dirname $0)
pushd $script_dir/.. > /dev/null

python3 configure.py --clean && ninja
python3 configure.py --clean --objects && ninja

# Output the progress report to a file if --report is not passed, otherwise discard it.
if [[ "$1" == "--report" ]]; then
    ./tools/objdiff/objdiff-cli report generate > report.json
else
    ./tools/objdiff/objdiff-cli report generate > /dev/null
fi
