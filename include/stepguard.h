/**
 * @file stepguard.h
 */
#ifndef STEPGUARD_H
#define STEPGUARD_H

#include "common.h"
#include <alarm.h>
#include <step.h>
#include <zap.h>

// Forward.
struct ASEG;

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
 * @brief Stepguard (?) state.
 */
enum SGGS
{
    SGGS_Nil = -1,
    SGGS_Patrol = 0,
    SGGS_Search = 1,
    SGGS_Attack = 2,
    SGGS_Dead = 3,
    SGGS_Max = 4
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
 * @brief Stepguard (?).
 * @todo Implement the struct.
 */
struct SGG : public LO
{
    // ...
    /* 0x180 */ OID oidSync;
    // ...
};

/**
 * @class STEP_GUARD
 * @brief Non-flashlight guard.
 */
struct STEPGUARD : public STEP
{
    // ...
    /* 0x720 */ SGG *psgg;
    /* 0x724 */ STRUCT_PADDING(12);
    /* 0x754 */ ASEGA *pasegaPatrol;
    /* 0x758 */ STRUCT_PADDING(35);
    /* 0x7e0 */ ASEGA *pasegaSgs;
    /* 0x7e4 */ STRUCT_PADDING(203);
    /* 0xb10 */ int ichkDead;
    /* 0xb14 */ STRUCT_PADDING(24);
    /* 0xb74 */ STEPGUARD *pstepguardBase;
    // ...
};

/**
 * @brief Initializes the stepguard fields with default values.
 */
void InitStepguard(STEPGUARD *pstepguard);

void LoadStepguardFromBrx(STEPGUARD *pstepguard, CBinaryInputStream *pbis);

void CloneStepguard(STEPGUARD *pstepguard, STEPGUARD *pstepguardBase);

void BindStepguard(STEPGUARD *pstepguard);

void PostStepguardLoadCallback(STEPGUARD *pstepguard, MSGID msgid, void *pv);

void PostStepguardLoad(STEPGUARD *pstepguard);

int FIgnoreStepguardIntersection(STEPGUARD *pstepguard, SO *psoOther);

void OnStepguardAdd(STEPGUARD *pstepguard);

void OnStepguardRemove(STEPGUARD *pstepguard);

void PresetStepguardAccel(STEPGUARD *pstepguard, float dt);

float DradEnemyStepguard(STEPGUARD *pstepguard);

void SetStepguardTargetHeading(STEPGUARD *pstepguard, float radTarget, float radTilt);

void UpdateStepguardDrive(STEPGUARD *pstepguard);

void UpdateStepguard(STEPGUARD *pstepguard, float dt);

SGS SgsNextStepguardAI(STEPGUARD *pstepguard);

void SetStepguardGoal(STEPGUARD *pstepguard, VECTOR *pposGoal);

int FReachedStepguardGoal(STEPGUARD *pstepguard);

int FFilterStepguardJump(STEPGUARD *pstepguard, SO *pso);

void MoveStepguardToGoal(STEPGUARD *pstepguard);

void LookStepguardAtGoal(STEPGUARD *pstepguard);

void UpdateStepguardGoal(STEPGUARD *pstepguard, int fEnter);

void OnStepguardWaypointActive(STEPGUARD *pstepguard);

void UpdateStepguardSgs(STEPGUARD *pstepguard);

void SetStepguardSgs(STEPGUARD *pstepguard, SGS sgs, ASEG *pasegTargetOverride);

void SetStepguardSgsExternal(STEPGUARD *pstepguard, SGS sgs, ASEG *pasegTargetOverride);

void OnStepguardExitingSgs(STEPGUARD *pstepguard, SGS sgsNext);

void OnStepguardEnteringSgs(STEPGUARD *pstepguard, SGS sgsPrev, ASEG *pasegTargetOverride);

SGGS SggsGetStepguard(STEPGUARD *pstepguard);

int FAbsorbStepguardWkr(STEPGUARD *pstepguard, WKR *pwkr);

int FTakeStepguardDamage(STEPGUARD *pstepguard, ZPR *pzpr);

void HandleStepguardGrfsgsc(STEPGUARD *pstepguard);

void DoStepguardFreefallJump(STEPGUARD *pstepguard);

void DoStepguardFreefallLanding(STEPGUARD *pstepguard);

void HandleStepguardMessage(STEPGUARD *pstepguard, MSGID msgid, void *pv);

SGAS SgasGetStepguard(STEPGUARD *pstepguard);

int FCanStepguardAttack(STEPGUARD *pstepguard);

void RenderStepguardSelf(STEPGUARD *pstepguard, CM *pcm, RO *pro);

int FValidSgs(SGS sgs);

void UseStepguardAnimation(STEPGUARD *pstepguard, SGS sgs, OID oidAseg);

void UseStepguardAnimationImmediate(STEPGUARD *pstepguard, SGS sgs, OID oidAseg);

void UseStepguardDeathAnimation(STEPGUARD *pstepguard, GRFTAK grftak, OID oidAseg);

ASEG *PasegFindStepguard(STEPGUARD *pstepguard, OID oidAseg);

void LoadStepguardAnimations(STEPGUARD *pstepguard);

void UseStepguardExpl(STEPGUARD *pstepguard, OID oidExpl);

void UseStepguardRwm(STEPGUARD *pstepguard, OID oidRwm);

void UseStepguardPhys(STEPGUARD *pstepguard, SGS sgs, OID oidPhys);

void LoadStepguardPhys(STEPGUARD *pstepguard);

void AddStepguardEffect(STEPGUARD *pstepguard, OID oidEffect, ZPK zpk);

void SetStepguardPathzone(STEPGUARD *pstepguard, OID oidPathzone);

SO *PsoEnemyStepguard(STEPGUARD *pstepguard);

void SetStepguardEnemyObject(STEPGUARD *pstepguard, SO *psoEnemy);

void RebindStepguardEnemy(STEPGUARD *pstepguard);

void AdjustStepguardDz(STEPGUARD *pstepguard, GRFADJ grfadj, DZ *pdz, int ixpd, float dt);

void SetStepguardAttackAngleMax(STEPGUARD *pstepguard, float degAttackMax);

void AddStepguardAlarm(STEPGUARD *pstepguard, ALARM *palarm);

void MatchStepguardAnimationPhase(STEPGUARD *pstepguard, OID oid0, OID oid1, OID oid2, OID oid3);

void AddStepguardCustomXps(STEPGUARD *pstepguard, SO *psoOther, int cbspPruned, BSP *abspPruned, BSP *pbspPruned, XP **ppxp);

void UpdateStepguardEffect(STEPGUARD *pstepguard);

void SetStepguardPatrolAnimation(STEPGUARD *pstepguard, ASEG *pasegPatrol);

int FInflictStepguardZap(STEPGUARD *pstepguard, XP *pxp, ZPR *pzpr);

int FDetectStepguard(STEPGUARD *pstepguard);

int FCheckStepguardEnemyHidden(STEPGUARD *pstepguard);

SGG *PsggNew(SW *psw);

void InitSgg(SGG *psgg);

void AddSggGuard(SGG *psgg, STEPGUARD *pstepguard);

void AddSggGuardName(SGG *psgg, OID oidGuard);

void AddSggSearchXfmName(SGG *psgg, OID oidXfm);

void RemoveSggGuard(SGG *psgg, STEPGUARD *pstepguard);

void BindSgg(SGG *psgg);

void PostSggLoadCallback(SGG *psgg, MSGID msgid, void *pv);

void EnsureSggCallback(SGG *psgg);

SO *PsoEnemySgg(SGG *psgg);

void UpdateSggCallback(SGG *psgg, MSGID msgid, void *pv);

SGGS SggsNextSgg(SGG *psgg);

int FDetectSgg(SGG *psgg);

int FAbandonSggSearch(SGG *psgg);

void EnsureSggAlarm(SGG *psgg, ALARM *palarm);

void TriggerSggAlarms(SGG *psgg, ALTK altk);

void SetSggSggs(SGG *psgg, SGGS sggs);

void AssignSggSearchPoints(SGG *psgg);

#endif // STEPGUARD_H
