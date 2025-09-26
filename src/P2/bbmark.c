#include <bbmark.h>
#include <slotheap.h>
#include <sw.h>

INCLUDE_ASM("asm/nonmatchings/P2/bbmark", UpdateSwPox__FP2SWP3OXAT1UcUc);

OX *PoxAddSw(SW *psw, OXA *poxa, OXA *poxaOther)
{
    OX *pox = (OX *)PvAllocSlotheapImpl(&psw->slotheapOx);
    pox->pxp = (XP *)nullptr;
    pox->psoOther = poxaOther->pso;
    pox->poxNext = poxa->pox;
    poxa->pox = pox;
    return pox;
}

INCLUDE_ASM("asm/nonmatchings/P2/bbmark", PoxRemoveSw__FP2SWP3OXAT1);

INCLUDE_ASM("asm/nonmatchings/P2/bbmark", PoxFromSoSo__FP2SOT0);

XP *PxpFirstFromSoSo(SO *pso, SO *psoOther)
{
    OX *pox = PoxFromSoSo(pso, psoOther);
    return pox ? pox->pxp : (XP *)nullptr;
}

INCLUDE_ASM("asm/nonmatchings/P2/bbmark", AddSwAaobrObject__FP2SWP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/bbmark", RemoveSwAaobrObject__FP2SWP2SO);

void InvalidateSwAaox(SW *psw)
{
    psw->fAaoxValid = 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/bbmark", UpdateSwAaox__FP2SW);

INCLUDE_ASM("asm/nonmatchings/P2/bbmark", InvalidateSwXpForObject__FP2SWP2SOi);

INCLUDE_ASM("asm/nonmatchings/P2/bbmark", RecalcSwXpAll__FP2SWi);

INCLUDE_ASM("asm/nonmatchings/P2/bbmark", RecalcSwOxfFilterForObject__FP2SWP2SO);
