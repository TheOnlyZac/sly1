#include <find.h>

INCLUDE_ASM(const s32, "P2/find", PdlFromSwOid__FP2SW3OID);

INCLUDE_ASM(const s32, "P2/find", MatchSwObject__FP2LOiiiT0iPiPP2LOT6);

INCLUDE_ASM(const s32, "P2/find", CploFindSwObjects__FP2SWi3OIDP2LOiPP2LO);

LO * PloFindSwObject(SW *psw, int grffso, OID oid, LO *ploContext) {
    LO *value1[4];
    value1[0] = 0;
    CploFindSwObjects(psw, grffso | 0x200, oid, ploContext, 1, value1);
    return value1[0];
}

INCLUDE_ASM(const s32, "P2/find", PloFindSwNearest__FP2SW3OIDP2LO);

INCLUDE_ASM(const s32, "P2/find", PloFindSwChild__FP2SW3OIDP3ALO);

INCLUDE_ASM(const s32, "P2/find", FIsCidDerivedFrom__F3CIDT0);

INCLUDE_ASM(const s32, "P2/find", CploFindSwObjectsByClass__FP2SWi3CIDP2LOiPP2LO);

INCLUDE_ASM(const s32, "P2/find", PloFindSwObjectByClass__FP2SWi3CIDP2LO);

INCLUDE_ASM(const s32, "P2/find", PaloFindLoCommonParent__FP2LOT0);
