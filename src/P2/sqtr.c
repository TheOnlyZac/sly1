#include <sqtr.h>

extern "C" void FUN_001c29e8(SQTRM *psqtrm)
{
    STRUCT_OFFSET(psqtrm, 0xc, int) = 0;
    STRUCT_OFFSET(psqtrm, 0x8, int) = 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/sqtr", UpdateSqtrm__FP5SQTRMP6VECTORP7MATRIX3ff);

INCLUDE_ASM("asm/nonmatchings/P2/sqtr", RenderSqtrm__FP5SQTRMP2CM);

INCLUDE_ASM("asm/nonmatchings/P2/sqtr", DrawSqtrm__FP3RPL);
