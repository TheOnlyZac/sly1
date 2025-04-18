/**
 * @file ui.h
 *
 * @brief User interface.
 */
#ifndef UI_H
#define UI_H

#include "common.h"
#include <screen.h>
#include <joy.h>

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
void DrawUi();
void RenderUi();
void ResetUi(UI *pui);
void SetUiUis(UI *pui, UIS uis);
void SetUiUPause(UI *pui, float rPause);
// ...more functions...

extern UI g_ui; // Global UI object

#endif // UI_H
