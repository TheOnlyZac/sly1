/**
 * @file flash.h
 */
#ifndef FLASH_H
#define FLASH_H

#include "common.h"
#include <mat.h>
#include <sm.h>
#include <shd.h>
#include <cm.h>

struct RO
{
    MATRIX4 mat;
    float uAlpha;
    float uAlphaCelBorder;
    undefined4 unk0;
    undefined4 unk1;
};

/**
 * @brief Flash.
 */
struct FLASH : public ALO
{
    int ctsurf;
    TSURF *atsurf;
    int ctbsp;
    TBSP *atbsp;
    SMP smpScale;
    float gScaleCur;
    float gScaleTarget;
    undefined4 unk0;
    undefined4 unk1;
    undefined4 unk2;
};

void InitFlash(FLASH *pflash);

void LoadFlashFromBrx(FLASH *pflash, CBinaryInputStream *pbis);

void UpdateFlash(FLASH *pflash, float dt);

void RenderFlashSelf(FLASH *pflash, CM *pcm, RO *pro);

int FPosFlashWithin(FLASH *pflash, VECTOR *ppos);

#endif // FLASH_H
