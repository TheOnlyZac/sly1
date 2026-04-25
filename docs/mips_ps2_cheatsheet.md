# Decompilation Cheatsheet
> Complete reference for the sly1 decomp project · [TheOnlyZac/sly1](https://github.com/TheOnlyZac/sly1)

---

## 0 · Types, Sizes & Quick Hex Reference

### A · Fundamental Types — size, alignment, MIPS instruction

| C Type | Alias | Size | Hex | Align | MIPS Load/Store | Range |
|--------|-------|------|-----|-------|-----------------|-------|
| `char` / `s8` | `int8_t` | 1 byte | `0x01` | 1 | `lb` / `sb` | −128 … 127 |
| `uchar` / `u8` | `uint8_t` | 1 byte | `0x01` | 1 | `lbu` / `sb` | 0 … 255 |
| `short` / `s16` | `int16_t` | 2 bytes | `0x02` | 2 | `lh` / `sh` | −32,768 … 32,767 |
| `ushort` / `u16` | `uint16_t` | 2 bytes | `0x02` | 2 | `lhu` / `sh` | 0 … 65,535 |
| `int` / `s32` | `int32_t` | 4 bytes | `0x04` | 4 | `lw` / `sw` | −2,147,483,648 … 2,147,483,647 |
| `uint` / `u32` | `uint32_t` | 4 bytes | `0x04` | 4 | `lw` / `sw` | 0 … 4,294,967,295 |
| `float` | `f32` | 4 bytes | `0x04` | 4 | `lwc1` / `swc1` | ±3.4e38 (~7 decimals) |
| `long` / `s64` | `int64_t` | 8 bytes | `0x08` | 8 | `ld` / `sd` | −9.2e18 … 9.2e18 |
| `double` | `f64` | 8 bytes | `0x08` | 8 | `ldc1` / `sdc1` | ±1.8e308 (~15 decimals) |
| `ptr` (PS2) | `void*` | 4 bytes | `0x04` | 4 | `lw` / `sw` | 32-bit address — like int |
| `VECTOR` | 4× float | 16 bytes | `0x10` | 16 | `lq` / `sq` | x, y, z, w |
| `MATRIX3` | 9× float | 36 bytes | `0x24` | 4 | 9× `lwc1`/`swc1` | 3×3 rotation |
| `MATRIX4` | 16× float | 64 bytes | `0x40` | 16 | 4× `lq`/`sq` | 4×4 transform |

### B · Hex → Decimal — common offsets & sizes

| Hex | Decimal | Meaning | Hex | Decimal | Meaning |
|-----|---------|---------|-----|---------|---------|
| `0x01` | 1 | 1 byte (char/bool) | `0x10` | 16 | 1 VECTOR (4 floats) |
| `0x02` | 2 | 1 short | `0x14` | 20 | 5 ints |
| `0x04` | 4 | 1 int / float / ptr | `0x18` | 24 | 6 ints |
| `0x08` | 8 | 2 ints or 1 double | `0x20` | 32 | 8 ints / 2 VECTORs |
| `0x0C` | 12 | 3 ints | `0x24` | 36 | 1 MATRIX3 |
| `0x40` | 64 | 1 MATRIX4 | `0x80` | 128 | 32 ints |
| `0xB0` | 176 | 44 vtable entries (×4) | `0x100` | 256 | 64 ints |
| `0x400` | 1024 | 256 ints | `0x1000` | 4096 | 1 memory page |

### C · Struct alignment rules & padding

| Rule | Detail | Concrete Example |
|------|--------|-----------------|
| Natural alignment | A field of size N must be at a multiple-of-N offset. | `float(4)` → offset `0x04`, `0x08`, `0x0C`… never `0x03` |
| Auto padding | Compiler inserts silent bytes to respect alignment. | `char(1)` + 3 bytes padding + `int(4)` → offsets `0x00` then `0x04` |
| Struct size multiple | Total size is rounded up to the largest field alignment. | `struct { char; float; }` → 8 bytes, not 5 |
| C++ inheritance (PS2) | Parent fields precede child fields in memory. | `ACPB : public ACP` → ACP fields first at offset `0x00` |
| VECTOR = 0x10 (16 B) | Always 16-aligned — `lq`/`sq` require it on EE. | Valid offsets: `0x10`, `0x20`, `0x30`… An odd offset = instant bug |
| Field N offset calc | Sum sizes + paddings of all preceding fields. | `int(4)+float(4)+char(1)+pad(3)+ptr(4)` → 4th field at `0x0C` |

### D · Bits → bytes → hex — quick reference

| Unit | Value | Note |
|------|-------|------|
| 1 nibble | 4 bits | = 1 hex digit (0–F) |
| 1 byte | 8 bits | = 2 hex digits e.g. `0xFF` = 255 |
| 1 short | 16 bits | = 2 bytes = 4 hex digits |
| 1 int/ptr PS2 | 32 bits | = 4 bytes = 8 hex digits |
| 1 VECTOR | 128 bits | = 16 bytes = `0x10` |
| 1 MATRIX4 | 512 bits | = 64 bytes = `0x40` |
| `0xFF` | 255 | max u8 |
| `0xFFFF` | 65,535 | max u16 |
| `0xFFFFFFFF` | 4,294,967,295 | max u32 / invalid ptr |
| `0x80000000` | −2,147,483,648 | min s32 (sign bit) |
| N × `0x04` | N ints | offset of N ints/floats |
| N × `0x10` | N VECTORs | offset of N vectors |

---

## 1 · Integer Registers ($0 – $31)

| Number | Alias | Name | Role |
|--------|-------|------|------|
| `$0` | `$zero` | Zero | Always 0. `daddu $s0,$a0,$zero` = copy `$a0` into `$s0` |
| `$2–$3` | `$v0–$v1` | Value | Return value (`return x;`). `$v0` = primary integer result |
| `$4–$7` | `$a0–$a3` | Argument | Arguments 1–4. `$a0` = 1st arg, `$a1` = 2nd, etc. |
| `$8–$11` | `$a4–$a7` | Argument | PS2 Arguments 5–8 — EE extension, absent on standard MIPS/x86 |
| `$12–$15`, `$24–$25` | `$t0–$t9` | Temporary | Clobbered after `jal` — do not rely on them after a function call |
| `$16–$23` | `$s0–$s7` | Saved | Preserved across `jal`. Survive calls. Used to hold args. |
| `$26–$27` | `$k0–$k1` | Kernel | Reserved for OS — never used in game code |
| `$28` | `$gp` | Global pointer | Points to global variables (rare in Sly) |
| `$29` | `$sp` | Stack pointer | Top of stack. `addiu $sp,$sp,-N` allocates N bytes |
| `$30` | `$fp`/`$s8` | Frame pointer | Rarely used in MIPS — often reused as 9th saved register |
| `$31` | `$ra` | Return address | Return address. `jr $ra` = return. Saved with `sq` if fn makes `jal` calls |

---

## 2 · Float Registers ($f0 – $f31) — Coprocessor 1 (FPU)

| Number | Alias | Name | Role |
|--------|-------|------|------|
| `$f0–$f3` | `$fv0–$fv1` | Float return | Float return value of a function (`return 1.5f;`) |
| `$f12–$f15` | `$fa0–$fa1` | Float args 1–4 | First 4 float args — e.g. `float t, float svt` in EvaluateAcpb |
| `$f20–$f31` | `$fs0–$fs5` | Saved float | Preserved — survive `jal` (like `$s0–$s7` for integers) |
| `$f4–$f11`, `$f16–$f19` | `$ft0–$ft7` | Temp float | Temporaries — lost after `jal` |

> `swc1 $f12, 4(a0)` — stores float from `$f12` at `(a0+4)` → `*(float*)(pObj+4) = val`  
> `lwc1` = inverse: loads a float from memory

---

## 3 · Float Arithmetic Instructions (FPU)

| Instruction | C Equivalent | Note |
|-------------|-------------|------|
| `add.s $fd,$fs,$ft` | `$fd = $fs + $ft` | Float addition |
| `sub.s $fd,$fs,$ft` | `$fd = $fs - $ft` | Float subtraction |
| `mul.s $fd,$fs,$ft` | `$fd = $fs * $ft` | Float multiplication |
| `div.s $fd,$fs,$ft` | `$fd = $fs / $ft` | Float division (slow!) |
| `neg.s $fd,$fs` | `$fd = -$fs` | Float negation |
| `abs.s $fd,$fs` | `$fd = fabsf($fs)` | Float absolute value |
| `sqrt.s $fd,$fs` | `$fd = sqrtf($fs)` | Square root |
| `mov.s $fd,$fs` | `$fd = $fs` | Copy float register |
| `cvt.s.w $fd,$fs` | `$fd = (float)$fs` | Convert int → float |
| `cvt.w.s $fd,$fs` | `$fd = (int)$fs` | Convert float → int (truncates) |
| `c.eq.s $fs,$ft` | `if ($fs==$ft) CC=1` | Float compare — result in Condition Code |
| `c.lt.s $fs,$ft` | `if ($fs<$ft) CC=1` | Float compare (less than) |
| `c.le.s $fs,$ft` | `if ($fs<=$ft) CC=1` | Float compare (less or equal) |
| `bc1t .label` | `if (CC==1) goto label` | Branch if float condition true |
| `bc1f .label` | `if (CC==0) goto label` | Branch if float condition false |
| `mfc1 $rt,$fs` | `$rt (int) = $fs (float)` | Move float → int register (raw bits) |
| `mtc1 $rt,$fs` | `$fs (float) = $rt (int)` | Move int → float register (raw bits) |

---

## 4 · Memory Instructions (load / store)

| Instruction | Size | C Type | Note |
|-------------|------|--------|------|
| `lb` / `sb` | 8 bits | `signed char` | Load/store 1 signed byte. `lbu` = unsigned |
| `lh` / `sh` | 16 bits | `short` | Load/store 2 signed bytes. `lhu` = unsigned |
| `lw` / `sw` | 32 bits | `int` / `ptr` | Most common — int, pointer, float seen as bits |
| `lwc1` / `swc1` | 32 bits | `float` | Load/store to float register `$f` |
| `ldc1` / `sdc1` | 64 bits | `double` | Load/store double (pair of `$f`) |
| `lq` / `sq` | 128 bits | quadword | PS2 EE-specific — save/restore `$s` registers (128 bits each) |
| `ld` / `sd` | 64 bits | doubleword | Load/store 64-bit integer |

---

## 5 · Jumps, Branches & Integer Arithmetic

| Instruction | Effect / C Equivalent |
|-------------|----------------------|
| `jal FunctionX` | Calls FunctionX, `$ra` = next address (+ delay slot) |
| `jalr $2` | Calls function at address in `$2` — vtable / function pointer |
| `jr $31` / `$ra` | `return` — jumps to `$ra` |
| `beqz $r, .label` | `if ($r == 0) goto label` → `if (ptr == NULL)` / `if (x == 0)` |
| `bnez $r, .label` | `if ($r != 0) goto label` |
| `beq $r,$s, .label` | `if ($r == $s) goto label` |
| `bne $r,$s, .label` | `if ($r != $s) goto label` |
| `bltz $r, .label` | `if ($r < 0) goto label` |
| `bgez $r, .label` | `if ($r >= 0) goto label` |
| `addiu $d,$s,N` | `$d = $s + N` (signed 16-bit immediate) |
| `daddu $d,$a,$b` | `$d = $a + $b` 64-bit — equiv. `addu` on EE |
| `subu $d,$a,$b` | `$d = $a - $b` |
| `and`/`or`/`xor`/`nor` | Bitwise operations — `andi`/`ori`/`xori` = immediate version |
| `sll`/`srl`/`sra $d,$s,N` | Shift left / logical right / arithmetic right by N bits |
| `slt $d,$a,$b` | `$d = ($a < $b) ? 1 : 0` — often followed by `bnez` for an `if` |
| `mult`/`div $a,$b` | Result in `HI:LO`. Retrieve with `mfhi`/`mflo` |

> **⚠ DELAY SLOT** — The instruction AFTER a jump (`jal`, `jr`, `beqz`…) **ALWAYS executes before the jump** — this is MIPS hardware. It is indented in the ASM. In C it is invisible. Read the indented instruction FIRST, then the jump.

---

## 6 · C++ Demangling — Reading Mangled Names

The compiler encodes the full signature in the function name. Format: `FunctionName__[qualifier]Args`

| Mangled suffix | Decoded | Explanation |
|---------------|---------|-------------|
| `Fv` | `void` | No argument (Fv = Function void args) |
| `Fi` | `int` | One int argument |
| `Ff` | `float` | One float argument |
| `Fc` | `char` | One char argument |
| `FPc` | `char*` | Pointer to char (P = Pointer) |
| `FP10CLOCK` | `CLOCK*` | Pointer to struct — number = length of name |
| `FP3ALOffi` | `ALO*, float, float, int` | Multiple args — read left to right |
| `T3` | (3rd arg repeated) | T + digit = repeat type of arg N |
| `R3` | (ref to 3rd type) | R + digit = reference to an already-seen type |
| `__F...` | free function | No `this` — global/static function |
| `__CF...` | const method | `const` method (`this` = const ptr) |

**Examples:**

| Mangled name (in .s files) | Decoded C++ signature |
|---------------------------|----------------------|
| `ResetClock__FP5CLOCKf` | `void ResetClock(CLOCK*, float)` |
| `GetDifficulty__Fv` | `int/enum GetDifficulty(void)` |
| `EvaluateAcpb__FP4ACPBP3ALOffiP6VECTORT5` | `void EvaluateAcpb(ACPB*, ALO*, float, float, int, VECTOR*, VECTOR*)` |
| `OnDifficultyGameLoad__FP10DIFFICULTY` | `void OnDifficultyGameLoad(DIFFICULTY*)` |

> **Tip:** `c++filt MangledName` in terminal decodes automatically. Or paste at https://demangler.com

---

## 7 · Reading a Struct from ASM — Finding Offsets

Each `lw`/`sw` reveals a struct field. The offset in the instruction = byte position in the struct.

| ASM instruction | Field (tentative) | What we can deduce |
|-----------------|------------------|--------------------|
| `lw $2, 0x00($4)` | `field_0x00` | ptr->field at offset 0 — often the vtable (C++) or first member |
| `lw $2, 0x04($4)` | `field_0x04` | 2nd field (if 1st was 4 bytes) |
| `lw $2, 0x0C($4)` | `field_0x0C` | Offset 12 — e.g. `ACPB::ckvb` in EvaluateAcpb |
| `lw $2, 0x10($4)` | `field_0x10` | Offset 16 — e.g. `ACPB::akvb` (KVB* pointer) |
| `lw $2, 0xB0($4)` | `vtable[0xB0]` | vtable entry — virtual method #44 (`0xB0/4=44`) |
| `lwc1 $f0, 0x08($4)` | `field_0x08` | Float field at offset 8 — `lwc1` = it's a float, not an int |
| `lbu $2, 0x01($4)` | `field_0x01` | char/bool field at offset 1 (unsigned) |

| # | Step | Detail |
|---|------|--------|
| 1 | List all `lw`/`sw` | Each unique offset = a different field in the struct |
| 2 | Sort by offset | Field order in the struct = ascending offset order |
| 3 | Deduce type | `lw`=int/ptr, `lwc1`=float, `lbu`=char, `lhu`=short, `lq`=128-bit vector |
| 4 | Check inheritance | `ACPB : public ACP` → ACP fields come first (offset 0) |
| 5 | Name the fields | Compare with Ghidra + other functions accessing the same struct |

---

## 8 · Recurring Patterns in Sly 1

| Typical ASM pattern | C meaning |
|--------------------|-----------|
| `addiu $sp,$sp,-N` `sq $ra,X($sp)` `sq $sN,Y($sp)` | Allocates N bytes on stack. Saves `$ra` if fn makes calls. Saves the `$s` registers it will use. |
| `lq $sN,Y($sp)` `lq $ra,X($sp)` `jr $ra` `addiu $sp,$sp,N` | Restores `$s` and `$ra`. Frees the stack. The `addiu` is in the delay slot of `jr`. |
| `daddu $sN,$aM,$zero` | Copies an arg (`$a`) into a `$s` before a `jal` that would clobber `$a`. Very common. |
| `lw $2,0x0($obj)` `lw $2,0xXX($2)` `jalr $2` | `(*obj->vtable[offset])()` — C++ virtual method. 1st `lw` = deref vtable, 2nd = get fn, `jalr` = call. |
| `beqz $reg,.end` | `if (ptr == NULL) return` — classic guard before accessing a pointer or calling a vtable. |
| `lw $2,0x10($4)` | `$2 = pObj->field_0x10` — offset is the byte offset into the struct. |
| `addiu $t0,$zero,0` (init) `bne $t0,$t1,.loop` (test) `addiu $t0,$t0,1` (incr) | Classic `for(int i=0; i<n; i++)` pattern — the three parts are often scattered around the body. |
| `sll $2,$2,2` `add $2,$2,$base` `lw $2,0($2)` `jr $2` | Switch via jump table. Multiplies index by 4, indexes a pointer array, jumps. |

---

## 9 · Annotated Example — EvaluateAcpb (ASM → full C)

Real function from the project — 30 lines of ASM → 10 lines of C.

| ASM | Pattern | Translation |
|-----|---------|-------------|
| `addiu $sp,$sp,-0x40` | prologue | Allocates 64 bytes on the stack |
| `sq $18,0x20($sp)` `sq $17,0x10($sp)` `sq $16,0x0($sp)` `sq $31,0x30($sp)` | saves | Saves `$s2`,`$s1`,`$s0`,`$ra` — fn will make a `jal` |
| `daddu $18,$8,$0` `daddu $17,$7,$0` `daddu $16,$5,$0` | copy args | `$s2=grfeval` `$s1=svt` `$s0=palo` — will survive the `jal` |
| `lw $5,0x10($4)` `jal EvaluateAkvb` `lw $4,0xC($4)` | call 1 | `EvaluateAkvb(pacpb->ckvb, pacpb->akvb, t, svt, grfeval, ppos, pv)` — delay slot: `lw` executes before `jal`! |
| `beqz $16,.end` `lq $31,0x30($sp)` | null check | `if (palo==NULL) goto end` — delay slot restores `$ra` during test |
| `lw $2,0x0($16)` `lw $2,0xB0($2)` | vtable | `$2 = *(palo->vtable + 0xB0)` — fetch virtual method pointer |
| `beqz $2,.end` | null check 2 | `if (func==NULL) goto end` — vtable slot may be empty |
| `daddu $4,$16,$0` `daddu $5,$17,$0` `jalr $2` `daddu $6,$18,$0` | vtable call | `func(palo, ppos, pv)` via pointer. Delay slot: prepares `$a2=pv` during jump |
| `lq $18,..` `lq $17,..` `lq $16,..` `jr $31` `addiu $sp,$29,0x40` | epilogue | Restores `$s2`,`$s1`,`$s0`. `return`. Delay slot frees stack. |

**Resulting C code:**

```c
void EvaluateAcpb(ACPB *pacpb, ALO *palo, float t, float svt,
                  GRFEVAL grfeval, VECTOR *ppos, VECTOR *pv)
{
    EvaluateAkvb(pacpb->ckvb, pacpb->akvb, t, svt, grfeval, ppos, pv);
    // ckvb at offset 0x0C, akvb at 0x10 in ACPB (after ACP inheritance)

    if (palo != NULL) {
        void (*func)(...) = *(void(**)(...))((char*)(*((void**)palo)) + 0xB0);
        // Deref vtable + offset 0xB0 = virtual method #44
        if (func != NULL)
            func(palo, ppos, pv);
        // Conditional call — some ALOs don't implement this method
    }
}
```

---

## 10 · Ghidra — Practical Tips for Sly 1

| Shortcut / Action | Name | Use for decomp |
|-------------------|------|----------------|
| `G` | Go to address | Type a hex address (e.g. `0011FDD8`) to jump directly to a function |
| `F` | Search functions | Search a function by name — useful after importing symbols |
| `L` | Rename symbol | Rename a variable/function — essential to document as you go |
| `T` | Retype variable | Change a variable's type — key to reading structs correctly |
| `Ctrl+Shift+E` | Edit function sig | Edit full signature (name, args, return types) |
| `Ctrl+F` | Find in listing | Search in the ASM listing |
| `Ctrl+Shift+F` | Search all | Global search across the whole program (slow but powerful) |
| `X` (xref) | Find references | Who calls this function? Who accesses this variable? Indispensable. |
| `Ctrl+Z` | Undo | Undo renames/retypes — experiment without risk |
| Decompiler | Pseudo-C window | Shows approximate C next to ASM — starting point for matching |
| Import `.yaml` | Load symbols | Ghidra script to import `symbol_addrs.txt` — official names in UI |

**Workflow:** 1) Open `SCUS_971.98` → 2) Import project symbols (`scripts/`) → 3) Find fn by address (`G`) → 4) Read pseudo-C → 5) Compare with ASM in `.s` → 6) Name variables (`L`+`T`) to clarify → 7) Copy pseudo-C into `diff.sh` and iterate

