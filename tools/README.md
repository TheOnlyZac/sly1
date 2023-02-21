# Code Matching Guide

This guide will walk you through the process of matching your code against the Sly 1 May Prototype. It works only on Windows for now.

## 1. Clone the Sly 1 repository

`git clone https://github.com/TheOnlyZac/sly1.git`

## 2. Download and extract the PS2 compiler collection (25 mb)

[https://archive.org/download/SNSystemsProDGPs2/ProDGPs2usrLocalSceFiles.zip](https://archive.org/download/SNSystemsProDGPs2/ProDGPs2usrLocalSceFiles.zip)

Extract it to your `C:\` drive.
* Once extracted, the path structure should look like: `C:\usr\local\sce\...`

If you are wondering why this step is needed, it will be useful for compiling our code (from the repo). CodeMatcher will be able to match it against Sly 1's original code.

## 3. Get the Sly 1 May Prototype ELF

You will need the Sly 1 May 2002 Prototype ELF for code matching. Find it online and extract the ELF to the `tools` folder (alongside `match_all.cmd`). Rename it from `SCUS971.98` to `sly_proto.elf`.

## 4. Match your code

After you have written your code, run `match_all.cmd` from the tools folder in the repo to compile the source tree and perform a function match. Alternatively, run `match_single.cmd` to compile and match a single file.

A summary of the process will be displayed, including functions that do match and which do not.

**Good luck, and have fun!**