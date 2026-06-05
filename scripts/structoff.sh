#!/bin/bash
#
# Print REAL compiled struct offsets/sizes using the EE (GCC 2.95) toolchain.
# Host gcc gives wrong layout (different EABI alignment), so always probe with
# the actual compiler. Each EXPR must be an integer constant expression; use a
# null base for offsetof-style queries, e.g. (int)(long)&((WATER*)0)->grfso
#
# Usage: scripts/structoff.sh <header> 'EXPR' ['EXPR' ...]
#
# Example:
#   scripts/structoff.sh water.h 'sizeof(WATER)' \
#       '(int)(long)&((WATER*)0)->grfso' '(int)(long)&((WATER*)0)->zpd.cploThrow'
#
set -e

if [ -z "$2" ]; then
	echo "Usage: $0 <header> 'EXPR' ['EXPR' ...]" >&2
	exit 1
fi

cd "$(dirname "$0")/.."

HDR="$1"
shift

SRC="$(mktemp /tmp/structoff.XXXXXX.cpp)"
OBJ="${SRC%.cpp}.o"
trap 'rm -f "$SRC" "$OBJ"' EXIT

{
	echo "#include <$HDR>"
	i=0
	for e in "$@"; do
		echo "int probe_$i(){ return (int)($e); }"
		i=$((i + 1))
	done
} > "$SRC"

WINEDEBUG=-all wine tools/cc/bin/ee-gcc.exe -c -Iinclude -isystem include/sdk/ee \
	-isystem include/gcc -x c++ -B"$PWD/tools/cc/lib/gcc-lib/ee/2.95.2/" \
	-O2 -G0 -ffast-math "$SRC" -o "$OBJ" 2>&1 | grep -viE 'warning|radv' || true

if ! [ -s "$OBJ" ]; then
	echo "error: compile failed (run without the grep filter to see why)" >&2
	exit 2
fi

DIS="$(mips-linux-gnu-objdump -d "$OBJ" 2>/dev/null)"
echo "# <$HDR>"
i=0
for e in "$@"; do
	# Each probe is a constant function: jr ra ; li v0,N (or move v0,zero for 0).
	block="$(echo "$DIS" | awk -v f="<probe_${i}__" 'index($0,f){p=1;next} p&&/^$/{exit} p{print}')"
	val="$(echo "$block" | grep -oE 'li[[:space:]]+v0,-?[0-9]+' | head -1 | grep -oE '\-?[0-9]+$')"
	if [ -z "$val" ] && echo "$block" | grep -q 'move[[:space:]]*.*v0,zero'; then
		val=0
	fi
	if [ -n "$val" ]; then
		printf '  %-46s = %s (0x%x)\n' "$e" "$val" "$val"
	else
		printf '  %-46s = ?\n' "$e"
	fi
	i=$((i + 1))
done
