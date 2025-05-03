#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

from typing import Callable

from .. import common

from .Elf32Constants import Elf32HeaderIdentifier, Elf32ObjectFileType, Elf32HeaderFlag, Elf32SectionHeaderType, Elf32SectionHeaderFlag, Elf32SymbolTableType, Elf32SymbolTableBinding, Elf32SymbolVisibility, Elf32SectionHeaderNumber
from .Elf32Dyns import Elf32Dyns
from .Elf32GlobalOffsetTable import Elf32GlobalOffsetTable
from .Elf32Header import Elf32Header
from .Elf32RegInfo import Elf32RegInfo
from .Elf32SectionHeaders import Elf32SectionHeaders, Elf32SectionHeaderEntry
from .Elf32StringTable import Elf32StringTable
from .Elf32Syms import Elf32Syms
from .Elf32Rels import Elf32Rels


class Elf32File:
    def __init__(self, array_of_bytes: bytes) -> None:
        self.header = Elf32Header.fromBytearray(array_of_bytes)
        # print(self.header)

        dataEncoding = self.header.ident.getDataEncoding()
        if dataEncoding == Elf32HeaderIdentifier.DataEncoding.DATA2MSB:
            common.GlobalConfig.ENDIAN = common.InputEndian.BIG
        elif dataEncoding == Elf32HeaderIdentifier.DataEncoding.DATA2LSB:
            common.GlobalConfig.ENDIAN = common.InputEndian.LITTLE

        elfFlags, unknownElfFlags = Elf32HeaderFlag.parseFlags(self.header.flags)
        self.elfFlags = elfFlags
        self.unknownElfFlags = unknownElfFlags

        self.strtab: Elf32StringTable | None = None
        self.symtab: Elf32Syms | None = None

        self.dynamic: Elf32Dyns | None = None
        self.dynstr: Elf32StringTable | None = None
        self.dynsym: Elf32Syms | None = None

        #! deprecated
        self.progbits: dict[common.FileSectionType, Elf32SectionHeaderEntry] = dict()
        #! deprecated
        self.nobits: Elf32SectionHeaderEntry | None = None

        #! deprecated
        self.progbitsSmall: dict[common.FileSectionType, Elf32SectionHeaderEntry] = dict()
        #! deprecated
        self.nobitsSmall: Elf32SectionHeaderEntry | None = None

        #! deprecated
        self.rel: dict[common.FileSectionType, Elf32Rels] = dict()

        self.progbitsExecute: dict[str, Elf32SectionHeaderEntry] = dict()
        self.progbitsWrite: dict[str, Elf32SectionHeaderEntry] = dict()
        self.progbitsNoWrite: dict[str, Elf32SectionHeaderEntry] = dict()

        self.nobitsPerName: dict[str, Elf32SectionHeaderEntry] = dict()

        self.smallSections: dict[str, Elf32SectionHeaderEntry] = dict()

        self.relPerName: dict[str, Elf32Rels] = dict()

        self.reginfo: Elf32RegInfo | None = None

        self.sectionHeaders = Elf32SectionHeaders(array_of_bytes, self.header.shoff, self.header.shnum)

        shstrtabSectionEntry = self.sectionHeaders.sections[self.header.shstrndx]
        self.shstrtab = Elf32StringTable(array_of_bytes, shstrtabSectionEntry.offset, shstrtabSectionEntry.size)

        self.got: Elf32GlobalOffsetTable | None = None

        for entry in self.sectionHeaders.sections:
            sectionEntryName = self.shstrtab[entry.name]
            # print(sectionEntryName, end="\t ")
            # print(entry)

            callback = self._sectionProcessorCallbacks.get(entry.type)
            if callback is not None:
                callback(self, array_of_bytes, entry, sectionEntryName)
            elif common.GlobalConfig.VERBOSE:
                common.Utils.eprint("Unknown section header type found:", sectionEntryName, entry, "\n")

        if self.got is not None and self.dynamic is not None and self.dynsym is not None:
            self.got.initTables(self.dynamic, self.dynsym)


    def handleHeaderIdent(self) -> None:
        if self.header.ident.getVersion() != 1:
            common.Utils.eprint(f"Warning: Elf version '{self.header.ident.getVersion()}' when version '1' was expected.")


    def handleFlags(self) -> None:
        if self.unknownElfFlags != 0:
            common.Utils.eprint(f"Warning: Elf header has unknown flags: 0x{self.unknownElfFlags:X}")

        if Elf32HeaderFlag.PIC in self.elfFlags or Elf32HeaderFlag.CPIC in self.elfFlags:
            common.GlobalConfig.PIC = True

        if Elf32HeaderFlag.XGOT in self.elfFlags:
            common.Utils.eprint(f"Warning: Elf with XGOT flag.")
            common.Utils.eprint(f"\t This flag is currently not handled in any way, please report this")

        if Elf32HeaderFlag.F_64BIT_WHIRL in self.elfFlags:
            common.Utils.eprint(f"Warning: Elf with F_64BIT_WHIRL flag.")
            common.Utils.eprint(f"\t This flag is currently not handled in any way, please report this")

        if Elf32HeaderFlag.ABI_ON32 in self.elfFlags:
            common.Utils.eprint(f"Warning: Elf with ABI_ON32 flag.")
            common.Utils.eprint(f"\t This flag is currently not handled in any way, please report this")

        if Elf32HeaderFlag._32BITSMODE in self.elfFlags:
            common.Utils.eprint(f"Warning: Elf with 32BITSMODE flag.")
            common.Utils.eprint(f"\t This flag is currently not handled in any way, please report this")

        if Elf32HeaderFlag.FP64 in self.elfFlags:
            common.Utils.eprint(f"Warning: Elf with FP64 flag.")
            common.Utils.eprint(f"\t This flag is currently not handled in any way, please report this")

        if Elf32HeaderFlag.NAN2008 in self.elfFlags:
            common.Utils.eprint(f"Warning: Elf with NAN2008 flag.")
            common.Utils.eprint(f"\t This flag is currently not handled in any way, please report this")

        if Elf32HeaderFlag.ABI2 in self.elfFlags and Elf32HeaderFlag.O64 in self.elfFlags:
            common.Utils.eprint(f"Warning: Elf compiled using N64 ABI. Support is in experimental state")
            common.GlobalConfig.ABI = common.Abi.N32
        elif Elf32HeaderFlag.ABI2 in self.elfFlags:
            common.Utils.eprint(f"Warning: Elf compiled using N32 ABI. Support is in experimental state")
            common.GlobalConfig.ABI = common.Abi.N32
        elif Elf32HeaderFlag.O64 in self.elfFlags:
            common.Utils.eprint(f"Warning: Elf compiled using O64 ABI. Support is in experimental state")
            common.GlobalConfig.ABI = common.Abi.O64

        if Elf32HeaderFlag.EABI32 in self.elfFlags:
            common.Utils.eprint(f"Warning: Elf compiled using EABI32 ABI. Support is in experimental state")
            common.GlobalConfig.ABI = common.Abi.EABI32

        if Elf32HeaderFlag.EABI64 in self.elfFlags:
            common.Utils.eprint(f"Warning: Elf compiled using EABI64 ABI. Support is in experimental state")
            common.GlobalConfig.ABI = common.Abi.EABI64

        unkArchLevel = {Elf32HeaderFlag.ARCH_5, Elf32HeaderFlag.ARCH_32, Elf32HeaderFlag.ARCH_64, Elf32HeaderFlag.ARCH_32R2, Elf32HeaderFlag.ARCH_64R2} & set(self.elfFlags)
        if unkArchLevel:
            unkArchLevelNames = [x.name for x in unkArchLevel]
            common.Utils.eprint(f"Warning: Elf uses not supported architecture level: {unkArchLevelNames}")
            common.Utils.eprint(f"\t This means this elf probably uses an unknown instruction set")

        if Elf32HeaderFlag.ARCH_1 in self.elfFlags:
            common.GlobalConfig.ARCHLEVEL = common.ArchLevel.MIPS1
        elif Elf32HeaderFlag.ARCH_2 in self.elfFlags:
            common.GlobalConfig.ARCHLEVEL = common.ArchLevel.MIPS2
        elif Elf32HeaderFlag.ARCH_3 in self.elfFlags:
            common.GlobalConfig.ARCHLEVEL = common.ArchLevel.MIPS3
        elif Elf32HeaderFlag.ARCH_4 in self.elfFlags:
            common.GlobalConfig.ARCHLEVEL = common.ArchLevel.MIPS5
        elif Elf32HeaderFlag.ARCH_5 in self.elfFlags:
            common.GlobalConfig.ARCHLEVEL = common.ArchLevel.MIPS5
        elif Elf32HeaderFlag.ARCH_32 in self.elfFlags:
            common.GlobalConfig.ARCHLEVEL = common.ArchLevel.MIPS32
        elif Elf32HeaderFlag.ARCH_64 in self.elfFlags:
            common.GlobalConfig.ARCHLEVEL = common.ArchLevel.MIPS64
        elif Elf32HeaderFlag.ARCH_32R2 in self.elfFlags:
            common.GlobalConfig.ARCHLEVEL = common.ArchLevel.MIPS32R2
        elif Elf32HeaderFlag.ARCH_64R2 in self.elfFlags:
            common.GlobalConfig.ARCHLEVEL = common.ArchLevel.MIPS64R2


    def _processSection_NULL(self, array_of_bytes: bytes, entry: Elf32SectionHeaderEntry, sectionEntryName: str) -> None:
        pass

    def _processSection_PROGBITS(self, array_of_bytes: bytes, entry: Elf32SectionHeaderEntry, sectionEntryName: str) -> None:
        fileSecType = common.FileSectionType.fromStr(sectionEntryName)
        smallFileSecType = common.FileSectionType.fromSmallStr(sectionEntryName)
        flags, unknownFlags = Elf32SectionHeaderFlag.parseFlags(entry.flags)

        if fileSecType != common.FileSectionType.Invalid:
            self.progbits[fileSecType] = entry
            if fileSecType == common.FileSectionType.Text:
                self.sectionHeaders.mipsText = entry
            elif fileSecType == common.FileSectionType.Data:
                self.sectionHeaders.mipsData = entry
        elif smallFileSecType != common.FileSectionType.Invalid:
            self.progbitsSmall[smallFileSecType] = entry
        elif sectionEntryName == ".got":
            self.got = Elf32GlobalOffsetTable(array_of_bytes, entry.offset, entry.size)
        elif sectionEntryName == ".interp":
            # strings with names of dynamic libraries
            common.Utils.printVerbose(f"Unhandled PROGBITS found: '{sectionEntryName}'")
        elif sectionEntryName == ".MIPS.stubs":
            # ?
            common.Utils.printVerbose(f"Unhandled PROGBITS found: '{sectionEntryName}'")
        elif sectionEntryName == ".init":
            # ?
            common.Utils.printVerbose(f"Unhandled PROGBITS found: '{sectionEntryName}'")
        elif common.GlobalConfig.VERBOSE:
            common.Utils.eprint(f"Unhandled PROGBITS found: '{sectionEntryName}'", entry, "\n")

        if smallFileSecType != common.FileSectionType.Invalid:
            self.smallSections[sectionEntryName] = entry

        if sectionEntryName == ".got":
            self.got = Elf32GlobalOffsetTable(array_of_bytes, entry.offset, entry.size)
        elif Elf32SectionHeaderFlag.EXECINSTR in flags and sectionEntryName != ".vutext":
            self.progbitsExecute[sectionEntryName] = entry
        elif sectionEntryName in {".rodata", ".rdata"}:
            # Some compilers set the Write flag on .rodata sections, so we need to hardcode
            # a special check to distinguish it properly
            self.progbitsNoWrite[sectionEntryName] = entry
        elif Elf32SectionHeaderFlag.WRITE in flags:
            self.progbitsWrite[sectionEntryName] = entry
        elif Elf32SectionHeaderFlag.ALLOC in flags:
            # Allocated on runtime but not executable nor writeable
            self.progbitsNoWrite[sectionEntryName] = entry
        elif Elf32SectionHeaderFlag.STRINGS in flags:
            # Why not?
            self.progbitsNoWrite[sectionEntryName] = entry
        elif sectionEntryName == ".comment":
            # Usually strings specifying the compiler used to build
            pass
        elif sectionEntryName == ".pdr":
            # Debugging section, dunno what it actually has
            pass
        elif not common.GlobalConfig.QUIET:
            common.Utils.eprint(f"Unhandled PROGBITS found: '{sectionEntryName}', flags: {flags}, unknownFlags: {unknownFlags}\n")

    def _processSection_SYMTAB(self, array_of_bytes: bytes, entry: Elf32SectionHeaderEntry, sectionEntryName: str) -> None:
        if sectionEntryName == ".symtab":
            self.symtab = Elf32Syms(array_of_bytes, entry.offset, entry.size)
        elif common.GlobalConfig.VERBOSE:
            common.Utils.eprint("Unhandled SYMTAB found: ", sectionEntryName, entry, "\n")

    def _processSection_STRTAB(self, array_of_bytes: bytes, entry: Elf32SectionHeaderEntry, sectionEntryName: str) -> None:
        if sectionEntryName == ".strtab":
            self.strtab = Elf32StringTable(array_of_bytes, entry.offset, entry.size)
        elif sectionEntryName == ".dynstr":
            self.dynstr = Elf32StringTable(array_of_bytes, entry.offset, entry.size)
        elif sectionEntryName == ".shstrtab":
            pass
        elif common.GlobalConfig.VERBOSE:
            common.Utils.eprint("Unhandled STRTAB found: ", sectionEntryName, entry, "\n")

    def _processSection_RELA(self, array_of_bytes: bytes, entry: Elf32SectionHeaderEntry, sectionEntryName: str) -> None:
        # ?
        pass

    def _processSection_HASH(self, array_of_bytes: bytes, entry: Elf32SectionHeaderEntry, sectionEntryName: str) -> None:
        # ?
        pass

    def _processSection_DYNAMIC(self, array_of_bytes: bytes, entry: Elf32SectionHeaderEntry, sectionEntryName: str) -> None:
        if sectionEntryName == ".dynamic":
            self.dynamic = Elf32Dyns(array_of_bytes, entry.offset, entry.size)
        elif common.GlobalConfig.VERBOSE:
            common.Utils.eprint("Unhandled DYNAMIC found: ", sectionEntryName, entry, "\n")

    def _processSection_NOTE(self, array_of_bytes: bytes, entry: Elf32SectionHeaderEntry, sectionEntryName: str) -> None:
        # ?
        pass

    def _processSection_NOBITS(self, array_of_bytes: bytes, entry: Elf32SectionHeaderEntry, sectionEntryName: str) -> None:
        if sectionEntryName == ".bss":
            self.nobits = entry
        if sectionEntryName == ".sbss":
            self.nobitsSmall = entry
        elif common.GlobalConfig.VERBOSE:
            common.Utils.eprint("Unhandled NOBITS found: ", sectionEntryName, entry, "\n")


        smallFileSecType = common.FileSectionType.fromSmallStr(sectionEntryName)
        if smallFileSecType != common.FileSectionType.Invalid:
            self.smallSections[sectionEntryName] = entry

        self.nobitsPerName[sectionEntryName] = entry

    def _processSection_REL(self, array_of_bytes: bytes, entry: Elf32SectionHeaderEntry, sectionEntryName: str) -> None:
        sectName = sectionEntryName[4:]

        if sectionEntryName.startswith(".rel"):
            fileSecType = common.FileSectionType.fromStr(sectName)
            if fileSecType != common.FileSectionType.Invalid:
                self.rel[fileSecType] = Elf32Rels(sectionEntryName, array_of_bytes, entry.offset, entry.size)
            elif common.GlobalConfig.VERBOSE:
                common.Utils.eprint("Unhandled REL subsection found: ", sectionEntryName, entry, "\n")
        elif common.GlobalConfig.VERBOSE:
            common.Utils.eprint("Unhandled REL found: ", sectionEntryName, entry, "\n")

        if sectionEntryName.startswith(".rel"):
            self.relPerName[sectName] = Elf32Rels(sectionEntryName, array_of_bytes, entry.offset, entry.size)
        else:
            common.Utils.eprint("Unhandled REL found: ", sectionEntryName, entry, "\n")

    def _processSection_DYNSYM(self, array_of_bytes: bytes, entry: Elf32SectionHeaderEntry, sectionEntryName: str) -> None:
        if sectionEntryName == ".dynsym":
            self.dynsym = Elf32Syms(array_of_bytes, entry.offset, entry.size)
        elif common.GlobalConfig.VERBOSE:
            common.Utils.eprint("Unhandled DYNSYM found: ", sectionEntryName, entry, "\n")


    def _processSection_MIPS_LIBLIST(self, array_of_bytes: bytes, entry: Elf32SectionHeaderEntry, sectionEntryName: str) -> None:
        # ?
        pass

    def _processSection_MIPS_MSYM(self, array_of_bytes: bytes, entry: Elf32SectionHeaderEntry, sectionEntryName: str) -> None:
        # ?
        pass

    def _processSection_MIPS_CONFLICT(self, array_of_bytes: bytes, entry: Elf32SectionHeaderEntry, sectionEntryName: str) -> None:
        # ?
        pass

    def _processSection_MIPS_GPTAB(self, array_of_bytes: bytes, entry: Elf32SectionHeaderEntry, sectionEntryName: str) -> None:
        # ?
        pass

    def _processSection_MIPS_DEBUG(self, array_of_bytes: bytes, entry: Elf32SectionHeaderEntry, sectionEntryName: str) -> None:
        # ?
        pass

    def _processSection_MIPS_REGINFO(self, array_of_bytes: bytes, entry: Elf32SectionHeaderEntry, sectionEntryName: str) -> None:
        if sectionEntryName == ".reginfo":
            self.reginfo = Elf32RegInfo.fromBytearray(array_of_bytes, entry.offset)
        elif common.GlobalConfig.VERBOSE:
            common.Utils.eprint("Unhandled MIPS_REGINFO found: ", sectionEntryName, entry, "\n")

    def _processSection_MIPS_OPTIONS(self, array_of_bytes: bytes, entry: Elf32SectionHeaderEntry, sectionEntryName: str) -> None:
        # ?
        pass

    def _processSection_MIPS_SYMBOL_LIB(self, array_of_bytes: bytes, entry: Elf32SectionHeaderEntry, sectionEntryName: str) -> None:
        # ?
        pass

    def _processSection_MIPS_ABIFLAGS(self, array_of_bytes: bytes, entry: Elf32SectionHeaderEntry, sectionEntryName: str) -> None:
        # ?
        pass


    _sectionProcessorCallbacks: dict[int, Callable[[Elf32File, bytes, Elf32SectionHeaderEntry, str], None]] = {
        Elf32SectionHeaderType.NULL.value: _processSection_NULL,
        Elf32SectionHeaderType.PROGBITS.value: _processSection_PROGBITS,
        Elf32SectionHeaderType.SYMTAB.value: _processSection_SYMTAB,
        Elf32SectionHeaderType.STRTAB.value: _processSection_STRTAB,
        # Elf32SectionHeaderType.RELA.value: _processSection_RELA,
        Elf32SectionHeaderType.HASH.value: _processSection_HASH,
        Elf32SectionHeaderType.DYNAMIC.value: _processSection_DYNAMIC,
        # Elf32SectionHeaderType.NOTE.value: _processSection_NOTE,
        Elf32SectionHeaderType.NOBITS.value: _processSection_NOBITS,
        Elf32SectionHeaderType.REL.value: _processSection_REL,
        Elf32SectionHeaderType.DYNSYM.value: _processSection_DYNSYM,

        Elf32SectionHeaderType.MIPS_LIBLIST.value: _processSection_MIPS_LIBLIST,
        Elf32SectionHeaderType.MIPS_MSYM.value: _processSection_MIPS_MSYM,
        Elf32SectionHeaderType.MIPS_CONFLICT.value: _processSection_MIPS_CONFLICT,
        Elf32SectionHeaderType.MIPS_GPTAB.value: _processSection_MIPS_GPTAB,
        Elf32SectionHeaderType.MIPS_DEBUG.value: _processSection_MIPS_DEBUG,
        Elf32SectionHeaderType.MIPS_REGINFO.value: _processSection_MIPS_REGINFO,
        Elf32SectionHeaderType.MIPS_OPTIONS.value: _processSection_MIPS_OPTIONS,
        Elf32SectionHeaderType.MIPS_SYMBOL_LIB.value: _processSection_MIPS_SYMBOL_LIB,
        Elf32SectionHeaderType.MIPS_ABIFLAGS.value: _processSection_MIPS_ABIFLAGS,
    }


    def readelf_fileHeader(self) -> None:
        print(f"ELF Header:")
        print(f"  Magic:  ", end="")
        for magic in self.header.ident.ident:
            print(f" {magic:02X}", end="")
        print(f"\n          ", end="")
        for magic in self.header.ident.ident:
            character = chr(magic)
            if not character.isprintable():
                character = f"{magic:02X}"

            print(f" {character:>2}", end="")
        print()

        print(f"  {'Class:':<34} {self.header.ident.getFileClass().name.replace('CLASS', 'ELF')}")

        print(f"  {'Data:':<34} ", end="")
        dataEncoding = self.header.ident.getDataEncoding()
        if dataEncoding == Elf32HeaderIdentifier.DataEncoding.DATANONE:
            print("Invalid data encoding")
        elif dataEncoding == Elf32HeaderIdentifier.DataEncoding.DATA2LSB:
            print("2's complement, little endian")
        elif dataEncoding == Elf32HeaderIdentifier.DataEncoding.DATA2MSB:
            print("2's complement, big endian")
        else:
            print(dataEncoding.name)

        print(f"  {'Version:':<34} ", end="")
        version = self.header.ident.getVersion()
        print(f"{version}" + (" (current)" if version == 1 else ""))

        print(f"  {'OS/ABI:':<34} ", end="")
        osAbi = self.header.ident.getOsAbi()
        if osAbi == Elf32HeaderIdentifier.OsAbi.NONE:
            print(f"UNIX - System V")
        elif osAbi == Elf32HeaderIdentifier.OsAbi.IRIX:
            print(f"SGI Irix")
        else:
            print(osAbi.name)

        print(f"  {'ABI Version:':<34} {self.header.ident.getAbiVersion()}")

        print(f"  {'Type:':<34} ", end="")
        try:
            filetype = Elf32ObjectFileType(self.header.type)
            print(f"{filetype.name}", end="")
            if filetype == Elf32ObjectFileType.NONE:
                print(" (No file type)")
            elif filetype == Elf32ObjectFileType.REL:
                print(" (Relocatable file)")
            elif filetype == Elf32ObjectFileType.EXEC:
                print(" (Executable file)")
            elif filetype == Elf32ObjectFileType.DYN:
                print(" (Shared object file)")
            elif filetype == Elf32ObjectFileType.CORE:
                print(" (Core file)")
            else:
                print(" (Unknown)")
        except ValueError:
            print(f"0x{self.header.type:04X}", end="")
            if 0xFE00 <= self.header.type <= 0xFEFF:
                print(" (OS-specific)")
            if 0xFF00 <= self.header.type <= 0xFFFF:
                print(" (Processor-specific)")
            else:
                print(" (Unknown)")

        # TODO: print name
        # print(f"  Machine:                           MIPS R3000")
        print(f"  {'Machine:':<34} {self.header.machine}")

        print(f"  {'Version:':<34} 0x{self.header.version:X}")

        print(f"  {'Entry point address:':<34} 0x{self.header.entry:08X}")

        print(f"  {'Start of program headers:':<34} 0x{self.header.phoff:X} (bytes into file)")

        print(f"  {'Start of section headers:':<34} 0x{self.header.shoff:X} (bytes into file)")

        print(f"  {'Flags:':<34} 0x{self.header.flags:X}", end="")
        for flag in self.elfFlags:
            printableFlagName = flag.name.lower().replace('arch_', 'mips')
            if len(printableFlagName) > 0 and printableFlagName[0] == "_":
                printableFlagName = printableFlagName[1:]
            print(f", {printableFlagName}", end="")
        if self.unknownElfFlags != 0:
            print(f", 0x{self.unknownElfFlags:08X}", end="")
        print()

        print(f"  {'Size of this header:':<34} 0x{self.header.ehsize:X} (bytes)")

        print(f"  {'Size of program headers:':<34} 0x{self.header.phentsize:X} (bytes)")

        print(f"  {'Number of program headers:':<34} {self.header.phnum}")

        print(f"  {'Size of section headers:':<34} 0x{self.header.shentsize:X} (bytes)")

        print(f"  {'Number of section headers:':<34} {self.header.shnum}")

        print(f"  {'Section header string table index:':<34} {self.header.shstrndx}")

        print()


    def readelf_sectionHeaders(self) -> None:
        flagsKeys = {
            Elf32SectionHeaderFlag.WRITE:               "W",
            Elf32SectionHeaderFlag.ALLOC:               "A",
            Elf32SectionHeaderFlag.EXECINSTR:           "X",
            Elf32SectionHeaderFlag.MERGE:               "M",
            Elf32SectionHeaderFlag.STRINGS:             "S",
            Elf32SectionHeaderFlag.INFO_LINK:           "I",
            Elf32SectionHeaderFlag.LINK_ORDER:          "L",
            Elf32SectionHeaderFlag.OS_NONCONFORMING:    "O",
            Elf32SectionHeaderFlag.GROUP:               "G",
            Elf32SectionHeaderFlag.TLS:                 "T",
            Elf32SectionHeaderFlag.COMPRESSED:          "C",
            Elf32SectionHeaderFlag.EXCLUDE:             "E",
        }

        print(f"There are {len(self.sectionHeaders)} section headers, starting at offset 0x{self.sectionHeaders.shoff:X}:")
        print()

        print(f"Section Headers:")

        largestSectionHeaderName = 17
        for header in self.sectionHeaders:
            name = self.shstrtab[header.name]

            if len(name) > largestSectionHeaderName:
                largestSectionHeaderName = len(name)

        print(f"  [{'Nr':>2}] {'Name':<{largestSectionHeaderName}}  {'Type':<15} {'Addr':<8} {'Off':<6} {'Size':<6} ES Flg Lk Inf Al")

        i = 0
        for header in self.sectionHeaders:
            name = self.shstrtab[header.name]

            headerType = Elf32SectionHeaderType.fromValue(header.type)
            headerTypeStr = f"<0x{header.type:X}>"
            if headerType is not None:
                headerTypeStr = headerType.name

            flags, unknownFlags = Elf32SectionHeaderFlag.parseFlags(header.flags)
            flagsStr: str = ""
            for flag in flags:
                flagsStr += flagsKeys[flag]

            if unknownFlags & 0x0FF00000:
                flagsStr += 'o'
            unknownFlags &= ~0x0FF00000
            if unknownFlags & 0xF0000000:
                flagsStr += 'p'
            unknownFlags &= ~0xF0000000

            print(f"  [{i:>2}] {name:<{largestSectionHeaderName}}  {headerTypeStr:<15} {header.addr:08X} {header.offset:06X} {header.size:06X} {header.entsize:02X} {flagsStr:>3} {header.link:> 2X} {header.info:> 3X} {header.addralign:>2X}")
            if unknownFlags:
                print(f"Warning unknown flags: 0x{unknownFlags:X}")

            i += 1

        print(f"Key to Flags:")
        print(f"  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),")
        print(f"  L (link order), O (extra OS processing required), G (group), T (TLS),")
        print(f"  C (compressed), x (unknown), o (OS specific), E (exclude),")
        print(f"  D (mbind), p (processor specific)")

        print()


    def _readelf_symbol_table(self, symbolTable: Elf32Syms, stringTable: Elf32StringTable|None) -> None:
        symbolTableName = ""

        for header in self.sectionHeaders:
            if header.offset == symbolTable.offset:
                symbolTableName = self.shstrtab[header.name]

        print(f"Symbol table '{symbolTableName}' contains {len(symbolTable.symbols)} entries:")

        print(f" {'Num':>5}: {'Value':>8} {'Size':>5} {'Type':7} {'Bind':6} {'Vis':9} {'Ndx':>15} {'Name'}")

        for i, sym in enumerate(symbolTable.symbols):
            entryType = Elf32SymbolTableType(sym.stType)

            bind = str(sym.stBind)
            stBind = Elf32SymbolTableBinding.fromValue(sym.stBind)
            if stBind is not None:
                bind = stBind.name

            visibility: str = f"0x{sym.other:X}"
            stOther = Elf32SymbolVisibility.fromValue(sym.other)
            if stOther is not None:
                visibility = stOther.name

            ndx: str = f"0x{sym.shndx:X}"
            shndx = Elf32SectionHeaderNumber.fromValue(sym.shndx)
            if shndx is not None:
                ndx = shndx.name
            elif entryType in { Elf32SymbolTableType.OBJECT, Elf32SymbolTableType.FUNC }:
                # spimdisasm-extension: instead of a number we use the section name if available
                section = self.sectionHeaders[sym.shndx]
                if section is not None:
                    ndx = self.shstrtab[section.name]

            symName = ""
            if stringTable is not None:
                symName = stringTable[sym.name]
            if symName == "":
                # GNU readelf uses the section's name as the name column for sections instead of the symbol's name.
                if entryType == Elf32SymbolTableType.SECTION:
                    section = self.sectionHeaders[sym.shndx]
                    if section is not None:
                        symName = self.shstrtab[section.name]

            print(f" {i:>5}: {sym.value:08X} {sym.size:>5X} {entryType.name:7} {bind:6} {visibility:9} {ndx:>15} {symName}")

        print()

    def readelf_syms(self) -> None:
        if self.symtab is None:
            return

        self._readelf_symbol_table(self.symtab, self.strtab)

    def readelf_dyn_syms(self) -> None:
        if self.dynsym is None:
            return

        self._readelf_symbol_table(self.dynsym, self.dynstr)

    def readelf_relocs(self) -> None:
        for relSection in self.rel.values():
            print(f"Relocation section '{relSection.sectionName}' at offset 0x{relSection.offset:X} contains {len(relSection.relocations)} entries:")

            # Info column is basically useless since this shows the type and sym too
            print(f" {'Offset':8} {'Info':8} {'Type':12} {'Sym.Value':>9} {'Sym.Name'}")
            for rel in relSection.relocations:
                relType = str(rel.rType)
                rType = common.RelocType.fromValue(rel.rType)
                if rType is not None:
                    relType = rType.name

                symValue = ""
                symName = ""
                if self.symtab is not None:
                    sym = self.symtab[rel.rSym]
                    symValue = f"{sym.value:08X}"
                    if self.strtab is not None:
                        symName = self.strtab[sym.name]
                if symName == "":
                    # Some relocations are an offset to a section on the current object instead of to a symtab symbol.
                    # TODO: what is the proper way to check this?
                    section = self.sectionHeaders[sym.shndx]
                    if section is not None:
                        symName = self.shstrtab[section.name]

                print(f" {rel.offset:08X} {rel.info:08X} {relType:<12} {symValue:>9} {symName}")

            print()

        print()

    def readelf_displayGot(self) -> None:
        print(f"Primary GOT:")
        gpValue = 0x7FF0
        entryAddress = 0
        if self.dynamic is not None and self.dynamic.pltGot is not None:
            gpValue = self.dynamic.getGpValue() or 0
            if common.GlobalConfig.GP_VALUE is not None:
                gpValue = common.GlobalConfig.GP_VALUE
            entryAddress = self.dynamic.pltGot
            print(f" Canonical gp value: {gpValue:X}")
            print()

        if self.got is not None:
            print(f" Reserved entries:")
            print(f"   Address {'Access':>12}  Initial Purpose")
            access = entryAddress - gpValue
            if access < 0:
                accessStr = f"-0x{-access:X}"
            else:
                accessStr = f"0x{access:X}"
            print(f"  {entryAddress:8X} {accessStr:5}($gp) {self.got.localsTable[0]:08X} Lazy resolver")
            entryAddress += 4

            print()

            print(f" Local entries:")
            print(f"   Address {'Access':>12}  Initial")
            for x in self.got.localsTable[1:]:
                access = entryAddress - gpValue
                if access < 0:
                    accessStr = f"-0x{-access:X}"
                else:
                    accessStr = f"0x{access:X}"
                print(f"  {entryAddress:8X} {accessStr:5}($gp) {x:08X}")
                entryAddress += 4

            print()

            print(f" Global entries:")
            print(f"  {'Address':>8} {'Access':>12}  Initial Sym.Val. Type    {'Ndx':12} Name")
            for gotEntry in self.got.globalsTable:
                access = entryAddress - gpValue
                if access < 0:
                    accessStr = f"-0x{-access:X}"
                else:
                    accessStr = f"0x{access:X}"
                entryType = Elf32SymbolTableType(gotEntry.symEntry.stType)
                ndx: str = f"0x{gotEntry.symEntry.shndx:X}"
                shndx = Elf32SectionHeaderNumber.fromValue(gotEntry.symEntry.shndx)
                if shndx is not None:
                    ndx = shndx.name
                symName = ""
                if self.dynstr is not None:
                    symName = self.dynstr[gotEntry.symEntry.name]
                print(f"  {entryAddress:8X} {accessStr:5}($gp) {gotEntry.getAddress():08X} {gotEntry.symEntry.value:08X} {entryType.name:7} {ndx:12} {symName}")
                entryAddress += 4

            print()

        print()
