"""
Configures the project for building. Invokes splat to split the binary and
creates build files for ninja.
"""

#! /usr/bin/env python3
import argparse
import os
import shutil
import sys
import json
import re
from pathlib import Path
from typing import List, Set

import ninja_syntax
import splat
import splat.scripts.split as split
from splat.segtypes.linker_entry import LinkerEntry

# MARK: Constants
ROOT = Path(__file__).parent.resolve()
TOOLS_DIR = ROOT / "tools"
OUTDIR = "out"

YAML_FILE = Path("config/sly1.yaml")
BASENAME = "SCUS_971.98"
LD_PATH = f"{BASENAME}.ld"
ELF_PATH = f"{OUTDIR}/{BASENAME}"
MAP_PATH = f"{OUTDIR}/{BASENAME}.map"
PRE_ELF_PATH = f"{OUTDIR}/{BASENAME}.elf"

COMMON_INCLUDES = "-Iinclude -isystem include/sdk/ee -isystem include/gcc"

CC_DIR = f"{TOOLS_DIR}/cc/bin"
COMMON_COMPILE_FLAGS = (
    f"-x c++ -B{TOOLS_DIR}/cc/lib/gcc-lib/ee/2.95.2/ -O2 -G0 -ffast-math"
)

WIBO = TOOLS_DIR / "wibo-i686"
WINECMD = f"{WIBO}" if WIBO.exists() else "WINEDEBUG=-all wine"

COMPILE_CMD = f"{CC_DIR}/ee-gcc.exe -c {COMMON_INCLUDES} {COMMON_COMPILE_FLAGS} $in"
if sys.platform == "linux":
    COMPILE_CMD = (
        f"{WINECMD} {CC_DIR}/ee-gcc.exe -c {COMMON_INCLUDES} {COMMON_COMPILE_FLAGS} $in"
    )

CATEGORY_MAP = {
    "P2": "Engine",
    "splice": "Splice",
    "ps2t": "Tooling",
    "sce": "Libs",
    "data": "Data",
}

# Segment types that should be assembled
ASSEMBLABLE_TYPES = (
    splat.segtypes.common.asm.CommonSegAsm,
    splat.segtypes.common.data.CommonSegData,
    splat.segtypes.common.databin.CommonSegDatabin,
    splat.segtypes.common.rodatabin.CommonSegRodatabin,
    splat.segtypes.common.textbin.CommonSegTextbin,
    splat.segtypes.common.bin.CommonSegBin,
)

# Segment types that should be compiled
COMPILABLE_TYPES = (splat.segtypes.common.c.CommonSegC,)


def clean():
    """
    Clean all products of the build process.
    """
    files_to_clean = [
        ".splache",
        ".ninja_log",
        "build.ninja",
        "permuter_settings.toml",
        "objdiff.json",
        LD_PATH,
    ]
    for filename in files_to_clean:
        if os.path.exists(filename):
            os.remove(filename)

    shutil.rmtree("asm", ignore_errors=True)
    shutil.rmtree("assets", ignore_errors=True)
    shutil.rmtree("obj", ignore_errors=True)
    shutil.rmtree("out", ignore_errors=True)


def write_permuter_settings():
    """
    Write the permuter settings file, comprising the compiler and assembler commands.
    """
    with open("permuter_settings.toml", "w", encoding="utf-8") as f:
        f.write(
            f"""compiler_command = "{COMPILE_CMD} -D__GNUC__"
assembler_command = "mips-linux-gnu-as -march=r5900 -mabi=eabi -Iinclude"
compiler_type = "gcc"

[preserve_macros]

[decompme.compilers]
"tools/build/cc/gcc/gcc" = "ee-gcc2.96"
"""
        )


