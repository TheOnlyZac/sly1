# 🦝 Sly Cooper and the Thievius Raccoonus

<!-- Build status shield -->
[build-url]:https://github.com/TheOnlyZac/sly1/actions/workflows/build.yml
[build-badge]: https://img.shields.io/github/actions/workflow/status/theonlyzac/sly1/build.yml?branch=main&label=build

[decompdev-url]: https://decomp.dev/TheOnlyZac/sly1
[data-progress-badge]: https://decomp.dev/TheOnlyZac/sly1.svg?mode=shield&label=data&measure=matched_data_percent

[engine-url]: https://decomp.dev/TheOnlyZac/sly1/SCUS_971.98?category=P2
[engine-progress-badge]: https://decomp.dev/TheOnlyZac/sly1.svg?mode=shield&category=P2&label=engine&measure=fuzzy_match_percent

[splice-url]: https://decomp.dev/TheOnlyZac/sly1/SCUS_971.98?category=splice
[splice-progress-badge]: https://decomp.dev/TheOnlyZac/sly1.svg?mode=shield&category=splice&label=splice&measure=fuzzy_match_percent

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
[![Build][build-badge]][build-url] [![Engine Progress][engine-progress-badge]][engine-url] [![Splice Progress][splice-progress-badge]][splice-url] [![Data Progress][data-progress-badge]][decompdev-url] [![Contributors][contributors-badge]][contributors-url] [![Discord Channel][discord-badge]][discord-url] [![Docs][docs-badge]][docs-url] [![Wiki][wiki-badge]][wiki-url]

[<img src="./docs/logo.png" style="margin:7px" align="right" width="33%" alt="Sly 1 Decompilation Logo by Cooper941">][docs-url]

