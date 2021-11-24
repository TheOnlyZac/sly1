# Sly Cooper and the Thievius Raccoonus

This is an experimental decompilation of Sly Cooper and the Thievius Raccoonus for the PlayStation 2. The project is based on the NTSC-U version of the game (SCUS-971.98).

The goal of this project is to better understand how the game works. This repo does not contain any game assets or original code from the game's executable.

## Beginner's Guide

### Windows - Visual Studio

First, clone the repo to your PC. Then open Visual Studio, click `File > Open > CMake...`, and open the file `CMakeLists.txt`. To build and run the main program, set your startup item to `main.exe`.

## Testing

To execute unit testing, first build the tests with `CMake > Build Only > Check`. Then run the tests with `CMake > Tests > Run CTests`. The results will show in the Output window and the Test Explorer.

### Windows/Unix - MSYS2 MINGW64/UCRT64 - GNU/Linux

Prerequisites: gcc (optionally clang), cmake, ninja, git

```bash
git clone https://github.com/TheOnlyZac/sly1
cd sly1
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j8
```

## Testing

You can run `cmake --build . --target check && ctest .`  or `make check` in the build directory in order to run tests.