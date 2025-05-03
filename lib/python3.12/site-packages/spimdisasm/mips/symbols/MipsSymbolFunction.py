#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

import rabbitizer

from ... import common

from . import SymbolText, analysis


class SymbolFunction(SymbolText):
    def __init__(self, context: common.Context, vromStart: int, vromEnd: int, inFileOffset: int, vram: int, instrsList: list[rabbitizer.Instruction], segmentVromStart: int, overlayCategory: str|None) -> None:
        super().__init__(context, vromStart, vromEnd, inFileOffset, vram, list(), segmentVromStart, overlayCategory)
        self.instructions = list(instrsList)

        self.instrAnalyzer = analysis.InstrAnalyzer(self.vram, context)

        self.branchesTaken: set[tuple[int, bool]] = set()

        self.pointersOffsets: set[int] = set()
        self.pointersRemoved: bool = False

        self.hasUnimplementedIntrs: bool = False
        self.isRsp: bool = False
        self.isLikelyHandwritten: bool = False
        self.gpRelHack: bool = False

    @property
    def nInstr(self) -> int:
        return len(self.instructions)

    @property
    def sizew(self) -> int:
        return self.nInstr

    def isFunction(self) -> bool:
        return True

    def _lookAheadSymbolFinder(self, instr: rabbitizer.Instruction, prevInstr: rabbitizer.Instruction, instructionOffset: int, trackedRegistersOriginal: rabbitizer.RegistersTracker, prev_is_likely: bool) -> None:
        if not prevInstr.isBranch() and not prevInstr.isUnconditionalBranch():
            return

        currentVram = self.getVramOffset(instructionOffset)

        prevInstrOffset = instructionOffset - 4
        branchOffset = prevInstr.getBranchOffsetGeneric()
        branch = prevInstrOffset + branchOffset

        if branch < 0:
            # Avoid jumping outside of the function
            return

        regsTracker = rabbitizer.RegistersTracker(trackedRegistersOriginal)

        self.instrAnalyzer.processInstr(regsTracker, instr, instructionOffset, currentVram, None)

        if (instructionOffset, prev_is_likely) in self.branchesTaken:
            return
        self.branchesTaken.add((instructionOffset, prev_is_likely))

        sizew = len(self.instructions)*4
        while branch < sizew:
            prevTargetInstr = self.instructions[branch//4 - 1]
            targetInstr = self.instructions[branch//4]

            self.instrAnalyzer.processInstr(regsTracker, targetInstr, branch, self.getVramOffset(branch), prevTargetInstr)

            self._lookAheadSymbolFinder(targetInstr, prevTargetInstr, branch, regsTracker, prev_is_likely or prevTargetInstr.isBranchLikely())

            if prevTargetInstr.isUnconditionalBranch():
                # Since we took the branch on the previous _lookAheadSymbolFinder
                # call then we don't have anything else to process here.
                return
            if prevTargetInstr.isJump() and not prevTargetInstr.doesLink():
                # Technically this is another form of unconditional branching.
                return

            self.instrAnalyzer.processPrevFuncCall(regsTracker, targetInstr, prevTargetInstr)
            branch += 4

    def _runInstructionAnalyzer(self) -> None:
        regsTracker = rabbitizer.RegistersTracker()

        sizew = len(self.instructions)*4

        instructionOffset = 0
        if instructionOffset < sizew:
            # First process the first instruction. We do this separately because the first one doesn't have a prev instruction.

            currentVram = self.getVramOffset(instructionOffset)
            instr = self.instructions[instructionOffset//4]

            if instr.isLikelyHandwritten() and not self.isRsp:
                self.isLikelyHandwritten = True
                self.endOfLineComment[instructionOffset//4] = " /* handwritten instruction */"

            if not common.GlobalConfig.DISASSEMBLE_UNKNOWN_INSTRUCTIONS and not instr.isImplemented():
                # Abort analysis
                self.hasUnimplementedIntrs = True
                return

            self.instrAnalyzer.processInstr(regsTracker, instr, instructionOffset, currentVram, None)
            instructionOffset += 4

        while instructionOffset < sizew:
            currentVram = self.getVramOffset(instructionOffset)
            prevInstr = self.instructions[instructionOffset//4 - 1]
            instr = self.instructions[instructionOffset//4]

            currentVram = self.getVramOffset(instructionOffset)
            prevInstr = self.instructions[instructionOffset//4 - 1]

            self.instrAnalyzer.printAnalisisDebugInfo_IterInfo(regsTracker, instr, currentVram)

            if instr.isLikelyHandwritten() and not self.isRsp:
                self.isLikelyHandwritten = True
                self.endOfLineComment[instructionOffset//4] = " /* handwritten instruction */"

            if not common.GlobalConfig.DISASSEMBLE_UNKNOWN_INSTRUCTIONS and not instr.isImplemented():
                # Abort analysis
                self.hasUnimplementedIntrs = True
                return

            if not prevInstr.isBranchLikely() and not prevInstr.isUnconditionalBranch():
                self.instrAnalyzer.processInstr(regsTracker, instr, instructionOffset, currentVram, prevInstr)

            # look-ahead symbol finder
            self._lookAheadSymbolFinder(instr, prevInstr, instructionOffset, regsTracker, prevInstr.isBranchLikely())

            if prevInstr.isJumpWithAddress() and not prevInstr.doesLink():
                targetVram = prevInstr.getBranchVramGeneric()
                if targetVram < self.vram or targetVram >= self.vramEnd:
                    # Function is jumping outside the current function, so
                    # the state of the registers is garbage to the rest of the
                    # function, so just reset everything.
                    # Jumping without linking outside of functions like this is
                    # usually caused by tail call optimizations.
                    regsTracker = rabbitizer.RegistersTracker()

            self.instrAnalyzer.processPrevFuncCall(regsTracker, instr, prevInstr, currentVram)

            if prevInstr.isUnconditionalBranch() or (prevInstr.isJumpWithAddress() and not prevInstr.doesLink()) or prevInstr.isReturn():
                # Execution diverges here, so it doesn't make sense to keep the current state.
                regsTracker = rabbitizer.RegistersTracker()

            instructionOffset += 4

        self.instrAnalyzer.printSymbolFinderDebugInfo_UnpairedLuis()

    def _processElfRelocSymbols(self) -> None:
        if len(self.context.globalRelocationOverrides) == 0:
            return

        if common.GlobalConfig.INPUT_FILE_TYPE != common.InputFileType.ELF:
            return

        instructionOffset = 0
        vrom = self.vromStart
        for instr in self.instructions:
            relocInfo = self.context.globalRelocationOverrides.get(vrom)
            if relocInfo is not None:
                if relocInfo.relocType == common.RelocType.MIPS_26:
                    if relocInfo.staticReference is not None:
                        targetVram = instr.getInstrIndexAsVram() + relocInfo.staticReference.sectionVram
                        if instr.doesLink():
                            # Function call
                            relocInfo.symbol = self.addFunction(targetVram, isAutogenerated=True)
                        else:
                            relocInfo.symbol = self.addBranchLabel(targetVram, isAutogenerated=True)
                        relocInfo.symbol._isStatic = True
                else:
                    offsetAddend = self.instrAnalyzer.symbolInstrOffset.get(instructionOffset)
                    if offsetAddend is not None:
                        hiOffset = self.instrAnalyzer.lowToHiDict.get(instructionOffset)
                        if hiOffset is not None:
                            self.instrAnalyzer.symbolInstrOffset[hiOffset] = offsetAddend

                    if relocInfo.staticReference is not None:
                        # For static symbols which only reference the start of a section
                        symbolVram = relocInfo.staticReference.sectionVram
                        if instr.hasOperandAlias(rabbitizer.OperandType.cpu_immediate):
                            if instructionOffset in self.instrAnalyzer.symbolInstrOffset:
                                addressOffset = self.instrAnalyzer.symbolInstrOffset[instructionOffset]
                                symbolVram += addressOffset
                            else:
                                symbolVram += instr.getProcessedImmediate()
                        contextSym = self.getSymbol(symbolVram, tryPlusOffset=True)
                        if contextSym is None:
                            contextSym = self.addSymbol(symbolVram, isAutogenerated=True)
                        relocInfo.symbol = contextSym
                        relocInfo.symbol._isStatic = True
                        relocInfo.addend = symbolVram - contextSym.vram
                    elif offsetAddend is not None:
                        # Addends for global symbols
                        relocInfo.addend = offsetAddend

            vrom += 4
            instructionOffset += 4


    def _postProcessGotAccesses(self) -> None:
        if not common.GlobalConfig.PIC:
            return

        globalGotOffsets: set[int] = set()

        for gotAccessOffset, gotAccess in self.instrAnalyzer.gotAccessAddresses.items():
            gpAccess = self.context.gpAccesses.requestAddress(gotAccess)
            if gpAccess is None:
                common.Utils.eprint(1, f"0x{self.instructions[gotAccessOffset//4].vram:08X}", f"0x{gotAccess:08X}", self.instructions[gotAccessOffset//4].disassemble())
                continue

            gotAddress = gpAccess.address
            if not gpAccess.isGotLocal:
                globalGotOffsets.add(gotAccessOffset)
                contextSym = self.addSymbol(gotAddress, isAutogenerated=True)
                contextSym.isGot = gpAccess.isGot
                contextSym.isGotGlobal = gpAccess.isGotGlobal
                loOffset = self.instrAnalyzer.hiToLowDict.get(gotAccessOffset)
                if loOffset is not None:
                    if loOffset in self.instrAnalyzer.symbolLoInstrOffset:
                        del self.instrAnalyzer.symbolLoInstrOffset[loOffset]
                    if loOffset in self.instrAnalyzer.symbolInstrOffset:
                        del self.instrAnalyzer.symbolInstrOffset[loOffset]
            else:
                # GOT-locals need to be paired
                loOffset = self.instrAnalyzer.hiToLowDict.get(gotAccessOffset)
                if loOffset is not None:
                    loInstr = self.instructions[loOffset//4]
                    gotAddress += loInstr.getProcessedImmediate()
                    self.instrAnalyzer.symbolInstrOffset[loOffset] = gotAddress

                    symAccess = self.instrAnalyzer.symbolTypesOffsets.get(loOffset)
                    if symAccess is not None:
                        if gotAddress not in self.instrAnalyzer.possibleSymbolTypes:
                            self.instrAnalyzer.possibleSymbolTypes[gotAddress] = dict()
                        if symAccess not in self.instrAnalyzer.possibleSymbolTypes[gotAddress]:
                            self.instrAnalyzer.possibleSymbolTypes[gotAddress][symAccess] = 0
                        self.instrAnalyzer.possibleSymbolTypes[gotAddress][symAccess] += 1

                contextSym = self.addSymbol(gotAddress, isAutogenerated=True)
                contextSym.isGot = True
                contextSym.isGotLocal = True
            self.instrAnalyzer.symbolInstrOffset[gotAccessOffset] = gotAddress
            self.instrAnalyzer.referencedVrams.add(gotAddress)

        # Aditional lookup for unpaired GOT-locals
        if len(self.instrAnalyzer.gotAccessAddresses) > 0:
            for loOffset, gotAccessOffset in self.instrAnalyzer.lowToHiDict.items():
                gotAccess_ = self.instrAnalyzer.gotAccessAddresses.get(gotAccessOffset)
                if gotAccess_ is None:
                    continue

                gpAccess = self.context.gpAccesses.requestAddress(gotAccess_)
                if gpAccess is None:
                    common.Utils.eprint(2, f"0x{self.instructions[gotAccessOffset//4].vram:08X}", f"0x{gotAccess_:08X}", self.instructions[gotAccessOffset//4].disassemble())
                    continue

                if not gpAccess.isGotLocal:
                    continue

                gotAddress = gpAccess.address

                loInstr = self.instructions[loOffset//4]
                gotAddress += loInstr.getProcessedImmediate()
                self.instrAnalyzer.symbolInstrOffset[loOffset] = gotAddress

                symAccess = self.instrAnalyzer.symbolTypesOffsets.get(loOffset)
                if symAccess is not None:
                    if gotAddress not in self.instrAnalyzer.possibleSymbolTypes:
                        self.instrAnalyzer.possibleSymbolTypes[gotAddress] = dict()
                    if symAccess not in self.instrAnalyzer.possibleSymbolTypes[gotAddress]:
                        self.instrAnalyzer.possibleSymbolTypes[gotAddress][symAccess] = 0
                    self.instrAnalyzer.possibleSymbolTypes[gotAddress][symAccess] += 1

                contextSym = self.addSymbol(gotAddress, isAutogenerated=True)
                contextSym.isGot = True
                contextSym.isGotLocal = True
                self.instrAnalyzer.symbolInstrOffset[gotAccessOffset] = gotAddress
                self.instrAnalyzer.referencedVrams.add(gotAddress)


        for loOffset, symVram in self.instrAnalyzer.symbolLoInstrOffset.items():
            hiOffset = self.instrAnalyzer.lowToHiDict.get(loOffset)
            if hiOffset is not None and hiOffset in self.instrAnalyzer.gotAccessAddresses:
                if hiOffset in globalGotOffsets:
                    if loOffset in self.instrAnalyzer.symbolInstrOffset:
                        del self.instrAnalyzer.symbolInstrOffset[loOffset]
                    continue

                if hiOffset in self.instrAnalyzer.symbolInstrOffset:
                    symVram = self.instrAnalyzer.symbolInstrOffset[hiOffset]
                    self.instrAnalyzer.symbolLoInstrOffset[loOffset] = symVram

                if loOffset in self.instrAnalyzer.referencedJumpTableOffsets:
                    self.instrAnalyzer.referencedJumpTableOffsets[loOffset] = symVram

                if loOffset in self.instrAnalyzer.indirectFunctionCallOffsets:
                    self.instrAnalyzer.indirectFunctionCallOffsets[loOffset] = symVram
        return

    def _getRelocTypeForInstruction(self, instr: rabbitizer.Instruction, instrOffset: int, contextSym: common.ContextSymbol|None=None, gotHiLo: bool=False, gotSmall: bool=False) -> common.RelocType:
        if instr.canBeHi():
            if common.GlobalConfig.PIC:
                if contextSym is not None and gotHiLo:
                    if contextSym.isGotGlobal and contextSym.getTypeSpecial() == common.SymbolSpecialType.function:
                        return common.RelocType.MIPS_CALL_HI16
                    else:
                        return common.RelocType.MIPS_GOT_HI16
            return common.RelocType.MIPS_HI16

        if instr.rs in {rabbitizer.RegGprO32.gp, rabbitizer.RegGprN32.gp}:
            if not common.GlobalConfig.PIC or gotSmall:
                if instr.modifiesRt() and instr.rt in {rabbitizer.RegGprO32.gp, rabbitizer.RegGprN32.gp}:
                    # Shouldn't make a gprel access if the dst register is $gp too
                    return common.RelocType.MIPS_LO16
                return common.RelocType.MIPS_GPREL16

            if contextSym is not None:
                if contextSym.isGotGlobal and contextSym.getTypeSpecial() == common.SymbolSpecialType.function and instrOffset in self.instrAnalyzer.indirectFunctionCallOffsets:
                    return common.RelocType.MIPS_CALL16
                elif contextSym.isGot:
                    return common.RelocType.MIPS_GOT16
                else:
                    return common.RelocType.MIPS_GPREL16

        elif common.GlobalConfig.PIC:
            if contextSym is not None and gotHiLo:
                if contextSym.isGotGlobal and contextSym.getTypeSpecial() == common.SymbolSpecialType.function:
                    return common.RelocType.MIPS_CALL_LO16
                else:
                    return common.RelocType.MIPS_GOT_LO16
        return common.RelocType.MIPS_LO16

    def _generateRelocsFromInstructionAnalyzer(self) -> None:
        for instrOffset, address in self.instrAnalyzer.symbolInstrOffset.items():
            if self.context.isAddressBanned(address):
                continue

            contextSym = self.getSymbol(address)

            gotHiLo = False
            gotSmall = False
            if contextSym is None and address < 0 and common.GlobalConfig.PIC and common.GlobalConfig.GP_VALUE is not None:
                # Negative pointer may mean it is a weird GOT access
                gotAccess = common.GlobalConfig.GP_VALUE + address
                gpAccess = self.context.gpAccesses.requestAddress(gotAccess)
                if gpAccess is not None:
                    address = gpAccess.address
                    contextSym = self.getSymbol(address)
                    gotHiLo = True
                    gotSmall = gpAccess.isSmallSection
                else:
                    common.Utils.eprint(4, f"0x{self.instructions[instrOffset//4].vram:08X}", f"0x{gotAccess:08X}", self.instructions[instrOffset//4].disassemble())
                    pass

            if contextSym is None:
                continue

            if contextSym.isGotGlobal:
                if instrOffset not in self.instrAnalyzer.gotAccessAddresses and not gotHiLo:
                    continue

            instr = self.instructions[instrOffset//4]

            relocType = self._getRelocTypeForInstruction(instr, instrOffset, contextSym, gotHiLo, gotSmall)
            if relocType == common.RelocType.MIPS_GPREL16:
                contextSym.accessedAsGpRel = True
            self.relocs[instrOffset] = common.RelocationInfo(relocType, contextSym, address - contextSym.vram)

        for instrOffset in self.instrAnalyzer.cploadOffsets:
            # .cpload directive is meant to use the `_gp_disp` pseudo-symbol
            instr = self.instructions[instrOffset//4]

            relocType = self._getRelocTypeForInstruction(instr, instrOffset)
            self.relocs[instrOffset] = common.RelocationInfo(relocType, "_gp_disp")

        for instrOffset, gpInfo in self.instrAnalyzer.gpSets.items():
            if gpInfo is None:
                continue
            hiInstrOffset = gpInfo.hiOffset
            hiInstr = self.instructions[hiInstrOffset//4]
            instr = self.instructions[instrOffset//4]

            hiRelocType = self._getRelocTypeForInstruction(hiInstr, hiInstrOffset)
            relocType = self._getRelocTypeForInstruction(instr, instrOffset)
            if not common.GlobalConfig.PIC and gpInfo.value == common.GlobalConfig.GP_VALUE:
                self.relocs[hiInstrOffset] = common.RelocationInfo(hiRelocType, "_gp")
                self.relocs[instrOffset] = common.RelocationInfo(relocType, "_gp")
            else:
                # TODO: consider reusing the logic of the self.instrAnalyzer.symbolInstrOffset loop
                address = gpInfo.value
                if self.context.isAddressBanned(address):
                    continue

                contextSym = self.getSymbol(address)
                if contextSym is None:
                    continue

                self.relocs[hiInstrOffset] = common.RelocationInfo(hiRelocType, contextSym)
                self.relocs[instrOffset] = common.RelocationInfo(relocType, contextSym)

        for instrOffset, constant in self.instrAnalyzer.constantInstrOffset.items():
            instr = self.instructions[instrOffset//4]
            relocType = self._getRelocTypeForInstruction(instr, instrOffset)

            if relocType in {common.RelocType.MIPS_HI16, common.RelocType.MIPS_LO16}:
                # We can only do this kind of shenanigans for normal %hi/%lo relocs

                symbol = self.getConstant(constant)
                if symbol is not None:
                    self.relocs[instrOffset] = common.RelocationInfo(relocType, symbol.getName())
                elif common.GlobalConfig.SYMBOL_FINDER_FILTERED_ADDRESSES_AS_HILO:
                    self.relocs[instrOffset] = common.RelocationInfo(relocType, f"0x{constant:X}")
                else:
                    # Pretend this pair is a constant
                    loInstr = instr
                    if instr.canBeHi():
                        loInstr = self.instructions[self.instrAnalyzer.hiToLowDict[instrOffset] // 4]

                    generatedReloc = self._generateHiLoConstantReloc(constant, instr, loInstr)
                    if generatedReloc is not None:
                        self.relocs[instrOffset] = generatedReloc
            else:
                comment = f"Failed to symbolize address 0x{constant:08X} for {relocType.getPercentRel()}. Make sure this address is within the recognized valid address space."
                if relocType in {common.RelocType.MIPS_GPREL16, common.RelocType.MIPS_GOT16}:
                    if common.GlobalConfig.GP_VALUE is None:
                        comment += f" Please specify a gp_value."
                    elif not self.context.isInTotalVramRange(common.GlobalConfig.GP_VALUE):
                        comment += f" The provided gp_value (0x{common.GlobalConfig.GP_VALUE:08X}) seems wrong."
                self.endOfLineComment[instrOffset//4] = f" /* {comment} */"

        for instrOffset, targetVram in self.instrAnalyzer.funcCallInstrOffsets.items():
            instr = self.instructions[instrOffset//4]
            is_j = instr.isJumpWithAddress() and not instr.doesLink()
            funcSym = self.getSymbolFromAnySegment(targetVram, lambda contextSym: contextSym.type == common.SymbolSpecialType.function or contextSym.type is None or (is_j and isinstance(contextSym.type, common.SymbolSpecialType) and contextSym.type.isTargetLabel()), tryPlusOffset=False)
            if funcSym is None:
                continue
            self.relocs[instrOffset] = common.RelocationInfo(common.RelocType.MIPS_26, funcSym)


    def analyze(self) -> None:
        self.contextSym.inFileOffset = self.inFileOffset
        if self.parent is not None:
            self.contextSym.parentFileName = self.parent.getName()

        if not common.GlobalConfig.DISASSEMBLE_UNKNOWN_INSTRUCTIONS and self.hasUnimplementedIntrs:
            offset = 0
            for instr in self.instructions:
                currentVram = self.getVramOffset(offset)
                currentVrom = self.getVromOffset(offset)
                contextSym = self.getSymbol(currentVram, vromAddress=currentVrom, tryPlusOffset=False)
                if contextSym is not None:
                    contextSym.isDefined = True
                offset += 4
            return

        self._runInstructionAnalyzer()

        self._postProcessGotAccesses()
        self._processElfRelocSymbols()

        # Branches
        for instrOffset, targetBranchVram in self.instrAnalyzer.branchInstrOffsets.items():
            if common.GlobalConfig.INPUT_FILE_TYPE == common.InputFileType.ELF:
                if self.getVromOffset(instrOffset) in self.context.globalRelocationOverrides:
                    # Avoid creating wrong symbols on elf files
                    continue
            branch = self.instrAnalyzer.branchTargetInstrOffsets[instrOffset]
            labelSym = self.addBranchLabel(targetBranchVram, isAutogenerated=True, symbolVrom=self.getVromOffset(branch))
            labelSym.referenceCounter += 1
            labelSym.referenceFunctions.add(self.contextSym)
            labelSym.parentFunction = self.contextSym
            labelSym.parentFileName = self.contextSym.parentFileName
            self.contextSym.branchLabels.add(labelSym.vram, labelSym)

        # Function calls
        for instrOffset, targetVram in self.instrAnalyzer.funcCallInstrOffsets.items():
            if self.context.isAddressBanned(targetVram):
                continue

            if common.GlobalConfig.INPUT_FILE_TYPE == common.InputFileType.ELF:
                if self.getVromOffset(instrOffset) in self.context.globalRelocationOverrides:
                    # Avoid creating wrong symbols on elf files
                    continue
            funcSym = self.addFunction(targetVram, isAutogenerated=True)
            funcSym.referenceCounter += 1
            funcSym.referenceFunctions.add(self.contextSym)


        # if not self.isRsp and common.GlobalConfig.INPUT_FILE_TYPE != common.InputFileType.ELF:
        #     for outsideInstrOffset in self.instrAnalyzer.funcCallOutsideRangesOffsets.keys():
        #         self.isLikelyHandwritten = True
        #         self.endOfLineComment[outsideInstrOffset//4] = " /* function call outside to the known address range */"

        # Symbols
        for loOffset, symVram in self.instrAnalyzer.symbolLoInstrOffset.items():
            if self.context.isAddressBanned(symVram):
                continue

            if common.GlobalConfig.INPUT_FILE_TYPE == common.InputFileType.ELF:
                if self.getVromOffset(loOffset) in self.context.globalRelocationOverrides:
                    # Avoid creating wrong symbols on elf files
                    continue

            symAccessDict = self.instrAnalyzer.possibleSymbolTypes.get(symVram, dict())
            symAccess = None
            if len(symAccessDict) == 1:
                # Infer type info if there's only one access type
                symAccess = list(symAccessDict)[0]

            contextSym = self.addSymbol(symVram, isAutogenerated=True, allowAddendInstead=True)
            if contextSym is not None:
                # TODO: do this in a less ugly way
                if contextSym.address != symVram:
                    if contextSym.address % 4 != 0 or symVram % 4 != 0:
                        if contextSym.getType() in {"u16", "s16", "u8", "u8"} or (symAccess is not None and symAccess.accessType in {rabbitizer.AccessType.BYTE, rabbitizer.AccessType.SHORT}):
                            if not (contextSym.getSize() > 4):
                                if contextSym.userDeclaredSize is None or symVram >= contextSym.address + contextSym.userDeclaredSize:
                                    if symAccess is not None:
                                        contextSym.setAccessTypeIfUnset(symAccess.accessType, symAccess.unsignedMemoryAccess)
                                    contextSym.setFirstLoAccessIfUnset(loOffset)
                                    contextSym = self.addSymbol(symVram, isAutogenerated=True)

            contextSym.referenceCounter += 1
            contextSym.referenceFunctions.add(self.contextSym)
            contextSym.setFirstLoAccessIfUnset(loOffset)
            if symAccess is not None:
                contextSym.setAccessTypeIfUnset(symAccess.accessType, symAccess.unsignedMemoryAccess)
                if contextSym.isAutogenerated:
                    # Handle mips1 doublefloats
                    if contextSym.accessType == rabbitizer.AccessType.FLOAT and common.GlobalConfig.ABI == common.Abi.O32:
                        instr = self.instructions[loOffset//4]
                        if instr.doesDereference() and instr.isFloat() and not instr.isDouble():
                            if instr.ft.value % 2 != 0:
                                # lwc1/swc1 with an odd fpr means it is an mips1 doublefloats reference
                                if symVram % 8 != 0:
                                    # We need to remove the the symbol pointing to the middle of this doublefloats
                                    got = contextSym.isGot
                                    gotLocal = contextSym.isGotLocal
                                    gotGlobal = contextSym.isGotGlobal
                                    self.removeSymbol(symVram)

                                    # Align down to 8
                                    symVram = (symVram >> 3) << 3
                                    contextSym = self.addSymbol(symVram, isAutogenerated=True)
                                    contextSym.referenceCounter += 1
                                    contextSym.referenceFunctions.add(self.contextSym)
                                    contextSym.setFirstLoAccessIfUnset(loOffset)
                                    contextSym.isGot = got
                                    contextSym.isGotLocal = gotLocal
                                    contextSym.isGotGlobal = gotGlobal
                                contextSym.accessType = rabbitizer.AccessType.DOUBLEFLOAT
                                contextSym.unsignedAccessType = False
                                contextSym.isMips1Double = True

        self._generateRelocsFromInstructionAnalyzer()

        # Jump tables
        for targetVram in self.instrAnalyzer.referencedJumpTableOffsets.values():
            jumpTable = self.addJumpTable(targetVram, isAutogenerated=True)
            jumpTable.parentFunction = self.contextSym
            self.contextSym.jumpTables.add(jumpTable.vram, jumpTable)

        # To debug jumptable rejection change this check to `True`
        if False:
            for jrInstrOffset, (referenceOffset, jtblAddress, branchOffset) in self.instrAnalyzer.rejectedjumpRegisterIntrOffset.items():
                self.endOfLineComment[jrInstrOffset//4] = f" /* Jumping to something at address 0x{jtblAddress:08X} (inferred from 0x{self.getVromOffset(referenceOffset):X}). Jumptable rejected by instruction at vrom 0x{self.getVromOffset(branchOffset):X} */"

        if self.isLikelyHandwritten:
            for instr in self.instructions:
                instr.inHandwrittenFunction = self.isLikelyHandwritten

        self.contextSym.autodetectedSize = self.sizew*4

        self.referencedVrams = self.instrAnalyzer.referencedVrams


    def countExtraPadding(self) -> int:
        count = 0
        if self.contextSym.userDeclaredSize == self.sizew * 4:
            return 0

        for i in range(len(self.instructions)-1, 0, -1):
            instr = self.instructions[i]
            nextInstr = self.instructions[i-1]

            if nextInstr.hasDelaySlot():
                return count

            if not instr.isNop():
                return count

            count += 1
        return count


    def countDiffOpcodes(self, other: SymbolFunction) -> int:
        result = 0
        for i in range(min(self.nInstr, other.nInstr)):
            if not self.instructions[i].sameOpcode(other.instructions[i]):
                result += 1
        return result

    def countSameOpcodeButDifferentArguments(self, other: SymbolFunction) -> int:
        result = 0
        for i in range(min(self.nInstr, other.nInstr)):
            instr1 = self.instructions[i]
            instr2 = other.instructions[i]
            if instr1.sameOpcodeButDifferentArguments(instr2):
                result += 1
        return result

    def blankOutDifferences(self, other_func: SymbolFunction) -> bool:
        if not common.GlobalConfig.REMOVE_POINTERS:
            return False

        was_updated = False

        for i in range(min(self.nInstr, other_func.nInstr)):
            instr1 = self.instructions[i]
            instr2 = other_func.instructions[i]
            if instr1.sameOpcodeButDifferentArguments(instr2):
                instr1.blankOut()
                instr2.blankOut()
                was_updated = True

        return was_updated

    def removePointers(self) -> bool:
        if not common.GlobalConfig.REMOVE_POINTERS:
            return False

        was_updated = False

        for instructionOffset in self.instrAnalyzer.symbolInstrOffset:
            self.instructions[instructionOffset//4].blankOut()
        was_updated = len(self.instrAnalyzer.symbolInstrOffset) > 0 or was_updated

        for fileOffset in self.pointersOffsets:
            index = (fileOffset - self.inFileOffset)//4
            if index < 0:
                continue
            if index >= self.nInstr:
                continue
            self.instructions[index].blankOut()

        if common.GlobalConfig.IGNORE_BRANCHES:
            for instructionOffset in self.instrAnalyzer.branchInstrOffsets:
                self.instructions[instructionOffset//4].blankOut()
            was_updated = len(self.instrAnalyzer.branchInstrOffsets) > 0 or was_updated

        self.pointersRemoved = True

        return was_updated

    def removeTrailingNops(self) -> bool:
        was_updated = False
        first_nop = self.nInstr

        for i in range(self.nInstr-1, 0-1, -1):
            instr = self.instructions[i]
            if not instr.isNop():
                if instr.isReturn():
                    first_nop += 1
                break
            first_nop = i

        if first_nop < self.nInstr:
            was_updated = True
            del self.instructions[first_nop:]
        return was_updated

    def _generateHiLoConstantReloc(self, constantValue: int, currentInstr: rabbitizer.Instruction, loInstr: rabbitizer.Instruction|None) -> common.RelocationInfo|None:
        if loInstr is None:
            if currentInstr.canBeHi():
                return common.RelocationInfo(common.RelocType.CUSTOM_CONSTANT_HI, f"0x{constantValue:X}")
            return None

        if loInstr.canBeLo():
            if loInstr.isUnsigned():
                if currentInstr.canBeHi():
                    return common.RelocationInfo(common.RelocType.CUSTOM_CONSTANT_HI, f"0x{constantValue:X}")
                if currentInstr.canBeLo():
                    return common.RelocationInfo(common.RelocType.CUSTOM_CONSTANT_LO, f"0x{constantValue:X}")
                return None
            else:
                hiHalf = constantValue >> 16
                loHalf = constantValue & 0xFFFF
                if loHalf < 0x8000:
                    # positive lo half
                    if currentInstr.canBeHi():
                        return common.RelocationInfo(common.RelocType.CUSTOM_CONSTANT_HI, f"0x{constantValue:X}")
                    if currentInstr.canBeLo():
                        return common.RelocationInfo(common.RelocType.CUSTOM_CONSTANT_LO, f"0x{constantValue:X}")
                else:
                    # negative lo half
                    # loHalf = rabbitizer.Utils.from2Complement(loHalf, 16)
                    pass
        return None


    def _getImmOverrideForInstruction(self, instr: rabbitizer.Instruction, instrOffset: int, isSplittedSymbol: bool=False) -> tuple[str|None, common.RelocationInfo|None]:
        if self.pointersRemoved:
            return None, None

        relocInfo = self.getReloc(instrOffset, instr)
        if relocInfo is not None:
            if relocInfo.isRelocNone():
                if instr.isJumpWithAddress():
                    return f"0x{instr.getInstrIndexAsVram():08X}", relocInfo
            else:
                ignoredRelocs = set()
                if self.gpRelHack:
                    ignoredRelocs.add(common.RelocType.MIPS_GPREL16)
                return relocInfo.getNameWithReloc(isSplittedSymbol=isSplittedSymbol, ignoredRelocs=ignoredRelocs), relocInfo

        if instr.isBranch() or instr.isUnconditionalBranch():
            if common.GlobalConfig.IGNORE_BRANCHES:
                return None, None
            branchOffset = instr.getBranchOffsetGeneric()
            targetBranchVram = self.getVramOffset(instrOffset + branchOffset)
            labelSymbol = self.getSymbol(targetBranchVram, tryPlusOffset=False)
            if labelSymbol is not None:
                return labelSymbol.getName(), None
            return None, None

        if instr.hasOperandAlias(rabbitizer.OperandType.cpu_immediate):
            if instrOffset in self.instrAnalyzer.symbolInstrOffset:
                address = self.instrAnalyzer.symbolInstrOffset[instrOffset]
                relocInfo = self._generateHiLoConstantReloc(address, instr, instr)
                if relocInfo is not None:
                    return relocInfo.getNameWithReloc(isSplittedSymbol=isSplittedSymbol), relocInfo

            elif instr.canBeHi():
                # Unpaired LUI
                relocInfo = self._generateHiLoConstantReloc(instr.getProcessedImmediate()<<16, instr, None)
                if relocInfo is not None:
                    return relocInfo.getNameWithReloc(isSplittedSymbol=isSplittedSymbol), relocInfo

        return None, None

    def getLabelForOffset(self, instructionOffset: int, migrate: bool=False) -> str:
        if common.GlobalConfig.IGNORE_BRANCHES or instructionOffset == 0:
            # Skip over this function to avoid duplication
            return ""

        currentVram = self.getVramOffset(instructionOffset)
        currentVrom = self.getVromOffset(instructionOffset)
        labelSym = self.getSymbol(currentVram, vromAddress=currentVrom, tryPlusOffset=False)

        if labelSym is None or labelSym.overlayCategory != self.overlayCategory:
            return ""

        labelSym.isDefined = True
        labelSym.sectionType = self.sectionType
        labelSym.vromAddress = currentVrom
        labelSymType = labelSym.getTypeSpecial()

        useLabelMacro = labelSymType is None or labelSymType == common.SymbolSpecialType.function or (labelSymType == common.SymbolSpecialType.jumptablelabel and not migrate) or labelSymType == common.SymbolSpecialType.gccexcepttablelabel
        if not useLabelMacro:
            if common.GlobalConfig.ASM_GLOBALIZE_TEXT_LABELS_REFERENCED_BY_NON_JUMPTABLE:
                # Check if any non-jumptable symbol references this label
                for otherSym in labelSym.referenceSymbols:
                    if otherSym.getTypeSpecial() != common.SymbolSpecialType.jumptable:
                        useLabelMacro = True
                        break

        if useLabelMacro:
            label = labelSym.getReferenceeSymbols()
            labelMacro = labelSym.getLabelMacro(isInMiddleLabel=True)
            if labelMacro is not None:
                label += f"{labelMacro} {labelSym.getName()}{common.GlobalConfig.LINE_ENDS}"
            if common.GlobalConfig.ASM_TEXT_FUNC_AS_LABEL:
                label += f"{labelSym.getName()}:{common.GlobalConfig.LINE_ENDS}"
        else:
            label = labelSym.getName() + ":" + common.GlobalConfig.LINE_ENDS
        label = (" " * common.GlobalConfig.ASM_INDENTATION_LABELS) + label
        return label

    def _emitInstruction(self, instr: rabbitizer.Instruction, instructionOffset: int, wasLastInstABranch: bool, isSplittedSymbol: bool=False) -> str:
        immOverride, relocInfo = self._getImmOverrideForInstruction(instr, instructionOffset, isSplittedSymbol=isSplittedSymbol)
        comment = self.generateAsmLineComment(instructionOffset, instr.getRaw())
        extraLJust = 0

        if wasLastInstABranch:
            extraLJust = -1
            comment += " "

        line = instr.disassemble(immOverride, extraLJust=extraLJust)

        if self.gpRelHack:
            # Get rid of `%gp_rel` and `$gp` since old assemblers don't support `%gp_rel`.
            #
            # We convert the explicit instructions with relocations into macro/pseudo
            # instructions and hope for the assembler to do the right thing.
            #
            # A few examples for the conversions (right being the macro instructions):
            # `lw     $v0, %gp_rel(example_var)($gp)` -> `lw     $v0, (example_var)`
            # `addiu  $v0, $gp, %gp_rel(example_var)` -> `la     $v0, (example_var)`
            #
            # Those assemblers will actually assemble those macro instructions into the
            # proper ones with gp_rel relocations only if they can also see the symbol
            # defined on the same assembly file and its size fits within the passed `-G`
            # parameter. It is the user's responsability to provide those definitions to
            # the assembler.
            if relocInfo is not None and relocInfo.relocType == common.RelocType.MIPS_GPREL16:
                if instr.canBeLo() and instr.doesDereference():
                    line = line.replace("($gp)", "").replace("($28)", "")
                elif instr.uniqueId == rabbitizer.InstrId.cpu_addiu:
                    line = line.replace("addiu ", "la    ").replace(", $gp, ", ", ").replace(", $28, ", ", ")

                endComment = self.endOfLineComment.get(instructionOffset//4, "")
                if " /* gp_rel: " not in endComment:
                    endComment += f" /* gp_rel: {immOverride} */"
                    self.endOfLineComment[instructionOffset//4] = endComment

        return f"{comment}  {line}"


    def _emitCpload(self, instr: rabbitizer.Instruction, instructionOffset: int, wasLastInstABranch: bool, isSplittedSymbol: bool=False) -> str:
        output = ""

        cpload = self.instrAnalyzer.cploads.get(instructionOffset)
        if cpload is not None:
            hiInstr = self.instructions[cpload.hiOffset//4]
            loInstr = self.instructions[cpload.loOffset//4]
            gpDisp = hiInstr.getProcessedImmediate() << 16
            gpDisp += loInstr.getProcessedImmediate()
            output += f"/* _gp_disp: 0x{gpDisp:X} */{common.GlobalConfig.LINE_ENDS}"
            if common.GlobalConfig.EMIT_CPLOAD:
                assert cpload.reg is not None
                output += f".cpload ${cpload.reg.name}"
            else:
                output += self._emitInstruction(instr, instructionOffset, wasLastInstABranch, isSplittedSymbol=isSplittedSymbol)
        else:
            if not common.GlobalConfig.EMIT_CPLOAD:
                output += self._emitInstruction(instr, instructionOffset, wasLastInstABranch, isSplittedSymbol=isSplittedSymbol)
            # don't emit the other instructions which are part of .cpload if the directive was emitted
        return output

    def disassemble(self, migrate: bool=False, useGlobalLabel: bool=True, isSplittedSymbol: bool=False) -> str:
        output = ""

        if migrate:
            output += self.getSpimdisasmVersionString()

        if not common.GlobalConfig.DISASSEMBLE_UNKNOWN_INSTRUCTIONS:
            if self.hasUnimplementedIntrs:
                return self.disassembleAsData(useGlobalLabel=useGlobalLabel, isSplittedSymbol=isSplittedSymbol)

        if not common.GlobalConfig.PIC and self.gpRelHack and len(self.instrAnalyzer.gpReferencedSymbols) > 0:
            output += f"/* Symbols accessed via $gp register */{common.GlobalConfig.LINE_ENDS}"
            for gpAddress in self.instrAnalyzer.gpReferencedSymbols:
                gpSym = self.getSymbol(gpAddress, tryPlusOffset=True)
                if gpSym is not None:
                    output += f".extern {gpSym.getName()}, 1{common.GlobalConfig.LINE_ENDS}"
            output += common.GlobalConfig.LINE_ENDS

        output += self.contextSym.getReferenceeSymbols()
        output += self.getPrevAlignDirective(0)

        if self.isLikelyHandwritten and common.GlobalConfig.ASM_COMMENT:
            if not self.isRsp:
                # RSP functions are always handwritten, so this is redundant
                output += "/* Handwritten function */" + common.GlobalConfig.LINE_ENDS

        self._generateRelocsFromInstructionAnalyzer()

        symName = self.getName()

        symSize = self.contextSym.getSize()
        if self.contextSym.userDeclaredSize is None:
            # Fixup symbol size to avoid counting padding as part of the symbol
            # on the emitted size and end directives.
            symSize -= 4 * self.countExtraPadding()

        output += self.getSymbolAsmDeclaration(symName, useGlobalLabel)

        wasLastInstABranch = False
        instructionOffset = 0
        for instr in self.instructions:
            currentLine = self.getLabelForOffset(instructionOffset, migrate=migrate)

            isCpload = instructionOffset in self.instrAnalyzer.cploadOffsets
            if isCpload:
                currentLine += self._emitCpload(instr, instructionOffset, wasLastInstABranch, isSplittedSymbol=isSplittedSymbol)
            else:
                currentLine += self._emitInstruction(instr, instructionOffset, wasLastInstABranch, isSplittedSymbol=isSplittedSymbol)

            currentLine += self.getEndOfLineComment(instructionOffset//4)
            if currentLine != "":
                currentLine += common.GlobalConfig.LINE_ENDS

            if common.GlobalConfig.EMIT_INLINE_RELOC:
                relocInfo = self.getReloc(instructionOffset, instr)
                currentLine += self.relocToInlineStr(relocInfo, isSplittedSymbol=isSplittedSymbol)

            output += currentLine

            wasLastInstABranch = instr.hasDelaySlot()
            instructionOffset += 4

            if instructionOffset == symSize:
                if common.GlobalConfig.ASM_TEXT_END_LABEL:
                    output += f"{common.GlobalConfig.ASM_TEXT_END_LABEL} {self.getName()}" + common.GlobalConfig.LINE_ENDS

                output += self.getSizeDirective(symName)

        nameEnd = self.getNameEnd()
        if nameEnd is not None:
            output += self.getSymbolAsmDeclaration(nameEnd, useGlobalLabel)

        return output

    def disassembleAsData(self, useGlobalLabel: bool=True, isSplittedSymbol: bool=False) -> str:
        self.contextSym.setTypeSpecial("u32", isAutogenerated=True)
        self.words = []
        for i, instr in enumerate(self.instructions):
            if not instr.isImplemented() or not instr.isValid():
                self.endOfLineComment[i] = " /* invalid instruction */"
            self.words.append(instr.getRaw())
        return super().disassembleAsData(useGlobalLabel=useGlobalLabel, isSplittedSymbol=isSplittedSymbol)
