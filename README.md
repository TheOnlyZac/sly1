# Sly Cooper and the Thievius Raccoonus
<!-- Readme badges -->

[![Build status][build-badge]][build-url] [![AppVeyor tests][tests-badge]][tests-url] [![Contributors][contributors-badge]][contributors-url] [![Discord Channel][discord-badge]][discord-url]

<!-- Build status links -->
[build-url]: https://ci.appveyor.com/project/TheOnlyZac/sly1/branch/main
[build-badge]: https://ci.appveyor.com/api/projects/status/800esepa77ctpv5p/branch/main?svg=true

<!-- Test status links -->
[tests-url]: https://ci.appveyor.com/project/TheOnlyZac/sly1/branch/main/tests
[tests-badge]: https://img.shields.io/appveyor/tests/theonlyzac/sly1/main

<!-- Contributors badge links -->
[contributors-url]: https://github.com/theonlyzac/sly1/graphs/contributors
[contributors-badge]: https://img.shields.io/github/contributors/theonlyzac/sly1?color=%23006ED1

<!-- Discord badge links -->
[discord-url]: https://discord.gg/2GSXcEzPJA
[discord-badge]: https://img.shields.io/discord/439454661100175380?color=%23006ED1&logo=discord&logoColor=%23FFFFFF

This is a work-in-progress, experimental decompilation of *Sly Cooper and the Thievius Raccoonus* for the PlayStation 2. It is based on the NTSC-U version of the game (`SCUS-971.98`).

The goal of this project is to better understand how the game works. **This repo does not contain any game assets or original code from the game's executable.**

New contributors are welcome and encouraged to make a pull request! If you would like to help but aren't sure where to start, you can [join our discord server][discord-url] and/or message [TheOnlyZac#0269](https://discordapp.com/channels/@me/TheOnlyZac#0269/) for more info and advice on where to begin.

## Frequently Asked Questions

#### What is a decompilation?
When the developers created the game they wrote programming code that we call the source code. Then, they compiled the source code into machine code that can run on the PS2. Our job is to reverse-engineer the compiled code and produce new, original code that behaves the same way. This process leaves us with code that is very similar (but not identical) to the source code and helps us understand what the programmers were thinking when they made the game.

#### How does it work?
We use a tool called [Ghidra](https://ghidra-sre.org/) which was created by the [NSA](https://www.nsa.gov/) for reverse-engineering software. Ghidra analyzes the game binary to identity functions, variables, data types and structures. We then reimplement each individual function by writing C++ code that produces the same output. We do not copy/paste any code or include any original assembly code from the game binary in the decompilation.

#### Has this ever been done before?
This is one of the first-ever large scale PS2 decompilation projects. Our inspiration comes from other decomp projects such as the [Super Mario 64 decomp](https://github.com/n64decomp/sm64) for the N64 and the [Breath of the Wild decomp](https://github.com/zeldaret/botw) for the Wii U (the latter is more similar in scope to what we are trying to do). There is also a Jak & Daxter decomp/PC port called [OpenGOAL](https://github.com/open-goal/jak-project), though that game is written in 98% GOAL language, not native PS2 code.

#### Is this a matching decomp?
Due to the lack of resources on PS2 reverse-engineering, the currently decompiled code is not matching. However, we are actively researching the PS2 compiler and working to come up with with a process for function matching.

#### How can I help?
If you would like to contribute but have no idea where to start, you can [join our discord server](https://discord.gg/gh5xwfj) and/or reach out to [TheOnlyZac#0269](https://discordapp.com/channels/@me/TheOnlyZac#0269/) for some resources and advice to get started!

## Getting Started

### Windows - Visual Studio

*Prerequisites: C++ CMake tools for Windows*

Clone the repo and open Visual Studio. Click `File > Open > CMake...` and open the file `CMakeLists.txt` in the main project folder. To build and run the main test program, set your startup item to `main.exe`.

For unit testing, build the target "Check" and the tests should appear in the Test Explorer window. It will run the tests, and the results will show in the Test Explorer as well as the Output window.

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

For testing, cd into the build directory and run `cmake --build . --target check` or `make check` to build the tests. Then run the tests with `ctest -C Debug`.

## Style Guide

### General

Our goal is to imitate the original source code as closely as possible based on symbols from the publicly available [May 2002 demo](https://hiddenpalace.org/Sly_Cooper_and_the_Thievius_Raccoonus_(May_19,_2002_prototype)). Please try to follow these guidelines when writing your code:
* Use official names from the debug symbols wherever possible.
* Indent with tabs, not spaces
* Put project includes before library includes.

### Symbol Names

For the most part, variables are named according to [Hungarian Notation](https://en.wikipedia.org/wiki/Hungarian_notation). The following prefixes are used to denote the type of a variable/symbol:
* `p` - Pointer
* `n` - Integer/number
* `c` - Integer/count of items
* `f` - Boolean/flag
* `l` - Long
* `d` - Float
* `u` - Unsigned
* `b` - Byte
* `ch` - Char
* `z` - Zero-terminated string
* `C` - Class name

The following prefixes are used to denote the scope of a variable:
* `g_` - Global variable
* `m_` - Class member
* `s_` - Static class member

Here are some examples of symbol names that combine the above prefixes:
* `ccoin`, `clife`, `ccharm` - Count of coins, lives, and charms
* `fSneakyFeet` - Flag that denotes whether Sly's footsteps make guitar noises
* `g_pgsCur` - Global pointer to the game's current GS struct
* `g_pchzArgs` - Global pointer to a zero-terminated char array of arguments
* `CBinaryInputStream` - Name of the class that handles reading data from binary streams
* `m_cbBulkData` - Member variable that stores the count of bytes in a data block

### Capitalization

Please try to stick to the following capitalization schemes:
* Use `ALLCAPS` for struct/enum names.
    * eg. `struct DIFFICULTY`, `enum class FLS`
* Use `UpperCamelCase` for function/class names and enum values.
    * eg. `void OnDifficultyGameLoad()`, `class CTransition`, `FCHT::InfiniteCharms`
* Use `lowerCamelCase` for local variables, function parameters, and class members.
    * eg. `char nextXorChar`, `Coin* pcoin`, `float m_rxScale`
