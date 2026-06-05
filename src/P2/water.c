#include <water.h>
#include <ensure.h>

void InitWater(WATER *pwater)
{
    InitSo(pwater);

    pwater->grfso |= 0x80000000000;
    pwater->unk_0x584 = 1;
    pwater->unk_0x364 = 1.0f;
    pwater->unk_0x588 = 1;
    pwater->unk_0x360 = 1.0f;

    SetSoConstraints(pwater, CT_Locked, NULL, CT_Locked, NULL);

    InitZpd(&pwater->zpd, pwater);
    pwater->zpd.zpk = ZPK_Water;
}

INCLUDE_ASM("asm/nonmatchings/P2/water", PostWaterLoad__FP5WATER);

INCLUDE_ASM("asm/nonmatchings/P2/water", CalculateWaterCurrent__FP5WATERP6VECTORN21);

void UpdateSwXaList(SW *psw, XA **ppxa)
{
    XA *pxa = *ppxa;
    XA *pxaFree = NULL;

    while (pxa != NULL)
    {
        SO *pso = pxa->pso;
        // grfso is an SO flag word at 0x538; accessed through WATER until the
        // base structs are fully reversed (see WATER definition).
        uint64_t grfso = ((WATER *)pso)->grfso;
        XA *pxaNext = pxa->pxaNextTarget;

        if (((grfso >> 59) & 1) != ((grfso >> 60) & 1))
        {
            if (grfso & (1ULL << 59))
                RemoveSoXa(pso, pxa);
            else
                AddSoXa(pso, pxa);
        }

        if (((WATER *)pxa->pso)->grfso & (1ULL << 60))
        {
            ppxa = &pxa->pxaNextTarget;
        }
        else
        {
            *ppxa = pxaNext;
            pxa->pxaNextTarget = pxaFree;
            pxaFree = pxa;
        }

        uint64_t grfsoClear = ((WATER *)pxa->pso)->grfso;
        grfsoClear &= ~(1ULL << 60);
        grfsoClear &= ~(1ULL << 59);
        ((WATER *)pxa->pso)->grfso = grfsoClear;

        pxa = pxaNext;
    }

    FreeSwXaList(psw, pxaFree);
}

INCLUDE_ASM("asm/nonmatchings/P2/water", UpdateWater__FP5WATERf);

INCLUDE_ASM("asm/nonmatchings/P2/water", AddWaterExternalAccelerations__FP5WATERP2XAf);

INCLUDE_ASM("asm/nonmatchings/P2/water", HandleWaterMessage__FP5WATER5MSGIDPv);

void UpdateWaterMergeGroup(WATER *pwater)
{
    if (pwater->paloRoot != pwater)
        return;

    MRG *pmrg = &pwater->mrg;
    RemoveSwMergeGroup(pwater->psw, pmrg);

    pmrg->apalo[0] = pwater;
    pmrg->cpalo = 1;

    XA *pxa = pwater->pxaFirst;
    while (pxa != NULL)
    {
        int cpalo = pmrg->cpalo;
        pmrg->apalo[cpalo] = pxa->pso;
        pmrg->cpalo = cpalo + 1;
        pxa = pxa->pxaNextTarget;
    }

    AddSwMergeGroup(pwater->psw, pmrg);
}

INCLUDE_ASM("asm/nonmatchings/P2/water", UGetWaterSubmerged__FP5WATERP2SOP6VECTORT2);

INCLUDE_ASM("asm/nonmatchings/P2/water", UpdateWaterBounds__FP5WATER);

int FInflictWaterZap(WATER *pwater, XP *pxp, ZPR *pzpr)
{
    InflictZpdZap(&pwater->zpd, pxp, pzpr);
    return 1;
}

ZPD *PzpdEnsureWater(WATER *pwater, ENSK ensk)
{
    return &pwater->zpd;
}

INCLUDE_ASM("asm/nonmatchings/P2/water", FUN_001ef830);
