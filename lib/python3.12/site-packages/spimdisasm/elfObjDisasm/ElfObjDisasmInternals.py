#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
from pathlib import Path
import rabbitizer

from .. import common
from .. import elf32
from .. import mips
from .. import frontendCommon as fec

from .. import __version__

PROGNAME = "elfObjDisasm"


def getToolDescription() -> str:
    return "Experimental MIPS elf disassembler"

def addOptionsToParser(parser: argparse.ArgumentParser) -> argparse.ArgumentParser:
    parser.add_argument("-V", "--version", action="version", version=f"%(prog)s {__version__}")

    parser.add_argument("binary", help="Path to input elf binary file")
    parser.add_argument("output", help="Path to output. Use '-' to print to stdout instead")

    parser.add_argument("--data-output", help="Path to output the data and rodata disassembly")

    parser.add_argument("--file-splits", help="Path to a file splits csv")

    parser.add_argument("--split-functions", help="Enables the function and rodata splitter. Expects a path to place the splited functions", metavar="PATH")

    parser.add_argument("--instr-category", help="The instruction category to use when disassembling every passed instruction. Defaults to 'cpu'", choices=["cpu", "rsp", "r3000gte", "r4000allegrex", "r5900"])

    parser.add_argument("--function-info", help="Specifies a path where to output a csvs sumary file of every analyzed function", metavar="PATH")


    readelfOptions = parser.add_argument_group("readelf-like flags")

    readelfOptions.add_argument("-a", "--all", help="Equivalent to --file-header --section-headers --syms --dyn-syms --relocs --display-got", action="store_true")
    readelfOptions.add_argument("--file-header", help="Display the ELF file header", action="store_true")
    readelfOptions.add_argument("-S", "--section-headers", help="Display the sections' header", action="store_true")
    readelfOptions.add_argument("-s", "--syms", help="Display the symbol table", action="store_true")
    readelfOptions.add_argument("--dyn-syms", help="Display the dynamic symbol table", action="store_true")
    readelfOptions.add_argument("-r", "--relocs", help="Display the relocations (if present)", action="store_true")
    readelfOptions.add_argument("--display-got", help="Shows Global offset table information", action="store_true")

    readelfOptions.add_argument("--readelf-only", help="Exit after processing the readelf-like flags, without performing any disassembly", action="store_true")


    common.Context.addParametersToArgParse(parser)

    common.GlobalConfig.addParametersToArgParse(parser)

    mips.InstructionConfig.addParametersToArgParse(parser)

    return parser

def getArgsParser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description=getToolDescription(), prog=PROGNAME, formatter_class=common.Utils.PreserveWhiteSpaceWrapRawTextHelpFormatter)
    return addOptionsToParser(parser)

def applyArgs(args: argparse.Namespace) -> None:
    if args.libultra_syms is None:
        args.libultra_syms = False
    if args.hardware_regs is None:
        args.hardware_regs = False
    common.GlobalConfig.parseArgs(args)
    mips.InstructionConfig.parseArgs(args)

def applyGlobalConfigurations() -> None:
    common.GlobalConfig.REMOVE_POINTERS = False
    common.GlobalConfig.IGNORE_BRANCHES = False
    common.GlobalConfig.SYMBOL_FINDER_FILTER_LOW_ADDRESSES = False

    common.GlobalConfig.ALLOW_UNKSEGMENT = False

    common.GlobalConfig.INPUT_FILE_TYPE = common.InputFileType.ELF


def applyReadelfLikeFlags(elfFile: elf32.Elf32File, args: argparse.Namespace) -> None:
    if args.all:
        elfFile.readelf_fileHeader()
        elfFile.readelf_sectionHeaders()
        elfFile.readelf_syms()
        elfFile.readelf_dyn_syms()
        elfFile.readelf_relocs()
        elfFile.readelf_displayGot()
    else:
        if args.file_header:
            elfFile.readelf_fileHeader()

        if args.section_headers:
            elfFile.readelf_sectionHeaders()

        if args.syms:
            elfFile.readelf_syms()

        if args.dyn_syms:
            elfFile.readelf_dyn_syms()

        if args.relocs:
            elfFile.readelf_relocs()

        if args.display_got:
            elfFile.readelf_displayGot()

    if args.readelf_only:
        exit(0)

SpecialSectionNames = {".text", ".data", ".rodata", ".bss"}

