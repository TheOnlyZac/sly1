#include <freeze.h>

void RemergeSwObject(SW *psw, ALO *palo)
{
    unsigned long long grfalo = STRUCT_OFFSET(palo, 0x2c8, unsigned long long);

    if ((grfalo & (0x8000ULL << 24)) == 0)
    {
        STRUCT_OFFSET(palo, 0x2c8, unsigned long long) = grfalo | (0x8000ULL << 24);
        int cpalo = STRUCT_OFFSET(psw, 0x1ed0, int);
        ALO **apalo = STRUCT_OFFSET(psw, 0x1ed4, ALO **);
        apalo[cpalo] = palo;
        STRUCT_OFFSET(psw, 0x1ed0, int) = cpalo + 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/freeze", MergeSwFreezeGroups__FP2SWP3ALOT1);

INCLUDE_ASM("asm/nonmatchings/P2/freeze", SplinterSwFreezeGroup__FP2SWP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/freeze", MergeSwGroup__FP2SWP3MRG);

INCLUDE_ASM("asm/nonmatchings/P2/freeze", AddSwMergeGroup__FP2SWP3MRG);

INCLUDE_ASM("asm/nonmatchings/P2/freeze", RemoveFromArray__FPiPPvPv);

INCLUDE_ASM("asm/nonmatchings/P2/freeze", RemoveSwMergeGroup__FP2SWP3MRG);

INCLUDE_ASM("asm/nonmatchings/P2/freeze", RemergeSwObjects__FP2SW);

INCLUDE_ASM("asm/nonmatchings/P2/freeze", FreezeAloHierarchy__FP3ALOi);

void GetAloFrozen(ALO *palo, int *pf)
{
    *pf = (int)(STRUCT_OFFSET(palo, 0x2c8, unsigned long long) >> 38) & 1;
}

INCLUDE_ASM("asm/nonmatchings/P2/freeze", FreezeAlo__FP3ALOi);

INCLUDE_ASM("asm/nonmatchings/P2/freeze", FreezeSo__FP2SOi);

INCLUDE_ASM("asm/nonmatchings/P2/freeze", RefreezeSwObjects__FP2SW);

INCLUDE_ASM("asm/nonmatchings/P2/freeze", UpdateSwBusyList__FP2SW);
