#!/bin/bash

# A simple script to set up the ProDG compilers + SCE Runtime Library
# to build the Sly 1 decompilation project.

WINE_ROOT=~/.wine/drive_c
TOP=$(pwd)

# The SDK (Runtime Library) version to install.
SDK_VER=242

die() { # perl-style `die` expressions.
	echo "Error: $@"
	exit 1
}

# downloads files and uses b2sum(1) to verify integrity
download_and_check() {
	echo "Downloading $1 and b2sums..."
	wget -qP /tmp $1
	wget -qP /tmp $1.b2

	BASENAME=$(basename $1)
		b2sum -c /tmp/$BASENAME.b2 || die "b2sums failed to verify when downloading $1"

		echo "b2sums verified, moving files out of /tmp"
		rm /tmp/$BASENAME.b2 # No longer needed
		mv /tmp/$BASENAME $TOP
}

# downloads files without checking integrity
download() {
	echo "Downloading $1..."
	wget -qP /tmp $1

	BASENAME=$(basename $1)

		echo "moving files out of /tmp"
		mv /tmp/$BASENAME $TOP
}

echo Starting ProDG setup script...

# download required files (registry + SDK package)
download "https://computernewb.com/~lily/sly1/prodg_sce$SDK_VER.7z"

# apply environment variables from the registry file
wine regedit prodg_env.reg

# Extract the SDK into the wine C drive root
echo "Extracting SDK to $WINE_ROOT..."
7z x -y $TOP/prodg_sce$SDK_VER.7z -o$WINE_ROOT

# Copy the compiler to tools/cc/ee-gcc2.9-991111/bin
echo "Copying compiler to tools dir..."
mkdir -p $TOP/tools/cc/ee-gcc2.9-991111/bin
cp $WINE_ROOT/usr/local/sce/ee/gcc/bin/ee-gcc.exe $TOP/tools/cc/ee-gcc2.9-991111/bin

echo "Removing temporary files..."
rm prodg_sce$SDK_VER.7z

echo "Setup complete!"
