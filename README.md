# Sly Cooper and the Thievius Raccoonus
<!-- Readme badges -->
[![Contributors][contributors-badge]][contributors-url] [![Discord Channel][discord-badge]][discord-url]

<!-- Contributors badge links -->
[contributors-url]: https://github.com/theonlyzac/sly1/graphs/contributors
[contributors-badge]: https://img.shields.io/github/contributors/theonlyzac/sly1?color=%23006ED1

<!-- Discord badge links -->
[discord-url]: https://discord.gg/gh5xwfj
[discord-badge]: https://img.shields.io/discord/439454661100175380?color=%23006ED1&logo=discord&logoColor=%23FFFFFF

This is a work-in-progress, experimental decompilation of *Sly Cooper and the Thievius Raccoonus* for the PlayStation 2. It is based on the NTSC-U version of the game (`SCUS-971.98`).

The goal of this project is to better understand how the game works to assist the speedrunning, glitch hunting and modding communities. **This repo does not contain any game assets or original code from the game's executable.**

New contributors are welcome and encouraged! If you would like to help but aren't sure where to start, you can [join our discord server](https://discord.gg/gh5xwfj) and/or message [TheOnlyZac#0269](https://discordapp.com/channels/@me/TheOnlyZac#0269/) for more info and advice.

## Getting Started

### Windows - Visual Studio

Clone the repo and open Visual Studio. Click `File > Open > CMake...` and open the file `CMakeLists.txt` in the main project folder. To build and run the main test program, set your startup item to `main.exe`.

#### Tests

Build the solution with `Build > Build All` and the tests should appear in the Test Explorer window. After running a test, the results will show in the Test Explorer and the Output window.

### Windows/Unix - MSYS2 MINGW64/UCRT64 - GNU/Linux

*Prerequisites: gcc (optionally clang), cmake, ninja, git, and base-devel*

```bash
git clone https://github.com/TheOnlyZac/sly1
cd sly1
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j8
```

#### Tests

In the build directory, run `cmake --build . --target check && ctest .`  or `make check` to run tests.

## Style Guide

Our goal is to imitate the original source code as closely as possible based on the debug symbols from the [May 2002 prototype](https://hiddenpalace.org/Sly_Cooper_and_the_Thievius_Raccoonus_(May_19,_2002_prototype)).

* Official names from the debug symbols should be used wherever possible.
* Use `ALLCAPS` for struct/enum names.
    * eg. `DIFFICULTY`, `COIN`, `FLS`
* Use `UpperCamelCase` for function/class names and enum values.
    * eg. `GLimitLm`, `ChangeSuck`, `OnDifficultyGameLoad`
* Use `lowerCamelCase` for variables, function parameters, and class members.
    * eg. `g_pgsCur`, `pCoin`, `nextXorChar`
* Name variables according to [Hungarian Notation](https://en.wikipedia.org/wiki/Hungarian_notation), which uses letter prefixes to denote the type.
* Project includes should come before library includes.
