#include <flash.h>
#include <clock.h>
#include <tn.h>

// NOTE: Could also belong to P2/find.c.
INCLUDE_ASM("asm/nonmatchings/P2/flash", junk_0015A8B0);

void InitFlash(FLASH *pflash)
{
    InitAlo(pflash);

    pflash->gScaleTarget = 1.0f;
    pflash->gScaleCur = 1.0f;

    SMP *psmpScale = &pflash->smpScale;
    psmpScale->svFast = 1.0f;
    psmpScale->svSlow = 0.2f;
    psmpScale->dtFast = 0.1f;
}

void LoadFlashFromBrx(FLASH *pflash, CBinaryInputStream *pbis)
{
    LoadAloFromBrx(pflash, pbis);
    LoadTbspFromBrx(pbis, &pflash->ctsurf, &pflash->atsurf, &pflash->ctbsp, &pflash->atbsp);
}

void UpdateFlash(FLASH *pflash, float dt)
{
    UpdateAlo(pflash, dt);
    pflash->gScaleCur = GSmooth(pflash->gScaleCur, pflash->gScaleTarget, g_clock.dt, &pflash->smpScale, 0);
}

INCLUDE_ASM("asm/nonmatchings/P2/flash", RenderFlashSelf__FP5FLASHP2CMP2RO);

INCLUDE_ASM("asm/nonmatchings/P2/flash", FPosFlashWithin__FP5FLASHP6VECTOR);
