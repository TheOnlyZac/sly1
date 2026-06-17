#include <fly.h>
#include <memory.h>
#include <clip.h>

INCLUDE_ASM("asm/nonmatchings/P2/fly", InitFly__FP3FLY);

INCLUDE_ASM("asm/nonmatchings/P2/fly", LoadFlyFromBrx__FP3FLYP18CBinaryInputStream);

void CloneFly(FLY *pfly, FLY *pflyBase)
{
    uint64_t tmp = STRUCT_OFFSET(pfly, 0x5dc, uint64_t);
    CloneSo((SO *)pfly, (SO *)pflyBase);
    STRUCT_OFFSET(pfly, 0x5dc, uint64_t) = tmp;

    if (STRUCT_OFFSET(pfly, 0x550, int) == 0)
    {
        StartSound((SFXID)0x41, (AMB **)((char *)pfly + 0x5e4), (ALO *)pfly, 0,
                   700.0f, 10.0f, 1.0f, 0.0f, 0.0f, 0, 0);
    }
    else
    {
        if (FFindDlEntry((DL *)((char *)pfly->psw + 0x1c48), pfly))
            RemoveDlEntry((DL *)((char *)pfly->psw + 0x1c48), pfly);
    }
}

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

int FCheckFlyOpenSpaceBelow(FLY *pfly)
{
    if (g_clock.t - STRUCT_OFFSET(pfly, 0x66c, float) < 0.05f)
        return 0;

    int cpso;
    SO **apso;
    VECTOR *ppos = &STRUCT_OFFSET(pfly, 0x140, VECTOR);

    InitStackImpl();
    IntersectSwBoundingSphere(STRUCT_OFFSET(pfly, 0x14, SW *), NULL, ppos,
        STRUCT_OFFSET(pfly, 0x64c, float), (PFNFILTER)FFilterFly, pfly, &cpso, &apso);

    qword qwBelow = STRUCT_OFFSET(pfly, 0x140, qword);
    VECTOR *pposBelow = (VECTOR *)&qwBelow;
    float zBelow = pposBelow->z - STRUCT_OFFSET(pfly, 0x64c, float);
    pposBelow->z = zBelow;
    SO *pso = PsoHitTestLineObjects(0, ppos, pposBelow, cpso, apso, NULL);
    FreeStackImpl();

    STRUCT_OFFSET(pfly, 0x66c, float) = g_clock.t;
    return pso == NULL;
}
