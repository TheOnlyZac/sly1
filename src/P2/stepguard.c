#include <stepguard.h>

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", InitStepguard__FP9STEPGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", LoadStepguardFromBrx__FP9STEPGUARDP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", CloneStepguard__FP9STEPGUARDT0);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", BindStepguard__FP9STEPGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", PostStepguardLoadCallback__FP9STEPGUARD5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", PostStepguardLoad__FP9STEPGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", FIgnoreStepguardIntersection__FP9STEPGUARDP2SO);

void OnStepguardAdd(STEPGUARD *pstepguard)
{
    OnPoAdd(pstepguard);

    // pstepguard->psgg
    if (STRUCT_OFFSET(pstepguard, 0x720, SGG *))
    {
        AddSggGuard(STRUCT_OFFSET(pstepguard, 0x720, SGG *), pstepguard);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", OnStepguardRemove__FP9STEPGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", PresetStepguardAccel__FP9STEPGUARDf);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", DradEnemyStepguard__FP9STEPGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", SetStepguardTargetHeading__FP9STEPGUARDff);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", FUN_001c7b60);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", UpdateStepguardDrive__FP9STEPGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", UpdateStepguard__FP9STEPGUARDf);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", SgsNextStepguardAI__FP9STEPGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", SetStepguardGoal__FP9STEPGUARDP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", FReachedStepguardGoal__FP9STEPGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", FFilterStepguardJump__FP9STEPGUARDP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", MoveStepguardToGoal__FP9STEPGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", FUN_001c8920);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", LookStepguardAtGoal__FP9STEPGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", UpdateStepguardGoal__FP9STEPGUARDi);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", FUN_001c8d40);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", OnStepguardWaypointActive__FP9STEPGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", UpdateStepguardSgs__FP9STEPGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", SetStepguardSgs__FP9STEPGUARD3SGSP4ASEG);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", SetStepguardSgsExternal__FP9STEPGUARD3SGSP4ASEG);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", OnStepguardExitingSgs__FP9STEPGUARD3SGS);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", OnStepguardEnteringSgs__FP9STEPGUARD3SGSP4ASEG);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", SggsGetStepguard__FP9STEPGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", FAbsorbStepguardWkr__FP9STEPGUARDP3WKR);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", FTakeStepguardDamage__FP9STEPGUARDP3ZPR);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", FUN_001c9a48);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", HandleStepguardGrfsgsc__FP9STEPGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", DoStepguardFreefallJump__FP9STEPGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", DoStepguardFreefallLanding__FP9STEPGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", FUN_001c9d50);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", HandleStepguardMessage__FP9STEPGUARD5MSGIDPv);

SGAS SgasGetStepguard(STEPGUARD *pstepguard)
{
    return SGAS_Force;
}

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", FCanStepguardAttack__FP9STEPGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", RenderStepguardSelf__FP9STEPGUARDP2CMP2RO);

int FValidSgs(SGS sgs)
{
    return ((uint)sgs < 0x11);
}

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", UseStepguardAnimation__FP9STEPGUARD3SGS3OID);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", UseStepguardAnimationImmediate__FP9STEPGUARD3SGS3OID);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", FUN_001ca6d0);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", UseStepguardDeathAnimation__FP9STEPGUARDi3OID);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", PasegFindStepguard__FP9STEPGUARD3OID);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", LoadStepguardAnimations__FP9STEPGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", UseStepguardExpl__FP9STEPGUARD3OID);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", UseStepguardRwm__FP9STEPGUARD3OID);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", UseStepguardPhys__FP9STEPGUARD3SGS3OID);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", LoadStepguardPhys__FP9STEPGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", AddStepguardEffect__FP9STEPGUARD3OID3ZPK);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", SetStepguardPathzone__FP9STEPGUARD3OID);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", PsoEnemyStepguard__FP9STEPGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", FUN_001caad0);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", SetStepguardEnemyObject__FP9STEPGUARDP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", RebindStepguardEnemy__FP9STEPGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", FUN_001cac28__FP9STEPGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", FUN_001cac30);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", AdjustStepguardDz__FP9STEPGUARDiP2DZif);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", SetStepguardAttackAngleMax__FP9STEPGUARDf);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", AddStepguardAlarm__FP9STEPGUARDP5ALARM);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", MatchStepguardAnimationPhase__FP9STEPGUARD3OIDN31);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", AddStepguardCustomXps__FP9STEPGUARDP2SOiP3BSPT3PP2XP);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", FUN_001caee0);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", UpdateStepguardEffect__FP9STEPGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", SetStepguardPatrolAnimation__FP9STEPGUARDP4ASEG);

int FInflictStepguardZap(STEPGUARD *pstepguard, XP *pxp, ZPR *pzpr)
{
    return 1;
}

int FDetectStepguard(STEPGUARD *pstepguard)
{
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", FCheckStepguardEnemyHidden__FP9STEPGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", FUN_001cb578);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", PsggNew__FP2SW);

void InitSgg(SGG *psgg)
{
    InitLo(psgg);
    STRUCT_OFFSET(psgg, 0x180, OID) = OID_Nil; // psgg->oidSync
}

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", AddSggGuard__FP3SGGP9STEPGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", AddSggGuardName__FP3SGG3OID);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", AddSggSearchXfmName__FP3SGG3OID);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", RemoveSggGuard__FP3SGGP9STEPGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", BindSgg__FP3SGG);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", PostSggLoadCallback__FP3SGG5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", EnsureSggCallback__FP3SGG);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", PsoEnemySgg__FP3SGG);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", UpdateSggCallback__FP3SGG5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", SggsNextSgg__FP3SGG);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", FDetectSgg__FP3SGG);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", FAbandonSggSearch__FP3SGG);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", EnsureSggAlarm__FP3SGGP5ALARM);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", TriggerSggAlarms__FP3SGG4ALTK);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", SetSggSggs__FP3SGG4SGGS);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", AssignSggSearchPoints__FP3SGG);

// junk_001CC3F8
JUNK_ADDIU(10);
JUNK_WORD(0x7c450000);
JUNK_WORD(0x48220800);
