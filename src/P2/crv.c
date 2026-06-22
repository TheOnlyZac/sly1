#include <crv.h>
#include <mark.h>
#include <bez.h>
#include <memory.h>

INCLUDE_ASM("asm/nonmatchings/P2/crv", SMeasureApos__FiP6VECTORPf);

float GWrapApos(float g, int cpos, float *mpiposg, int fClosed)
{
    float f0 = g;
    if (fClosed == 0) {
        return f0;
    }
    
    float f1 = mpiposg[0];
    float f3 = mpiposg[cpos - 1];
    float f2 = f3 - f1;
    
    while (f0 < f1) {
        f0 = f0 + f2;
    }
    
    while (f3 < f0) {
        f0 = f0 - f2;
    }
    
    return f0;
}

INCLUDE_ASM("asm/nonmatchings/P2/crv", IposFindAposG__FfiPfiT2T2);

INCLUDE_ASM("asm/nonmatchings/P2/crv", EvaluateAposG__FfiP6VECTORPfiT2T2);

INCLUDE_ASM("asm/nonmatchings/P2/crv", FindAposClosestPointAll__FP6VECTORP6CONSTRiT0N20PiPf);

INCLUDE_ASM("asm/nonmatchings/P2/crv", FindAposClosestPointSegment__FP6VECTORP6CONSTRiT0iiT0T0PiPf);

INCLUDE_ASM("asm/nonmatchings/P2/crv", ConvertApos__FiP6VECTORP7MATRIX4T2);

extern char D_002176D0[];
extern char D_00217708[];

CRV *PcrvNew(CRVK crvk)
{
    CRV *pcrv;

    switch (crvk)
    {
    case CRVK_Linear:
        pcrv = (CRV *)PvAllocSwClearImpl(0x1C);
        pcrv->unknown = (undefined4)&D_002176D0;
        break;
    case CRVK_Cubic:
        pcrv = (CRV *)PvAllocSwClearImpl(0x1D0);
        pcrv->unknown = (undefined4)&D_00217708;
        break;
    default:
        pcrv = NULL;
        break;
    }

    if (pcrv != NULL)
        pcrv->crvk = crvk;

    return pcrv;
}

float SFromCrvU(CRV *pcrv, float u)
{
    return 0.0f;
}

float UFromCrvS(CRV *pcrv, float s)
{
    return 0.0f;
}

int IcvFindCrvU(CRV *pcrv, float u, float *du, float *duSeg)
{
    return IposFindAposG(u, pcrv->ccv, pcrv->mpicvu, pcrv->fClosed, du, duSeg);
}

int IcvFindCrvS(CRV *pcrv, float s, float *ds, float *dsSeg)
{
    return IposFindAposG(s, pcrv->ccv, pcrv->mpicvs, pcrv->fClosed, ds, dsSeg);
}

INCLUDE_ASM("asm/nonmatchings/P2/crv", GMeasureCrvU__FP5CRVMCf);

float UMaxCrv(CRV *pcrv)
{
    return pcrv->mpicvu[pcrv->ccv - 1];
}

float SMaxCrv(CRV *pcrv)
{
    return pcrv->mpicvs[pcrv->ccv - 1];
}

JUNK_ADDIU(A0);

float SMeasureCrvSegmentU(CRVMS *pcrvms, float u)
{
    VECTOR pos;
    float du, ps;
    void *pcrv;
    void **pvtbl;
    void (*pfn)(void *, VECTOR *, int);

    pcrv = STRUCT_OFFSET(pcrvms, 0x0, void *);
    pvtbl = STRUCT_OFFSET(pcrv, 0x0, void **);
    pfn = (void (*)(void *, VECTOR *, int))pvtbl[1];
    if (pfn != NULL)
    {
        pfn(pcrv, &pos, 0);
    }

    FindClosestPointOnLineSegment(&pos, STRUCT_OFFSET(pcrvms, 0x4, VECTOR *), STRUCT_OFFSET(pcrvms, 0x8, VECTOR *), &du, &ps);
    return ps;
}

INCLUDE_ASM("asm/nonmatchings/P2/crv", FindCrvClosestPointOnLineSegmentFromU__FP3CRVP6VECTORT1fT1T1PfT6);

JUNK_ADDIU(A0);

float DuGetCrvSearchIncrement(CRV *pcrv)
{
    return (pcrv->mpicvu[1] - pcrv->mpicvu[0]) * 0.1f;
}

INCLUDE_ASM("asm/nonmatchings/P2/crv", LoadCrvlFromBrx__FP4CRVLP18CBinaryInputStream);

