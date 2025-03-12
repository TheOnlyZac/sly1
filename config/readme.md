# Splat Config Files

This directory contains config files for splat, the tool we use to split and disassemble the game binary. The config files are used to tell splat how to split the binary and what to name the output files.

## Files in this directory
- `sly1.yaml` - Main config file for splat. Contains the offsets of each file split in the game binary. Creating new `.c` files involves modifying this file to create a `c` split and then running `python3 configure.py` to generate the new files.
- `symbol_addrs.txt` - Contains the addresses of symbols in the game binary. Used by splat to properly reference functions and variables in the game code when splitting the binary.
- `checksum.sha1` - SHA1 checksum of the original game binary. Used to verify the integrity of the binary after compilation.

## Adding new splits
To add a new source code file to the project, you must add the split to `sly1.yaml`. Here is an example of some file splits:
```yaml
    - [0x1f560, c, P2/brx]
    - [0x1fe70, asm, P2/ac]
    #- [0x, asm, P2/act]
```
- The first line tells Splat to split the binary at offset `0x1f560` and create a new file `P2/brx.c` (if it doesn't exist). It defines a translation unit starting at `0x1f560` and ending at the beginning of the next split. The `.c` file will have INCLUDE_ASM macros for each function in the split.
- The second line tells Splat that the data starting from offset `0x1fe70` is in the translation unit `P2/ac`, but not to create a new `.c` file yet. It will only create `.s` files in the `asm/nonmatchings/` directory for each function in the split.
- The third line is commented out and does nothing, because we know the next translation unit is `P2/act`, but we don't yet know what offset that translation unit starts at. When we find out (by finding the end of the last function in `P2/ac` and the start of the first function in `P2/act`), we can uncomment this line and add the offset.

When splat is run, it will create `.s` assembly files for each non-matching functions in each split in the `asm/nonmatchings/` directory.
