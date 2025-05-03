#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

import dataclasses
import rabbitizer

from .... import common


@dataclasses.dataclass
class SymbolTypeInfo:
    accessType: rabbitizer.Enum
    """<rabbitizer.AccessType>"""
    unsignedMemoryAccess: bool

    def __eq__(self, other: object) -> bool:
        if not isinstance(other, SymbolTypeInfo):
            return False
        return self.accessType == other.accessType and self.unsignedMemoryAccess == other.unsignedMemoryAccess

    # https://stackoverflow.com/a/56915493/6292472
    def __hash__(self) -> int:
        return hash((self.accessType, self.unsignedMemoryAccess))


@dataclasses.dataclass
class CploadInfo:
    hiOffset: int
    loOffset: int
    adduOffset: int|None = None
    reg: rabbitizer.Enum|None = None

@dataclasses.dataclass
class GpSetInfo:
    """Info for tracking when a $gp register is set"""
    hiOffset: int
    loOffset: int
    value: int


class InstrAnalyzer:
    def __init__(self, funcVram: int, context: common.Context) -> None:
        self.funcVram = funcVram
        self.context = context
        "read-only"

        self.currentGpValue: int|None = common.GlobalConfig.GP_VALUE

        self.referencedVrams: set[int] = set()
        "Every referenced vram found"
        self.referencedConstants: set[int] = set()
        "Every referenced constant found"

        self.referencedVramsInstrOffset: dict[int, int] = dict()

        # Branches
        self.branchInstrOffsets: dict[int, int] = dict()
        "key: branch instruction offset, value: target vram"

        self.branchTargetInstrOffsets: dict[int, int] = dict()
        "key: branch instruction offset, value: relative branch target"

        self.branchLabelOffsets: set[int] = set()

        # Function calls
        self.funcCallInstrOffsets: dict[int, int] = dict()
        "key: func call instruction offset, value: target vram"
        self.funcCallOutsideRangesOffsets: dict[int, int] = dict()
        "key: func call instruction offset, value: target vram which is outside the known vram address range"

        # Jump register (jumptables)
        self.jumpRegisterIntrOffset: dict[int, int] = dict()
        self.referencedJumpTableOffsets: dict[int, int] = dict()
        self.rejectedjumpRegisterIntrOffset: dict[int, tuple[int, int, int]] = dict()
        " key: jr instr offset, value: (jumptable reference offset, jumptable address, branch offset)"

        # Jump and link (functions)
        self.indirectFunctionCallIntrOffset: dict[int, int] = dict()
        self.indirectFunctionCallOffsets: dict[int, int] = dict()

        # Constants
        self.constantHiInstrOffset: dict[int, int] = dict()
        "key: offset of instruction which is setting the %hi constant, value: constant"
        self.constantLoInstrOffset: dict[int, int] = dict()
        "key: offset of instruction which is setting the %lo constant, value: constant"

        self.constantInstrOffset: dict[int, int] = dict()

        # Symbols
        self.symbolHiInstrOffset: dict[int, int] = dict()
        "key: offset of instruction which is setting the %hi symbol, value: symbol"
        self.symbolLoInstrOffset: dict[int, int] = dict()
        "key: offset of instruction which is setting the %lo symbol, value: symbol"

        self.symbolGpInstrOffset: dict[int, int] = dict()
        self.gpReferencedSymbols: set[int] = set()

        self.symbolInstrOffset: dict[int, int] = dict()

        self.possibleSymbolTypes: dict[int, dict[SymbolTypeInfo, int]] = dict()
        "key: address, value: {<SymbolTypeInfo>: number of times this type appears in code}"
        self.symbolTypesOffsets: dict[int, SymbolTypeInfo] = dict()

        # %hi/%lo pairing
        self.hiToLowDict: dict[int, int] = dict()
        "key: %hi instruction offset, value: %lo instruction offset"
        self.lowToHiDict: dict[int, int] = dict()
        "key: %lo instruction offset, value: %hi instruction offset"

        self.luiInstrs: dict[int, rabbitizer.Instruction] = dict()

        self.nonLoInstrOffsets: set[int] = set()

        self.gotAccessAddresses: dict[int, int] = dict()

        self.unpairedCploads: list[CploadInfo] = list()
        "cploads which are not yet fully paired"
        self.cploadOffsets: set[int] = set()
        "Offset of every cpload instruction"
        self.cploads: dict[int, CploadInfo] = dict()
        "Completed cpload, key: offset of last instruction of the cpload"

        self.gpSetsOffsets: set[int] = set()
        "Offsets of every instruction that set the $gp register"
        self.gpSets: dict[int, GpSetInfo|None] = dict()
        "Instructions setting the $gp register, key: offset of the low instruction"


    def processBranch(self, regsTracker: rabbitizer.RegistersTracker, instr: rabbitizer.Instruction, instrOffset: int, currentVram: int) -> None:
        regsTracker.processBranch(instr, instrOffset)

        if instrOffset in self.branchInstrOffsets:
            # Already processed
            return

        branchOffset = instr.getBranchOffsetGeneric()
        branch = instrOffset + branchOffset
        targetBranchVram = self.funcVram + branch

        if not common.GlobalConfig.PIC:
            self.referencedVrams.add(targetBranchVram)

        self.branchLabelOffsets.add(branch)
        self.branchInstrOffsets[instrOffset] = targetBranchVram
        self.branchTargetInstrOffsets[instrOffset] = branch

    def processFuncCall(self, instr: rabbitizer.Instruction, instrOffset: int) -> None:
        if instrOffset in self.funcCallInstrOffsets:
            # Already processed
            return

        target = instr.getInstrIndexAsVram()
        if not self.context.isAddressInGlobalRange(target):
            self.funcCallOutsideRangesOffsets[instrOffset] = target

        if not common.GlobalConfig.PIC:
            self.referencedVrams.add(target)
        self.referencedVramsInstrOffset[instrOffset] = target

        self.funcCallInstrOffsets[instrOffset] = target


    def processConstant(self, regsTracker: rabbitizer.RegistersTracker, luiInstr: rabbitizer.Instruction, luiOffset: int, lowerInstr: rabbitizer.Instruction, lowerOffset: int) -> int|None:
        upperHalf = luiInstr.getProcessedImmediate() << 16
        lowerHalf = lowerInstr.getProcessedImmediate()
        constant = upperHalf | lowerHalf

        self.referencedConstants.add(constant)

        self.constantHiInstrOffset[luiOffset] = constant
        self.constantLoInstrOffset[lowerOffset] = constant
        self.constantInstrOffset[luiOffset] = constant
        self.constantInstrOffset[lowerOffset] = constant

        self.hiToLowDict[luiOffset] = lowerOffset
        self.lowToHiDict[lowerOffset] = luiOffset

        regsTracker.processConstant(lowerInstr, constant, lowerOffset)

        return constant


    def pairHiLo(self, hiValue: int|None, luiOffset: int|None, lowerInstr: rabbitizer.Instruction, lowerOffset: int) -> int|None:
        # lui being None means this symbol is a $gp access
        assert (hiValue is None and luiOffset is None) or (hiValue is not None and luiOffset is not None)

        lowerHalf = lowerInstr.getProcessedImmediate()

        if lowerOffset in self.symbolLoInstrOffset:
            # This %lo has been processed already

            # Check the other lui has the same immediate value as this one, and reject the pair if it doesn't
            if hiValue is not None:
                otherLuiOffset = self.lowToHiDict.get(lowerOffset, None)
                if otherLuiOffset is not None:
                    otherLuiInstr = self.luiInstrs.get(otherLuiOffset, None)
                    if otherLuiInstr is not None:
                        if hiValue != otherLuiInstr.getProcessedImmediate() << 16:
                            return None

            if not common.GlobalConfig.COMPILER.value.pairMultipleHiToSameLow:
                # IDO does not pair multiples %hi to the same %lo
                return self.symbolLoInstrOffset[lowerOffset]

            else:
                if luiOffset is None or hiValue is None:
                    return None

                if self.hiToLowDict.get(luiOffset, None) == lowerOffset and self.lowToHiDict.get(lowerOffset, None) == luiOffset:
                    # This pair has been already paired
                    return self.symbolLoInstrOffset[lowerOffset]

                # luiInstrPrev = self.instructions[(luiOffset-4)//4]
                # if luiInstrPrev.isBranchLikely() or luiInstrPrev.isUnconditionalBranch():
                #     # This lui will be nullified afterwards, so it is likely for it to be re-used lui
                #     pass
                # elif luiInstrPrev.isBranch():
                #     # I'm not really sure if a lui on any branch slot is enough to believe this is really a symbol
                #     # Let's hope it does for now...
                #     pass
                # elif luiOffset + 4 == lowerOffset:
                if luiOffset + 4 == lowerOffset:
                    # Make an exception if the lower instruction is just after the LUI
                    pass
                else:
                    upperHalf = hiValue
                    address = upperHalf + lowerHalf
                    if address == self.symbolLoInstrOffset[lowerOffset]:
                        # Make an exception if the resulting address is the same
                        pass
                    else:
                        return self.symbolLoInstrOffset[lowerOffset]

        if hiValue is None and self.currentGpValue is None:
            # Trying to pair a gp relative offset, but we don't know the gp address
            return None

        if hiValue is not None:
            upperHalf = hiValue
        else:
            assert self.currentGpValue is not None
            upperHalf = self.currentGpValue

        return upperHalf + lowerHalf


    def processSymbol(self, address: int, luiOffset: int|None, lowerInstr: rabbitizer.Instruction, lowerOffset: int) -> int|None:
        if address <= 0:
            # PS2 seems to do LUI/ADDIU pairs for 0 and -1 for some reason, filter them out
            if not common.GlobalConfig.PIC:
                return None

        # filter out stuff that may not be a real symbol
        filterOut = False
        if not self.context.totalVramRange.isInRange(address):
            if common.GlobalConfig.SYMBOL_FINDER_FILTER_LOW_ADDRESSES or common.GlobalConfig.SYMBOL_FINDER_FILTER_HIGH_ADDRESSES:
                filterOut |= common.GlobalConfig.SYMBOL_FINDER_FILTER_LOW_ADDRESSES and address < common.GlobalConfig.SYMBOL_FINDER_FILTER_ADDRESSES_ADDR_LOW
                filterOut |= common.GlobalConfig.SYMBOL_FINDER_FILTER_HIGH_ADDRESSES and address >= common.GlobalConfig.SYMBOL_FINDER_FILTER_ADDRESSES_ADDR_HIGH
            else:
                filterOut |= True

        if filterOut:
            contextSym = self.context.globalSegment.getSymbol(address)
            if contextSym is not None:
                if contextSym.isUserDeclared:
                    # If the user declared a symbol outside the total vram range then use it anyways
                    filterOut = False

        if address > 0 and filterOut and lowerInstr.uniqueId != rabbitizer.InstrId.cpu_addiu:
            if common.GlobalConfig.SYMBOL_FINDER_FILTERED_ADDRESSES_AS_CONSTANTS:
                # Let's pretend this value is a constant
                constant = address
                self.referencedConstants.add(constant)

                self.constantLoInstrOffset[lowerOffset] = constant
                self.constantInstrOffset[lowerOffset] = constant
                if luiOffset is not None:
                    self.constantHiInstrOffset[luiOffset] = constant
                    self.constantInstrOffset[luiOffset] = constant

                    self.hiToLowDict[luiOffset] = lowerOffset
                    self.lowToHiDict[lowerOffset] = luiOffset
            return None

        if not common.GlobalConfig.PIC:
            self.referencedVrams.add(address)

        if lowerOffset not in self.symbolLoInstrOffset:
            self.symbolLoInstrOffset[lowerOffset] = address
            self.symbolInstrOffset[lowerOffset] = address
            self.referencedVramsInstrOffset[lowerOffset] = address
        if luiOffset is not None:
            if luiOffset not in self.symbolHiInstrOffset:
                self.symbolHiInstrOffset[luiOffset] = address
                self.symbolInstrOffset[luiOffset] = address
                self.referencedVramsInstrOffset[luiOffset] = address

            self.hiToLowDict[luiOffset] = lowerOffset
            self.lowToHiDict[lowerOffset] = luiOffset
        else:
            self.symbolGpInstrOffset[lowerOffset] = address
            self.gpReferencedSymbols.add(address)
            self.symbolInstrOffset[lowerOffset] = address
            self.referencedVramsInstrOffset[lowerOffset] = address

        self.processSymbolType(address, lowerInstr, lowerOffset)

        return address

    def processGotSymbol(self, address: int, instr: rabbitizer.Instruction, instrOffset: int) -> None:
        if address <= 0:
            return

        self.gotAccessAddresses[instrOffset] = address
        return

    def processSymbolType(self, address: int, instr: rabbitizer.Instruction, instrOffset: int) -> None:
        accessType = instr.getAccessType()
        unsignedMemoryAccess = instr.doesUnsignedMemoryAccess()
        if accessType == rabbitizer.AccessType.INVALID:
            return

        if address not in self.possibleSymbolTypes:
            self.possibleSymbolTypes[address] = dict()
        symAccess = SymbolTypeInfo(accessType, unsignedMemoryAccess)
        if symAccess not in self.possibleSymbolTypes[address]:
            self.possibleSymbolTypes[address][symAccess] = 0
        self.possibleSymbolTypes[address][symAccess] += 1

        self.symbolTypesOffsets[instrOffset] = symAccess

    def processSymbolDereferenceType(self, regsTracker: rabbitizer.RegistersTracker, instr: rabbitizer.Instruction, instrOffset: int) -> None:
        address = regsTracker.getAddressIfCanSetType(instr, instrOffset)
        if address is None:
            return

        self.processSymbolType(address, instr, instrOffset)


    def symbolFinder(self, regsTracker: rabbitizer.RegistersTracker, instr: rabbitizer.Instruction, prevInstr: rabbitizer.Instruction|None, instrOffset: int) -> None:
        if instr.canBeHi():
            if prevInstr is None:
                regsTracker.processLui(instr, instrOffset)
            else:
                regsTracker.processLui(instr, instrOffset, prevInstr)
            self.luiInstrs[instrOffset] = instr
            return

        if instr.doesLoad() and instr.rs in {rabbitizer.RegGprO32.gp, rabbitizer.RegGprN32.gp}:
            regsTracker.processGpLoad(instr, instrOffset)

        if not instr.canBeLo():
            return

        if instr.isUnsigned():
            # Constants
            luiOffset = regsTracker.getLuiOffsetForConstant(instr)
            if luiOffset is None:
                return
            luiInstr = self.luiInstrs.get(luiOffset, None)
            if luiInstr is None:
                return
            self.processConstant(regsTracker, luiInstr, luiOffset, instr, instrOffset)
            return

        if instrOffset in self.nonLoInstrOffsets:
            return

        pairingInfo = regsTracker.preprocessLoAndGetInfo(instr, instrOffset)
        if not pairingInfo.shouldProcess:
            if regsTracker.hasLoButNoHi(instr):
                self.nonLoInstrOffsets.add(instrOffset)
            return

        if pairingInfo.isGpGot and not common.GlobalConfig.PIC:
            return

        upperHalf: int|None = pairingInfo.value
        luiOffset = pairingInfo.instrOffset
        if pairingInfo.isGpRel:
            upperHalf = None
            luiOffset = None

        if luiOffset is not None:
            luiInstr = self.luiInstrs.get(luiOffset)
            if luiInstr is not None and luiInstr.rt in {rabbitizer.RegGprO32.gp, rabbitizer.RegGprN32.gp}:
                if instr.readsRs() and instr.rs in {rabbitizer.RegGprO32.gp, rabbitizer.RegGprN32.gp} and instr.modifiesRt() and instr.rt in {rabbitizer.RegGprO32.gp, rabbitizer.RegGprN32.gp}:
                    if common.GlobalConfig.PIC:
                        # cpload
                        self.unpairedCploads.append(CploadInfo(luiOffset, instrOffset))
                    else:
                        hiGpValue = luiInstr.getProcessedImmediate() << 16
                        loGpValue = instr.getProcessedImmediate()
                        gpValue = hiGpValue+loGpValue
                        self.gpSets[instrOffset] = GpSetInfo(luiOffset, instrOffset, gpValue)
                        self.gpSetsOffsets.add(luiOffset)
                        self.gpSetsOffsets.add(instrOffset)
                        if not common.GlobalConfig.PIC:
                            self.currentGpValue = gpValue
                    # early return to avoid counting this pairing as a normal symbol
                    return

        address = self.pairHiLo(upperHalf, luiOffset, instr, instrOffset)
        if address is None:
            return

        if upperHalf is None:
            if common.GlobalConfig.PIC:
                self.processGotSymbol(address, instr, instrOffset)
                regsTracker.processLo(instr, address, instrOffset)
                return

        address = self.processSymbol(address, luiOffset, instr, instrOffset)
        if address is not None:
            regsTracker.processLo(instr, address, instrOffset)


    def processJumpRegister(self, regsTracker: rabbitizer.RegistersTracker, instr: rabbitizer.Instruction, instrOffset: int) -> None:
        jrRegData = regsTracker.getJrRegData(instr)
        if jrRegData.hasInfo():
            offset = jrRegData.offset()
            address = jrRegData.address()

            if jrRegData.checkedForBranching():
                self.rejectedjumpRegisterIntrOffset[instrOffset] = (offset, address, jrRegData.lastBranchOffset())
            else:
                # Jumptables never check the register they are branching into,
                # since the references should always be valid.
                # This kind of check usually is performed on tail call
                # optimizations when a function pointer is involved.
                # For example:
                # ```mips
                # lw          $t0, ...
                # beqz        $t0, .LXXXXXXXX
                #  nop
                # jr          $t0
                #  nop
                # ```
                self.referencedJumpTableOffsets[offset] = address

            self.jumpRegisterIntrOffset[instrOffset] = address
            if not common.GlobalConfig.PIC:
                self.referencedVrams.add(address)

    def processJumpAndLinkRegister(self, regsTracker: rabbitizer.RegistersTracker, instr: rabbitizer.Instruction, instrOffset: int) -> None:
        jrRegData = regsTracker.getJrRegData(instr)
        if jrRegData.hasInfo():
            offset = jrRegData.offset()
            address = jrRegData.address()

            self.indirectFunctionCallOffsets[offset] = address
            self.indirectFunctionCallIntrOffset[instrOffset] = address
            if not common.GlobalConfig.PIC:
                self.referencedVrams.add(address)


    def processInstr(self, regsTracker: rabbitizer.RegistersTracker, instr: rabbitizer.Instruction, instrOffset: int, currentVram: int, prevInstr: rabbitizer.Instruction|None) -> None:
        if instr.isBranch() or instr.isUnconditionalBranch():
            self.processBranch(regsTracker, instr, instrOffset, currentVram)

        elif instr.isJumpWithAddress():
            self.processFuncCall(instr, instrOffset)

        elif instr.hasOperandAlias(rabbitizer.OperandType.cpu_immediate):
            self.symbolFinder(regsTracker, instr, prevInstr, instrOffset)
            self.processSymbolDereferenceType(regsTracker, instr, instrOffset)

        elif instr.isJumptableJump():
            self.processJumpRegister(regsTracker, instr, instrOffset)

        elif instr.isJump() and instr.doesLink():
            # jalr, implicit not isJumpWithAddress
            self.processJumpAndLinkRegister(regsTracker, instr, instrOffset)

        elif instr.uniqueId == rabbitizer.InstrId.cpu_addu:
            # special check for .cpload
            if len(self.unpairedCploads) > 0:
                if instr.rd in {rabbitizer.RegGprO32.gp, rabbitizer.RegGprN32.gp} and instr.rs in {rabbitizer.RegGprO32.gp, rabbitizer.RegGprN32.gp}:
                    cpload = self.unpairedCploads.pop()
                    cpload.adduOffset = instrOffset
                    cpload.reg = instr.rt
                    self.cploadOffsets.add(cpload.hiOffset)
                    self.cploadOffsets.add(cpload.loOffset)
                    self.cploadOffsets.add(instrOffset)
                    self.cploads[instrOffset] = cpload

        regsTracker.overwriteRegisters(instr, instrOffset)
        if not common.GlobalConfig.PIC:
            dstReg = instr.getDestinationGpr()
            if dstReg is not None and (dstReg == rabbitizer.RegGprO32.gp or dstReg == rabbitizer.RegGprN32.gp):
                if instrOffset not in self.gpSets:
                    self.gpSets[instrOffset] = None
                    self.gpSetsOffsets.add(instrOffset)
                    self.currentGpValue = None


    def processPrevFuncCall(self, regsTracker: rabbitizer.RegistersTracker, instr: rabbitizer.Instruction, prevInstr: rabbitizer.Instruction, currentVram: int | None = None) -> None:
        regsTracker.unsetRegistersAfterFuncCall(instr, prevInstr)



    def printAnalisisDebugInfo_IterInfo(self, regsTracker: rabbitizer.RegistersTracker, instr: rabbitizer.Instruction, currentVram: int) -> None:
        if not common.GlobalConfig.PRINT_FUNCTION_ANALYSIS_DEBUG_INFO:
            return

        print("_printAnalisisDebugInfo_IterInfo")
        print()
        print(f"vram: {currentVram:X}")
        print(instr)
        # print(instr.rs, instr.getRegisterName(instr.rs))
        # print(instr.rt, instr.getRegisterName(instr.rt))
        # print(instr.rd, instr.getRegisterName(instr.rd))
        # print(regsTracker.registers)
        # print({instr.getRegisterName(x): y for x, y in regsTracker.registers.items()})
        # _t is shorthand of temp
        # print({instr.getRegisterName(register_t): f"{state_t.value:X},{state_t.loOffset:X},{state_t.dereferenced}" for register_t, state_t in regsTracker.registers.items() if state_t.hasLoValue})
        print()

    def printSymbolFinderDebugInfo_UnpairedLuis(self) -> None:
        if not common.GlobalConfig.PRINT_UNPAIRED_LUIS_DEBUG_INFO:
            return

        firstNotePrinted = False

        for instructionOffset, luiInstr in self.luiInstrs.items():
            # if instructionOffset in self.nonPointerLuiSet:
            #     continue
            if instructionOffset in self.constantInstrOffset:
                # print(f"{currentVram:06X} ", end="")
                # print(f"C  {self.constantsPerInstruction[instructionOffset]:8X}", luiInstr)
                pass
            else:
                if common.GlobalConfig.SYMBOL_FINDER_FILTER_LOW_ADDRESSES and luiInstr.getProcessedImmediate() < 0x8000: # filter out stuff that may not be a real symbol
                    continue
                if common.GlobalConfig.SYMBOL_FINDER_FILTER_HIGH_ADDRESSES and luiInstr.getProcessedImmediate() >= 0xC000: # filter out stuff that may not be a real symbol
                    continue

                # print(f"{currentVram:06X} ", end="")
                # if instructionOffset in self.pointersPerInstruction:
                #     print(f"P  {self.pointersPerInstruction[instructionOffset]:8X}", luiInstr)
                # else:
                #     print("NO         ", luiInstr)

                if instructionOffset not in self.symbolInstrOffset:
                    if not firstNotePrinted:
                        print("_printSymbolFinderDebugInfo_UnpairedLuis")
                        print(f"funcVram: {self.funcVram:08X}")
                        firstNotePrinted = True

                    print(f"{luiInstr.vram:06X} ", "NO         ", luiInstr)

        if firstNotePrinted:
            print()