void EvaluateCrvlFromU(CRVL *pcrvl, float u, VECTOR *ppos, VECTOR *pnormTangent)
{
    EvaluateAposG(
        u,
        STRUCT_OFFSET(pcrvl, 0xC, int),
        STRUCT_OFFSET(pcrvl, 0x18, VECTOR *),
        STRUCT_OFFSET(pcrvl, 0x10, float *),
        STRUCT_OFFSET(pcrvl, 0x8, int),
        ppos,
        pnormTangent);
}

void EvaluateCrvlFromS(CRVL *pcrvl, float s, VECTOR *ppos, VECTOR *pnormTangent)
{
    EvaluateAposG(
        s,
        STRUCT_OFFSET(pcrvl, 0xC, int),
        STRUCT_OFFSET(pcrvl, 0x18, VECTOR *),
        STRUCT_OFFSET(pcrvl, 0x14, float *),
        STRUCT_OFFSET(pcrvl, 0x8, int),
        ppos,
        pnormTangent);
}

INCLUDE_ASM("asm/nonmatchings/P2/crv", RenderCrvlSegment__FP4CRVLiP7MATRIX4P2CMG4RGBAi);

void ConvertCrvl(CRVL *pcrvl, MATRIX4 *pmatSrc, MATRIX4 *pmatDst)
{
    ConvertApos(STRUCT_OFFSET(pcrvl, 0xC, int), STRUCT_OFFSET(pcrvl, 0x18, VECTOR *), pmatSrc, pmatDst);
}

float SFromCrvlU(CRVL *pcrvl, float u)
{
    float du;
    float duSeg;
    int icv;
    float frac;
    float *mpicvs;

    icv = IcvFindCrvU((CRV *)pcrvl, u, &du, &duSeg);
    frac = du / duSeg;
    mpicvs = ((CRV *)pcrvl)->mpicvs;
    return (1.0f - frac) * mpicvs[icv] + frac * mpicvs[icv + 1];
}

float UFromCrvlS(CRVL *pcrvl, float s)
{
    float ds, dsSeg;
    int icv;
    float *mpicvu;
    float u0, u1;
    float result;

    icv = IcvFindCrvS((CRV *)pcrvl, s, &ds, &dsSeg);
    mpicvu = STRUCT_OFFSET(pcrvl, 0x10, float *);
    u0 = mpicvu[icv];
    u1 = mpicvu[icv + 1];
    result = (1.0f - (ds / dsSeg)) * u0 + (ds / dsSeg) * u1;
    return result;
}

void MeasureCrvl(CRVL *pcrvl)
{
    SMeasureApos(STRUCT_OFFSET(pcrvl, 0xC, int), STRUCT_OFFSET(pcrvl, 0x18, VECTOR *), STRUCT_OFFSET(pcrvl, 0x14, float *));
}

INCLUDE_ASM("asm/nonmatchings/P2/crv", FindCrvlClosestPointAll__FP4CRVLP6VECTORP6CONSTRT1T1PfT5);

INCLUDE_ASM("asm/nonmatchings/P2/crv", FindCrvlClosestPointFromU__FP4CRVLP6VECTORfP6CONSTRT1T1PfT6);

INCLUDE_ASM("asm/nonmatchings/P2/crv", FindCrvlClosestPointFromS__FP4CRVLP6VECTORfP6CONSTRT1T1PfT6);

void LoadCrvcFromBrx(CRVC *pcrvc, CBinaryInputStream *pbis)
{
    int icv;
    int ccv;

    STRUCT_OFFSET(pcrvc, 0x8, int) = pbis->U8Read();
    ccv = pbis->U8Read();
    STRUCT_OFFSET(pcrvc, 0xC, int) = ccv;
    STRUCT_OFFSET(pcrvc, 0x10, void *) = PvAllocSwImpl(ccv * 4);
    STRUCT_OFFSET(pcrvc, 0x14, void *) = PvAllocSwImpl(STRUCT_OFFSET(pcrvc, 0xC, int) * 4);
    STRUCT_OFFSET(pcrvc, 0x18, void *) = PvAllocSwImpl(STRUCT_OFFSET(pcrvc, 0xC, int) * 16);
    STRUCT_OFFSET(pcrvc, 0x1C, void *) = PvAllocSwImpl(STRUCT_OFFSET(pcrvc, 0xC, int) * 16);
    STRUCT_OFFSET(pcrvc, 0x20, void *) = PvAllocSwImpl(STRUCT_OFFSET(pcrvc, 0xC, int) * 16);

    for (icv = 0; icv < STRUCT_OFFSET(pcrvc, 0xC, int); icv++)
    {
        STRUCT_OFFSET(pcrvc, 0x10, float *)[icv] = pbis->F32Read();
        pbis->ReadVector((VECTOR *)((char *)STRUCT_OFFSET(pcrvc, 0x18, void *) + icv * 16));
        pbis->ReadVector((VECTOR *)((char *)STRUCT_OFFSET(pcrvc, 0x1C, void *) + icv * 16));
        pbis->ReadVector((VECTOR *)((char *)STRUCT_OFFSET(pcrvc, 0x20, void *) + icv * 16));
    }

    if (STRUCT_OFFSET(*(void **)pcrvc, 0x24, void *) != NULL)
    {
        ((void (*)(CRVC *))STRUCT_OFFSET(*(void **)pcrvc, 0x24, void *))(pcrvc);
    }

    InvalidateCrvcCache(pcrvc);
}