def getOutputPath(inputPath: Path, textOutput: Path, dataOutput: Path, sectionType: common.FileSectionType, sectionName: str) -> Path:
    outputPath = dataOutput
    if sectionType == common.FileSectionType.Text:
        outputPath = textOutput

    outputFilePath = outputPath
    if str(outputPath) != "-":
        outname = f"{inputPath.stem}"
        if sectionName not in SpecialSectionNames:
            outname += f"_{sectionName}"
        outputFilePath = outputFilePath / outname

    return outputFilePath

def processSection(
        context: common.Context, array_of_bytes: bytes,
        processedSections: dict[common.FileSectionType, list[mips.sections.SectionBase]],
        segmentPaths: dict[common.FileSectionType, list[Path]],
        sectionsPerName: dict[str, mips.sections.SectionBase],
        inputPath: Path, textOutput: Path, dataOutput: Path,
        sectionName: str, sectionEntry: elf32.Elf32SectionHeaderEntry,
        sectionType: common.FileSectionType,
        sectionClass: type[mips.sections.SectionText]|type[mips.sections.SectionData]|type[mips.sections.SectionRodata]|type[mips.sections.SectionBss]
    ) -> None:
    outputFilePath = getOutputPath(inputPath, textOutput, dataOutput, sectionType, sectionName)

    vromStart = sectionEntry.offset
    vromEnd = vromStart + sectionEntry.size
    vramStart = sectionEntry.addr
    if sectionEntry.addr == 0:
        vramStart = sectionEntry.offset

    mipsSection: mips.sections.SectionBase


    inname = f"{inputPath.stem}"
    if sectionName not in SpecialSectionNames:
        inname += f"_{sectionName}"

    if issubclass(sectionClass, mips.sections.SectionBss):
        bssStart = vramStart
        bssEnd = bssStart + sectionEntry.size
        mipsSection = sectionClass(context, vromStart, vromEnd, bssStart, bssEnd, inname, 0, None)
    else:
        mipsSection = sectionClass(context, vromStart, vromEnd, vramStart, inname, array_of_bytes, 0, None)

    mipsSection.setCommentOffset(vromStart)
    mipsSection.customSectionName = sectionName
    processedSections[sectionType].append(mipsSection)
    segmentPaths[sectionType].append(outputFilePath)
    sectionsPerName[sectionName] = mipsSection


def getProcessedSections(context: common.Context, elfFile: elf32.Elf32File, array_of_bytes: bytes, inputPath: Path, textOutput: Path, dataOutput: Path) -> tuple[dict[common.FileSectionType, list[mips.sections.SectionBase]], dict[common.FileSectionType, list[Path]], dict[str, mips.sections.SectionBase]]:
    processedSections: dict[common.FileSectionType, list[mips.sections.SectionBase]] = {
        common.FileSectionType.Text: [],
        common.FileSectionType.Data: [],
        common.FileSectionType.Rodata: [],
        common.FileSectionType.Bss: [],
    }
    segmentPaths: dict[common.FileSectionType, list[Path]] = {
        common.FileSectionType.Text: [],
        common.FileSectionType.Data: [],
        common.FileSectionType.Rodata: [],
        common.FileSectionType.Bss: [],
    }
    sectionsPerName: dict[str, mips.sections.SectionBase] = dict()

    for sectionName, sectionEntry in elfFile.progbitsExecute.items():
        processSection(context, array_of_bytes, processedSections, segmentPaths, sectionsPerName, inputPath, textOutput, dataOutput, sectionName, sectionEntry, common.FileSectionType.Text, mips.sections.SectionText)

    for sectionName, sectionEntry in elfFile.progbitsWrite.items():
        processSection(context, array_of_bytes, processedSections, segmentPaths, sectionsPerName, inputPath, textOutput, dataOutput, sectionName, sectionEntry, common.FileSectionType.Data, mips.sections.SectionData)

    for sectionName, sectionEntry in elfFile.progbitsNoWrite.items():
        processSection(context, array_of_bytes, processedSections, segmentPaths, sectionsPerName, inputPath, textOutput, dataOutput, sectionName, sectionEntry, common.FileSectionType.Rodata, mips.sections.SectionRodata)

    for sectionName, sectionEntry in elfFile.nobitsPerName.items():
        processSection(context, array_of_bytes, processedSections, segmentPaths, sectionsPerName, inputPath, textOutput, dataOutput, sectionName, sectionEntry, common.FileSectionType.Bss, mips.sections.SectionBss)

    return processedSections, segmentPaths, sectionsPerName

