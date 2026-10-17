#include <crv.h>
#include <bez.h>
#include <util.h>
#include <mark.h>
#include <memory.h>

extern VTCRVL g_vtcrvl;
extern VTCRVC g_vtcrvc;

// TODO: Remove once rodata is migrated.
extern float D_00249FC0;
extern float D_00249FC4;

INCLUDE_ASM("asm/nonmatchings/P2/crv", SMeasureApos__FiP6VECTORPf);

INCLUDE_ASM("asm/nonmatchings/P2/crv", GWrapApos__FfiPfi);

INCLUDE_ASM("asm/nonmatchings/P2/crv", IposFindAposG__FfiPfiT2T2);

INCLUDE_ASM("asm/nonmatchings/P2/crv", EvaluateAposG__FfiP6VECTORPfiT2T2);

INCLUDE_ASM("asm/nonmatchings/P2/crv", FindAposClosestPointAll__FP6VECTORP6CONSTRiT0N20PiPf);

INCLUDE_ASM("asm/nonmatchings/P2/crv", FindAposClosestPointSegment__FP6VECTORP6CONSTRiT0iiT0T0PiPf);

INCLUDE_ASM("asm/nonmatchings/P2/crv", ConvertApos__FiP6VECTORP7MATRIX4T2);

CRV *PcrvNew(CRVK crvk)
{
    CRV *pcrv;
    switch (crvk)
    {
        case CRVK_Linear:
        {
            pcrv = (CRV *)PvAllocSwClearImpl(0x1c); // TODO: Replace with sizeof.
            pcrv->pvtcrvl = &g_vtcrvl;
            break;
        }
        case CRVK_Cubic:
        {
            pcrv = (CRV *)PvAllocSwClearImpl(0x1d0); // TODO: Replace with sizeof.
            pcrv->pvtcrvc = &g_vtcrvc;
            break;
        }
        default:
        {
            pcrv = NULL;
            break;
        }
    }

    if (pcrv)
    {
        pcrv->crvk = crvk;
    }

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
    if (pcrvms->pcrv->pvtcrv->pfnEvaluateCrvFromU)
    {
        pcrvms->pcrv->pvtcrv->pfnEvaluateCrvFromU(pcrvms->pcrv, u, &pos, NULL);
    }

    float uSeg, s;
    FindClosestPointOnLineSegment(&pos, pcrvms->ppos0, pcrvms->ppos1, &uSeg, &s);
    return s;
}

void FindCrvClosestPointOnLineSegmentFromU(CRV *pcrv, VECTOR *ppos0, VECTOR *ppos1, float u, VECTOR *pposClosest, VECTOR *pnormTangentClosest, float *pu, float *ps)
{
    float uBest;
    CRVMS crvms;
    crvms.pcrv = pcrv;
    crvms.ppos0 = ppos0;
    crvms.ppos1 = ppos1;
    MinimizeRange(
        SMeasureCrvSegmentU, &crvms, u,
        (pcrv->mpicvu[1] - pcrv->mpicvu[0]) * 0.1f,
        (pcrv->fClosed) ? D_00249FC0 : pcrv->mpicvu[0],
        (pcrv->fClosed) ? D_00249FC4 : pcrv->mpicvu[pcrv->ccv - 1],
        &uBest, NULL
    );

    if (pposClosest || pnormTangentClosest)
    {
        if (pcrv->pvtcrv->pfnEvaluateCrvFromU)
        {
            pcrv->pvtcrv->pfnEvaluateCrvFromU(pcrv, uBest, pposClosest, pnormTangentClosest);
        }
    }

    if (pu)
    {
        *pu = uBest;
    }
    if (ps)
    {
        *ps = pcrv->pvtcrv->pfnSFromCrvU(pcrv, uBest);
    }
}

JUNK_NOP();
JUNK_ADDIU(A0);

float DuGetCrvSearchIncrement(CRV *pcrv)
{
    return (pcrv->mpicvu[1] - pcrv->mpicvu[0]) * 0.1f;
}

void LoadCrvlFromBrx(CRVL *pcrvl, CBinaryInputStream *pbis)
{
    pcrvl->fClosed = pbis->U8Read();
    pcrvl->ccv = pbis->U8Read();

    pcrvl->mpicvu = (float *)PvAllocSwImpl(pcrvl->ccv * sizeof(float));
    pcrvl->mpicvs = (float *)PvAllocSwImpl(pcrvl->ccv * sizeof(float));
    pcrvl->mpicvpos = (VECTOR *)PvAllocSwImpl(pcrvl->ccv * sizeof(VECTOR));

    for (int i = 0; i < pcrvl->ccv; i++)
    {
        pcrvl->mpicvu[i] = pbis->F32Read();
        pbis->ReadVector(&pcrvl->mpicvpos[i]);
    }

    if (pcrvl->pvtcrv->pfnMeasureCrv)
    {
        pcrvl->pvtcrv->pfnMeasureCrv(pcrvl);
    }
}

