#include <stepguard.h>
#include <asega.h>
#include <so.h>

extern SNIP s_asnipStepguardLoad;

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", InitStepguard__FP9STEPGUARD);

void LoadStepguardFromBrx(STEPGUARD *pstepguard, CBinaryInputStream *pbis)
{
    LoadSoFromBrx(pstepguard, pbis);
    SnipAloObjects(pstepguard, 1, &s_asnipStepguardLoad);
    LoadStepguardAnimations(pstepguard);
    LoadStepguardPhys(pstepguard);
}

void CloneStepguard(STEPGUARD *pstepguard, STEPGUARD *pstepguardBase)
{
    int ichkDead = STRUCT_OFFSET(pstepguard, 0xb10, int); // pstepguard->ichkDead
    SGG *psgg = STRUCT_OFFSET(pstepguard, 0x720, SGG *); // pstepguard->psgg
    ClonePo(pstepguard, pstepguardBase);
    STRUCT_OFFSET(pstepguard, 0xb10, int) = ichkDead; // pstepguard->ichkDead
    STRUCT_OFFSET(pstepguard, 0x720, SGG *) = psgg; // pstepguard->psgg
    STRUCT_OFFSET(pstepguard, 0xb74, STEPGUARD *) = pstepguardBase; // pstepguard->pstepguardBase
}

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", BindStepguard__FP9STEPGUARD);

void PostStepguardLoadCallback(STEPGUARD *pstepguard, MSGID msgid, void *pv)
{
    pstepguard->pvtlo->pfnRemoveLo(pstepguard);
}

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

/**
 * @todo 96.67% match.
 * https://decomp.me/scratch/HcoZ7
 */
INCLUDE_ASM("asm/nonmatchings/P2/stepguard", OnStepguardRemove__FP9STEPGUARD);
#ifdef SKIP_ASM
extern float D_0024D654;

void OnStepguardRemove(STEPGUARD *pstepguard)
{
    OnPoRemove(pstepguard);

    ASEGA *pasegaSgs = STRUCT_OFFSET(pstepguard, 0x7e0, ASEGA *);
    if (pasegaSgs)
    {
        RetractAsega(pasegaSgs);
        STRUCT_OFFSET(pstepguard, 0x7e0, ASEGA *) = 0;
    }

    ASEGA *pasegaPatrol = STRUCT_OFFSET(pstepguard, 0x754, ASEGA *);
    if (pasegaPatrol)
    {
        RetractAsega(pasegaPatrol);
        STRUCT_OFFSET(pstepguard, 0x754, ASEGA *) = 0;
    }

    SGG *psgg = STRUCT_OFFSET(pstepguard, 0x720, SGG *);
    if (psgg)
    {
        RemoveSggGuard(psgg, pstepguard);
    }

    const float val = D_0024D654;
    STRUCT_OFFSET(pstepguard, 0xa60, int) = 0;
    STRUCT_OFFSET(pstepguard, 0x748, int) = 0;
    STRUCT_OFFSET(pstepguard, 0xba4, int) = 0;

    STRUCT_OFFSET(pstepguard, 0xbf4, float) = val;
    STRUCT_OFFSET(pstepguard, 0xbf8, float) = val;
    STRUCT_OFFSET(pstepguard, 0xbfc, float) = val;
    STRUCT_OFFSET(pstepguard, 0x72c, int) = 0;
    STRUCT_OFFSET(pstepguard, 0xc00, float) = val;
}
#endif // SKIP_ASM

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

SGGS SggsGetStepguard(STEPGUARD *pstepguard)
{
    SGG *psgg = STRUCT_OFFSET(pstepguard, 0x720, SGG*);
    if (psgg == NULL)
        return SGGS_Dead;
    return STRUCT_OFFSET(psgg, 0x50, SGGS);
}

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", FAbsorbStepguardWkr__FP9STEPGUARDP3WKR);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", FTakeStepguardDamage__FP9STEPGUARDP3ZPR);

extern "C" int FUN_001c9a48(STEPGUARD *pstepguard)
{
    return STRUCT_OFFSET(pstepguard, 0xbd8, int) != 0;
}

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

