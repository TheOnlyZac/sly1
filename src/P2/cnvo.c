#include <cnvo.h>

INCLUDE_ASM("asm/nonmatchings/P2/cnvo", InitCnvo__FP4CNVO);

INCLUDE_ASM("asm/nonmatchings/P2/cnvo", LoadCnvoFromBrx__FP4CNVOP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/cnvo", PostCnvoLoad__FP4CNVO);

INCLUDE_ASM("asm/nonmatchings/P2/cnvo", AdjustCnvoXpVelocity__FP4CNVOP2XPi);

INCLUDE_ASM("asm/nonmatchings/P2/cnvo", SetCnvoBeltSpeed__FP4CNVOf);

INCLUDE_ASM("asm/nonmatchings/P2/cnvo", MatchCnvoScrollerToBeltSpeed__FP4CNVO);
