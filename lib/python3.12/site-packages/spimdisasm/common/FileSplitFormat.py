#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

from pathlib import Path
from typing import Generator

from . import Utils
from .FileSectionType import FileSectionType


class FileSplitEntry:
    def __init__(self, offset: int, vram: int, fileName: str, section: FileSectionType, nextOffset: int, isHandwritten: bool, isRsp: bool) -> None:
        self.offset: int = offset
        self.vram: int = vram
        self.fileName: str = fileName
        self.section: FileSectionType = section
        self.nextOffset: int = nextOffset
        self.isHandwritten: bool = isHandwritten
        self.isRsp: bool = isRsp


class FileSplitFormat:
    def __init__(self, csvPath: Path|None = None) -> None:
        self.splits: list[list[str]] = list()

        if csvPath is not None:
            self.readCsvFile(csvPath)

    def __len__(self) -> int:
        return len(self.splits)

    def __iter__(self) -> Generator[FileSplitEntry, None, None]:
        section = FileSectionType.Invalid

        for i, row in enumerate(self.splits):
            offsetStr, vramStr, fileName = row

            isHandwritten = False
            isRsp = False
            offsetStr = offsetStr.upper()
            if offsetStr[-1] == "H":
                isHandwritten = True
                offsetStr = offsetStr[:-1]
            elif offsetStr[-1] == "R":
                isRsp = True
                offsetStr = offsetStr[:-1]

            possibleSection = FileSectionType.fromStr(fileName)
            if possibleSection != FileSectionType.Invalid:
                if possibleSection == FileSectionType.End:
                    break
                else:
                    section = possibleSection
                    continue

            vram = int(vramStr, 16)
            offset = int(offsetStr, 16)
            nextOffset = 0xFFFFFF
            if i + 1 < len(self.splits):
                if self.splits[i+1][2] == ".end":
                    nextOffsetStr = self.splits[i+1][0]
                elif self.splits[i+1][2].startswith("."):
                    nextOffsetStr = self.splits[i+2][0]
                else:
                    nextOffsetStr = self.splits[i+1][0]
                if nextOffsetStr.upper()[-1] in ("H", "R"):
                    nextOffsetStr = nextOffsetStr[:-1]
                nextOffset = int(nextOffsetStr, 16)

            yield FileSplitEntry(offset, vram, fileName, section, nextOffset, isHandwritten, isRsp)

    def readCsvFile(self, csvPath: Path) -> None:
        self.splits = Utils.readCsv(csvPath)
        self.splits = [x for x in self.splits if len(x) > 0]

    def append(self, element: FileSplitEntry | list[str]) -> None:
        if isinstance(element, FileSplitEntry):

            offset = f"{element.offset:X}"
            if element.isRsp:
                offset += "R"
            elif element.isHandwritten:
                offset += "H"

            vram = f"{element.vram:X}"
            fileName = element.fileName

            if element.section != FileSectionType.Invalid:
                section = element.section.toStr()
                self.splits.append(["offset", "vram", section])

            self.splits.append([offset, vram, fileName])

            # nextOffset # ignored
        elif isinstance(element, list):
            if len(element) != 3:
                # TODO: error message
                raise TypeError()
            for x in element:
                if not isinstance(x, str):
                    # TODO: error message
                    raise TypeError()
            self.splits.append(element)
        else:
            # TODO: error message
            raise TypeError()

    def appendEndSection(self, offset: int, vram: int) -> None:
        self.splits.append([f"{offset:X}", f"{vram:X}", ".end"])