void RenderStepguardSelf(STEPGUARD *pstepguard, CM *pcm, RO *pro)
{
    RenderStepSelf(pstepguard, pcm, pro);
}

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

void UseStepguardExpl(STEPGUARD *pstepguard, OID oidExpl)
{
    STRUCT_OFFSET(pstepguard, 0xafc, OID) = oidExpl;
    STRUCT_OFFSET(pstepguard, 0xaf8, int) = 1;
}

void UseStepguardRwm(STEPGUARD *pstepguard, OID oidRwm)
{
    STRUCT_OFFSET(pstepguard, 0xb08, OID) = oidRwm;
    STRUCT_OFFSET(pstepguard, 0xb04, int) = 1;
}

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", UseStepguardPhys__FP9STEPGUARD3SGS3OID);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", LoadStepguardPhys__FP9STEPGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", AddStepguardEffect__FP9STEPGUARD3OID3ZPK);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", SetStepguardPathzone__FP9STEPGUARD3OID);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", PsoEnemyStepguard__FP9STEPGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", FUN_001caad0);

void SetStepguardEnemyObject(STEPGUARD *pstepguard, SO *psoEnemy)
{
    STRUCT_OFFSET(pstepguard, 0xB48, SO *) = psoEnemy;
    STRUCT_OFFSET(pstepguard, 0xB40, int) = 1;
}

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", RebindStepguardEnemy__FP9STEPGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", FUN_001cac28__FP9STEPGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", FUN_001cac30);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", AdjustStepguardDz__FP9STEPGUARDiP2DZif);

void SetStepguardAttackAngleMax(STEPGUARD *pstepguard, float degAttackMax)
{
    STRUCT_OFFSET(pstepguard, 0x74c, float) = degAttackMax * 0.017453294f;
}

void AddStepguardAlarm(STEPGUARD *pstepguard, ALARM *palarm)
{
    EnsureSggAlarm(STRUCT_OFFSET(pstepguard, 0x720, SGG *), palarm);
}

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

void AddSggGuardName(SGG * p, OID oid)
{
    int c = STRUCT_OFFSET(p, 0x9c, int);
    if ((unsigned int)c < 16)
    {
        OID *a = &STRUCT_OFFSET(p, 0xa0, OID);
        a[c] = oid;
        STRUCT_OFFSET(p, 0x9c, int) = c + 1;
    }
}

void AddSggSearchXfmName(SGG * p, OID oid)
{
    int c = STRUCT_OFFSET(p, 0x124, int);
    if ((unsigned int)c < 16)
    {
        OID *a = &STRUCT_OFFSET(p, 0x128, OID);
        a[c] = oid;
        STRUCT_OFFSET(p, 0x124, int) = c + 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", RemoveSggGuard__FP3SGGP9STEPGUARD);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", BindSgg__FP3SGG);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", PostSggLoadCallback__FP3SGG5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", EnsureSggCallback__FP3SGG);

SO *PsoEnemySgg(SGG *psgg)
{
    SO *pso = STRUCT_OFFSET(psgg, 0x5c, SO *);
    void *pvt = STRUCT_OFFSET(pso, 0x0, void *);
    SO *(*fn)(SO *) = (SO *(*)(SO *))STRUCT_OFFSET(pvt, 0x198, void *);
    return fn(pso);
}

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", UpdateSggCallback__FP3SGG5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", SggsNextSgg__FP3SGG);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", FDetectSgg__FP3SGG);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", FAbandonSggSearch__FP3SGG);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", EnsureSggAlarm__FP3SGGP5ALARM);

void TriggerSggAlarms(SGG *psgg, ALTK altk)
{
    for (int i = 0; i < STRUCT_OFFSET(psgg, 0x168, int); i++) // psgg->calarms
    {
        TriggerAlarm(STRUCT_OFFSET_INDEX(psgg, 0x16c, ALARM *, i), altk); // psgg->palarms[i]
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", SetSggSggs__FP3SGG4SGGS);

INCLUDE_ASM("asm/nonmatchings/P2/stepguard", AssignSggSearchPoints__FP3SGG);

// junk_001CC3F8
JUNK_ADDIU(10);
JUNK_WORD(0x7c450000);
JUNK_WORD(0x48220800);
