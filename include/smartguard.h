#ifndef SMARTGUARD_H
#define SMARTGUARD_H

#include "common.h"
#include <stepguard.h>
#include <actseg.h>
#include <cid.h>
#include <mq.h>
#include <so.h>

/**
 * @class SMART_GUARD
 * @brief non-flashlight guard.
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
