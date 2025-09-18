#include <rat.h>
#include <util.h>
#include <sw.h>

void InitRat(RAT *prat)
{
    InitSo(prat);
    STRUCT_OFFSET(prat, 0x608, LM).gMin = 0.5f; // prat->lmDtStop.gMin
    STRUCT_OFFSET(prat, 0x608, LM).gMax = 1.0f; // prat->lmDtStop.gMax
    STRUCT_OFFSET(prat, 0x55c, float) = GRandGaussian(g_clock.t + 3.0f, 1.0f, 2.5f); // prat->tRatSqueak
    STRUCT_OFFSET(prat, 0x664, int) = -1; // prat->ccoin
}

INCLUDE_ASM("asm/nonmatchings/P2/rat", LoadRatFromBrx__FP3RATP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/rat", PostRatLoad__FP3RAT);

void OnRatAdd(RAT *prat)
{
    OnSoAdd(prat);
    AppendDlEntry(&prat->psw->dlRat, prat);
}

void OnRatRemove(RAT *prat)
{
    OnSoRemove(prat);
    RemoveDlEntry(&prat->psw->dlRat, prat);
}

INCLUDE_ASM("asm/nonmatchings/P2/rat", CloneRat__FP3RATT0);

INCLUDE_ASM("asm/nonmatchings/P2/rat", PresetRatAccel__FP3RATf);

INCLUDE_ASM("asm/nonmatchings/P2/rat", UpdateRat__FP3RATf);

INCLUDE_ASM("asm/nonmatchings/P2/rat", AdjustRatNewXp__FP3RATP2XPi);

INCLUDE_ASM("asm/nonmatchings/P2/rat", AdjustRatXpVelocity__FP3RATP2XPi);

INCLUDE_ASM("asm/nonmatchings/P2/rat", RenderRatAll__FP3RATP2CMP2RO);

INCLUDE_ASM("asm/nonmatchings/P2/rat", FAbsorbRatWkr__FP3RATP3WKR);

INCLUDE_ASM("asm/nonmatchings/P2/rat", ChooseRatFleeTarget__FP3RAT);

INCLUDE_ASM("asm/nonmatchings/P2/rat", HideRat__FP3RATi);

INCLUDE_ASM("asm/nonmatchings/P2/rat", SetRatRats__FP3RAT4RATS);

INCLUDE_ASM("asm/nonmatchings/P2/rat", OnRatholeAdd__FP7RATHOLE);

INCLUDE_ASM("asm/nonmatchings/P2/rat", OnRatholeRemove__FP7RATHOLE);