---

## 11 · Common Errors & Troubleshooting

| Error | Symptom | Solution |
|-------|---------|----------|
| checksum failed | Compiled binary doesn't match original | C logic is wrong — op order, missing cast, wrong type. Re-check the diff. |
| `undefined reference to 'X__FP...'` | Linker can't find the function | `symbol_addrs.txt` missing entry or wrong address. Verify exact mangled name. |
| `ninja: no work to do` (diff.sh) | Script doesn't find the function | Wrong mangled name in command. Verify with `grep` in `symbol_addrs.txt`. |
| Matches decomp.me but not locally | Local compiler differs | GCC version or flag mismatch. Open a GitHub issue or ask on Discord. |
| Shifted registers in diff | Fn compiles but registers differ | Declaration order or cast issue. Reorder local variables. Try `volatile`. |
| Delay slot differs | Delay slot instruction doesn't match | Reorder calls or assignments so compiler optimizes in the right order. |
| `lq`/`sq` instead of `lw`/`sw` | Ghidra shows unexpected 128-bit accesses | Normal on PS2 EE — `$s` are 128 bits. In C they remain normal 32/64-bit types. |
| Wrong struct offset | Fields not at expected offsets | Check inheritance (parent comes first) and alignment (float/ptr on 4 or 8 bytes). |

