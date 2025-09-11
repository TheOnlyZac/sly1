/**
 * @file wm.h
 *
 * @brief World map?
 */
#ifndef WM_H
#define WM_H

#include "common.h"
#include <flash.h>
#include <game.h>
#include <vec.h>
#include <joy.h>
#include <alo.h>
#include <cm.h>
#include <mq.h>

typedef int GRFDS;

/**
 * @brief World map state.
 */
enum WMS
{
    WMS_Nil = -1,
    WMS_Hidden = 0,
    WMS_Appearing = 1,
    WMS_Manual = 2,
    WMS_Warping = 3,
    WMS_Disappearing = 4,
    WMS_Max = 5
};

/**
 * @brief World map direction.
 */
enum WMD
{
    WMD_Nil = -1,
    WMD_Up = 0,
    WMD_Down = 1,
    WMD_Left = 2,
    WMD_Right = 3,
    WMD_Max = 4
};

/**
 * @brief World map something (?)
 * @todo Implement the struct.
 */
struct WMC
{
    // ...
};

/**
 * @class WORLD_MAP
 * @brief World map accessed from the hideout, by pressing Select, or Pause > View Map.
 * @todo Implement the struct.
 */
struct WM : public ALO
{
    // ...
};

void PostWmLoad(WM *pwm);

void BindWm(WM *pwm);

void RefreshWmMoveStats(WM *pwm, WORLDLEVEL worldlevel);

void ThrowWmDisplayState(WM *pwm, WORLDLEVEL worldlevel, int fReverse);

void CatchWmDisplayState(WM *pwm);

void UpdateWm(WM *pwm, float dt);

void RenderWmAll(WM *pwm, CM *pcm, RO *pro);

void HandleWmMessage(WM *pwm, MSGID msgid, void *pv);

/**
 * @brief Sets the WM state.
 *
 * @param pwm Pointer to the WM.
 * @param pwms Pointer to the WM state.
*/
void SetWmWms(WM* pwm, WMS wms);

void ShowWm(WM *pwm, WORLDLEVEL worldlevel, WMS wmsActive);

void HideWm(WM *pwm);

void MoveWm(WM *pwm, WMD wmd);

void GetWmWorldPosScreen(WM *pwm, WORLDLEVEL worldlevel, VECTOR *pposScreen);

void SetWmCursor(WM *pwm, WORLDLEVEL worldlevel);

void PostWmcLoad(WMC *pwmc);

void UpdateWmcActive(WMC *pwmc, JOY *pjoy);

void OnWmcActive(WMC *pwmc, int fActive);

void DrawWmFan(float xCenter, float yCenter, float sRadius, float rad, int cseg, RGBA *rgbaCenter, RGBA rgbaEdge, GRFDS grfds);

void DrawWmc(WMC *pwmc);

#endif // WM_H
