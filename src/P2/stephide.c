#include <stephide.h>

INCLUDE_ASM("asm/nonmatchings/P2/stephide", JtbsChooseJtHide__FP2JTP2LOP4JTHK);

INCLUDE_ASM("asm/nonmatchings/P2/stephide", MeasureJtJumpToTarget__FP2JTP6VECTORP3ALOT1T1PfT5T1T1);

INCLUDE_ASM("asm/nonmatchings/P2/stephide", GetJtRailLanding__FP2JTP4RAILfP6VECTORT3);

float GMeasureJumpRail(MJR *pmjr, float u)
{
    VECTOR posLanding;
    VECTOR vLanding;
    float gInteg;

    GetJtRailLanding(STRUCT_OFFSET(pmjr, 0x0, JT *),
                     STRUCT_OFFSET(pmjr, 0x4, RAIL *),
                     u, &posLanding, &vLanding);

    MeasureJtJumpToTarget(STRUCT_OFFSET(pmjr, 0x0, JT *),
                          (VECTOR *)((uint8_t *)pmjr + 0x10),
                          STRUCT_OFFSET(STRUCT_OFFSET(pmjr, 0x4, RAIL *), 0x18, ALO *),
                          &posLanding, &vLanding, 0, &gInteg, 0, 0);

    return gInteg;
}

INCLUDE_ASM("asm/nonmatchings/P2/stephide", FUN_001cea58);

INCLUDE_ASM("asm/nonmatchings/P2/stephide", GMeasureJumpHshape__FP3MJHf);

INCLUDE_ASM("asm/nonmatchings/P2/stephide", FUN_001ceb18);

INCLUDE_ASM("asm/nonmatchings/P2/stephide", FUN_001cedf8);

INCLUDE_ASM("asm/nonmatchings/P2/stephide", FUN_001cee30);

INCLUDE_ASM("asm/nonmatchings/P2/stephide", FUN_001ceec8);

extern float D_00274E3C;

extern "C" float FUN_001cf138(JT *pjt, int n, float a, float b)
{
    a = a + b;
    if (n == STRUCT_OFFSET(pjt, 0x2bdc, int))
        a = a + D_00274E3C;
    return a;
}

INCLUDE_ASM("asm/nonmatchings/P2/stephide", FUN_001cf158);

INCLUDE_ASM("asm/nonmatchings/P2/stephide", UpdateJtActiveHide__FP2JTP3JOY);

INCLUDE_ASM("asm/nonmatchings/P2/stephide", MatchJtXmgRail__FP2JTP3XMGP6ACTADJ);

INCLUDE_ASM("asm/nonmatchings/P2/stephide", UpdateJtHide__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/stephide", UpdateJtInternalXpsHide__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/stephide", SetJtHfdk__FP2JT4HFDK);

INCLUDE_ASM("asm/nonmatchings/P2/stephide", ResetJtDynamicTunnel__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/stephide", PresetJtAccelHide__FP2JT);

INCLUDE_ASM("asm/nonmatchings/P2/stephide", FUN_001d1478);
