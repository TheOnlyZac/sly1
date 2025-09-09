#include <rchm.h>

INCLUDE_ASM(const s32, "P2/rchm", InitRchm__FP4RCHM);

INCLUDE_ASM(const s32, "P2/rchm", LoadRchmFromBrx__FP4RCHMP18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/rchm", PostRchmLoad__FP4RCHM);

INCLUDE_ASM(const s32, "P2/rchm", ReblendRchm__FP4RCHMP3TWRP6VECTOR);

INCLUDE_ASM(const s32, "P2/rchm", BuildRchmCoefficients__FP4RCHMfffPf);

INCLUDE_ASM(const s32, "P2/rchm", ConvertRchmIposToRclIoLhub__FP4RCHMiPfN22);

INCLUDE_ASM(const s32, "P2/rchm", SetRchmNaturalCoefficients__FP4RCHMfff);

INCLUDE_ASM(const s32, "P2/rchm", SetRchmCenterCoefficients__FP4RCHMfff);

INCLUDE_ASM(const s32, "P2/rchm", PredictRchmTargetPos__FP4RCHMP6TARGETfP6VECTOR);

INCLUDE_ASM(const s32, "P2/rchm", PredictRchmTargetLocalPos__FP4RCHMP6TARGETfP6VECTOR);

INCLUDE_ASM(const s32, "P2/rchm", PtwrMapRchmSafe__FP4RCHMP3BSPP6VECTOR);

INCLUDE_ASM(const s32, "P2/rchm", FindRchmClosestPoint__FP4RCHMP6VECTORT1PP3TWRPf);

INCLUDE_ASM(const s32, "P2/rchm", TrackJtTarget__FP2JTP4RCHMP6TARGET);

INCLUDE_ASM(const s32, "P2/rchm", TrackJtPipe__FP2JTP4RCHMP4PIPEPf);
