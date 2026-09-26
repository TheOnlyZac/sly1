#include <sensor.h>
#include <shdanim.h>
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

int FCheckSensorObject(SENSOR *psensor, SO *psoOther)
{
    if (psensor->fTriggerAll != 0)
    {
        return 1;
    }

    if (FIgnoreSensorObject(psensor, psoOther))
    {
        return 0;
    }

    for (int i = 0; i < (int)psensor->coidTrigger; i++)
    {
        if (FMatchesLoName(psoOther, psensor->aoidTrigger[i]))
        {
            return 1;
        }
    }

    for (int i = 0; i < (int)psensor->ccidTrigger; i++)
    {
        if (FIsBasicDerivedFrom(psoOther, psensor->acidTrigger[i]))
        {
            return 1;
        }
    }

    return 0;
}

int FIgnoreSensorObject(SENSOR *psensor, SO *psoOther)
{
    for (int i = 0; i < (int)psensor->coidNoTrigger; i++)
    {
        if (FMatchesLoName(psoOther, psensor->aoidNoTrigger[i]))
        {
            return 1;
        }
    }

    for (int i = 0; i < (int)psensor->ccidNoTrigger; i++)
    {
        if (FIsBasicDerivedFrom(psoOther, psensor->acidNoTrigger[i]))
        {
            return 1;
        }
    }

    return 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/sensor", FOnlySensorTriggerObject__FP6SENSORP2SO);
#ifdef SKIP_ASM
/**
 * @todo 83.20% match.
 */
int FOnlySensorTriggerObject(SENSOR *psensor, SO *psoOther)
{
    if (!psoOther)
    {
        return 0;
    }

    if (psensor->fTriggerAll != 0)
    {
        return 0;
    }

    if (psensor->coidTrigger != 1)
    {
        return 0;
    }

    if (psensor->ccidTrigger != 1)
    {
        return 0;
    }

    return !FMatchesLoName(psoOther, psensor->aoidTrigger[0]);
}
#endif // SKIP_ASM

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
    if (psensor->coidTrigger >= 4)
        return;

    psensor->aoidTrigger[psensor->coidTrigger++] = oid;
}

void AddSensorNoTriggerObject(SENSOR *psensor, OID oid)
{
    if (psensor->coidNoTrigger >= 4)
        return;

    psensor->aoidNoTrigger[psensor->coidNoTrigger++] = oid;
}

void AddSensorTriggerClass(SENSOR *psensor, CID cid)
{
    if (psensor->ccidTrigger >= 4)
        return;

    psensor->acidTrigger[psensor->ccidTrigger++] = cid;
}

void AddSensorNoTriggerClass(SENSOR *psensor, CID cid)
{
    if (psensor->ccidNoTrigger >= 4)
        return;

    psensor->acidNoTrigger[psensor->ccidNoTrigger++] = cid;
}

void InitLasen(LASEN *plasen)
{
    InitSensor(plasen);
    STRUCT_OFFSET(plasen, 0xb04, float) = 1.0f; // plasen->uDrawMax
}

void LoadLasenFromBrx(LASEN *plasen, CBinaryInputStream *pbis)
{
    LoadSoFromBrx(plasen, pbis);
    SnipAloObjects(plasen, 2, s_asnipLasen);
}

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

INCLUDE_ASM("asm/nonmatchings/P2/sensor", FFilterLasen__FPvP2SO);
#ifdef SKIP_ASM
/**
 * @todo 94.35% match. Missing two shift instructions.
 */
ulong FFilterLasen(void *pv, SO *pso)
{
    if (STRUCT_OFFSET(pso, 0x538, ulong) & 0x80000000000)
    {
        return 0;
    }

    if (STRUCT_OFFSET(pso, 0x50, uint) == STRUCT_OFFSET(pv, 0x50, uint))
    {
        return 0;
    }

    if (FIgnoreSensorObject((SENSOR *)pv, pso))
    {
        return 0;
    }

    if (
        pso == g_pjt &&
        STRUCT_OFFSET(pso, 0x2220, uint) == 6 &&
        STRUCT_OFFSET(pso, 0x239c, uint) == 3 &&
        (GetGrfvault_unknown() & 0x12000) != 0
    )
    {
        return 0;
    }

    int64_t fHidden = (int64_t)STRUCT_OFFSET(pso, 0x2cc, uint);
    fHidden = (fHidden ^ 1) & 1;
    return (ulong)fHidden;
}
#endif // SKIP_ASM

