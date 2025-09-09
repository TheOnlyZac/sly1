/**
 * @file missile.h
 */
#ifndef MISSILE_H
#define MISSILE_H

#include "common.h"
#include <bomb.h>
#include <bis.h>
#include <vec.h>
#include <alo.h>
#include <cm.h>

// Forward.
struct RO;

/**
 * @brief Missile.
 * @todo Implement the struct.
 */
struct MISSILE : public BOMB
{
    // ...
};

/**
 * @brief (?) missile.
 * @todo Implement the struct.
 */
struct ACCMISS : public MISSILE
{
    // ...
};

/**
 * @brief (?) missile.
 * @todo Implement the struct.
 */
struct SPLMISS : public MISSILE
{
    // ...
};

void InitMissile(MISSILE *pmissile);

void LoadMissileFromBrx(MISSILE *pmissile, CBinaryInputStream *pbis);

void OnMissileRemove(MISSILE *pmissile);

void ProjectMissileTransform(MISSILE *pmissile, float dt, int fParentDirty);

void FireMissile(MISSILE *pmissile, ALO *paloTarget, VECTOR *pposTargetLocal);

void RenderMissileAll(MISSILE *pmissile, CM *pcm, RO *pro);


void InitAccmiss(ACCMISS *paccmiss);

void FireAccmiss(ACCMISS *paccmiss, ALO *paloTarget, VECTOR *pposTarget);

void PresetAccmissAccel(ACCMISS *paccmiss, float dt);


void FireSplmiss(SPLMISS *psplmiss, ALO *paloTarget, VECTOR *pposTargetLocal);

void ProjectSplmissTransform(SPLMISS *psplmiss, float dt, int fParentDirty);

#endif // MISSILE_H