---

## 12 · Full Workflow — From Zero to PR

| # | Step | Command / Action |
|---|------|-----------------|
| 1 | Find | `wc -l asm/nonmatchings/**/*.s \| sort -n` → pick < 40 lines, few `jal`, readable name |
| 2 | Read ASM | Identify: prologue, saved args, calls (`jal`), null checks, vtable, epilogue |
| 3 | Research | `grep` the struct in `include/` for types. Ghidra for starting pseudo-C. |
| 4 | Wrap | In `.c`: `#ifdef SKIP_ASM` / fn / `#endif` below `INCLUDE_ASM` |
| 5 | Diff | `./scripts/diff.sh MangledName File` → live diff. Iterate to 100%. |
| 6 | Integrate | Remove `INCLUDE_ASM` + `#ifdef`. Add to `symbol_addrs.txt` if missing. |
| 7 | Validate | Full build — `sha1sum` must pass. If not: see Troubleshooting. |
| 8 | PR | Fork → branch → commit → pull request on GitHub. Describe the fn and its logic. |

---

## 13 · PS2 EE Calling Convention — How Args Are Passed

| Category | Registers used | Detail |
|----------|---------------|--------|
| Integers / pointers | `$a0–$a3` (`$4–$7`) then `$a4–$a7` (`$8–$11`) | PS2 passes up to 8 integer args in registers — no stack passing for the first 8 |
| Floats | `$f12`, `$f13`, `$f14`, `$f15` (then `$f16`, `$f17`… per ABI) | Float args use FPU registers — independent from `$a`. A float does NOT consume a `$a`. |
| Mixed int+float | `EvaluateAcpb(ACPB*,ALO*,float,float,int,VECTOR*,VECTOR*)` | `$a0=pacpb` `$a1=palo` `$f12=t` `$f13=svt` `$a2=grfeval` `$a3=ppos` `$a4=pv` — ints and floats have their own slots |
| Return value | Integer: `$v0` / Float: `$f0` | `void` functions: nothing. Usually one return. Two values: `$v0+$v1` or `$f0+$f2`. |
| > 8 int args | Passed on stack (`$sp + offset`) | Rare in Sly — most fns have fewer than 8 args. If you see `lw` at `$sp+large_value` it's a stack arg |
| Structs by value | Copied to stack or passed by pointer | In practice in Sly: always by pointer (`VECTOR*`, `MATRIX3*`). Never a struct copy as direct arg. |
| Caller-saved regs | `$a0–$a7`, `$t0–$t9`, `$v0–$v1`, `$f4–$f19` | Caller must save them if needed after `jal` — hence `daddu $s0,$a0,$zero` before calls |
| Callee-saved regs | `$s0–$s7`, `$f20–$f31`, `$ra`, `$sp` | Called function MUST restore them before returning — hence `sq`/`lq` in prologue/epilogue |

