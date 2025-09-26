/**
 * @file dart.h
 *
 * @brief Dartgun projectiles.
 */
#ifndef DART_H
#define DART_H

#include "common.h"
#include <bis.h>
#include <mq.h>
#include <so.h>
#include <po.h>

// Forward.
struct EXPL;

/**
 * @brief Dart State.
 */
enum DARTS
{
    DARTS_Nil = -1,
    DARTS_AvailToFire = 0,
    DARTS_ReadyToFire = 1,
    DARTS_Airborne = 2,
    DARTS_Sticking = 3,
    DARTS_Stuck = 4,
    DARTS_Fading = 5,
    DARTS_Max = 6
};

/**
 * @class DART
 * @brief Projectile for dartguns.
 * @todo Implement the struct.
 */
struct DART : public SO
{
    // ...
    /* 0x56c */ DLE dleDartFree;
    // ...
    /* 0x58c */ EXPL *pexpl;
    // ...
};

void InitDart(DART *pdart);

void OnDartAdd(DART *pdart);

void RemoveDart(DART *pdart);

void CloneDart(DART *pdart, DART *pdartBase);

void LoadDartFromBrx(DART *pdart, CBinaryInputStream *pbis);

void HandleDartMessage(DART *pdart, MSGID msgid, void *pv);

void PostDartLoad(DART *pdart);

void UpdateDart(DART *pdart, float dt);

void SetDartDarts(DART *pdart, DARTS darts);

void ApplyDartThrow(DART *pdart, PO *ppo);

void UpdateDartAirborne(DART *pdart, float dt);

#endif // DART_H
