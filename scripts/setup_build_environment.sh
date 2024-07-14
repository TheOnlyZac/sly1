#!/bin/bash

set -e

# Get script directory
script_dir=$(dirname $0)
pushd $script_dir > /dev/null

# Check if sudo
if [ "$EUID" -ne 0 ]
  then echo "Installing packages requires sudo, run the script with sudo."
  exit
fi

# Update packages
apt-get update

# Setup wine
sudo dpkg --add-architecture i386
sudo apt-get update
sudo apt-get install wine32

# Install MIPS assembler
sudo apt-get install binutils-mips-linux-gnu

# Setup compiler
./setup-progd-linux.sh

popd > /dev/null
echo "Build environment setup complete."
echo "Next, copy the elf from your copy of the game to the 'disc' directory."
echo "Then use the 'build.sh' script to build the elf."

