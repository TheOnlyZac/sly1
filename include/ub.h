/**
 * @file ub.h
 *
 * @brief Underwater boss.
 */
#ifndef UB_H
#define UB_H

#include "common.h"
#include <gomer.h>
#include <anim.h>
#include <vec.h>
#include <so.h>

/**
 * @class UW_BOSS_GOMER
 * @brief Underwater boss gomer (Raleigh).
 */
struct UBG : public GOMER
{
	// ...
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

int FIgnoreUbgIntersection(UBG *pubg, SO *psoOther);

#endif // UB_H