**C prototype → register mapping:**

| C prototype | Register mapping | Note |
|------------|-----------------|------|
| `void Foo(int a, float b, int c, VECTOR *v)` | `$a0=a` `$f12=b` `$a1=c` `$a2=v` | int and float have separate slots — `c` is `$a1` not `$a2`! |
| `int Bar(float x, float y, float z)` | `$f12=x` `$f13=y` `$f14=z` return→`$f0` | 3 floats → 3 consecutive FPU registers |
| `void Baz(ALO*,float,float,int,VECTOR*,VECTOR*)` | `$a0` `$f12` `$f13` `$a1` `$a2` `$a3` | Exact pattern of EvaluateAcpb/Acpc — very common in `ac.c` |

---

## 14 · Special Registers HI / LO — mult, div & accumulator

HI and LO are two special 64-bit registers that receive `mult` and `div` results. They cannot be used directly — you must go through `mfhi`/`mflo`.

| Instruction | Effect | Note |
|-------------|--------|------|
| `mult $a, $b` | `HI:LO = $a * $b` (signed 64-bit) | Result 64-bit: LO = low 32 bits, HI = high 32 bits |
| `multu $a, $b` | `HI:LO = $a * $b` (unsigned) | Unsigned version of `mult` |
| `div $a, $b` | `LO = $a / $b` `HI = $a % $b` | Quotient in LO, remainder in HI — both in one call |
| `divu $a, $b` | `LO = $a / $b` `HI = $a % $b` (u) | Unsigned version |
| `mflo $dst` | `$dst = LO` | Move From LO — retrieve mult result or quotient |
| `mfhi $dst` | `$dst = HI` | Move From HI — retrieve high bits of mult or remainder |
| `mtlo $src` | `LO = $src` | Move To LO — rare, mainly used for `macc` |
| `mthi $src` | `HI = $src` | Move To HI |
| `madd $a, $b` | `HI:LO += $a * $b` | Multiply-Accumulate — accumulates multiple products (DSP) |
| `msub $a, $b` | `HI:LO -= $a * $b` | Multiply-Subtract accumulator |
| `mul $d,$a,$b` | `$d = ($a * $b) & 0xFFFFFFFF` | Pseudo-instruction: `mult` + `mflo` in one — destroys `HI:LO` |

