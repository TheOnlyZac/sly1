#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
from pathlib import Path

from .. import mapfile
from .. import utils


def doSymInfo(mapPath: Path, symName: str, *, as_vram: bool=False, as_vrom: bool=False, as_name: bool=False) -> int:
    if not mapPath.exists():
        print(f"Could not find mapfile at '{mapPath}'")
        return 1

    mapFile = mapfile.MapFile()
    mapFile.readMapFile(mapPath)

    possibleFiles: list[mapfile.File] = []

    if as_vram:
        address = int(symName, 0)
        info, possibleFiles = mapFile.findSymbolByVram(address)
    elif as_vrom:
        address = int(symName, 0)
        info, possibleFiles = mapFile.findSymbolByVrom(address)
    elif as_name:
        info = mapFile.findSymbolByName(symName)

    # Start the guessing game
    elif utils.convertibleToInt(symName, 0):
        address = int(symName, 0)
        info, possibleFiles = mapFile.findSymbolByVram(address)
        if info is None:
            info, possibleFiles2 = mapFile.findSymbolByVrom(address)
            possibleFiles.extend(possibleFiles2)
    else:
        info = mapFile.findSymbolByName(symName)

    if info is not None:
        print(info.getAsStrPlusOffset(symName))
        return 0
    print(f"'{symName}' not found in map file '{mapPath}'")
    if len(possibleFiles) > 0:
        print("But it may be a local symbol of either of the following files:")
        for f in possibleFiles:
            print(f"    {f.asStr()})")
    return 1


def processArguments(args: argparse.Namespace):
    mapPath: Path = args.mapfile
    symName: str = args.symname
    as_vram: bool = args.vram
    as_vrom: bool = args.vrom
    as_name: bool = args.name

    exit(doSymInfo(mapPath, symName, as_vram=as_vram, as_vrom=as_vrom, as_name=as_name))

def addSubparser(subparser: argparse._SubParsersAction[argparse.ArgumentParser]):
    parser = subparser.add_parser("sym_info", help="Display various information about a symbol or address.")

    parser.add_argument("mapfile", help="Path to a map file.", type=Path)
    parser.add_argument("symname", help="Symbol name or VROM/VRAM address to lookup. How to treat this argument will be guessed.")

    vram_vrom_group = parser.add_mutually_exclusive_group()
    vram_vrom_group.add_argument("--vram", help="Treat the argument as a VRAM address instead of guessing.", action="store_true")
    vram_vrom_group.add_argument("--vrom", help="Treat the argument as a VROM address instead of guessing.", action="store_true")
    vram_vrom_group.add_argument("--name", help="Treat the argument as a symbol name instead of guessing.", action="store_true")

    parser.set_defaults(func=processArguments)
