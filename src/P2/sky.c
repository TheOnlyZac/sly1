#include <sky.h>

void PostSkyLoad(SKY *psky)
{
	PostAloLoad(psky);
	STRUCT_OFFSET(psky, 0x2c8, ulong) &= 0xfffffcffffffffff;
	STRUCT_OFFSET(psky, 0x2c8, ulong) |= 0x10000000000;
}

INCLUDE_ASM("asm/nonmatchings/P2/sky", UpdateSky__FP3SKYf);
