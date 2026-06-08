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

void MergeSwGroup(SW *psw, MRG *pmrg)
{
    int i = 0;
    int iFirst;

    while (i < pmrg->cpalo)
    {
        if (FIsLoInWorld((LO *)pmrg->apalo[i]))
            break;
        i++;
    }

    iFirst = i;
    for (; i < pmrg->cpalo; i++)
    {
        if (FIsLoInWorld((LO *)pmrg->apalo[i]))
        {
            MergeSwFreezeGroups(psw, pmrg->apalo[iFirst]->paloFreezeRoot, pmrg->apalo[i]->paloFreezeRoot);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/freeze", AddSwMergeGroup__FP2SWP3MRG);

INCLUDE_ASM("asm/nonmatchings/P2/freeze", RemoveFromArray__FPiPPvPv);

INCLUDE_ASM("asm/nonmatchings/P2/freeze", RemoveSwMergeGroup__FP2SWP3MRG);

INCLUDE_ASM("asm/nonmatchings/P2/freeze", RemergeSwObjects__FP2SW);

INCLUDE_ASM("asm/nonmatchings/P2/freeze", FreezeAloHierarchy__FP3ALOi);

void GetAloFrozen(ALO *palo, int *pf)
{
    *pf = (int)(STRUCT_OFFSET(palo, 0x2c8, unsigned long long) >> 38) & 1;
}

void FreezeAlo(ALO *palo, int fFreeze)
{
    extern VECTOR D_00248D30;

    if (fFreeze)
    {
        SFX *psfx;

        STRUCT_OFFSET(palo, 0xa0, VU_VECTOR) = STRUCT_OFFSET(palo, 0x150, VU_VECTOR);
        STRUCT_OFFSET(palo, 0xb0, VU_VECTOR) = STRUCT_OFFSET(palo, 0x160, VU_VECTOR);
        psfx = STRUCT_OFFSET(palo, 0x2ac, SFX *);
        STRUCT_OFFSET(palo, 0x29c, int) = 0;
        if (psfx)
            StopSound(psfx->pamb, 0);
        (*(void (**)(ALO *, VECTOR *))(*(uint8_t **)palo + 0x90))(palo, &D_00248D30);
        (*(void (**)(ALO *, VECTOR *))(*(uint8_t **)palo + 0x94))(palo, &D_00248D30);
        STRUCT_OFFSET(palo, 0x2c8, unsigned long long) |= (0x8000ULL << 23);
    }
    else
    {
        SFX *psfx;

        STRUCT_OFFSET(palo, 0x2c8, unsigned long long) &= ~(0x8000ULL << 23);
        (*(void (**)(ALO *, VECTOR *))(*(uint8_t **)palo + 0x90))(palo, (VECTOR *)((uint8_t *)palo + 0xa0));
        (*(void (**)(ALO *, VECTOR *))(*(uint8_t **)palo + 0x94))(palo, (VECTOR *)((uint8_t *)palo + 0xb0));
        psfx = STRUCT_OFFSET(palo, 0x2ac, SFX *);
        if (psfx)
            StartSound(psfx->sfxid, &psfx->pamb, palo, NULL, psfx->sStart, psfx->sFull, psfx->uVol, psfx->uPitch, psfx->uDoppler, &psfx->lmRepeat, NULL);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/freeze", FreezeSo__FP2SOi);

INCLUDE_ASM("asm/nonmatchings/P2/freeze", RefreezeSwObjects__FP2SW);

INCLUDE_ASM("asm/nonmatchings/P2/freeze", UpdateSwBusyList__FP2SW);
