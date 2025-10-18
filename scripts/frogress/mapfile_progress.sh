#!/bin/bash

set -e

script_dir=$(dirname $0)
pushd $script_dir/../.. > /dev/null

if [[ "$1" == "--help" || "$1" == "-h" ]]; then
    echo "Usage: $0 [--skip-build]"
    echo "  --skip-build: Skip building and just check progress"
    exit 0
fi

if [[ "$1" != "--skip-build" ]]; then
    ./scripts/build.sh
fi

python3 -m mapfile_parser progress out/SCUS_971.98.map asm asm/nonmatchings/

popd > /dev/null
