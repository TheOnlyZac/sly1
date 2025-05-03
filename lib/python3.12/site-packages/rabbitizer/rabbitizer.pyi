#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

from .Enum import Enum
from .InstrCategory import InstrCategory
from .TrinaryValue import TrinaryValue


class Instruction:
    rs: Enum
    """The value of the `rs` register for this instruction.
    The type of this attribute will be either a `RegGprO32` or a `RegGprN32` depending on the current `config.regNames_gprAbiNames` value.
    If the current instruction does not use the `rs` register, then a Runtime exception will be raised.
    Read-only."""
    rt: Enum
    """The value of the `rt` register for this instruction.
    The type of this attribute will be either a `RegGprO32` or a `RegGprN32` depending on the current `config.regNames_gprAbiNames` value.
    If the current instruction does not use the `rt` register, then a Runtime exception will be raised.
    Read-only."""
    rd: Enum
    """The value of the `rd` register for this instruction.
    The type of this attribute will be either a `RegGprO32` or a `RegGprN32` depending on the current `config.regNames_gprAbiNames` value.
    If the current instruction does not use the `rd` register, then a Runtime exception will be raised.
    Read-only."""
    sa: int
    """The value of the `sa` field for this instruction.
    If the current instruction does not have a `sa` field, then a Runtime exception will be raised.
    Read-only."""
    fs: Enum
    """The value of the `fs` register for this instruction.
    The type of this attribute will be either a `RegGprO32`, `RegGprN32` or a `RegGprN64` depending on the current `config.regNames_gprAbiNames` value.
    If the current instruction does not use the `fs` register, then a Runtime exception will be raised.
    Read-only."""
    ft: Enum
    """The value of the `ft` register for this instruction.
    The type of this attribute will be either a `RegGprO32`, `RegGprN32` or a `RegGprN64` depending on the current `config.regNames_gprAbiNames` value.
    If the current instruction does not use the `ft` register, then a Runtime exception will be raised.
    Read-only."""
    fd: Enum
    """The value of the `fd` register for this instruction.
    The type of this attribute will be either a `RegGprO32`, `RegGprN32` or a `RegGprN64` depending on the current `config.regNames_gprAbiNames` value.
    If the current instruction does not use the `fd` register, then a Runtime exception will be raised.
    Read-only."""

    uniqueId: Enum
    """An unique identificator for the opcode of this instruction.
    The type is an `InstrId` enum.
    Read-only."""

    instrIdType: Enum
    """An identificator for the general type for the opcode of this instruction.
    The type is an `InstrIdType` enum.
    Read-only."""

    vram: int = 0
    """The vram (virtual ram) address for this instruction"""
    inHandwrittenFunction: bool = False
    """Boolean value indicating if the current instruction is used on a handwritten function. This is intended to be determined by the user."""

    flag_r5900DisasmAsData: Enum = TrinaryValue.NONE
    """Flag to override the r5900DisasmAsData global configuration.

    - This flag allows to fine-tune R5900 instruction set that are affected by the global `gnuMode` option.
        - Currently these instructions are: `trunc.w.s` (r5900 mode), `cvt.w.s` (r5900 mode), `vclipw` and `vsqrt`.

    - `TrinaryValue.TRUE` forces the instruction to be disassembled as data.
    - `TrinaryValue.FALSE` bypasses the global checks for disassembling a word as data. A word will still be disassembled as data if it can't be decoded.
    - `TrinaryValue.NONE` leaves this decision to the global settings.
    """
    flag_r5900UseDollar: Enum = TrinaryValue.NONE
    """Flag to override the disasmAsData global configuration.

    - `TrinaryValue.TRUE` forces the use of dollar signs ($) on R5900's VU instructions.
    - `TrinaryValue.FALSE` forces disassembling to not use of dollar signs ($) on R5900's VU instructions.
    - `TrinaryValue.NONE` leaves this decision to the global settings.
    """


    def __init__(self, word: int, vram: int=0, category: Enum=InstrCategory.CPU) -> None:
        """Decode an Instruction encoded as the 4 bytes `word`, located at `vram`.

        `vram` is used to decode jump instructions that use the PC value to get the upper bits of the target address.
        """

    def getRaw(self) -> int:
        """Get the word value encoding the instruction.

        The returned value may not be the same as the one to instance this Instruction
        if a method that modifies the word has been used, like `instr.blankOut()`.
        """
    def getImmediate(self) -> int: #! deprecated
        """Use `getProcessedImmediate()` instead"""
    def getProcessedImmediate(self) -> int:
        """Get the (possibly signed) immediate value for this instruction.

        This only makes sense for an instruction with an immediate,
        which can be checked with `instr.hasOperandAlias(OperandType.cpu_immediate)`.

        An exception will be raised if the instruction does not contain an immediate field.
        """
    def getInstrIndexAsVram(self) -> int:
        """Get the target vram address this instruction jumps to.
        This method is intended only for direct jump instructions.

        This only makes sense if the instruction is a direct jump,
        which can be checked with `instr.isJumpWithAddress()`.

        An exception will be raised if the instruction is not a jump instruction.
        """
    def getBranchOffset(self) -> int:
        """Returns the offset (in bytes) that the branch instruction would branch,
        relative to the instruction itself. This method is intended only for branch
        instructions.

        The returned value can be negative, meaning the branch instructions does
        a backwards branch.

        This only makes sense for an instruction is a branch,
        which can be checked with `instr.isBranch()`.

        To get the branch offset of either a branch instruction or a jump instruction
        use `instr.getBranchOffsetGeneric()` instead.

        An exception will be raised if the instruction is not a branch instruction.
        """
    def getGenericBranchOffset(self, currentVram: int) -> int: #! deprecated
        """Use `getBranchOffsetGeneric()` instead"""
    def getBranchOffsetGeneric(self) -> int:
        """Returns the offset (in bytes) that the instruction would branch,
        relative to the instruction itself. This method is intended for both branch
        and jump instructions.

        The returned value can be either positive or negative.

        This only makes sense for an instruction is a branch or a direct jump,
        which can be checked with `instr.isBranch()` or `instr.isJumpWithAddress()`.

        An exception will be raised if the instruction is neither a branch or a
        jump instruction.
        """
    def getBranchVramGeneric(self) -> int:
        """Get the target vram address this instruction jumps to.
        This method is intended only for branch or direct jump instructions.

        This only makes sense for an instruction is a branch or a direct jump,
        which can be checked with `instr.isBranch()` or `instr.isJumpWithAddress()`.

        An exception will be raised if the instruction is neither a branch or a
        jump instruction.
        """
    def getDestinationGpr(self) -> Enum|None:
        """
        Returns the general purpose register (GPR) which this instruction modifies,
        or `None` if the instruction does not modify the state of any GPR
        """
    def outputsToGprZero(self) -> bool:
        """
        Returns `True` if the GPR which is modified by this register is $zero,
        `False` otherwise.
        Returns `false` if this instruction does not modify a GPR.
        """
    def getOpcodeName(self) -> str:
        """Returns the mnemonic of the instruction.
        """

    def blankOut(self) -> None:
        """Zero'es out every field (registers and immediate) of the instruction
        leaving only the mnemonic.
        """

    def isImplemented(self) -> bool: #! deprecated
        """Use `instr.isValid()` instead"""
    def isLikelyHandwritten(self) -> bool:
        """Try to guess if the given instruction was handwritten by a human
        instead of generated by a C compiler.
        """
    def isNop(self) -> bool:
        """Check if the instruction is literally the `nop` instruction."""
    def isUnconditionalBranch(self) -> bool:
        """Check if the instruction is an instruction that will always branch unconditionally.

        This is always true for the `b` instruction.

        Some compilers use the `j` instruction for unconditional branches instead
        of the `b` instruction. Treating this instruction as an unconditional branch
        can be configured with the `config.toolchainTweaks_treatJAsUnconditionalBranch`
        option.
        """
    def isFunctionCall(self) -> bool:
        """Check if this is an instruction used for function calls.

        This is always true for "and link" instructions.

        Some compilers use the `j` instruction for tail call optimizations, meaning
        we may require to give special treatment to this instruction if we are
        analyzing code emitted by one of those compilers, like clearing registers
        after a tail call. This can be configured by turning off the
        `config.toolchainTweaks_treatJAsUnconditionalBranch` option.
        """

    def isReturn(self) -> bool:
        """Check if the instruction and its register is the one usually used for
        returning from a function.

        Specfically, this checks if the instruction is a `jr $ra`.

        Returns `False` if the instruction is not a `jr` or if it is a `jr` but
        the register is not `$ra`.
        """
    def isJumptableJump(self) -> bool:
        """Check if the instruction and its register is the one usually used for
        jumping with jumptables.

        Specfically, this checks if the instruction is a `jr` but its register is
        not `$ra`.

        Returns `False` if the instruction is not a `jr` or if it is a `jr` but
        the register is `$ra`.
        """

    def isJrRa(self) -> bool: #! deprecated
        """Use `isReturn()` instead"""
    def isJrNotRa(self) -> bool: #! deprecated
        """Use `isJumptableJump()` instead"""

    def hasDelaySlot(self) -> bool:
        """Check if the instruction has a delay slot."""
    def mapInstrToType(self) -> str|None: #! deprecated
        """use `getAccessType()` instead"""

    def sameOpcode(self, other: Instruction) -> bool:
        """Check if two instructions have the same mnemonic"""
    def sameOpcodeButDifferentArguments(self, other: Instruction) -> bool:
        """Check if two instructions have the same mnemonic but their arguments
        are different.
        """

    def hasOperand(self, operand: Enum) -> bool:
        """Check if the instruction has specifically the `operand`.

        `operand` should be from the `OperandType` enum.
        """
    def hasOperandAlias(self, operand: Enum) -> bool:
        """Check if the instruction has the `operand` or an alias of it.

        (if unsure whether to use `hasOperand` or `hasOperandAlias`, use `hasOperandAlias`)

        `operand` should be from the `OperandType` enum.
        """

    def isValid(self) -> bool:
        """Check the word corresponds to a valid instruction."""

    #! deprecated
    def isUnknownType(self) -> bool: ...
    #! deprecated
    def isJType(self) -> bool:
        """Use `isJumpWithAddress()` instead"""
    #! deprecated
    def isIType(self) -> bool:
        """Use `hasOperandAlias(OperandType.cpu_immediate)` instead"""
    #! deprecated
    def isRType(self) -> bool: ...
    #! deprecated
    def isRegimmType(self) -> bool:
        """Use `hasOperandAlias(OperandType.cpu_immediate)` instead"""

    def isBranch(self) -> bool:
        """Instruction is a branch instruction.

        This is also true for branch likely instructions.
        """
    def isBranchLikely(self) -> bool: ...
    def isJump(self) -> bool: ...
    def isJumpWithAddress(self) -> bool: ...
    def isTrap(self) -> bool: ...
    def isFloat(self) -> bool: ...
    def isDouble(self) -> bool: ...
    def isUnsigned(self) -> bool: ...
    def modifiesRs(self) -> bool: ...
    def modifiesRt(self) -> bool: ...
    def modifiesRd(self) -> bool: ...
    def readsRs(self) -> bool: ...
    def readsRt(self) -> bool: ...
    def readsRd(self) -> bool: ...
    def readsHI(self) -> bool: ...
    def readsLO(self) -> bool: ...
    def modifiesHI(self) -> bool: ...
    def modifiesLO(self) -> bool: ...
    def modifiesFs(self) -> bool: ...
    def modifiesFt(self) -> bool: ...
    def modifiesFd(self) -> bool: ...
    def readsFs(self) -> bool: ...
    def readsFt(self) -> bool: ...
    def readsFd(self) -> bool: ...
    def notEmitedByCompilers(self) -> bool: #! deprecated
        """Use `notEmittedByCompilers()` instead"""
    def notEmittedByCompilers(self) -> bool: ...
    def canBeHi(self) -> bool: ...
    def canBeLo(self) -> bool: ...
    def doesLink(self) -> bool: ...
    def doesDereference(self) -> bool: ...
    def doesLoad(self) -> bool: ...
    def doesStore(self) -> bool: ...
    def maybeIsMove(self) -> bool: ...
    def isPseudo(self) -> bool: ...
    def getAccessType(self) -> Enum: ...
    def doesUnsignedMemoryAccess(self) -> bool: ...

    def disassemble(self, immOverride: str|None=None, extraLJust: int=0) -> str:
        """Returns a string that can be assembled back to the instruction raw word.
        `immOverride` can be a string that replaces the immediate in the disassembly,
        or the jump target, if any. If the instruction has neither, it is ignored.
        Examples:
        >>> Instruction(0x3C0A0042).disassemble()
        'lui         $t2, 0x42'
        >>> Instruction(0x3C0A0042).disassemble("hex_answer")
        'lui         $t2, hex_answer'
        >>> Instruction(0x0C000042).disassemble()
        'jal         func_80000108'
        >>> Instruction(0x0C000042).disassemble("my_target")
        'jal         my_target'
        """

    def __reduce__(self) -> tuple: ...

    def __repr__(self) -> str: ...
    def __str__(self) -> str: ...
