#include <ac.h>

INCLUDE_ASM("asm/nonmatchings/P2/ac", FindKey__FfiiiPcPfT5PPv);

void EvaluateAcp(ACP *pacp, ALO *palo, float t, float svt, GRFEVAL grfeval, VECTOR *ppos, VECTOR *pv)
{
    return;
}

void GetAcpTimes(ACP *pacp, int *pct, float **pat)
{
    *pct = 0;
    if (pat)
    {
        *pat = (float *)nullptr;
    }
}

void EvaluateAcr(ACR *pacr, ALO *palo, float t, float svt, GRFEVAL grfeval, MATRIX3 *pmat, VECTOR *pw)
{
    return;
}

void EvaluateAcrEul(ACR *pacr, ALO *palo, float t, float svt, GRFEVAL grfeval, VECTOR *peul, VECTOR *pdeul)
{
    return;
}

void GetAcrTimes(ACR *pacr, int *pct, float **pat)
{
    *pct = 0;
    if (pat)
    {
        *pat = (float *)nullptr;
    }
}

void EvaluateAcs(ACS *pacs, ALO *palo, float t, GRFEVAL grfeval, MATRIX3 *pmat)
{
    return;
}

void GetAcsTimes(ACS *pacs, int *pct, float **pat)
{
    *pct = 0;
    if (pat)
    {
        *pat = (float *)nullptr;
    }
}

void EvaluateAcg(ACG *pacg, ALO *palo, float t, float svt, GRFEVAL grfeval, float *pg, float *pdg)
{
    return;
}

