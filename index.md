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

New contributors are welcome and encouraged to make a pull request! If you would like to help but aren't sure where to start, you can [join our discord server](https://discord.gg/gh5xwfj) and/or message [TheOnlyZac#0269](https://discordapp.com/channels/@me/TheOnlyZac#0269/) for more info and advice on where to begin.

## Frequently Asked Questions

#### What is a decompilation?
When the developers created the game, they wrote programming code that we call the source code. Then, they compiled the code into machine code that can run on the PS2. Our job is to disasemble that code and reverse engineer it to re-create the original code. This process is called decompilation, and it leaves us with code that is very similar (but not identical) to the source code.

#### How does it work?
We use a tool called [Ghidra](https://ghidra-sre.org/) which was created by the [NSA](https://www.nsa.gov/) for reverse-engineering software. Ghidra does a lot of the work for us by auto-decompiling the assembly code in the game's executable to human-readable C code. This auto-decompiled code is messy and has a lot of mistakes, so we use it as a base. We look at each individual function, clean it up, add variable names, fix data types, and finally re-write the code in C++.

#### Has this ever been done before?
This is one of the first ever large-scale PS2 decompilation projects. Our inspiration comes from other decomp projects such as the [Super Mario 64 decomp](https://github.com/n64decomp/sm64) for the N64 and the [Breath of the Wild decomp](https://github.com/zeldaret/botw) for the Wii U (the latter is more similar in scope to what we are trying to do).

#### Is this a matching decomp?
We are not currently aiming for a matching decomp due to the added complexity and lack of resources/info on PS2 reverse-engineering. However, this is subject to change once we learn more about the PS2 compiler and come up with a process for function matching.

#### How can I help?
If you would like to contribute but have no idea where to start, you can [join our discord server](https://discord.gg/gh5xwfj) and/or reach out to [TheOnlyZac#0269](https://discordapp.com/channels/@me/TheOnlyZac#0269/) for some resources and advice to get started!
