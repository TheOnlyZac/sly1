#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

import dataclasses
import enum


@dataclasses.dataclass
class CompilerProperties:
    name: str

    hasLateRodata: bool = False

    prevAlign_double: int|None = None # TODO: Specifying 3 as the default should be harmless. Need to investigate.
    prevAlign_jumptable: int|None = None
    prevAlign_string: int|None = 2
    prevAlign_function: int|None = None

    pairMultipleHiToSameLow: bool = True

    allowRdataMigration: bool = False

    bigAddendWorkaroundForMigratedFunctions: bool = True
    """
    Modern GAS can handle big addends (outside the 16-bits range) for the `%lo`
    directive just fine, but old assemblers choke on them, so we truncate them
    to said range when building with those assemblers.

    Decomp projects usually use two assemblers:
    - One to assemble unmigrated files, usually with modern GAS.
    - Another one to assemble individual functions that get inserted into C
      files, either with asm directives from the compiler (using the built-in
      old assembler shipped with the old compiler) or with an external tools
      (like asm-proc for IDO).

    Modern GAS requires no addend truncation to produce matching output, so we
    don't use the workaround for unmigrated asm files.

    For migrated functions we need to know if the compiler uses modern GAS or
    old GAS. If it uses modern GAS (like IDO projects), then this flag should
    be turned off, but if the project uses its own old assembler (like most GCC
    based projects) then this flag needs to be turned on.
    """

    sectionAlign_text: int|None = None
    """
    The value the compiler will use to align the `.text` section of the given
    object.

    Used for determining `.text` file splits when disassembling full ROM images.

    The real aligment value will be computed like `1 << x`, where `x`
    corresponds to the value given to this property.

    If a compiler emits multiple `.text` sections per object (i.e. each function
    is emitted on its own section) then it is better to keep this value as
    `None`, since the split detector won't give any meaningful result.
    """

    sectionAlign_rodata: int|None = None
    """
    The value the compiler will use to align the `.rodata` section of the given
    object.

    Used for determining `.rodata` file splits when disassembling full ROM images.

    The real aligment value will be computed like `1 << x`, where `x`
    corresponds to the value given to this property.
    """


@enum.unique
class Compiler(enum.Enum):
    # General GCC
    GCC = CompilerProperties("GCC", prevAlign_jumptable=3)

    # N64
    IDO = CompilerProperties("IDO", hasLateRodata=True, pairMultipleHiToSameLow=False, bigAddendWorkaroundForMigratedFunctions=False, sectionAlign_text=4, sectionAlign_rodata=4)
    KMC = CompilerProperties("KMC", prevAlign_jumptable=3, sectionAlign_text=4, sectionAlign_rodata=4)
    SN64 = CompilerProperties("SN64", prevAlign_double=3, prevAlign_jumptable=3, allowRdataMigration=True, sectionAlign_text=4, sectionAlign_rodata=4)

    # iQue
    EGCS = CompilerProperties("EGCS", prevAlign_jumptable=3, sectionAlign_text=4, sectionAlign_rodata=4)

    # PS1
    PSYQ = CompilerProperties("PSYQ", prevAlign_double=3, prevAlign_jumptable=3, allowRdataMigration=True)

    # PS2
    MWCCPS2 = CompilerProperties("MWCCPS2", prevAlign_jumptable=4)
    EEGCC = CompilerProperties("EEGCC", prevAlign_jumptable=3, prevAlign_string=3, prevAlign_function=3)

    @staticmethod
    def fromStr(value: str) -> Compiler|None:
        return compilerOptions.get(value)


compilerOptions: dict[str, Compiler] = {
    x.name: x
    for x in [
        Compiler.GCC,
        Compiler.IDO,
        Compiler.KMC,
        Compiler.SN64,
        Compiler.EGCS,
        Compiler.PSYQ,
        Compiler.MWCCPS2,
        Compiler.EEGCC,
    ]
}
