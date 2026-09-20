#include <sensor.h>
#include <lookat.h>
#include <freeze.h>
#include <alarm.h>
#include <asega.h>
#include <game.h>
#include <alo.h>
#include <so.h>
#include <lo.h>
#include <jt.h>

// .data
static SNIP s_asnipLasen[2] =
{
    {2, OID_laser_sensor_render, 0xae4},
    {2, OID_laser_damage_render, 0xae8},
};

int g_fLasenBusyListChange = 0;

static SNIP s_asnipCamsen[2] =
{
    {2, OID_camera_damage_render, 0x5d0},
    {2, OID_camera_zap_render, 0x5d4},
};

void InitSensor(SENSOR *psensor)
{
    InitSo(psensor);
    psensor->sensors = SENSORS_Nil;
    psensor->sensm = SENSM_SenseOnly;
}

void SetSensorAlarm(SENSOR *psensor, ALARM *palarm)
{
    psensor->palarm = palarm;
}

void SetSensorSensors(SENSOR *psensor, SENSORS sensors)
{
    if (psensor->sensors == sensors)
    {
        return;
    }

    if (psensor->sensors == SENSORS_SenseEnabled && sensors == SENSORS_SenseTriggered)
    {
        if (psensor->palarm)
        {
            TriggerAlarm(psensor->palarm, ALTK_Trigger);
            if (psensor->sensors != SENSORS_SenseEnabled)
            {
                sensors = psensor->sensors;
            }
        }

        HandleLoSpliceEvent(psensor, 2, 0, NULL);
    }

    psensor->sensors = sensors;
    psensor->tSensors = g_clock.t;
}

INCLUDE_ASM("asm/nonmatchings/P2/sensor", FCheckSensorObject__FP6SENSORP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", FIgnoreSensorObject__FP6SENSORP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", FOnlySensorTriggerObject__FP6SENSORP2SO);

void PauseSensor(SENSOR *psensor)
{
    ASEGA *pasega = PasegaFindAloNearest(psensor);
    if (pasega)
    {
        psensor->svtRestore = pasega->svtLocal;
        pasega->svtLocal = 0.0f;
        psensor->pasegaPause = pasega;
    }
}

void UpdateSensor(SENSOR *psensor, float dt)
{
    UpdateSo(psensor, dt);

    if (psensor->pasegaPause && g_pjt && g_pjt->jts != JTS_Sidestep)
    {
        psensor->pasegaPause->svtLocal = psensor->svtRestore;
        psensor->pasegaPause = NULL;
        psensor->svtRestore = 0.0f;
    }
}

void AddSensorTriggerObject(SENSOR *psensor, OID oid)
{
    if (psensor->ctriggerObjects >= 4)
        return;

    psensor->atriggerObjects[psensor->ctriggerObjects++] = oid;
}

void AddSensorNoTriggerObject(SENSOR *psensor, OID oid)
{
    if (psensor->cnoTriggerObjects >= 4)
        return;

    psensor->anoTriggerObjects[psensor->cnoTriggerObjects++] = oid;
}

void AddSensorTriggerClass(SENSOR *psensor, CID cid)
{
    if (psensor->ctriggerClasses >= 4)
        return;

    psensor->atriggerClasses[psensor->ctriggerClasses++] = cid;
}

void AddSensorNoTriggerClass(SENSOR *psensor, CID cid)
{
    if (psensor->cnoTriggerClasses >= 4)
        return;

    psensor->anoTriggerClasses[psensor->cnoTriggerClasses++] = cid;
}

INCLUDE_ASM("asm/nonmatchings/P2/sensor", InitLasen__FP5LASEN);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", LoadLasenFromBrx__FP5LASENP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", BindLasen__FP5LASEN);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", PostLasenLoad__FP5LASEN);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", UpdateBusyLasenSenseTimes__Fv);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", UpdateLasen__FP5LASENf);

void FreezeLasen(LASEN *plasen, int fFreeze)
{
    FreezeSo(plasen, fFreeze);
    if (fFreeze)
    {
        if (STRUCT_OFFSET(plasen, 0xaf8, int)) // plasen->fBusyLasen
        {
            RemoveDlEntry(&plasen->psw->dlBusyLasen, plasen);
            STRUCT_OFFSET(plasen, 0xaf8, int) = 0; // plasen->fBusyLasen
        }
    }
    else
    {
        AppendDlEntry(&plasen->psw->dlBusyLasen, plasen);
        STRUCT_OFFSET(plasen, 0xaf8, int) = 1; // plasen->fBusyLasen
    }

    g_fLasenBusyListChange = 1;
}

INCLUDE_ASM("asm/nonmatchings/P2/sensor", RenderLasenSelf__FP5LASENP2CMP2RO);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", FUN_001afaf8__FP6SENSORP2SO);
#ifdef SKIP_ASM
/**
 * @todo 73.57% matched.
 */
