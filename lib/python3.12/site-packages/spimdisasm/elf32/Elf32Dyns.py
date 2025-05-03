#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

import dataclasses
import struct
from typing import Generator

from .. import common

from .Elf32Constants import Elf32DynamicTable


# a.k.a. Dyn ()
@dataclasses.dataclass
class Elf32DynEntry:
    tag:  int  # int32_t  # 0x00
    "Dynamic entry type"
    val:  int  # uint32_t # 0x04
    "Integer value"
                            # 0x08

    @property
    def ptr(self) -> int:
        "Address value"
        # Elf32_Addr
        return self.val

    @staticmethod
    def fromBytearray(array_of_bytes: bytes, offset: int = 0) -> Elf32DynEntry:
        entryFormat = common.GlobalConfig.ENDIAN.toFormatString() + "II"
        unpacked = struct.unpack_from(entryFormat, array_of_bytes, offset)

        return Elf32DynEntry(*unpacked)

    @staticmethod
    def structSize() -> int:
        return 0x08


class Elf32Dyns:
    def __init__(self, array_of_bytes: bytes, offset: int, rawSize: int) -> None:
        self.dyns: list[Elf32DynEntry] = list()
        self.offset: int = offset
        self.rawSize: int = rawSize

        self.pltGot: int | None = None
        self.localGotNo: int | None = None
        self.symTabNo: int | None = None
        self.gotSym: int | None = None

        for i in range(rawSize // Elf32DynEntry.structSize()):
            entry = Elf32DynEntry.fromBytearray(array_of_bytes, offset + i*Elf32DynEntry.structSize())
            self.dyns.append(entry)

            if entry.tag == Elf32DynamicTable.PLTGOT.value:
                self.pltGot = entry.val
            elif entry.tag == Elf32DynamicTable.MIPS_LOCAL_GOTNO.value:
                self.localGotNo = entry.val
            elif entry.tag == Elf32DynamicTable.MIPS_SYMTABNO.value:
                self.symTabNo = entry.val
            elif entry.tag == Elf32DynamicTable.MIPS_GOTSYM.value:
                self.gotSym = entry.val
            elif entry.tag == Elf32DynamicTable.NULL.value:
                pass
            else:
                pass
                # print(f"Unknown dyn value: tag={entry.tag:08X} val={entry.val:08X}")

    def __getitem__(self, key: int) -> Elf32DynEntry:
        return self.dyns[key]

    def __iter__(self) -> Generator[Elf32DynEntry, None, None]:
        for entry in self.dyns:
            yield entry

    def getGpValue(self) -> int|None:
        if self.pltGot is None:
            return None
        return self.pltGot + 0x7FF0
