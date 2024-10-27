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
 * @brief User interface state.
 */
enum UIS
{
    UIS_Nil = -1,
    UIS_Splash = 0,
    UIS_Attract = 1,
    UIS_Playing = 2,
    UIS_Pausing = 3,
    UIS_Paused = 4,
    UIS_Unpausing = 5,
    UIS_WorldMap = 6,
    //todo What is 7?
    UIS_Wiping = 8,
    UIS_Max = 9
};

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
