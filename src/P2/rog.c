#include <rog.h>
#include <cm.h>
#include <clock.h>
#include <mat.h>
#include <dl.h>
#include <emitter.h>
#include <sm.h>
#include <find.h>
#include <basic.h>
#include <game.h>

extern SNIP s_asnipLoadRov[2];
extern SNIP s_asnipPostRov[6];
extern SNIP s_asnipLoadRoh[6];
extern SNIP s_asnipLoadRoc[1];
extern SNIP s_asnipPostRoc[1];
extern SNIP s_asnipLoadRost[1];
extern SMP s_smpRovAccel; // guess
extern SMP s_smpRocAccel; // guess
extern VECTOR g_normalZ;
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

INCLUDE_ASM("asm/nonmatchings/P2/rog", UpdateRovActive__FP3ROVP3JOYf);

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

INCLUDE_ASM("asm/nonmatchings/P2/rog", SetRovRovs__FP3ROV4ROVS);

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

INCLUDE_ASM("asm/nonmatchings/P2/rog", HandleRovMessage__FP3ROV5MSGIDPv);

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

INCLUDE_ASM("asm/nonmatchings/P2/rog", PropagateRovForce__FP3ROViP2XPiP2DZP2FX);

int FIsRovSoundBase(ROV *prov)
{
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/rog", InitRob__FP3ROB);

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
 * @brief 80% match.
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

INCLUDE_ASM("asm/nonmatchings/P2/rog", PostRobLoad__FP3ROB);

INCLUDE_ASM("asm/nonmatchings/P2/rog", UpdateRob__FP3ROBf);

INCLUDE_ASM("asm/nonmatchings/P2/rog", FUN_001a4d60);

INCLUDE_ASM("asm/nonmatchings/P2/rog", RobsNextRob__FP3ROB);

INCLUDE_ASM("asm/nonmatchings/P2/rog", SetRobRobs__FP3ROB4ROBS);

INCLUDE_ASM("asm/nonmatchings/P2/rog", AddRobRoc__FP3ROB);

INCLUDE_ASM("asm/nonmatchings/P2/rog", AddRobRoh__FP3ROB);

INCLUDE_ASM("asm/nonmatchings/P2/rog", AdjustRobDifficulty__FP3ROBf);

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

INCLUDE_ASM("asm/nonmatchings/P2/rog", SetRohRohs__FP3ROH4ROHS);

INCLUDE_ASM("asm/nonmatchings/P2/rog", FAbsorbRohWkr__FP3ROHP3WKR);

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

INCLUDE_ASM("asm/nonmatchings/P2/rog", UpdateRoc__FP3ROCf);

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
