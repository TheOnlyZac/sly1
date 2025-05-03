#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

from typing import TextIO
from pathlib import Path

import rabbitizer

from .. import common

from . import sections
from . import symbols
from . import FunctionRodataEntry


def createSectionFromSplitEntry(splitEntry: common.FileSplitEntry, array_of_bytes: bytes, context: common.Context, vromStart: int = 0) -> sections.SectionBase:
    offsetStart = splitEntry.offset
    offsetEnd = splitEntry.nextOffset

    if offsetEnd == 0xFFFFFF:
        offsetEnd = len(array_of_bytes)

    if offsetStart >= 0 and offsetEnd >= 0:
        common.Utils.printVerbose(f"Parsing offset range [{offsetStart:02X}, {offsetEnd:02X}]")
    elif offsetEnd >= 0:
        common.Utils.printVerbose(f"Parsing until offset 0x{offsetEnd:02X}")
    elif offsetStart >= 0:
        common.Utils.printVerbose(f"Parsing since offset 0x{offsetStart:02X}")

    sectionStart = vromStart + offsetStart
    sectionEnd = vromStart + offsetEnd

    common.Utils.printVerbose(f"Using VRAM {splitEntry.vram:08X}")
    vram = splitEntry.vram

    f: sections.SectionBase
    if splitEntry.section == common.FileSectionType.Text:
        f = sections.SectionText(context, sectionStart, sectionEnd, vram, splitEntry.fileName, array_of_bytes, 0, None)
        if splitEntry.isRsp:
            f.instrCat = rabbitizer.InstrCategory.RSP
    elif splitEntry.section == common.FileSectionType.Data:
        f = sections.SectionData(context, sectionStart, sectionEnd, vram, splitEntry.fileName, array_of_bytes, 0, None)
    elif splitEntry.section == common.FileSectionType.Rodata:
        f = sections.SectionRodata(context, sectionStart, sectionEnd, vram, splitEntry.fileName, array_of_bytes, 0, None)
    elif splitEntry.section == common.FileSectionType.Bss:
        bssVramEnd = splitEntry.vram + offsetEnd - offsetStart
        f = sections.SectionBss(context, sectionStart, sectionEnd, splitEntry.vram, bssVramEnd, splitEntry.fileName, 0, None)
    elif splitEntry.section == common.FileSectionType.Reloc:
        f = sections.SectionRelocZ64(context, sectionStart, sectionEnd, vram, splitEntry.fileName, array_of_bytes, 0, None)
    else:
        common.Utils.eprint("Error! Section not set!")
        exit(-1)

    f.isHandwritten = splitEntry.isHandwritten

    return f

def writeSection(path: Path, fileSection: sections.SectionBase) -> Path:
    path.parent.mkdir(parents=True, exist_ok=True)
    fileSection.saveToFile(str(path))
    return path


#! @deprecated: Use the static methods from FunctionRodataEntry instead
def getRdataAndLateRodataForFunctionFromSection(func: symbols.SymbolFunction, rodataSection: sections.SectionRodata) -> tuple[list[symbols.SymbolBase], list[symbols.SymbolBase], int]:
    entry = FunctionRodataEntry.getEntryForFuncFromSection(func, rodataSection)

    lateRodataSize = 0
    for rodataSym in entry.lateRodataSyms:
        lateRodataSize += rodataSym.sizew

    return entry.rodataSyms, entry.lateRodataSyms, lateRodataSize

#! @deprecated: Use the static methods from FunctionRodataEntry instead
def getRdataAndLateRodataForFunction(func: symbols.SymbolFunction, rodataFileList: list[sections.SectionBase]) -> tuple[list[symbols.SymbolBase], list[symbols.SymbolBase], int]:
    entry = FunctionRodataEntry.getEntryForFuncFromPossibleRodataSections(func, rodataFileList)

    lateRodataSize = 0
    for rodataSym in entry.lateRodataSyms:
        lateRodataSize += rodataSym.sizew

    return entry.rodataSyms, entry.lateRodataSyms, lateRodataSize

