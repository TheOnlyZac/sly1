#include <rog.h>
#include <cm.h>
#include <clock.h>
#include <mat.h>
#include <dl.h>
#include <memory.h>
#include <emitter.h>
#include <sm.h>
#include <find.h>
#include <asega.h>
#include <aseg.h>
#include <xform.h>
#include <wipe.h>
#include <vec.h>
#include <gcc/math.h>
#include <basic.h>
#include <game.h>
#include <screen.h>
#include <ui.h>
#include <find.h>
#include <difficulty.h>
#include <prompt.h>
#include <sw.h>

extern SNIP s_asnipLoadRov[2];
extern SNIP s_asnipPostRov[6];
extern SNIP s_asnipLoadRoh[6];
extern SNIP s_asnipLoadRoc[1];
extern SNIP s_asnipPostRoc[1];
extern SNIP s_asnipLoadRost[1];
extern SMP s_smpRovAccel; // guess
extern SMP s_smpRocAccel; // guess
extern VECTOR g_normalZ;
extern BLOT g_binoc;
extern BLOT g_unkblot0;
extern BLOT g_unkblot12;
// the symbol for this function is still unmangled in symbol_addrs.txt (difficulty.c has it as INCLUDE_ASM)
void OnDifficultyPlayerDeathUnmangled(float scalar, DIFFICULTY *pdifficulty) asm("OnDifficultyPlayerDeath");
extern PROMPT D_0026FF68; // guess, a global prompt

void PropagateSoForce(SO *pso, GRFSG grfsg, XP *pxp, int ixpd, DZ *pdz, FX *afx); // @todo move to so.h
// rodata of this file (order matters: smp, then rodd)
extern const SMP s_smpRovPan = {30.0f, 0.0f, 0.2f}; // guess
extern const RODD D_0024C9D0 = {{ // default rodd values, raw words
    0x40000000, 0x40a00000, 0x00000000, 0x00000000,
    0x00000000, 0x3f800000, 0x00000000, 0x00000000,
    0x00000000, 0x41000000, 0x00000000, 0x00000000,
    0x00000000, 0x3f800000, 0x00000000, 0x00000000,
    0x3f800000, 0x40200000, 0x3dcccccd, 0x3e99999a,
    0x00000000, 0x3f800000, 0x00000000, 0x00000000,
    0x3fc00000, 0x40400000, 0x3e19999a, 0x3ecccccd,
    0x00000000, 0x3f800000, 0x00000000, 0x00000000,
    0x43c80000, 0x44bb8000, 0x00000000, 0x00000000,
    0x00000000, 0x3f800000, 0x00000000, 0x00000000,
    0x40400000, 0x40c00000, 0x00000000, 0x00000000,
    0x00000000, 0x3f800000, 0x00000000, 0x00000000
}};

// Inline copy of GLimitLm (the original is inlined here and the out of line one does not match).
static inline float GLimitLmInl(LM *plm, float g)
{
    float lo = plm->gMin;
    float hi = plm->gMax;
    if (g < lo)
    {
        return lo;
    }
    if (g > hi)
    {
        return hi;
    }
    return g;
}
extern VECTOR g_vecZero; // guess
#include <sound.h>
#include <util.h>

// vtable slot 0x64 takes a parent arg (declared with one arg in vtables.h)
#define SetAloParentVt(palo, pparent) ((void (*)(ALO *, ALO *))(palo)->pvtalo->pfnSetAloParent)(palo, pparent)
extern OID s_mpmpostoidRost[]; // guess
extern OID s_mpmpocsoidRoc[]; // guess

struct W2 // 8 byte copy helper
{
    int a;
    int b;
};

void InitRov(ROV *prov)
{
    InitPo(prov);
    STRUCT_OFFSET(prov, 0x628, float) = 2000.0f; // prov->svMax
    STRUCT_OFFSET(prov, 0x610, ROVS) = ROVS_Nil; // prov->rovs
    STRUCT_OFFSET(prov, 0x614, ROVTS) = ROVTS_Nil; // prov->rovts
}

void LoadRovFromBrx(ROV *prov, CBinaryInputStream *pbis)
{
    LoadSoFromBrx(prov, pbis);
    SnipAloObjects(prov, 2, s_asnipLoadRov);
}

void PostRovLoad(ROV *prov)
{
    PostAloLoad(prov);
    if (STRUCT_OFFSET(prov, 0x678, int))
    {
        SnipAloObjects(prov, 6, s_asnipPostRov);
        SetSoConstraints(prov, CT_Free, 0, CT_Locked, 0);
        if (STRUCT_OFFSET(prov, 0x640, SM *))
        {
            STRUCT_OFFSET(prov, 0x644, SMA *) = PsmaApplySm(STRUCT_OFFSET(prov, 0x640, SM *), prov, OID_Nil, 0);
        }
        if (STRUCT_OFFSET(prov, 0x650, SM *))
        {
            STRUCT_OFFSET(prov, 0x654, SMA *) = PsmaApplySm(STRUCT_OFFSET(prov, 0x650, SM *), prov, OID_Nil, 1);
        }
        STRUCT_OFFSET(prov, 0x668, int) = CploFindSwObjectsByClass(
            g_psw, (GRFFSO)1, (CID)0x50, STRUCT_OFFSET(prov, 0x664, LO *), 3, &STRUCT_OFFSET(prov, 0x66c, LO *));
        SetRovRovs(prov, ROVS_Descend);
        SetRovRovts(prov, ROVTS_Calm);
    }
    else
    {
        prov->pvtlo->pfnRemoveLo(prov);
    }
}

void UpdateRovActive(ROV *prov, JOY *pjoy, float dt)
{
    if (STRUCT_OFFSET(prov, 0x688, int))
    {
        RetractAsega(STRUCT_OFFSET(prov, 0x684, ASEGA *));
        STRUCT_OFFSET(prov, 0x684, ASEGA *) = 0;
        STRUCT_OFFSET(prov, 0x688, int) = 0;
    }
    ReadRovJoystick(prov, pjoy);
    SetVectorCylind(&STRUCT_OFFSET(prov, 0x630, VECTOR), STRUCT_OFFSET(prov, 0x618, float),
                    STRUCT_OFFSET(prov, 0x61c, float) * STRUCT_OFFSET(prov, 0x628, float), 0.0f);
    MATRIX3 mat;
    SMP smp = s_smpRovPan;
    float radPan = RadSmooth(
        atan2f(STRUCT_OFFSET(STRUCT_OFFSET(prov, 0x64c, ALO *), 0x114, float),
               STRUCT_OFFSET(STRUCT_OFFSET(prov, 0x64c, ALO *), 0x110, float)),
        STRUCT_OFFSET(prov, 0x620, float), g_clock.dt, &smp, 0);
    LoadRotateMatrixPanTilt(radPan, 0.0f, &mat);
    ConvertAloMat(0, prov, &mat, &mat);
    STRUCT_OFFSET(prov, 0x64c, ALO *)->pvtalo->pfnRotateAloToMat(STRUCT_OFFSET(prov, 0x64c, ALO *), &mat);
}

INCLUDE_ASM("asm/nonmatchings/P2/rog", UpdateRov__FP3ROVf);

void ReadRovJoystick(ROV *prov, JOY *pjoy)
{
    if (pjoy->uDeflect > 0.3f)
    {
        // prov->radJoyLeft
        AdjustCmJoy(g_pcm, pjoy, JOYID_Left, &STRUCT_OFFSET(prov, 0x618, float));
    }
    STRUCT_OFFSET(prov, 0x61c, float) = pjoy->uDeflect;

    if (pjoy->uDeflect2 > 0.8f)
    {
        // prov->radJoyRight
        AdjustCmJoy(g_pcm, pjoy, JOYID_Right, &STRUCT_OFFSET(prov, 0x620, float));
    }
    STRUCT_OFFSET(prov, 0x624, float) = pjoy->uDeflect2;
}

