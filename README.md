# Sly Cooper and the Thievius Raccoonus

<!-- Build status shield -->
[build-url]:https://github.com/TheOnlyZac/sly1/actions/workflows/build.yml
[build-badge]: https://img.shields.io/github/actions/workflow/status/theonlyzac/sly1/build.yml?branch=main&label=build

[code-progress-badge]: https://img.shields.io/endpoint?label=progress&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fslycooper1%2Fus%2Fall%2F%3Fmode%3Dshield%26measure%3DP2

<!--[data-progress-badge]: https://img.shields.io/endpoint?label=data&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fslycooper1%2Fus%2Fall%2F%3Fmode%3Dshield%26measure%3Ddata-->

<!-- Contributors shield -->
[contributors-url]: https://github.com/theonlyzac/sly1/graphs/contributors
[contributors-badge]: https://img.shields.io/github/contributors/theonlyzac/sly1?color=%23db6d28

<!-- Discord shield -->
[discord-url]: https://discord.gg/2GSXcEzPJA
[discord-badge]: https://img.shields.io/discord/439454661100175380?color=%235865F2&logo=discord&logoColor=%23FFFFFF

<!-- Docs shield -->
[docs-url]: https://theonlyzac.github.io/sly1
[docs-badge]: https://img.shields.io/badge/docs-github.io-2C4AA8

<!-- Wiki shield -->
[wiki-url]: https://slymods.info
[wiki-badge]: https://img.shields.io/badge/wiki-slymods.info-2C4AA8

<!-- Shields -->
[![Build][build-badge]][build-url] ![code-progress-badge] <!--![data-progress-badge]--> [![Contributors][contributors-badge]][contributors-url] [![Discord Channel][discord-badge]][discord-url] [![Docs][docs-badge]][docs-url] [![Wiki][wiki-badge]][wiki-url]

[<img src="./logo.png" style="margin:7px" align="right" width="33%" alt="Sly 1 Decompilation Logo by Cooper941">][docs-url]

