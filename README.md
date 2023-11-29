# Sly Cooper and the Thievius Raccoonus

<!-- shields.io badges -->
[![Build status][build-badge]][build-url] <!--[![AppVeyor tests][tests-badge]][tests-url]--> [![Discord Channel][discord-badge]][discord-url] [![Wiki][wiki-badge]][wiki-url] [![Contributors][contributors-badge]][contributors-url]

<!-- Build status badge -->
[build-url]: https://ci.appveyor.com/project/TheOnlyZac/sly1/branch/main
[build-badge]: https://ci.appveyor.com/api/projects/status/800esepa77ctpv5p/branch/main?svg=true

<!-- Test status badge -->
[tests-url]: https://ci.appveyor.com/project/TheOnlyZac/sly1/branch/main/tests
[tests-badge]: https://img.shields.io/appveyor/tests/theonlyzac/sly1/main

<!-- Contributors badge -->
[contributors-url]: https://github.com/theonlyzac/sly1/graphs/contributors
[contributors-badge]: https://img.shields.io/github/contributors/theonlyzac/sly1?color=%23006ED1

<!-- Discord badge -->
[discord-url]: https://discord.gg/2GSXcEzPJA
[discord-badge]: https://img.shields.io/discord/439454661100175380?color=%23006ED1&logo=discord&logoColor=%23FFFFFF

<!-- Wiki badge -->
[wiki-url]: https://slymods.info
[wiki-badge]: https://img.shields.io/badge/wiki-slymods.info-006ED1

This is a work-in-progress decompilation of [*Sly Cooper and the Thievius Raccoonus*](https://en.wikipedia.org/wiki/Sly_Cooper_and_the_Thievius_Raccoonus) for the PlayStation 2. It is based on the NTSC-U version of the game (`SCUS-971.98`). Documentation of the game's internal structures and mechanics can be found on the [SlyMods Wiki][wiki-url].

The goal of this project is to better understand how the game works. **This repo does not contain any game assets or code from the game's executable.**

New contributors are welcome and encouraged to make a pull request! If you would like to help but aren't sure where to begin, you can [join our Discord server][discord-url] and/or read [CONTRIBUTING.md](/CONTRIBUTING.MD) for info on how to get started.


## Frequently Asked Questions

#### What is a decompilation?

When the developers created the game they wrote programming code that we call the source code. Then they compiled the source code into machine code that can run on the PS2. Our job is to reverse-engineer the compiled code and produce new, original code that behaves the same way. This process leaves us with code that is very similar (but not identical) to the source code and helps us understand what the programmers were thinking when they made the game.

#### How does it work?

We use a tool called [Ghidra](https://ghidra-sre.org/) which was created by the [NSA](https://www.nsa.gov/) for reverse-engineering software. Ghidra analyzes the game binary to identity functions, variables, data types and structures. We then reimplement each individual function by writing C++ code that produces the same output. We do not copy/paste any code or include any original assembly code from the game binary in the decompilation.

#### Has this ever been done before?

This is one of the first large-scale PS2 decompilation projects. We take inspiration from other projects like the [Super Mario 64 decomp](https://github.com/n64decomp/sm64) for the N64 and the [Breath of the Wild decomp](https://github.com/zeldaret/botw) for the Wii U (the latter being more similar in scope to this project). There is also a Jak & Daxter decomp/PC port called [OpenGOAL](https://github.com/open-goal/jak-project), though that game is written in 98% GOAL language rather than C/C++.

#### Is this a matching decomp?

Most of the decompiled code is not yet matching. We are actively researching the PS2 compiler and working to come up with with a process for function matching.

#### How can I help?

If you would like to contribute but have no idea where to start, you can [join our discord server](https://discord.gg/gh5xwfj) and/or read [CONTRIBUTING.md](/CONTRIBUTING.MD) for some resources and advice to get started!


## Getting Started

### Windows/Linux - CLI

**Prerequisites**: gcc, cmake, ninja

```bash
git clone https://github.com/TheOnlyZac/sly1
cd sly1
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

To build unit tests, `cd` into the build directory and run `cmake --build . --target check` or `make check`. Run them with `ctest -C Debug`.

### Windows - Visual Studio

**Prerequisites**: C++ CMake tools for Windows

Clone the repo and open Visual Studio. Click `File > Open > CMake...` and open the file `CMakeLists.txt` in the main project folder. Set the startup item to `SCUS_971.98`.

For unit testing, build the target "Check" and the tests should appear in the Test Explorer window. It will run the tests, and the results will show in the Test Explorer as well as the Output window.
