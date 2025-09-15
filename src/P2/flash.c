#include <flash.h>
#include <clock.h>

extern CLOCK g_clock;

/**
 * @todo 88.42% matched
 * https://decomp.me/scratch/rIdzw
 */
INCLUDE_ASM("asm/nonmatchings/P2/flash", InitFlash__FP5FLASH);
#ifdef SKIP_ASM
void InitFlash(FLASH *pflash)
{
    InitAlo(pflash);

    float fOne   = 1.0f;
    float fSmall = 0.2f;
    float fTiny  = 0.1f;

    float* p = (float*)((char*)pflash + 0x2e0);

    pflash->gScaleTarget = fOne;
    pflash->gScaleCur    = fOne;
    p[0] = fOne;   // smpScale.svSlow (0x2e0)
    p[1] = fSmall; // smpScale.dtFast+4 (0x2e4)
    p[2] = fTiny;  // smpScale.dtFast (0x2e8)
}
#endif // SKIP_ASM

INCLUDE_ASM("asm/nonmatchings/P2/flash", LoadFlashFromBrx__FP5FLASHP18CBinaryInputStream);

void UpdateFlash(FLASH *pflash, float dt)
{
    UpdateAlo(pflash, dt);
    pflash->gScaleCur = GSmooth(pflash->gScaleCur, pflash->gScaleTarget, g_clock.dt, &pflash->smpScale, 0);
}

INCLUDE_ASM("asm/nonmatchings/P2/flash", RenderFlashSelf__FP5FLASHP2CMP2RO);

INCLUDE_ASM("asm/nonmatchings/P2/flash", FPosFlashWithin__FP5FLASHP6VECTOR);