def changeGlobalSegmentRanges(context: common.Context, processedSegments: dict[common.FileSectionType, list[mips.sections.SectionBase]]) -> None:
    lowestVromStart: int|None = None
    highestVromEnd: int|None = None
    lowestVramStart: int|None = None
    highestVramEnd: int|None = None

    for subSegment in processedSegments.values():
        for section in subSegment:
            if lowestVromStart is None or section.vromStart < lowestVromStart:
                lowestVromStart = section.vromStart
            if highestVromEnd is None or section.vromEnd > highestVromEnd:
                highestVromEnd = section.vromEnd
            if lowestVramStart is None or section.vram < lowestVramStart:
                lowestVramStart = section.vram
            if highestVramEnd is None or section.vramEnd > highestVramEnd:
                highestVramEnd = section.vramEnd

    if lowestVromStart is None:
        lowestVromStart = 0x0
    if highestVromEnd is None:
        highestVromEnd = 0xFFFFFFFF
    if lowestVramStart is None:
        lowestVramStart = 0x0
    if highestVramEnd is None:
        highestVramEnd = 0xFFFFFFFF
    context.changeGlobalSegmentRanges(lowestVromStart, highestVromEnd, lowestVramStart, highestVramEnd)
    return


def addContextSymFromSymEntry(context: common.Context, symEntry: elf32.Elf32SymEntry, symAddress: int, symName: str|None=None, symVrom: int|None=None) -> common.ContextSymbol|None:
    if symAddress == 0:
        return None

    segment = context.globalSegment
    if not segment.isVramInRange(symAddress):
        segment = context.unknownSegment

    if symEntry.stType == elf32.Elf32SymbolTableType.FUNC.value:
        segment = context.globalSegment
        contextSym = segment.addFunction(symAddress, vromAddress=symVrom)
    elif symEntry.stType == elf32.Elf32SymbolTableType.OBJECT.value:
        contextSym = segment.addSymbol(symAddress, vromAddress=symVrom)
    elif symEntry.stType == elf32.Elf32SymbolTableType.SECTION.value:
        # print(symEntry)
        return None
    elif symEntry.stType == elf32.Elf32SymbolTableType.NOTYPE.value:
        if symEntry.shndx == elf32.Elf32SectionHeaderNumber.ABS.value:
            segment = context.globalSegment
            contextSym = segment.addSymbol(symAddress, vromAddress=symVrom)
            contextSym.isElfNotype = True
        else:
            bind = elf32.Elf32SymbolTableBinding.fromValue(symEntry.stBind)
            if bind != elf32.Elf32SymbolTableBinding.LOCAL:
                common.Utils.eprint(f"Warning: Non-LOCAL ({bind}) NOTYPE symbol '{symName}' has an unhandled shndx value: '0x{symEntry.shndx:X}'")
            contextSym = segment.addSymbol(symAddress, vromAddress=symVrom)
    else:
        common.Utils.eprint(f"Warning: symbol '{symName}' has an unhandled stType: '{symEntry.stType}'")
        contextSym = segment.addSymbol(symAddress, vromAddress=symVrom)

    if symName is not None:
        if symName.startswith("."):
            contextSym._isStatic = True
        else:
            contextSym.name = symName
    contextSym.isUserDeclared = True
    contextSym.setSizeIfUnset(symEntry.size)

    bind = elf32.Elf32SymbolTableBinding.fromValue(symEntry.stBind)
    if bind is not None:
        contextSym.visibility = bind.name.lower()

    return contextSym


def insertSymtabIntoContext(context: common.Context, symbolTable: elf32.Elf32Syms, stringTable: elf32.Elf32StringTable, elfFile: elf32.Elf32File) -> None:
    # Use the symbol table to replace symbol names present in disassembled sections
    for i, symEntry in enumerate(symbolTable):
        symName = stringTable[symEntry.name]

        if symEntry.shndx == 0:
            continue

        sectHeaderEntry = elfFile.sectionHeaders[symEntry.shndx]
        if sectHeaderEntry is None:
            continue

        if elfFile.header.type != elf32.Elf32ObjectFileType.REL.value:
            if symEntry.value != 0:
                addContextSymFromSymEntry(context, symEntry, symEntry.value, symName)
            continue

        sectName = elfFile.shstrtab[sectHeaderEntry.name]
        sectType = common.FileSectionType.fromStr(sectName)
        if sectType == common.FileSectionType.Invalid:
            common.Utils.eprint(f"Warning: symbol {i} (name: '{symName}', value: 0x{symEntry.value:X}) is referencing invalid section '{sectName}'")
            continue

        symVrom = symEntry.value + sectHeaderEntry.offset
        symAddress = symVrom

        contextSym = addContextSymFromSymEntry(context, symEntry, symAddress, symName, symVrom)
        if contextSym is not None:
            contextSym.sectionType = sectType

