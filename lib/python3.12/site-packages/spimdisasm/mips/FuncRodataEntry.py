#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2023-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

from typing import Generator, TextIO

from collections import deque
import dataclasses

from .. import common

from . import sections
from . import symbols


@dataclasses.dataclass
class FunctionRodataEntry:
    """
    Class to facilitate rodata migration.

    The algorithm aims to pair zero or more migrable rodata symbols from a
    rodata section to a function.

    This class assumes at least one of the following is true for any given
    instance:
    - `FunctionRodataEntry.function` is not `None`.
    - `FunctionRodataEntry.rodataSyms` has at least one element.

    If `FunctionRodataEntry.lateRodataSyms` has elements then
    `FunctionRodataEntry.function` is not `None`.

    The recommended way to instance this class is by using
    `FunctionRodataEntry.getAllEntriesFromSections`.
    """

    function: symbols.SymbolFunction | None = None
    rodataSyms: list[symbols.SymbolBase] = dataclasses.field(default_factory=list)
    lateRodataSyms: list[symbols.SymbolBase] = dataclasses.field(default_factory=list)
    sectionText: str = ".text"
    sectionRodata: str = ".rodata"
    sectionLateRodata: str = ".late_rodata"

    def hasRodataSyms(self) -> bool:
        return len(self.rodataSyms) > 0 or len(self.lateRodataSyms) > 0

    def iterRodataSyms(self) -> Generator[symbols.SymbolBase, None, None]:
        for sym in self.rodataSyms:
            yield sym
        for sym in self.lateRodataSyms:
            yield sym

    def writeToFile(self, f: TextIO, writeFunction: bool=True) -> None:
        # Sadly, we have some logic that may affect disassembling other symbols
        # on the "function"'s disassembly function, like setting the rom address
        # of jumptable labels. Having this info may affect the name they get
        # disassembled as.
        # To avoid this issue, we disassemble the function first without writing
        # it to the file.
        disassembledFunction: str|None = None
        if self.function is not None:
            disassembledFunction = self.function.disassemble(migrate=self.hasRodataSyms(), isSplittedSymbol=True)

        if len(self.rodataSyms) > 0:
            # Write the rdata
            f.write(f".section {self.sectionRodata}{common.GlobalConfig.LINE_ENDS}")
            for sym in self.rodataSyms:
                f.write(sym.disassemble(migrate=True, useGlobalLabel=True, isSplittedSymbol=True))
                f.write(common.GlobalConfig.LINE_ENDS)

        if len(self.lateRodataSyms) > 0:
            assert self.function is not None
            # Write the late_rodata
            f.write(f".section {self.sectionLateRodata}{common.GlobalConfig.LINE_ENDS}")

            lateRodataSize = 0
            for sym in self.lateRodataSyms:
                lateRodataSize += sym.sizew

            if lateRodataSize / len(self.function.instructions) > 1/3:
                align = 4
                firstLateRodataVram = self.lateRodataSyms[0].vram
                if firstLateRodataVram is not None and firstLateRodataVram % 8 == 0:
                    align = 8
                f.write(f".late_rodata_alignment {align}{common.GlobalConfig.LINE_ENDS}")
            for sym in self.lateRodataSyms:
                f.write(sym.disassemble(migrate=True, useGlobalLabel=True, isSplittedSymbol=True))
                f.write(common.GlobalConfig.LINE_ENDS)

        if disassembledFunction is not None:
            if len(self.rodataSyms) > 0 or len(self.lateRodataSyms) > 0:
                f.write(f"{common.GlobalConfig.LINE_ENDS}.section {self.sectionText}{common.GlobalConfig.LINE_ENDS}")

            if writeFunction:
                # Write the function itself
                f.write(disassembledFunction)

    def getName(self) -> str:
        assert self.function is not None or self.hasRodataSyms()

        if self.function is not None:
            return self.function.getName()

        rodataSymsLen = len(self.rodataSyms)
        if rodataSymsLen > 0:
            assert rodataSymsLen == 1, rodataSymsLen
            return self.rodataSyms[0].getName()

        lateRodataSyms = len(self.lateRodataSyms)
        assert lateRodataSyms == 1, lateRodataSyms
        return self.lateRodataSyms[0].getName()



    @staticmethod
    def _shouldMigrateRodataSymbolToFunction(rodataSym: symbols.SymbolBase, intersection: set[int], funcName: str, already_migrated_syms: set[int]) -> bool:
        if rodataSym.vram in already_migrated_syms:
            return False

        functionOwner = rodataSym.contextSym.functionOwnerForMigration
        if functionOwner is not None:
            # If a function owner was specified for this symbol then it is only
            # allowed to be migrated to that function and none other
            if functionOwner == funcName:
                return True
            return False

        if rodataSym.vram not in intersection:
            return False

        if not rodataSym.shouldMigrate():
            return False

        return True

    @staticmethod
    def _updateMigrableSymbolsSets(rodataSym: symbols.SymbolBase, intersection: set[int], funcName: str, migrableRodataSyms: set[int], maybeMigrableRodataSyms: set[int], rodataMigratedSomewhereElse: bool, already_migrated_syms: set[int]) -> bool:
        # We try to decide which symbols should be migrated by checking from left
        # to right.
        # Completely unreferenced symbols may get migrated to the current
        # function if they are between two symbols that do get migrated to this
        # function.
        # This is acomplished by keeping a second set of tentative symbols to
        # migrate (`maybeMigrableRodataSyms`) which gets added to the main set
        # when we see the next migrable symbol.

        if rodataMigratedSomewhereElse:
            return rodataMigratedSomewhereElse

        if FunctionRodataEntry._shouldMigrateRodataSymbolToFunction(rodataSym, intersection, funcName, already_migrated_syms):
            migrableRodataSyms.add(rodataSym.vram)

            migrableRodataSyms.update(maybeMigrableRodataSyms)
            maybeMigrableRodataSyms.clear()
        elif len(migrableRodataSyms) > 0:
            if len(rodataSym.contextSym.referenceSymbols) > 0 or len(rodataSym.contextSym.referenceFunctions) > 0:
                rodataMigratedSomewhereElse = True
            elif rodataSym.shouldMigrate():
                if rodataSym.vram in already_migrated_syms:
                    rodataMigratedSomewhereElse = True
                else:
                    maybeMigrableRodataSyms.add(rodataSym.vram)
            else:
                rodataMigratedSomewhereElse = True

        return rodataMigratedSomewhereElse

    @staticmethod
    def getEntryForFuncFromSection(func: symbols.SymbolFunction, rodataSection: sections.SectionRodata|None, already_migrated_syms: set[int]=set()) -> FunctionRodataEntry:
        """
        Pairs the given function to the migrable rodata symbols of the given
        rodata section.

        If `rodataSection` is `None` or if the function does not reference any
        of the symbols from the given `rodataSection` then a
        `FunctionRodataEntry` containing the given function.
        """

        if rodataSection is None:
            return FunctionRodataEntry(func)

        rodataList: list[symbols.SymbolBase] = []
        lateRodataList: list[symbols.SymbolBase] = []

        intersection = func.instrAnalyzer.referencedVrams & rodataSection.symbolsVRams

        funcName = func.getName()

        migrableRodataSyms: set[int] = set()
        migrableLateRodataSyms: set[int] = set()
        maybeMigrableRodataSyms: set[int] = set()
        maybeMigrableLateRodataSyms: set[int] = set()
        rodataMigratedSomewhereElse: bool = False
        lateRodataMigratedSomewhereElse: bool = False
        for rodataSym in rodataSection.symbolList:
            if rodataMigratedSomewhereElse:
                if not common.GlobalConfig.COMPILER.value.hasLateRodata:
                    break
                if lateRodataMigratedSomewhereElse:
                    break

            if rodataSym.contextSym.isLateRodata():
                lateRodataMigratedSomewhereElse = FunctionRodataEntry._updateMigrableSymbolsSets(rodataSym, intersection, funcName, migrableLateRodataSyms, maybeMigrableLateRodataSyms, lateRodataMigratedSomewhereElse, already_migrated_syms)
            else:
                rodataMigratedSomewhereElse = FunctionRodataEntry._updateMigrableSymbolsSets(rodataSym, intersection, funcName, migrableRodataSyms, maybeMigrableRodataSyms, rodataMigratedSomewhereElse, already_migrated_syms)

        for rodataSym in rodataSection.symbolList:
            if rodataSym.vram in migrableLateRodataSyms:
                lateRodataList.append(rodataSym)
            elif rodataSym.vram in migrableRodataSyms:
                rodataList.append(rodataSym)

        return FunctionRodataEntry(func, rodataList, lateRodataList)

    @staticmethod
    def getEntryForFuncFromPossibleRodataSections(func: symbols.SymbolFunction, rodataFileList: list[sections.SectionBase]) -> FunctionRodataEntry:
        """
        Searches and try to pair migrable rodata symbols to the given function.

        If no migrable rodata symbols are found then a `FunctionRodataEntry`
        containing only the passed function will be returned.
        """

        for rodataSection in rodataFileList:
            assert isinstance(rodataSection, sections.SectionRodata)

            entry = FunctionRodataEntry.getEntryForFuncFromSection(func, rodataSection)
            if entry.hasRodataSyms():
                return entry

        return FunctionRodataEntry(func)

    @staticmethod
    def getAllEntriesFromSections(textSection: sections.SectionText|None, rodataSection: sections.SectionRodata|None) -> list[FunctionRodataEntry]:
        """
        Return all functions to rodata symbols pairings from the given
        sections.

        The returned list preserves original ordering of both the text and
        rodata sections.

        Either a function or a rodata symbol may be orphaned. This means the
        said symbol is paired to zero symbols of the other section. In these
        cases an entry containing the specific symbol is created and inserted
        in corresponding place of the list so it preserves the ordering of both
        sections.
        """

        # The simplest way to know which symbols has not been migrated yet and
        # preserve order at the same time seem to be just keeping a list of the
        # symbols and remove the ones that have been handled somehow (either by
        # migrating to a function or adding an no-function entry for the given
        # symbol).
        # We use deque instead of a plain list because we want fast removal of
        # the first symbol.
        remainingRodataSymbols = deque(rodataSection.symbolList if rodataSection is not None else [])
        handledSymbols: set[int] = set()

        allEntries: list[FunctionRodataEntry] = []

        textSymbols = textSection.symbolList if textSection is not None else []
        for func in textSymbols:
            assert isinstance(func, symbols.SymbolFunction)

            entry = FunctionRodataEntry.getEntryForFuncFromSection(func, rodataSection, handledSymbols)

            for sym in entry.iterRodataSyms():
                handledSymbols.add(sym.vram)

            # Preserve the order of rodata symbols by looking for symbols that has not been migrated yet
            if len(entry.rodataSyms) > 0:
                firstFuncRodataSym = entry.rodataSyms[0]

                while len(remainingRodataSymbols) > 0:
                    rodataSym = remainingRodataSymbols[0]

                    if rodataSym.vram in handledSymbols:
                        # Drop migrated symbols
                        remainingRodataSymbols.popleft()
                        continue

                    if rodataSym.vram >= firstFuncRodataSym.vram:
                        # Take all the symbols up to symbols referenced by the current function
                        break

                    allEntries.append(FunctionRodataEntry(rodataSyms=[rodataSym]))
                    handledSymbols.add(rodataSym.vram)
                    remainingRodataSymbols.popleft()

            allEntries.append(entry)

        # Check if there's any rodata symbol remaining and add it to the list
        for rodataSym in remainingRodataSymbols:
            if rodataSym.vram not in handledSymbols:
                allEntries.append(FunctionRodataEntry(rodataSyms=[rodataSym]))

        return allEntries