ROVS RovsNextRov(ROV *prov)
{
    ROVS rovs = STRUCT_OFFSET(prov, 0x610, ROVS);
    switch (rovs)
    {
    case ROVS_Brake:
        if (STRUCT_OFFSET(prov, 0x61c, float) > 0.0f)
        {
            rovs = ROVS_Drive;
        }
        break;
    case ROVS_Drive:
        if (STRUCT_OFFSET(prov, 0x61c, float) == 0.0f)
        {
            rovs = ROVS_Brake;
        }
        break;
    case ROVS_Descend:
        if (!STRUCT_OFFSET(prov, 0x684, int))
        {
            rovs = ROVS_Drive;
        }
        break;
    }
    return rovs;
}

/**
 * @todo Near match (2 differing lines of 144): the prologue stores of $21 and $18 are scheduled in a different order.
 */
INCLUDE_ASM("asm/nonmatchings/P2/rog", SetRovRovs__FP3ROV4ROVS);
#ifdef SKIP_ASM
void SetRovRovs(ROV *prov, ROVS rovs)
{
    int i;
    ASEG *paseg = 0;
    ROVS rovsPrev = STRUCT_OFFSET(prov, 0x610, ROVS);
    if (rovsPrev != rovs)
    {
        STRUCT_OFFSET(prov, 0x610, ROVS) = rovs;
        OID oid = OID_Nil;
        int fPause = 0;
        SFXID sfxid = (SFXID)0x14d;
        switch (rovs)
        {
        case ROVS_Brake:
            oid = (OID)0x28f;
            fPause = 1;
            sfxid = (SFXID)-1;
            break;
        case ROVS_Drive:
            oid = (OID)0x290;
            break;
        case ROVS_Descend:
            oid = (OID)0x290;
            paseg = STRUCT_OFFSET(prov, 0x680, ASEG *);
            break;
        case ROVS_Ascend:
            oid = (OID)0x290;
            paseg = STRUCT_OFFSET(prov, 0x67c, ASEG *);
            TriggerDefaultExit(0, WIPEK_Keyhole);
            break;
        }
        for (i = 0; i < STRUCT_OFFSET(prov, 0x668, int); i++)
        {
            if (fPause)
            {
                PauseEmitterIndefinite(STRUCT_OFFSET(prov, 0x66c + i * 4, EMITTER *));
            }
            else
            {
                UnpauseEmitter(STRUCT_OFFSET(prov, 0x66c + i * 4, EMITTER *));
            }
        }
        SMA *psma = STRUCT_OFFSET(prov, 0x644, SMA *);
        if (psma)
        {
            if (rovsPrev == ROVS_Nil)
            {
                SeekSma(psma, oid);
            }
            else
            {
                SetSmaGoal(psma, oid);
            }
        }
        if (paseg)
        {
            ApplyAseg(paseg, prov, 0.0f, 1.0f, 1, &STRUCT_OFFSET(prov, 0x684, ASEGA *));
        }
        AMB *pamb = STRUCT_OFFSET(prov, 0x648, AMB *);
        if (pamb)
        {
            if (sfxid == STRUCT_OFFSET(pamb, 0x0, SFXID))
            {
                return;
            }
            StopSound(pamb, 0);
            STRUCT_OFFSET(prov, 0x648, AMB *) = 0;
        }
        if (sfxid != (SFXID)-1)
        {
            StartSound(sfxid, &STRUCT_OFFSET(prov, 0x648, AMB *), prov, 0, 10000.0f, 6000.0f, 0.5f, 0.0f, 0.0f, 0, 0);
        }
    }
}
#endif // SKIP_ASM

ROVTS RovtsNextRov(ROV *prov)
{
    ROVTS rovts = STRUCT_OFFSET(prov, 0x614, ROVTS);
    switch (rovts)
    {
    case ROVTS_Calm:
        if (STRUCT_OFFSET(prov, 0x624, float) >= 0.8f)
        {
            rovts = ROVTS_Firing;
        }
        break;
    case ROVTS_Firing:
        if (STRUCT_OFFSET(prov, 0x624, float) < 0.8f)
        {
            rovts = ROVTS_Calm;
        }
        break;
    }
    return rovts;
}

