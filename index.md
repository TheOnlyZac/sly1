## Sly Cooper and the Thievius Raccoonus
<!-- Readme badges -->

[![Build status][build-badge]][build-url] [![AppVeyor tests][tests-badge]][tests-url] [![Contributors][contributors-badge]][contributors-url] [![Discord Channel][discord-badge]][discord-url]

<!-- Build status links -->
[build-url]: https://ci.appveyor.com/project/TheOnlyZac/sly1
[build-badge]: https://ci.appveyor.com/api/projects/status/800esepa77ctpv5p/branch/main?svg=true

<!-- Test status links -->
[tests-url]: https://ci.appveyor.com/project/TheOnlyZac/sly1/build/tests
[tests-badge]: https://img.shields.io/appveyor/tests/theonlyzac/sly1/main

<!-- Contributors badge links -->
[contributors-url]: https://github.com/theonlyzac/sly1/graphs/contributors
[contributors-badge]: https://img.shields.io/github/contributors/theonlyzac/sly1?color=%23006ED1

<!-- Discord badge links -->
[discord-url]: https://discord.gg/gh5xwfj
[discord-badge]: https://img.shields.io/discord/439454661100175380?color=%23006ED1&logo=discord&logoColor=%23FFFFFF

This is a work-in-progress, experimental decompilation of *Sly Cooper and the Thievius Raccoonus* for the PlayStation 2. It is based on the NTSC-U version of the game (`SCUS-971.98`).

The goal of this project is to better understand how the game works. **This repo does not contain any game assets or original code from the game's executable.**

New contributors are welcome and encouraged to make a pull request! If you would like to help but aren't sure where to start, you can [join our discord server][discord-url] and checkout [CONTRIBUTING.md](https://github.com/TheOnlyZac/sly1/blob/main/CONTRIBUTING.MD) for info on how to get started.

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
If you would like to contribute but have no idea where to start, you can [join our discord server](https://discord.gg/gh5xwfj) and/or check out [CONTRIBUTING.md](https://github.com/TheOnlyZac/sly1/blob/main/CONTRIBUTING.MD) for some resources and advice to get started!
