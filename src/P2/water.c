#include <water.h>
#include <ensure.h>
#include <vtables.h>

void InitWater(WATER *pwater)
{
    InitSo(pwater);

    STRUCT_OFFSET(pwater, 0x538, uint64_t) |= 0x80000000000;
    pwater->unk_0x584 = 1;
    STRUCT_OFFSET(pwater, 0x364, float) = 1.0f;
    pwater->unk_0x588 = 1;
    STRUCT_OFFSET(pwater, 0x360, float) = 1.0f;

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
        uint64_t grfso = STRUCT_OFFSET(pso, 0x538, uint64_t);
        XA *pxaNext = pxa->pxaNextTarget;

        if (((grfso >> 59) & 1) != ((grfso >> 60) & 1))
        {
            if (grfso & (1ULL << 59))
                RemoveSoXa(pso, pxa);
            else
                AddSoXa(pso, pxa);
        }

        if (STRUCT_OFFSET(pxa->pso, 0x538, uint64_t) & (1ULL << 60))
        {
            ppxa = &pxa->pxaNextTarget;
        }
        else
        {
            *ppxa = pxaNext;
            pxa->pxaNextTarget = pxaFree;
            pxaFree = pxa;
        }

        uint64_t grfsoClear = STRUCT_OFFSET(pxa->pso, 0x538, uint64_t);
        grfsoClear &= ~(1ULL << 60);
        grfsoClear &= ~(1ULL << 59);
        STRUCT_OFFSET(pxa->pso, 0x538, uint64_t) = grfsoClear;

        pxa = pxaNext;
    }

    FreeSwXaList(psw, pxaFree);
}

INCLUDE_ASM("asm/nonmatchings/P2/water", UpdateWater__FP5WATERf);

void AddWaterExternalAccelerations(WATER *pwater, XA *pxa, float dt)
{
    SO *pso = pxa->pso;
    ((void (*)(SO *, WATER *))STRUCT_OFFSET(pso->pvtlo, 0x128, void *))(pso, pwater);
}

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

void FUN_001ef830(WATER *pwater)
{
    pwater->zpd.cploThrow = 0;
}
