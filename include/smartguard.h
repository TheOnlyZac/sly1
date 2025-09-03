#ifndef SMARTGUARD_H
#define SMARTGUARD_H

#include "common.h"
#include <stepguard.h>
#include <actseg.h>
#include <cid.h>
#include <mq.h>
#include <so.h>

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
 * @brief Flashlight guard state.
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
 * @brief Flashlight guard.
 */
struct SMARTGUARD : public STEPGUARD
{
    // ...
};

void InitSmartguard(SMARTGUARD *psmartguard);

void PostSmartguardLoadFlashlight(SMARTGUARD *psmartguard);

void UseSmartguardFlashlightTarget(SMARTGUARD *psmartguard, SGS sgs, OID oidTarget);

void PostSmartguardLoad(SMARTGUARD *psmartguard);

int FFilterSmartguardDetect(SMARTGUARD *psmartguard, SO *pso);

int FDetectSmartguard(SMARTGUARD *psmartguard);

void UpdateSmartguard(SMARTGUARD *psmartguard, float dt);

void UpdateSmartguardFlashlight(SMARTGUARD *psmartguard);

void OnSmartguardEnteringSgs(SMARTGUARD *psmartguard, SGS sgsPrev, ASEG *pasegOverride);

int FCanSmartguardAttack(SMARTGUARD *psmartguard);

SGAS SgasGetSmartguard(SMARTGUARD *psmartguard);

void HandleSmartguardMessage(SMARTGUARD *psmartguard, MSGID msgid, void *pv);

void FreezeSmartguard(SMARTGUARD *psmartguard, int fFreeze);

#endif // SMARTGUARD_H
