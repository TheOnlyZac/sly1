#include "common.h"

INCLUDE_ASM(const s32, "P2/brx", StartupBrx__Fv);

INCLUDE_ASM(const s32, "P2/brx", PloNew__F3CIDP2SWP3ALO3OIDi);

INCLUDE_ASM(const s32, "P2/brx", LoadOptionFromBrx__FPvP5EOPIDP18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/brx", snd_SendIOPCommandAndWait);

INCLUDE_ASM(const s32, "P2/brx", snd_SendIOPCommandNoWait);

INCLUDE_ASM(const s32, "P2/brx", LoadOptionsFromBrx__FPvP18CBinaryInputStream);

uint IploFromStockOid(int oid) {
    int iplo;

    if (oid >= 0xC && oid <= 0x2a) {
        iplo = oid - 0xC;
    } else {
        iplo = -1;
    }
    return iplo;
}

INCLUDE_ASM(const s32, "P2/brx", LoadSwObjectsFromBrx__FP2SWP3ALOP18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/brx", SetLoDefaults__FP2LO);
