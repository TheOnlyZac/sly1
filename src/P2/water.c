#include <water.h>
#include <ensure.h>
#include <vtables.h>
#include <wr.h>
#include <bsp.h>

struct JT;
extern JT *g_pjt;
extern VU_VECTOR D_00248D30;
extern VU_VECTOR g_normalZ;

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

/**
 * @brief ~95% match. The VU0 transform, the LSG[16] clip workspace, the frame
 * layout (fixed via LSG now being 16-byte-vector / 0x70) and the structure all
 * match; only a few instructions in the g_pjt height branch differ (gcc
 * schedules the g_pjt load into a delay slot, and the max.s/add.s operand order
 * canonicalizes differently). Needs the permuter to settle. Kept under SKIP_ASM
 * so the real build uses the asm and the checksum stays green.
 */
INCLUDE_ASM("asm/nonmatchings/P2/water", UGetWaterSubmerged__FP5WATERP2SOP6VECTORT2);
#ifdef SKIP_ASM
float UGetWaterSubmerged(WATER *pwater, SO *pso, VECTOR *pposSurface, VECTOR *pnormalSurface)
{
    VECTOR4 aedge[2];
    LSG alsg[16];
    VECTOR4 scratch;

    void *p278 = STRUCT_OFFSET(pwater, 0x278, void *);
    if (p278 != NULL)
    {
        WR *pwr = STRUCT_OFFSET(p278, 0xC, WR *);
        WarpWrTransform(pwr, 50.0f, (VECTOR *)((char *)pso + 0x140), NULL, (VECTOR *)&aedge[0], NULL, NULL);
        // %0=aedge[0] %1=aedge[1] %2=scratch %3=pso->pos %4=aedge[0](warp)
        asm volatile(
            ".set noat\n\t"
            "lui $1, 0x4000\n\t"
            "mtc1 $1, $f0\n\t"
            "lui $1, 0xbf80\n\t"
            "mtc1 $1, $f1\n\t"
            ".set at\n\t"
            "mfc1 $2, $f0\n\t"
            "qmtc2.ni $2, $vf3\n\t"
            "lqc2 $vf1, %3\n\t"
            "mfc1 $2, $f1\n\t"
            "qmtc2.ni $2, $vf4\n\t"
            "lqc2 $vf2, %4\n\t"
            "vmulax.xyzw ACC, $vf1, $vf3x\n\t"
            "vmaddx.xyzw $vf1, $vf2, $vf4x\n\t"
            "sqc2 $vf3, %2\n\t"
            "sqc2 $vf1, %0\n\t"
            "sqc2 $vf4, %2\n\t"
            "sqc2 $vf1, %1"
            : "=m"(aedge[0]), "=m"(aedge[1]), "=m"(scratch)
            : "m"(STRUCT_OFFSET(pso, 0x140, VU_VECTOR)), "m"(aedge[0])
            : "$1", "$2", "$f0", "$f1");
    }
    else
    {
        *(VU_VECTOR *)&aedge[0] = STRUCT_OFFSET(pso, 0x140, VU_VECTOR);
        *(VU_VECTOR *)&aedge[1] = *(VU_VECTOR *)&aedge[0];
    }

    if ((void *)pso == (void *)g_pjt)
    {
        float z = aedge[0].z + -75.0f;
        if (STRUCT_OFFSET(pso, 0x690, int) == 0)
            aedge[0].z = z;
        else
        {
            float m = STRUCT_OFFSET(pso, 0x6A8, float);
            aedge[0].z = m > z ? m : z;
        }
    }
    else
    {
        aedge[0].z += STRUCT_OFFSET(pso, 0x428, float) - STRUCT_OFFSET(pso, 0x148, float);
    }

    aedge[1].z += STRUCT_OFFSET(pso, 0x438, float) - STRUCT_OFFSET(pso, 0x148, float);

    if (ClsgClipEdgeToBsp(STRUCT_OFFSET(pwater, 0x3F8, BSP *), (VECTOR *)&aedge[0], (VECTOR *)&aedge[1], NULL, 0x10, alsg) == 0)
    {
        if (pnormalSurface != NULL)
            *(VU_VECTOR *)pnormalSurface = g_normalZ;
        return 0.0f;
    }

    if (pposSurface != NULL)
        *(VU_VECTOR *)pposSurface = *(VU_VECTOR *)&alsg[0].apos[1];

    if (pnormalSurface != NULL)
    {
        void *pn = STRUCT_OFFSET(&alsg[0], 0x54, void *);
        if (pn != NULL)
            *(VU_VECTOR *)pnormalSurface = *(VU_VECTOR *)pn;
        else
            *(VU_VECTOR *)pnormalSurface = g_normalZ;
    }

    return alsg[0].au[1] - alsg[0].au[0];
}
#endif

void UpdateWaterBounds(WATER *pwater)
{
    UpdateSoBounds(pwater);

    void *p278 = STRUCT_OFFSET(pwater, 0x278, void *);
    if (p278 == NULL)
        return;

    WR *pwr = STRUCT_OFFSET(p278, 0xC, WR *);
    if (pwr == NULL)
        return;

    VU_VECTOR dpos;
    GetWrBounds(pwr, (VECTOR *)&dpos);

    // %0=vecBoundsMin %1=vecBoundsMax %2=sRadiusBounds %3=unk_0x3d4 %4=dpos
    asm volatile(
        "lqc2 $vf3, %4\n\t"
        "vmul.xyz $vf1, $vf3, $vf3\n\t"
        "vaddw.x $vf2, $vf0, $vf0w\n\t"
        "vadday.x ACC, $vf1, $vf1y\n\t"
        "vmaddz.x $vf1, $vf2, $vf1z\n\t"
        "lwc1 $f2, %2\n\t"
        ".word 0x4A0103BD\n\t" // vsqrt Q, $vf1x
        "vwaitq\n\t"
        "vaddq.x $vf1, $vf0, Q\n\t"
        "lwc1 $f0, %3\n\t"
        "qmfc2.ni $2, $vf1\n\t"
        "mtc1 $2, $f1\n\t"
        "lqc2 $vf2, %0\n\t"
        "lqc2 $vf1, %1\n\t"
        "add.s $f0, $f0, $f1\n\t"
        "add.s $f2, $f2, $f1\n\t"
        "vsub.xyzw $vf2, $vf2, $vf3\n\t"
        "vadd.xyzw $vf1, $vf1, $vf3\n\t"
        "sqc2 $vf2, %0\n\t"
        "sqc2 $vf1, %1\n\t"
        "swc1 $f0, %3\n\t"
        "swc1 $f2, %2"
        : "=m"(pwater->vecBoundsMin), "=m"(pwater->vecBoundsMax),
          "=m"(pwater->sRadiusBounds), "=m"(pwater->unk_0x3d4)
        : "m"(dpos)
        : "$f0", "$f1", "$f2", "$2");
}

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
