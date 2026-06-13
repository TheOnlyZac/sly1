#include <fly.h>

INCLUDE_ASM("asm/nonmatchings/P2/fly", InitFly__FP3FLY);

INCLUDE_ASM("asm/nonmatchings/P2/fly", LoadFlyFromBrx__FP3FLYP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/fly", CloneFly__FP3FLYT0);

INCLUDE_ASM("asm/nonmatchings/P2/fly", FreezeFly__FP3FLYi);

void PostFlyLoad(FLY *pfly)
{
    extern SNIP D_002621E0;

    SnipAloObjects((ALO *)pfly, 2, &D_002621E0);

    if (STRUCT_OFFSET(pfly, 0x550, int) == 1)
    {
        STRUCT_OFFSET(pfly, 0x688, float) = g_clock.t +
            GRandInRange(STRUCT_OFFSET(pfly, 0x63c, float), STRUCT_OFFSET(pfly, 0x640, float));
        STRUCT_OFFSET(pfly, 0x680, float) = g_clock.t +
            GRandInRange(STRUCT_OFFSET(pfly, 0x670, float), STRUCT_OFFSET(pfly, 0x674, float));
    }

    SetFlyFlys(pfly, (FLYS)STRUCT_OFFSET(pfly, 0x560, int));
    PostAloLoad((ALO *)pfly);
    STRUCT_OFFSET(pfly, 0x64c, float) =
        STRUCT_OFFSET(pfly, 0x3cc, float) + STRUCT_OFFSET(pfly, 0x3cc, float);
}

INCLUDE_ASM("asm/nonmatchings/P2/fly", PresetFlyAccel__FP3FLYf);

INCLUDE_ASM("asm/nonmatchings/P2/fly", UpdateFly__FP3FLYf);

INCLUDE_ASM("asm/nonmatchings/P2/fly", RenderFlySelf__FP3FLYP2CMP2RO);

INCLUDE_ASM("asm/nonmatchings/P2/fly", FAbsorbFlyWkr__FP3FLYP3WKR);

INCLUDE_ASM("asm/nonmatchings/P2/fly", SetFlyFlys__FP3FLY4FLYS);

INCLUDE_ASM("asm/nonmatchings/P2/fly", EmitFlyDroppings__FP3FLY);

INCLUDE_ASM("asm/nonmatchings/P2/fly", FFindFlyClosestLandingPos__FP3FLYP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/fly", FlysAttemptedFlyLanding__FP3FLY);

INCLUDE_ASM("asm/nonmatchings/P2/fly", FShouldFlyFlee__FP3FLY);

INCLUDE_ASM("asm/nonmatchings/P2/fly", FFilterFly__FPvP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/fly", FCheckFlyOpenSpaceBelow__FP3FLY);
