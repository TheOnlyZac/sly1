#include <gomer.h>

#define PI 3.1415927f

void InitGomer(GOMER *pgomer)
{
    InitStepguard(pgomer);
    STRUCT_OFFSET(pgomer, 0xC20, float) = 1000.0f;
    STRUCT_OFFSET(pgomer, 0xC24, float) = 1500.0f;
    STRUCT_OFFSET(pgomer, 0xC28, float) = PI / 4.0f;
    STRUCT_OFFSET(pgomer, 0xC2C, float) = PI;
    STRUCT_OFFSET(pgomer, 0xC10, float) = 2000.0f;
    STRUCT_OFFSET(pgomer, 0xC30, int) = -1;
    STRUCT_OFFSET(pgomer, 0xC14, float) = 300.0f;
    STRUCT_OFFSET(pgomer, 0xC18, int) = -1;
    STRUCT_OFFSET(pgomer, 0x73C, float) = 300.0f;
    STRUCT_OFFSET(pgomer, 0x738, int) = 0;
    STRUCT_OFFSET(pgomer, 0x74C, float) = PI / 3.0f;
}

INCLUDE_ASM("asm/nonmatchings/P2/gomer", PostGomerLoad__FP5GOMER);

INCLUDE_ASM("asm/nonmatchings/P2/gomer", FUN_00167ef0);

INCLUDE_ASM("asm/nonmatchings/P2/gomer", FDetectGomer__FP5GOMER);
