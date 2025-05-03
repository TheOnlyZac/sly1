#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

from ... import common

from .. import symbols

from . import SectionBase


class SectionData(SectionBase):
    def __init__(self, context: common.Context, vromStart: int, vromEnd: int, vram: int, filename: str, array_of_bytes: bytes, segmentVromStart: int, overlayCategory: str|None) -> None:
        if common.GlobalConfig.ENDIAN_DATA is not None:
            words = common.Utils.endianessBytesToWords(common.GlobalConfig.ENDIAN_DATA, array_of_bytes, vromStart, vromEnd)
        else:
            words = common.Utils.bytesToWords(array_of_bytes, vromStart, vromEnd)
        super().__init__(context, vromStart, vromEnd, vram, filename, words, common.FileSectionType.Data, segmentVromStart, overlayCategory)


    def analyze(self) -> None:
        self._checkAndCreateFirstSymbol()

        symbolList: list[tuple[int, common.ContextSymbol]] = []
        localOffset = 0
        localOffsetsWithSymbols: set[int] = set()

        needsFurtherAnalyzis = False

        for w in self.words:
            currentVram = self.getVramOffset(localOffset)

            contextSym = self._getOwnedSymbol(localOffset)
            if contextSym is not None:
                symbolList.append((localOffset, contextSym))
                localOffsetsWithSymbols.add(localOffset)

            elif self.popPointerInDataReference(currentVram) is not None:
                contextSym = self._addOwnedSymbol(localOffset)
                if contextSym is not None:
                    symbolList.append((localOffset, contextSym))
                    localOffsetsWithSymbols.add(localOffset)

            if self.checkWordIsASymbolReference(w):
                if w < currentVram and self.containsVram(w):
                    # References a data symbol from this section and it is behind this current symbol
                    needsFurtherAnalyzis = True

            localOffset += 4

        if needsFurtherAnalyzis:
            localOffset = 0
            for w in self.words:
                currentVram = self.getVramOffset(localOffset)

                if self.popPointerInDataReference(currentVram) is not None and localOffset not in localOffsetsWithSymbols:
                    contextSym = self._addOwnedSymbol(localOffset)
                    if contextSym is not None:
                        symbolList.append((localOffset, contextSym))
                        localOffsetsWithSymbols.add(localOffset)

                localOffset += 4

            # Since we appended new symbols, this list is not sorted anymore
            symbolList.sort()

        self.processStaticRelocs()

        for i, (offset, contextSym) in enumerate(symbolList):
            if i + 1 == len(symbolList):
                words = self.words[offset//4:]
            else:
                nextOffset = symbolList[i+1][0]
                if offset == nextOffset:
                    continue
                words = self.words[offset//4:nextOffset//4]

            vrom = self.getVromOffset(offset)
            vromEnd = vrom + 4*len(words)
            sym = symbols.SymbolData(self.context, vrom, vromEnd, offset + self.inFileOffset, contextSym.vram, words, self.segmentVromStart, self.overlayCategory)
            sym.parent = self
            sym.setCommentOffset(self.commentOffset)
            sym.stringEncoding = self.stringEncoding
            sym.analyze()
            self.symbolList.append(sym)

            self.symbolsVRams.add(contextSym.vram)


    def removePointers(self) -> bool:
        if not common.GlobalConfig.REMOVE_POINTERS:
            return False

        was_updated = False
        for i in range(self.sizew):
            top_byte = (self.words[i] >> 24) & 0xFF
            if top_byte == 0x80:
                self.words[i] = top_byte << 24
                was_updated = True
            if (top_byte & 0xF0) == 0x00 and (top_byte & 0x0F) != 0x00:
                self.words[i] = top_byte << 24
                was_updated = True

        return was_updated
