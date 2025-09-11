/**
 * @file flash.h
 *
 * @brief Flash (might be flash animation, or literal screen flashes).
 */
#ifndef FLASH_H
#define FLASH_H

#include "common.h"
#include <mat.h>
#include <sm.h>
#include <cm.h>

/**
 * @brief Unknown (render options?).
 */
struct RO
{
    MATRIX4 mat;
    float uAlpha;
    float uAlphaCelBorder;
    undefined4 unk0;
    undefined4 unk1;
};

/**
 * @class FLASHLIGHT
 * @brief Flashlight guard's flashlight (maybe reused for spotlights?).
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

/**
 * @brief Initializes the given flashlight.
 *
 * @param pflash Flash to initialize.
 */
void InitFlash(FLASH *pflash);

/**
 * @brief Loads a flashlight from the given binary input stream.
 *
 * @param pflash Where to load the flash.
 * @param pbis Binary input stream.
 */
void LoadFlashFromBrx(FLASH *pflash, CBinaryInputStream *pbis);

/**
 * @brief Updates the given flashlight.
 *
 * @param pflash Flash to update.
 * @param dt Delta time.
 */
void UpdateFlash(FLASH *pflash, float dt);

/**
 * @brief Renders the given flashlight.
 *
 * @param pflash Flash to render.
 * @param pcm Camera to render from.
 * @param pro Render options(?).
 */
void RenderFlashSelf(FLASH *pflash, CM *pcm, RO *pro);

int FPosFlashWithin(FLASH *pflash, VECTOR *ppos);

#endif // FLASH_H
