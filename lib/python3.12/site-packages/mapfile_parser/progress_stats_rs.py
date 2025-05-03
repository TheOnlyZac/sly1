#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2023-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

from .mapfile_parser import ProgressStats as ProgressStats

def printStats(totalStats: ProgressStats, progressPerFolder: dict[str, ProgressStats]):
    ProgressStats.printHeader()
    totalStats.print("all", totalStats)
    print()

    for folder, statsEntry in progressPerFolder.items():
        statsEntry.print(folder, totalStats)