> **Typical pattern:** `mult $a0,$a1` → `mflo $v0` → `return $v0` = `return a*b`  
> `div $a0,$a1` → `mflo $v0` → `mfhi $v1` = quotient in `$v0`, remainder in `$v1`

---

## 15 · VU0 / VU1 & PS2 SIMD Instructions (128-bit vectors)

The PS2 has two Vector Units (VU0, VU1) for vector math. VU0 is accessible inline from the main CPU via COP2 instructions.

| Concept / Instruction | Syntax / Registers | Role |
|----------------------|-------------------|------|
| Registers VF | `$vf0–$vf31` | 32 × 128-bit vector registers — each = 4 floats (x, y, z, w) |
| Registers VI | `$vi0–$vi15` | 16 × 16-bit integer registers — indices, counters inside VUs |
| `VCLIP` | COP2 instruction | 3D clipping test — indicates which components exceed the frustum |
| `VADD` | `vfd = vfs + vft` | Vector addition — all 4 components x,y,z,w in parallel |
| `VSUB` | `vfd = vfs - vft` | Vector subtraction |
| `VMUL` | `vfd = vfs * vft` | Component-wise multiplication (NOT dot product!) |
| `VMADD` | `vfd = vfs*vft + ACC` | Multiply-add with vector accumulator |
| `VOPMULA` | `ACC = vfs x vft` | Partial cross product — stores in accumulator |
| `VOPMSUB` | `vfd = vfs x vft - ACC` | Full cross product with subtraction — computes true 3D cross product |
| `VITOF0`/`FTOI0` | `int(float)` | Vector integer/float conversion for all 4 components |
| `LQC2`/`SQC2` | load/store 128-bit | Load/store a VF register from/to memory — equiv. `lq`/`sq` but to VF |
| `CTC2`/`CFC2` | CPU-VU0 transfer | Move between CPU integer registers and VU0 control registers |

