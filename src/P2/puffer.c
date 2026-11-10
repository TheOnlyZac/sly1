#include <puffer.h>
#include <find.h>
#include <difficulty.h>
#include <rog.h>
#include <vec.h>
#include <sm.h>
#include <ui.h>
#include <lo.h>
#include <vol.h>
#include <clock.h>
#include <alo.h>
#include <vtables.h>
#include <po.h>
#include <oid.h>

extern VECTOR g_normalZ;
extern BLOT g_unkblot1;
extern BLOT g_unkblot8;
extern BLOT g_unkblot9;

/**
 * @todo ~65% matched (22 differing lines of 41): scheduling of the float loads and the qword copy differs.
 */
INCLUDE_ASM("asm/nonmatchings/P2/puffer", InitPuffer__FP6PUFFER);
#ifdef SKIP_ASM
void InitPuffer(PUFFER *ppuffer)
{
    InitPo(ppuffer);
    STRUCT_OFFSET(ppuffer, 0x61c, float) = -10.0f;
    STRUCT_OFFSET(ppuffer, 0x624, float) = D_0026A71C;
    STRUCT_OFFSET(ppuffer, 0x628, float) = D_0026A718;
    STRUCT_OFFSET(ppuffer, 0x630, qword) = *(qword *)&g_normalZ;
    STRUCT_OFFSET(ppuffer, 0x688, float) = 120.0f;
    InitDl(&STRUCT_OFFSET(ppuffer, 0x6a8, DL), 0x568);
    InitDl(&STRUCT_OFFSET(ppuffer, 0x69c, DL), 0x568);
    g_ppuffer = ppuffer;
}
#endif

void LoadPufferFromBrx(PUFFER *ppuffer, CBinaryInputStream *pbis)
{
    LoadSoFromBrx(ppuffer, pbis);
    SnipAloObjects(ppuffer, 1, D_0026A728);
}

INCLUDE_ASM("asm/nonmatchings/P2/puffer", PostPufferLoad__FP6PUFFER);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", PresetPufferAccel__FP6PUFFERf);

/**
 * @todo ~75% matched (8 differing lines of 31): branch layout of the final compare differs.
 */
INCLUDE_ASM("asm/nonmatchings/P2/puffer", FFilterPuffer__FP6PUFFERP2SO);
#ifdef SKIP_ASM
int FFilterPuffer(PUFFER *ppuffer, SO *psoOther)
{
    return (STRUCT_OFFSET(psoOther, 0x538, uint64_t) & 0x80000000000)
        && FIsBasicDerivedFrom(psoOther, (CID)0x1f)
        && STRUCT_OFFSET(psoOther, 0x50, PUFFER *) != ppuffer;
}
#endif

INCLUDE_ASM("asm/nonmatchings/P2/puffer", UpdatePuffer__FP6PUFFERf);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", PpufftChoosePuffer__FP6PUFFER);

void FUN_001973d8(PUFFER *ppuffer)
{
    float u = (float)STRUCT_OFFSET(ppuffer, 0x680, int) / (float)STRUCT_OFFSET(ppuffer, 0x684, int);
    float fMin = 0.0f;
    float fMax = 1.0f;
    float f;
    if (u < fMin)
        f = fMin;
    else if (fMax < u)
        f = fMax;
    else
        f = u;
    OnDifficultyPlayerDeathRaw(1.0f - f * 0.8f, &g_difficulty);
}

void FUN_00197458(PUFFER *ppuffer, int fEnter)
{
    if (fEnter == 1)
    {
        if (STRUCT_OFFSET(g_ppuffer, 0x6b8, SMA *) != NULL)
        {
            OID oidGoal;
            OID oidCur;
            GetSmaGoal(STRUCT_OFFSET(g_ppuffer, 0x6b8, SMA *), &oidGoal);
            GetSmaCur(STRUCT_OFFSET(g_ppuffer, 0x6b8, SMA *), &oidCur);
            if (oidGoal != (OID)0x3f4 && oidCur != (OID)0x3f4)
            {
                SetSmaGoal(STRUCT_OFFSET(g_ppuffer, 0x6b8, SMA *), (OID)0x3f5);
                FUN_001973d8(g_ppuffer);
            }
        }
    }
}

