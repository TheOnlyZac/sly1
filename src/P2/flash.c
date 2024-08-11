#include <flash.h>
#include <clock.h>

extern CLOCK g_clock;

INCLUDE_ASM(const s32, "P2/flash", InitFlash__FP5FLASH);

INCLUDE_ASM(const s32, "P2/flash", LoadFlashFromBrx__FP5FLASHP18CBinaryInputStream);

void UpdateFlash(FLASH *pflash,float dt)
{
    UpdateAlo((ALO *)pflash,dt);
    pflash->gScaleCur = GSmooth(pflash->gScaleCur, pflash->gScaleTarget, g_clock.dt, &pflash->smpScale, 0);
}

INCLUDE_ASM(const s32, "P2/flash", RenderFlashSelf__FP5FLASHP2CMP2RO);

INCLUDE_ASM(const s32, "P2/flash", FPosFlashWithin__FP5FLASHP6VECTOR);