#! @deprecated: Use the static methods from FunctionRodataEntry instead
def writeFunctionRodataToFile(f: TextIO, func: symbols.SymbolFunction, rdataList: list[symbols.SymbolBase], lateRodataList: list[symbols.SymbolBase], lateRodataSize: int=0) -> None:
    entry = FunctionRodataEntry(func, rdataList, lateRodataList)
    entry.writeToFile(f, writeFunction=False)

#! @deprecated: Use the static methods from FunctionRodataEntry instead
def writeSplitedFunction(path: Path, func: symbols.SymbolFunction, rodataFileList: list[sections.SectionBase]) -> None:
    path.mkdir(parents=True, exist_ok=True)
    entry = FunctionRodataEntry.getEntryForFuncFromPossibleRodataSections(func, rodataFileList)

    funcPath = path / (func.getName()+ ".s")
    with funcPath.open("w") as f:
        entry.writeToFile(f, writeFunction=True)

def writeOtherRodata(path: Path, rodataFileList: list[sections.SectionBase]) -> None:
    for rodataSection in rodataFileList:
        assert isinstance(rodataSection, sections.SectionRodata)

        rodataPath = path / rodataSection.name
        rodataPath.mkdir(parents=True, exist_ok=True)

        for rodataSym in rodataSection.symbolList:
            if rodataSym.shouldMigrate():
                continue

            rodataSymbolPath = rodataPath / (rodataSym.getName() + ".s")
            common.Utils.printVerbose(f"Writing unmigrated rodata {rodataSymbolPath}")

            with rodataSymbolPath.open("w") as f:
                f.write(".section .rodata" + common.GlobalConfig.LINE_ENDS)
                f.write(rodataSym.disassemble(migrate=True))


def writeMigratedFunctionsList(processedSegments: dict[common.FileSectionType, list[sections.SectionBase]], functionMigrationPath: Path, name: str) -> None:
    funcAndRodataOrderPath = functionMigrationPath / f"{name}_migrated_functions.txt"

    rodataSymbols: list[tuple[symbols.SymbolBase, symbols.SymbolFunction|None]] = []
    for section in processedSegments.get(common.FileSectionType.Rodata, []):
        for sym in section.symbolList:
            rodataSymbols.append((sym, None))
    rodataSymbolsVrams = {sym.vram for sym, _ in rodataSymbols}

    funcs: list[symbols.SymbolFunction] = []
    for section in processedSegments.get(common.FileSectionType.Text, []):
        for func in section.symbolList:
            assert isinstance(func, symbols.SymbolFunction)
            funcs.append(func)

            referencedRodata = rodataSymbolsVrams & func.instrAnalyzer.referencedVrams
            for i in range(len(rodataSymbols)):
                if len(referencedRodata) == 0:
                    break

                rodataSym, funcReferencingThisSym = rodataSymbols[i]

                if rodataSym.vram not in referencedRodata:
                    continue

                referencedRodata.remove(rodataSym.vram)

                if funcReferencingThisSym is not None:
                    # This rodata sym already has a corresponding function associated
                    continue

                rodataSymbols[i] = (rodataSym, func)

    resultingList: list[symbols.SymbolBase] = []
    alreadyAddedFuncs: set[symbols.SymbolFunction] = set()

    lastFunc = None
    for rodataSym, funcReferencingThisSym in rodataSymbols:
        if funcReferencingThisSym is None:
            resultingList.append(rodataSym)
        elif funcReferencingThisSym not in alreadyAddedFuncs:
            alreadyAddedFuncs.add(funcReferencingThisSym)
            lastFunc = funcReferencingThisSym

            for func in funcs:
                if func.vram >= funcReferencingThisSym.vram:
                    break
                if func in alreadyAddedFuncs:
                    continue

                alreadyAddedFuncs.add(func)
                resultingList.append(func)
            resultingList.append(funcReferencingThisSym)

    if lastFunc is None:
        for func in funcs:
            resultingList.append(func)
    else:
        for func in funcs:
            if func.vram <= lastFunc.vram:
                continue
            resultingList.append(func)

    with funcAndRodataOrderPath.open("w") as f:
        for sym in resultingList:
            f.write(sym.getName() + "\n")
