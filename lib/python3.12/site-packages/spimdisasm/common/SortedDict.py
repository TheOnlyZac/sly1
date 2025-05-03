#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

from abc import ABCMeta, abstractmethod
import bisect
from typing import Any, Generator, TypeVar

# typing.Mapping and typing.MutableMapping are deprecated since Python 3.9.
# Using collections.abc is encouraged instead, but 3.7 and 3.8 will to run this file
# with a "'ABCMeta' object is not subscriptable" exception, so this is a hacky way to
# try to be future proof and not have problems because those types will be removed
# in the future
try:
    from collections.abc import Mapping, MutableMapping
    MutableMapping[int, int]
except:
    from typing import Mapping, MutableMapping

ValueType = TypeVar("ValueType")


class SortedDict(MutableMapping[int, ValueType]):
    def __init__(self, other: Mapping[int, ValueType]|None=None) -> None:
        self.map: dict[int, ValueType] = dict()
        self.sortedKeys: list[int] = list()

        if other is not None:
            for key, value in other.items():
                self.add(key, value)


    def add(self, key: int, value: ValueType) -> None:
        if key not in self.map:
            # Avoid adding the key twice if it is already on the map
            bisect.insort(self.sortedKeys, key)
        self.map[key] = value

    def remove(self, key: int) -> None:
        del self.map[key]
        self.sortedKeys.remove(key)


    def getKeyRight(self, key: int, inclusive: bool=True) -> tuple[int, ValueType]|None:
        """Returns the pair with the greatest key which is less or equal to the `key` parameter, or None if there's no smaller pair than the passed `key`.

        If `inclusive` is `False`, then the returned pair will be strictly less than the passed `key`.
        """
        if inclusive:
            index = bisect.bisect_right(self.sortedKeys, key)
        else:
            index = bisect.bisect_left(self.sortedKeys, key)
        if index == 0:
            return None
        currentKey = self.sortedKeys[index - 1]
        return currentKey, self.map[currentKey]

    def getKeyLeft(self, key: int, inclusive: bool=True) -> tuple[int, ValueType]|None:
        """Returns the pair with the smallest key which is gretest or equal to the `key` parameter, or None if there's no greater pair than the passed `key`.

        If `inclusive` is `False`, then the returned pair will be strictly greater than the passed `key`.
        """
        if inclusive:
            index = bisect.bisect_left(self.sortedKeys, key)
        else:
            index = bisect.bisect_right(self.sortedKeys, key)
        if index == len(self.sortedKeys):
            return None
        key = self.sortedKeys[index]
        return key, self.map[key]


    def getRange(self, startKey: int, endKey: int, startInclusive: bool=True, endInclusive: bool=False) -> Generator[tuple[int, ValueType], None, None]:
        """Generator which iterates in the range [`startKey`, `endKey`], returining a (key, value) tuple.

        By default the `startKey` is inclusive but the `endKey` isn't, this can be changed with the `startInclusive` and `endInclusive` parameters"""
        if startInclusive:
            keyIndexStart = bisect.bisect_left(self.sortedKeys, startKey)
        else:
            keyIndexStart = bisect.bisect_right(self.sortedKeys, startKey)

        if endInclusive:
            keyIndexEnd = bisect.bisect_right(self.sortedKeys, endKey)
        else:
            keyIndexEnd = bisect.bisect_left(self.sortedKeys, endKey)

        for index in range(keyIndexStart, keyIndexEnd):
            key = self.sortedKeys[index]
            yield (key, self.map[key])

    def getRangeAndPop(self, startKey: int, endKey: int, startInclusive: bool=True, endInclusive: bool=False) -> Generator[tuple[int, ValueType], None, None]:
        """Similar to `getRange`, but every pair is removed from the dictionary.

        Please note this generator iterates in reverse/descending order"""
        if startInclusive:
            keyIndexStart = bisect.bisect_left(self.sortedKeys, startKey)
        else:
            keyIndexStart = bisect.bisect_right(self.sortedKeys, startKey)

        if endInclusive:
            keyIndexEnd = bisect.bisect_right(self.sortedKeys, endKey)
        else:
            keyIndexEnd = bisect.bisect_left(self.sortedKeys, endKey)

        for index in range(keyIndexEnd-1, keyIndexStart-1, -1):
            key = self.sortedKeys[index]
            value = self.map[key]
            self.remove(key)
            yield (key, value)

    def index(self, key: int) -> int|None:
        """Returns the index of the passed `key` in the sorted dictionary, or None if the key is not present."""
        if key not in self.map:
            return None
        return bisect.bisect_left(self.sortedKeys, key)

    def __getitem__(self, key: int) -> ValueType:
        return self.map[key]

    def __setitem__(self, key: int, value: ValueType) -> None:
        self.add(key, value)

    def __delitem__(self, key: int) -> None:
        self.remove(key)

    def __iter__(self) -> Generator[int, None, None]:
        "Iteration is sorted by keys"
        for key in self.sortedKeys:
            yield key

    def __len__(self) -> int:
        return len(self.map)

    def __contains__(self, key: object) -> bool:
        return self.map.__contains__(key)


    def __str__(self) -> str:
        ret = "SortedDict({"
        comma = False
        for key, value in self.items():
            if comma:
                ret += ", "
            ret += f"{repr(key)}: {repr(value)}"
            comma = True
        ret += "})"
        return ret

    def __repr__(self) -> str:
        return self.__str__()
