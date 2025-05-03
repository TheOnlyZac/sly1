#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

import sys
from typing import TextIO
from pathlib import Path

from .. import common

from . import symbols


class FileBase(common.ElementBase):
    def __init__(self, context: common.Context, vromStart: int, vromEnd: int, vram: int, filename: str, words: list[int], sectionType: common.FileSectionType, segmentVromStart: int, overlayCategory: str|None) -> None:
        super().__init__(context, vromStart, vromEnd, 0, vram, filename, words, sectionType, segmentVromStart, overlayCategory)

        self.symbolList: list[symbols.SymbolBase] = []

        self.pointersOffsets: set[int] = set()

        self.isHandwritten: bool = False

        self.fileBoundaries: list[int] = list()

        self.symbolsVRams: set[int] = set()
        "addresses of symbols in this section"

        self.bytes: bytes = common.Utils.wordsToBytes(self.words)

        self.sectionAlignment: int|None = 4
        """
        In log2

        If the desired alignment for the file is 8, then `sectionAlignment`
        should be set to 3.
        """

        self.sectionFlags: str|None = None


    def setCommentOffset(self, commentOffset: int) -> None:
        self.commentOffset = commentOffset
        for sym in self.symbolList:
            sym.setCommentOffset(self.commentOffset)

    def getAsmPrelude_includes(self) -> str:
        output = ""

        output += f".include \"macro.inc\"{common.GlobalConfig.LINE_ENDS}"
        output += common.GlobalConfig.LINE_ENDS
        return output

    def getAsmPrelude_instructionDirectives(self) -> str:
        return ""

    def getAsmPrelude_sectionStart(self) -> str:
        output = ""

        output += f".section {self.getSectionName()}"
        if self.sectionFlags is not None:
            output += f", \"{self.sectionFlags}\""
        output += common.GlobalConfig.LINE_ENDS

        output += common.GlobalConfig.LINE_ENDS
        if self.sectionAlignment is not None:
            output += f".align {self.sectionAlignment}{common.GlobalConfig.LINE_ENDS}"
            output += common.GlobalConfig.LINE_ENDS
        return output

    def getAsmPrelude(self) -> str:
        output = ""

        if common.GlobalConfig.ASM_PRELUDE_USE_INCLUDES:
            output += self.getAsmPrelude_includes()
        if common.GlobalConfig.ASM_PRELUDE_USE_INSTRUCTION_DIRECTIVES:
            output += self.getAsmPrelude_instructionDirectives()
        if common.GlobalConfig.ASM_PRELUDE_USE_SECTION_START:
            output += self.getAsmPrelude_sectionStart()

        return output

    def getHash(self) -> str:
        buffer = common.Utils.wordsToBytes(self.words)
        return common.Utils.getStrHash(buffer)


    def printNewFileBoundaries(self) -> None:
        if not common.GlobalConfig.PRINT_NEW_FILE_BOUNDARIES:
            return

        if len(self.fileBoundaries) > 0:
            print(f"File {self.name}")
            print(f"Section: {self.sectionType.toStr()}")
            print(f"Found {len(self.symbolList)} symbols.")
            print(f"Found {len(self.fileBoundaries)} file boundaries.")

            print("    offset, size,       vram, symbols")

            boundaries = list(self.fileBoundaries)
            boundaries.append(self.sizew*4 + self.inFileOffset)

            for i in range(len(boundaries)-1):
                start = boundaries[i]
                end = boundaries[i+1]

                symbolsInBoundary = 0
                for func in self.symbolList:
                    funcOffset = func.inFileOffset - self.inFileOffset
                    if start <= funcOffset < end:
                        symbolsInBoundary += 1
                fileVram = 0
                if self.vram is not None:
                    fileVram = start + self.vram
                print(f"    {start+self.commentOffset:06X}, {end-start:06X}, {fileVram:08X}, {symbolsInBoundary:7}")

            print()

    def printAnalyzisResults(self) -> None:
        self.printNewFileBoundaries()


    def compareToFile(self, other_file: FileBase) -> dict:
        hash_one = self.getHash()
        hash_two = other_file.getHash()

        result = {
            "equal": hash_one == hash_two,
            "hash_one": hash_one,
            "hash_two": hash_two,
            "size_one": self.sizew * 4,
            "size_two": other_file.sizew * 4,
            "diff_bytes": 0,
            "diff_words": 0,
        }

        diff_bytes = 0
        diff_words = 0

        if not result["equal"]:
            min_len = min(self.sizew, other_file.sizew)
            for i in range(min_len):
                for j in range(4):
                    if (self.words[i] & (0xFF << (j * 8))) != (other_file.words[i] & (0xFF << (j * 8))):
                        diff_bytes += 1

            min_len = min(self.sizew, other_file.sizew)
            for i in range(min_len):
                if self.words[i] != other_file.words[i]:
                    diff_words += 1

        result["diff_bytes"] = diff_bytes
        result["diff_words"] = diff_words

        return result

    def blankOutDifferences(self, other: FileBase) -> bool:
        if not common.GlobalConfig.REMOVE_POINTERS:
            return False

        return False

    def removePointers(self) -> bool:
        if not common.GlobalConfig.REMOVE_POINTERS:
            return False

        return False


    def disassemble(self, migrate: bool=False, useGlobalLabel: bool=True) -> str:
        output = ""

        if not migrate:
            output += self.getSpimdisasmVersionString()

        for i, sym in enumerate(self.symbolList):
            output += sym.disassemble(migrate=migrate, useGlobalLabel=useGlobalLabel, isSplittedSymbol=False)
            if i + 1 < len(self.symbolList):
                output += common.GlobalConfig.LINE_ENDS
        return output

    def disassembleToFile(self, f: TextIO) -> None:
        if common.GlobalConfig.ASM_USE_PRELUDE:
            f.write(self.getAsmPrelude())
        f.write(self.disassemble())


    def saveToFile(self, filepath: str) -> None:
        if len(self.symbolList) == 0:
            return

        if filepath == "-":
            self.disassembleToFile(sys.stdout)
        else:
            if common.GlobalConfig.WRITE_BINARY:
                if self.sizew > 0:
                    buffer = common.Utils.wordsToBytes(self.words)
                    common.Utils.writeBytesToFile(Path(filepath + self.sectionType.toStr()), buffer)
            with open(filepath + self.sectionType.toStr() + ".s", "w", encoding="utf-8") as f:
                self.disassembleToFile(f)


def createEmptyFile() -> FileBase:
    return FileBase(common.Context(), 0, 0, 0, "", [], common.FileSectionType.Unknown, 0, None)