void InvalidateCrvcCache(CRVC *pcrvc)
{
    STRUCT_OFFSET(pcrvc, 0x1c0, int) = -1;
}

INCLUDE_ASM("asm/nonmatchings/P2/crv", FillCrvcCache__FP4CRVCi);

INCLUDE_ASM("asm/nonmatchings/P2/crv", EvaluateCrvcFromU__FP4CRVCfP6VECTORT2);

void EvaluateCrvcFromS(CRVC *pcrvc, float s, VECTOR *ppos, VECTOR *pnormTangent)
{
    float u;

    u = ((float (*)(CRVC *, float))STRUCT_OFFSET(*(void **)pcrvc, 0x18, void *))(pcrvc, s);
    if (STRUCT_OFFSET(*(void **)pcrvc, 0x4, void *))
    {
        ((void (*)(CRVC *, float, VECTOR *, VECTOR *))STRUCT_OFFSET(*(void **)pcrvc, 0x4, void *))(pcrvc, u, ppos, pnormTangent);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/crv", RenderCrvcSegment__FP4CRVCiP7MATRIX4P2CMG4RGBAi);

INCLUDE_ASM("asm/nonmatchings/P2/crv", ConvertCrvc__FP4CRVCP7MATRIX4T1);

float SFromCrvcU(CRVC *pcrvc, float u)
{
    float du;
    float duSeg;
    int icv;

    icv = IcvFindCrvU((CRV *)pcrvc, u, &du, &duSeg);

    return SBezierPosLength(
               duSeg,
               du,
               (VECTOR *)((char *)STRUCT_OFFSET(pcrvc, 0x18, void *) + icv * 16),
               (VECTOR *)((char *)STRUCT_OFFSET(pcrvc, 0x20, void *) + icv * 16),
               (VECTOR *)((char *)STRUCT_OFFSET(pcrvc, 0x18, void *) + (icv * 16 + 16)),
               (VECTOR *)((char *)STRUCT_OFFSET(pcrvc, 0x1C, void *) + (icv * 16 + 16))) +
           STRUCT_OFFSET(pcrvc, 0x14, float *)[icv];
}

float UFromCrvcS(CRVC *pcrvc, float s)
{
    int icv;
    int ipos;
    float g;
    float dg;
    float dgSeg;
    float u;
    float *pmp;

    icv = IcvFindCrvS((CRV *)pcrvc, s, &g, NULL);
    FillCrvcCache(pcrvc, icv);
    ipos = IposFindAposG(g, 0x14, &STRUCT_OFFSET(pcrvc, 0x170, float), 0, &dg, &dgSeg);
    pmp = STRUCT_OFFSET(pcrvc, 0x10, float *);
    u = ((float)ipos + dg / dgSeg) * (1.0f / 19.0f);
    return (1.0f - u) * pmp[icv] + u * pmp[icv + 1];
}

INCLUDE_ASM("asm/nonmatchings/P2/crv", MeasureCrvc__FP4CRVC);

INCLUDE_ASM("asm/nonmatchings/P2/crv", FindCrvcClosestPointAll__FP4CRVCP6VECTORP6CONSTRT1T1PfT5);

INCLUDE_ASM("asm/nonmatchings/P2/crv", FindCrvcClosestPointFromU__FP4CRVCP6VECTORfP6CONSTRT1T1PfT6);

INCLUDE_ASM("asm/nonmatchings/P2/crv", FindCrvcClosestPointFromS__FP4CRVCP6VECTORfP6CONSTRT1T1PfT6);
