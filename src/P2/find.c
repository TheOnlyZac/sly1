#include <find.h>

INCLUDE_ASM(const s32, "P2/find", PdlFromSwOid__FP2SW3OID);

INCLUDE_ASM(const s32, "P2/find", MatchSwObject__FP2LOiiiT0iPiPP2LOT6);

INCLUDE_ASM(const s32, "P2/find", CploFindSwObjects__FP2SWi3OIDP2LOiPP2LO);

INCLUDE_ASM(const s32, "P2/find", PloFindSwObject__FP2SWi3OIDP2LO);

INCLUDE_ASM(const s32, "P2/find", PloFindSwNearest__FP2SW3OIDP2LO);

INCLUDE_ASM(const s32, "P2/find", PloFindSwChild__FP2SW3OIDP3ALO);

INCLUDE_ASM(const s32, "P2/find", FIsCidDerivedFrom__F3CIDT0);

INCLUDE_ASM(const s32, "P2/find", CploFindSwObjectsByClass__FP2SWi3CIDP2LOiPP2LO);

INCLUDE_ASM(const s32, "P2/find", PloFindSwObjectByClass__FP2SWi3CIDP2LO);

ALO * PaloFindLoCommonParent(LO *plo, LO *ploOther) {
    ALO *current;
    while (plo != (LO *)0x0) {
        current = (ALO *)ploOther;
        while (current != (ALO *)0x0) {
            if (plo == current) {
                return (ALO *)plo;
            }
            current = (ALO *)current->paloParent;
        }
        plo = (LO *)plo->paloParent;
    }
    return (ALO *)0x0;
}