def insertDynsymIntoContext(context: common.Context, symbolTable: elf32.Elf32Syms, stringTable: elf32.Elf32StringTable) -> None:
    for symEntry in symbolTable:
        if symEntry.value == 0 or symEntry.shndx == 0:
            continue

        symName = stringTable[symEntry.name]
        addContextSymFromSymEntry(context, symEntry, symEntry.value, symName)

def insertGotIntoContext(context: common.Context, got: elf32.Elf32GlobalOffsetTable, stringTable: elf32.Elf32StringTable) -> None:
    lazyResolver = got.localsTable[0]
    lazyResolverSym = context.globalSegment.addSymbol(lazyResolver)
    lazyResolverSym.name = f"$$.LazyResolver"
    lazyResolverSym.isUserDeclared = True
    lazyResolverSym.isGotLocal = True

    gotIndex = len(got.localsTable)

    for gotEntry in got.globalsTable:
        symName = stringTable[gotEntry.symEntry.name]

        contextSym = addContextSymFromSymEntry(context, gotEntry.symEntry, gotEntry.getAddress(), symName)
        if contextSym is not None:
            contextSym.gotIndex = gotIndex
        gotIndex += 1


def injectAllElfSymbols(context: common.Context, elfFile: elf32.Elf32File, processedSegments: dict[common.FileSectionType, list[mips.sections.SectionBase]], sectionsPerName: dict[str, mips.sections.SectionBase]) -> None:
    if elfFile.symtab is not None and elfFile.strtab is not None:
        # Inject symbols from the reloc table referenced in each section
        if elfFile.header.type == elf32.Elf32ObjectFileType.REL.value:
            for sectionName, relocs in elfFile.relPerName.items():
                subSegment = sectionsPerName.get(sectionName, None)
                for rel in relocs:
                    symbolEntry = elfFile.symtab[rel.rSym]
                    symbolName = elfFile.strtab[symbolEntry.name]

                    if symbolEntry.stType != elf32.Elf32SymbolTableType.SECTION.value:
                        if symbolName == "":
                            continue

                    if subSegment is None:
                        common.Utils.eprint(f"Warning: reloc '{rel}' references unhandled section '{sectionName}'")
                        continue

                    relocVrom = subSegment.vromStart + rel.offset
                    relocInfo = context.addGlobalReloc(relocVrom, common.RelocType(rel.rType), symbolName)
                    if symbolEntry.stType == elf32.Elf32SymbolTableType.SECTION.value:
                        sectionEntry = elfFile.sectionHeaders[symbolEntry.shndx]
                        assert sectionEntry is not None, rel

                        sectionType = common.FileSectionType.fromStr(elfFile.shstrtab[sectionEntry.name])
                        if sectionType != common.FileSectionType.Invalid:
                            sectionVram = processedSegments[sectionType][0].vram
                            relocInfo.staticReference = common.RelocationStaticReference(sectionType, sectionVram)

        # Use the symtab to replace symbol names present in disassembled sections
        insertSymtabIntoContext(context, elfFile.symtab, elfFile.strtab, elfFile)

    if elfFile.dynsym is not None and elfFile.dynstr is not None:
        # Use the dynsym to replace symbol names present in disassembled sections
        insertDynsymIntoContext(context, elfFile.dynsym, elfFile.dynstr)

    if elfFile.got is not None and elfFile.dynstr is not None:
        insertGotIntoContext(context, elfFile.got, elfFile.dynstr)
    return

def processGlobalOffsetTable(context: common.Context, elfFile: elf32.Elf32File) -> None:
    if elfFile.dynamic is not None:
        common.GlobalConfig.GP_VALUE = elfFile.dynamic.getGpValue()

    if elfFile.reginfo is not None:
        common.GlobalConfig.GP_VALUE = elfFile.reginfo.gpValue

    if elfFile.dynamic is not None and elfFile.got is not None:
        globalsTable = [gotEntry.getAddress() for gotEntry in elfFile.got.globalsTable]

        assert elfFile.dynamic.pltGot is not None
        context.initGotTable(elfFile.dynamic.pltGot, elfFile.got.localsTable, globalsTable)

        for small in elfFile.smallSections.values():
            context.addSmallSection(small.addr, small.size)
    return


