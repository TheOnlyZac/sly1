#!/bin/bash

# ##############################################################################
# Set these paths to point to your PCSX2 1.7 executable and your copy of the game
PCSX2_PATH="/opt/pcsx2-v1.7.AppImage"
ISO_PATH=""
# ##############################################################################

# Exit on error
set -e

# Function to print an error message and exit
die() {
	echo "run.sh: error: $@"
	exit 1
}

# Error if PCSX2 path is empty
if [ -z "$PCSX2_PATH" ]; then
    die PCSX2 path is empty, please edit the paths in 'scripts/run.sh'
    exit 1
fi

# Warn if ISO path is empty
if [ -z "$ISO_PATH" ]; then
    echo "Warning: ISO path is empty, please edit the paths in 'scripts/run.sh'"
# Error if ISO path is not valid
elif [ ! -f "$ISO_PATH" ]; then
    die Game ISO not found at '$ISO_PATH'
    exit 1
fi

# Error if PCSX2 is not valid
if [ ! -f "$PCSX2_PATH" ]; then
    die PCSX2 executable not found at '$PCSX2_PATH'
    exit 1
fi

# Show error message if PCSX2 is not executable
if [ ! -x "$PCSX2_PATH" ]; then
    die PCSX2 executable is not executable
    exit 1
fi

# Switch to the project root directory
pushd "$(dirname "$0")/.." > /dev/null

# Build the game
echo Compiling ELF...
#make clean > /dev/null
make > /dev/null

# Run the game
echo Booting ELF in PCSX2...
"$PCSX2_PATH" -nogui -console -elf "./bin/debug/SCUS_971.98" "$ISO_PATH"

# Switch back to the original directory
popd > /dev/null
echo Done.