# MARK: Build
def generate_ninja_build(
    linker_entries: List[LinkerEntry],
    skip_checksum=False,
    objects_only=False,
    dual_objects=False,
):
    """
    Generate ninja build rules for objects and the final ELF file.
    If objects_only is True, only build objects and skip linking/checksum.
    If dual_objects is True, build objects twice: once normally, once with -DSKIP_ASM.
    """
    built_objects: Set[Path] = set()
    objdiff_units = []  # For objdiff.json

    def compute_object_path(obj_path: Path, out_dir: str = None) -> Path:
        """Compute the final object path, stripping .s or .c extensions if needed."""
        if not out_dir:
            return obj_path

        # Strip .s/.c extensions or handle .c.o/.s.o cases
        if obj_path.suffix == ".o" and obj_path.with_suffix("").suffix in [".s", ".c"]:
            stem = obj_path.with_suffix("").stem
        else:
            stem = obj_path.stem

        return Path(out_dir) / (stem + ".o")

    def collect_objdiff_unit(object_path: Path, src_path: Path) -> None:
        """Collect objdiff metadata for a compilation unit."""
        if not src_path or "target" not in str(object_path):
            return

        # Compute relative path for name
        try:
            if src_path.parts[0] in ["asm", "src"]:
                rel = Path(*src_path.parts[1:])
            else:
                rel = src_path
            name = str(rel.with_suffix(""))
        except (IndexError, ValueError):
            name = str(src_path.with_suffix(""))

        target_path = str(object_path)

        # Check if source file exists in src/
        src_base = rel.with_suffix("")
        has_src = any(Path("src").rglob(src_base.name + ext) for ext in [".c", ".cpp"])

        # Determine categories
        categories = [name.split("/")[0]]
        if "P2/splice/" in name:
            categories.append("splice")
        elif "P2/ps2t" in name:
            categories.append("ps2t")

        unit = {
            "name": name,
            "target_path": target_path,
            "metadata": {"progress_categories": categories},
        }

        if has_src:
            # Replace 'target' segment with 'current' in path
            op = Path(object_path)
            parts = list(op.parts)
            for idx, part in enumerate(parts):
                if part == "target":
                    parts[idx] = "current"
                    break
            unit["base_path"] = str(Path(*parts))

        objdiff_units.append(unit)

    def build_object(
        object_path: Path,
        src_paths: List[Path],
        rule: str,
        out_dir: str = None,
        extra_flags: str = "",
        collect_objdiff: bool = False,
    ):
        """Build a single object file."""
        final_path = compute_object_path(object_path, out_dir)

        if final_path.suffix == ".o":
            built_objects.add(final_path)

        build_vars = {"cflags": extra_flags} if extra_flags else {}

        ninja.build(
            outputs=[str(final_path)],
            rule=rule,
            inputs=[str(s) for s in src_paths],
            variables=build_vars,
        )

        if collect_objdiff and src_paths:
            collect_objdiff_unit(final_path, src_paths[0])

    with open(str(ROOT / "build.ninja"), "w", encoding="utf-8") as f:
        ninja = ninja_syntax.Writer(f, width=9999)

        # MARK: Rules
        cross = "mips-linux-gnu-"

        ld_args = "-EL -T config/undefined_syms_auto.txt -T config/undefined_funcs_auto.txt -Map $mapfile -T $in -o $out --no-warn-rwx-segments"

        ninja.rule(
            "as",
            description="as $in",
            command=f"cpp {COMMON_INCLUDES} $in -o  - | {cross}as -no-pad-sections -EL -march=5900 -mabi=eabi -Iinclude -o $out",
        )

        ninja.rule(
            "cc",
            description="cc $in",
            command=f"{COMPILE_CMD} $cflags -o $out && {cross}strip $out -N dummy-symbol-name",
        )

        ninja.rule(
            "ld",
            description="link $out",
            command=f"{cross}ld {ld_args}",
        )

        ninja.rule(
            "sha1sum",
            description="sha1sum $in",
            command="sha1sum -c $in && touch $out",
        )

        ninja.rule(
            "elf",
            description="elf $out",
            command=f"{cross}objcopy $in $out -O binary",
        )

        # MARK: Object compilation
        # Build all the objects
        for entry in linker_entries:
            seg = entry.segment

            if seg.type[0] == ".":
                continue

            if entry.object_path is None:
                continue

            # Determine rule based on segment type
            rule = None
            if isinstance(seg, COMPILABLE_TYPES):
                rule = "cc"
            elif isinstance(seg, ASSEMBLABLE_TYPES):
                rule = "as"
            else:
                print(f"ERROR: Unsupported build segment type {seg.type}")
                sys.exit(1)

            # Build objects (single or dual mode)
            if dual_objects:
                build_object(
                    entry.object_path,
                    entry.src_paths,
                    rule,
                    out_dir="obj/target",
                    collect_objdiff=True,
                )
                build_object(
                    entry.object_path,
                    entry.src_paths,
                    rule,
                    out_dir="obj/current",
                    extra_flags="-DSKIP_ASM",
                )
            else:
                build_object(entry.object_path, entry.src_paths, rule)

        if objects_only:
            # Write objdiff.json if dual_objects (i.e. --objects)
            if dual_objects:
                objdiff = {
                    "$schema": "https://raw.githubusercontent.com/encounter/objdiff/main/config.schema.json",
                    "custom_make": "ninja",
                    "custom_args": [],
                    "build_target": False,
                    "build_base": True,
                    "watch_patterns": [
                        "src/**/*.c",
                        "src/**/*.cp",
                        "src/**/*.cpp",
                        "src/**/*.cxx",
                        "src/**/*.h",
                        "src/**/*.hp",
                        "src/**/*.hpp",
                        "src/**/*.hxx",
                        "src/**/*.s",
                        "src/**/*.S",
                        "src/**/*.asm",
                        "src/**/*.inc",
                        "src/**/*.py",
                        "src/**/*.yml",
                        "src/**/*.txt",
                        "src/**/*.json",
                    ],
                    "units": objdiff_units,
                    "progress_categories": [
                        {"id": id, "name": name} for id, name in CATEGORY_MAP.items()
                    ],
                }
                with open("objdiff.json", "w", encoding="utf-8") as objdiff_file:
                    json.dump(objdiff, objdiff_file, indent=2)
            return

        ninja.build(
            PRE_ELF_PATH,
            "ld",
            LD_PATH,
            implicit=[str(obj) for obj in built_objects],
            variables={"mapfile": MAP_PATH},
        )

        ninja.build(
            ELF_PATH,
            "elf",
            PRE_ELF_PATH,
        )

        if not skip_checksum:
            ninja.build(
                ELF_PATH + ".ok",
                "sha1sum",
                "config/checksum.sha1",
                implicit=[ELF_PATH],
            )
        else:
            print("Skipping checksum step")


