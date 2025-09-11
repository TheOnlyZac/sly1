#include <rail.h>

extern float D_0024C8C4;

void InitRail(RAIL *prail)
{
    InitLo(prail);
    STRUCT_OFFSET(prail, 0x4c, float) = D_0024C8C4; // prail->rdvGravity
    STRUCT_OFFSET(prail, 0x54, int) = -1; // prail->fSlippery
}

INCLUDE_ASM("asm/nonmatchings/P2/rail", OnRailAdd__FP4RAIL);

INCLUDE_ASM("asm/nonmatchings/P2/rail", OnRailRemove__FP4RAIL);

INCLUDE_ASM("asm/nonmatchings/P2/rail", PostLoadRail__FP4RAIL);

INCLUDE_ASM("asm/nonmatchings/P2/rail", CloneRail__FP4RAILT0);
