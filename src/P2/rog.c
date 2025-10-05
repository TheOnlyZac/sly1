#include <rog.h>
#include <cm.h>

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

INCLUDE_ASM("asm/nonmatchings/P2/rog", RovtsNextRov__FP3ROV);

INCLUDE_ASM("asm/nonmatchings/P2/rog", SetRovRovts__FP3ROV5ROVTS);

INCLUDE_ASM("asm/nonmatchings/P2/rog", HandleRovMessage__FP3ROV5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/rog", PresetRovAccel__FP3ROVf);

INCLUDE_ASM("asm/nonmatchings/P2/rog", AdjustRovXpVelocity__FP3ROVP2XPi);

INCLUDE_ASM("asm/nonmatchings/P2/rog", AdjustRovNewXp__FP3ROVP2XPi);

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

INCLUDE_ASM("asm/nonmatchings/P2/rog", SpawnedRobRoh__FP3ROBP3ROH);

INCLUDE_ASM("asm/nonmatchings/P2/rog", GrabbedRobRoh__FP3ROBP3ROH);

INCLUDE_ASM("asm/nonmatchings/P2/rog", DroppedRobRoh__FP3ROBP3ROH);

INCLUDE_ASM("asm/nonmatchings/P2/rog", ReturnedRobRoh__FP3ROBP3ROH);

INCLUDE_ASM("asm/nonmatchings/P2/rog", ExitedRobRoh__FP3ROBP3ROH);

INCLUDE_ASM("asm/nonmatchings/P2/rog", KilledRobRoh__FP3ROBP3ROH);

INCLUDE_ASM("asm/nonmatchings/P2/rog", FChooseRobRoc__FP3ROBP3ROH);

INCLUDE_ASM("asm/nonmatchings/P2/rog", TakeRobRoc__FP3ROBP3ROHP3ROC);

INCLUDE_ASM("asm/nonmatchings/P2/rog", FChooseRobRoh__FP3ROBP3ROC);

INCLUDE_ASM("asm/nonmatchings/P2/rog", FChooseRobReturnPoint__FP3ROBP3ROH);

INCLUDE_ASM("asm/nonmatchings/P2/rog", ChooseRobWanderLocation__FP3ROBP3ROH);

INCLUDE_ASM("asm/nonmatchings/P2/rog", ProddCurRob__FP3ROB4ENSK);

INCLUDE_ASM("asm/nonmatchings/P2/rog", InitRoh__FP3ROH);

INCLUDE_ASM("asm/nonmatchings/P2/rog", LoadRohFromBrx__FP3ROHP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/rog", CloneRoh__FP3ROHT0);

INCLUDE_ASM("asm/nonmatchings/P2/rog", PostRohLoad__FP3ROH);

INCLUDE_ASM("asm/nonmatchings/P2/rog", UpdateRoh__FP3ROHf);

INCLUDE_ASM("asm/nonmatchings/P2/rog", MoveRohToTarget__FP3ROHP6VECTORi);

INCLUDE_ASM("asm/nonmatchings/P2/rog", RohsNextRoh__FP3ROH);

INCLUDE_ASM("asm/nonmatchings/P2/rog", SetRohRohs__FP3ROH4ROHS);

INCLUDE_ASM("asm/nonmatchings/P2/rog", FAbsorbRohWkr__FP3ROHP3WKR);

INCLUDE_ASM("asm/nonmatchings/P2/rog", ProcContactRoh__FP3ROH);

INCLUDE_ASM("asm/nonmatchings/P2/rog", InitRoc__FP3ROC);

INCLUDE_ASM("asm/nonmatchings/P2/rog", LoadRocFromBrx__FP3ROCP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/rog", CloneRoc__FP3ROCT0);

INCLUDE_ASM("asm/nonmatchings/P2/rog", PostRocLoad__FP3ROC);

INCLUDE_ASM("asm/nonmatchings/P2/rog", UpdateRoc__FP3ROCf);

INCLUDE_ASM("asm/nonmatchings/P2/rog", PresetRocAccel__FP3ROCf);

INCLUDE_ASM("asm/nonmatchings/P2/rog", AdjustRocNewXp__FP3ROCP2XPi);

INCLUDE_ASM("asm/nonmatchings/P2/rog", FAbsorbRocWkr__FP3ROCP3WKR);

INCLUDE_ASM("asm/nonmatchings/P2/rog", RocsNextRoc__FP3ROC);

INCLUDE_ASM("asm/nonmatchings/P2/rog", SetRocRocs__FP3ROC4ROCS);

INCLUDE_ASM("asm/nonmatchings/P2/rog", InitRost__FP4ROST);

INCLUDE_ASM("asm/nonmatchings/P2/rog", LoadRostFromBrx__FP4ROSTP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/rog", CloneRost__FP4ROSTT0);

INCLUDE_ASM("asm/nonmatchings/P2/rog", PostRostLoad__FP4ROST);

INCLUDE_ASM("asm/nonmatchings/P2/rog", UpdateRost__FP4ROSTf);

INCLUDE_ASM("asm/nonmatchings/P2/rog", RostsNextRost__FP4ROST);

INCLUDE_ASM("asm/nonmatchings/P2/rog", SetRostRosts__FP4ROST5ROSTS);

INCLUDE_ASM("asm/nonmatchings/P2/rog", InitRop__FP3ROP);

INCLUDE_ASM("asm/nonmatchings/P2/rog", LoadRopFromBrx__FP3ROPP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/rog", PostRopLoad__FP3ROP);

INCLUDE_ASM("asm/nonmatchings/P2/rog", UpdateRop__FP3ROPf);

INCLUDE_ASM("asm/nonmatchings/P2/rog", SetRopRops__FP3ROP4ROPS);

INCLUDE_ASM("asm/nonmatchings/P2/rog", RopsNextRop__FP3ROP);
