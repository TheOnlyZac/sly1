#include <rchm.h>

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

INCLUDE_ASM("asm/nonmatchings/P2/rchm", TrackJtTarget__FP2JTP4RCHMP6TARGET);

INCLUDE_ASM("asm/nonmatchings/P2/rchm", TrackJtPipe__FP2JTP4RCHMP4PIPEPf);
