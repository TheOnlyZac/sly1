#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse

import mapfile_parser


def mapfileParserMain():
    parser = argparse.ArgumentParser(description="Interface to call any of the mapfile_parser's CLI utilities", prog="mapfile_parser")

    parser.add_argument("-V", "--version", action="version", version=f"%(prog)s {mapfile_parser.__version__}")

    subparsers = parser.add_subparsers(description="action", help="the action to perform", required=True)

    mapfile_parser.frontends.bss_check.addSubparser(subparsers)
    mapfile_parser.frontends.first_diff.addSubparser(subparsers)
    mapfile_parser.frontends.jsonify.addSubparser(subparsers)
    mapfile_parser.frontends.pj64_syms.addSubparser(subparsers)
    mapfile_parser.frontends.progress.addSubparser(subparsers)
    mapfile_parser.frontends.sym_info.addSubparser(subparsers)
    mapfile_parser.frontends.symbol_sizes_csv.addSubparser(subparsers)
    mapfile_parser.frontends.upload_frogress.addSubparser(subparsers)

    args = parser.parse_args()
    args.func(args)


if __name__ == "__main__":
    mapfileParserMain()