# MARK: Short loop fix
# Pattern to workaround unintended nops around loops
COMMENT_PART = r"\/\* (.+) ([0-9A-Z]{2})([0-9A-Z]{2})([0-9A-Z]{2})([0-9A-Z]{2}) \*\/"
INSTRUCTION_PART = r"(\b(bne|bnel|beq|beql|bnez|bnezl|beqzl|bgez|bgezl|bgtz|bgtzl|blez|blezl|bltz|bltzl|b)\b.*)"
OPCODE_PATTERN = re.compile(f"{COMMENT_PART}  {INSTRUCTION_PART}")

PROBLEMATIC_FUNCS = {
    "RefOpForEach__FiP4CRefP6CFrame",                            # P2/splice/bif
    "PredictAsegEffect__FP4ASEGffP3ALOT3iP6VECTORP7MATRIX3T6T6", # P2/aseg
    "ProjectBlipgTransform__FP5BLIPGfi",                         # P2/blip
    "ExplodeExplsExplso__FP5EXPLSP6EXPLSO",                      # P2/emitter
    "ApplyDzg__FP3DZGiPiPPP2SOff",                               # P2/dzg
    "UpdateJtActive__FP2JTP3JOYf",                               # P2/jt
    "RebuildLightVifs__FP5LIGHT",                                # P2/light
    "AddMatrix4Matrix4__FP7MATRIX4N20",                          # P2/mat
    "FInvertMatrix__FiPfT1",                                     # P2/mat
    "RenderMsGlobset__FP2MSP2CMP2RO",                            # P2/ms
    "BounceRipgRips__FP4RIPG",                                   # P2/rip
    "FUN_001aea70",                                              # P2/screen
    "UpdateShadow__FP6SHADOWf",                                  # P2/shadow
    "LoadShadersFromBrx__FP18CBinaryInputStream",                # P2/shd
    "FillShaders__Fi",                                           # P2/shd
    "UpdateStepPhys__FP4STEP",                                   # P2/step
    "DrawTvBands__FP2TVR4GIFS",                                  # P2/tv
    "FIgnoreUbgIntersection__FP3UBGP2SO",                        # P2/ub
    "PwarpFromOid__F3OIDT0",                                     # P2/xform
    "TriggerWarp__FP4WARP"                                       # P2/xform
}

def replace_instructions_with_opcodes(asm_folder: Path) -> None:
    """
    Replace branch instructions with raw opcodes for functions that trigger the short loop bug.
    """
    nm_folder = ROOT / asm_folder / "nonmatchings"

    for p in nm_folder.rglob("*.s"):
        if p.stem not in PROBLEMATIC_FUNCS:
            continue

        with p.open("r") as file:
            content = file.read()

        if re.search(OPCODE_PATTERN, content):
            # Reference found
            # Embed the opcode, we have to swap byte order for correct endianness
            content = re.sub(
                OPCODE_PATTERN,
                r"/* \1 \2\3\4\5 */  .word      0x\5\4\3\2 /* \6 */",
                content,
            )

            # Write the updated content back to the file
            with p.open("w") as file:
                file.write(content)


# MARK: Main
def main():
    """
    Main function, parses arguments and runs the configuration.
    """
    parser = argparse.ArgumentParser(description="Configure the project")
    parser.add_argument(
        "-c",
        "--clean",
        help="Clean artifacts and build",
        action="store_true",
    )
    parser.add_argument(
        "-C",
        "--clean-only",
        help="Only clean artifacts",
        action="store_true",
    )
    parser.add_argument(
        "-s",
        "--skip-checksum",
        help="Skip the checksum step",
        action="store_true",
    )
    parser.add_argument(
        "--objects",
        help="Build objects to obj/target and obj/current (with -DSKIP_ASM), skip linking and checksum",
        action="store_true",
    )
    parser.add_argument(
        "-noloop",
        "--no-short-loop-workaround",
        help="Do not replace branch instructions with raw opcodes for functions that trigger the short loop bug",
        action="store_true",
    )
    args = parser.parse_args()

    if args.clean or args.clean_only:
        clean()
        if args.clean_only:
            return

    split.main([YAML_FILE], modes="all", verbose=False)

    linker_entries = split.linker_writer.entries

    if args.objects:
        generate_ninja_build(
            linker_entries, skip_checksum=True, objects_only=True, dual_objects=True
        )
    else:
        generate_ninja_build(linker_entries, args.skip_checksum)

    write_permuter_settings()

    if not args.no_short_loop_workaround:
        replace_instructions_with_opcodes(split.config["options"]["asm_path"])


if __name__ == "__main__":
    main()
