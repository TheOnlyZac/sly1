#include <ac.h>

INCLUDE_ASM(const s32, "P2/ac", FindKey__FfiiiPcPfT5PPv);

void EvaluateAcp(ACP *pacp, ALO *palo, float t, float svt, GRFEVAL grfeval, VECTOR *ppos, VECTOR *pv)
{
    return;
}

INCLUDE_ASM(const s32, "P2/ac", GetAcpTimes__FP3ACPPiPPf);

void EvaluateAcr(ACR *pacr, ALO *palo, float t, float svt, GRFEVAL grfeval, MATRIX3 *pmat, VECTOR *pw)
{
    return;
}

void EvaluateAcrEul(ACR *pacr, ALO *palo, float t, float svt, GRFEVAL grfeval, VECTOR *peul, VECTOR *pdeul)
{
    return;
}

INCLUDE_ASM(const s32, "P2/ac", GetAcrTimes__FP3ACRPiPPf);

void EvaluateAcs(ACS *pacs, ALO *palo, float t, GRFEVAL grfeval, MATRIX3 *pmat)
{
    return;
}

INCLUDE_ASM(const s32, "P2/ac", GetAcsTimes__FP3ACSPiPPf);

void EvaluateAcg(ACG *pacg, ALO *palo, float t, float svt, GRFEVAL grfeval, float *pg, float *pdg)
{
    return;
}

INCLUDE_ASM(const s32, "P2/ac", GetAcgTimes__FP3ACGPiPPf);

INCLUDE_ASM(const s32, "P2/ac", LoadAcgbFromBrx__FP4ACGBP18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/ac", EvaluateAcgb__FP4ACGBP3ALOffiPfT5);

INCLUDE_ASM(const s32, "P2/ac", GetAcgbTimes__FP4ACGBPiPPf);

INCLUDE_ASM(const s32, "P2/ac", LoadAcgbwFromBrx__FP5ACGBWP18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/ac", EvaluateAcgbw__FP5ACGBWP3ALOffiPfT5);

INCLUDE_ASM(const s32, "P2/ac", GetAcgbwTimes__FP5ACGBWPiPPf);

INCLUDE_ASM(const s32, "P2/ac", EvaluateAcgl__FP4ACGLP3ALOffiPfT5);

INCLUDE_ASM(const s32, "P2/ac", LoadAcglFromBrx__FP4ACGLP18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/ac", GetAcglTimes__FP4ACGLPiPPf);

INCLUDE_ASM(const s32, "P2/ac", EvaluateApacg__FPP3ACGP3ALOffiP6VECTORN25);

INCLUDE_ASM(const s32, "P2/ac", LoadApacgFromBrx__FPP3ACGP6VECTORP18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/ac", GetApacgTimes__FPP3ACGPiPPf);

INCLUDE_ASM(const s32, "P2/ac", EvaluateAkvb__FiP3KVBffiP6VECTORT5);

INCLUDE_ASM(const s32, "P2/ac", LoadAkvbFromBrx__FPiPP3KVBP18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/ac", GetAkvbTimes__FiP3KVBPiPPf);

INCLUDE_ASM(const s32, "P2/ac", EvaluateAcpc__FP4ACPCP3ALOffiP6VECTORT5);

INCLUDE_ASM(const s32, "P2/ac", LoadAcpcFromBrx__FP4ACPCP18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/ac", GetAcpcTimes__FP4ACPCPiPPf);

INCLUDE_ASM(const s32, "P2/ac", EvaluateAcpb__FP4ACPBP3ALOffiP6VECTORT5);

INCLUDE_ASM(const s32, "P2/ac", LoadAcpbFromBrx__FP4ACPBP18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/ac", GetAcpbTimes__FP4ACPBPiPPf);

INCLUDE_ASM(const s32, "P2/ac", EvaluateAcrc__FP4ACRCP3ALOffiP7MATRIX3P6VECTOR);

INCLUDE_ASM(const s32, "P2/ac", EvaluateAcrcEul__FP4ACRCP3ALOffiP6VECTORT5);

INCLUDE_ASM(const s32, "P2/ac", LoadAcrcFromBrx__FP4ACRCP18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/ac", GetAcrcTimes__FP4ACRCPiPPf);

INCLUDE_ASM(const s32, "P2/ac", EvaluateAcrb__FP4ACRBP3ALOffiP7MATRIX3P6VECTOR);

INCLUDE_ASM(const s32, "P2/ac", EvaluateAcrbEul__FP4ACRBP3ALOffiP6VECTORT5);

INCLUDE_ASM(const s32, "P2/ac", LoadAcrbFromBrx__FP4ACRBP18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/ac", GetAcrbTimes__FP4ACRBPiPPf);

INCLUDE_ASM(const s32, "P2/ac", EvaluateAcsc__FP4ACSCP3ALOfiP7MATRIX3);

INCLUDE_ASM(const s32, "P2/ac", LoadAcscFromBrx__FP4ACSCP18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/ac", GetAcscTimes__FP4ACSCPiPPf);

INCLUDE_ASM(const s32, "P2/ac", EvaluateAcsb__FP4ACSBP3ALOfiP7MATRIX3);

INCLUDE_ASM(const s32, "P2/ac", LoadAcsbFromBrx__FP4ACSBP18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/ac", GetAcsbTimes__FP4ACSBPiPPf);

INCLUDE_ASM(const s32, "P2/ac", EvaluateAcpbl__FP5ACPBLP3ALOffiP6VECTORT5);

INCLUDE_ASM(const s32, "P2/ac", EvaluateAcrbl__FP5ACRBLP3ALOffiP7MATRIX3P6VECTOR);

INCLUDE_ASM(const s32, "P2/ac", EvaluateAcgblt__FP6ACGBLTP3ALOffiPfT5);

INCLUDE_ASM(const s32, "P2/ac", EvaluateAcgblp__FP6ACGBLPP3ALOffiPfT5);

INCLUDE_ASM(const s32, "P2/ac", PacpNew__F4ACVK);

INCLUDE_ASM(const s32, "P2/ac", PacrNew__F4ACVK);

INCLUDE_ASM(const s32, "P2/ac", PacsNew__F4ACVK);

INCLUDE_ASM(const s32, "P2/ac", PacgNew__F4ACGK);
