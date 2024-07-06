#include <flash.h>

INCLUDE_ASM(const s32, "P2/flash", InitFlash__FP5FLASH);

INCLUDE_ASM(const s32, "P2/flash", LoadFlashFromBrx__FP5FLASHP18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/flash", UpdateFlash__FP5FLASHf);

INCLUDE_ASM(const s32, "P2/flash", RenderFlashSelf__FP5FLASHP2CMP2RO);

INCLUDE_ASM(const s32, "P2/flash", FPosFlashWithin__FP5FLASHP6VECTOR);
