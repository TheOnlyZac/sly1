#include <crv.h>
#include <mark.h>

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

INCLUDE_ASM("asm/nonmatchings/P2/crv", PcrvNew__F4CRVK);

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

INCLUDE_ASM("asm/nonmatchings/P2/crv", SFromCrvlU__FP4CRVLf);

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

INCLUDE_ASM("asm/nonmatchings/P2/crv", LoadCrvcFromBrx__FP4CRVCP18CBinaryInputStream);

void InvalidateCrvcCache(CRVC *pcrvc)
{
    STRUCT_OFFSET(pcrvc, 0x1c0, int) = -1;
}

INCLUDE_ASM("asm/nonmatchings/P2/crv", FillCrvcCache__FP4CRVCi);

INCLUDE_ASM("asm/nonmatchings/P2/crv", EvaluateCrvcFromU__FP4CRVCfP6VECTORT2);

INCLUDE_ASM("asm/nonmatchings/P2/crv", EvaluateCrvcFromS__FP4CRVCfP6VECTORT2);

INCLUDE_ASM("asm/nonmatchings/P2/crv", RenderCrvcSegment__FP4CRVCiP7MATRIX4P2CMG4RGBAi);

INCLUDE_ASM("asm/nonmatchings/P2/crv", ConvertCrvc__FP4CRVCP7MATRIX4T1);

INCLUDE_ASM("asm/nonmatchings/P2/crv", SFromCrvcU__FP4CRVCf);

INCLUDE_ASM("asm/nonmatchings/P2/crv", UFromCrvcS__FP4CRVCf);

INCLUDE_ASM("asm/nonmatchings/P2/crv", MeasureCrvc__FP4CRVC);

INCLUDE_ASM("asm/nonmatchings/P2/crv", FindCrvcClosestPointAll__FP4CRVCP6VECTORP6CONSTRT1T1PfT5);

INCLUDE_ASM("asm/nonmatchings/P2/crv", FindCrvcClosestPointFromU__FP4CRVCP6VECTORfP6CONSTRT1T1PfT6);

INCLUDE_ASM("asm/nonmatchings/P2/crv", FindCrvcClosestPointFromS__FP4CRVCP6VECTORfP6CONSTRT1T1PfT6);
