## Sly Cooper and the Thievius Raccoonus

This project is a work-in-progress, experimental decompilation of Sly Cooper and the Thievius Raccoonus for the PlayStation 2. It is based on the NTSC-U version of the game (`SCUS-971.98`).

The goal of the project is to better understand how the game works, out of curiosity and to aid in glitch hunting for speedruns. It does not contain any game assets or original code from the game's executable.

### FAQ

#### What is a decompilation?
When the developers created the game, they wrote programming code that we call the *source code*. Then, they *compiled* that code into machine code which can be run on the PS2. Our job is to disasemble that code and *reverse engineer* it to re-create the original code. This process is called *decompilation*, and it leaves us with code that is very similar (but not identical) to the original source code.

#### How does it work?
We use a tool called [Ghidra](https://ghidra-sre.org/) which was created by the [NSA](https://www.nsa.gov/) for reverse-engineering software. Ghidra does a lot of the work for us by auto-decompiling the assembly code in the game's executable to human-readable C code. This auto-decompiled code is messy and has a lot of mistakes, so we use it as a base. We look at each individual function, clean it up, add variable and function names, fix mistakes, add data types, and finally re-write the code in C++.

#### Has this ever been done before?
We are not aware of any other major PS2 decompilation projects. However, this project is inspired by other projects such as the [Super Mario 64 decomp](https://github.com/n64decomp/sm64) for the N64 and the [Breath of the Wild decomp](https://github.com/zeldaret/botw) for the Wii U. The latter is more similar in scope to what we are trying to do.

#### Is this a matching decomp?
We are not currently aiming for a matching decomp due to the added complexity and difficulty. However, this is subject to change if and when it becomes possible and easy for us to do so.

#### How can I help?
If you would like to contribute but have no idea where to start, reach out to me, TheOnlyZac, on [Discord](https://discordapp.com/channels/@me/TheOnlyZac#0269/) or [Twitter](https://twitter.com/the_only_zac) and I will provide some resources for you to get started!