void SetRovRovts(ROV *prov, ROVTS rovts)
{
    ROVTS rovtsPrev = STRUCT_OFFSET(prov, 0x614, ROVTS);
    if (rovtsPrev != rovts)
    {
        OID oid;
        SFXID sfxid;
        STRUCT_OFFSET(prov, 0x614, ROVTS) = rovts;
        switch (rovts)
        {
        case ROVTS_Calm:
            oid = (OID)0x293;
            sfxid = (SFXID)-1;
            break;
        case ROVTS_Firing:
            oid = (OID)0x294;
            sfxid = (SFXID)0x150;
            break;
        }
        SMA *psma = STRUCT_OFFSET(prov, 0x654, SMA *);
        if (psma)
        {
            if (rovtsPrev == ROVTS_Nil)
            {
                SeekSma(psma, oid);
            }
            else
            {
                SetSmaGoal(psma, oid);
            }
        }
        AMB *pamb = STRUCT_OFFSET(prov, 0x658, AMB *);
        if (pamb)
        {
            if (sfxid == STRUCT_OFFSET(pamb, 0x0, SFXID))
            {
                return;
            }
            StopSound(pamb, 0);
            STRUCT_OFFSET(prov, 0x658, AMB *) = 0;
        }
        if (sfxid != (SFXID)-1)
        {
            StartSound(sfxid, &STRUCT_OFFSET(prov, 0x658, AMB *), prov, 0, 10000.0f, 6000.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
    }
}

void HandleRovMessage(ROV *prov, MSGID msgid, void *pv)
{
    HandlePoMessage(prov, msgid, pv);
    switch (msgid)
    {
    case MSGID_label:
        switch (STRUCT_OFFSET(pv, 0x8, OID))
        {
        case 0x295:
            StartSound((SFXID)0x152, 0, 0, &STRUCT_OFFSET(prov, 0x140, VECTOR), 12000.0f, 8000.0f, 0.5f, 0.0f, 0.0f, 0,
                       0);
            UnpauseEmitter(STRUCT_OFFSET(prov, 0x65c, EMITTER *));
            break;
        case 0x296:
            StartSound((SFXID)0x152, 0, 0, &STRUCT_OFFSET(prov, 0x140, VECTOR), 12000.0f, 8000.0f, 0.5f, 0.0f, 0.0f, 0,
                       0);
            UnpauseEmitter(STRUCT_OFFSET(prov, 0x660, EMITTER *));
            break;
        }
        break;
    case MSGID_asega_limit:
        if (pv == STRUCT_OFFSET(prov, 0x684, void *))
        {
            STRUCT_OFFSET(prov, 0x688, int) = 1;
        }
        break;
    }
}

void PresetRovAccel(ROV *prov, float dt)
{
    MATRIX3 mat;
    PresetSoAccel(prov, dt);
    LoadRotateMatrixPanTilt(STRUCT_OFFSET(prov, 0x618, float), 0.0f, &mat);
    AccelSoTowardMatSmooth(prov, g_clock.dt, &mat, &s_smpRovAccel);
}

INCLUDE_ASM("asm/nonmatchings/P2/rog", AdjustRovXpVelocity__FP3ROVP2XPi);

void AdjustRovNewXp(ROV *prov, XP *pxp, int ixpd)
{
    if (!FDrivenAlo(prov) && STRUCT_OFFSET(pxp, 0x88, float) > 0.7f)
    {
        STRUCT_OFFSET(pxp, 0x94, float) = 20.0f;
    }
}

void PropagateRovForce(ROV *prov, GRFSG grfsg, XP *pxp, int ixpd, DZ *pdz, FX *afx)
{
    qword aqwSave[2];
    aqwSave[0] = STRUCT_OFFSET(prov, 0x440, qword);
    aqwSave[1] = STRUCT_OFFSET(prov, 0x450, qword);
    BASIC *pbasic = *(BASIC **)((uint8_t *)pxp + ((1 - ixpd) << 6));
    if (pbasic)
    {
        if (FIsBasicDerivedFrom(pbasic, (CID)0x43) || FIsBasicDerivedFrom(pbasic, (CID)0x42))
        {
            STRUCT_OFFSET(prov, 0x450, int) = 1;
            STRUCT_OFFSET(prov, 0x440, qword) = *(qword *)&g_normalZ;
        }
    }
    PropagateSoForce(prov, grfsg, pxp, ixpd, pdz, afx);
    STRUCT_OFFSET(prov, 0x440, qword) = aqwSave[0];
    STRUCT_OFFSET(prov, 0x450, qword) = aqwSave[1];
}

int FIsRovSoundBase(ROV *prov)
{
    return 0;
}

void InitRob(ROB *prob)
{
    RODD rodd;
    InitAlo(prob);
    InitDl(&STRUCT_OFFSET(prob, 0x35c, DL), 0x5a0);
    InitDl(&STRUCT_OFFSET(prob, 0x368, DL), 0x5a0);
    InitDl(&STRUCT_OFFSET(prob, 0x374, DL), 0x5a0);
    InitDl(&STRUCT_OFFSET(prob, 0x384, DL), 0x5b0);
    InitDl(&STRUCT_OFFSET(prob, 0x390, DL), 0x5b0);
    InitDl(&STRUCT_OFFSET(prob, 0x3a0, DL), 0x568);
    InitDl(&STRUCT_OFFSET(prob, 0x3ac, DL), 0x568);
    STRUCT_OFFSET(prob, 0x2d0, OID) = OID_Nil;
    STRUCT_OFFSET(prob, 0x2d4, OID) = OID_Nil;
    STRUCT_OFFSET(prob, 0x2d8, OID) = OID_Nil;
    STRUCT_OFFSET(prob, 0x2dc, OID) = OID_Nil;
    STRUCT_OFFSET(prob, 0x64c, int) = -1;
    STRUCT_OFFSET(prob, 0x650, int) = -1;
    STRUCT_OFFSET(prob, 0x3b8, int) = 0x28;
    rodd = D_0024C9D0;
    CopyAb(&STRUCT_OFFSET(prob, 0x3e0, RODD), &rodd, 0xc0);
    CopyAb(&STRUCT_OFFSET(prob, 0x4a0, RODD), &rodd, 0xc0);
    STRUCT_OFFSET(prob, 0x3d0, qword) = *(qword *)&g_clqOne;
    STRUCT_OFFSET(prob, 0x348, float) = 2300.0f;
    STRUCT_OFFSET(prob, 0x344, float) = 1500.0f;
    STRUCT_OFFSET(prob, 0x34c, float) = 1.46f;
    STRUCT_OFFSET(prob, 0x340, int) = 0;
    STRUCT_OFFSET(prob, 0x350, float) = 3000.0f;
}

void SetRobCollectible(ROB *prob, OID oidCollectible)
{
    STRUCT_OFFSET(prob, 0x2d0, OID) = oidCollectible;
}

void SetRobHarvester(ROB *prob, OID oidHarvester)
{
    STRUCT_OFFSET(prob, 0x2d4, OID) = oidHarvester;
}

void SetRobVehicle(ROB *prob, OID oidVehicle)
{
    STRUCT_OFFSET(prob, 0x2d8, OID) = oidVehicle;
}

void SetRobPrize(ROB *prob, OID oidPrize)
{
    STRUCT_OFFSET(prob, 0x2dc, OID) = oidPrize;
}

void AddRobSpawnTunnel(ROB *prob, OID oidSpawnTunnel)
{
    int coidRost = STRUCT_OFFSET(prob, 0x2e0, int); // prob->coidRost
    OID *aoidRost = &STRUCT_OFFSET(prob, 0x2e4, OID); // prob->aoidRost
    aoidRost[coidRost] = oidSpawnTunnel;
    STRUCT_OFFSET(prob, 0x2e0, int) = coidRost + 1; // prob->coidRost
}

/**
 * @brief Near match (1 differing line of 10): the target returns `(fls & 2) > 0` via `sltu $2, $0, $2` in the
 * delay slot, every bool-style form tried (about 20) gives different code.
 * https://decomp.me/scratch/s3oRy
 */
INCLUDE_ASM("asm/nonmatchings/P2/rog", RobkCur__Fv);
#ifdef SKIP_ASM
ROBK RobkCur()
{
    if ((uint)g_plsCur->fls & FLS_Secondary)
    {
        return ROBK_Tertiary;
    }

    return (ROBK)((uint)g_plsCur->fls & FLS_KeyCollected);
}
#endif // SKIP_ASM

INCLUDE_ASM("asm/nonmatchings/P2/rog", BindRob__FP3ROB);

void PostRobLoad(ROB *prob)
{
    PostAloLoad(prob);
    if (STRUCT_OFFSET(prob, 0x64c, ROBK) != RobkCur())
    {
        prob->pvtlo->pfnRemoveLo(prob);
        return;
    }
    float gRaw = GEvaluateClq(&STRUCT_OFFSET(prob, 0x3d0, CLQ), g_plsCur->uSuck);
    float g = GLimitLmInl(&g_lmZeroOne, gRaw);
    float *pgA = &STRUCT_OFFSET(prob, 0x3e0, float);
    float *pgB = &STRUCT_OFFSET(prob, 0x4a0, float);
    float *pgCur = &STRUCT_OFFSET(prob, 0x560, float);
    int i = 0;
    do
    {
        *pgCur++ = GLerp(*pgA++, *pgB++, g);
        i++;
    } while ((uint)i < 0x30);
    AdjustRobDifficulty(prob, 0.0f);
    SetRobRobs(prob, ROBS_Descend);
}

void UpdateRob(ROB *prob, float dt)
{
    UpdateAlo(prob, dt);
    ROBS robs;
    while ((robs = RobsNextRob(prob)) != STRUCT_OFFSET(prob, 0x650, ROBS))
    {
        SetRobRobs(prob, robs);
    }
    switch (robs)
    {
    case ROBS_Normal:
        if (STRUCT_OFFSET(prob, 0x3bc, int) < STRUCT_OFFSET(prob, 0x3b8, int))
        {
            if (STRUCT_OFFSET(prob, 0x634, float) < g_clock.t)
            {
                AddRobRoc(prob);
            }
        }
        if (STRUCT_OFFSET(prob, 0x640, float) < g_clock.t)
        {
            AddRobRoh(prob);
        }
        break;
    case ROBS_Ascend:
    {
        ROP *prop = STRUCT_OFFSET(prob, 0x358, ROP *);
        if (prop)
        {
            if (!STRUCT_OFFSET(prop, 0x550, int))
            {
                ALO *palo = STRUCT_OFFSET(prob, 0x658, ALO *);
                if (!palo || STRUCT_OFFSET(palo, 0x2d4, int) != 3)
                {
                    SetRopRops(prop, ROPS_Reveal);
                }
            }
        }
        break;
    }
    case ROBS_Descend:
    case ROBS_Instruct:
    case ROBS_Lose:
    case ROBS_Win:
    case ROBS_Max:
        break;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/rog", FUN_001a4d60);

ROBS RobsNextRob(ROB *prob)
{
    ROBS robs = STRUCT_OFFSET(prob, 0x650, ROBS);
    switch (robs)
    {
    case ROBS_Descend:
        if ((uint)STRUCT_OFFSET(STRUCT_OFFSET(prob, 0x354, ROV *), 0x610, ROVS) <= 1)
        {
            robs = ROBS_Instruct;
        }
        break;
    case ROBS_Instruct:
    {
        ALO *palo = STRUCT_OFFSET(prob, 0x658, ALO *);
        if (!palo || STRUCT_OFFSET(palo, 0x2d4, int) != 3)
        {
            robs = ROBS_Normal;
        }
        break;
    }
    case ROBS_Normal:
        if (STRUCT_OFFSET(prob, 0x3c0, int))
        {
            robs = ROBS_Lose;
        }
        else if (STRUCT_OFFSET(prob, 0x3c4, int) == STRUCT_OFFSET(prob, 0x3b8, int))
        {
            robs = ROBS_Ascend;
        }
        break;
    case ROBS_Lose:
        if (STRUCT_OFFSET(STRUCT_OFFSET(prob, 0x658, ALO *), 0x2d4, int) != 3)
        {
            robs = ROBS_Win;
        }
        break;
    case ROBS_Ascend:
    {
        ROP *prop = STRUCT_OFFSET(prob, 0x358, ROP *);
        if (prop)
        {
            if (STRUCT_OFFSET(prop, 0x550, int) == 3 && STRUCT_OFFSET(prop, 0x554, float) + 3.0f < g_clock.t)
            {
                robs = ROBS_Max;
            }
        }
        else if (STRUCT_OFFSET(prob, 0x654, float) + 5.0f < g_clock.t)
        {
            ALO *palo = STRUCT_OFFSET(prob, 0x658, ALO *);
            if (!palo || STRUCT_OFFSET(palo, 0x2d4, int) != 3)
            {
                robs = ROBS_Max;
            }
        }
        break;
    }
    case ROBS_Win:
    case ROBS_Max:
        break;
    }
    return robs;
}

struct PK // unaligned pointer store helper
{
    LO *plo;
} __attribute__((packed));
void SetRobRobs(ROB *prob, ROBS robs)
{
    if (STRUCT_OFFSET(prob, 0x650, ROBS) != robs)
    {
        STRUCT_OFFSET(prob, 0x650, ROBS) = robs;
        STRUCT_OFFSET(prob, 0x654, float) = g_clock.t;
        STRUCT_OFFSET(prob, 0x658, LO *) = 0;
        switch (robs)
        {
        case ROBS_Descend:
            break;
        case ROBS_Instruct:
        {
            int n = STRUCT_OFFSET(prob, 0x64c, int);
            int pad; // unused local, reproduces the 16 byte stack frame
            asm("" : : "m"(pad));
            if (n < 3)
            {
                if (n >= 0)
                {
                    if (g_plsCur->afDialogPlayed[0])
                    {
                        STRUCT_OFFSET(prob, 0x658, LO *) = 0;
                    }
                    else
                    {
                        STRUCT_OFFSET(prob, 0x658, LO *) =
                            PloFindSwObject(STRUCT_OFFSET(prob, 0x14, SW *), 0x105, (OID)0x33b, 0);
                    }
                }
            }
            if (STRUCT_OFFSET(prob, 0x658, LO *))
            {
                BLOT *pbinoc = &g_binoc;
                STRUCT_OFFSET(pbinoc, 0x324, PK).plo = STRUCT_OFFSET(prob, 0x658, LO *);
                PushUiActiveBlot(&g_ui, pbinoc);
            }
            break;
        }
        case ROBS_Normal:
        {
            BLOT *pblot = &g_unkblot0;
            STRUCT_OFFSET(pblot, 0x264, int *) = &STRUCT_OFFSET(prob, 0x3c4, int);
            STRUCT_OFFSET(pblot, 0x268, int *) = &STRUCT_OFFSET(prob, 0x3b8, int);
            FUN_001ddc38(STRUCT_OFFSET(prob, 0x14, SW *), prob);
            break;
        }
        case ROBS_Ascend:
        {
            LO *plo = PloFindSwObject(STRUCT_OFFSET(prob, 0x14, SW *), 0x105, (OID)0x33d, 0);
            if ((STRUCT_OFFSET(prob, 0x658, LO *) = plo))
            {
                BLOT *pbinoc = &g_binoc;
                STRUCT_OFFSET(pbinoc, 0x324, LO *) = plo;
                PushUiActiveBlot(&g_ui, pbinoc);
            }
            for (ROH *proh = STRUCT_OFFSET(prob, 0x384, ROH *); proh; proh = STRUCT_OFFSET(proh, 0x5b0, ROH *))
            {
                SetRohRohs(proh, (ROHS)8);
            }
            OnDifficultyCollectKey(&g_difficulty);
            break;
        }
        case ROBS_Lose:
        {
            LO *plo = PloFindSwObject(STRUCT_OFFSET(prob, 0x14, SW *), 0x105, (OID)0x33e, 0);
            if ((STRUCT_OFFSET(prob, 0x658, LO *) = plo))
            {
                BLOT *pbinoc = &g_binoc;
                STRUCT_OFFSET(pbinoc, 0x324, LO *) = plo;
                PushUiActiveBlot(&g_ui, pbinoc);
            }
            for (ROH *proh = STRUCT_OFFSET(prob, 0x384, ROH *); proh; proh = STRUCT_OFFSET(proh, 0x5b0, ROH *))
            {
                ROH *prohOwner = STRUCT_OFFSET(proh, 0x55c, ROH *);
                if (!prohOwner || STRUCT_OFFSET(prohOwner, 0x18, ROH *) != proh)
                {
                    SetRohRohs(proh, (ROHS)7);
                }
            }
            OnDifficultyPlayerDeathUnmangled(1.0f, &g_difficulty);
            break;
        }
        case ROBS_Win:
            SetPrompt(&D_0026FF68, (PRP)0, (PRK)0x1a);
            break;
        case ROBS_Max:
            SetRovRovs(STRUCT_OFFSET(prob, 0x354, ROV *), ROVS_Ascend);
            ((void (*)(BLOT *))STRUCT_OFFSET(g_unkblot12.pvtblot, 0x3c, void *))(&g_unkblot12);
            break;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/rog", AddRobRoc__FP3ROB);

INCLUDE_ASM("asm/nonmatchings/P2/rog", AddRobRoh__FP3ROB);

void AdjustRobDifficulty(ROB *prob, float rRoc)
{
    float u1 = GLimitLmInl(&g_lmZeroOne, GEvaluateClq(&STRUCT_OFFSET(prob, 0x5b0, CLQ), rRoc));
    STRUCT_OFFSET(prob, 0x62c, float) = GLerp(STRUCT_OFFSET(prob, 0x5a0, float), STRUCT_OFFSET(prob, 0x5a8, float), u1);
    STRUCT_OFFSET(prob, 0x630, float) = GLerp(STRUCT_OFFSET(prob, 0x5a4, float), STRUCT_OFFSET(prob, 0x5ac, float), u1);
    float u2 = GLimitLmInl(&g_lmZeroOne, GEvaluateClq(&STRUCT_OFFSET(prob, 0x5d0, CLQ), rRoc));
    STRUCT_OFFSET(prob, 0x638, float) = GLerp(STRUCT_OFFSET(prob, 0x5c0, float), STRUCT_OFFSET(prob, 0x5c8, float), u2);
    STRUCT_OFFSET(prob, 0x63c, float) = GLerp(STRUCT_OFFSET(prob, 0x5c4, float), STRUCT_OFFSET(prob, 0x5cc, float), u2);
    float u3 = GLimitLmInl(&g_lmZeroOne, GEvaluateClq(&STRUCT_OFFSET(prob, 0x5f0, CLQ), rRoc));
    STRUCT_OFFSET(prob, 0x644, float) = GLerp(STRUCT_OFFSET(prob, 0x5e0, float), STRUCT_OFFSET(prob, 0x5e4, float), u3);
    float u4 = GLimitLmInl(&g_lmZeroOne, GEvaluateClq(&STRUCT_OFFSET(prob, 0x610, CLQ), rRoc));
    STRUCT_OFFSET(prob, 0x648, float) = GLerp(STRUCT_OFFSET(prob, 0x600, float), STRUCT_OFFSET(prob, 0x604, float), u4);
    float u5 = GLimitLmInl(&g_lmZeroOne, GEvaluateClq(&STRUCT_OFFSET(prob, 0x570, CLQ), rRoc));
    int cRoc = (int)GLerp(STRUCT_OFFSET(prob, 0x560, float), STRUCT_OFFSET(prob, 0x564, float), u5);
    int cRocOld = STRUCT_OFFSET(prob, 0x624, int);
    if (cRocOld < cRoc && STRUCT_OFFSET(prob, 0x380, int) == cRocOld)
    {
        STRUCT_OFFSET(prob, 0x634, float) =
            g_clock.t + GRandInRange(STRUCT_OFFSET(prob, 0x62c, float), STRUCT_OFFSET(prob, 0x630, float));
    }
    STRUCT_OFFSET(prob, 0x624, int) = cRoc;
    float u6 = GLimitLmInl(&g_lmZeroOne, GEvaluateClq(&STRUCT_OFFSET(prob, 0x590, CLQ), rRoc));
    int cRoh = (int)GLerp(STRUCT_OFFSET(prob, 0x580, float), STRUCT_OFFSET(prob, 0x584, float), u6);
    int cRohOld = STRUCT_OFFSET(prob, 0x628, int);
    if (cRohOld < cRoh && STRUCT_OFFSET(prob, 0x39c, int) == cRohOld)
    {
        STRUCT_OFFSET(prob, 0x640, float) =
            g_clock.t + GRandInRange(STRUCT_OFFSET(prob, 0x638, float), STRUCT_OFFSET(prob, 0x63c, float));
    }
    STRUCT_OFFSET(prob, 0x628, int) = cRoh;
}

void DestroyedRobRoc(ROB *prob, ROC *proc)
{
    STRUCT_OFFSET(prob, 0x3c4, int) += 1;
    AdjustRobDifficulty(
        prob, (float)STRUCT_OFFSET(prob, 0x3c4, int) / (float)STRUCT_OFFSET(prob, 0x3b8, int));
    if (STRUCT_OFFSET(proc, 0x55c, ROH *))
    {
        RemoveDlEntry(&STRUCT_OFFSET(prob, 0x35c, DL), proc);
    }
    else
    {
        RemoveDlEntry(&STRUCT_OFFSET(prob, 0x368, DL), proc);
    }
    AppendDlEntry(&STRUCT_OFFSET(prob, 0x374, DL), proc);
    if (STRUCT_OFFSET(proc, 0x55c, ROH *))
    {
        if (FChooseRobRoc(prob, STRUCT_OFFSET(proc, 0x55c, ROH *)))
        {
            SetRohRohs(STRUCT_OFFSET(proc, 0x55c, ROH *), ROHS_Collect);
        }
        else
        {
            STRUCT_OFFSET(STRUCT_OFFSET(proc, 0x55c, ROH *), 0x55c, ROC *) = 0;
            SetRohRohs(STRUCT_OFFSET(proc, 0x55c, ROH *), ROHS_Wander);
        }
    }
    STRUCT_OFFSET(proc, 0x55c, ROH *) = 0;
    proc->pvtlo->pfnRemoveLo(proc);
    if (STRUCT_OFFSET(prob, 0x380, int) == STRUCT_OFFSET(prob, 0x624, int))
    {
        STRUCT_OFFSET(prob, 0x634, float) =
            g_clock.t + GRandInRange(STRUCT_OFFSET(prob, 0x62c, float), STRUCT_OFFSET(prob, 0x630, float));
    }
    STRUCT_OFFSET(prob, 0x380, int) -= 1;
}

void SpawnedRobRoh(ROB *prob, ROH *proh)
{
    RemoveDlEntry(&STRUCT_OFFSET(prob, 0x3ac, DL), STRUCT_OFFSET(proh, 0x560, ROST *));
    AppendDlEntry(&STRUCT_OFFSET(prob, 0x3a0, DL), STRUCT_OFFSET(proh, 0x560, ROST *));
    SetRostRosts(STRUCT_OFFSET(proh, 0x560, ROST *), ROSTS_Close);
    STRUCT_OFFSET(proh, 0x560, ROST *) = 0;
}

void GrabbedRobRoh(ROB *prob, ROH *proh)
{
#define ALO_ROH STRUCT_OFFSET(proh, 0x55c, ALO *)
    ALO_ROH->pvtalo->pfnSetAloParent(ALO_ROH);
    ALO_ROH->pvtalo->pfnSetAloVelocityVec(ALO_ROH, &g_vecZero);
    ALO_ROH->pvtalo->pfnSetAloAngularVelocityVec(ALO_ROH, &g_vecZero);
    SetSoConstraints((SO *)ALO_ROH, CT_Locked, 0, CT_Locked, 0);
#undef ALO_ROH
    StartSound((SFXID)0x151, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
}

void DroppedRobRoh(ROB *prob, ROH *proh)
{
    ALO *palo = STRUCT_OFFSET(proh, 0x55c, ALO *);
    SetAloParentVt(palo, 0);
    palo->pvtalo->pfnSetAloVelocityVec(palo, &g_vecZero);
    palo->pvtalo->pfnSetAloAngularVelocityVec(palo, &g_vecZero);
    SetSoConstraints((SO *)palo, CT_Project, &g_normalZ, CT_Locked, 0);
}

void ReturnedRobRoh(ROB *prob, ROH *proh)
{
    SetRostRosts(STRUCT_OFFSET(proh, 0x560, ROST *), ROSTS_Open);
}

void ExitedRobRoh(ROB *prob, ROH *proh)
{
    STRUCT_OFFSET(prob, 0x3c0, int) += 1;
    RemoveDlEntry(&STRUCT_OFFSET(prob, 0x35c, DL), STRUCT_OFFSET(proh, 0x55c, SO *));
    AppendDlEntry(&STRUCT_OFFSET(prob, 0x374, DL), STRUCT_OFFSET(proh, 0x55c, SO *));
    RemoveDlEntry(&STRUCT_OFFSET(prob, 0x384, DL), proh);
    AppendDlEntry(&STRUCT_OFFSET(prob, 0x390, DL), proh);
    RemoveDlEntry(&STRUCT_OFFSET(prob, 0x3ac, DL), STRUCT_OFFSET(proh, 0x560, ROST *));
    AppendDlEntry(&STRUCT_OFFSET(prob, 0x3a0, DL), STRUCT_OFFSET(proh, 0x560, ROST *));
    SetAloParentVt(STRUCT_OFFSET(proh, 0x55c, ALO *), 0);
    STRUCT_OFFSET(proh, 0x55c, ALO *)->pvtlo->pfnRemoveLo(STRUCT_OFFSET(proh, 0x55c, ALO *));
    proh->pvtlo->pfnRemoveLo(proh);
    SetRostRosts(STRUCT_OFFSET(proh, 0x560, ROST *), ROSTS_Close);
    ALO *palo = STRUCT_OFFSET(proh, 0x55c, ALO *);
    STRUCT_OFFSET(proh, 0x560, ROST *) = 0;
    STRUCT_OFFSET(palo, 0x55c, ROH *) = 0;
    STRUCT_OFFSET(proh, 0x55c, ALO *) = 0;
    if (STRUCT_OFFSET(prob, 0x380, int) == STRUCT_OFFSET(prob, 0x624, int))
    {
        STRUCT_OFFSET(prob, 0x634, float) =
            g_clock.t + GRandInRange(STRUCT_OFFSET(prob, 0x62c, float), STRUCT_OFFSET(prob, 0x630, float));
    }
    STRUCT_OFFSET(prob, 0x380, int) -= 1;
    if (STRUCT_OFFSET(prob, 0x39c, int) == STRUCT_OFFSET(prob, 0x628, int))
    {
        STRUCT_OFFSET(prob, 0x640, float) =
            g_clock.t + GRandInRange(STRUCT_OFFSET(prob, 0x638, float), STRUCT_OFFSET(prob, 0x63c, float));
    }
    STRUCT_OFFSET(prob, 0x39c, int) -= 1;
    StartSound((SFXID)0x51, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
}

void KilledRobRoh(ROB *prob, ROH *proh)
{
    RemoveDlEntry(&STRUCT_OFFSET(prob, 0x384, DL), proh);
    AppendDlEntry(&STRUCT_OFFSET(prob, 0x390, DL), proh);
    if (STRUCT_OFFSET(proh, 0x560, ROST *))
    {
        RemoveDlEntry(&STRUCT_OFFSET(prob, 0x3ac, DL), STRUCT_OFFSET(proh, 0x560, ROST *));
        AppendDlEntry(&STRUCT_OFFSET(prob, 0x3a0, DL), STRUCT_OFFSET(proh, 0x560, ROST *));
        SetRostRosts(STRUCT_OFFSET(proh, 0x560, ROST *), ROSTS_Close);
    }
    ROC *proc = STRUCT_OFFSET(proh, 0x55c, ROC *);
    if (proc)
    {
        if (STRUCT_OFFSET(proc, 0x18, ROH *) == proh)
        {
            DroppedRobRoh(prob, proh);
        }
        RemoveDlEntry(&STRUCT_OFFSET(prob, 0x35c, DL), proc);
        AppendDlEntry(&STRUCT_OFFSET(prob, 0x368, DL), proc);
        if (!FChooseRobRoh(prob, proc))
        {
            STRUCT_OFFSET(proc, 0x55c, ROH *) = 0;
        }
    }
    STRUCT_OFFSET(proh, 0x560, ROST *) = 0;
    STRUCT_OFFSET(proh, 0x55c, ROC *) = 0;
    proh->pvtlo->pfnRemoveLo(proh);
    if (STRUCT_OFFSET(prob, 0x39c, int) == STRUCT_OFFSET(prob, 0x628, int))
    {
        STRUCT_OFFSET(prob, 0x640, float) =
            g_clock.t + GRandInRange(STRUCT_OFFSET(prob, 0x638, float), STRUCT_OFFSET(prob, 0x63c, float));
    }
    STRUCT_OFFSET(prob, 0x39c, int) -= 1;
}

INCLUDE_ASM("asm/nonmatchings/P2/rog", FChooseRobRoc__FP3ROBP3ROH);

void TakeRobRoc(ROB *prob, ROH *proh, ROC *proc)
{
    ROC *procOld = STRUCT_OFFSET(proh, 0x55c, ROC *);
    if (procOld && procOld == proc)
    {
        return;
    }
    ROH *prohOld = STRUCT_OFFSET(proc, 0x55c, ROH *);
    STRUCT_OFFSET(proh, 0x55c, ROC *) = proc;
    STRUCT_OFFSET(proc, 0x55c, ROH *) = proh;
    if (!prohOld)
    {
        RemoveDlEntry(&STRUCT_OFFSET(prob, 0x368, DL), proc);
        AppendDlEntry(&STRUCT_OFFSET(prob, 0x35c, DL), proc);
    }
    if (procOld)
    {
        RemoveDlEntry(&STRUCT_OFFSET(prob, 0x35c, DL), procOld);
        AppendDlEntry(&STRUCT_OFFSET(prob, 0x368, DL), procOld);
        STRUCT_OFFSET(procOld, 0x55c, ROH *) = 0;
        FChooseRobRoh(prob, procOld);
    }
    if (prohOld)
    {
        STRUCT_OFFSET(prohOld, 0x55c, ROC *) = 0;
        SetRohRohs(prohOld, ROHS_Wander);
        if (FChooseRobRoc(prob, prohOld))
        {
            SetRohRohs(prohOld, ROHS_Collect);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/rog", FChooseRobRoh__FP3ROBP3ROC);

INCLUDE_ASM("asm/nonmatchings/P2/rog", FChooseRobReturnPoint__FP3ROBP3ROH);

INCLUDE_ASM("asm/nonmatchings/P2/rog", ChooseRobWanderLocation__FP3ROBP3ROH);

RODD *ProddCurRob(ROB *prob, ENSK ensk)
{
    return &STRUCT_OFFSET(prob, 0x3e0, RODD) + STRUCT_OFFSET(prob, 0x620, int);
}

void InitRoh(ROH *proh)
{
    InitSo(proh);
    STRUCT_OFFSET(proh, 0x550, ROHS) = ROHS_Nil; // proh->rohs
    STRUCT_OFFSET(proh, 0x584, float) = 1.0f;
    STRUCT_OFFSET(proh, 0x588, float) = 2.5f;
    SetSoConstraints(proh, CT_Tangent, &g_normalZ, CT_Project, &g_normalZ);
}

void LoadRohFromBrx(ROH *proh, CBinaryInputStream *pbis)
{
    LoadSoFromBrx(proh, pbis);
    SnipAloObjects(proh, 6, s_asnipLoadRoh);
    InferExpl(&STRUCT_OFFSET(proh, 0x5ac, EXPL *), proh);
}

void CloneRoh(ROH *proh, ROH *prohBase)
{
    W2 w = STRUCT_OFFSET(proh, 0x5b0, W2);
    CloneSo(proh, prohBase);
    STRUCT_OFFSET(proh, 0x5b0, W2) = w;
}

void PostRohLoad(ROH *proh)
{
    PostAloLoad(proh);
    SetRohRohs(proh, ROHS_Inactive);
    proh->pvtlo->pfnRemoveLo(proh);
}

INCLUDE_ASM("asm/nonmatchings/P2/rog", UpdateRoh__FP3ROHf);

INCLUDE_ASM("asm/nonmatchings/P2/rog", MoveRohToTarget__FP3ROHP6VECTORi);

INCLUDE_ASM("asm/nonmatchings/P2/rog", RohsNextRoh__FP3ROH);

struct OVR // guess
{
    OID oid;
    ALO *palo;
};
void SetRohRohs(ROH *proh, ROHS rohs)
{
    ROHS rohsPrev = STRUCT_OFFSET(proh, 0x550, ROHS);
    if (rohsPrev == rohs)
    {
        return;
    }
    if (STRUCT_OFFSET(proh, 0x59c, ASEGA *))
    {
        RetractAsega(STRUCT_OFFSET(proh, 0x59c, ASEGA *));
        STRUCT_OFFSET(proh, 0x59c, ASEGA *) = 0;
    }
    if (STRUCT_OFFSET(proh, 0x5a8, SMA *))
    {
        RetractSma(STRUCT_OFFSET(proh, 0x5a8, SMA *));
        STRUCT_OFFSET(proh, 0x5a8, SMA *) = 0;
    }
    switch (STRUCT_OFFSET(proh, 0x550, ROHS))
    {
    case ROHS_Spawn:
        SpawnedRobRoh(STRUCT_OFFSET(proh, 0x558, ROB *), proh);
        break;
    case ROHS_Return:
        if (rohs == ROHS_Exit)
        {
            ReturnedRobRoh(STRUCT_OFFSET(proh, 0x558, ROB *), proh);
        }
        break;
    case ROHS_Exit:
        if (rohs == ROHS_Inactive)
        {
            ExitedRobRoh(STRUCT_OFFSET(proh, 0x558, ROB *), proh);
        }
        break;
    case ROHS_Die:
        KilledRobRoh(STRUCT_OFFSET(proh, 0x558, ROB *), proh);
        break;
    }
    STRUCT_OFFSET(proh, 0x550, ROHS) = rohs;
    STRUCT_OFFSET(proh, 0x554, float) = g_clock.t;
    ASEG *paseg = 0;
    SM *psm = 0;
    OVR aovr[2];
    OVR *povr = aovr;
    switch (rohs)
    {
    case ROHS_Inactive:
    case ROHS_Dead:
        break;
    case ROHS_Spawn:
    case ROHS_Wander:
    case ROHS_Collect:
        paseg = STRUCT_OFFSET(proh, 0x58c, ASEG *);
        break;
    case ROHS_Grab:
        GrabbedRobRoh(STRUCT_OFFSET(proh, 0x558, ROB *), proh);
        povr->oid = (OID)0x2a0;
        povr->palo = STRUCT_OFFSET(proh, 0x55c, ALO *);
        povr++;
        paseg = STRUCT_OFFSET(proh, 0x594, ASEG *);
        break;
    case ROHS_Return:
    case ROHS_Exit:
        povr->oid = (OID)0x2a0;
        povr->palo = STRUCT_OFFSET(proh, 0x55c, ALO *);
        povr++;
        paseg = STRUCT_OFFSET(proh, 0x590, ASEG *);
        break;
    case ROHS_Happy:
        psm = STRUCT_OFFSET(proh, 0x5a0, SM *);
        break;
    case ROHS_Sad:
        psm = STRUCT_OFFSET(proh, 0x5a4, SM *);
        break;
    case ROHS_Die:
        paseg = STRUCT_OFFSET(proh, 0x598, ASEG *);
        break;
    }
    if (paseg)
    {
        ApplyAsegOvr(paseg, proh, povr - aovr, aovr, 0.0f, 1.0f, 1, &STRUCT_OFFSET(proh, 0x59c, ASEGA *));
    }
    if (psm)
    {
        STRUCT_OFFSET(proh, 0x5a8, SMA *) = PsmaApplySm(psm, proh, (OID)-1, 1);
    }
}

int FAbsorbRohWkr(ROH *proh, WKR *pwkr)
{
    if (STRUCT_OFFSET(pwkr, 0xc, uint) & 0x20)
    {
        switch (STRUCT_OFFSET(proh, 0x550, ROHS))
        {
        case ROHS_Spawn:
        case ROHS_Wander:
        case ROHS_Collect:
        case ROHS_Grab:
        case ROHS_Return:
        case ROHS_Happy:
        case ROHS_Sad:
            SetRohRohs(proh, ROHS_Die);
            break;
        case ROHS_Exit:
        {
            ROC *proc = STRUCT_OFFSET(proh, 0x55c, ROC *);
            SetRohRohs(proh, ROHS_Die);
            if (proc)
            {
                SetRocRocs(proc, ROCS_Destroyed);
            }
            break;
        }
        }
        if (STRUCT_OFFSET(proh, 0x550, ROHS) == ROHS_Die)
        {
            ALO *palo = STRUCT_OFFSET(proh, 0x5ac, ALO *);
            if (palo)
            {
                struct
                {
                    int msgid;
                    int pad[3];
                    VECTOR vecA;
                    VECTOR vecB;
                    int pad2[8];
                } msg;
                msg.msgid = 6;
                STRUCT_OFFSET(&msg, 0x10, qword) = STRUCT_OFFSET(pwkr, 0x30, qword);
                STRUCT_OFFSET(&msg, 0x20, qword) = STRUCT_OFFSET(pwkr, 0x20, qword);
                msg.vecA.z += 3000.0f;
                ((void (*)(ALO *, void *))STRUCT_OFFSET(palo->pvtalo, 0x7c, void *))(palo, &msg);
            }
            StartSound((SFXID)0x37, 0, 0, &STRUCT_OFFSET(pwkr, 0x20, VECTOR), 12000.0f, 8000.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        }
    }
    return STRUCT_OFFSET(pwkr, 0xc, uint) != 0;
}

ROC *ProcContactRoh(ROH *proh)
{
    void *pv = *STRUCT_OFFSET(proh, 0x480, void **);
    for (; pv; pv = STRUCT_OFFSET(pv, 0x4, void *))
    {
        if (STRUCT_OFFSET(pv, 0x0, int) && FIsBasicDerivedFrom(STRUCT_OFFSET(pv, 0xc, BASIC *), (CID)0x43))
        {
            return STRUCT_OFFSET(pv, 0xc, ROC *);
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/rog", InitRoc__FP3ROC);

void LoadRocFromBrx(ROC *proc, CBinaryInputStream *pbis)
{
    LoadSoFromBrx(proc, pbis);
    SnipAloObjects(proc, 1, s_asnipLoadRoc);
    InferExpl(&STRUCT_OFFSET(proc, 0x574, EXPL *), proc);
}

void CloneRoc(ROC *proc, ROC *procBase)
{
    W2 w = STRUCT_OFFSET(proc, 0x5a0, W2);
    CloneSo(proc, procBase);
    STRUCT_OFFSET(proc, 0x5a0, W2) = w;
}

void PostRocLoad(ROC *proc)
{
    PostAloLoad(proc);
    SnipAloObjects(proc, 1, s_asnipPostRoc);
    void *pv = STRUCT_OFFSET(proc, 0x578, void *);
    if (pv)
    {
        STRUCT_OFFSET(proc, 0x57c, W2) = STRUCT_OFFSET(pv, 0x2dc, W2);
    }
    if (STRUCT_OFFSET(proc, 0x560, SM *))
    {
        STRUCT_OFFSET(proc, 0x564, SMA *) = PsmaApplySm(STRUCT_OFFSET(proc, 0x560, SM *), proc, OID_Nil, 0);
    }
    SetRocRocs(proc, ROCS_Rest);
    proc->pvtlo->pfnRemoveLo(proc);
}

void UpdateRoc(ROC *proc, float dt)
{
    ROCS rocs;
    UpdateSo(proc, dt);
    while ((rocs = RocsNextRoc(proc)) != STRUCT_OFFSET(proc, 0x550, ROCS))
    {
        SetRocRocs(proc, rocs);
    }
    if (STRUCT_OFFSET(proc, 0x578, EMITTER *))
    {
        float g = -STRUCT_OFFSET(proc, 0x158, float);
        if (g > 0.0001f)
        {
            UnpauseEmitter(STRUCT_OFFSET(proc, 0x578, EMITTER *));
            LM *plm = &g_lmZeroOne;
            float u = GLimitLmInl(plm, GEvaluateClq(&STRUCT_OFFSET(proc, 0x590, CLQ), g));
            float gA = STRUCT_OFFSET(proc, 0x57c, float) * u;
            float gB = STRUCT_OFFSET(proc, 0x580, float) * u;
            void *pemitter = STRUCT_OFFSET(proc, 0x578, void *);
            STRUCT_OFFSET(pemitter, 0x2dc, float) = gA;
            STRUCT_OFFSET(pemitter, 0x2e0, float) = gB;
        }
        else
        {
            PauseEmitterIndefinite(STRUCT_OFFSET(proc, 0x578, EMITTER *));
        }
    }
}

void PresetRocAccel(ROC *proc, float dt)
{
    MATRIX3 mat;
    PresetSoAccel(proc, dt);
    if (STRUCT_OFFSET(proc, 0x18, int) == 0)
    {
        TiltMatUpright(&STRUCT_OFFSET(proc, 0x110, MATRIX3), 0, &mat);
        AccelSoTowardMatSmooth(proc, g_clock.dt, &mat, &s_smpRocAccel);
    }
}

void AdjustRocNewXp(ROC *proc, XP *pxp, int ixpd)
{
    STRUCT_OFFSET(pxp, 0x98, float) *= 0.6f;
}

INCLUDE_ASM("asm/nonmatchings/P2/rog", FAbsorbRocWkr__FP3ROCP3WKR);

ROCS RocsNextRoc(ROC *proc)
{
    ROCS rocs = STRUCT_OFFSET(proc, 0x550, ROCS);
    switch (rocs)
    {
    case ROCS_Hit1:
    case ROCS_Hit2:
    case ROCS_Hit3:
    case ROCS_Hit4:
    case ROCS_Hit5:
    case ROCS_Hit6:
    case ROCS_Hit7:
    case ROCS_Hit8:
        if (g_clock.t - STRUCT_OFFSET(proc, 0x554, float) > STRUCT_OFFSET(proc, 0x56c, float))
        {
            rocs = (ROCS)(rocs - 1);
        }
        break;
    case ROCS_Destroyed:
        rocs = ROCS_Rest;
        break;
    }
    return rocs;
}

void SetRocRocs(ROC *proc, ROCS rocs)
{
    ROCS rocsPrev = STRUCT_OFFSET(proc, 0x550, ROCS);
    if (rocs != rocsPrev)
    {
        if (rocsPrev == ROCS_Destroyed)
        {
            DestroyedRobRoc(STRUCT_OFFSET(proc, 0x558, ROB *), proc);
        }
        STRUCT_OFFSET(proc, 0x550, ROCS) = rocs;
        SMA *psma = STRUCT_OFFSET(proc, 0x564, SMA *);
        STRUCT_OFFSET(proc, 0x554, float) = g_clock.t;
        if (psma)
        {
            OID oid = s_mpmpocsoidRoc[rocs];
            if (rocsPrev == ROCS_Nil)
            {
                SeekSma(psma, oid);
            }
            else
            {
                SetSmaGoal(psma, oid);
            }
        }
    }
}

void InitRost(ROST *prost)
{
    InitSo(prost);
    STRUCT_OFFSET(prost, 0x550, ROSTS) = ROSTS_Nil; // prost->rosts
}

void LoadRostFromBrx(ROST *prost, CBinaryInputStream *pbis)
{
    LoadSoFromBrx(prost, pbis);
    SnipAloObjects(prost, 1, s_asnipLoadRost);
}

void CloneRost(ROST *prost, ROST *prostBase)
{
    W2 w = STRUCT_OFFSET(prost, 0x568, W2);
    CloneSo(prost, prostBase);
    STRUCT_OFFSET(prost, 0x568, W2) = w;
}

void PostRostLoad(ROST *prost)
{
    int pad[4]; // pad forces frame size
    PostAloLoad(prost);
    if (STRUCT_OFFSET(prost, 0x55c, SM *))
    {
        STRUCT_OFFSET(prost, 0x560, SMA *) = PsmaApplySm(STRUCT_OFFSET(prost, 0x55c, SM *), prost, OID_Nil, 1);
    }
    for (BASIC *pbasic = STRUCT_OFFSET(prost, 0x34, BASIC *); pbasic; pbasic = STRUCT_OFFSET(pbasic, 0x1c, BASIC *))
    {
        if (FIsBasicDerivedFrom(pbasic, (CID)0x7e))
        {
            STRUCT_OFFSET(prost, 0x564, BASIC *) = pbasic;
            break;
        }
    }
    SetRostRosts(prost, ROSTS_Close);
}

void UpdateRost(ROST *prost, float dt)
{
    ROSTS rosts;
    UpdateSo(prost, dt);
    while ((rosts = RostsNextRost(prost)) != STRUCT_OFFSET(prost, 0x550, ROSTS))
    {
        SetRostRosts(prost, rosts);
    }
}

ROSTS RostsNextRost(ROST *prost)
{
    return STRUCT_OFFSET(prost, 0x550, ROSTS);
}

void SetRostRosts(ROST *prost, ROSTS rosts)
{
    ROSTS rostsPrev = STRUCT_OFFSET(prost, 0x550, ROSTS);
    if (rostsPrev != rosts)
    {
        STRUCT_OFFSET(prost, 0x550, ROSTS) = rosts;
        SMA *psma = STRUCT_OFFSET(prost, 0x560, SMA *);
        STRUCT_OFFSET(prost, 0x554, float) = g_clock.t;
        if (psma)
        {
            OID oid = s_mpmpostoidRost[rosts];
            if (rostsPrev == ROSTS_Nil)
            {
                SeekSma(psma, oid);
            }
            else
            {
                SetSmaGoal(psma, oid);
            }
        }
    }
}

void InitRop(ROP *prop)
{
    InitSo(prop);
    STRUCT_OFFSET(prop, 0x550, ROPS) = ROPS_Nil; // prop->rops
    SetSoConstraints(prop, CT_Locked, 0, CT_Locked, 0);
}

INCLUDE_ASM("asm/nonmatchings/P2/rog", LoadRopFromBrx__FP3ROPP18CBinaryInputStream);

void PostRopLoad(ROP *prop)
{
    PostAloLoad(prop);
    if (STRUCT_OFFSET(prop, 0x558, int) == 0)
    {
        prop->pvtlo->pfnRemoveLo(prop);
    }
    else
    {
        STRUCT_OFFSET(prop, 0x55c, LO *) = PloFindSwObjectByClass(
            STRUCT_OFFSET(prop, 0x14, SW *), (GRFFSO)0x101, (CID)0x59, STRUCT_OFFSET(prop, 0x34, LO *));
        SetRopRops(prop, ROPS_StayPut);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/rog", UpdateRop__FP3ROPf);

INCLUDE_ASM("asm/nonmatchings/P2/rog", SetRopRops__FP3ROP4ROPS);

ROPS RopsNextRop(ROP *prop)
{
    ROPS rops = STRUCT_OFFSET(prop, 0x550, ROPS);
    switch (rops)
    {
    case ROPS_StayPut:
        break;
    case ROPS_Reveal:
    {
        void *pv = STRUCT_OFFSET(prop, 0x564, void *);
        if (pv == 0 || STRUCT_OFFSET(STRUCT_OFFSET(pv, 0x8, void *), 0x34, float) <= STRUCT_OFFSET(pv, 0x14, float))
        {
            rops = ROPS_Collect;
        }
    }
    case ROPS_Collect:
        if ((uint)g_plsCur->fls & FLS_KeyCollected)
        {
            rops = ROPS_Collected;
        }
        break;
    }
    return rops;
}
