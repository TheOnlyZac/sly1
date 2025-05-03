#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
from pathlib import Path
from typing import Callable

import spimdisasm
import rabbitizer

from .. import common
from .. import mips

from .. import __version__


ProgressCallbackType = Callable[[int, str, int], None]


_sLenLastLine = 80


def getSplittedSections(context: common.Context, splits: common.FileSplitFormat, array_of_bytes: bytes, inputPath: Path, textOutput: Path, dataOutput: Path) -> tuple[dict[common.FileSectionType, list[mips.sections.SectionBase]], dict[common.FileSectionType, list[Path]]]:
    processedFiles: dict[common.FileSectionType, list[mips.sections.SectionBase]] = {
        common.FileSectionType.Text: [],
        common.FileSectionType.Data: [],
        common.FileSectionType.Rodata: [],
        common.FileSectionType.Bss: [],
    }
    processedFilesOutputPaths: dict[common.FileSectionType, list[Path]] = {k: [] for k in processedFiles}

    for row in splits:
        if row.section == common.FileSectionType.Text:
            outputPath = textOutput
        elif row.section == common.FileSectionType.Data:
            outputPath = dataOutput
        elif row.section == common.FileSectionType.Rodata:
            outputPath = dataOutput
        elif row.section == common.FileSectionType.Bss:
            outputPath = dataOutput
        elif row.section == common.FileSectionType.Reloc:
            outputPath = dataOutput
        elif row.section == common.FileSectionType.Dummy:
            # Ignore dummy sections
            continue
        else:
            common.Utils.eprint("Error! Section not set!")
            exit(1)

        outputFilePath = outputPath
        if str(outputPath) != "-":
            fileName = row.fileName
            if row.fileName == "":
                fileName = f"{inputPath.stem}_{row.vram:08X}"

            outputFilePath = outputPath / fileName

        common.Utils.printVerbose(f"Reading '{row.fileName}'")
        f = mips.FilesHandlers.createSectionFromSplitEntry(row, array_of_bytes, context)
        f.setCommentOffset(row.offset)
        processedFiles[row.section].append(f)
        processedFilesOutputPaths[row.section].append(outputFilePath)

    return processedFiles, processedFilesOutputPaths


gInstrCategoriesNameMap = {
    "cpu": rabbitizer.InstrCategory.CPU,
    "rsp": rabbitizer.InstrCategory.RSP,
    "r3000gte": rabbitizer.InstrCategory.R3000GTE,
    "r4000allegrex": rabbitizer.InstrCategory.R4000ALLEGREX,
    "r5900": rabbitizer.InstrCategory.R5900,
}

def getInstrCategoryFromStr(category: str|None) -> rabbitizer.Enum:
    # TODO: consider moving this logic to rabbitizer
    if category is None:
        category = "cpu"
    return gInstrCategoriesNameMap.get(category.lower(), rabbitizer.InstrCategory.CPU)


def configureProcessedFiles(processedFiles: dict[common.FileSectionType, list[mips.sections.SectionBase]], category: str|None) -> None:
    instrCat = getInstrCategoryFromStr(category)

    for textFile in processedFiles.get(common.FileSectionType.Text, []):
        assert isinstance(textFile, mips.sections.SectionText)

        textFile.instrCat = instrCat


def analyzeProcessedFiles(processedFiles: dict[common.FileSectionType, list[mips.sections.SectionBase]], processedFilesOutputPaths: dict[common.FileSectionType, list[Path]], processedFilesCount: int, progressCallback: ProgressCallbackType|None=None) -> None:
    i = 0
    for sectionType, filesInSection in sorted(processedFiles.items()):
        pathLists = processedFilesOutputPaths[sectionType]
        for fileIndex, f in enumerate(filesInSection):
            if progressCallback is not None:
                filePath = pathLists[fileIndex]
                progressCallback(i, str(filePath), processedFilesCount)
            f.analyze()
            f.printAnalyzisResults()

            i += 1
    return

def progressCallback_analyzeProcessedFiles(i: int, filePath: str, processedFilesCount: int) -> None:
    global _sLenLastLine

    common.Utils.printQuietless(_sLenLastLine*" " + "\r", end="")
    progressStr = f"Analyzing: {i/processedFilesCount:%}. File: {filePath}\r"
    _sLenLastLine = max(len(progressStr), _sLenLastLine)
    common.Utils.printQuietless(progressStr, end="", flush=True)
    common.Utils.printVerbose("")


