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
 * @class MISSILE
 * @brief Missile (maybe the ones fired by smartguards?).
 * @todo Implement the struct.
 */
struct MISSILE : public BOMB
{
    // ...
};

/**
 * @class ACCEL_MISSILE
 * @brief Accelerating missile.
 * @todo Implement the struct.
 */
struct ACCMISS : public MISSILE
{
    // ...
};

/**
 * @class TARGET_MISSILE
 * @brief Target missile.
 * @todo Implement the struct.
 */
struct TARMISS : public MISSILE
{
    // ...
};

/**
 * @class SPLINE_MISSILE
 * @brief Spline missile.
 * @todo Implement the struct.
 */
struct SPLMISS : public MISSILE
{
    // ...
};

/**
 * @class GROUND_MISSILE
 * @brief Ground missile.
 * @todo Implement the struct.
 */
struct GROUNDMISS : public MISSILE
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
