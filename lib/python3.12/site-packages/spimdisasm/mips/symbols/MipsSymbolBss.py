#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

from ... import common

from . import SymbolBase


class SymbolBss(SymbolBase):
    def __init__(
        self,
        context: common.Context,
        vromStart: int,
        vromEnd: int,
        inFileOffset: int,
        vram: int,
        spaceSize: int,
        segmentVromStart: int,
        overlayCategory: str | None,
    ):
        super().__init__(
            context,
            vromStart,
            vromEnd,
            inFileOffset,
            vram,
            list(),
            common.FileSectionType.Bss,
            segmentVromStart,
            overlayCategory,
        )

        self.spaceSize: int = spaceSize

    @property
    def sizew(self) -> int:
        return self.spaceSize // 4

    def analyze(self) -> None:
        super().analyze()

        if self.contextSym.hasUserDeclaredSize():
            # Check user declared size matches the size that will be generated
            contextSymSize = self.contextSym.getSize()
            if self.spaceSize != contextSymSize:
                warningMessage = f"""
Range check triggered: .bss symbol (name: {self.getName()}, address: 0x{self.contextSym.vram:08X}):
    User declared size (0x{contextSymSize:X}) does not match the .space that will be emitted (0x{self.spaceSize:X}).
    Try checking the size again or look for symbols which overlaps this region"""
                if common.GlobalConfig.PANIC_RANGE_CHECK:
                    assert self.spaceSize == contextSymSize, warningMessage
                else:
                    common.Utils.eprint(f"\n{warningMessage}\n")

    def disassembleAsBss(self, useGlobalLabel: bool = True) -> str:
        output = self.contextSym.getReferenceeSymbols()
        output += self.getPrevAlignDirective(0)

        output += self.getSymbolAsmDeclaration(self.getName(), useGlobalLabel)
        output += self.generateAsmLineComment(0, emitRomOffset=False)
        output += f" .space 0x{self.spaceSize:02X}{common.GlobalConfig.LINE_ENDS}"

        nameEnd = self.getNameEnd()
        if nameEnd is not None:
            output += self.getSymbolAsmDeclaration(nameEnd, useGlobalLabel)

        return output

    def disassemble(
        self,
        migrate: bool = False,
        useGlobalLabel: bool = True,
        isSplittedSymbol: bool = False,
    ) -> str:
        return self.disassembleAsBss()
