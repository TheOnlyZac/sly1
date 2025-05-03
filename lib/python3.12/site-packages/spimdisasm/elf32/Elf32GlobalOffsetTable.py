#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

import dataclasses
import struct

from .. import common

from .Elf32Constants import Elf32SectionHeaderNumber
from .Elf32Dyns import Elf32Dyns
from .Elf32Syms import Elf32Syms, Elf32SymEntry


@dataclasses.dataclass
class GotEntry:
    symEntry: Elf32SymEntry
    initial: int|None = None

    def getAddress(self) -> int:
        if self.initial is not None:
            return self.initial
        return self.symEntry.value


class Elf32GlobalOffsetTable:
    def __init__(self, array_of_bytes: bytes, offset: int, rawSize: int) -> None:
        self.entries: list[int] = list()
        self.offset: int = offset
        self.rawSize: int = rawSize

        entryFormat = common.GlobalConfig.ENDIAN.toFormatString() + f"{rawSize//4}I"
        self.entries = list(struct.unpack_from(entryFormat, array_of_bytes, offset))


        self.localsTable: list[int] = list()
        self.globalsTable: list[GotEntry] = list()

    def __getitem__(self, key: int) -> int:
        return self.entries[key]

    def __len__(self) -> int:
        return len(self.entries)


    def initTables(self, dynamic: Elf32Dyns, dynsym: Elf32Syms) -> None:
        if dynamic.gotSym is None or dynamic.localGotNo is None:
            return

        # for i in range(len(self.entries)):
        #     print(i, f"{self.entries[i]:X}")

        for i in range(dynamic.localGotNo):
            self.localsTable.append(self.entries[i])

        for i in range(dynamic.gotSym, len(dynsym)):
            symEntry = dynsym[i]
            gotEntry = GotEntry(symEntry)

            if symEntry.shndx == Elf32SectionHeaderNumber.UNDEF.value or symEntry.shndx == Elf32SectionHeaderNumber.COMMON.value:
                gotIndex = dynamic.localGotNo + (i - dynamic.gotSym)
                gotEntry.initial = self.entries[gotIndex]

            self.globalsTable.append(gotEntry)
