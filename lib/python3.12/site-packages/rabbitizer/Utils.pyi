#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations


class Utils:
    @staticmethod
    def from2Complement(number: int, bits: int) -> int: ...

    @staticmethod
    def escapeString(src: str) -> str: ...

    @staticmethod
    def floatRepr_32From16(hex_repr: int) -> int:
        """
        Converts an unsigned 16 bits value representing a half precision
        float to a unsigned 32 bits value representing a single precision
        float.
        """
