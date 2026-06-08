#include <rchm.h>
#include <clock.h>

void InitRchm(RCHM *prchm)
{
    InitLo(prchm);
    prchm->oidTouch = OID_Nil;
    prchm->oidHost = OID_Nil;
}

INCLUDE_ASM("asm/nonmatchings/P2/rchm", LoadRchmFromBrx__FP4RCHMP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/rchm", PostRchmLoad__FP4RCHM);

INCLUDE_ASM("asm/nonmatchings/P2/rchm", ReblendRchm__FP4RCHMP3TWRP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/rchm", BuildRchmCoefficients__FP4RCHMfffPf);

INCLUDE_ASM("asm/nonmatchings/P2/rchm", ConvertRchmIposToRclIoLhub__FP4RCHMiPfN22);

void SetRchmNaturalCoefficients(RCHM *prchm, float rcl, float io, float lhub)
{
    prchm->rclNatural = rcl;
    prchm->ioNatural = io;
    prchm->lhubNatural = lhub;
}

void SetRchmCenterCoefficients(RCHM *prchm, float rcl, float io, float lhub)
{
    prchm->fCenterSet = 1;
    prchm->rclNatural = rcl;
    prchm->ioNatural = io;
    prchm->lhubNatural = lhub;
}

INCLUDE_ASM("asm/nonmatchings/P2/rchm", PredictRchmTargetPos__FP4RCHMP6TARGETfP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/rchm", PredictRchmTargetLocalPos__FP4RCHMP6TARGETfP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/rchm", PtwrMapRchmSafe__FP4RCHMP3BSPP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/rchm", FindRchmClosestPoint__FP4RCHMP6VECTORT1PP3TWRPf);

void TrackJtTarget(JT *pjt, RCHM *prchm, TARGET *ptarget)
{
    VECTOR posLocal;
    VECTOR posClosest;
    TWR *ptwr;
    float s;
    float dt;

    if (ptarget == NULL)
        return;

    dt = STRUCT_OFFSET(pjt, 0x2424, float) - g_clock.t;
    if (dt < g_clock.dt)
        dt = g_clock.dt;

    PredictRchmTargetLocalPos(prchm, ptarget, dt, &posLocal);
    FindRchmClosestPoint(prchm, &posLocal, &posClosest, &ptwr, &s);
    ReblendRchm(prchm, ptwr, &posClosest);
}

void TrackJtPipe(JT *pjt, RCHM *prchm, PIPE *ppipe, float *psPipe)
{
    VECTOR posPipeLocal;
    VECTOR posOnPipe;
    VECTOR posWorld;
    VECTOR posLocal;
    TWR *ptwr;
    float s;

    ConvertAloPos(NULL, ppipe->paloParent, (VECTOR *)((uint8_t *)pjt + 0x140), &posPipeLocal);

    if (STRUCT_OFFSET(STRUCT_OFFSET(ppipe, 0x34, void *), 0x0, void **)[0xc] != NULL)
    {
        (*(void (**)(void *, float, VECTOR *, int, VECTOR *, int, int, float *))
            (STRUCT_OFFSET(STRUCT_OFFSET(ppipe, 0x34, void **), 0x0, void **) + 0xc))(
            STRUCT_OFFSET(ppipe, 0x34, void *), *psPipe, &posPipeLocal, 0, &posOnPipe, 0, 0, psPipe);
    }

    ConvertAloPos(ppipe->paloParent, (ALO *)pjt, &posOnPipe, &posWorld);
    FindRchmClosestPoint(prchm, &posWorld, &posLocal, &ptwr, &s);
    ReblendRchm(prchm, ptwr, &posLocal);
}
