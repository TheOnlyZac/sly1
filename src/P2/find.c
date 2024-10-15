#include <find.h>

DL *PdlFromSwOid(SW *psw, OID oid) {
    s32 v1 = 0x95675;
    s32 a2 = 0xc;
    u32 v0 = oid * v1;
    v0 = v0 & 0x1ff;
    v0 = v0 * a2;
    v0 = v0 + 0x84;
    return (DL*) ((u32) psw + v0);
}

INCLUDE_ASM(const s32, "P2/find", MatchSwObject__FP2LOiiiT0iPiPP2LOT6);

INCLUDE_ASM(const s32, "P2/find", CploFindSwObjects__FP2SWi3OIDP2LOiPP2LO);

INCLUDE_ASM(const s32, "P2/find", PloFindSwObject__FP2SWi3OIDP2LO);

INCLUDE_ASM(const s32, "P2/find", PloFindSwNearest__FP2SW3OIDP2LO);

INCLUDE_ASM(const s32, "P2/find", PloFindSwChild__FP2SW3OIDP3ALO);

INCLUDE_ASM(const s32, "P2/find", FIsCidDerivedFrom__F3CIDT0);

INCLUDE_ASM(const s32, "P2/find", CploFindSwObjectsByClass__FP2SWi3CIDP2LOiPP2LO);

INCLUDE_ASM(const s32, "P2/find", PloFindSwObjectByClass__FP2SWi3CIDP2LO);

INCLUDE_ASM(const s32, "P2/find", PaloFindLoCommonParent__FP2LOT0);
