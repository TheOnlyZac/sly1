/**
 * @file dartgun.h
 */
#ifndef DARTGUN_H
#define DARTGUN_H

#include "common.h"
#include <break.h>
#include <dart.h>
#include <rat.h>
#include <oid.h>
#include <so.h>
#include <mq.h>

/**
 * @class DARTGUN
 * @brief Dart gun used in High Class Heist?
 */
struct DARTGUN : public BRK
{
    // ...
};

void InitDartgun(DARTGUN *pdartgun);

void HandleDartgunMessage(DARTGUN *pdartgun, MSGID msgid, void *pv);

void BindDartgun(DARTGUN *pdartgun);

void PostDartgunLoad(DARTGUN *pdartgun);

void UpdateDartgun(DARTGUN *pdartgun, float dt);

int FIgnoreDartgunIntersection(DARTGUN *pdartgun, SO *psoOther);

void BreakDartgun(DARTGUN *pdartgun);

void SetDartgunGoalState(DARTGUN *pdartgun, OID oidStateGoal);

void TrackDartgun(DARTGUN *pdartgun, OID *poidStateGoal);

int FPrepareDartgunToFire__FP7DARTGUN(DARTGUN *pdartgun);

void FireDartgun(DARTGUN *pdartgun);

void AgeDartgunStuckDart(DARTGUN *pdartgun);

RAT *PratGetDartgunRatTarget(DARTGUN *pdartgun);

void AddDartgunRatTarget(DARTGUN *pdartgun, OID oid);

void StartDartgunTargetAreaChange(DARTGUN *pdartgun);

void AddDartgunTargetAreaTarget(DARTGUN *pdartgun, ALO *paloTarget);

#endif // DARTGUN_H
