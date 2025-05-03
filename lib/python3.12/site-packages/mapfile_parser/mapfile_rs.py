#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2023-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

from typing import Any


from .mapfile_parser import FoundSymbolInfo as FoundSymbolInfo
from .mapfile_parser import SymbolComparisonInfo as SymbolComparisonInfo
from .mapfile_parser import MapsComparisonInfo as MapsComparisonInfo
from .mapfile_parser import Symbol as Symbol
from .mapfile_parser import File as File
from .mapfile_parser import Segment as Segment
from .mapfile_parser import MapFile as MapFile


def __filers_serializeVram(self: File, humanReadable: bool=True) -> str|int|None:
    if humanReadable:
        return f"0x{self.vram:08X}"
    return self.vram

def __filers_serializeSize(self: File, humanReadable: bool=True) -> str|int|None:
    if humanReadable:
        return f"0x{self.size:X}"
    return self.size

def __filers_serializeVrom(self: File, humanReadable: bool=True) -> str|int|None:
    if self.vrom is None:
        return None
    if humanReadable:
        return f"0x{self.vrom:06X}"
    return self.vrom

def __filers_toJson(self: File, humanReadable: bool=True) -> dict[str, Any]:
    fileDict: dict[str, Any] = {
        "filepath": str(self.filepath),
        "sectionType": self.sectionType,
        "vram": self.serializeVram(humanReadable=humanReadable),
        "size": self.serializeSize(humanReadable=humanReadable),
        "vrom": self.serializeVrom(humanReadable=humanReadable),
    }

    symbolsList = []
    for symbol in self:
        symbolsList.append(symbol.toJson(humanReadable=humanReadable))

    fileDict["symbols"] = symbolsList
    return fileDict

File.serializeVram = __filers_serializeVram # type: ignore
File.serializeSize = __filers_serializeSize # type: ignore
File.serializeVrom = __filers_serializeVrom # type: ignore
File.toJson = __filers_toJson # type: ignore


def __segmentrs_serializeVram(self: Segment, humanReadable: bool=True) -> str|int|None:
    if humanReadable:
        return f"0x{self.vram:08X}"
    return self.vram

def __segmentrs_serializeSize(self: Segment, humanReadable: bool=True) -> str|int|None:
    if humanReadable:
        return f"0x{self.size:X}"
    return self.size

def __segmentrs_serializeVrom(self: Segment, humanReadable: bool=True) -> str|int|None:
    if humanReadable:
        return f"0x{self.vrom:06X}"
    return self.vrom

def __segmentrs_toJson(self: Segment, humanReadable: bool=True) -> dict[str, Any]:
    segmentDict: dict[str, Any] = {
        "name": self.name,
        "vram": self.serializeVram(humanReadable=humanReadable),
        "size": self.serializeSize(humanReadable=humanReadable),
        "vrom": self.serializeVrom(humanReadable=humanReadable),
    }

    filesList = []
    for file in self:
        filesList.append(file.toJson(humanReadable=humanReadable))

    segmentDict["files"] = filesList

    return segmentDict

Segment.serializeVram = __segmentrs_serializeVram # type: ignore
Segment.serializeSize = __segmentrs_serializeSize # type: ignore
Segment.serializeVrom = __segmentrs_serializeVrom # type: ignore
Segment.toJson = __segmentrs_toJson # type: ignore



def __mapfilers_printAsCsv(self: MapFile, printVram: bool=True, skipWithoutSymbols: bool=True):
    print(self.toCsv(printVram=printVram, skipWithoutSymbols=skipWithoutSymbols), end="")

def __mapfilers_printSymbolsCsv(self: MapFile):
    print(self.toCsvSymbols(), end="")

def __mapfilers_toJson(self: MapFile, humanReadable: bool=True) -> dict[str, Any]:
    segmentsList = []
    for segment in self:
        segmentsList.append(segment.toJson(humanReadable=humanReadable))

    result: dict[str, Any] = {
        "segments": segmentsList
    }
    return result

MapFile.printAsCsv = __mapfilers_printAsCsv # type: ignore
MapFile.printSymbolsCsv = __mapfilers_printSymbolsCsv # type: ignore
MapFile.toJson = __mapfilers_toJson # type: ignore
