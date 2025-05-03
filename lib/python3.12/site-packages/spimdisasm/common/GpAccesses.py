#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

import dataclasses

from .. import common

from .SortedDict import SortedDict


class GlobalOffsetTable:
    def __init__(self) -> None:
        self.localsTable: list[int] = list()
        self.globalsTable: list[int] = list()

        self.tableAddress: int|None = None


    def initTables(self, pltGot: int, localsTable: list[int], globalsTable: list[int]) -> None:
        self.tableAddress = pltGot
        self.localsTable = [address for address in localsTable]
        self.globalsTable = [address for address in globalsTable]


    def getGotSymEntry(self, address: int) -> tuple[int|None, bool|None]:
        if self.tableAddress is None:
            return None, None

        index = (address - self.tableAddress) // 4

        if index < 0:
            common.Utils.eprint(f"Warning: %got address 0x{address:X} not found on local or global table (negative index)")
            common.Utils.eprint(f"    index: {index}, len(localsTable):{len(self.localsTable)}, len(globalsTable): {len(self.globalsTable)}")
            return None, None

        if index < len(self.localsTable):
            return self.localsTable[index], False

        index -= len(self.localsTable)
        if index >= len(self.globalsTable):
            common.Utils.eprint(f"Warning: %got address 0x{address:X} not found on local or global table (out of range)")
            common.Utils.eprint(f"    index: {index}, len(globalsTable): {len(self.globalsTable)}")
            return None, None
        return self.globalsTable[index], True


@dataclasses.dataclass
class SmallSection:
    address: int
    size: int

    def isInRange(self, address: int) -> bool:
        return self.address <= address < self.address + self.size


@dataclasses.dataclass
class GpAccess:
    address: int

    isGotLocal: bool = False
    isGotGlobal: bool = False
    isSmallSection: bool = False

    @property
    def isGot(self) -> bool:
        return self.isGotLocal or self.isGotGlobal


class GpAccessContainer:
    def __init__(self) -> None:
        self.got = GlobalOffsetTable()
        self.smallSections: SortedDict[SmallSection] = SortedDict()

    def addSmallSection(self, address: int, size: int) -> None:
        self.smallSections[address] = SmallSection(address, size)

    def initGotTable(self, tableAddress: int, localsTable: list[int], globalsTable: list[int]) -> None:
        self.got.initTables(tableAddress, localsTable, globalsTable)

        self.addSmallSection(tableAddress, (len(localsTable) + len(globalsTable)) * 4)

    def requestAddress(self, address: int) -> GpAccess|None:
        small = self.smallSections.getKeyRight(address)
        if small is None:
            common.Utils.eprint(f"Warning: No section found for $gp access at address 0x{address:08X}")
            return None

        sectionAddr, sectionData = small

        if sectionAddr != self.got.tableAddress:
            if not sectionData.isInRange(address):
                common.Utils.eprint(f"Warning: No section found for $gp access at address 0x{address:08X}")
                return None

            # small section
            access = GpAccess(address)
            access.isSmallSection = True
            return access

        # got
        gotEntry, inGlobalTable = self.got.getGotSymEntry(address)

        if gotEntry is None or inGlobalTable is None:
            return None

        access = GpAccess(gotEntry)
        access.isGotGlobal = inGlobalTable
        access.isGotLocal = not inGlobalTable

        return access
