#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

from .Enum import Enum
from .Abi import Abi

class _RabbitizerConfig:
    regNames_namedRegisters: bool = True
    regNames_gprAbiNames: Enum = Abi.O32
    regNames_fprAbiNames: Enum = Abi.NUMERIC
    regNames_userFpcCsr: bool = True
    regNames_vr4300Cop0NamedRegisters: bool = True
    regNames_vr4300RspCop0NamedRegisters: bool = True
    regNames_r4000AllegrexVfpuControlNamedRegisters: bool = False

    pseudos_enablePseudos: bool = True
    pseudos_pseudoBeqz: bool = True
    pseudos_pseudoBnez: bool = True
    pseudos_pseudoB: bool = True
    pseudos_pseudoMove: bool = True
    pseudos_pseudoNot: bool = True
    pseudos_pseudoNeg: bool = True
    pseudos_pseudoNegu: bool = True
    pseudos_pseudoBal: bool = True

    toolchainTweaks_treatJAsUnconditionalBranch: bool = True
    toolchainTweaks_sn64DivFix: bool = False
    toolchainTweaks_gnuMode: bool = True

    misc_opcodeLJust: int = 11
    misc_unknownInstrComment: bool = True
    misc_omit0XOnSmallImm: bool = False
    misc_upperCaseImm: bool = True
    misc_expandJalr: bool = False

config: _RabbitizerConfig
