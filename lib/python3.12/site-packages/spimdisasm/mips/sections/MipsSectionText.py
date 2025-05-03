#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

import rabbitizer

from ... import common

from .. import symbols
from ..MipsFileBase import FileBase

from . import SectionBase


class SectionText(SectionBase):
    def __init__(self, context: common.Context, vromStart: int, vromEnd: int, vram: int, filename: str, array_of_bytes: bytes, segmentVromStart: int, overlayCategory: str|None) -> None:
        super().__init__(context, vromStart, vromEnd, vram, filename, common.Utils.bytesToWords(array_of_bytes, vromStart, vromEnd), common.FileSectionType.Text, segmentVromStart, overlayCategory)

        self.instrCat: rabbitizer.Enum = rabbitizer.InstrCategory.CPU
        self.detectRedundantFunctionEnd: bool|None = None
        self.gpRelHack: bool = False
        """Get rid of `%gp_rel` and `$gp` since old assemblers don't support `%gp_rel`."""

        self.enableStringGuessing = False


    @property
    def nFuncs(self) -> int:
        return len(self.symbolList)

    @staticmethod
    def wordListToInstructions(wordList: list[int], currentVram: int|None, instrCat: rabbitizer.Enum) -> list[rabbitizer.Instruction]:
        instrsList: list[rabbitizer.Instruction] = list()
        for word in wordList:
            instr = rabbitizer.Instruction(word, category=instrCat)

            if currentVram is not None:
                instr.vram = currentVram
                currentVram += 4

            instrsList.append(instr)
        return instrsList


    def getAsmPrelude_instructionDirectives(self) -> str:
        output = ""

        output += f"/* assembler directives */{common.GlobalConfig.LINE_ENDS}"
        output += f".set noat      /* allow manual use of $at */{common.GlobalConfig.LINE_ENDS}"
        output += f".set noreorder /* do not insert nops after branches */{common.GlobalConfig.LINE_ENDS}"
        if common.GlobalConfig.ARCHLEVEL >= common.ArchLevel.MIPS3:
            output += f".set gp=64     /* allow use of 64-bit general purpose registers */{common.GlobalConfig.LINE_ENDS}"
        output += common.GlobalConfig.LINE_ENDS
        return output


    def tryDetectRedundantFunctionEnd(self) -> bool:
        if common.GlobalConfig.COMPILER != common.Compiler.IDO:
            return False

        if self.detectRedundantFunctionEnd is None:
            return common.GlobalConfig.DETECT_REDUNDANT_FUNCTION_END
        return self.detectRedundantFunctionEnd


    def _findFunctions_branchChecker(self, instructionOffset: int, instr: rabbitizer.Instruction, funcsStartsList: list[int], unimplementedInstructionsFuncList: list[bool], farthestBranch: int, isLikelyHandwritten: bool, isInstrImplemented: bool) -> tuple[int, bool]:
        haltFunctionSearching = False

        if instr.isJumpWithAddress():
            # If this instruction is a jump and it is jumping to a function then
            # don't treat it as a branch, it is probably actually being used as
            # a jump
            targetVram = instr.getInstrIndexAsVram()
            auxSym = self.getSymbol(targetVram, tryPlusOffset=False, checkGlobalSegment=False)

            if auxSym is not None and auxSym.isTrustableFunction(self.instrCat == rabbitizer.InstrCategory.RSP):
                return farthestBranch, haltFunctionSearching

        if instr.doesLink():
            # This is used more as a function call than as an actual branch
            return farthestBranch, haltFunctionSearching

        branchOffset = instr.getBranchOffsetGeneric()
        if branchOffset > farthestBranch:
            # keep track of the farthest branch target
            farthestBranch = branchOffset
        if branchOffset < 0:
            if branchOffset + instructionOffset < 0:
                # Whatever we are reading is not a valid instruction
                if not instr.isJump(): # Make an exception for `j`
                    haltFunctionSearching = True
            # make sure to not branch outside of the current function
            if not isLikelyHandwritten and isInstrImplemented:
                j = len(funcsStartsList) - 1
                while j >= 0:
                    if branchOffset + instructionOffset < 0:
                        break
                    otherFuncStartOffset = funcsStartsList[j] * 4
                    if (branchOffset + instructionOffset) < otherFuncStartOffset:
                        vram = self.getVramOffset(otherFuncStartOffset)
                        vromAddress = self.getVromOffset(otherFuncStartOffset)
                        funcSymbol = self.getSymbol(vram, vromAddress=vromAddress, tryPlusOffset=False, checkGlobalSegment=False)
                        if funcSymbol is not None and funcSymbol.isTrustableFunction(self.instrCat == rabbitizer.InstrCategory.RSP):
                            j -= 1
                            continue
                        del funcsStartsList[j]
                        del unimplementedInstructionsFuncList[j-1]
                    else:
                        break
                    j -= 1
        return farthestBranch, haltFunctionSearching

    def _findFunctions_checkFunctionHalted(self, instructionOffset: int, currentVrom: int, currentVram: int, currentInstructionStart: int) -> bool:
        if instructionOffset == currentInstructionStart:
            # Check if we have a function after the first instruction of the current function.
            # This can happen when a garbage instruction was emitted and it was misinterpreted as
            # the beginning of a function. This seems to be a common situation section padding on SN64.
            funcSymbol = self.getSymbol(currentVram + 4, vromAddress=currentVrom + 4, tryPlusOffset=False, checkGlobalSegment=False)
            if funcSymbol is not None and funcSymbol.isTrustableFunction(self.instrCat == rabbitizer.InstrCategory.RSP):
                if funcSymbol.vromAddress is None or currentVrom + 4 == funcSymbol.vromAddress:
                    return True

        return False

    def _findFunctions_checkFunctionEnded(self, instructionOffset: int, instr: rabbitizer.Instruction, index: int, currentVrom: int, currentVram: int, currentFunctionSym: common.ContextSymbol|None, farthestBranch: int, currentInstructionStart: int, isLikelyHandwritten: bool, instrsList: list[rabbitizer.Instruction], nInstr: int) -> tuple[bool, bool, bool]:
        functionEnded = False
        prevFuncHadUserDeclaredSize = False
        functionHalted = False

        # Try to find the end of the function
        if currentFunctionSym is not None and currentFunctionSym.userDeclaredSize is not None:
            # If the function has a size set by the user then only use that and ignore the other ways of determining function-ends
            if instructionOffset + 8 == currentInstructionStart + currentFunctionSym.getSize():
                functionEnded = True
                prevFuncHadUserDeclaredSize = True
        elif self._findFunctions_checkFunctionHalted(instructionOffset, currentVrom, currentVram, currentInstructionStart):
            functionEnded = True
            functionHalted = True
        else:
            funcSymbol = self.getSymbol(currentVram + 8, vromAddress=currentVrom + 8, tryPlusOffset=False, checkGlobalSegment=False)
            # If there's another function after this then the current function has ended
            if funcSymbol is not None and funcSymbol.isTrustableFunction(self.instrCat == rabbitizer.InstrCategory.RSP):
                if funcSymbol.vromAddress is None or currentVrom + 8 == funcSymbol.vromAddress:
                    functionEnded = True

            if not functionEnded and not (farthestBranch > 0) and instr.isJump():
                if instr.isReturn():
                    # Found a jr $ra and there are no branches outside of this function
                    if self.tryDetectRedundantFunctionEnd():
                        # IDO -g, -g1 and -g2 can generate a redundant and unused `jr $ra; nop`. In normal conditions this would be detected
                        # as its own separate empty function, which would cause issues on a decompilation project.
                        # In other words, we try to detect the following pattern, and the last two instructions not being a function
                        # already referenced or user-declared.
                        # jr         $ra
                        #  nop
                        # jr         $ra
                        #  nop
                        redundantPatternDetected = False
                        if index + 3 < nInstr:
                            instr1 = instrsList[index+1]
                            instr2 = instrsList[index+2]
                            instr3 = instrsList[index+3]
                            if funcSymbol is None and instr1.isNop() and instr2.isReturn() and instr3.isNop():
                                redundantPatternDetected = True
                        if not redundantPatternDetected:
                            functionEnded = True
                    else:
                        functionEnded = True
                elif instr.isJumptableJump():
                    # Usually jumptables, ignore
                    pass
                elif not instr.doesLink():
                    if isLikelyHandwritten or self.instrCat == rabbitizer.InstrCategory.RSP:
                        # I don't remember the reasoning of this condition...
                        functionEnded = True
                    elif instr.isJumpWithAddress():
                        # If this instruction is a jump and it is jumping to a function then
                        # we can consider this as a function end. This can happen as a
                        # tail-optimization in modern compilers
                        if not rabbitizer.config.toolchainTweaks_treatJAsUnconditionalBranch:
                            functionEnded = True
                        else:
                            targetVram = instr.getInstrIndexAsVram()
                            auxSym = self.getSymbol(targetVram, tryPlusOffset=False, checkGlobalSegment=False)
                            if auxSym is not None and auxSym.isTrustableFunction(self.instrCat == rabbitizer.InstrCategory.RSP):
                                functionEnded = True

        return functionEnded, prevFuncHadUserDeclaredSize, functionHalted

    def _findFunctions(self, instrsList: list[rabbitizer.Instruction]) -> tuple[list[int], list[bool]]:
        nInstr = len(instrsList)

        if nInstr == 0:
            return [0], [False]

        functionEnded = False
        functionHalted = False
        farthestBranch = 0
        funcsStartsList: list[int] = [0]
        unimplementedInstructionsFuncList: list[bool] = []

        instructionOffset = 0
        currentInstructionStart = 0
        currentFunctionSym = self.getSymbol(self.getVramOffset(instructionOffset), vromAddress=self.getVromOffset(instructionOffset), tryPlusOffset=False, checkGlobalSegment=False)

        isLikelyHandwritten = self.isHandwritten

        isInstrImplemented = True
        index = 0

        if instrsList[0].isNop():
            # Loop over until we find a instruction that isn't a nop
            while index < nInstr:
                if currentFunctionSym is not None:
                    break

                instr = instrsList[index]
                if not instr.isNop():
                    break
                index += 1
                instructionOffset += 4

                currentInstructionStart = instructionOffset
                currentFunctionSym = self.getSymbol(self.getVramOffset(instructionOffset), vromAddress=self.getVromOffset(instructionOffset), tryPlusOffset=False, checkGlobalSegment=False)

            if index != 0:
                funcsStartsList.append(index)
                unimplementedInstructionsFuncList.append(not isInstrImplemented)

        prevFuncHadUserDeclaredSize = False

        while index < nInstr:
            instr = instrsList[index]
            if not instr.isImplemented() or not instr.isValid():
                isInstrImplemented = False

            if functionEnded:
                functionEnded = False

                isLikelyHandwritten = self.isHandwritten
                if not functionHalted:
                    index += 1
                    instructionOffset += 4
                functionHalted = False

                auxSym = self.getSymbol(self.getVramOffset(instructionOffset), vromAddress=self.getVromOffset(instructionOffset), tryPlusOffset=False, checkGlobalSegment=False)

                # Loop over until we find a instruction that isn't a nop
                while index < nInstr:
                    if auxSym is not None:
                        break

                    instr = instrsList[index]
                    if not instr.isNop():
                        break
                    index += 1
                    instructionOffset += 4

                    auxSym = self.getSymbol(self.getVramOffset(instructionOffset), vromAddress=self.getVromOffset(instructionOffset), tryPlusOffset=False, checkGlobalSegment=False)

                currentInstructionStart = instructionOffset
                currentFunctionSym = auxSym

                funcsStartsList.append(index)
                unimplementedInstructionsFuncList.append(not isInstrImplemented)
                if index >= nInstr:
                    break
                if prevFuncHadUserDeclaredSize:
                    auxSym = self.addFunction(self.getVramOffset(instructionOffset), isAutogenerated=True, symbolVrom=self.getVromOffset(instructionOffset))
                    auxSym.isAutocreatedSymFromOtherSizedSym = True
                prevFuncHadUserDeclaredSize = False
                instr = instrsList[index]
                isInstrImplemented = instr.isImplemented() and instr.isValid()

            currentVram = self.getVramOffset(instructionOffset)
            currentVrom = self.getVromOffset(instructionOffset)

            if self.instrCat != rabbitizer.InstrCategory.RSP and not isLikelyHandwritten:
                isLikelyHandwritten = instr.isLikelyHandwritten()

            if instr.isBranch() or instr.isUnconditionalBranch():
                farthestBranch, haltFunctionSearching = self._findFunctions_branchChecker(instructionOffset, instr, funcsStartsList, unimplementedInstructionsFuncList, farthestBranch, isLikelyHandwritten, isInstrImplemented)
                if haltFunctionSearching:
                    break

            functionEnded, prevFuncHadUserDeclaredSize, functionHalted = self._findFunctions_checkFunctionEnded(instructionOffset, instr, index, currentVrom, currentVram, currentFunctionSym, farthestBranch, currentInstructionStart, isLikelyHandwritten, instrsList, nInstr)

            index += 1
            farthestBranch -= 4
            instructionOffset += 4

        unimplementedInstructionsFuncList.append(not isInstrImplemented)
        return funcsStartsList, unimplementedInstructionsFuncList

    def _findCalls(self, instrsList: list[rabbitizer.Instruction]) -> None:
        # A simple pass to gather function calls.
        # Hopefully should improve function starts found by `_findFunctions`

        for instr in instrsList:
            if instr.doesLink():
                if instr.isJumpWithAddress() or instr.isBranch():
                    funcVram = instr.getBranchVramGeneric()
                    self.addFunction(funcVram, isAutogenerated=True)


    def analyze(self) -> None:
        instrsList = self.wordListToInstructions(self.words, self.getVramOffset(0), self.instrCat)
        nInstr = len(instrsList)

        self._findCalls(instrsList)
        funcsStartsList, unimplementedInstructionsFuncList = self._findFunctions(instrsList)

        previousSymbolExtraPadding = 0
        sectionAlign_text = common.GlobalConfig.COMPILER.value.sectionAlign_text
        textAlignment = 1 << sectionAlign_text if sectionAlign_text is not None else None

        i = 0
        startsCount = len(funcsStartsList)
        for startIndex in range(startsCount):
            start = funcsStartsList[startIndex]
            hasUnimplementedIntrs = unimplementedInstructionsFuncList[startIndex]
            end = nInstr
            if startIndex + 1 < startsCount:
                end = funcsStartsList[startIndex+1]

            if start >= end:
                break

            localOffset = start*4
            vram = self.getVramOffset(localOffset)

            vrom = self.getVromOffset(localOffset)
            vromEnd = vrom + (end - start)*4

            if common.GlobalConfig.DISASSEMBLE_UNKNOWN_INSTRUCTIONS or not hasUnimplementedIntrs:
                self.addFunction(vram, isAutogenerated=True, symbolVrom=vrom)
            else:
                self.addSymbol(vram, sectionType=self.sectionType, isAutogenerated=True, symbolVrom=vrom)

            self.symbolsVRams.add(vram)

            func = symbols.SymbolFunction(self.context, vrom, vromEnd, self.inFileOffset + localOffset, vram, instrsList[start:end], self.segmentVromStart, self.overlayCategory)
            func.setCommentOffset(self.commentOffset)
            func.index = i
            func.pointersOffsets |= self.pointersOffsets
            func.hasUnimplementedIntrs = hasUnimplementedIntrs
            func.parent = self
            func.isRsp = self.instrCat == rabbitizer.InstrCategory.RSP
            func.gpRelHack = self.gpRelHack
            func.analyze()
            self.symbolList.append(func)

            if textAlignment is not None:
                # Section boundaries detection

                if (self.vromStart + func.inFileOffset) % textAlignment == 0 and previousSymbolExtraPadding > 0:
                    # If the previous symbol had trailing padding and the
                    # current symbol is aligned to the expected alignment then
                    # add this offset as a section boundary.
                    self.fileBoundaries.append(func.inFileOffset)

                previousSymbolExtraPadding = func.countExtraPadding()

            i += 1

        # Filter out repeated values and sort
        self.fileBoundaries = sorted(set(self.fileBoundaries))


    def compareToFile(self, other: FileBase) -> dict:
        result = super().compareToFile(other)

        if isinstance(other, SectionText):
            result["text"] = {
                "diff_opcode": self.countDiffOpcodes(other),
                "same_opcode_same_args": self.countSameOpcodeButDifferentArguments(other),
            }

        return result

    def countDiffOpcodes(self, other: SectionText) -> int:
        result = 0
        for i in range(min(self.nFuncs, other.nFuncs)):
            func = self.symbolList[i]
            other_func = other.symbolList[i]
            assert isinstance(func, symbols.SymbolFunction)
            assert isinstance(other_func, symbols.SymbolFunction)
            result += func.countDiffOpcodes(other_func)
        return result

    def countSameOpcodeButDifferentArguments(self, other: SectionText) -> int:
        result = 0
        for i in range(min(self.nFuncs, other.nFuncs)):
            func = self.symbolList[i]
            other_func = other.symbolList[i]
            assert isinstance(func, symbols.SymbolFunction)
            assert isinstance(other_func, symbols.SymbolFunction)
            result += func.countSameOpcodeButDifferentArguments(other_func)
        return result

    def blankOutDifferences(self, other_file: FileBase) -> bool:
        if not common.GlobalConfig.REMOVE_POINTERS:
            return False

        if not isinstance(other_file, SectionText):
            return False

        was_updated = False
        for i in range(min(self.nFuncs, other_file.nFuncs)):
            func = self.symbolList[i]
            other_func = other_file.symbolList[i]
            assert isinstance(func, symbols.SymbolFunction)
            assert isinstance(other_func, symbols.SymbolFunction)
            func_updated = func.blankOutDifferences(other_func)
            if func_updated:
                localOffset = func.inFileOffset - self.inFileOffset
                for wordOffset, instr in enumerate(func.instructions):
                    self.words[localOffset // 4 + wordOffset] = instr.getRaw()

                localOffset = other_func.inFileOffset - other_file.inFileOffset
                for wordOffset, instr in enumerate(other_func.instructions):
                    other_file.words[localOffset // 4 + wordOffset] = instr.getRaw()
            was_updated = func_updated or was_updated

        return was_updated

    def removePointers(self) -> bool:
        if not common.GlobalConfig.REMOVE_POINTERS:
            return False

        was_updated = False
        for func in self.symbolList:
            assert isinstance(func, symbols.SymbolFunction)
            func_updated = func.removePointers()
            if func_updated:
                localOffset = func.inFileOffset - self.inFileOffset
                for wordOffset, instr in enumerate(func.instructions):
                    self.words[localOffset // 4 + wordOffset] = instr.getRaw()
            was_updated = func_updated or was_updated

        return was_updated

    def removeTrailingNops(self) -> bool:
        was_updated = False

        if self.nFuncs > 0:
            func = self.symbolList[-1]
            assert isinstance(func, symbols.SymbolFunction)
            func.removeTrailingNops()
            was_updated = True

        return was_updated

    def getGpRelHack(self) -> bool:
        return self.gpRelHack

    def setGpRelHack(self, value: bool) -> None:
        self.gpRelHack = value
        for func in self.symbolList:
            assert isinstance(func, symbols.SymbolFunction)
            func.gpRelHack = value

    def suspectedPaddingGarbage(self) -> list[int]:
        garbage: list[int] = []

        sectionAlign_text = common.GlobalConfig.COMPILER.value.sectionAlign_text
        textAlignment = 1 << sectionAlign_text if sectionAlign_text is not None else None
        if textAlignment is None:
            return garbage

        for func in self.symbolList:
            assert isinstance(func, symbols.SymbolFunction)
            if func.sizew * 4 >= textAlignment:
                # i.e. if textAlignment is 0x10, then reject functions with more than 3 instructions
                continue
            if (func.vram + func.sizew * 4) % textAlignment != 0:
                # Only functions that may be at the end of a section
                continue
            if func.contextSym.referenceCounter != 0:
                # Only unused functions
                continue

            if func.sizew >= 2:
                instr = func.instructions[-2]
                if instr.isJump() or instr.isBranch():
                    # Only count as garbage functions that do not have a proper jump at its end
                    continue

            garbage.append(func.inFileOffset + func.sizew * 4)

        return garbage
