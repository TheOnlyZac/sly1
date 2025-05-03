#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

import dataclasses
import enum

from .ContextSymbols import ContextSymbol
from .FileSectionType import FileSectionType
from .GlobalConfig import GlobalConfig


class RelocType(enum.Enum):
    MIPS_NONE           = 0 # No reloc
    MIPS_16             = 1 # Direct 16 bit
    MIPS_32             = 2 # Direct 32 bit
    MIPS_REL32          = 3 # PC relative 32 bit
    MIPS_26             = 4 # Direct 26 bit shifted
    MIPS_HI16           = 5 # High 16 bit
    MIPS_LO16           = 6 # Low 16 bit
    MIPS_GPREL16        = 7 # GP relative 16 bit
    MIPS_LITERAL        = 8 # 16 bit literal entry
    MIPS_GOT16          = 9 # 16 bit GOT entry
    MIPS_PC16           = 10 # PC relative 16 bit
    MIPS_CALL16         = 11 # 16 bit GOT entry for function
    MIPS_GPREL32        = 12 # GP relative 32 bit

    MIPS_GOT_HI16       = 22
    MIPS_GOT_LO16       = 23
    MIPS_CALL_HI16      = 30
    MIPS_CALL_LO16      = 31

    CUSTOM_CONSTANT_HI  = -1
    CUSTOM_CONSTANT_LO  = -2

    def getPercentRel(self) -> str|None:
        return _percentRel.get(self)

    def getWordRel(self) -> str|None:
        return _wordRel.get(self)

    @staticmethod
    def fromValue(value: int) -> RelocType|None:
        try:
            return RelocType(value)
        except ValueError:
            return None

    @staticmethod
    def fromStr(value: str) -> RelocType|None:
        value = value.upper()
        if value == "MIPS_NONE":
            return RelocType.MIPS_NONE
        if value == "MIPS_16":
            return RelocType.MIPS_16
        if value == "MIPS_32":
            return RelocType.MIPS_32
        if value == "MIPS_REL32":
            return RelocType.MIPS_REL32
        if value == "MIPS_26":
            return RelocType.MIPS_26
        if value == "MIPS_HI16":
            return RelocType.MIPS_HI16
        if value == "MIPS_LO16":
            return RelocType.MIPS_LO16
        if value == "MIPS_GPREL16":
            return RelocType.MIPS_GPREL16
        if value == "MIPS_LITERAL":
            return RelocType.MIPS_LITERAL
        if value == "MIPS_GOT16":
            return RelocType.MIPS_GOT16
        if value == "MIPS_PC16":
            return RelocType.MIPS_PC16
        if value == "MIPS_CALL16":
            return RelocType.MIPS_CALL16
        if value == "MIPS_GPREL32":
            return RelocType.MIPS_GPREL32
        if value == "MIPS_GOT_HI16":
            return RelocType.MIPS_GOT_HI16
        if value == "MIPS_GOT_LO16":
            return RelocType.MIPS_GOT_LO16
        if value == "MIPS_CALL_HI16":
            return RelocType.MIPS_CALL_HI16
        if value == "MIPS_CALL_LO16":
            return RelocType.MIPS_CALL_LO16
        if value == "CUSTOM_CONSTANT_HI":
            return RelocType.CUSTOM_CONSTANT_HI
        if value == "CUSTOM_CONSTANT_LO":
            return RelocType.CUSTOM_CONSTANT_LO
        return None


_percentRel = {
    # RelocType.MIPS_NONE:       f"",
    # RelocType.MIPS_16:         f"",
    # RelocType.MIPS_32:         f"",
    # RelocType.MIPS_REL32:      f"",
    # RelocType.MIPS_26:         f"",
    RelocType.MIPS_HI16:       f"%hi",
    RelocType.MIPS_LO16:       f"%lo",
    RelocType.MIPS_GPREL16:    f"%gp_rel",
    # RelocType.MIPS_LITERAL:    f"",
    RelocType.MIPS_GOT16:      f"%got",
    # RelocType.MIPS_PC16:       f"",
    RelocType.MIPS_CALL16:     f"%call16",
    # RelocType.MIPS_GPREL32:    f"",

    RelocType.MIPS_GOT_HI16:   f"%got_hi",
    RelocType.MIPS_GOT_LO16:   f"%got_lo",
    RelocType.MIPS_CALL_HI16:  f"%call_hi",
    RelocType.MIPS_CALL_LO16:  f"%call_lo",
}