def nukePointers(processedFiles: dict[common.FileSectionType, list[mips.sections.SectionBase]], processedFilesOutputPaths: dict[common.FileSectionType, list[Path]], processedFilesCount: int, progressCallback: ProgressCallbackType|None=None) -> None:
    i = 0
    for sectionType, filesInSection in processedFiles.items():
        pathLists = processedFilesOutputPaths[sectionType]
        for fileIndex, f in enumerate(filesInSection):
            if progressCallback is not None:
                filePath = pathLists[fileIndex]
                progressCallback(i, str(filePath), processedFilesCount)
            f.removePointers()
            i += 1
    return

def progressCallback_nukePointers(i: int, filePath: str, processedFilesCount: int) -> None:
    global _sLenLastLine

    common.Utils.printVerbose(f"Nuking pointers of {filePath}")
    common.Utils.printQuietless(_sLenLastLine*" " + "\r", end="")
    progressStr = f" Nuking pointers: {i/processedFilesCount:%}. File: {filePath}\r"
    _sLenLastLine = max(len(progressStr), _sLenLastLine)
    common.Utils.printQuietless(progressStr, end="")


def writeProcessedFiles(processedFiles: dict[common.FileSectionType, list[mips.sections.SectionBase]], processedFilesOutputPaths: dict[common.FileSectionType, list[Path]], processedFilesCount: int, progressCallback: ProgressCallbackType|None=None) -> None:
    common.Utils.printVerbose("Writing files...")
    i = 0
    for section, filesInSection in processedFiles.items():
        pathLists = processedFilesOutputPaths[section]
        for fileIndex, f in enumerate(filesInSection):
            filePath = pathLists[fileIndex]
            if progressCallback is not None:
                progressCallback(i, str(filePath), processedFilesCount)

            common.Utils.printVerbose(f"Writing {filePath}")
            mips.FilesHandlers.writeSection(filePath, f)
            i += 1
    return

def progressCallback_writeProcessedFiles(i: int, filePath: str, processedFilesCount: int) -> None:
    global _sLenLastLine

    common.Utils.printVerbose(f"Writing {filePath}")
    common.Utils.printQuietless(_sLenLastLine*" " + "\r", end="")
    progressStr = f"Writing: {i/processedFilesCount:%}. File: {filePath}\r"
    _sLenLastLine = max(len(progressStr), _sLenLastLine)
    common.Utils.printQuietless(progressStr, end="")

    if str(filePath) == "-":
        common.Utils.printQuietless()


def migrateFunctions(processedFiles: dict[common.FileSectionType, list[mips.sections.SectionBase]], functionMigrationPath: Path, progressCallback: ProgressCallbackType|None=None) -> None:
    funcTotal = sum(len(x.symbolList) for x in processedFiles.get(common.FileSectionType.Text, []))
    rodataFileList = processedFiles.get(common.FileSectionType.Rodata, [])

    remainingRodataSyms: list[mips.symbols.SymbolBase] = []
    rodataSectionNamesMapping: dict[int, str] = dict()
    for x in rodataFileList:
        remainingRodataSyms.extend(x.symbolList)
        for y in x.symbolList:
            rodataSectionNamesMapping[y.vram] = x.getName()

    i = 0
    for textFile in processedFiles.get(common.FileSectionType.Text, []):
        filePath = functionMigrationPath / textFile.getName()
        filePath.mkdir(parents=True, exist_ok=True)
        for func in textFile.symbolList:
            if progressCallback is not None:
                progressCallback(i, func.getName(), funcTotal)

            assert isinstance(func, mips.symbols.SymbolFunction)
            entry = mips.FunctionRodataEntry.getEntryForFuncFromPossibleRodataSections(func, rodataFileList)

            for sym in entry.iterRodataSyms():
                if sym in remainingRodataSyms:
                    remainingRodataSyms.remove(sym)

            funcPath = filePath / (func.getName()+ ".s")
            common.Utils.printVerbose(f"Writing function {funcPath}")
            with funcPath.open("w") as f:
                entry.writeToFile(f, writeFunction=True)

            i += 1

    for rodataSym in remainingRodataSyms:
        rodataPath = functionMigrationPath / rodataSectionNamesMapping[rodataSym.vram]
        rodataPath.mkdir(parents=True, exist_ok=True)
        rodataSymbolPath = rodataPath / f"{rodataSym.getName()}.s"
        common.Utils.printVerbose(f"Writing unmigrated rodata {rodataSymbolPath}")
        with rodataSymbolPath.open("w") as f:
            f.write(".section .rodata" + common.GlobalConfig.LINE_ENDS)
            f.write(rodataSym.disassemble(migrate=True))


