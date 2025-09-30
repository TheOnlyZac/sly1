#include <sw.h>

void InitSwDlHash(SW *psw)
{
    DL *pdl = psw->adlHash;

    for (uint i = 0; i < 512; i++)
    {
        InitDl(pdl, sizeof(DL));
        pdl++;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/sw", InitSw__FP2SW);

INCLUDE_ASM("asm/nonmatchings/P2/sw", DeleteSw__FP2SW);

INCLUDE_ASM("asm/nonmatchings/P2/sw", SetupBulkDataFromBrx__FiP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/sw", LoadBulkDataFromBrx__FP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/sw", SetSwGravity__FP2SWf);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dbac0);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dbae0);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dbb00);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FOverflowSwLo__FP2SWP2LOi);

INCLUDE_ASM("asm/nonmatchings/P2/sw", PxaAllocSw__FP2SW);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FreeSwXaList__FP2SWP2XA);

INCLUDE_ASM("asm/nonmatchings/P2/sw", PmqAllocSw__FP2SW);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FreeSwMqList__FP2SWP2MQ);

INCLUDE_ASM("asm/nonmatchings/P2/sw", EnsureSwCallback__FP2SWPFPv5MSGIDPv_vPv5MSGIDT2);

INCLUDE_ASM("asm/nonmatchings/P2/sw", PostSwCallback__FP2SWPFPv5MSGIDPv_vPv5MSGIDT2);

INCLUDE_ASM("asm/nonmatchings/P2/sw", ClearSwCallbacks__FP2SWiPFPv5MSGIDPv_vPv5MSGIDT3);

INCLUDE_ASM("asm/nonmatchings/P2/sw", ProcessSwCallbacks__FP2SW);

INCLUDE_ASM("asm/nonmatchings/P2/sw", ProcessSwSpliceScheduledCallbacks__FP2SWf);

INCLUDE_ASM("asm/nonmatchings/P2/sw", PstsoAllocSw__FP2SW);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FreeSwStsoList__FP2SWP4STSO);

INCLUDE_ASM("asm/nonmatchings/P2/sw", AddSwProxySource__FP2SWP2LOi);

INCLUDE_ASM("asm/nonmatchings/P2/sw", PloGetSwProxySource__FP2SWi);

INCLUDE_ASM("asm/nonmatchings/P2/sw", IntersectSwBoundingBox__FP2SWP2SOP6VECTORT2PFPvP2SO_iPvPiPPP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/sw", IntersectSwBoundingSphere__FP2SWP2SOP6VECTORfPFPvP2SO_iPvPiPPP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/sw", RemoveOxa__FP3OXAPP3OXA);

INCLUDE_ASM("asm/nonmatchings/P2/sw", InitSwAoxa__FP2SW);

INCLUDE_ASM("asm/nonmatchings/P2/sw", AddOxa__FP3OXAPP3OXA);

INCLUDE_ASM("asm/nonmatchings/P2/sw", PoxaAllocSw__FP2SWP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FreeSwPoxa__FP2SWP3OXA);

INCLUDE_ASM("asm/nonmatchings/P2/sw", CreateSwDefaultLights__FP2SW);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dccc0);

INCLUDE_ASM("asm/nonmatchings/P2/sw", CreateSwPrizes__FP2SW);

INCLUDE_ASM("asm/nonmatchings/P2/sw", LoadSwFromBrx__FP2SWP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FClipLineHomogeneous__FP7VECTOR4);

INCLUDE_ASM("asm/nonmatchings/P2/sw", DrawLineWorld__FP6VECTORT0G4RGBAP2CMi);

INCLUDE_ASM("asm/nonmatchings/P2/sw", DrawAxesWorld__FP6VECTORP7MATRIX3fP2CMi);

INCLUDE_ASM("asm/nonmatchings/P2/sw", SetSwIllum__FP2SWf);

INCLUDE_ASM("asm/nonmatchings/P2/sw", SetSwIllumShadow__FP2SWf);

INCLUDE_ASM("asm/nonmatchings/P2/sw", SetSwExcitement__FP2SWf);

int FLevelSwVisited(SW *psw, WID wid)
{
    return GrflsFromWid(wid) & 1;
}

int FLevelSwPrimary(SW *psw, WID wid)
{
    return GrflsFromWid(wid) & 2;
}

int FLevelSwSecondary(SW *psw, WID wid)
{
    return GrflsFromWid(wid) & 4;
}

int FLevelSwTertiary(SW *psw, WID wid)
{
    return GrflsFromWid(wid) & 8;
}

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dd710);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dd758);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dd7a0);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dd7e8);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dd888);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dd8e8);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dd908);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dd928);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dd950);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dd9a0);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dd9c0);

INCLUDE_ASM("asm/nonmatchings/P2/sw", SetSwPlayerSuck__FP2SWf);

INCLUDE_ASM("asm/nonmatchings/P2/sw", GetSwPlayerSuck__FP2SWPf);

INCLUDE_ASM("asm/nonmatchings/P2/sw", IncrementSwHandsOff__FP2SW);

INCLUDE_ASM("asm/nonmatchings/P2/sw", DecrementSwHandsOff__FP2SW);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dda80);

INCLUDE_ASM("asm/nonmatchings/P2/sw", IsSwVagPlaying__FP2SWPi);

INCLUDE_ASM("asm/nonmatchings/P2/sw", SetSwDarken__FP2SWf);

INCLUDE_ASM("asm/nonmatchings/P2/sw", SetSwDarkenSmooth__FP2SWf);

INCLUDE_ASM("asm/nonmatchings/P2/sw", CancelSwDialogPlaying__FP2SW);