void GetAcgTimes(ACG *pacg, int *pct, float **pat)
{
    *pct = 0;
    if (pat)
    {
        *pat = (float *)nullptr;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/ac", LoadAcgbFromBrx__FP4ACGBP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/ac", EvaluateAcgb__FP4ACGBP3ALOffiPfT5);

INCLUDE_ASM("asm/nonmatchings/P2/ac", GetAcgbTimes__FP4ACGBPiPPf);

INCLUDE_ASM("asm/nonmatchings/P2/ac", LoadAcgbwFromBrx__FP5ACGBWP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/ac", EvaluateAcgbw__FP5ACGBWP3ALOffiPfT5);

INCLUDE_ASM("asm/nonmatchings/P2/ac", GetAcgbwTimes__FP5ACGBWPiPPf);

INCLUDE_ASM("asm/nonmatchings/P2/ac", EvaluateAcgl__FP4ACGLP3ALOffiPfT5);

INCLUDE_ASM("asm/nonmatchings/P2/ac", LoadAcglFromBrx__FP4ACGLP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/ac", GetAcglTimes__FP4ACGLPiPPf);

INCLUDE_ASM("asm/nonmatchings/P2/ac", EvaluateApacg__FPP3ACGP3ALOffiP6VECTORN25);

INCLUDE_ASM("asm/nonmatchings/P2/ac", LoadApacgFromBrx__FPP3ACGP6VECTORP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/ac", GetApacgTimes__FPP3ACGPiPPf);

INCLUDE_ASM("asm/nonmatchings/P2/ac", EvaluateAkvb__FiP3KVBffiP6VECTORT5);

INCLUDE_ASM("asm/nonmatchings/P2/ac", LoadAkvbFromBrx__FPiPP3KVBP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/ac", GetAkvbTimes__FiP3KVBPiPPf);

INCLUDE_ASM("asm/nonmatchings/P2/ac", EvaluateAcpc__FP4ACPCP3ALOffiP6VECTORT5);

INCLUDE_ASM("asm/nonmatchings/P2/ac", LoadAcpcFromBrx__FP4ACPCP18CBinaryInputStream);

void GetAcpcTimes(ACPC *pacpc, int *pct, float **pat)
{
    GetApacgTimes(&STRUCT_OFFSET(pacpc, 0x20, ACG *), pct, pat); // pacpc->apacg
}

INCLUDE_ASM("asm/nonmatchings/P2/ac", EvaluateAcpb__FP4ACPBP3ALOffiP6VECTORT5);

INCLUDE_ASM("asm/nonmatchings/P2/ac", LoadAcpbFromBrx__FP4ACPBP18CBinaryInputStream);

void GetAcpbTimes(ACPB *pacpb, int *pct, float **pat)
{
    // pacpb->ckvb, pacpb->akvb
    GetAkvbTimes(STRUCT_OFFSET(pacpb, 0xc, int), STRUCT_OFFSET(pacpb, 0x10, KVB *), pct, pat);
}

INCLUDE_ASM("asm/nonmatchings/P2/ac", EvaluateAcrc__FP4ACRCP3ALOffiP7MATRIX3P6VECTOR);

void EvaluateAcrcEul(ACRC *pacrc, ALO *palo, float t, float svt, GRFEVAL grfeval, VECTOR *peul, VECTOR *pdeul)
{
    // pacrc->apacg, pacrc->eulDefault
    EvaluateApacg(&STRUCT_OFFSET(pacrc, 0x20, ACG *), palo, t, svt, grfeval, &STRUCT_OFFSET(pacrc, 0x10, VECTOR), peul, pdeul);
}

INCLUDE_ASM("asm/nonmatchings/P2/ac", LoadAcrcFromBrx__FP4ACRCP18CBinaryInputStream);

void GetAcrcTimes(ACRC *pacrc, int *pct, float **pat)
{
    // pacrc->apacg
    GetApacgTimes(&STRUCT_OFFSET(pacrc, 0x20, ACG *), pct, pat);
}

INCLUDE_ASM("asm/nonmatchings/P2/ac", EvaluateAcrb__FP4ACRBP3ALOffiP7MATRIX3P6VECTOR);

void EvaluateAcrbEul(ACRB *pacrb, ALO *palo, float t, float svt, GRFEVAL grfeval, VECTOR *peul, VECTOR *pdeul)
{
    // pacrb->ckvb, pacrb->akvb 
    EvaluateAkvb(STRUCT_OFFSET(pacrb, 0xc, int), STRUCT_OFFSET(pacrb, 0x10, KVB *), t, svt, grfeval, peul, pdeul);
}

INCLUDE_ASM("asm/nonmatchings/P2/ac", LoadAcrbFromBrx__FP4ACRBP18CBinaryInputStream);

void GetAcrbTimes(ACRB *pacrb, int *pct, float **pat)
{
    // pacrb->ckvb, pacrb->akvb
    GetAkvbTimes(STRUCT_OFFSET(pacrb, 0xc, int), STRUCT_OFFSET(pacrb, 0x10, KVB *), pct, pat);
}

INCLUDE_ASM("asm/nonmatchings/P2/ac", EvaluateAcsc__FP4ACSCP3ALOfiP7MATRIX3);

void LoadAcscFromBrx(ACSC *pacsc, CBinaryInputStream *pbis)
{
    // pacsc->apacg, pacsc->vecDefault
    LoadApacgFromBrx(&STRUCT_OFFSET(pacsc, 0x20, ACG *), &STRUCT_OFFSET(pacsc, 0x10, VECTOR), pbis);
}

void GetAcscTimes(ACSC *pacsc, int *pct, float **pat)
{
    // pacsc->apacg
    GetApacgTimes(&STRUCT_OFFSET(pacsc, 0x20, ACG *), pct, pat);
}

INCLUDE_ASM("asm/nonmatchings/P2/ac", EvaluateAcsb__FP4ACSBP3ALOfiP7MATRIX3);

void LoadAcsbFromBrx(ACSB *pacsb, CBinaryInputStream *pbis)
{
    // pacsb->ckvb, pacsb->akvb
    LoadAkvbFromBrx(&STRUCT_OFFSET(pacsb, 0x08, int), &STRUCT_OFFSET(pacsb, 0x0c, KVB *), pbis);
}

void GetAcsbTimes(ACSB *pacsb, int *pct, float **pat)
{
    // pacsb->ckvb, pacsb->akvb 
    GetAkvbTimes(STRUCT_OFFSET(pacsb, 0x08, int), STRUCT_OFFSET(pacsb, 0x0c, KVB *), pct, pat);
}

INCLUDE_ASM("asm/nonmatchings/P2/ac", EvaluateAcpbl__FP5ACPBLP3ALOffiP6VECTORT5);

INCLUDE_ASM("asm/nonmatchings/P2/ac", EvaluateAcrbl__FP5ACRBLP3ALOffiP7MATRIX3P6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/ac", EvaluateAcgblt__FP6ACGBLTP3ALOffiPfT5);

INCLUDE_ASM("asm/nonmatchings/P2/ac", EvaluateAcgblp__FP6ACGBLPP3ALOffiPfT5);

INCLUDE_ASM("asm/nonmatchings/P2/ac", PacpNew__F4ACVK);

INCLUDE_ASM("asm/nonmatchings/P2/ac", PacrNew__F4ACVK);

INCLUDE_ASM("asm/nonmatchings/P2/ac", PacsNew__F4ACVK);

INCLUDE_ASM("asm/nonmatchings/P2/ac", PacgNew__F4ACGK);
