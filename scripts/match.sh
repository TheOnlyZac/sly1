#!/bin/bash
#
# Headless per-symbol match check (no TUI). Builds the target (asm) and current
# (your C, -DSKIP_ASM) objects, then diffs a single symbol's instructions AND
# relocations. Prints "MATCH" or the instruction diff.
#
# Usage: scripts/match.sh <unit> <MangledSymbol>
#   <unit>  splat unit path, e.g. P2/water   (object: obj/{target,current}/water.o)
#
# Example: scripts/match.sh P2/water InitWater__FP5WATER
#
set -e

if [ -z "$2" ]; then
	echo "Usage: $0 <unit> <MangledSymbol>   (e.g. $0 P2/water InitWater__FP5WATER)" >&2
	exit 1
fi

cd "$(dirname "$0")/.."
if [ -z "$VIRTUAL_ENV" ]; then
	source "env/bin/activate"
fi

UNIT="$1"
SYM="$2"
OBJ="$(basename "$UNIT").o"

python3 configure.py --objects >/dev/null
ninja "obj/target/$OBJ" "obj/current/$OBJ" >/dev/null

for v in target current; do
	mips-linux-gnu-objdump -dr "obj/$v/$OBJ" 2>/dev/null | awk -v s="<$SYM>:" '
		$0 ~ s {p=1} p && /^$/ {p=0} p {print}' \
	| sed -E 's/^\s*[0-9a-f]+:\s+[0-9a-f]{8}\s+//; s/^\s*[0-9a-f]+: (R_MIPS)/\1/; s/^[0-9a-f]+ </</; s/[0-9a-f]+ <([A-Za-z])/<\1/g' \
	> "/tmp/match_$v.txt"
done

if ! [ -s /tmp/match_target.txt ]; then
	echo "error: symbol '$SYM' not found in obj/target/$OBJ" >&2
	exit 2
fi

if diff -q /tmp/match_target.txt /tmp/match_current.txt >/dev/null; then
	echo "MATCH: $SYM"
else
	echo "DIFFERS: $SYM"
	diff /tmp/match_target.txt /tmp/match_current.txt
	exit 1
fi
