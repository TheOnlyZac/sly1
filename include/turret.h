/**
 * @file turret.h
 *
 * @brief Stationary turret from Murray levels(?).
 */
#ifndef TURRET_H
#define TURRET_H

#include "common.h"
#include <dialog.h>
#include <alo.h>
#include <joy.h>
#include <so.h>
#include <po.h>
#include <mq.h>

/**
 * @class TURRET
 * @brief Stationary turret (maybe the one used in the murray levels).
 */
struct TURRET : public PO
{
    // ...
};

void InitTurret(TURRET *pturret);

void PostTurretLoad(TURRET *pturret);

void UpdateTurret(TURRET *pturret, float dt);

void UpdateTurretActive(TURRET *pturret, JOY *pjoy, float dt);

void OnTurretActive(TURRET *pturret, int fActive, PO *ppoOther);

int FFilterTurret(TURRET *pturret, SO *psoOther);

void UpdateTurretAim(TURRET *pturret);

void FireTurret(TURRET *pturret);

void HandleTurretMessage(TURRET *pturret, MSGID msgid, void *pv);

int FIgnoreTurretIntersection(TURRET *pturret, SO *psoOther);

void CollectTurretPrize(TURRET *pturret, PCK pck, ALO *paloOther);

void GetTurretDiapi(TURRET *pturret, DIALOG *pdialog, DIAPI *pdiapi);

#endif // TURRET_H
