#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
import rabbitizer

from .. import common
from ..common import Utils


class InstructionConfig:
    @staticmethod
    def addParametersToArgParse(parser: argparse.ArgumentParser) -> None:
        registerNames = parser.add_argument_group("MIPS register names options")

        registerNames.add_argument("--named-registers", help=f"(Dis)allows named registers for every instruction. This flag takes precedence over similar flags in this category. Defaults to {rabbitizer.config.regNames_namedRegisters}", action=Utils.BooleanOptionalAction)

        abi_choices = ["numeric", "32", "o32", "n32", "n64"]
        registerNames.add_argument("--Mgpr-names", help=f"Use GPR names according to the specified ABI. Defaults to {rabbitizer.config.regNames_gprAbiNames.name.lower()}", choices=abi_choices)
        registerNames.add_argument("--Mfpr-names", help=f"Use FPR names according to the specified ABI. Defaults to {rabbitizer.config.regNames_fprAbiNames.name.lower()}", choices=abi_choices)
        registerNames.add_argument("--Mreg-names", help=f"Use GPR and FPR names according to the specified ABI. This flag takes precedence over --Mgpr-names and --Mfpr-names", choices=abi_choices)

        registerNames.add_argument("--use-fpccsr", help=f"Toggles using the FpcCsr alias for float register $31 when using the numeric ABI. Defaults to {rabbitizer.config.regNames_userFpcCsr}", action=Utils.BooleanOptionalAction)

        registerNames.add_argument("--cop0-named-registers", help=f"Toggles using the built-in names for registers of the VR4300's Coprocessor 0. Defaults to {rabbitizer.config.regNames_vr4300Cop0NamedRegisters}", action=Utils.BooleanOptionalAction)
        registerNames.add_argument("--rsp-cop0-named-registers", help=f"Toggles using the built-in names for registers of the RSP's Coprocessor 0. Defaults to {rabbitizer.config.regNames_vr4300RspCop0NamedRegisters}", action=Utils.BooleanOptionalAction)


        miscOpts = parser.add_argument_group("MIPS misc instructions options")

        miscOpts.add_argument("--pseudo-instr", help=f"Toggles producing pseudo instructions. Defaults to {rabbitizer.config.pseudos_enablePseudos}", action=Utils.BooleanOptionalAction)

        miscOpts.add_argument("--j-branch", help=f"Treat J instructions as unconditional branches. {rabbitizer.config.toolchainTweaks_treatJAsUnconditionalBranch}", action=Utils.BooleanOptionalAction)

        miscOpts.add_argument("--sn64-div-fix", help=f"Enables a few fixes for SN64's assembler related to div/divu instructions. Defaults to {rabbitizer.config.toolchainTweaks_sn64DivFix}", action=Utils.BooleanOptionalAction)

        miscOpts.add_argument("--opcode-ljust", help=f"Set the minimal number of characters to left-align the opcode name. Defaults to {rabbitizer.config.misc_opcodeLJust}")

        miscOpts.add_argument("--unk-instr-comment", help=f"Disables the extra comment produced after unknown instructions. Defaults to {rabbitizer.config.misc_unknownInstrComment}", action=Utils.BooleanOptionalAction)


    @staticmethod
    def parseArgs(args: argparse.Namespace) -> None:
        if args.named_registers is not None:
            rabbitizer.config.regNames_namedRegisters = args.named_registers

        if common.GlobalConfig.ABI != common.Abi.O32:
            rabbitizer.config.regNames_gprAbiNames = rabbitizer.Abi.fromStr(common.GlobalConfig.ABI.name)
            rabbitizer.config.regNames_fprAbiNames = rabbitizer.Abi.fromStr(common.GlobalConfig.ABI.name)

        if args.Mgpr_names:
            rabbitizer.config.regNames_gprAbiNames = rabbitizer.Abi.fromStr(args.Mgpr_names)
        if args.Mfpr_names:
            rabbitizer.config.regNames_fprAbiNames = rabbitizer.Abi.fromStr(args.Mfpr_names)
        if args.Mreg_names:
            rabbitizer.config.regNames_gprAbiNames = rabbitizer.Abi.fromStr(args.Mreg_names)
            rabbitizer.config.regNames_fprAbiNames = rabbitizer.Abi.fromStr(args.Mreg_names)

        if args.use_fpccsr is not None:
            rabbitizer.config.regNames_userFpcCsr = args.use_fpccsr

        if args.cop0_named_registers is not None:
            rabbitizer.config.regNames_vr4300Cop0NamedRegisters = args.cop0_named_registers
        if args.rsp_cop0_named_registers is not None:
            rabbitizer.config.regNames_vr4300RspCop0NamedRegisters = args.rsp_cop0_named_registers

        if args.pseudo_instr is not None:
            rabbitizer.config.pseudos_enablePseudos = args.pseudo_instr

        if args.j_branch is not None:
            rabbitizer.config.toolchainTweaks_treatJAsUnconditionalBranch = args.j_branch

        if args.sn64_div_fix is not None:
            rabbitizer.config.toolchainTweaks_sn64DivFix = args.sn64_div_fix

        if args.opcode_ljust is not None:
            rabbitizer.config.misc_opcodeLJust = int(args.opcode_ljust, 0)

        if args.unk_instr_comment is not None:
            rabbitizer.config.misc_unknownInstrComment = args.unk_instr_comment