> In Sly 1: most game code uses normal scalar floats (FPU). VUs appear mainly in the renderer and matrix calculations.  
> For decomp: `lq`/`sq` on `$s` registers = classic save (not VU). `LQC2`/`SQC2` = true VU vector access.

---

## 16 · Engine Lexicon — All Modules & Types in Sly Cooper

Overview of the PS2 engine architecture. Each `.c` file corresponds to a system.

### Math, Geometry & Base Types

| Type | Source file | Role & key functions |
|------|-------------|---------------------|
| `VECTOR` | `vec.h` / `P2/vec.c` | 4 floats (x,y,z,w). 16 bytes. Position, direction, color. Passed by `VECTOR*`. `SetVectorCylind`, `SetVectorSphere`, `SProjectVector`, `GetNormalVector` |
| `MATRIX3` | `mat.h` / `P2/mat.c` | 3×3 rotation matrix (9 floats, 36 bytes). Object orientation. `MatMulMatTransMat`, `LoadIdentityMatrix3` |
| `MATRIX4` | `mat.h` / `P2/mat.c` | 4×4 full transform matrix (16 floats). Position + rotation. `LoadIdentityMatrix4`, `mul` operator |
| `LSG` | `P2/clip.c` | Line Segment — segment between two points. Output of clipping functions. `ClsgClipEdgeToObject` |
| `BSP` | `P2/bsp.c` | Binary Space Partition — space-splitting tree for geometry. `PruneBsp`, `PbspPointInBspQuick` |
| `GEOM` | `P2/geom.c` | Object collision geometry (mesh). `InitGeom`, `CloneGeom`. Contains BSP and BSPC for intersection tests. |
| `CONSTR` | `P2/crv.c` | Constraint — path constraint curve. `FindAposClosestPointAll`, `EvaluateAposG`. Used for rails and paths. |

### World Object System (LO / ALO / SO / SW)

| Type | Source file | Role & key functions |
|------|-------------|---------------------|
| `SW` | `P2/sw.c` | World — the current world. Root container of all objects. `InitSw`, `DeleteSw`, `SetSwGravity`. Each level = one SW. |
| `LO` | `P2/lo.c` | Live Object — base object in the world. `InitLo`, `AddLo`, `RemoveLo`, `PostLoLoad`. Every object inherits from LO. |
| `ALO` | `P2/alo.c` | Animated Live Object — LO with animation. Has vtable, VECTOR position, MATRIX3, ASEG list. `InitAlo`, `AddAloHierarchy`. |
| `SO` | `P2/so.c` | Solid Object — ALO with physics and collision. `InitSo`, `EnableSoPhys`, `DisplaceSo`, `ImpactSo`. |
| `BASIC` | `P2/basic.c` | Base class of all scriptable objects. `FIsBasicDerivedFrom`, `EnsureBasicSidebag`, `GetBasicCid`. C++/Splice bridge. |
| `OID` | `common.h` | Object ID — unique object identifier (32-bit integer). Used to reference objects in Splice scripts. |
| `MSGID`/`MSG` | `common.h` | Message ID — messaging system between objects. `HandleXxxMessage` receives MSGID + `void*` payload. |

### Animation System (AC\* / ASEG / ACT / BLEND)

