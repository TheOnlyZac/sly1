#include <water.h>
#include <ensure.h>
#include <vtables.h>
#include <wr.h>

extern VU_VECTOR D_00248D30;

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

// TODO: logic matches except the DLI-prologue (s_pdliFirst push) store/load
// scheduling; needs decomp-permuter to settle the instruction order.
INCLUDE_ASM("asm/nonmatchings/P2/water", PostWaterLoad__FP5WATER);

void CalculateWaterCurrent(WATER *pwater, VECTOR *ppos, VECTOR *pv, VECTOR *pw)
{
    VU_VECTOR vec0;
    VU_VECTOR vecPos;
    VU_VECTOR vecCur;
    VU_VECTOR vecWarp;

    ConvertAloVec(NULL, pwater, ppos, (VECTOR *)&vec0);
    *(int *)((char *)&vec0 + 8) = 0;
    vecPos = pwater->vecCurrent;
    vecCur = D_00248D30;
    CalculateAloTransformAdjust(pwater, NULL, (VECTOR *)&vec0, NULL, (VECTOR *)&vecPos, (VECTOR *)&vecCur);

    void *p278 = STRUCT_OFFSET(pwater, 0x278, void *);
    if (p278 != NULL)
    {
        WR *pwr = STRUCT_OFFSET(p278, 0xC, WR *);
        WarpWrTransform(pwr, 50.0f, ppos, NULL, NULL, NULL, (VECTOR *)&vecWarp);
        asm volatile(
            "lqc2 $vf1, %1\n\t"
            "lqc2 $vf2, %2\n\t"
            "vadd.xyzw $vf1, $vf1, $vf2\n\t"
            "sqc2 $vf1, %0"
            : "=m"(vecPos)
            : "m"(vecPos), "m"(vecWarp));
    }

    if (pv != NULL)
        *(VU_VECTOR *)pv = vecPos;
    if (pw != NULL)
        *(VU_VECTOR *)pw = vecCur;
}

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

// TODO: blocked on VU0 SIMD (lqc2/sqc2/vsub/vadd) + ~16KB — no VU0 infra yet.
INCLUDE_ASM("asm/nonmatchings/P2/water", UpdateWater__FP5WATERf);

void AddWaterExternalAccelerations(WATER *pwater, XA *pxa, float dt)
{
    SO *pso = pxa->pso;
    ((void (*)(SO *, WATER *))STRUCT_OFFSET(pso->pvtlo, 0x128, void *))(pso, pwater);
}

// TODO: logic matches except the find-one XA loop's gcc form (peeling +
// *ppxa reload); needs decomp-permuter. Handler: MSGID_removed drops the
// object(s) from the XA list and sends MSGID_water_left via pfnSendLoMessage.
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

// TODO: blocked on VU0 SIMD (lqc2/qmtc2/vmulax/vmaddx) — no VU0 infra yet.
INCLUDE_ASM("asm/nonmatchings/P2/water", UGetWaterSubmerged__FP5WATERP2SOP6VECTORT2);

// TODO: blocked on VU0 SIMD (vmul/vsqrt/lqc2/sqc2 bounds math) — no VU0 infra yet.
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
