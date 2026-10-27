/**
 * @file ub.h
 *
 * @brief Underwater boss.
 */
#ifndef UB_H
#define UB_H

#include "common.h"
#include <gomer.h>
#include <vec.h>
#include <so.h>
#include <screen.h>
#include <ui.h>

// Forward.
struct ASEG;
struct SM;
struct SMA;
struct XFM;

extern BLOT g_unkblot7;

/**
 * @class UW_BOSS_GOMER
 * @brief Underwater boss gomer (Raleigh).
 */
struct UBG : public GOMER
{
    /* 0xc50 */ SM *psmWorld;
    /* 0xc54 */ SMA *psmaWorld;
    /* 0xc58 */ OID oidPatrolGoal;
    /* 0xc5c */ int cJump;
    /* 0xc60 */ XFM *pxfmMiddle;
    /* 0xc64 */ SO *apsoPads[6];
    /* 0xc7c */ SO *psoLastDunk;
    /* 0xc80 */ int aichk[4];
    /* 0xc90 */ int nBossctr;
};

void InitUbg(UBG *pubg);

void PostUbgLoad(UBG *pubg);

SO *PsoPadUbgClosest(UBG *pubg, VECTOR *ppos);

void OnUbgEnteringSgs(UBG *pubg, SGS sgsPrev, ASEG *pasegOverride);

SGS SgsNextUbgAI(UBG *pubg);

int FDetectUbg(UBG *pubg);

int FCanUbgAttack(UBG *pubg);

void DoUbgFreefallJump(UBG *pubg);

void DoUbgFreefallLanding(UBG *pubg);

void UpdateUbgGoal(UBG *pubg, int fEnter);

void UpdateUbgSgs(UBG *pubg);

void FUN_001e8fe8();

int FIgnoreUbgIntersection(UBG *pubg, SO *psoOther);

#endif // UB_H