void OnPufferActive(PUFFER *ppuffer, int fActive, PO *ppoOther)
{
    OnPoActive(ppuffer, fActive, ppoOther);
}

INCLUDE_ASM("asm/nonmatchings/P2/puffer", UpdatePufferActive__FP6PUFFERP3JOYf);

/**
 * @todo ~90% matched (6 differing lines of 56): argument register for the FUN_001e9970 result.
 */
INCLUDE_ASM("asm/nonmatchings/P2/puffer", FUN_00197788__FP6PUFFER);
#ifdef SKIP_ASM
void FUN_00197788(PUFFER *ppuffer)
{
    OID oid;
    GetSmaCur(STRUCT_OFFSET(ppuffer, 0x6b8, SMA *), &oid);
    void *pv = (void *)oid;
    if (oid == (OID)0x3f3)
        pv = FUN_001e9970();
    if (pv != NULL)
    {
        g_unkblot1.pvtblot->pfnShowBlot(&g_unkblot1);
        g_unkblot8.pvtblot->pfnShowBlot(&g_unkblot8);
        g_unkblot9.pvtblot->pfnShowBlot(&g_unkblot9);
    }
    else
    {
        g_unkblot1.pvtblot->pfnHideBlot(&g_unkblot1);
        g_unkblot8.pvtblot->pfnHideBlot(&g_unkblot8);
        g_unkblot9.pvtblot->pfnHideBlot(&g_unkblot9);
    }
}
#endif

INCLUDE_ASM("asm/nonmatchings/P2/puffer", FUN_00197848);

void FUN_00197a08(PUFFER *ppuffer, PUFFC *ppuffc)
{
    ROST *prost = STRUCT_OFFSET(ppuffc, 0xc14, ROST *);
    SetRostRosts(prost, (ROSTS)0);
    RemoveDlEntry(&STRUCT_OFFSET(ppuffer, 0x6a8, DL), prost);
    AppendDlEntry(&STRUCT_OFFSET(ppuffer, 0x69c, DL), prost);
    STRUCT_OFFSET(ppuffc, 0xc14, ROST *) = NULL;
}

void FUN_00197a68(PUFFER *ppuffer, PUFFC *ppuffc)
{
    float f98 = D_0026A83C;
    float f94 = D_0026A840;
    STRUCT_OFFSET(ppuffc, 0x98, float) = f98;
    STRUCT_OFFSET(ppuffc, 0x94, float) = f94;
}

INCLUDE_ASM("asm/nonmatchings/P2/puffer", AddPufferWaterAcceleration__FP6PUFFERP5WATERf);

INCLUDE_ASM("asm/nonmatchings/P2/puffer", HandlePufferMessage__FP6PUFFER5MSGIDPv);

void PostPuffcLoad(PUFFC *ppuffc)
{
    PostStepguardLoad(ppuffc);
}

INCLUDE_ASM("asm/nonmatchings/P2/puffer", PresetPuffcAccel__FP5PUFFCf);

SGS FUN_001982a0(PUFFC *ppuffc)
{
    SGS sgsRet;
    switch (STRUCT_OFFSET(ppuffc, 0x724, SGS))
    {
    case SGS_PatrolIdle:
        if (SggsGetStepguard(ppuffc) == SGGS_Patrol) { sgsRet = SGS_ReturnToPatrol; break; }
        sgsRet = SgsNextStepguardAI(ppuffc);
        break;
    case SGS_Stun:
        sgsRet = SGS_Stun;
        if (STRUCT_OFFSET(ppuffc, 0xc10, int)) sgsRet = SGS_Reset;
        break;
    default:
        sgsRet = SgsNextStepguardAI(ppuffc);
        break;
    }
    return sgsRet;
}

INCLUDE_ASM("asm/nonmatchings/P2/puffer", UpdatePuffcGoal__FP5PUFFCi);

