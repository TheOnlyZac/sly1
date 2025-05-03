#!/usr/bin/env python3

# SPDX-FileCopyrightText: © 2022-2024 Decompollaborate
# SPDX-License-Identifier: MIT

from __future__ import annotations

import argparse
from pathlib import Path
import requests # type: ignore

from .. import utils
from .. import progress_stats
from . import progress


def getFrogressEntriesFromStats(totalStats: progress_stats.ProgressStats, progressPerFolder: dict[str, progress_stats.ProgressStats], verbose: bool=False) -> dict[str, int]:
    entries: dict[str, int] = {}
    if verbose:
        progress_stats.ProgressStats.printHeader()
        totalStats.print("all", totalStats)
        print()

    entries.update(totalStats.getAsFrogressEntry("all"))

    for folder, statsEntry in progressPerFolder.items():
        if verbose:
            statsEntry.print(folder, totalStats)
        entries.update(statsEntry.getAsFrogressEntry(folder))

    if verbose:
        print()
    return entries

def uploadEntriesToFrogress(entries: dict[str, int], category: str, url: str, apikey: str|None=None, verbose: bool=False):
    if verbose:
        print(f"Publishing entries to {url}")
        for key, value in entries.items():
            print(f"\t{key}: {value}")

    if not apikey:
        if verbose:
            print("Missing apikey, exiting without uploading")
        return 1

    data = utils.getFrogressDataDict(apikey, utils.getFrogressCategoriesDict({category: entries}))

    r = requests.post(url, json=data)
    r.raise_for_status()
    if verbose:
        print("Done!")
    return 0


def doUploadFrogress(mapPath: Path, asmPath: Path, nonmatchingsPath: Path, project: str, version: str, category: str, baseurl: str, apikey: str|None=None, verbose: bool=False, checkFunctionFiles: bool=True) -> int:
    if not mapPath.exists():
        print(f"Could not find mapfile at '{mapPath}'")
        return 1

    totalStats, progressPerFolder = progress.getProgress(mapPath, asmPath, nonmatchingsPath, checkFunctionFiles=checkFunctionFiles)

    entries: dict[str, int] = getFrogressEntriesFromStats(totalStats, progressPerFolder, verbose)

    url = utils.generateFrogressEndpointUrl(baseurl, project, version)
    return uploadEntriesToFrogress(entries, category, url, apikey=apikey, verbose=verbose)


def processArguments(args: argparse.Namespace):
    mapPath: Path = args.mapfile
    asmPath: Path = args.asmpath
    nonmatchingsPath: Path = args.nonmatchingspath
    project: str = args.project
    version: str = args.version
    category: str = args.category
    baseurl: str = args.baseurl
    apikey: str|None = args.apikey
    verbose: bool = args.verbose
    checkFunctionFiles: bool = not args.avoid_function_files

    exit(doUploadFrogress(mapPath, asmPath, nonmatchingsPath, project, version, category, baseurl, apikey, verbose, checkFunctionFiles))

def addSubparser(subparser: argparse._SubParsersAction[argparse.ArgumentParser]):
    parser = subparser.add_parser("upload_frogress", help="Uploads current progress of the matched functions to frogress (https://github.com/decompals/frogress).")

    parser.add_argument("mapfile", help="Path to a map file", type=Path)
    parser.add_argument("asmpath", help="Path to asm folder", type=Path)
    parser.add_argument("nonmatchingspath", help="Path to nonmatchings folder", type=Path)
    parser.add_argument("project", help="Project slug")
    parser.add_argument("version", help="Version slug")
    parser.add_argument("category", help="Category slug")
    parser.add_argument("--baseurl", help="API base URL", default="https://progress.deco.mp")
    parser.add_argument("--apikey", help="API key. Dry run is performed if this option is omitted")
    parser.add_argument("-v", "--verbose", action="store_true")
    parser.add_argument("-f", "--avoid-function-files", help="Avoid checking if the assembly file for a function exists as a way to determine if the function has been matched or not", action="store_true")

    parser.set_defaults(func=processArguments)
