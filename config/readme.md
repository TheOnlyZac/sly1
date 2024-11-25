# Splat Config Files

This directory contains config files for splat, the tool we use to split and disassemble the game binary. The config files are used to tell splat how to split the binary and what to name the output files.

## Files in this directory
- `sly1.yaml` - Main config file for splat. Contains the offsets of each file split in the game binary. Creating new `.c` files involves modifying this file to create a `c` split and then running `python configure.py` to generate the new files.
- `symbol_addrs.txt` - Contains the addresses of symbols in the game binary. Used by splat to properly reference functions and variables in the game code when splitting the binary.
- `checksum.sha1` - SHA1 checksum of the original game binary. Used to verify the integrity of the binary after compilation.

## Adding new splits
To add a new source code file to the project, you must add the split to `sly1.yaml`. Here is an example of some file splits:
```yaml
    - [0x1f560, c, P2/brx]
    - [0x1fe70, asm, P2/ac]
    #- [0x, asm, P2/act]
```
- The first line tells splat to split the binary at offset `0x1f560` and create a new file `P2/brx.c`. It will contain the data from the translation unit starting at `0x1f560` and ending at the next split offset. The `c` tells splat to create a `.c` file in `src/P2/`.
- The second line tells splat to split that the functions starting from offset `0x1fe70` are in the translation unit `P2/ac`, but not to create a new `.c` file.
- The third line is commented out and does nothing, because we know the next translation unit is `P2/act`, but we don't yet know the offset of the first function in that TU.

When splat is run, it will create `.s` assembly files for each non-matching functions in each split in the `asm/nonmatchings/` directory.