def processArguments(args: argparse.Namespace) -> int:
    applyArgs(args)

    applyGlobalConfigurations()

    context = common.Context()
    context.parseArgs(args)

    common.Utils.printQuietless(f"{PROGNAME} (spimdisasm {__version__})")

    inputPath = Path(args.binary)
    array_of_bytes = common.Utils.readFileAsBytearray(inputPath)
    elfFile = elf32.Elf32File(array_of_bytes)

    elfFile.handleHeaderIdent()
    elfFile.handleFlags()

    instrCategory = args.instr_category
    if instrCategory is None:
        if elf32.Elf32Constants.Elf32HeaderFlag._5900 in elfFile.elfFlags:
            instrCategory = "r5900"

    common.Utils.printQuietless(f"{PROGNAME} {inputPath}: Processing global offset table...")
    processGlobalOffsetTable(context, elfFile)

    applyReadelfLikeFlags(elfFile, args)

    textOutput = Path(args.output)
    if args.data_output is None:
        dataOutput = textOutput
    else:
        dataOutput = Path(args.data_output)

    common.Utils.printQuietless(f"{PROGNAME} {inputPath}: Reading segments...")
    if args.file_splits is not None:
        splits = common.FileSplitFormat()
        splits.readCsvFile(Path(args.file_splits))
        processedSegments, segmentPaths = fec.FrontendUtilities.getSplittedSections(context, splits, array_of_bytes, inputPath, textOutput, dataOutput)
        sectionsPerName: dict[str, mips.sections.SectionBase] = dict()
        for sectType, subSection in processedSegments.items():
            if len(subSection) < 1:
                continue
            if sectType == common.FileSectionType.Text:
                sectionsPerName[".text"] = subSection[0]
            elif sectType == common.FileSectionType.Data:
                sectionsPerName[".data"] = subSection[0]
            elif sectType == common.FileSectionType.Rodata:
                sectionsPerName[".rodata"] = subSection[0]
            elif sectType == common.FileSectionType.Bss:
                sectionsPerName[".bss"] = subSection[0]
    else:
        processedSegments, segmentPaths, sectionsPerName = getProcessedSections(context, elfFile, array_of_bytes, inputPath, textOutput, dataOutput)

    changeGlobalSegmentRanges(context, processedSegments)

    fec.FrontendUtilities.configureProcessedFiles(processedSegments, instrCategory)

    common.Utils.printQuietless(f"{PROGNAME} {inputPath}: Injecting elf symbols...")
    injectAllElfSymbols(context, elfFile, processedSegments, sectionsPerName)

    processedFilesCount = 0
    for sect in processedSegments.values():
        processedFilesCount += len(sect)

    common.Utils.printQuietless(f"{PROGNAME} {inputPath}: Analyzing sections...")
    fec.FrontendUtilities.analyzeProcessedFiles(processedSegments, segmentPaths, processedFilesCount)

    common.Utils.printQuietless(f"{PROGNAME} {inputPath}: Writing files...")
    fec.FrontendUtilities.writeProcessedFiles(processedSegments, segmentPaths, processedFilesCount)

    if args.split_functions is not None:
        common.Utils.printQuietless(f"{PROGNAME} {inputPath}: Migrating functions and rodata...")
        functionMigrationPath = Path(args.split_functions)
        fec.FrontendUtilities.migrateFunctions(processedSegments, functionMigrationPath)

        common.Utils.printQuietless(f"{PROGNAME} {inputPath}: Generating functions list...")
        mips.FilesHandlers.writeMigratedFunctionsList(processedSegments, functionMigrationPath, inputPath.stem)

    if args.save_context is not None:
        common.Utils.printQuietless(f"{PROGNAME} {inputPath}: Writing context...")
        contextPath = Path(args.save_context)
        contextPath.parent.mkdir(parents=True, exist_ok=True)
        context.saveContextToFile(contextPath)

    if args.function_info is not None:
        fec.FrontendUtilities.writeFunctionInfoCsv(processedSegments, Path(args.function_info))

    common.Utils.printQuietless(f"{PROGNAME} {inputPath}: Done!")

    return 0

def addSubparser(subparser: argparse._SubParsersAction[argparse.ArgumentParser]) -> None:
    parser = subparser.add_parser(PROGNAME, help=getToolDescription(), formatter_class=common.Utils.PreserveWhiteSpaceWrapRawTextHelpFormatter)

    addOptionsToParser(parser)

    parser.set_defaults(func=processArguments)


def elfObjDisasmMain() -> int:
    args = getArgsParser().parse_args()

    return processArguments(args)
