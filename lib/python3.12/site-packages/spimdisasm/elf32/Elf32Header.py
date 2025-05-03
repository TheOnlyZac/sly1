#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

import dataclasses
import struct

from .Elf32Constants import Elf32HeaderIdentifier


@dataclasses.dataclass
class Elf32Identifier:
    ident:      list[int]  # 16 bytes  # 0x00
                                       # 0x10

    def checkMagic(self) -> bool:
        if self.ident[0] != 0x7F:
            return False
        if self.ident[1] != 0x45: # 'E'
            return False
        if self.ident[2] != 0x4C: # 'L'
            return False
        if self.ident[3] != 0x46: # 'F'
            return False
        return True

    def getFileClass(self) -> Elf32HeaderIdentifier.FileClass:
        return Elf32HeaderIdentifier.FileClass(self.ident[4])

    def getDataEncoding(self) -> Elf32HeaderIdentifier.DataEncoding:
        return Elf32HeaderIdentifier.DataEncoding(self.ident[5])

    def getVersion(self) -> int:
        return self.ident[6]

    def getOsAbi(self) -> Elf32HeaderIdentifier.OsAbi:
        return Elf32HeaderIdentifier.OsAbi(self.ident[7])

    def getAbiVersion(self) -> int:
        return self.ident[8]

    # should always return 0
    def getPad(self) -> int:
        return self.ident[9]


    @staticmethod
    def fromBytearray(array_of_bytes: bytes, offset: int = 0) -> Elf32Identifier:
        identFormat = "16B"
        ident = list(struct.unpack_from(identFormat, array_of_bytes, 0 + offset))

        identifier = Elf32Identifier(ident)

        if not identifier.checkMagic():
            # TODO: consider making my own exceptions
            raise RuntimeError("Not an ELF file: wrong magic")

        if identifier.getFileClass() != Elf32HeaderIdentifier.FileClass.CLASS32:
            raise RuntimeError(f"Unsupported ELF file class: {identifier.getFileClass()} (expected CLASS32)")

        assert identifier.getPad() == 0

        return identifier

    @staticmethod
    def structSize() -> int:
        return 0x10


# a.k.a. Ehdr (elf header)
@dataclasses.dataclass
class Elf32Header:
    ident:      Elf32Identifier # 16 bytes  # 0x00
    type:       int             # half      # 0x10
    machine:    int             # half      # 0x12
    version:    int             # word      # 0x14
    entry:      int             # address   # 0x18
    phoff:      int             # offset    # 0x1C
    shoff:      int             # offset    # 0x20
    flags:      int             # word      # 0x24
    ehsize:     int             # half      # 0x28
    phentsize:  int             # half      # 0x2A
    phnum:      int             # half      # 0x2C
    shentsize:  int             # half      # 0x2E
    shnum:      int             # half      # 0x30
    shstrndx:   int             # half      # 0x32
                                            # 0x34

    @staticmethod
    def fromBytearray(array_of_bytes: bytes, offset: int = 0) -> Elf32Header:
        identifier = Elf32Identifier.fromBytearray(array_of_bytes, offset)

        dataEncoding = identifier.getDataEncoding()
        if dataEncoding == Elf32HeaderIdentifier.DataEncoding.DATA2MSB:
            endianFormat = ">" # big
        elif dataEncoding == Elf32HeaderIdentifier.DataEncoding.DATA2LSB:
            endianFormat = "<" # little
        else:
            raise RuntimeError(f"Unsupported ELF data encoding: {dataEncoding}")

        headerFormat = endianFormat + "HHIIIIIHHHHHH"
        unpacked = struct.unpack_from(headerFormat, array_of_bytes, Elf32Identifier.structSize() + offset)
        # print(unpacked)

        return Elf32Header(identifier, *unpacked)

    @staticmethod
    def structSize() -> int:
        return 0x34