int FUN_001afaf8(SENSOR *psensor, SO *pso)
{
    unsigned long long mask;
    uint tmp2cc;

    /* Mask: (0x8000 << 28) in 64-bits */
    mask = ((ulong)0x8000) << 28;
    if (STRUCT_OFFSET(pso, 0x538, ulong) & mask)
        return 0;

    if (STRUCT_OFFSET(pso, 0x50, uint) == STRUCT_OFFSET(psensor, 0x50, uint))
        return 0;

    if (FIgnoreSensorObject(psensor, pso))
        return 0;

    if (pso == g_pjt)
    {
        if (STRUCT_OFFSET(pso, 0x2220, uint) != 6)
            return 0;
        if (STRUCT_OFFSET(pso, 0x239C, uint) != 3)
            return 0;
        if (GetGrfvault_unknown() & 0x12000)
            return 0;
    }

    tmp2cc = STRUCT_OFFSET(pso, 0x2CC, uint);
    /* Invert lowest bit and mask to 1 */
    return (int)(((tmp2cc ^ 1u) & 1u));
}
#endif

INCLUDE_ASM("asm/nonmatchings/P2/sensor", SenseLasen__FP5LASENP7SENSORS);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", EnableLasen__FP5LASEN5SENSM);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", DisableLasen__FP5LASEN);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", OnLasenAlarmTriggered__FP5LASEN);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", SetLasenSensors__FP5LASEN7SENSORS);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", SCalcLasenShapeExtent__FP5LASENP5LBEAM);

void RetractLasen(LASEN *plasen, float dtRetract)
{
    // plasen->svuDrawMax
    STRUCT_OFFSET(plasen, 0xb08, float) = -1.0f / dtRetract;
}

void ExtendLasen(LASEN *plasen, float dtExpand)
{
    // plasen->svuDrawMax
    STRUCT_OFFSET(plasen, 0xb08, float) = 1.0f / dtExpand;
}

void InitCamsen(CAMSEN *pcamsen)
{
    InitSensor(pcamsen);
    STRUCT_OFFSET(pcamsen, 0x5d8, CSDTS) = CSDTS_Nil; // pcamsen->csdts
}

void PostCamsenLoad(CAMSEN *pcamsen)
{
    PostAloLoad(pcamsen);
    SnipAloObjects(pcamsen, 2, s_asnipCamsen);

    // pcamsen->paloRenderDamage
    if (STRUCT_OFFSET(pcamsen, 0x5d0, ALO *) == NULL)
    {
        STRUCT_OFFSET(pcamsen, 0x5d0, ALO *) = pcamsen;
    }

    // pcamsen->paloRenderZap
    if (STRUCT_OFFSET(pcamsen, 0x5d4, ALO *) == 0)
    {
        STRUCT_OFFSET(pcamsen, 0x5d4, ALO *) = (ALO *)pcamsen->psw->aploStock[0x0b]; // TODO: Unknown CID.
    }

    // pcamsen->pactla
    if (STRUCT_OFFSET(pcamsen, 0x200, ACTLA *))
    {
        // pcamsen->pactla->nPriorityEnabled = 0;
        STRUCT_OFFSET(STRUCT_OFFSET(pcamsen, 0x200, ACTLA *), 0x44, int) = 0;
    }

    // pcamsen->bspcCamera.absp
    STRUCT_OFFSET(pcamsen, 0x538, ulong) |= 0x80000000000;
    SetSoConstraints(pcamsen, CT_Locked, NULL, CT_Locked, NULL);
    pcamsen->pvtcamsen->pfnSetCamsenSensors(pcamsen, STRUCT_OFFSET(pcamsen, 0x560, int)); // pcamsen->sensorsInitial
}

INCLUDE_ASM("asm/nonmatchings/P2/sensor", UpdateCamsen__FP6CAMSENf);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", RenderCamsenSelf__FP6CAMSENP2CMP2RO);

int FIgnoreCamsenIntersection(CAMSEN *pcamsen, SO *psoOther)
{
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/P2/sensor", FFilterCamsen__FPvP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", SenseCamsen__FP6CAMSENP7SENSORS);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", EnableCamsen__FP6CAMSEN5SENSM);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", DisableCamsen__FP6CAMSEN);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", OnCamsenAlarmTriggered__FP6CAMSEN);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", SetCamsenSensors__FP6CAMSEN7SENSORS);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", SetCamsenCsdts__FP6CAMSEN5CSDTS);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", InitPrsen__FP5PRSEN);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", PostPrsenLoad__FP5PRSEN);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", UpdatePrsen__FP5PRSENf);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", SensePrsen__FP5PRSENP7SENSORS);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", EnablePrsen__FP5PRSEN5SENSM);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", DisablePrsen__FP5PRSEN);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", OnPrsenAlarmTriggered__FP5PRSEN);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", SetPrsenSensors__FP5PRSEN7SENSORS);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", UpdatePrsenLoopShader__FP5PRSEN);
