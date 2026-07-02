#include <rog.h>
#include <cm.h>
#include <game.h>
#include <emitter.h>
#include <dl.h>
#include <find.h>
#include <util.h>
#include <vec.h>
#include <screen.h>

extern SNIP s_asnipLoadRov[2];

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
    default:
        break;
    }

    return rovts;
}

INCLUDE_ASM("asm/nonmatchings/P2/rog", SetRovRovts__FP3ROV5ROVTS);

INCLUDE_ASM("asm/nonmatchings/P2/rog", HandleRovMessage__FP3ROV5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/rog", PresetRovAccel__FP3ROVf);

INCLUDE_ASM("asm/nonmatchings/P2/rog", AdjustRovXpVelocity__FP3ROVP2XPi);

void AdjustRovNewXp(ROV *prov, XP *pxp, int ixpd)
{
    if (FDrivenAlo(prov))
        return;

    if (0.7f < STRUCT_OFFSET(pxp, 0x88, float))
        STRUCT_OFFSET(pxp, 0x94, float) = 20.0f;
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

ROBK RobkCur()
{
    int grfrob = *(int *)g_plsCur;
    if ((grfrob & 0x4) == 0)
        return (ROBK)((grfrob & 0x2) > 0);
    return ROBK_Tertiary;
}

INCLUDE_ASM("asm/nonmatchings/P2/rog", BindRob__FP3ROB);

INCLUDE_ASM("asm/nonmatchings/P2/rog", PostRobLoad__FP3ROB);

INCLUDE_ASM("asm/nonmatchings/P2/rog", UpdateRob__FP3ROBf);

extern int FUN_001e9970();
extern BLOT g_unkblot0;

void FUN_001a4d60(ROB *prob)
{
    int fShow = 0;
    if (STRUCT_OFFSET(prob, 0x650, int) == 2)
    {
        fShow = FUN_001e9970();
    }

    if (fShow)
    {
        g_unkblot0.pvtblot->pfnShowBlot(&g_unkblot0);
    }
    else
    {
        g_unkblot0.pvtblot->pfnHideBlot(&g_unkblot0);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/rog", RobsNextRob__FP3ROB);

INCLUDE_ASM("asm/nonmatchings/P2/rog", SetRobRobs__FP3ROB4ROBS);

INCLUDE_ASM("asm/nonmatchings/P2/rog", AddRobRoc__FP3ROB);

INCLUDE_ASM("asm/nonmatchings/P2/rog", AddRobRoh__FP3ROB);

INCLUDE_ASM("asm/nonmatchings/P2/rog", AdjustRobDifficulty__FP3ROBf);

void DestroyedRobRoc(ROB *prob, ROC *proc)
{
    int cRoc = STRUCT_OFFSET(prob, 0x3c4, int) + 1;
    STRUCT_OFFSET(prob, 0x3c4, int) = cRoc;
    AdjustRobDifficulty(prob, (float)cRoc / (float)STRUCT_OFFSET(prob, 0x3b8, int));

    if (STRUCT_OFFSET(proc, 0x55c, ROH *) != NULL)
        RemoveDlEntry(&STRUCT_OFFSET(prob, 0x35c, DL), proc);
    else
        RemoveDlEntry(&STRUCT_OFFSET(prob, 0x368, DL), proc);

    AppendDlEntry(&STRUCT_OFFSET(prob, 0x374, DL), proc);

    if (STRUCT_OFFSET(proc, 0x55c, ROH *) != NULL)
    {
        if (FChooseRobRoc(prob, STRUCT_OFFSET(proc, 0x55c, ROH *)))
        {
            SetRohRohs(STRUCT_OFFSET(proc, 0x55c, ROH *), ROHS_Collect);
        }
        else
        {
            STRUCT_OFFSET(STRUCT_OFFSET(proc, 0x55c, ROH *), 0x55c, ROC *) = NULL;
            SetRohRohs(STRUCT_OFFSET(proc, 0x55c, ROH *), ROHS_Wander);
        }
    }

    STRUCT_OFFSET(proc, 0x55c, ROH *) = NULL;
    // @todo clean up this vtable call
    (*(void (**)(ROC *))((char *)((LO *)proc)->pvtlo + 0x1c))(proc);

    if (STRUCT_OFFSET(prob, 0x380, int) == STRUCT_OFFSET(prob, 0x624, int))
    {
        STRUCT_OFFSET(prob, 0x634, float) =
            g_clock.t + GRandInRange(STRUCT_OFFSET(prob, 0x62c, float), STRUCT_OFFSET(prob, 0x630, float));
    }
    STRUCT_OFFSET(prob, 0x380, int) -= 1;
}

void SpawnedRobRoh(ROB *prob, ROH *proh)
{
    RemoveDlEntry((DL *)&STRUCT_OFFSET(prob, 0x3AC, int), STRUCT_OFFSET(proh, 0x560, ROST *));
    AppendDlEntry((DL *)&STRUCT_OFFSET(prob, 0x3A0, int), STRUCT_OFFSET(proh, 0x560, ROST *));
    SetRostRosts(STRUCT_OFFSET(proh, 0x560, ROST *), ROSTS_Close);
    STRUCT_OFFSET(proh, 0x560, ROST *) = NULL;
}

void GrabbedRobRoh(ROB *prob, ROH *proh)
{
    (*(void (**)(SO *))(*(uint8_t **)STRUCT_OFFSET(proh, 0x55c, SO *) + 0x64))(STRUCT_OFFSET(proh, 0x55c, SO *));
    (*(void (**)(SO *, VECTOR *))(*(uint8_t **)STRUCT_OFFSET(proh, 0x55c, SO *) + 0x90))(STRUCT_OFFSET(proh, 0x55c, SO *), &D_00248D30);
    (*(void (**)(SO *, VECTOR *))(*(uint8_t **)STRUCT_OFFSET(proh, 0x55c, SO *) + 0x94))(STRUCT_OFFSET(proh, 0x55c, SO *), &D_00248D30);
    SetSoConstraints(STRUCT_OFFSET(proh, 0x55c, SO *), CT_Locked, NULL, CT_Locked, NULL);
    StartSound((SFXID)0x151, NULL, NULL, NULL, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, NULL, NULL);
}

void DroppedRobRoh(ROB *prob, ROH *proh)
{

    SO *pso = STRUCT_OFFSET(proh, 0x55c, SO *);

    (*(void (**)(SO *, int))(*(uint8_t **)pso + 0x64))(pso, 0);
    (*(void (**)(SO *, VECTOR *))(*(uint8_t **)pso + 0x90))(pso, &D_00248D30);
    (*(void (**)(SO *, VECTOR *))(*(uint8_t **)pso + 0x94))(pso, &D_00248D30);
    SetSoConstraints(pso, CT_Project, &g_normalZ, CT_Locked, NULL);
}

void ReturnedRobRoh(ROB *prob, ROH *proh)
{
    SetRostRosts(STRUCT_OFFSET(proh, 0x560, ROST*), ROSTS_Open);
}

INCLUDE_ASM("asm/nonmatchings/P2/rog", ExitedRobRoh__FP3ROBP3ROH);

void KilledRobRoh(ROB *prob, ROH *proh)
{
    RemoveDlEntry(&STRUCT_OFFSET(prob, 0x384, DL), proh);
    AppendDlEntry(&STRUCT_OFFSET(prob, 0x390, DL), proh);

    if (STRUCT_OFFSET(proh, 0x560, ROST *) != NULL)
    {
        RemoveDlEntry(&STRUCT_OFFSET(prob, 0x3ac, DL), STRUCT_OFFSET(proh, 0x560, void *));
        AppendDlEntry(&STRUCT_OFFSET(prob, 0x3a0, DL), STRUCT_OFFSET(proh, 0x560, void *));
        SetRostRosts(STRUCT_OFFSET(proh, 0x560, ROST *), ROSTS_Close);
    }

    ROC *proc = STRUCT_OFFSET(proh, 0x55c, ROC *);
    if (proc != NULL)
    {
        if (STRUCT_OFFSET(proc, 0x18, ROH *) == proh)
        {
            DroppedRobRoh(prob, proh);
        }
        RemoveDlEntry(&STRUCT_OFFSET(prob, 0x35c, DL), proc);
        AppendDlEntry(&STRUCT_OFFSET(prob, 0x368, DL), proc);
        if (!FChooseRobRoh(prob, proc))
            STRUCT_OFFSET(proc, 0x55c, ROH *) = NULL;
    }

    STRUCT_OFFSET(proh, 0x560, ROST *) = NULL;
    STRUCT_OFFSET(proh, 0x55c, ROC *) = NULL;
    (*(void (**)(ROH *))(STRUCT_OFFSET(proh, 0x0, uint8_t *) + 0x1c))(proh);

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
    ROC *procPrev = STRUCT_OFFSET(proh, 0x55c, ROC *);
    if (procPrev != NULL)
    {
        if (procPrev == proc)
            return;
    }

    ROH *prohPrev = STRUCT_OFFSET(proc, 0x55c, ROH *);
    STRUCT_OFFSET(proh, 0x55c, ROC *) = proc;
    STRUCT_OFFSET(proc, 0x55c, ROH *) = proh;

    if (prohPrev == NULL)
    {
        RemoveDlEntry(&STRUCT_OFFSET(prob, 0x368, DL), proc);
        AppendDlEntry(&STRUCT_OFFSET(prob, 0x35c, DL), proc);
    }

    if (procPrev != NULL)
    {
        RemoveDlEntry(&STRUCT_OFFSET(prob, 0x35c, DL), procPrev);
        AppendDlEntry(&STRUCT_OFFSET(prob, 0x368, DL), procPrev);
        STRUCT_OFFSET(procPrev, 0x55c, ROH *) = NULL;
        FChooseRobRoh(prob, procPrev);
    }

    if (prohPrev != NULL)
    {
        STRUCT_OFFSET(prohPrev, 0x55c, ROC *) = NULL;
        SetRohRohs(prohPrev, ROHS_Wander);
        if (FChooseRobRoc(prob, prohPrev))
            SetRohRohs(prohPrev, ROHS_Collect);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/rog", FChooseRobRoh__FP3ROBP3ROC);

INCLUDE_ASM("asm/nonmatchings/P2/rog", FChooseRobReturnPoint__FP3ROBP3ROH);

void ChooseRobWanderLocation(ROB *prob, ROH *proh)
{
    float rad = GRandInRange(0.0f, 6.2831855f);
    float sXY = GRandInRange(0.0f, STRUCT_OFFSET(prob, 0x348, float));
    SetVectorCylind((VECTOR *)((uint8_t *)proh + 0x570), rad, sXY, 0.0f);
    STRUCT_OFFSET(proh, 0x574, float) = STRUCT_OFFSET(proh, 0x574, float) * STRUCT_OFFSET(prob, 0x34c, float);
}

RODD *ProddCurRob(ROB *prob, ENSK ensk)
{
    int irodd = STRUCT_OFFSET(prob, 0x620, int);
    return (RODD *)((uint8_t *)prob + (irodd * 0xC0 + 0x3E0));
}

extern VECTOR g_normalZ;

void InitRoh(ROH *proh)
{
    InitSo(proh);
    STRUCT_OFFSET(proh, 0x550, int) = -1;
    STRUCT_OFFSET(proh, 0x584, float) = 1.0f;
    STRUCT_OFFSET(proh, 0x588, float) = 2.5f;
    SetSoConstraints(proh, CT_Tangent, &g_normalZ, CT_Project, &g_normalZ);
}

extern SNIP D_0026B7E8;

void LoadRohFromBrx(ROH *proh, CBinaryInputStream *pbis)
{
    LoadSoFromBrx(proh, pbis);
    SnipAloObjects(proh, 6, &D_0026B7E8);
    InferExpl(&STRUCT_OFFSET(proh, 0x5ac, EXPL *), proh);
}

INCLUDE_ASM("asm/nonmatchings/P2/rog", CloneRoh__FP3ROHT0);

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
    void *pv = STRUCT_OFFSET(STRUCT_OFFSET(proh, 0x480, DL *), 0x0, void *);

    while (pv != NULL)
    {
        if (STRUCT_OFFSET(pv, 0x0, int) != 0)
        {
            if (FIsBasicDerivedFrom(STRUCT_OFFSET(pv, 0xc, BASIC *), (CID)0x43))
                return STRUCT_OFFSET(pv, 0xc, ROC *);
        }
        pv = STRUCT_OFFSET(pv, 0x4, void *);
    }

    return NULL;
}

INCLUDE_ASM("asm/nonmatchings/P2/rog", InitRoc__FP3ROC);

extern SNIP D_0026B830;

void LoadRocFromBrx(ROC *proc, CBinaryInputStream *pbis)
{
    LoadSoFromBrx(proc, pbis);
    SnipAloObjects(proc, 1, &D_0026B830);
    InferExpl(&STRUCT_OFFSET(proc, 0x574, EXPL *), proc);
}

INCLUDE_ASM("asm/nonmatchings/P2/rog", CloneRoc__FP3ROCT0);

INCLUDE_ASM("asm/nonmatchings/P2/rog", PostRocLoad__FP3ROC);

INCLUDE_ASM("asm/nonmatchings/P2/rog", UpdateRoc__FP3ROCf);

void PresetRocAccel(ROC *proc, float dt)
{
    MATRIX3 mat;
    extern SMP D_0026B850;

    PresetSoAccel(proc, dt);

    if (STRUCT_OFFSET(proc, 0x18, int) == 0)
    {
        TiltMatUpright((MATRIX3 *)((uint8_t *)proc + 0x110), NULL, &mat);
        AccelSoTowardMatSmooth(proc, g_clock.dt, &mat, &D_0026B850);
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

extern SNIP D_0026B888;

void LoadRostFromBrx(ROST *prost, CBinaryInputStream *pbis)
{
    LoadSoFromBrx(prost, pbis);
    SnipAloObjects(prost, 1, &D_0026B888);
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
    STRUCT_OFFSET(prop, 0x550, int) = -1; // prop->rops
    SetSoConstraints(prop, CT_Locked, NULL, CT_Locked, NULL);
}

extern SNIP D_0026B8A0;

void LoadRopFromBrx(ROP *prop, CBinaryInputStream *pbis)
{
    LoadSoFromBrx(prop, pbis);
    SnipAloObjects(prop, 1, &D_0026B8A0);
    InferExpl(&STRUCT_OFFSET(prop, 0x568, EXPL *), prop);
}

void PostRopLoad(ROP *prop)
{
    PostAloLoad(prop);

    if (STRUCT_OFFSET(prop, 0x558, int) == 0)
    {
        prop->pvtlo->pfnRemoveLo(prop);
    }
    else
    {
        STRUCT_OFFSET(prop, 0x55C, LO *) =
            PloFindSwObjectByClass(prop->psw, 0x101, (CID)0x59, STRUCT_OFFSET(prop, 0x34, LO *));
        SetRopRops(prop, ROPS_StayPut);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/rog", UpdateRop__FP3ROPf);

INCLUDE_ASM("asm/nonmatchings/P2/rog", SetRopRops__FP3ROP4ROPS);

INCLUDE_ASM("asm/nonmatchings/P2/rog", RopsNextRop__FP3ROP);
