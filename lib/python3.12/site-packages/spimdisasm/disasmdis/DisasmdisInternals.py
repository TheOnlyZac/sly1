#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
from typing import Generator
import rabbitizer
import sys

from .. import common
from .. import frontendCommon as fec

from .. import __version__

PROGNAME = "disasmdis"


def getToolDescription() -> str:
    return "CLI tool to disassemble multiples instructions passed as argument"

def addOptionsToParser(parser: argparse.ArgumentParser) -> argparse.ArgumentParser:
    parser.add_argument("-V", "--version", action="version", version=f"%(prog)s {__version__}")

    parser.add_argument("input", help="Hex words to be disassembled. Leading '0x' must be omitted", nargs='+')

    parser.add_argument("--endian", help="Set the endianness of input files. Defaults to 'big'", choices=["big", "little", "middle"], default="big")
    parser.add_argument("--instr-category", help="The instruction category to use when disassembling every passed instruction. Defaults to 'cpu'", choices=["cpu", "rsp", "r3000gte", "r4000allegrex", "r5900"])
    parser.add_argument("--pseudos", help="Enables all pseudo-instructions supported by rabbitizer", action="store_true")

    return parser

def getArgsParser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description=getToolDescription(), prog=PROGNAME, formatter_class=common.Utils.PreserveWhiteSpaceWrapRawTextHelpFormatter)
    return addOptionsToParser(parser)


def applyArgs(args: argparse.Namespace) -> None:
    common.GlobalConfig.ENDIAN = common.InputEndian(args.endian)
    if args.pseudos:
        rabbitizer.config.pseudos_enablePseudos = True
    else:
        rabbitizer.config.pseudos_enablePseudos = False

def getWordFromStr(inputStr: str) -> int:
    arr = bytearray()
    for index in range(0, len(inputStr), 2):
        byteStr = inputStr[index:index+2]
        temp = 0
        for char in byteStr:
            temp *= 16
            temp += int(char, 16)
        arr.append(temp)
    while len(arr) % 4 != 0:
        arr.append(0)
    return common.Utils.bytesToWords(arr)[0]

def wordGeneratorFromStrList(inputlist: list|None) -> Generator[int, None, None]:
    if inputlist is None:
        return

    wordStr = ""
    for inputStr in inputlist:
        for character in inputStr:
            if character not in "0123456789abcdefABCDEF":
                continue
            wordStr += character
            if len(wordStr) == 8:
                yield getWordFromStr(wordStr)
                wordStr = ""

    if len(wordStr) > 0:
        yield getWordFromStr(wordStr)

def getWordListFromStdin() -> Generator[int, None, None]:
    if sys.stdin.isatty():
        return

    lines = ""
    try:
        for line in sys.stdin:
            lines += line
    except KeyboardInterrupt:
        pass
    for word in wordGeneratorFromStrList(lines.split(" ")):
        yield word


def processArguments(args: argparse.Namespace) -> int:
    applyArgs(args)

    category = fec.FrontendUtilities.getInstrCategoryFromStr(args.instr_category)

    for word in getWordListFromStdin():
        instr = rabbitizer.Instruction(word, category=category)
        print(instr.disassemble())

    for word in wordGeneratorFromStrList(args.input):
        instr = rabbitizer.Instruction(word, category=category)
        print(instr.disassemble())

    return 0

def addSubparser(subparser: argparse._SubParsersAction[argparse.ArgumentParser]) -> None:
    parser = subparser.add_parser("disasmdis", help=getToolDescription(), formatter_class=common.Utils.PreserveWhiteSpaceWrapRawTextHelpFormatter)

    addOptionsToParser(parser)

    parser.set_defaults(func=processArguments)


def disasmdisMain() -> int:
    args = getArgsParser().parse_args()

    return processArguments(args)
