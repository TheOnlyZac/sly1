/**
 * @file rwm.h
 */
#ifndef RWM_H
#define RWM_H

#include "common.h"
#include <vec.h>
#include <oid.h>
#include <so.h>
#include <lo.h>

/**
 * @class AMMO_MANAGER
 * @brief Object representing a manager for projectile ammo.
 * @todo Implement the struct.
 */
struct RWM : public LO
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct RWTI
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct RWAC
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct RWFI
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct RWC
{
    // ...
};

void InitRwm(RWM *prwm);

void PostRwmLoad(RWM *prwm);

RWC *PrwcFindRwm(RWM *prwm, OID oidCache);

void EnableRwmRwc(RWM *prwm, OID oidCache);

void DisableRwmRwc(RWM *prwm, OID oidCache);

void ResizeRwmRwc(RWM *prwm, OID oidCache, int cpso);

int FIsRwmAmmo(RWM *prwm, SO *psoAmmo);

int FAvailableRwmAmmo(RWM *prwm, SO *psoAmmo);

void CycleRwmCache(RWM *prwm);

void ReloadRwm(RWM *prwm);

int FEnsureRwmLoaded(RWM *prwm);

int FFireRwm(RWM *prwm, int fAim);

void ClearRwmFireInfo(RWM *prwm);

void ClearRwmTargetInfo(RWM *prwm);

void ClearRwmAimConstraints(RWM *prwm);

void GetRwfiPosMat(RWFI *prwfi, VECTOR *ppos, MATRIX3 *pmat);

void GetRwtiPos(RWTI *prwti, VECTOR *pposSource, VECTOR *ppos);

void GetRwacPan(RWAC *prwac, float *pradPan);

void GetRwacTilt(RWAC *prwac, float *pradTilt);

#endif // RWM_H
