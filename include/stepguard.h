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
    /* 0x34 */ STRUCT_PADDING(7);
    /* 0x50 */ SGGS sggs;
    /* 0x54 */ STRUCT_PADDING(69);
    /* 0x168 */ int calarms;        // count of alarms
    /* 0x16c */ ALARM **palarms;    // array of alarm pointers
    /* 0x170 */ STRUCT_PADDING(4);
    /* 0x180 */ OID oidSync;
    // ...
};

/**
 * @class STEP_GUARD
 * @brief Non-flashlight guard.
 */
struct STEPGUARD : public STEP
{
    /* 0x6c0 */ STRUCT_PADDING(24);
    /* 0x720 */ SGG *psgg;
    /* 0x724 */ SGS sgs;
    /* 0x728 */ STRUCT_PADDING(11);
    /* 0x754 */ ASEGA *pasegaPatrol;
    /* 0x758 */ STRUCT_PADDING(21);
    /* 0x7ac */ int unk7ac; // Nonzero lets a guard taunt when unkBFC expires.
    /* 0x7b0 */ STRUCT_PADDING(3);
    /* 0x7bc */ int unk7bc;
    /* 0x7c0 */ STRUCT_PADDING(1);
    /* 0x7c4 */ int unk7c4;
    /* 0x7c8 */ STRUCT_PADDING(1);
    /* 0x7cc */ int unk7cc; // Nonzero means FCanStepguardAttack is consulted.
    /* 0x7d0 */ STRUCT_PADDING(4);
    /* 0x7e0 */ ASEGA *pasegaSgs;
    /* 0x7e4 */ STRUCT_PADDING(82);
    /* 0x92c */ int unk92c;
    /* 0x930 */ int unk930;
    /* 0x934 */ STRUCT_PADDING(75);
    /* 0xa60 */ int unka60; // Nonzero while the guard has a goal it has not reached.
    /* 0xa64 */ STRUCT_PADDING(43);
    /* 0xb10 */ int ichkDead;
    /* 0xb14 */ STRUCT_PADDING(24);
    /* 0xb74 */ STEPGUARD *pstepguardBase;
    /* 0xb78 */ STRUCT_PADDING(31);
    /* 0xbf4 */ float unkbf4; // Timers, compared against g_clock.t.
    /* 0xbf8 */ float unkbf8;
    /* 0xbfc */ float unkbfc;
    /* 0xc00 */ float unkc00;
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

/**
 * @brief Decides which state a stepguard should be in next.
 *
 * @details Looks at the guard's current state and the state of its group (patrol,
 * search or attack). Returns SGS_Taunt if the taunt timer has run out, otherwise
 * moves the guard along its patrol, search and attack states, for example from
 * SGS_Discover to SGS_Pursue once its animation ends, or from the pursue and attack
 * states to SGS_LostPlayer when the lost-player timer expires. Returns the current
 * state if nothing should change.
 *
 * @param pstepguard The stepguard.
 * @return The state the guard should move to.
 * @note Some of the fields it reads are not named yet.
 */
SGS SgsNextStepguardAI(STEPGUARD *pstepguard);

void SetStepguardGoal(STEPGUARD *pstepguard, VECTOR *pposGoal);

/**
 * @brief Checks whether a stepguard has reached its goal.
 *
 * @param pstepguard The stepguard.
 * @return Nonzero if the guard has a goal and its two goal values are equal.
 */
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

/**
 * @brief Gets the state of a stepguard's group.
 *
 * @param pstepguard The stepguard.
 * @return The group's state, or SGGS_Dead if the guard has no group.
 */
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

/**
 * @brief Checks the struct has a 0 on an address, no idea what it means.
 * @todo Figure out what this actually does and give it a better name.
 * @param stepguard Pointer to the stepguard instance.
 * @param i Unused parameter.
 * @return Returns 1 if not equals 0, 0 otherwise.
 */
int FUN_001c9a48(STEPGUARD *stepguard, int i);

#endif // STEPGUARD_H
