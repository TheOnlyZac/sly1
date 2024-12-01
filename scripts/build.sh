#!/bin/bash

# Get directory of this script
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

# CD into project dir
cd $DIR/..

# Ensure disc/SCUS_971.98 exists
if [ ! -f disc/SCUS_971.98 ]; then
  echo "Error: SCUS_971.98 not found. Copy it from your own game disc to the 'disc' directory of this project."
  exit
fi

# Configure and build
python3 configure.py --clean
ninja