void EvaluateCrvlFromU(CRVL *pcrvl, float u, VECTOR *ppos, VECTOR *pnormTangent)
{
    EvaluateAposG(u, pcrvl->ccv, pcrvl->mpicvpos, pcrvl->mpicvu, pcrvl->fClosed, ppos, pnormTangent);
}

void EvaluateCrvlFromS(CRVL *pcrvl, float s, VECTOR *ppos, VECTOR *pnormTangent)
{
    EvaluateAposG(s, pcrvl->ccv, pcrvl->mpicvpos, pcrvl->mpicvs, pcrvl->fClosed, ppos, pnormTangent);
}

INCLUDE_ASM("asm/nonmatchings/P2/crv", RenderCrvlSegment__FP4CRVLiP7MATRIX4P2CMG4RGBAi);

void ConvertCrvl(CRVL *pcrvl, MATRIX4 *pmatSrc, MATRIX4 *pmatDst)
{
    ConvertApos(pcrvl->ccv, pcrvl->mpicvpos, pmatSrc, pmatDst);
}

float SFromCrvlU(CRVL *pcrvl, float u)
{
    float du, duSeg;
    int iU = IcvFindCrvU(pcrvl, u, &du, &duSeg);
    return (1.0f - du / duSeg) * pcrvl->mpicvs[iU] + (du / duSeg) * pcrvl->mpicvs[iU + 1];
}

float UFromCrvlS(CRVL *pcrvl, float s)
{
    float du, duSeg;
    int iU = IcvFindCrvS(pcrvl, s, &du, &duSeg);
    return (1.0f - du / duSeg) * pcrvl->mpicvu[iU] + (du / duSeg) * pcrvl->mpicvu[iU + 1];
}

void MeasureCrvl(CRVL *pcrvl)
{
    SMeasureApos(pcrvl->ccv, pcrvl->mpicvpos, pcrvl->mpicvs);
}

void FindCrvlClosestPointAll(CRVL *pcrvl, VECTOR *ppos, CONSTR *pconstr, VECTOR *pposClosest, VECTOR *pnormTangentClosest, float *pu, float *ps)
{
    int icv;
    float r;
    FindAposClosestPointAll(ppos, pconstr, pcrvl->ccv, pcrvl->mpicvpos, pposClosest, pnormTangentClosest, &icv, &r);

    if (ps)
    {
        *ps = (1.0f - r) * pcrvl->mpicvs[icv] + r * pcrvl->mpicvs[icv + 1];
    }
    if (pu)
    {
        *pu = (1.0f - r) * pcrvl->mpicvu[icv] + r * pcrvl->mpicvu[icv + 1];
    }
}

void FindCrvlClosestPointFromU(CRVL *pcrvl, VECTOR *ppos, float u, CONSTR *pconstr, VECTOR *pposClosest, VECTOR *pnormTangentClosest, float *pu, float *ps)
{
    int iposStart = IposFindAposG(u, pcrvl->ccv, pcrvl->mpicvu, pcrvl->fClosed, NULL, NULL);

    int icv;
    float r;
    FindAposClosestPointSegment(
        ppos, pconstr, pcrvl->ccv,
        pcrvl->mpicvpos, iposStart,
        pcrvl->fClosed, pposClosest,
        pnormTangentClosest, &icv, &r
    );

    if (ps)
    {
        *ps = (1.0f - r) * pcrvl->mpicvs[icv] + r * pcrvl->mpicvs[icv + 1];
    }
    if (pu)
    {
        *pu = (1.0f - r) * pcrvl->mpicvu[icv] + r * pcrvl->mpicvu[icv + 1];
    }
}

void FindCrvlClosestPointFromS(CRVL *pcrvl, VECTOR *ppos, float s, CONSTR *pconstr, VECTOR *pposClosest, VECTOR *pnormTangentClosest, float *pu, float *ps)
{
    int iposStart = IposFindAposG(s, pcrvl->ccv, pcrvl->mpicvs, pcrvl->fClosed, NULL, NULL);

    int icv;
    float r;
    FindAposClosestPointSegment(
        ppos, pconstr, pcrvl->ccv,
        pcrvl->mpicvpos, iposStart,
        pcrvl->fClosed, pposClosest,
        pnormTangentClosest, &icv, &r
    );

    if (ps)
    {
        *ps = (1.0f - r) * pcrvl->mpicvs[icv] + r * pcrvl->mpicvs[icv + 1];
    }
    if (pu)
    {
        *pu = (1.0f - r) * pcrvl->mpicvu[icv] + r * pcrvl->mpicvu[icv + 1];
    }
}

