#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

from ... import common

from . import SymbolBase


class SymbolData(SymbolBase):
    def __init__(
        self,
        context: common.Context,
        vromStart: int,
        vromEnd: int,
        inFileOffset: int,
        vram: int,
        words: list[int],
        segmentVromStart: int,
        overlayCategory: str | None,
    ):
        super().__init__(
            context,
            vromStart,
            vromEnd,
            inFileOffset,
            vram,
            words,
            common.FileSectionType.Data,
            segmentVromStart,
            overlayCategory,
        )

    def analyze(self) -> None:
        super().analyze()

        if self.contextSym.hasUserDeclaredSize():
            # Check user declared size matches the size that will be generated
            contextSymSize = self.contextSym.getSize()
            actualSize = self.sizew * 4
            if actualSize < contextSymSize:
                warningMessage = f"""
Range check triggered: .data symbol (name: {self.getName()}, address: 0x{self.contextSym.vram:08X}):
    User declared size (0x{contextSymSize:X}) does not match the amount of bytes that will be emitted (0x{actualSize:X}).
    Try checking the size again or look for symbols which overlaps this region"""
                if common.GlobalConfig.PANIC_RANGE_CHECK:
                    assert actualSize == contextSymSize, warningMessage
                else:
                    common.Utils.eprint(f"\n{warningMessage}\n")