This is a work-in-progress decompilation of [*Sly Cooper and the Thievius Raccoonus*](https://en.wikipedia.org/wiki/Sly_Cooper_and_the_Thievius_Raccoonus) for the PlayStation 2. It builds the NTSC-U version of the game, `SCUS_971.98` (SHA1: `57dc305d`).

Our goal is to fully decompile the game engine to matching source code. This repo does **not** contain any assets or original code from the game's files; you need your own copy of the game to build and run it.

Documentation of the code is hosted at [theonlyzac.github.io/sly1](https://theonlyzac.github.io/sly1). For more info on the game's internal systems and mechanics, check out the [SlyMods Wiki][wiki-url].

New contributors are welcome to make a pull request! If you would like to help but aren't sure where to start, check out [CONTRIBUTING.md](/docs/CONTRIBUTING.md) and [join our Discord server][discord-url] if you have any questions.

[![Quickstart](https://img.shields.io/badge/⚡%20Quickstart-093fbe?style=for-the-badge)](#-quickstart)
[![Manual Setup](https://img.shields.io/badge/⚙️%20Manual%20Setup-093fbe?style=for-the-badge)](#%EF%B8%8F-manual-setup)
[![Running the Game](https://img.shields.io/badge/🎮%20Running%20the%20Game-093fbe?style=for-the-badge)](#-running-the-game)
[![Project Structure](https://img.shields.io/badge/📁%20Project%20Structure-093fbe?style=for-the-badge)](#-project-structure)
[![FAQ](https://img.shields.io/badge/❓%20FAQ-093fbe?style=for-the-badge)](#-frequently-asked-questions)
[![Contributors](https://img.shields.io/badge/🩵%20Contributors-093fbe?style=for-the-badge)](#-contributors)
[![Star History](https://img.shields.io/badge/⭐%20Star%20History-093fbe?style=for-the-badge)](#-star-history)
[![Discord](https://img.shields.io/badge/Discord-093fbe?style=for-the-badge&logo=discord)](https://discord.gg/2GSXcEzPJA)

## ⚡ Quickstart

You can quickly setup the project on Linux (or WSL) using the quickstart script. Follow these three steps get started.

### 1. Clone the repo and run quickstart.sh

Copy and run the following block of commands. It may ask for your password to install dependencies.

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

## ⚙️ Manual Setup

The project can be built on Linux (or Windows using WSL). Follow the instructions below to set up the build environment.

### 1. Clone the repository

Clone the repo to your local machine:

```bash
git clone https://github.com/TheOnlyZac/sly1
cd sly1
```

### 2. Extract your game's ELF file

To build the project, you will need to extract the original ELF file from your own legally obtained copy of the game. Mount the disc on your PC and copy the file `SCUS_971.98` from your disc to the `disc` directory of this project.

### 3. Setup Python environment

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

### 4. Setup build environment

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
./scripts/setup_progd_linux.sh
```

<!--#### Windows

*Prerequisites: [Chocolatey](https://chocolatey.org/install)*

1. Install 7zip:
```powershell
choco install 7zip
```

2. Setup build environment:
```powershell
.\scripts\setup_progd_windows.bat
```-->

### 5. Configure and build the project

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

## 🎮 Running the Game

Running the compiled executable requires [PCSX2 2.0](https://pcsx2.net/). You must have your own copy of the original game and the BIOS from your own PS2. They are not included in this repo and we cannot provide them for you.

Once you have those, and you have built the executable `SCUS_971.98`, you can run it using one of three methods:

### Method 1: Boot from PCSX2 GUI (Recommended)

1. In your PCSX2 games folder, make an alias (Linux) or symbolic link (Windows) called `SCUS_971.98.elf`, which points to the `out/SCUS_971.98` file built by this project.
    * Note: The alias/symlink must point to `out/SCUS_971.98`, not `out/SCUS_971.98.elf`.
2. The alias/symlink will be recognized as a game in PCSX2. Right click on it, then click `Properties... > Disc Path > Browse` and select the ISO of your game backup.
3. Click "Close" and boot the game as normal.

You only have make the alias/symlink once, and it will update every time you build the project.

### Method 2: Run PCSX2 from command line

To boot the elf in PCSX2 from the command line, use the following command:

```bash
pcsx2.exe -elf "C:/.../sly1/out/SCUS_971.98" "C:/.../GameBackup.iso"
```

* Replace `pcsx2.exe` with the path to your PCSX2 v2.0 executable (it will be an `.appimage` file on Linux or `.exe` file on Windows).
* The `-elf` parameter specifies the path to the `SCUS_971.98` you built from this project. Replace `...` with the path to this project on your computer. The emulator will use this ELF to boot the game.
* The last argument is the path to your game ISO. Replace `...` with the path to a backup of your own game disc. This is where the emulator will load assets from.

### Method 3: Autorun script

The `run.sh` script in the `scripts` dir will automatically rebuild the executable and run it in the PCSX2 emulator. To use it, you must first edit the script to set the `PCSX2_PATH` and `ISO_PATH` variables to the correct paths on your system.

## 📁 Project Structure

The project files are sorted into the following directories. Many of them have their own readme with more info about what they contain.

* `include` - Header files for the game engine.
* `src` - The decompiled source code.
  * All of the code for the game engine is in `src/P2`.
  * Code for the game's scripting engine is in `src/P2/splice`.
* `config` - Config files for Splat (binary splitting tool).
* `scripts` - Utility scripts for setting up the build environment.
* `docs` - Documentation and instructions for contributing.
* `tools` - Utilities for function matching.
* `reference` - Reference files for functions and data structures.

When you build the executable, the following directories will be created.

* `asm` - Disassembled assembly code from the elf.
* `assets`- Binary data extracted from the elf.
* `obj` - Compiled object files.
* `out` - Compiled executables.

## ❓ Frequently Asked Questions

### What is a decompilation?

When the developers created the game, they wrote source code and compiled it to assembly code that can run on the PS2. A decompilation involves reverse-engineering the assembly code to produce new, original code that compiles to the same assembly. This process leaves us with source code that is similar to and behaves the same as the source code (though not necessarily identical), which helps us understand what the programmers were thinking when they made the game.

### How do you decompile the code?

We use a tool called [Splat](https://github.com/ethteck/splat/) to split the binary into assembly files representing each individual function. We then reimplement every function and data structure by writing C++ code that compiles to the same assembly code. We do not copy any code from the original game binary into the decompilation.

### Has this ever been done before?

There are many other decompilation projects, but this was one of the first ones for the PS2. Our inspirations include as the [Super Mario 64 decomp](https://github.com/n64decomp/sm64) for the N64 and the [Breath of the Wild decomp](https://github.com/zeldaret/botw) for the Wii U (the latter being more similar in scope to this project). There is also a Jak & Daxter decomp/PC port called [OpenGOAL](https://github.com/open-goal/jak-project), though that game is 98% GOAL language rather than C/C++.

### Is this a matching decomp?

Yes. This was the first PS2 decompilation project that targeted the PS2 and utilized function matching, before it was even possible to produce a byte-matching executable. We have built a matching elf since July 2024. Our ultimate goal is to match 100% of the game's functions.

### What is Splice?

Splice is the game's scripting engine; it handles things like scripted events, animated cutscenes, and guard spawning by executing scripts stored in the level files. The code for Splice is a distinct subset of the game engine code, which is why it has its own folder and progress percentage.

### How can I help?

If you want to contribute, check out [CONTRIBUTING.md](/docs/CONTRIBUTING.md) and feel free to [join our discord server](https://discord.gg/gh5xwfj)!

## 🩵 Contributors

Thank you to everyone who has volunteered their time to make this project possible!

<a href="https://github.com/theonlyzac/sly1/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=theonlyzac/sly1" />
</a>

<small>Made with [contrib.rocks](https://contrib.rocks).</small>

## ⭐ Star History

<a href="https://star-history.com/#theonlyzac/sly1&Date">
  <picture>
    <source media="(prefers-color-scheme: dark)" srcset="https://api.star-history.com/svg?repos=theonlyzac/sly1&type=Date&theme=dark" />
    <source media="(prefers-color-scheme: light)" srcset="https://api.star-history.com/svg?repos=theonlyzac/sly1&type=Date" />
    <img alt="Star History Chart" src="https://api.star-history.com/svg?repos=theonlyzac/sly1&type=Date" />
  </picture>
</a>