void LoadCrvcFromBrx(CRVC *pcrvc, CBinaryInputStream *pbis)
{
    pcrvc->fClosed = pbis->U8Read();
    pcrvc->ccv = pbis->U8Read();
    pcrvc->mpicvu = (float *)PvAllocSwImpl(pcrvc->ccv * sizeof(float));
    pcrvc->mpicvs = (float *)PvAllocSwImpl(pcrvc->ccv * sizeof(float));
    pcrvc->mpicvpos = (VECTOR *)PvAllocSwImpl(pcrvc->ccv * sizeof(VECTOR));
    pcrvc->mpicvdposIn = (VECTOR *)PvAllocSwImpl(pcrvc->ccv * sizeof(VECTOR));
    pcrvc->mpicvdposOut = (VECTOR *)PvAllocSwImpl(pcrvc->ccv * sizeof(VECTOR));

    for (int i = 0; i < pcrvc->ccv; i++)
    {
        pcrvc->mpicvu[i] = pbis->F32Read();
        pbis->ReadVector(&pcrvc->mpicvpos[i]);
        pbis->ReadVector(&pcrvc->mpicvdposIn[i]);
        pbis->ReadVector(&pcrvc->mpicvdposOut[i]);
    }

    if (pcrvc->pvtcrv->pfnMeasureCrv)
    {
        pcrvc->pvtcrv->pfnMeasureCrv(pcrvc);
    }

    InvalidateCrvcCache(pcrvc);
}

void InvalidateCrvcCache(CRVC *pcrvc)
{
    pcrvc->icvCache = -1;
}

INCLUDE_ASM("asm/nonmatchings/P2/crv", FillCrvcCache__FP4CRVCi);

INCLUDE_ASM("asm/nonmatchings/P2/crv", EvaluateCrvcFromU__FP4CRVCfP6VECTORT2);

void EvaluateCrvcFromS(CRVC *pcrvc, float s, VECTOR *ppos, VECTOR *pnormTangent)
{
    float u = pcrvc->pvtcrv->pfnUFromCrvS(pcrvc, s);

    if (pcrvc->pvtcrv->pfnEvaluateCrvFromU)
    {
        pcrvc->pvtcrv->pfnEvaluateCrvFromU(pcrvc, u, ppos, pnormTangent);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/crv", RenderCrvcSegment__FP4CRVCiP7MATRIX4P2CMG4RGBAi);

INCLUDE_ASM("asm/nonmatchings/P2/crv", ConvertCrvc__FP4CRVCP7MATRIX4T1);

float SFromCrvcU(CRVC *pcrvc, float u)
{
    float du, duSeg;
    int icv = IcvFindCrvU(pcrvc, u, &du, &duSeg);
    return SBezierPosLength(duSeg, du, &pcrvc->mpicvpos[icv], &pcrvc->mpicvdposOut[icv], &pcrvc->mpicvpos[icv + 1], &pcrvc->mpicvdposIn[icv + 1]) + pcrvc->mpicvs[icv];
}

INCLUDE_ASM("asm/nonmatchings/P2/crv", UFromCrvcS__FP4CRVCf);

INCLUDE_ASM("asm/nonmatchings/P2/crv", MeasureCrvc__FP4CRVC);

INCLUDE_ASM("asm/nonmatchings/P2/crv", FindCrvcClosestPointAll__FP4CRVCP6VECTORP6CONSTRT1T1PfT5);

INCLUDE_ASM("asm/nonmatchings/P2/crv", FindCrvcClosestPointFromU__FP4CRVCP6VECTORfP6CONSTRT1T1PfT6);

void FindCrvcClosestPointFromS(CRVC *pcrvc, VECTOR *ppos, float s, CONSTR *pconstr, VECTOR *pposClosest, VECTOR *pnormTangentClosest, float *pu, float *ps)
{
    float u = pcrvc->pvtcrv->pfnUFromCrvS(pcrvc, s);

    if (pcrvc->pvtcrv->pfnFindCrvClosestPointFromU)
    {
        pcrvc->pvtcrv->pfnFindCrvClosestPointFromU(pcrvc, ppos, u, pconstr, pposClosest, pnormTangentClosest, pu, ps);
    }
}
