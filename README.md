# Sly Cooper and the Thievius Raccoonus

This is an experimental decompilation of Sly Cooper and the Thievius Raccoonus for the PlayStation 2. The project is based on the NTSC-U version of the game (SCUS-971.98).

The goal of this project is to better understand how the game works. This repo does not contain any game assets or original code from the game's executable.

## Beginner's Guide

### Windows - Visual Studio

First, clone the repo to your PC. Then open Visual Studio, click `File > Open > CMake...`, and open the file `CMakeLists.txt`.

To compile and run, make sure your startup item is `test.exe (Sly1Decomp\src\test.exe)`. This will build the project and execute the tests in `main.cpp`.

### Windows/Unix - MSYS2 MINGW64/UCRT64 - GNU/Linux

Prereqs: gcc (optionally clang), cmake, ninja, git, (maybe others like base-devel)

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