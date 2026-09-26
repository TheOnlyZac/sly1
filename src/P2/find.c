#include <find.h>

extern VT *g_mpcidpvt[162];

DL *PdlFromSwOid(SW *psw, OID oid)
{
    return &psw->adlHash[(oid * 0x95675) & 0x1ff];
}

INCLUDE_ASM("asm/nonmatchings/P2/find", MatchSwObject__FP2LOiiiT0iPiPP2LOT6);

INCLUDE_ASM("asm/nonmatchings/P2/find", CploFindSwObjects__FP2SWi3OIDP2LOiPP2LO);

LO *PloFindSwObject(SW *psw, GRFFSO grffso, OID oid, LO *ploContext)
{
    LO *aplo = NULL;
    CploFindSwObjects(psw, grffso | FSO_ReturnActualCount, oid, ploContext, 1, &aplo);
    return aplo;
}

LO *PloFindSwNearest(SW *psw, OID oid, LO *ploContext)
{
    LO *aplo = NULL;
    CploFindSwObjects(psw, FSO_ReturnActualCount | FSO_FindNearest, oid, ploContext, 1, &aplo);
    return aplo;
}

LO *PloFindSwChild(SW *psw, OID oid, ALO *paloAncestor)
{
    LO *aplo = NULL;
    CploFindSwObjects(psw, FSO_ReturnActualCount | FSO_FindChild, oid, paloAncestor, 1, &aplo);
    return aplo;
}

int FIsCidDerivedFrom(CID cid, CID cidAncestor)
{
    VT *vt = g_mpcidpvt[cid];
    while (vt)
    {
        if (vt->cid == cidAncestor)
        {
            return 1;
        }

        vt = vt->pvtSuper;
    }

    return 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/find", CploFindSwObjectsByClass__FP2SWi3CIDP2LOiPP2LO);

LO *PloFindSwObjectByClass(SW *psw, GRFFSO grffso, CID cid, LO *ploContext)
{
    LO *aplo = NULL;
    CploFindSwObjectsByClass(psw, grffso | FSO_ReturnActualCount, cid, ploContext, 1, &aplo);
    return aplo;
}

ALO *PaloFindLoCommonParent(LO *plo, LO *ploOther)
{
    while (plo)
    {
        ALO *current = (ALO *)ploOther;
        while (current)
        {
            if (plo == current)
            {
                return (ALO *)plo;
            }

            current = (ALO *)current->paloParent;
        }

        plo = (LO *)plo->paloParent;
    }

    return NULL;
}
