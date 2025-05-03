#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

import dataclasses
import struct
from typing import Generator

from .. import common

from .Elf32Constants import Elf32SectionHeaderNumber


# a.k.a. Shdr (section header)
@dataclasses.dataclass
class Elf32SectionHeaderEntry:
    name:       int  # word     # 0x00
    type:       int  # word     # 0x04
    flags:      int  # word     # 0x08
    addr:       int  # address  # 0x0C
    offset:     int  # offset   # 0x10
    size:       int  # word     # 0x14
    link:       int  # word     # 0x18
    info:       int  # word     # 0x1C
    addralign:  int  # word     # 0x20
    entsize:    int  # word     # 0x24
                                # 0x28

    @staticmethod
    def fromBytearray(array_of_bytes: bytes, offset: int = 0) -> Elf32SectionHeaderEntry:
        headerFormat = common.GlobalConfig.ENDIAN.toFormatString() + "10I"
        unpacked = struct.unpack_from(headerFormat, array_of_bytes, offset)

        return Elf32SectionHeaderEntry(*unpacked)


class Elf32SectionHeaders:
    def __init__(self, array_of_bytes: bytes, shoff: int, shnum: int) -> None:
        self.sections: list[Elf32SectionHeaderEntry] = list()
        self.shoff: int = shoff
        self.shnum: int = shnum

        self.mipsText: Elf32SectionHeaderEntry | None = None
        self.mipsData: Elf32SectionHeaderEntry | None = None

        for i in range(shnum):
            sectionHeaderEntry = Elf32SectionHeaderEntry.fromBytearray(array_of_bytes, shoff + i * 0x28)
            self.sections.append(sectionHeaderEntry)
            # print(sectionHeaderEntry)

    def __getitem__(self, key: int) -> Elf32SectionHeaderEntry | None:
        if key == Elf32SectionHeaderNumber.UNDEF.value:
            return None
        if key == Elf32SectionHeaderNumber.COMMON.value:
            common.Utils.eprint("Warning: Elf32SectionHeaderNumber.COMMON not implemented\n")
            return None
        if key == Elf32SectionHeaderNumber.MIPS_ACOMMON.value:
            common.Utils.eprint("Warning: Elf32SectionHeaderNumber.MIPS_ACOMMON not implemented\n")
            return None
        if key == Elf32SectionHeaderNumber.MIPS_TEXT.value:
            return self.mipsText
        if key == Elf32SectionHeaderNumber.MIPS_DATA.value:
            return self.mipsData
        if key == Elf32SectionHeaderNumber.MIPS_SCOMMON.value:
            common.Utils.eprint("Warning: Elf32SectionHeaderNumber.MIPS_SCOMMON not implemented\n")
            return None
        if key == Elf32SectionHeaderNumber.MIPS_SUNDEFINED.value:
            common.Utils.eprint("Warning: Elf32SectionHeaderNumber.MIPS_SUNDEFINED not implemented\n")
            return None
        if key > len(self.sections):
            return None
        return self.sections[key]

    def __iter__(self) -> Generator[Elf32SectionHeaderEntry, None, None]:
        for entry in self.sections:
            yield entry

    def __len__(self) -> int:
        return len(self.sections)
