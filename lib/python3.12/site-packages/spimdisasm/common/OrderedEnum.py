#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

import enum


class OrderedEnum(enum.Enum):
     def __ge__(self, other: OrderedEnum) -> bool:
         if isinstance(other, self.__class__):
             return bool(self.value >= other.value)
         return NotImplemented

     def __gt__(self, other: OrderedEnum) -> bool:
         if isinstance(other, self.__class__):
             return bool(self.value > other.value)
         return NotImplemented

     def __le__(self, other: OrderedEnum) -> bool:
         if isinstance(other, self.__class__):
             return bool(self.value <= other.value)
         return NotImplemented

     def __lt__(self, other: OrderedEnum) -> bool:
         if isinstance(other, self.__class__):
             return bool(self.value < other.value)
         return NotImplemented
