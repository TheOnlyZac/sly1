# Reference files

This directory contains source code that doesn't build, and pertains to source code files which are either partially matched, or not yet started. If you want to get started with decompiling those files you can use them as a starting point. They are all source code files we wrote by hand before we started using Splat to compile a matching executable.

It is organized as follows:

* `include/` contains header files for the game engine. Most function signatures are probably correct. Many of the very short structs/enums are correct, but the longer ones are probably not correct (missing fields, wrong field types, etc), though they can be used as a starting point.
* `src/P2/` contains source code files for the game engine. None of the code is matching, though we tried to make them resemble the original code as closely as possible, so they may help you understand the logic and control flow of certain functions.