INCLUDE_ASM("asm/nonmatchings/P2/sensor", SenseLasen__FP5LASENP7SENSORS);

void EnableLasen(LASEN *plasen, SENSM sensm)
{
    plasen->sensm = sensm;
    SENSORS sensors = (sensm == SENSM_SenseOnly) ? SENSORS_SenseEnabled : SENSORS_DamageEnabled;
    plasen->pvtlasen->pfnSetLasenSensors(plasen, sensors);
}

void DisableLasen(LASEN *plasen)
{
    if (plasen->sensors != SENSORS_Disabled)
    {
        SENSORS sensors = (plasen->sensm == SENSM_SenseOnly) ? SENSORS_SenseDisabling : SENSORS_DamageDisabling;
        plasen->pvtlasen->pfnSetLasenSensors(plasen, sensors);
    }
}

void OnLasenAlarmTriggered(LASEN *plasen)
{
    // NOTE: Merging the if statements doesn't produce matching code.
    if (plasen->sensors < SENSORS_SenseDisabling)
    {
        if (plasen->sensors > SENSORS_Nil)
        {
            plasen->pvtlasen->pfnSetLasenSensors(plasen, SENSORS_SenseDisabling);
        }
    }

    plasen->sensm = SENSM_DamageTarget;
}

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
        // pcamsen->pactla->nPriorityEnabled
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

void EnableCamsen(CAMSEN *pcamsen, SENSM sensm)
{
    pcamsen->sensm = sensm;
    SENSORS sensors = (sensm == SENSM_SenseOnly) ? SENSORS_SenseEnabled : SENSORS_DamageEnabled;
    pcamsen->pvtcamsen->pfnSetCamsenSensors(pcamsen, sensors);
}

void DisableCamsen(CAMSEN *pcamsen)
{
    if (pcamsen->sensors != SENSORS_Disabled)
    {
        SENSORS sensors = (pcamsen->sensm == SENSM_SenseOnly) ? SENSORS_SenseDisabling : SENSORS_DamageDisabling;
        pcamsen->pvtcamsen->pfnSetCamsenSensors(pcamsen, sensors);
    }

    if (pcamsen->palarm && pcamsen->palarm->alarms == ALARMS_Disabled && ABS(g_clock.t - pcamsen->palarm->tAlarms) < 0.2f)
    {
        // pcamsen->fRemainDisabledIndefinite
        STRUCT_OFFSET(pcamsen, 0x5c0, int) = 1;
    }
}

