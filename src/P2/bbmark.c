#include <bbmark.h>
#include <slotheap.h>
#include <sw.h>

INCLUDE_ASM("asm/nonmatchings/P2/bbmark", UpdateSwPox__FP2SWP3OXAT1UcUc);

OX *PoxAddSw(SW *psw, OXA *poxa, OXA *poxaOther)
{
    OX *pox = (OX *)PvAllocSlotheapImpl(&psw->slotheapOx);
    pox->pxp = NULL;
    pox->psoOther = poxaOther->pso;
    pox->poxNext = poxa->pox;
    poxa->pox = pox;
    return pox;
}

OX *PoxRemoveSw(SW *psw, OXA *poxa, OXA *poxaOther)
{
    OX **ppox = &poxa->pox;
    OX *pox = poxa->pox;
    SO *psoOther = poxaOther->pso;

    while (pox)
    {
        if (pox->psoOther == psoOther)
        {
            *ppox = pox->poxNext;
            break;
        }
        ppox = &pox->poxNext;
        pox = pox->poxNext;
    }

    return pox;
}

OX *PoxFromSoSo(SO *pso, SO *psoOther)
{
    OX *pox = STRUCT_OFFSET(STRUCT_OFFSET(pso, 0x50, SW *), 0x480, OXA *)->pox;
    SO *psoKey = STRUCT_OFFSET(psoOther, 0x50, SO *);
    while (pox != NULL)
    {
        if (pox->psoOther == psoKey)
            return pox;
        pox = pox->poxNext;
    }
    return NULL;
}

XP *PxpFirstFromSoSo(SO *pso, SO *psoOther)
{
    OX *pox = PoxFromSoSo(pso, psoOther);
    return pox ? pox->pxp : NULL;
}

INCLUDE_ASM("asm/nonmatchings/P2/bbmark", AddSwAaobrObject__FP2SWP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/bbmark", RemoveSwAaobrObject__FP2SWP2SO);

void InvalidateSwAaox(SW *psw)
{
    psw->fAaoxValid = 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/bbmark", UpdateSwAaox__FP2SW);

void InvalidateSwXpForObject(SW *psw, SO *pso, GRFPVA grfpvaInvalid)
{
    SW *pswObject = STRUCT_OFFSET(pso, 0x50, SW *);
    if (pswObject)
    {
        STRUCT_OFFSET(pswObject, 0x4B8, int) &= ~grfpvaInvalid;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/bbmark", RecalcSwXpAll__FP2SWi);

INCLUDE_ASM("asm/nonmatchings/P2/bbmark", RecalcSwOxfFilterForObject__FP2SWP2SO);
