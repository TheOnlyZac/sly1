# Code Matching Guide

This guide will walk you through the process of matching your code against the Sly 1 May Prototype.

## 1. Clone the repository

```sh
git clone https://github.com/TheOnlyZac/sly1.git
```

## 2. Run the setup script

The setup script will download and install the compiler needed to compile the code and run CodeMatcher.

### Linux
```sh
cd sly1/scripts
./setup-progd-linux.sh
```

### Windows
```powershell
cd sly1\scripts
.\setup-progd-windows.bat
```

## 3. Get the Sly 1 May Prototype ELF

You will need the Sly 1 May 2002 Prototype ELF for code matching. Download and and extract the ELF to the `tools/codematcher` folder (alongside `CodeMatcher.exe`). Rename it from `SCUS971.98` to `sly_proto.elf`.

## 4. Match your code

After you have written your code, you can use the scripts in the `scripts` folder to compile the code and match functions.

* `match_all.sh` will compile the complete source tree and match all functions.
* `match_file.sh <file>` will compile a single file and match all functions in that file.
* `match_function_live.sh <file> <function>` will compile a single file and match a single function in that file.
  * It will continuously dump the function bytes and print the disassembly to the console so you can compare it against the original.

These scripts will only work on Linux or WSL. If you are on Windows, you will have to run CodeMatcher manually from the command line.

**Good luck, and have fun!**
