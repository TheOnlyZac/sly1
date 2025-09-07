#include <keyhole.h>

extern KEYHOLE *g_pkeyhole;

void InitKeyhole(KEYHOLE *pkeyhole)
{
    InitLo(pkeyhole);
    g_pkeyhole = pkeyhole;
}

INCLUDE_ASM(const s32, "P2/keyhole", LoadKeyholeFromBrx__FP7KEYHOLEP18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/keyhole", DrawKeyholeMask__FP7KEYHOLEffff);

INCLUDE_ASM(const s32, "P2/keyhole", DrawKeyhole__FP7KEYHOLEf);

INCLUDE_ASM(const s32, "P2/keyhole", keyhole__static_initialization_and_destruction_0);

INCLUDE_ASM(const s32, "P2/keyhole", _GLOBAL_$I$InitKeyhole__FP7KEYHOLE);
