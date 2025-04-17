# Contributing Guide

## So you want to decompile Sly 1...

You've come to the right place! We welcome new contributors of all skill levels. Even if you've never tried game hacking, modding, or reverse-engineering, we have a dedicated community of modders and reverse-engineers to help you get started. Feel feel to join our [Discord server](https://discord.gg/2GSXcEzPJA) and ask for help in #sly-research.

This guide will help you start contributing to the project. This is a 100% volunteer-driven project, all contributions are greatly appreciated. The current goal is to decompile and match as many game functions as possible, while imitating the style and structure of the original code to understand the inner workings of the game engine.

By following this guide, you will learn how to fork the repo on GitHub, choose a function to reverse-engineer, write code to match it, and integrate that code into the project. Once you've done that, and your pull request is merged, you will get the Decomp Contributor role in the Discord Server.

## Contents

1. [Getting Started](#getting-started)
2. [Find a function to match](#find-a-function-to-match)
3. [Match the function](#match-the-function)
4. [Integrate the matched code](#integrate-the-matched-code)
5. [Make a Pull Request](#make-a-pull-request)
6. [Conclusion](#conclusion)

## Getting started

If you haven't used Git before, follow the [Beginner's Guide](/docs/BEGINNERSGUIDE.md) to learn how to fork the repo, make changes, and submit a pull request when you're done. If you're already familiar with Git, continue on with this guide.

First, follow the instructions in the [README](/README.md) to build the project. If you see the following in the terminal, you're ready to start contributing:

```
[XXX/XXX] sha1sum config/checksum.sha1
out/SCUS_971.98: OK
```

The goal of this project is to match the original code closely enough that it compiles to a byte-matching executable. This means writing functions that compiles to the same assembly as the original functions. You will know it matches if you build the project and it says `SCUS_971.98: OK` with no errors.

## Find a function to match

First, find a function in the game that you want to match. There are a few ways to do this:
* Browse Ghidra for interesting functions.
* Look through the `src` directory to find functions in `.c` files that haven't been matched yet.
  * Functions that haven't been matched will have an `INCLUDE_ASM` macro as as placeholder.
* Look through the `asm/nonmatchings` folder.
* Ask for suggestions on Discord.

## Match the function

Once you have a function selected, you can start matching it using either **Objdiff** or **Decomp.me**. Both tools are used to match assembly code to C code, but they have different workflows.

### Decomp.me

[decomp.me](https://decomp.me/) is a website for collaborative decompilation. It allows you to upload assembly code and create a "scratch" which can be used to match the function. This is recommended if you are new to matching, as it is easier to use than Objdiff, or if you are asking others for help with matching.

To use decomp.me, follow these steps:

1. Go the website and click "Start decomping".
2. Click "PS2", then under "Preset", select "Sly Cooper and the Thievius Raccoonus".
3. Under "Diff label", enter the name of the function.
4. Find the `.s` file corresponding to the function you want to match in the `asm/nonmatchings` directory. Copy the contents of the file into the "Target assembly" box.
5. Copy any functions, global variables, or data types used by the function from the headers in the `include` directory into the "Context" box.
   * E.g. For the function `void ResetClock(struct CLOCK* pclock, float t)`, you will need to include the definition of `CLOCK` struct, and the `TICK` data type since it is used in the CLOCK struct.
   * You should almost always copy the entirety of "types.h" to ensure you have all the necessary primitive types.
6. Click "Create scratch".
7. **(Recommended)** Go to the "Options" tab and under "Debug information" select `-g3 (Macro expansions)`. This will show you which line numbers the source code correspond to each line in the assembly.

Then start writing your code under the "Source code" tab. It will tell you what percent of the code matches the original. Tweak the code until it matches 100%. An example scratch can be found here: https://decomp.me/scratch/hmmyP

### Objdiff

[Objdiff](https://github.com/encounter/objdiff), as the name implies, is a tool for showing the diff between a symbol in two object files. It can be used to match functions just like decomp.me, but it is faster and more convenient since it is included in the project and doesn't require uploading anything to a website.

To use Objdiff, follow these steps:

1. Reconfigure the project using `python3 configure.py --objects`. This will generate the object files and the `objdiff.json` config file, but it won't build the final elf or run the checksum.
2. From the project root, run `./toold/objdiff/objdiff diff FunctionName --project . -u objname`.
    * Replace `FunctionName` with the **mangled name** of the function you want to match, and `P2/objname
    * E.g. to match `OnDifficultyGameLoad` defined in `difficulty.c`, run this command:
    ```bash
    ./tools/objdiff/objdiff diff OnDifficultyGameLoad__FP10DIFFICULTY --project . -u P2/difficulty
    ```
3. Edit the source code until the function matches. The CURRENT assembly will update each time you save the file.

*Note: You can use the code in the `reference` directory to help you during matching. The code in that directory does not match, but it may be useful as an outline for certain functions.*

## Integrate the matched code

Once the function matches 100%, follow these steps to integrate it into the project. If you used objdiff, you probably already did this.
1. Replace the `INCLUDE_ASM` macro in the `.c` file with the matched function.
   * If the function is in a new file, **do not create a new file**. Creating new `.c` files is done by editing the `config/sly1.yaml` file to change the file split from `asm` to `c`, then running `python3 configure.py` to generate the new file. If you don't know how to do this, feel free to ask for help in the Discord server.
2. Check `config/symbol_addrs.txt` to see if the mangled name of the function is present.
   * If it is not, add the **mangled name** of the function with it's address. The mangled name of the function can be found in the debug symbols for the May 2002 prototype. If you don't know how to find it, ask for help in the Discord server; someone will be able to find it for you easily.
   * The symbol_addrs.txt file is grouped alphabetically by filename, then sorted by address within the file.

The project should build and match. Here are some common troubleshooting tips:
* `undefined reference error` usually means the entry in the symbol_addrs.txt is wrong. Make sure the function name is mangled in symbol_addrs.txt and unmangled in the source code, and the mangled version matches the signature of the function. Also ensure that the address is correct in symbol_addrs.txt.
* `checksum failed` means the compiled elf with your added code doesn't match the original. If it matches on decomp.me but not in the project, it might be an issue with the compiler, so open an issue on GitHub or let someone know on Discord.
* `ninja: no work to do` in objdiff likely means the name of the function is wrong in your objdiff command and/or in the symbol_addrs.txt. Make sure you are using the correct mangled name of the function in both places.

<!--### CodeMatcher

You can use [CodeMatcher](https://github.com/felinis/CodeMatcher) to help match your code against the original code. It can compile and match the entire source tree or just one file at a time. Matching against the release elf is not fully set up yet, so for now we are matching against the [May 19 2002 prototype](https://hiddenpalace.org/Sly_Cooper_and_the_Thievius_Raccoonus_(May_19,_2002_prototype)). For instructions on using CodeMatcher, see the [Code Matching Guide](/tools/codematcher/README.md).

If you are adding new code, it is strongly recommended that you run CodeMatcher before submitting a pull request. We will accept pull requests that don't match as long as the code is clean and readable, but in the future we may require that your code matches before merging it into the main branch.-->

## Make a pull request

Once you add your code to the project and it builds + matches, you can open a pull request to merge your fork into the main branch of the project. A code reviewer will need to approve it before it can be merged into the main branch.

We are a volunteer-driven project, so please be patient while we review your code. These are the main things we will look for in your code:

* It compiles without any errors.
* The compiled elf matches the original elf.

If everything looks good, we will merge your pull request as soon as possible. If anything needs to be addressd, we will let you know.

## Conclusion

Thank you for reading, and we appreciate any contributions you make to the project! The project is 100% volunteern-driven, so perfection is not required. The most important thing is to have fun and learn something new about the game.

If you have any questions or concerns, feel free to ask in the [Discord server](https://discord.gg/2Y8b8Z2) or [open an issue](https://github.com/TheOnlyZac/sly1/issues/new) on GitHub.
