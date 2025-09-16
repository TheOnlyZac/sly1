/**
 * @file stepguard.h
 */
#ifndef STEPGUARD_H
#define STEPGUARD_H

#include "common.h"
#include <step.h>
#include <anim.h>

/**
 * @brief Unknown.
 */
enum SGAS
{
    SGAS_Nil = -1,
    SGAS_No = 0,
    SGAS_Yes = 1,
    SGAS_Force = 2,
    SGAS_Max = 3
};

/**
 * @brief Stepguard State.
 */
enum SGS
{
    SGS_Nil = -1,
    SGS_Reset = 0,
    SGS_Patrol = 1,
    SGS_PatrolIdle = 2,
    SGS_PatrolWaypoint = 3,
    SGS_ReturnToPatrol = 4,
    SGS_Search = 5,
    SGS_SearchIdle = 6,
    SGS_Discover = 7,
    SGS_LostPlayer = 8,
    SGS_GiveUpSearch = 9,
    SGS_Taunt = 10,
    SGS_Dying = 11,
    SGS_Pursue = 12,
    SGS_PursueIdle = 13,
    SGS_Attack = 14,
    SGS_AttackIdle = 15,
    SGS_Stun = 16,
    SGS_Max = 17
};

/**
 * @class STEP_GUARD
 * @brief Non-flashlight guard.
 */
struct STEPGUARD : public STEP
{
    // ...
};

/**
 * @brief Initializes the stepguard fields with default values.
 */
void InitStepguard(STEPGUARD *pstepguard);

/**
 * @todo
 */
void PostStepguardLoad(STEPGUARD *pstepguard);

// ...

/**
 * @todo
 */
void SetStepguardSgs(STEPGUARD *pstepguard, SGS sgs, ASEG *pasegTargetOverride);

#endif // STEPGUARD_H
