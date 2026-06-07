#include <crv.h>

INCLUDE_ASM("asm/nonmatchings/P2/crv", SMeasureApos__FiP6VECTORPf);

INCLUDE_ASM("asm/nonmatchings/P2/crv", GWrapApos__FfiPfi);

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

INCLUDE_ASM("asm/nonmatchings/P2/crv", IcvFindCrvU__FP3CRVfPfT2);

INCLUDE_ASM("asm/nonmatchings/P2/crv", IcvFindCrvS__FP3CRVfPfT2);

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

INCLUDE_ASM("asm/nonmatchings/P2/crv", SMeasureCrvSegmentU__FP5CRVMSf);

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

INCLUDE_ASM("asm/nonmatchings/P2/crv", ConvertCrvl__FP4CRVLP7MATRIX4T1);

INCLUDE_ASM("asm/nonmatchings/P2/crv", SFromCrvlU__FP4CRVLf);

INCLUDE_ASM("asm/nonmatchings/P2/crv", UFromCrvlS__FP4CRVLf);

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
