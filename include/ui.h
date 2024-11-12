/**
 * @file ui.h
 *
 * @brief User interface.
 */
#ifndef UI_H
#define UI_H

#include "common.h"
#include <screen.h>

/**
 * @brief User interface.
 *
 * @note Roughly based on May proto, may be inaccurate.
 */
struct UI
{
    UIS uis;
    float tUis;
    BLOT *apblotActive;
    int cpblotActive;
    UIS uisPlaying;
    float rvolMusicPrepause;
    float rvolEffectsPrepause;
};

#endif // UI_H