void OnPuffcExitingSgs(PUFFC *ppuffc, SGS sgsNext)
{
    if (STRUCT_OFFSET(ppuffc, 0x724, SGS) == SGS_Stun)
    {
        FUN_00197a08((PUFFER *)PpoCur(), ppuffc);
        VECTOR vel;
        STRUCT_OFFSET(&vel, 0, qword) = STRUCT_OFFSET(ppuffc, 0x150, qword);
        vel.z = 0.0f;
        typedef void (*PFNV)(PUFFC *, VECTOR *);
        STRUCT_OFFSET(STRUCT_OFFSET(ppuffc, 0x0, void *), 0x90, PFNV)(ppuffc, &vel);
    }
    OnStepguardExitingSgs(ppuffc, sgsNext);
}

void OnPuffcEnteringSgs(PUFFC *ppuffc, SGS sgsPrev, ASEG *pasegOverride)
{
    OnStepguardEnteringSgs(ppuffc, sgsPrev, pasegOverride);
    if (STRUCT_OFFSET(ppuffc, 0x724, SGS) == SGS_Stun)
    {
        FUN_001c8920__FP9STEPGUARD(ppuffc);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/puffer", UpdatePuffcSgs__FP5PUFFC);

void HandlePuffcMessage(PUFFC *ppuffc, MSGID msgid, void *pv)
{
    HandleStepguardMessage(ppuffc, msgid, pv);
    if (msgid != MSGID_water_entered)
    {
        if (msgid == MSGID_water_left)
        {
            if (STRUCT_OFFSET(pv, 0x4, PUFFC *) == ppuffc)
                STRUCT_OFFSET(ppuffc, 0xc10, int) = 0;
        }
    }
    else
    {
        if (STRUCT_OFFSET(pv, 0x4, PUFFC *) == ppuffc)
            STRUCT_OFFSET(ppuffc, 0xc10, int) = STRUCT_OFFSET(pv, 0x0, int);
    }
}

/**
 * @todo ~80% matched (16 differing lines of 70): float compare and count store scheduling.
 */
INCLUDE_ASM("asm/nonmatchings/P2/puffer", UpdatePuffc__FP5PUFFCf);
#ifdef SKIP_ASM
void UpdatePuffc(PUFFC *ppuffc, float dt)
{
    PO *ppo = PpoCur();
    if (FIsBasicDerivedFrom(ppo, (CID)0x18) && STRUCT_OFFSET(ppo, 0x640, VOL *) != NULL &&
        FIsLoInWorld(STRUCT_OFFSET(ppo, 0x640, VOL *)) && FCheckVolPoint(STRUCT_OFFSET(ppo, 0x640, VOL *), &STRUCT_OFFSET(ppuffc, 0x140, VECTOR)))
    {
        WKR wkr;
        wkr.ploSource = ppuffc;
        wkr.grftak = (GRFTAK)2;
        wkr.ploTarget = ppuffc;
        if (PaloAbsorbWkr(&wkr, 0, NULL))
        {
            int cpuff = STRUCT_OFFSET(ppo, 0x67c, int) + 1;
            int cpuffMax = D_0026A720;
            if (!(cpuff < cpuffMax))
                cpuff = cpuffMax;
            STRUCT_OFFSET(ppo, 0x67c, int) = cpuff;
            if (D_0024C868 == STRUCT_OFFSET(ppo, 0x698, float))
                STRUCT_OFFSET(ppo, 0x698, float) = g_clock.t + D_0026A838;
        }
    }
    UpdateStepguard(ppuffc, dt);
}
#endif

int FCanPuffcAttack(PUFFC *ppuffc)
{
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/puffer", FUN_00198860__FP5PUFFC);

void PostPuffbLoad(PUFFB *ppuffb)
{
    SnipAloObjects(ppuffb, 3, D_0026A8E0);
    PostAloLoad(ppuffb);
    PUFFER *ppuffer = (PUFFER *)PloFindSwObjectByClass(ppuffb->psw, 5, (CID)0x18, NULL);
    if (ppuffer != NULL)
    {
        STRUCT_OFFSET(ppuffer, 0x684, int) += 1;
    }
}
