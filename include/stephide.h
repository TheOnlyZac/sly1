/**
 * @file stephide.h
 */
#ifndef STEPHIDE_H
#define STEPHIDE_H

#include "common.h"
#include <jt.h>

// Forward.
struct MJR;
struct MJH;
struct XMG;
struct RAIL;
struct ACTADJ;

/**
 * @brief Unknown.
 */
enum HFDK
{
    HFDK_Nil = -1,
    HFDK_Match = 0,
    HFDK_Left = 1,
    HFDK_Right = 2,
    HFDK_Stand = 3,
    HFDK_Max = 4
};

JTBS JtbsChooseJtHide(JT *pjt, LO *ploForce, JTHK *pjthk);

void MeasureJtJumpToTarget(JT *pjt, VECTOR *pvJump, ALO *palo, VECTOR *pposTarget, VECTOR *pdvTarget, float *pdtJump, float *pgInteg, VECTOR *pposPredict, VECTOR *pvPredict);

void GetJtRailLanding(JT *pjt, RAIL *prail, float uRail, VECTOR *ppos, VECTOR *pv);

float GMeasureJumpRail(MJR *pmjr, float u);

float GMeasureJumpHshape(MJH *pmjh, float s);

// TODO: Add unknown functions here.

void UpdateJtActiveHide(JT *pjt, JOY *pjoy);

void MatchJtXmgRail(JT *pjt, XMG *pxmg, ACTADJ *pactadj);

void UpdateJtHide(JT *pjt);

void UpdateJtInternalXpsHide(JT *pjt);

void SetJtHfdk(JT *pjt, HFDK hfdk);

void ResetJtDynamicTunnel(JT *pjt);

void PresetJtAccelHide(JT *pjt);

#endif // STEPHIDE_H
