/**
 * @file murray.h
 *
 * @brief "The Murray".
 */
#ifndef MURRAY_H
#define MURRAY_H

#include "common.h"
#include <stepguard.h>
#include <turret.h>
#include <xform.h>

// Forward.
struct WKR;

/**
 * @brief Murray.
 * @todo Implement the struct.
 */
struct MURRAY : public STEPGUARD
{
    // ...
};

void InitMurray(MURRAY *pmurray);

void PostMurrayLoad(MURRAY *pmurray);

void OnMurrayEnteringSgs(MURRAY *pmurray, SGS sgsPrev, ASEG *pasegOverride);

void OnMurrayExitingSgs(MURRAY *pmurray, SGS sgs);

void UpdateMurrayGoal(MURRAY *pmurray, int fEnter);

void UpdateMurraySgs(MURRAY *pmurray);

int FAbsorbMurrayWkr(MURRAY *pmurray, WKR *pwkr);

int FDetectMurray(MURRAY *pmurray);

/**
 * @brief Always returns false and never gets called anywhere.
 */
int FCanMurrayAttack(MURRAY *pmurray);

void AddMurrayEnemy(MURRAY *pmurray, ALO *paloEnemy);

void SetMurrayPursueXfm(MURRAY *pmurray, XFM *pxfm);

void SetMurrayPatrolXfm(MURRAY *pmurray, XFM *pxfm);

void CollectMurrayPrize(MURRAY *pmurray, PCK pck, ALO *paloOther);

#endif // MURRAY_H
