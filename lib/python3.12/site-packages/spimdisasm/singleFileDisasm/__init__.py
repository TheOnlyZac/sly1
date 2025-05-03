#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations


from .SingleFileDisasmInternals import getToolDescription as getToolDescription
from .SingleFileDisasmInternals import addOptionsToParser as addOptionsToParser
from .SingleFileDisasmInternals import getArgsParser as getArgsParser
from .SingleFileDisasmInternals import applyArgs as applyArgs
from .SingleFileDisasmInternals import applyGlobalConfigurations as applyGlobalConfigurations
from .SingleFileDisasmInternals import getSplits as getSplits
from .SingleFileDisasmInternals import changeGlobalSegmentRanges as changeGlobalSegmentRanges
from .SingleFileDisasmInternals import processArguments as processArguments
from .SingleFileDisasmInternals import addSubparser as addSubparser
from .SingleFileDisasmInternals import disassemblerMain as disassemblerMain
