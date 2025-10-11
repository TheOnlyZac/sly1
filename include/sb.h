/**
 * @file sb.h
 *
 * @brief Snow boss.
 */
#ifndef SB_H
#define SB_H

#include <stepguard.h>

/**
 * @class S_BOSS_GUARD
 * @brief Snow boss guard (Panda King).
 */
struct SBG : public STEPGUARD
{
    // ...
};

void PostSbgLoad(SBG *psbg);

undefined4 FUN_001a9928(SBG *psbg);

void UpdateSbgGoal(SBG *psbg, int fEnter);

void UpdateSbgSgs(SBG *psbg, SGS sgsPrev, ASEG *pasegTargetOverride);

void UpdateSbg(SBG *psbg, float dt);

// ...

int FAbsorbSbgWkr(SBG *psbg, WKR *pwkr);

// ...

#endif // SB_H