This is a work-in-progress decompilation of [*Sly Cooper and the Thievius Raccoonus*](https://en.wikipedia.org/wiki/Sly_Cooper_and_the_Thievius_Raccoonus) for the PlayStation 2. It builds the NTSC-U version of the game, `SCUS_971.98` (SHA1: `57dc305d`).

The goal of this project is to better understand the game engine. This repo does not contain any game assets or original code from the game's executable; It requires your own copy of the game to build and run.

Documentation of the code can be found at [theonlyzac.github.io/sly1](https://theonlyzac.github.io/sly1). For further reading on the game's internal structures and mechanics, visit the [SlyMods Wiki][wiki-url].

New contributors are welcome and encouraged to make a pull request! If you would like to help but aren't sure where to start, check out [CONTRIBUTING.md](/docs/CONTRIBUTING.md) and feel free to [join our Discord server][discord-url] for guidance.

## Quickstart

You can quickly setup the project on Linux (or WSL) using the quickstart script. Follow these three steps get started.

### 1. Clone the repo and run quickstart.sh

Copy and run the following command. It may ask for your password to install dependencies.

```bash
git clone https://github.com/theonlyzac/sly1 && \
cd sly1 && \
./scripts/quickstart.sh
```

### 2. Extract the executable from your disc

Copy the file `SCUS_971.98` from your Sly 1 game disc to the `disc` directory of the project. It is needed to build.

### 3. Build the project

```bash
./scripts/build.sh
```

If it works, you will see this:

```
[XXX/XXX] sha1sum config/checksum.sha1
out/SCUS_971.98: OK
```

If you have any issues, or you prefer to set up the project manually, follow the instructions below. Instructions to run the game are also provided below.

## Manual Setup

The project can be built on Linux (or Windows using WSL). Follow the instructions below to set up the build environment.

### Clone the repository

Clone the repo to your local machine:

```bash
git clone https://github.com/TheOnlyZac/sly1
cd sly1
```

### Extract your original ELF file

To build the project, you will need to extract the original ELF file from your own legally obtained copy of the game. Mount the disc on your PC and copy the file `SCUS_971.98` from your disc to the `disc` directory of this project.

### Setup Python environment

If you don't have Python 3.9 or higher, install it:

```bash
sudo apt-get install python3 python3-pip
```

Create a Python environment for the project:

```bash
python3 -m venv env
```

Activate the environment:

```bash
source env/bin/activate
```

Then install the required Python packages:

```bash
pip3 install -U -r requirements.txt
```

### Setup build environment

Setup wine:

```bash
sudo dpkg --add-architecture i386
sudo apt-get update
sudo apt-get install wine32
```

Install the MIPS assembler:

```bash
sudo apt-get install binutils-mips-linux-gnu
```

Setup the compiler using the provided script:

```bash
./scripts/setup-progd-linux.sh
```

<!--#### Windows

*Prerequisites: [Chocolatey](https://chocolatey.org/install)*

1. Install 7zip:
```powershell
choco install 7zip
```

2. Setup build environment:
```powershell
.\scripts\setup-progd-windows.bat
```-->

### Configure and build the project

Run the configure script and the build with ninja:

```bash
python3 configure.py
ninja
```

The default behavior is to split the binary using Splat, build the object files (inserting the split assembly in place of non-matching functions), link the matching executable, and confirm that the checksum of the built executable matches the original.

You can alter the behavior by passing any of the following arguments to  `configure.py`:

* `--clean` - Delete any existing build files and configure the project.
* `--clean-only` - Delete any existing build files **without** configuring the project.
* `--skip-checksum` - Skip the checksum verification step. This is necessary if you are intentionally changing the code, but note that the elf may not boot.
* `--objects` - Builds the object files for matching with objdiff and generates an objdiff config file. Outputs two sets of object files: `obj/target` and `obj/current` (the latter of which will be updated automatically by objdiff as you edit the source code).

## Running

Running the executable requires [PCSX2 2.0](https://pcsx2.net/). You must have your own copy of the original game and the BIOS from your own PS2. They are not included in this repo and we cannot provide them for you.

Once you have those and you have built the executable, you can run it using one of three methods:

### Method 1: Boot from PCSX2 GUI (Recommended)

In your PCSX2 game dir, make an alias (Linux) or symbolic link (Windows) called `SCUS_971.98.elf` which points to the `SCUS_971.98` file built by this project. The alias/link will be recognized as a game in PCSX2. Right click on the elf in PCSX2 and click "Properties..." > "Disc Path" > "Browse" > Select the ISO of your game backup. Then click "Close" and start the game as normal.

### Method 2: Run PCSX2 from command line

To boot the elf in PCSX2 from the command line, use the following command:

```bash
pcsx2.exe -elf ".../sly1/out/SCUS_971.98" "/path/to/game/backup.iso"
```

Replace `pcsx2.exe` with the path to your PCSX2 v2.0 executable (it will be an `.appimage` file on Linux or `.exe` file on Windows).

* The `-elf` parameter specifies the path to the `SCUS_971.98` you built from this project. Replace `...` with the path to this repository. The emulator will use this ELF to boot the game.
* The last argument is the path to your game ISO. Replace `/path/to/game/backup.iso` with the path to a backup of your own game disc. This is where the game will load the assets from.

### Method 3: Autorun script

The `run.sh` script in the `scripts` dir will automatically rebuild the executable and run it in the PCSX2 emulator. To use it, you must first edit the script to set the `PCSX2_PATH` and `ISO_PATH` variables to the correct paths on your system.

## Project Structure

The project is divided into the following directories:

* `include` - Header files for the game engine.
* `src` - The decompiled source code.
  * All of the code for the game engine is in `src/P2`.
  * Code for the game's scripting engine is in `src/P2/splice`.
* `config` - Config files for Splat (binary splitting tool).
* `scripts` - Utility scripts for setting up the build environment.
* `docs` - Documentation and instructions for contributing.
* `tools` - Utilities for function matching.
* `reference` - Reference files for functions and data structures.

When you build the executable, the following directories will be created:

* `asm` - Disassembled assembly code from the elf.
* `assets`- Binary data extracted from the elf.
* `obj` - Compiled object files.
* `out` - Compiled executables.

## FAQ

### What is a decompilation?

When the developers created the game, they wrote source code and compiled it to assembly code that can run on the PS2. A decompilation involves reverse-engineering the assembly code to produce new, original code that compiles to matching assembly. This process leaves us with source code that is similar to and behaves the same as the source code (though not necessarily identical), which helps us understand what the programmers were thinking when they made the game.

### How does it work?

We use a tool called [Splat](https://github.com/ethteck/splat/) to split the binary into assembly files representing each individual function. We then reimplement every function and data structure by writing C++ code that compiles to the same assembly code. We do not include any data or code from the original game binary in the decompilation.

### Has this ever been done before?

This was one the first PS2 decompilations; Several others have been started since we began in 2020. Our main inspiration was other projects such as the [Super Mario 64 decomp](https://github.com/n64decomp/sm64) for the N64 and the [Breath of the Wild decomp](https://github.com/zeldaret/botw) for the Wii U (the latter being more similar in scope to this project). There is also a Jak & Daxter decomp/PC port called [OpenGOAL](https://github.com/open-goal/jak-project), though that game is 98% GOAL language rather than C/C++.

### Is this a matching decomp?

Yes. This was the first PS2 decompilation project that targeted the PS2 and utilized function matching, before it was even possible to produce a byte-matching executable. We have built a matching elf since July 2024. The ultimate goal is to match 100% of the game's functions.

### How can I help?

If you want to contribute, check out [CONTRIBUTING.md](/docs/CONTRIBUTING.md) and feel free to [join our discord server](https://discord.gg/gh5xwfj) if you have any questions!

## Star History

<a href="https://star-history.com/#theonlyzac/sly1&Date">
  <picture>
    <source media="(prefers-color-scheme: dark)" srcset="https://api.star-history.com/svg?repos=theonlyzac/sly1&type=Date&theme=dark" />
    <source media="(prefers-color-scheme: light)" srcset="https://api.star-history.com/svg?repos=theonlyzac/sly1&type=Date" />
    <img alt="Star History Chart" src="https://api.star-history.com/svg?repos=theonlyzac/sly1&type=Date" />
  </picture>
</a>
