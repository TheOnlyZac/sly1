# Contributing

Welcome to the **Sly Cooper Decompilation Project**! This guide will help you start contributing to the project. We are a volunteer-driven project, so we appreciate any contributions you make.

# Contents

1. [Getting Started](#getting-started)
2. [Function Matching](#function-matching)
3. [Code Review Process](#code-review-process)
4. [Conclusion](#conclusion)


## Getting Started

If you have never used Git before, follow the steps in the [Beginner's Guide](/docs/BEGINNERSGUIDE.md) to learn how to fork the repo, make changes, and submit a pull request. If you are already familiar with Git, go ahead and read the rest of this guide instead.

For instructions on how to build and run the project, see the [README](/README.md).


## Function Matching

The goal of this project is to match the original code closely enough that it compiles to a byte-matching executable. This means writing functions that compiles to the same assembly as the original functions. When you build the project, you will know it matches if it says `SCUS_971.98: OK`.

### Decomp.me

You can use the website [decomp.me](https://decomp.me/) to assist with function matching.
* First choose a function to decompile, then go the website and click "Start decomping".
* Select "PlayStation 2", and for the compiler, select `EE GCC build 991111-01`.
  * **Note**: The actual compiler version is `EE GCC build 2.9-ee-991111b/r4`, but that is not available on decomp.me as of this writing; Keep in mind that your code may not match perfectly on the website, even though it would match in this project.
* For "Diff label", enter the name of the function.
* Paste in the asm of the function into the "Target assembly" box.
* Click "Create scratch"

Then start writing your code in the "Source code" box. It will tell you what percent of the code matches the original. When you get close to 100%, you can copy the code and paste it into the project and build it to see if it matches, then tweak it until it does.


### CodeMatcher

You can use [CodeMatcher](https://github.com/felinis/CodeMatcher) to help match your code against the original code. It can compile and match the entire source tree or just one file at a time. Matching against the release elf is not fully set up yet, so for now we are matching against the [May 19 2002 prototype](https://hiddenpalace.org/Sly_Cooper_and_the_Thievius_Raccoonus_(May_19,_2002_prototype)). For instructions on using CodeMatcher, see the [Code Matching Guide](/tools/codematcher/README.md).

If you are adding new code, it is strongly recommended that you run CodeMatcher before submitting a pull request. We will accept pull requests that don't match as long as the code is clean and readable, but in the future we may require that your code matches before merging it into the main branch.


## Code Review Process

Once you create a pull request, a code reviewer will need to approve it before it can be merged into the main branch. We are a volunteer-driven project, so please be patient while we review your code. These are the main things we will look for in your code:

* It compiles and runs without any errors.
* The compiled elf matches the original elf.
* It follows the [style guide](/docs/STYLEGUIDE.md), or is at least clean and readable.

If everything looks good, we will merge your pull request as soon as possible. If anything needs to be fixed, we will let you know.


## Conclusion

Thank you for reading, and we appreciate any contributions you make to the project!

When in doubt, just try and follow the style of the existing code, and do your best to write clean and readable code. The project is 100% volunteern-driven, so perfection is not required. The most important thing is to have fun and learn something new about the game!

If you have any questions or concerns, feel free to ask in the [Discord server](https://discord.gg/2Y8b8Z2) or [open an issue](https://github.com/TheOnlyZac/sly1/issues/new) on GitHub.