_wordRel = {
    # RelocType.MIPS_NONE:       f"",
    # RelocType.MIPS_16:         f"",
    RelocType.MIPS_32:         f".word",
    # RelocType.MIPS_REL32:      f"",
    # RelocType.MIPS_26:         f"",
    # RelocType.MIPS_HI16:       f"",
    # RelocType.MIPS_LO16:       f"",
    # RelocType.MIPS_GPREL16:    f"",
    # RelocType.MIPS_LITERAL:    f"",
    # RelocType.MIPS_GOT16:      f"",
    # RelocType.MIPS_PC16:       f"",
    # RelocType.MIPS_CALL16:     f"",
    RelocType.MIPS_GPREL32:    f".gpword",
    # RelocType.MIPS_GOT_HI16:   f"",
    # RelocType.MIPS_GOT_LO16:   f"",
    # RelocType.MIPS_CALL_HI16:  f"",
    # RelocType.MIPS_CALL_LO16:  f"",
}

_operationRel = {
    RelocType.CUSTOM_CONSTANT_HI:  f">> 16",
    RelocType.CUSTOM_CONSTANT_LO:  f"& 0xFFFF",
}

@dataclasses.dataclass
class RelocationStaticReference:
    # For elfs with relocations to static symbols
    sectionType: FileSectionType
    sectionVram: int

@dataclasses.dataclass
class RelocationInfo:
    relocType: RelocType
    symbol: ContextSymbol|str

    addend: int = 0

    staticReference: RelocationStaticReference|None = None
    globalReloc: bool = False

    def getName(self, isSplittedSymbol: bool=False) -> str:
        if isinstance(self.symbol, ContextSymbol):
            name = self.symbol.getName()
        else:
            name = self.symbol

        if self.addend == 0:
            return name

        if GlobalConfig.COMPILER.value.bigAddendWorkaroundForMigratedFunctions and isSplittedSymbol:
            if self.relocType == RelocType.MIPS_LO16:
                if self.addend < -0x8000:
                    return f"{name} - (0x{-self.addend:X} & 0xFFFF)"
                if self.addend > 0x7FFF:
                    return f"{name} + (0x{self.addend:X} & 0xFFFF)"

        if self.addend < 0:
            return f"{name} - 0x{-self.addend:X}"
        return f"{name} + 0x{self.addend:X}"

    def getNameWithReloc(self, *, isSplittedSymbol: bool=False, ignoredRelocs: set[RelocType]=set()) -> str:
        name = self.getName(isSplittedSymbol=isSplittedSymbol)

        percentRel = self.relocType.getPercentRel()
        if percentRel is not None:
            if self.relocType in ignoredRelocs:
                return f"({name})"
            return f"{percentRel}({name})"

        wordRel = self.relocType.getWordRel()
        if wordRel is not None:
            return f"{wordRel} {name}"

        operationRel = _operationRel.get(self.relocType)
        if operationRel is not None:
            return f"({name} {operationRel})"

        return name

    def getInlineStr(self, isSplittedSymbol: bool=False) -> str:
        output = f"    # {self.relocType.name} '{self.getName(isSplittedSymbol=isSplittedSymbol)}'"
        if self.staticReference is not None:
            output += f" (static)"
        if self.globalReloc:
            output += f" (global reloc)"
        output += f"{GlobalConfig.LINE_ENDS}"
        return output

    def isRelocNone(self) -> bool:
        return self.relocType == RelocType.MIPS_NONE