| Type | Source file | Role & key functions |
|------|-------------|---------------------|
| `ASEG` | `P2/aseg.c` | Animation Segment — animation clip on disk. `InitAseg`, `LoadAsegFromBrx`, `CloneAseg`. |
| `ASEGA` | `P2/asega.c` | Animation Segment Application — ASEG being played. `SetAsegaHandsOff`, `UpdateAsegaIeaCur`. |
| `ACT` | `P2/act.c` | Action — animation sequence for an object. `PactNew`, `InitAct`, `RetractAct`, `GetActPositionGoal`. |
| `ACP` | `P2/ac.c` | Animation Curve Position — base of position curves. `EvaluateAcp`. Subclasses: ACPB, ACPC, ACPBL. |
| `ACR` | `P2/ac.c` | Animation Curve Rotation — rotation curves. `EvaluateAcr`. Subclasses: ACRB, ACRC, ACRBL. |
| `ACS` | `P2/ac.c` | Animation Curve Scale — scale curves. `EvaluateAcs`. Subclasses: ACSB, ACSC. |
| `KVB` | `P2/ac.c` | Key Value Bezier — scalar Bezier keyframe. Atomic block of curves. `EvaluateAkvb`. Contains time, value, tangents. |
| `GRFEVAL` | `P2/ac.c` | Eval flags (int bitfield). Controls interpolation, extrapolation, loop. Passed to all `Evaluate*`. |
| `BLEND` | `P2/blend.c` | Animation blending. `EnsureAsegBlendDynamic`. Mixes multiple ASEGs for transitions. |
| `RCHM` | `P2/rchm.c` | Reach Map — IK reach map. `BuildRchmCoefficients`, `ReblendRchm`. |
| `IK`/`IKH` | `P2/ik.c` | Inverse Kinematics. `SolveAloIK`, `RenderIkhSelf`. |

### Physics, Gameplay & Sly Movement (JT / XP / DZG)

| Type | Source file | Role & key functions |
|------|-------------|---------------------|
| `JT` | `P2/jt.c` | Jumping Thing — Sly Cooper's physics entity (player). `InitJt`, `PresetJtAccel`, `AdjustJtNewXp`. Core movement. |
| `XP` | `P2/mark.c` | Contact Point — contact between Sly and the world. `PxpAdd`, `RecalcSwXpPos`, `FreeSwXpList`. |
| `DZ`/`DZG` | `P2/dzg.c` | Dead Zone / DZ Group — physical constraint zone. `SolveDzg`, `AppendDzgDz`. |
| `FX` | `P2/solve.c` | Force eXchange — force exchange between objects. `CalculateSoEffect`, `PropagateSoForce`. |
| `CM` | `P2/cm.c` | Camera. `CalcCmAdjust`, `SpringCm`, `GetCmCpdefi`. Handles camera position and tracking. |
| `STEP` | `P2/step.c` | Step — Sly's locomotion system. `InitStep`, `PostStepLoad`. Orchestrates stepcane, steprun, stephide… |
| `JOY` | `P2/joy.c` | Joystick — controller input. `StartupJoy`, `UpdateJoy`. Translates DualShock into movement vectors. |

### Graphics Rendering (GLOB / GIFS / VIFS / SHD / RPL)

| Type | Source file | Role & key functions |
|------|-------------|---------------------|
| `GLOB` | `P2/glob.c` | Globe — 3D mesh of an object. `LoadGlobsetFromBrx`, `BuildSubglobSinglePass`. Contains vertices, UV, normals. |
| `SHD` | `P2/shd.c` | Shader / texture. `Tex0FromTexIframeCtk`, `PackTexGifs`, `LoadBmpFromBrx`. Contains texture + GS render params. |
| `GIFS` | `P2/gifs.c` | GIF Packet Stream — GIF packets sent to GS (Graphics Synthesizer). `AddPrimBulk`, `AddPrimPack`, `EndPrim`. |
| `VIFS` | `P2/vifs.c` | VIF Packet Stream — VIF packets sent to VUs. `AddVifMscal`, `AddVifBaseOffset`. |
| `RPL` | `P2/render.c` | Render Plane — sorted render plane. `SubmitRpl`, `NCmpPrplReverseZ`. Z-sorts objects for rendering. |
| `SAA` | `P2/shdanim.c` | Shader Animation Array — texture animation (UV scroll, palette anim). `PsaaLoadFromBrx`, `InitSaa`. |
| `EMITTER` | `P2/emitter.c` | Particle emitter. `InitEmitter`, `LoadEmitterFromBrx`, `CloneEmitter`. Smoke, sparks, bubbles. |

### Engine Systems (BRX / CLOCK / SPLICE)

| Type | Source file | Role & key functions |
|------|-------------|---------------------|
| `BRX` | `P2/brx.c` | Binary Resource — game asset file format. `PloNew`, `LoadSwObjectsFromBrx`. Container for all assets. |
| `CLOCK` | `P2/clock.c` | Engine clock. `SetClockRate`, `MarkClockTick`, `ResetClock`. Each system has its CLOCK for delta time. |
| `ALARM` | `P2/alarm.c` | Time alarm. `InitAlarm`, `UpdateAlarm`, `CloneAlarm`. Fires callbacks after a delay. |
| `DMAS` | `P2/dmas.c` | DMA Stream — PS2 DMA manager. `StartupDma`, `AllocGlobal`, `AllocSw`. Memory transfers without CPU. |
| `SLOTHEAP` | `P2/slotheap.c` | Slot Heap allocator. `PvAllocSlotheapImpl`, `CreateSlotheapSw`. Memory pool for frequent allocations. |
| `PHASE` | `P2/phasemem.c` | Game phase (global state). `SetPhase`, `ClearPhase`. Controls game phase (loading, gameplay, cutscene…) |

### Splice — Scheme-like Scripting Engine (P2/splice/)

