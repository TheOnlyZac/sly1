#include <rog.h>
#include <cm.h>
#include <clock.h>
#include <mat.h>
#include <dl.h>
#include <emitter.h>

extern SNIP s_asnipLoadRov[2];
extern SNIP s_asnipLoadRoh[6];
extern SNIP s_asnipLoadRoc[1];
extern SNIP s_asnipLoadRost[1];
extern SMP s_smpRovAccel; // guess
extern SMP s_smpRocAccel; // guess
extern VECTOR g_normalZ;

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

INCLUDE_ASM("asm/nonmatchings/P2/rog", PostRovLoad__FP3ROV);

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

INCLUDE_ASM("asm/nonmatchings/P2/rog", RovsNextRov__FP3ROV);

INCLUDE_ASM("asm/nonmatchings/P2/rog", SetRovRovs__FP3ROV4ROVS);

INCLUDE_ASM("asm/nonmatchings/P2/rog", RovtsNextRov__FP3ROV);

INCLUDE_ASM("asm/nonmatchings/P2/rog", SetRovRovts__FP3ROV5ROVTS);

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

INCLUDE_ASM("asm/nonmatchings/P2/rog", DestroyedRobRoc__FP3ROBP3ROC);

void SpawnedRobRoh(ROB *prob, ROH *proh)
{
    RemoveDlEntry(&STRUCT_OFFSET(prob, 0x3ac, DL), STRUCT_OFFSET(proh, 0x560, ROST *));
    AppendDlEntry(&STRUCT_OFFSET(prob, 0x3a0, DL), STRUCT_OFFSET(proh, 0x560, ROST *));
    SetRostRosts(STRUCT_OFFSET(proh, 0x560, ROST *), ROSTS_Close);
    STRUCT_OFFSET(proh, 0x560, ROST *) = 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/rog", GrabbedRobRoh__FP3ROBP3ROH);

INCLUDE_ASM("asm/nonmatchings/P2/rog", DroppedRobRoh__FP3ROBP3ROH);

void ReturnedRobRoh(ROB *prob, ROH *proh)
{
    SetRostRosts(STRUCT_OFFSET(proh, 0x560, ROST *), ROSTS_Open);
}

INCLUDE_ASM("asm/nonmatchings/P2/rog", ExitedRobRoh__FP3ROBP3ROH);

INCLUDE_ASM("asm/nonmatchings/P2/rog", KilledRobRoh__FP3ROBP3ROH);

INCLUDE_ASM("asm/nonmatchings/P2/rog", FChooseRobRoc__FP3ROBP3ROH);

INCLUDE_ASM("asm/nonmatchings/P2/rog", TakeRobRoc__FP3ROBP3ROHP3ROC);

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
    // vtable slot 0x1c (name unconfirmed)
    (*(void (**)(ROH *))(*(int *)proh + 0x1c))(proh);
}

INCLUDE_ASM("asm/nonmatchings/P2/rog", UpdateRoh__FP3ROHf);

INCLUDE_ASM("asm/nonmatchings/P2/rog", MoveRohToTarget__FP3ROHP6VECTORi);

INCLUDE_ASM("asm/nonmatchings/P2/rog", RohsNextRoh__FP3ROH);

INCLUDE_ASM("asm/nonmatchings/P2/rog", SetRohRohs__FP3ROH4ROHS);

INCLUDE_ASM("asm/nonmatchings/P2/rog", FAbsorbRohWkr__FP3ROHP3WKR);

INCLUDE_ASM("asm/nonmatchings/P2/rog", ProcContactRoh__FP3ROH);

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

INCLUDE_ASM("asm/nonmatchings/P2/rog", PostRocLoad__FP3ROC);

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

INCLUDE_ASM("asm/nonmatchings/P2/rog", RocsNextRoc__FP3ROC);

INCLUDE_ASM("asm/nonmatchings/P2/rog", SetRocRocs__FP3ROC4ROCS);

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

INCLUDE_ASM("asm/nonmatchings/P2/rog", CloneRost__FP4ROSTT0);

INCLUDE_ASM("asm/nonmatchings/P2/rog", PostRostLoad__FP4ROST);

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

INCLUDE_ASM("asm/nonmatchings/P2/rog", SetRostRosts__FP4ROST5ROSTS);

void InitRop(ROP *prop)
{
    InitSo(prop);
    STRUCT_OFFSET(prop, 0x550, ROPS) = ROPS_Nil; // prop->rops
    SetSoConstraints(prop, CT_Locked, 0, CT_Locked, 0);
}

INCLUDE_ASM("asm/nonmatchings/P2/rog", LoadRopFromBrx__FP3ROPP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/rog", PostRopLoad__FP3ROP);

INCLUDE_ASM("asm/nonmatchings/P2/rog", UpdateRop__FP3ROPf);

INCLUDE_ASM("asm/nonmatchings/P2/rog", SetRopRops__FP3ROP4ROPS);

INCLUDE_ASM("asm/nonmatchings/P2/rog", RopsNextRop__FP3ROP);
