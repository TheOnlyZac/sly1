export const meta = {
  name: 'decomp-lhf-draft',
  description: 'Draft matching C for tiny sly1 leaf functions (parallel, read-only)',
  phases: [{ title: 'Draft' }],
}

const cands = (typeof args === 'string' ? JSON.parse(args) : args) || []
const BATCH = 4
const batches = []
for (let i = 0; i < cands.length; i += BATCH) batches.push(cands.slice(i, i + BATCH))

const SCHEMA = {
  type: 'object',
  additionalProperties: false,
  properties: {
    drafts: {
      type: 'array',
      items: {
        type: 'object',
        additionalProperties: false,
        properties: {
          unit: { type: 'string' },
          sym: { type: 'string' },
          code: { type: 'string' },
          includes: { type: 'array', items: { type: 'string' } },
          confidence: { type: 'number' },
          notes: { type: 'string' },
        },
        required: ['unit', 'sym', 'code', 'includes', 'confidence', 'notes'],
      },
    },
  },
  required: ['drafts'],
}

function draftPrompt(batch) {
  const list = batch
    .map((c) => `- unit "${c.unit}", symbol "${c.sym}"  (asm: asm/nonmatchings/${c.unit}/${c.sym}.s, ~${c.n} instrs; source file: src/${c.unit}.c)`)
    .join('\n')
  return [
    'You are decompiling TINY functions in the Sly 1 PS2 decomp at /home/johan/git/sly1 to C++ that compiles with EE GCC 2.95 to bytes IDENTICAL to the original MIPS assembly. Produce a matching C function for EACH candidate below.',
    '',
    'Per candidate, do this:',
    '1. Read asm/nonmatchings/<unit>/<sym>.s. Work out EXACTLY what it does. Reg conventions: args $4=a0,$5=a1,$6=a2,$7=a3; float args $f12,$f14; int return in $2($v0); float return in $f0. daddu $2,$0,$0 => return 0; addiu $2,$0,1 => return 1.',
    '2. Determine the signature. Demangle the symbol (e.g. Set...__FP9STEPGUARDf => void Set...(STEPGUARD*, float); __FP4ROST => (ROST*)). Cross-check the prototype in the unit header (grep the symbol base name under include/). For FUN_ names with no mangling, infer arg types from how regs are used and give the function the EXACT name FUN_xxxx; note that it will mangle (handled later).',
    '3. Struct field access at offset 0xNN on a pointer: read the struct def. If a NAMED field already lands at that exact COMPILED offset, use it (verify with: scripts/structoff.sh <header.h> \'(int)(long)&((TYPE*)0)->field\'). Otherwise use STRUCT_OFFSET(ptr, 0xNN, type) — macro in common.h: (*(type*)((uint8_t*)(ptr)+(offset))). MATCH THE WIDTH: lb=>char, lbu=>uchar, lh=>short, lhu=>ushort, lw/sw=>int (or a pointer/float type per use), ld/sd=>64-bit (use long long/uint64_t), lq/sq=>16-byte qword copy (use a 16-byte type; lower your confidence and explain in notes).',
    '4. Float ops: a float field read/returned => float type. Compares/moves => mirror them.',
    '5. Output the FULL C function definition that REPLACES this exact line in src/<unit>.c:  INCLUDE_ASM("asm/nonmatchings/<unit>", <sym>);',
    '6. In "includes": list ONLY header tokens (e.g. "<so.h>") needed that are NOT already #included at the top of src/<unit>.c (read that file to check). Prefer adding nothing.',
    '',
    'HARD RULES:',
    '- DO NOT modify any struct/header, DO NOT add or grow struct fields. Use STRUCT_OFFSET for unnamed fields.',
    '- DO NOT run ninja, configure.py, scripts/match.sh, or build/link ANYTHING (builds are serialized by the caller). You MAY run scripts/structoff.sh (it only writes /tmp) and read any file.',
    '- Keep the C as direct as the asm (GCC 2.95 is literal). Mirror operation order.',
    '- confidence: 0..1 (1 = you are sure it is a byte-exact match). Put any risk in notes (esp. lq/sq, float, or guessed FUN_ signatures).',
    '',
    'Candidates:',
    list,
    '',
    'Return every candidate as a draft via the schema (one entry per candidate, even low-confidence ones).',
  ].join('\n')
}

phase('Draft')
const results = await parallel(
  batches.map((b, i) => () =>
    agent(draftPrompt(b), { label: `draft#${i + 1} [${b.length}]`, phase: 'Draft', schema: SCHEMA })
  )
)

const drafts = results.filter(Boolean).flatMap((r) => (r && r.drafts) || [])
log(`drafted ${drafts.length} / ${cands.length} functions`)
return { drafts }