def progressCallback_migrateFunctions(i: int, funcName: str, funcTotal: int) -> None:
    global _sLenLastLine

    common.Utils.printVerbose(f"Spliting {funcName}", end="")
    common.Utils.printQuietless(_sLenLastLine*" " + "\r", end="")
    common.Utils.printVerbose()
    progressStr = f" Writing: {i/funcTotal:%}. Function: {funcName}\r"
    _sLenLastLine = max(len(progressStr), _sLenLastLine)
    common.Utils.printQuietless(progressStr, end="")


def writeFunctionInfoCsv(processedFiles: dict[common.FileSectionType, list[mips.sections.SectionBase]], csvPath: Path) -> None:
    csvPath.parent.mkdir(parents=True, exist_ok=True)

    with csvPath.open("w") as f:
        f.write("vrom,address,name,file,length,hash of top bits of words,functions called by this function,non-jal function calls,referenced functions\n")
        for textFile in processedFiles.get(common.FileSectionType.Text, []):
            for func in textFile.symbolList:
                assert isinstance(func, mips.symbols.SymbolFunction)
                f.write(f"0x{func.vromStart:06X},0x{func.vram:08X},{func.getName()},{textFile.getName()},0x{func.sizew*4:X},")

                bitswordlist = []
                for instr in func.instructions:
                    topbits = instr.getRaw() & 0xFC000000

                    bitswordlist.append(topbits)
                bitbytelist = common.Utils.endianessWordsToBytes(common.Utils.InputEndian.BIG, bitswordlist)

                f.write(common.Utils.getStrHash(bitbytelist))
                f.write(",")

                calledFuncs = []
                for instrOffset, targetVram in func.instrAnalyzer.funcCallInstrOffsets.items():
                    funcSym = func.getSymbol(targetVram, tryPlusOffset=False)
                    if funcSym is None:
                        continue

                    calledFuncs.append(funcSym.getName())
                f.write("[" + ";".join(calledFuncs) + "]")
                f.write(",")

                nonJalCalls = []
                for loOffset, targetVram in func.instrAnalyzer.indirectFunctionCallOffsets.items():
                    funcSym = func.getSymbol(targetVram, tryPlusOffset=False)
                    if funcSym is None:
                        continue

                    nonJalCalls.append(funcSym.getName())
                f.write("[" + ";".join(nonJalCalls) + "]")
                f.write(",")

                referencedFunctions = []
                for loOffset, symVram in func.instrAnalyzer.symbolLoInstrOffset.items():
                    funcSym = func.getSymbol(symVram, tryPlusOffset=False)
                    if funcSym is None:
                        continue

                    if funcSym.getTypeSpecial() != common.SymbolSpecialType.function:
                        continue

                    referencedFunctions.append(funcSym.getName())
                f.write("[" + ";".join(referencedFunctions) + "]")

                f.write("\n")

            # For adding new lines at the end of each file
            # f.write("\n")


def cliMain() -> int:
    parser = argparse.ArgumentParser(description="Interface to call any of the spimdisasm's CLI utilities", prog="spimdisasm")

    parser.add_argument("-V", "--version", action="version", version=f"%(prog)s {__version__}")

    subparsers = parser.add_subparsers(description="action", help="The CLI utility to run", required=True)

    spimdisasm.disasmdis.addSubparser(subparsers)
    spimdisasm.singleFileDisasm.addSubparser(subparsers)
    spimdisasm.elfObjDisasm.addSubparser(subparsers)
    spimdisasm.rspDisasm.addSubparser(subparsers)

    args = parser.parse_args()
    return int(args.func(args))
