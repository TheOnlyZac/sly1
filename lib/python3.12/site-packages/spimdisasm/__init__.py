#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

__version_info__: tuple[int, int, int] = (1, 34, 2)
__version__ = ".".join(map(str, __version_info__)) # + "-dev0"
__author__ = "Decompollaborate"

from . import common as common
from . import elf32 as elf32
from . import mips as mips

# Front-end scripts
from . import frontendCommon as frontendCommon
from . import disasmdis as disasmdis
from . import rspDisasm as rspDisasm
from . import elfObjDisasm as elfObjDisasm
from . import singleFileDisasm as singleFileDisasm
