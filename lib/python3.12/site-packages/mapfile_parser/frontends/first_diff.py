#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
from pathlib import Path
from typing import Callable, Literal

from .. import mapfile
from .. import utils


def doFirstDiff(mapPath: Path, expectedMapPath: Path, romPath: Path, expectedRomPath: Path, diffCount: int=5, mismatchSize: bool=False, addColons: bool=True, bytesConverterCallback:Callable[[bytes, mapfile.MapFile],str|None]|None=None, endian: Literal["big", "little"] ="big") -> int:
    if not mapPath.exists():
        print(f"{mapPath} must exist")
        return 1
    if not expectedMapPath.exists():
        print(f"{expectedMapPath} must exist")
        return 1
    if not romPath.exists():
        print(f"{romPath} must exist")
        return 1
    if not expectedRomPath.exists():
        print(f"{expectedRomPath} must exist")
        return 1

    builtRom = utils.readFileAsBytearray(romPath)
    expectedRom = utils.readFileAsBytearray(expectedRomPath)

    if len(builtRom) != len(expectedRom):
        print("Modified ROM has different size...")
        print(f"It should be 0x{len(expectedRom):X} but it is 0x{len(builtRom):X}")
        if not mismatchSize:
            return 1

    if builtRom == expectedRom:
        print("No differences!")
        return 0

    builtMapFile = mapfile.MapFile()
    builtMapFile.readMapFile(mapPath)
    expectedMapFile = mapfile.MapFile()
    expectedMapFile.readMapFile(expectedMapPath)

    endian_diff = 0
    if endian == "little":
        endian_diff = 3

    map_search_diff: set[str] = set()
    diffs = 0
    shift_cap = 1000
    for i in range(24, min(len(builtRom), len(expectedRom)), 4):
        # (builtRom[i:i+4] != expectedRom[i:i+4], but that's slightly slower in CPython...)
        if diffs <= shift_cap and (
            builtRom[i] != expectedRom[i]
            or builtRom[i + 1] != expectedRom[i + 1]
            or builtRom[i + 2] != expectedRom[i + 2]
            or builtRom[i + 3] != expectedRom[i + 3]
        ):
            if diffs == 0:
                vromInfo, possibleFiles = builtMapFile.findSymbolByVrom(i)
                extraMessage = ""
                if vromInfo is not None:
                    extraMessage = f", {vromInfo.getAsStrPlusOffset()}"
                elif len(possibleFiles) > 0:
                    extraMessage = f", in file {possibleFiles[0].asStr()}"
                print(f"First difference at ROM addr 0x{i:X}{extraMessage}")
                builtBytes = builtRom[i : i + 4]
                expectedBytes = expectedRom[i : i + 4]
                print(f"Bytes: {utils.hexbytes(builtBytes, addColons=addColons)} vs {utils.hexbytes(expectedBytes, addColons=addColons)}")
                if bytesConverterCallback is not None:
                    builtConverted = bytesConverterCallback(builtBytes, builtMapFile)
                    expectedConverted = bytesConverterCallback(expectedBytes, expectedMapFile)
                    if builtConverted is not None and expectedConverted is not None:
                        print(f"{builtConverted} vs {expectedConverted}")
            diffs += 1

        if (
            len(map_search_diff) < diffCount
            and builtRom[i+endian_diff] >> 2 != expectedRom[i+endian_diff] >> 2
        ):
            vromInfo, possibleFiles = builtMapFile.findSymbolByVrom(i)
            if vromInfo is not None:
                vromMessage = vromInfo.getAsStr()
                if vromMessage not in map_search_diff:
                    map_search_diff.add(vromMessage)

                    extraMessage = f", {vromInfo.getAsStrPlusOffset()}"
                    print(f"Instruction difference at ROM addr 0x{i:X}{extraMessage}")
                    builtBytes = builtRom[i : i + 4]
                    expectedBytes = expectedRom[i : i + 4]
                    print(f"Bytes: {utils.hexbytes(builtBytes, addColons=addColons)} vs {utils.hexbytes(expectedBytes, addColons=addColons)}")
                    if bytesConverterCallback is not None:
                        builtConverted = bytesConverterCallback(builtBytes, builtMapFile)
                        expectedConverted = bytesConverterCallback(expectedBytes, expectedMapFile)
                        if builtConverted is not None and expectedConverted is not None:
                            print(f"{builtConverted} vs {expectedConverted}")
            elif len(possibleFiles) > 0:
                extraMessage = f", in file {possibleFiles[0].asStr()}"
                print(f"Instruction difference at ROM addr 0x{i:X}{extraMessage}")
                builtBytes = builtRom[i : i + 4]
                expectedBytes = expectedRom[i : i + 4]
                print(f"Bytes: {utils.hexbytes(builtBytes, addColons=addColons)} vs {utils.hexbytes(expectedBytes, addColons=addColons)}")
                if bytesConverterCallback is not None:
                    builtConverted = bytesConverterCallback(builtBytes, builtMapFile)
                    expectedConverted = bytesConverterCallback(expectedBytes, expectedMapFile)
                    if builtConverted is not None and expectedConverted is not None:
                        print(f"{builtConverted} vs {expectedConverted}")

        if len(map_search_diff) >= diffCount and diffs > shift_cap:
            break

    if diffs == 0:
        print("No differences but ROMs differ?")
        return 1

    print()
    definite_shift = diffs > shift_cap
    if definite_shift:
        print(f"Over {shift_cap} differing words, must be a shifted ROM.")
    else:
        print(f"{diffs} differing word(s).")

    if diffs > 100:
        firstDifferingSym = builtMapFile.findLowestDifferingSymbol(expectedMapFile)
        if firstDifferingSym is None:
            print(f"No ROM shift{' (!?)' if definite_shift else ''}")
        else:
            sym, file, prevSym = firstDifferingSym
            extraMessage = ""
            if prevSym is not None:
                extraMessage = f" -- in {prevSym.name}?"
            print(f"Map appears to have shifted just before {sym.name} ({file.filepath}){extraMessage}")
            return 1

    return 0


def processArguments(args: argparse.Namespace):
    mapPath: Path = args.mapfile
    expectedMapPath: Path = args.expectedmap
    romPath: Path = args.rompath
    expectedRomPath: Path = args.expectedrom

    diffCount: int = args.count
    mismatchSize: bool = args.mismatch_size

    endian = args.endian

    exit(doFirstDiff(mapPath, expectedMapPath, romPath, expectedRomPath, diffCount, mismatchSize, endian=endian))


def addSubparser(subparser: argparse._SubParsersAction[argparse.ArgumentParser]):
    parser = subparser.add_parser("first_diff", help="Find the first difference(s) between the built ROM and the base ROM.")

    parser.add_argument("mapfile", help="Path to a map file", type=Path)
    parser.add_argument("expectedmap", help="Path to the map file in the expected dir", type=Path)
    parser.add_argument("rompath", help="Path to built ROM", type=Path)
    parser.add_argument("expectedrom", help="Path to the expected ROM", type=Path)

    parser.add_argument("-c", "--count", type=int, default=5, help="find up to this many instruction difference(s)")
    parser.add_argument("-m", "--mismatch-size", help="Do not exit early if the ROM sizes does not match", action="store_true")
    parser.add_argument("-e", "--endian", help="Specify endianness of the binary", choices=["big", "little"], default="big")

    parser.set_defaults(func=processArguments)
