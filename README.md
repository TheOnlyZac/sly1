# Sly Cooper and the Thievius Raccoonus

This is an experimental decompilation of Sly Cooper and the Thievius Raccoonus for the PlayStation 2. The project is a work-in-progress, and based on the NTSC-U version of the game `(`SCUS-971.98`).

The goal of this project is to better understand how the game works. This repo does not contain any game assets or original code from the game's executable.

## Getting Started

### Windows - Visual Studio

Clone the repo to your machine and open Visual Studio. Click `File > Open > CMake...` and open the file `CMakeLists.txt` in the main project folder. To build and run the main program, set your startup item to `main.exe`.

#### Testing

Build the solution with `Build > Build All` and run tests in the Test Explorer window. The results will show in the Test Explorer and the Output window.

### Windows/Unix - MSYS2 MINGW64/UCRT64 - GNU/Linux

Prerequisites: gcc (optionally clang), cmake, ninja, git, and base-devel

```bash
git clone https://github.com/TheOnlyZac/sly1
cd sly1
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j8
```

#### Testing

In the build directory, run `cmake --build . --target check && ctest .`  or `make check` to run tests.

## Style Guide

Our goal is to imitate the original source code as closely as possible based on the debug symbols from the [May 2002 prototype](https://hiddenpalace.org/Sly_Cooper_and_the_Thievius_Raccoonus_(May_19,_2002_prototype)).

* Original symbol names should be used wherever possible.
* Use `ALLCAPS` for struct and enum names.
* Use `UpperCamelCase` for function names, class names, and enum values.
* Use `lowerCamelCase` for variables, function params, and class members.
* Name variables according to [Hungarian Notation](https://en.wikipedia.org/wiki/Hungarian_notation), which uses letter prefixes to denote the type.
* Project includes should come before library includes.
