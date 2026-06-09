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
- **Headless per-symbol match check** (the TUI needs a tty; use this for
  automated/iterative work): `./scripts/match.sh <unit> <MangledSymbol>`, e.g.
  `./scripts/match.sh P2/water InitWater__FP5WATER`. It dual-builds and diffs the
  symbol's instructions **and** relocations, printing `MATCH` or the diff.
- **Inspect a struct's real compiled layout**:
  `./scripts/structoff.sh <header> 'EXPR' ['EXPR' ...]`, e.g.
  `./scripts/structoff.sh water.h 'sizeof(WATER)' '(int)(long)&((WATER*)0)->grfso'`.
  Always probe with the EE compiler — host gcc gives wrong offsets (different
  EABI alignment), and the `/* 0xNN */` header comments are not the compiled
  offsets.
- Mechanics behind those scripts: the build defines `-DSKIP_ASM`, so the real
  ELF is built from C; `INCLUDE_ASM` expands to nothing under `SKIP_ASM` and
  pulls in the `.s` otherwise. Objdiff dual-builds `obj/target/*.o` (asm) vs
  `obj/current/*.o` (your C) via `python3 configure.py --objects && ninja`.
  objdump prints every unresolved call as `jal 0 <First>`, so a real check must
  compare the `R_MIPS_26` reloc rows too (`match.sh` does).

## Suggested matching workflow

1. Read the target `.s` in `asm/nonmatchings/<unit>/<Symbol>.s` and the function
   prototype in the header. Note every struct offset it touches.
2. Lay out the struct: probe sizes/offsets with `scripts/structoff.sh`, then add
   fields to the (sub)struct via `STRUCT_PADDING` to land at absolute offsets —
   **never grow the base structs** (see below).
3. Write the C under the `INCLUDE_ASM` line, wrapped in `#ifdef SKIP_ASM` /
   `#endif`, so the asm is still available as the diff target.
4. Loop: edit → `scripts/match.sh <unit> <Symbol>` → adjust for GCC 2.95 quirks
   (see tips below) until it prints `MATCH`.
5. When matched, delete the `INCLUDE_ASM` line and the `#ifdef SKIP_ASM`/`#endif`
   wrapper, leaving plain C.
6. After the file is done (or after any shared-header edit), run
   `./scripts/build.sh` and confirm `out/SCUS_971.98: OK`.

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

- Keep the base structs as-is. Lay out only the subclass's **own** fields inside
  the subclass via leading `STRUCT_PADDING` from `sizeof(base)`.
- Do **not** redeclare base fields that live past the base's truncated end
  (e.g. SO fields between `0x2d0` and a subclass's first own field) as members of
  the subclass. Doing so pins the subclass layout to the *current* `sizeof(base)`
  in two places, so when the base is later grown to its true size the redeclared
  fields collide/shift and fail the checksum — and it misrepresents whose fields
  they are. Reach such base fields via `STRUCT_OFFSET` instead, and delete the
  redeclaration once it has no compiled users.
- For a base field accessed through a generic `SO*` (e.g. the `grfso` flag word
  at `0x538`), reach it with `STRUCT_OFFSET(pSo, 0x538, int)` (defined in
  `include/common.h`) — `STRUCT_OFFSET(ptr, off, type)` dereferences a typed
  field at a raw byte offset, and `STRUCT_OFFSET_INDEX(ptr, off, type, i)` does
  the same for an array element (it bakes in the `(i << 2) + off` ordering that
  matches GCC's codegen). Prefer these over an ad-hoc cast or a redeclared
  member so the offset access is self-documenting; note the field's meaning in a
  comment.
- The subclass's leading `STRUCT_PADDING` is itself still calibrated to the
  current `sizeof(base)` — that dependency is inherent to absolute-offset layout
  and unavoidable; `STRUCT_OFFSET` only removes the *extra* coupling from
  redeclaring base fields.

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
