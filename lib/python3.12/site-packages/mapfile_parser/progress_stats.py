#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

import dataclasses


@dataclasses.dataclass
class ProgressStats:
    undecompedSize: int = 0
    decompedSize: int = 0

    @property
    def total(self) -> int:
        return self.undecompedSize + self.decompedSize

    def undecompedPercentage(self) -> float:
        return self.undecompedSize / self.total * 100

    def decompedPercentage(self) -> float:
        return self.decompedSize / self.total * 100

    def undecompedPercentageTotal(self, totalStats: ProgressStats) -> float:
        return self.undecompedSize / totalStats.total * 100

    def decompedPercentageTotal(self, totalStats: ProgressStats) -> float:
        return self.decompedSize / totalStats.total * 100

    def getAsFrogressEntry(self, name: str) -> dict[str, int]:
        categories: dict[str, int] = {}
        categories[name] = self.decompedSize
        categories[f"{name}/total"] = self.total
        return categories

    @staticmethod
    def getHeaderAsStr(categoryColumnSize: int=28) -> str:
        categoryStr = "{0:<{1}}".format('Category', categoryColumnSize)
        return f"{categoryStr}: {'DecompedSize':>12} / {'Total':>8} {'OfFolder':>10}%  ({'OfTotal':>20}%)"

    @staticmethod
    def printHeader(categoryColumnSize: int=28):
        print(ProgressStats.getHeaderAsStr(categoryColumnSize=categoryColumnSize))

    def getEntryAsStr(self, category: str, totalStats: ProgressStats, categoryColumnSize: int=28) -> str:
        categoryStr = "{0:<{1}}".format(category, categoryColumnSize)
        return f"{categoryStr}: {self.decompedSize:>12} / {self.total:>8} {self.decompedPercentage():>10.4f}%  ({self.decompedPercentageTotal(totalStats):>8.4f}% / {self.total / totalStats.total * 100:>8.4f}%)"

    def print(self, category: str, totalStats: ProgressStats, categoryColumnSize: int=28):
        print(self.getEntryAsStr(category, totalStats, categoryColumnSize=categoryColumnSize))

    def asJsonEntry(self) -> dict[str, int|float]:
        return {
            "decomped": self.decompedSize,
            "total": self.total,
            "percentage": round(self.decompedPercentage(), 4)
        }


def printStats(totalStats: ProgressStats, progressPerFolder: dict[str, ProgressStats]):
    ProgressStats.printHeader()
    totalStats.print("all", totalStats)
    print()

    for folder, statsEntry in progressPerFolder.items():
        statsEntry.print(folder, totalStats)

