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

extern BLOT* g_unkblot7;

void PostSbgLoad(SBG *psbg);

/**
 * @brief Unknown function.
 * @param psbg Pointer to Panda King.
 * @return Unknown return value.
 * @todo Figure out what this actually does, give better name. 
 */
undefined4 FUN_001a9928(SBG *psbg);

/**
 * @brief Updates Panda King's goal. 
 *        Also sets the goal if Panda King is stunned.
 *
 * @param psbg Pointer to Panda King.
 * @param fEnter Goal entry flag.
 */

void UpdateSbgGoal(SBG *psbg, int fEnter);

void UpdateSbgSgs(SBG *psbg, SGS sgsPrev, ASEG *pasegTargetOverride);

void UpdateSbg(SBG *psbg, float dt);

// ...

int FAbsorbSbgWkr(SBG *psbg, WKR *pwkr);

/**
 * @brief Calls functions in g_unkblot7.
 * @todo Figure out what this actually does, give better name. 
 */
void FUN_001a9a98();

// ...

#endif // SB_H
