/**
 * @file ui.h
 *
 * @brief User interface.
 */
#ifndef UI_H
#define UI_H

#include "common.h"
#include <joy.h>

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
    // todo: What is 7?
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
    int tUis;
    BLOT *apblotActive;
    int cpblotActive;
    UIS uisPlaying;
    float rvolMusicPrepause;
    float rvolEffectsPrepause;
    int unk1;
    int unk2;
    int unk3;
    int unk4;
    int unk5;
    int unk6;
};

void StartupUi();

void InitUi(UI *pui);

void PostUiLoad(UI *pui);

void UpdateUi(UI *pui);

void PushUiActiveBlot(UI *pui, BLOT *pblot);

void PopUiActiveBlot(UI *pui);

/**
 * @brief Calls DrawBlots to draw the UI.
 */
void DrawUi();

/**
 * @brief Calls RenderBlots to render the UI.
 */
void RenderUi();

/**
 * @brief Resets the UI to its initial state.
 *
 * @param pui Pointer to UI struct
 */
void ResetUi(UI *pui);

/**
 * @brief Sets the UI state.
 *
 * @param pui Pointer to UI struct
 * @param uis UI state
 */
void SetUiUis(UI *pui, UIS uis);

/**
 * @brief Sets the UI pause state.
 *
 * @param pui Pointer to UI struct
 * @param rPause Pause state
 */
void SetUiUPause(UI *pui, float rPause);

// ...more functions...

extern UI g_ui; // Global UI object

#endif // UI_H