void OnCamsenAlarmTriggered(CAMSEN *pcamsen)
{
    if (pcamsen->sensm != SENSM_SenseOnly)
    {
        return;
    }

    pcamsen->sensm = SENSM_DamageTarget;
    if (pcamsen->sensors != SENSORS_Disabled)
    {
        pcamsen->pvtcamsen->pfnSetCamsenSensors(pcamsen, SENSORS_SenseDisabling);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/sensor", SetCamsenSensors__FP6CAMSEN7SENSORS);
#ifdef SKIP_ASM
/**
 * @todo 66.00% match. GCC doesn't want to generate jump tables like in the target.
 */
void SetCamsenSensors(CAMSEN *pcamsen, SENSORS sensors)
{
    if (pcamsen->sensors == sensors)
    {
        return;
    }

    switch (pcamsen->sensors)
    {
        case SENSORS_DamageTriggered:
        {
            SetCamsenCsdts(pcamsen, CSDTS_Nil);
            break;
        }
        case SENSORS_Disabled:
        {
            // pcamsen->fRemainDisabledIndefinite
            STRUCT_OFFSET(pcamsen, 0x5c0, int) = 0;
            break;
        }
    }

    switch (sensors)
    {
        case SENSORS_DamageTriggered:
        {
            SetCamsenCsdts(pcamsen, CSDTS_Focus);
            break;
        }
    }

    SetSensorSensors(pcamsen, sensors);
}
#endif // SKIP_ASM

INCLUDE_ASM("asm/nonmatchings/P2/sensor", SetCamsenCsdts__FP6CAMSEN5CSDTS);

void InitPrsen(PRSEN *pprsen)
{
    InitSensor(pprsen);
    STRUCT_OFFSET(pprsen, 0x5d0, int) = -1;
    STRUCT_OFFSET(pprsen, 0x5d4, int) = -1;
    STRUCT_OFFSET(pprsen, 0x5e0, int) = -1;
    STRUCT_OFFSET(pprsen, 0x5e4, int) = -1;
    STRUCT_OFFSET(pprsen, 0x5f0, int) = -1;
    STRUCT_OFFSET(pprsen, 0x5f4, int) = -1;
    STRUCT_OFFSET(pprsen, 0x600, int) = -1;
}

INCLUDE_ASM("asm/nonmatchings/P2/sensor", PostPrsenLoad__FP5PRSEN);
#ifdef SKIP_ASM
/**
 * @todo 81.16% match.
 */
void PostPrsenLoad(PRSEN *pprsen)
{
    PostAloLoad(pprsen);

    // pprsen->globset.cpsaa
    for (int i = 0; i < STRUCT_OFFSET(pprsen, 0x27c, int); i++)
    {
        SAA **apsaa = &STRUCT_OFFSET(pprsen, 0x280, SAA *);
        SAA *psaa = apsaa[i];

        if (psaa->saak == SAAK_Loop && psaa->sai.pshd)
        {
            // pprsen->ploop
            STRUCT_OFFSET(pprsen, 0x610, LOOP *) = (LOOP *)psaa;
            break;
        }
    }

    pprsen->pvtprsen->pfnSetPrsenSensors(pprsen, pprsen->sensorsInitial);
}
#endif // SKIP_ASM

INCLUDE_ASM("asm/nonmatchings/P2/sensor", UpdatePrsen__FP5PRSENf);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", SensePrsen__FP5PRSENP7SENSORS);

void EnablePrsen(PRSEN *pprsen, SENSM sensm)
{
    pprsen->sensm = sensm;
    SENSORS sensors = (sensm == SENSM_SenseOnly) ? SENSORS_SenseEnabled : SENSORS_DamageEnabled;
    pprsen->pvtprsen->pfnSetPrsenSensors(pprsen, sensors);
}

void DisablePrsen(PRSEN *pprsen)
{
    if (pprsen->sensors != SENSORS_Disabled)
    {
        SENSORS sensors = (pprsen->sensm == SENSM_SenseOnly) ? SENSORS_SenseDisabling : SENSORS_DamageDisabling;
        pprsen->pvtprsen->pfnSetPrsenSensors(pprsen, sensors);
    }

    if (pprsen->palarm && pprsen->palarm->alarms == ALARMS_Disabled && ABS(g_clock.t - pprsen->palarm->tAlarms) < 0.2f)
    {
        // pprsen->fRemainDisabledIndefinite
        STRUCT_OFFSET(pprsen, 0x5c0, int) = 1;
    }
}

void OnPrsenAlarmTriggered(PRSEN *pprsen)
{
    pprsen->sensm = SENSM_DamageTarget;

    if (STRUCT_OFFSET(pprsen, 0x608, float) < 0.0f) // pprsen->dtRemainEnabled
    {
        STRUCT_OFFSET(pprsen, 0x618, int) = 0; // pprsen->fTriggered

        switch (pprsen->sensors)
        {
            case SENSORS_SenseEnabled:
            {
                pprsen->pvtprsen->pfnSetPrsenSensors(pprsen, SENSORS_SenseDisabling);
                break;
            }
            case SENSORS_DamageEnabled:
            {
                pprsen->pvtprsen->pfnSetPrsenSensors(pprsen, SENSORS_DamageDisabling);
                break;
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/sensor", SetPrsenSensors__FP5PRSEN7SENSORS);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", UpdatePrsenLoopShader__FP5PRSEN);
