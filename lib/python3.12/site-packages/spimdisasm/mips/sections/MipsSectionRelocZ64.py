#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

# Relocation format used by overlays of Zelda64, Yoshi Story and Doubutsu no Mori (Animal Forest)

from __future__ import annotations

from pathlib import Path

from ... import common

from .. import symbols

from . import SectionBase


class RelocEntry:
    def __init__(self, entry: int) -> None:
        self.sectionId = entry >> 30
        self.relocType = (entry >> 24) & 0x3F
        self.offset = entry & 0x00FFFFFF

    @property
    def reloc(self) -> int:
        return (self.sectionId << 30) | (self.relocType << 24) | (self.offset)

    def getSectionType(self) -> common.FileSectionType:
        return common.FileSectionType.fromId(self.sectionId)

    def getRelocType(self) -> common.RelocType|None:
        return common.RelocType.fromValue(self.relocType)

    def __str__(self) -> str:
        section = self.getSectionType().toStr()
        relocName = "None"
        reloc = self.getRelocType()
        if reloc is not None:
            relocName = reloc.name

        return f"{section} {relocName} 0x{self.offset:X}"
    def __repr__(self) -> str:
        return self.__str__()


class SectionRelocZ64(SectionBase):
    def __init__(self, context: common.Context, vromStart: int, vromEnd: int, vram: int, filename: str, array_of_bytes: bytes, segmentVromStart: int, overlayCategory: str|None) -> None:
        super().__init__(context, vromStart, vromEnd, vram, filename, common.Utils.bytesToWords(array_of_bytes, vromStart, vromEnd), common.FileSectionType.Reloc, segmentVromStart, overlayCategory)

        self.seekup: int = self.words[-1]

        self.setCommentOffset(self.sizew*4 - self.seekup)

        # Remove non reloc stuff
        self.words: list[int] = self.words[-self.seekup // 4:]

        self.sectionSizes: dict[common.FileSectionType, int] = {
            common.FileSectionType.Text: self.words[0],
            common.FileSectionType.Data: self.words[1],
            common.FileSectionType.Rodata: self.words[2],
            common.FileSectionType.Bss: self.words[3],
        }
        self.relocCount: int = self.words[4]

        self.tail: list[int] = self.words[self.relocCount+5:-1]

        self.entries: list[RelocEntry] = list()
        for word in self.words[5:self.relocCount+5]:
            self.entries.append(RelocEntry(word))

        self.differentSegment: bool = False

        self.sectionFlags = "a"
        self.enableStringGuessing = False

    @property
    def nRelocs(self) -> int:
        return len(self.entries)

    @property
    def textSize(self) -> int:
        return self.sectionSizes[common.FileSectionType.Text]
    @property
    def dataSize(self) -> int:
        return self.sectionSizes[common.FileSectionType.Data]
    @property
    def rodataSize(self) -> int:
        return self.sectionSizes[common.FileSectionType.Rodata]
    @property
    def bssSize(self) -> int:
        return self.sectionSizes[common.FileSectionType.Bss]


    def analyze(self) -> None:
        # The name may be a path, so we take the name of the file and discard everything else
        relocName = Path(self.name).stem

        localOffset = 0

        sym: symbols.SymbolBase

        currentVram = self.getVramOffset(localOffset)
        vrom = self.getVromOffset(localOffset)
        vromEnd = vrom + 4 * 4
        sym = symbols.SymbolData(self.context, vrom, vromEnd, localOffset + self.inFileOffset, currentVram, self.words[0:4], self.segmentVromStart, self.overlayCategory)
        sym.contextSym.name = f"{relocName}_OverlayInfo"
        sym.contextSym.userDeclaredType = "s32"
        sym.contextSym.allowedToReferenceSymbols = False
        sym.contextSym.allowedToBeReferenced = False
        sym.parent = self
        sym.setCommentOffset(self.commentOffset)
        sym.endOfLineComment = {i: f" /* _{relocName}Segment{sectName.toCapitalizedStr()}Size */" for i, sectName in enumerate(common.FileSections_ListBasic)}
        sym.analyze()
        self.symbolList.append(sym)
        localOffset += 4 * 4

        currentVram = self.getVramOffset(localOffset)
        vrom = self.getVromOffset(localOffset)
        vromEnd = vrom + 4
        sym = symbols.SymbolData(self.context, vrom, vromEnd, localOffset + self.inFileOffset, currentVram, [self.relocCount], self.segmentVromStart, self.overlayCategory)
        sym.contextSym.name = f"{relocName}_RelocCount"
        sym.contextSym.userDeclaredType = "s32"
        sym.contextSym.allowedToReferenceSymbols = False
        sym.contextSym.allowedToBeReferenced = False
        sym.parent = self
        sym.setCommentOffset(self.commentOffset)
        sym.analyze()
        self.symbolList.append(sym)
        localOffset += 4

        currentVram = self.getVramOffset(localOffset)
        vrom = self.getVromOffset(localOffset)
        vromEnd = vrom + 4 * len(self.entries)
        sym = symbols.SymbolData(self.context, vrom, vromEnd, localOffset + self.inFileOffset, currentVram, [r.reloc for r in self.entries], self.segmentVromStart, self.overlayCategory)
        sym.contextSym.name = f"{relocName}_OverlayRelocations"
        sym.contextSym.userDeclaredType = "s32"
        sym.contextSym.allowedToReferenceSymbols = False
        sym.contextSym.allowedToBeReferenced = False
        sym.parent = self
        sym.setCommentOffset(self.commentOffset)
        sym.endOfLineComment = {i: f" /* {str(r)} */" for i, r in enumerate(self.entries)}
        sym.analyze()
        self.symbolList.append(sym)
        localOffset += 4 * len(self.entries)

        if len(self.tail) > 0:
            currentVram = self.getVramOffset(localOffset)
            vrom = self.getVromOffset(localOffset)
            vromEnd = vrom + 4 * len(self.tail)
            sym = symbols.SymbolData(self.context, vrom, vromEnd, localOffset + self.inFileOffset, currentVram, self.tail, self.segmentVromStart, self.overlayCategory)
            sym.contextSym.name = f"{relocName}_Padding"
            sym.contextSym.userDeclaredType = "s32"
            sym.contextSym.allowedToReferenceSymbols = False
            sym.contextSym.allowedToBeReferenced = False
            sym.parent = self
            sym.setCommentOffset(self.commentOffset)
            sym.analyze()
            self.symbolList.append(sym)
            localOffset += 4 * len(self.tail)

        currentVram = self.getVramOffset(localOffset)
        vrom = self.getVromOffset(localOffset)
        vromEnd = vrom + 4
        sym = symbols.SymbolData(self.context, vrom, vromEnd, localOffset + self.inFileOffset, currentVram, [self.seekup], self.segmentVromStart, self.overlayCategory)
        sym.contextSym.name = f"{relocName}_OverlayInfoOffset"
        sym.contextSym.userDeclaredType = "s32"
        sym.contextSym.allowedToReferenceSymbols = False
        sym.contextSym.allowedToBeReferenced = False
        sym.parent = self
        sym.setCommentOffset(self.commentOffset)
        sym.analyze()
        self.symbolList.append(sym)

        for sym in self.symbolList:
            if sym.vram is not None:
                self.symbolsVRams.add(sym.vram)
