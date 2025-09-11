#include <find.h>

DL *PdlFromSwOid(SW *psw, OID oid)
{
    return &psw->adlHash[(oid * 0x95675) & 0x1ff];
}

INCLUDE_ASM("asm/nonmatchings/P2/find", MatchSwObject__FP2LOiiiT0iPiPP2LOT6);

INCLUDE_ASM("asm/nonmatchings/P2/find", CploFindSwObjects__FP2SWi3OIDP2LOiPP2LO);

LO *PloFindSwObject(SW *psw, int grffso, OID oid, LO *ploContext)
{
    LO *aplo[4];
    aplo[0] = 0;
    CploFindSwObjects(psw, FSO_ReturnActualCount | grffso, oid, ploContext, 1, aplo);
    return aplo[0];
}

LO *PloFindSwNearest(SW *psw, OID oid, LO *ploContext)
{
    LO *aplo[4];
    aplo[0] = 0;
    CploFindSwObjects(psw, FSO_ReturnActualCount | FSO_FindNearest, oid, ploContext, 1, aplo);
    return aplo[0];
}

LO *PloFindSwChild(SW *psw, OID oid, ALO *paloAncestor)
{
    LO *aplo[4];
    aplo[0] = 0;
    CploFindSwObjects(psw, FSO_ReturnActualCount | FSO_FindChild, oid, paloAncestor, 1, aplo);
    return aplo[0];
}

int FIsCidDerivedFrom(CID cid, CID cidAncestor)
{
    void **ppv = (&g_mpcidpvt)[cid];
    while (ppv)
    {
        if (ppv[1] == (void *)cidAncestor)
        {
            return 1;
        }

        ppv = (void **)*ppv;
    }

    return 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/find", CploFindSwObjectsByClass__FP2SWi3CIDP2LOiPP2LO);

INCLUDE_ASM("asm/nonmatchings/P2/find", PloFindSwObjectByClass__FP2SWi3CIDP2LO);

ALO *PaloFindLoCommonParent(LO *plo, LO *ploOther)
{
    ALO *current;
    while (plo)
    {
        current = (ALO *)ploOther;
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

    return (ALO *)nullptr;
}
