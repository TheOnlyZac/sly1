#include "common.h"

INCLUDE_ASM(const s32, "P2/brx", StartupBrx__Fv);

INCLUDE_ASM(const s32, "P2/brx", PloNew__F3CIDP2SWP3ALO3OIDi);

INCLUDE_ASM(const s32, "P2/brx", LoadOptionFromBrx__FPvP5EOPIDP18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/brx", snd_SendIOPCommandAndWait);

INCLUDE_ASM(const s32, "P2/brx", snd_SendIOPCommandNoWait);

INCLUDE_ASM(const s32, "P2/brx", LoadOptionsFromBrx__FPvP18CBinaryInputStream);

uint IploFromStockOid(int oid)
{
    int iplo;

    // Ensure oid is a stock object (OID between 12 and 42)
    if (oid >= 12 && oid <= 42)
    {
        iplo = oid - 12;
    }
    else
    {
        iplo = -1;
    }

    return iplo;
}

INCLUDE_ASM(const s32, "P2/brx", LoadSwObjectsFromBrx__FP2SWP3ALOP18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/brx", SetLoDefaults__FP2LO);
