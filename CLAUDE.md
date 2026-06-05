# CLAUDE.md

Guidance for working in this repo (a WIP decompilation of the PS2 game *Sly
Cooper and the Thievius Raccoonus*, NTSC-U `SCUS_971.98`). The goal is matching
C/C++ source: code that compiles (with the EE GCC 2.95 toolchain under Wine) to
bytes identical to the original executable.

## Conventions & style

Follow [docs/STYLEGUIDE.md](docs/STYLEGUIDE.md) for naming (Hungarian-style
prefixes: `p`ointer, `c`ount, `f`lag, `g_`lobal, `m_`ember…), capitalization
(`ALLCAPS` structs/enums, `UpperCamelCase` functions, `lowerCamelCase`
locals), brace-on-new-line + 4-space indent, and Doxygen comments. See
[docs/CONTRIBUTING.md](docs/CONTRIBUTING.md) for the end-to-end matching
workflow. Prefer official symbol names from the May 19 2002 prototype; when
unknown, use a clear descriptive name (offset-suffixed placeholders like
`unk_0x360` are acceptable for not-yet-understood struct fields).

## Build & verify

- Full build + checksum: `./scripts/build.sh` → expect `out/SCUS_971.98: OK`.
  This (`sha1sum -c config/checksum.sha1`) is the ground-truth "did I break
  anything" check — run it after touching shared headers.
- Per-function diff (interactive TUI): `./scripts/diff.sh <MangledName> [P2/unit]`.
- The build defines `-DSKIP_ASM`, so the real ELF is built from C; `INCLUDE_ASM`
  expands to nothing under `SKIP_ASM` and pulls in the `.s` otherwise. Objdiff
  dual-builds `obj/target/*.o` (asm) vs `obj/current/*.o` (your C, `-DSKIP_ASM`)
  via `python3 configure.py --objects && ninja`.
- Headless one-shot verify (the TUI needs a tty): build the dual objects, then
  `objdump -dr obj/{target,current}/<unit>.o`, slice out the symbol, strip the
  leading address/opcode-byte columns, and diff. Equal instructions **and**
  relocations = a match (objdump prints all unresolved calls as `jal 0 <First>`,
  so always compare the `R_MIPS_26` reloc rows too).
- To inspect a struct's real compiled layout, compile an address-of/`sizeof`
  probe with the EE compiler and read the immediates:
  `wine tools/cc/bin/ee-gcc.exe -c -Iinclude -isystem include/sdk/ee -isystem include/gcc -x c++ -B$PWD/tools/cc/lib/gcc-lib/ee/2.95.2/ -O2 -G0 -ffast-math probe.cpp`.

## Critical: do NOT grow engine base struct sizes

The base classes `LO` → `ALO` → `SO` are intentionally **truncated**:
`sizeof(SO)` compiles to `0x2d0`, even though the real game's `SO` is `0x550`.
The `/* 0xNN */` offset comments in the base headers are aspirational targets,
**not** the compiled offsets (e.g. `ALO::grfzon` compiles to `0x7c`, documented
`0x88`).

Each subclass instead places its own fields at correct **absolute** offsets
using explicit `STRUCT_PADDING(...)` **calibrated to the current truncated base
size** (e.g. `struct JT` pads ~1090 words to land `paloMine` at `0x1518`).

Growing `SO`/`ALO`/`LO` to their "true" size shifts every subclass's fields and
**fails the checksum** — the breakage surfaces in compiled-C accessors of other
subclasses (e.g. `SetFsp` reading `JT`), not in your file. So when reversing a
new subclass:

- Keep the base structs as-is. Lay out the whole object inside the subclass via
  leading `STRUCT_PADDING` from `sizeof(base)` — including fields that
  semantically belong to the SO base but live past `0x2d0`.
- For a base field accessed through a generic `SO*` (e.g. the `grfso` flag word
  at `0x538`), cast to the subclass type to reach the offset; note it in a
  comment.

## GCC 2.95 matching tips

Matching is mostly about steering this old compiler's scheduler/allocator:

- `x & ~A & ~B` with two constant masks gets folded into one `&` by the front
  end / combiner. To force two separate ANDs (one load, two ANDs, one store),
  load into a local and split into `tmp &= ~A; tmp &= ~B;`.
- Register choice is driven by variable live-ranges: reusing one variable pins
  it to a register across its whole range; use a *fresh* local for a late block
  to let the allocator pick the register the target uses.
- Mirror the original's pointer/index reuse — introduce locals like
  `MRG *pmrg = &x->mrg;` or `int c = p->count;` when the asm keeps a value in a
  register rather than reloading it.
- Store ordering: GCC may reverse independent store pairs; reorder the source
  statements to compensate.
