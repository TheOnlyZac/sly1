/**
 * @file tank.h
 */
#ifndef TANK_H
#define TANK_H

#include "common.h"
#include <jt.h>
#include <cm.h>
#include <po.h>
#include <joy.h>
#include <zap.h>
#include <step.h>
#include <flash.h>

// Forward.
enum MSGID;

/**
 * @brief Tank State.
 */
enum TANKS
{
    TANKS_Nil = -1,
    TANKS_Passive = 0,
    TANKS_Active = 1,
    TANKS_Zap = 2,
    TANKS_Dead = 3,
    TANKS_Peek = 4,
    TANKS_Max = 5
};

/**
 * @class HOVER_TANK
 * @brief Hover tank used in A Ghastly Voyage and Rapid Fire Assault.
 */
struct TANK : public STEP
{
    // ...
};

void InitTank(TANK *ptank);

void PostTankLoad(TANK *ptank);

void UpdateTank(TANK *ptank, float dt);

void UseTankCharm(TANK *ptank);

void UpdateTankActive(TANK *ptank, JOY *pjoy, float dt);

void OnTankActive(TANK *ptank, int fActive, PO *ppoOther);

void RenderTankAll(TANK *ptank, CM *pcm, RO *pro);

void ImpactTank(TANK *ptank, int fParentDirty);

int FInvulnerableTank(TANK *ptank, ZPK zpk);

void ApplyTankThrow(TANK *ptank, PO *ppo);

int FTakeTankDamage(TANK *ptank, ZPR *pzpr);

// TODO: Define XP.
// void AdjustTankNewXp(TANK *ptank, XP *pxp, int ixpd);

void HandleTankMessage(TANK *ptank, MSGID msgid, void *pv);

JTHS JthsCurrentTank(TANK *ptank);

void SetTankTanks(TANK *ptank, TANKS tanks);

#endif // TANK_H
