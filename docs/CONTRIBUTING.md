# Contributing

Welcome to the **Sly Cooper Decompilation Project**! This guide will help you start contributing to the project. We are a volunteer-driven project, so we appreciate any contributions you make.**If you need help with anything, you are welcome to ask in the #sly-research channel of the [Discord server](https://discord.gg/2GSXcEzPJA)!**

# Contents

1. [Getting Started](#getting-started)
2. [Find a function to match](#find-a-function-to-match)
3. [Match the function using Decomp.me](#match-the-function-using-decompme)
4. [Integrate the matched code](#integrate-the-matched-code)
5. [Conclusion](#conclusion)


## Getting Started

If you haven't used Git before, follow the steps in the [Beginner's Guide](/docs/BEGINNERSGUIDE.md) to learn how to fork the repo, make changes, and submit a pull request. If you are already familiar with Git, continue on with this guide.

Start by following the instructions to build and run the project in the [README](/README.md). If you see the following in the console, you're ready to start contributing:

```
[XXX/XXX] sha1sum checksum.sha1
out/SCUS_971.98: OK
```

The goal of this project is to match the original code closely enough that it compiles to a byte-matching executable. This means writing functions that compiles to the same assembly as the original functions. You will know it matches if you build the project and it says `SCUS_971.98: OK`.

## Find a function to match

First, find a function in the game that you want to match. There are a few ways to do this:
* Browse Ghidra for interesting functions.
* Look through the `src` directory to find functions in `.c` files that haven't been matched yet (they will have an `INCLUDE_ASM` macro as as placeholder).
* Look through the `asm/nonmatchings` folder.
* Ask for suggestions in the Discord server.

## Match the function using Decomp.me

Once you have chosen a function, you can use the website [decomp.me](https://decomp.me/) to match it.
* Go the website and click "Start decomping".
* Select "PlayStation 2"
* Under "Select a compiler", select "EE GCC 2.95.2 (SN BUILD v2.73a)".
* Under "Diff label", enter the name of the function.
* Find the `.s` file corresponding to the function you want to match in the `asm/nonmatchings` folder. Copy the contents of the file into the "Target assembly" box.
* Find the `.h` header file in the `include` folder where the function is/would be declared. Copy it into the "Context" box, as well as any other relevant function/data definitions in other headers.
* Click "Create scratch".
* Click the "Options" tab, then copy and paste this into the "Compiler options" text box:
  * `-x c++ -O2 -G0`.

Then start writing your code under the "Source code" tab. It will tell you what percent of the code matches the original. Tweak the code until it matches 100%.

**Note: The `reference` directory contains source code files that do not match, but are based on the original code. You can use them as a reference to help you match the code.**

## Integrate the matched code

Once the function matches 100%, follow these steps to integrate it into the project:
1. Replace the `INCLUDE_ASM` macro in the `.c` file with the matched function.
   * If the function is in a new file, **do not create a new file**. Creating new `.c` files is done by editing the `config/sly1.yaml` file to change the file split from `asm` to `c`, then running `python configure.py` to generate the new file. If you don't know how to do this, feel free to ask for help in the Discord server.
2. Edit `config/symbol_addrs.txt` to add the **mangled name of the function** with its address.
   * The symbol_addrs.txt file is sorted alphabetically by filename, then by address within the file.
   * The mangled name of the function can be found by searching the strings in the May 19 prototype elf. If you don't know how to do this, ask for help in the Discord server. Someone will be able to find it for you easily.

The project should build and match. Here are some tips for troubleshooting common issues:
* Undefined reference errors usually means the entry in the symbol_addrs.txt is wrong. Ensure you are using the correct mangled function name in the symbol_addrs.txt, and the normal un-mangled name in the source code.
* Checksum failed means the compiled elf doesn't match the original. If it matches on decomp.me, it might be an issue with the compiler, so open an issue on GitHub or let someone know on Discord.

<!--### CodeMatcher

You can use [CodeMatcher](https://github.com/felinis/CodeMatcher) to help match your code against the original code. It can compile and match the entire source tree or just one file at a time. Matching against the release elf is not fully set up yet, so for now we are matching against the [May 19 2002 prototype](https://hiddenpalace.org/Sly_Cooper_and_the_Thievius_Raccoonus_(May_19,_2002_prototype)). For instructions on using CodeMatcher, see the [Code Matching Guide](/tools/codematcher/README.md).

If you are adding new code, it is strongly recommended that you run CodeMatcher before submitting a pull request. We will accept pull requests that don't match as long as the code is clean and readable, but in the future we may require that your code matches before merging it into the main branch.-->


## Code Review Process

Once you add your code to the project and it builds + matches, you can open a pull request to merge your fork into the main branch of the project. A code reviewer will need to approve it before it can be merged into the main branch.

We are a volunteer-driven project, so please be patient while we review your code. These are the main things we will look for in your code:

* It compiles without any errors.
* The compiled elf matches the original elf.
* It follows the [style guide](/docs/STYLEGUIDE.md), or is at least clean and understandable.

If everything looks good, we will merge your pull request as soon as possible. If anything needs to be fixed, we will let you know.


## Conclusion

Thank you for reading, and we appreciate any contributions you make to the project!

When in doubt, just try and follow the style of the existing code, and do your best to write clean and readable code. The project is 100% volunteern-driven, so perfection is not required. The most important thing is to have fun and learn something new about the game!

If you have any questions or concerns, feel free to ask in the [Discord server](https://discord.gg/2Y8b8Z2) or [open an issue](https://github.com/TheOnlyZac/sly1/issues/new) on GitHub.