| Type | Source file | Role & key functions |
|------|-------------|---------------------|
| `CRef` | `splice/ref.cpp` | Reference — Splice value (int, float, symbol, list, object…). Everything is a `CRef`. `RefOpAdd`, `RefOpCar`, `RefOpCdr`. |
| `CPair` | `splice/pair.cpp` | Pair (`car . cdr`) — Scheme list structure. `PpairNew`, `CloneTo`, `DeletePair`. Base of all Splice lists. |
| `CFrame` | `splice/frame.cpp` | Environment frame — namespace for Splice variables. `AddParent`, `RefAddBinding`, `PrefFindBinding`. |
| `CGc` | `splice/gc.cpp` | Splice Garbage Collector. `AddRootFrame`, `PushFrame`, `Startup`, `Shutdown`. Manages Splice runtime memory. |
| `RefEval*` | `splice/eval.cpp` | Splice evaluator. `RefEvalIf`, `RefEvalWhile`, `RefEvalLambda`, `RefEvalApply`. |
| `RefOp*` | `splice/bif.cpp` | Built-In Functions. `RefOpAdd`, `RefOpVectorDotProduct`, `RefOpFindObject`, `RefOpStartSound`. |

### Enemies, Gameplay & Interactive Objects

| Type | Source file | Role & key functions |
|------|-------------|---------------------|
| `STEPGUARD` | `P2/stepguard.c` | Guard enemy. `InitStepguard`, `CloneStepguard`, `BindStepguard`. Locomotion, detection, patrol. |
| `UBG` | `P2/ub.c` | Ubiquitous Guard — basic omnipresent guard. `InitUbg`, `FDetectUbg`. Simplified detection AI. |
| `SBG` | `P2/sb.c` | Super Boss Guard — level boss. `UpdateSbgGoal`. AI with SGS (State Group System). |
| `SGS` | `P2/sb.c` | State Group System — AI state machine. `OnSbgEnteringSgs`. Each SGS = one AI state (patrol, alert…). |
| `SENSOR` | `P2/sensor.c` | Detection zone. `InitSensor`, `FCheckSensorObject`. Triggers events on contact. |
| `CHKPNT` | `P2/chkpnt.c` | Checkpoint — save point. `SaveChkmgrCheckpoint`, `ReturnChkmgrToCheckpoint`. Manages Sly respawns. |
| `DPRIZE` | `P2/coin.c` | Drop Prize — collectible (coins, keys). `InitDprize`, `CollectSprize`. |
| `TARGET` | `P2/target.c` | Target — attack target. `StartupTarget`. Sly aims at enemy TARGETs. |
| `WAYPOINT` | `P2/waypoint.c` | AI waypoint. `InitWaypoint`. Guards follow WAYPOINT chains. |

> **AC\* suffix hierarchy:** B=Bezier | C=Component (x/y/z separate) | L=Linear | W=Weighted | BL=Blend | BLT=BlendTwist | BLP=BlendPose  
> Example: `ACRBL` = Animation Curve Rotation Bezier Linear

> **Prototype vs Release:** Some modules from the May 2002 prototype were removed from the release: `cycle.c` (wheeled vehicle), `hg.c` (hang glider), `stepski.c` (ski), `rope.c`, `sc.c`, `mouthgame.c`, debug menu. Functions from these modules may appear in Ghidra but have no `.s` in the repo.

---

## 17 · decomp.me — Tips for Getting the Most Out of It

decomp.me is a collaborative decompilation web tool. m2c auto-decompiles the ASM — you then refine it.

| Field / Option | Value / Action | Why |
|----------------|---------------|-----|
| Preset | `PS2 > Sly Cooper and the Thievius Raccoonus` | Choose this exact preset — it configures the correct MIPS GCC compiler and flags to match Sly. |
| Target assembly | Content of the `.s` file | Paste the raw `.s` content (`asm/nonmatchings/…`). No file header, just the instructions. |
| Diff label | Mangled name of the function | e.g. `EvaluateAcpb__FP4ACPBP3ALOffiP6VECTORT5` — must match the `glabel` exactly in the `.s` |
| Context | Type definitions used | Paste needed structs and typedefs from the `.h` files. Without this m2c can't type variables. |
| Context — what | Structs, enums, prototypes of called functions | e.g. for EvaluateAcpb: paste `struct KVB`, `struct ACP`, `struct ACPB`, `typedef GRFEVAL`, `EvaluateAkvb` prototype |
| Options > Debug | `-g3` (Macro expansions) | Shows source line numbers in generated ASM — helps match ASM/C correspondence |
| m2c output | Starting point, not the solution | m2c generates valid but ugly C (`TEMP_0`, `TEMP_1`…). Rename, type, restructure until 100%. |
| Score | 100% Green everywhere in the diff | CURRENT and TARGET columns must be identical. One red line = not good. |
| Fork | Fork button on an existing scratch | If someone started a fn on decomp.me, fork their scratch rather than starting from zero. |
| Permanent URL | Share the scratch link | Each scratch has a fixed URL — share on Discord to ask for help on a specific fn. |

**Cleaning up m2c output:**

| Typical m2c output | How to clean it up |
|-------------------|-------------------|
| `TEMP_0`, `TEMP_1`… | Temporary variables — rename them according to their deduced usage from context |
| `(s32)` / `(f32)` casts | m2c is conservative about types — simplify casts when the struct gives you the type |
| `goto .L...` | Jump labels — often transformable into `if`/`else` or `while` when structure is clear |
| `*(u32 *)(reg + N)` | Struct field access — replace with `ptr->field` when the struct is defined in Context |
| Shifted registers in diff | If an arg is in the wrong `$a`: check the order of float vs int args in the signature |

---

*[github.com/TheOnlyZac/sly1](https://github.com/TheOnlyZac/sly1) · Generated with Claude · Sly Cooper and the Thievius Raccoonus — PS2 Matching Decompilation · v6-EN*
