#include <sensor.h>
#include <so.h>
#include <lo.h>
#include <alarm.h>
#include <game.h>
#include <freeze.h>

void InitSensor(SENSOR *psensor)
{
	InitSo(psensor);
	STRUCT_OFFSET(psensor, 0x558, SENSORS) = SENSORS_Nil;
	STRUCT_OFFSET(psensor, 0x554, int) = 0;
}

void SetSensorAlarm(SENSOR *psensor, ALARM *palarm)
{
	STRUCT_OFFSET(psensor, 0x550, ALARM *) = palarm; // psensor->palarm = palarm;
}

INCLUDE_ASM("asm/nonmatchings/P2/sensor", SetSensorSensors__FP6SENSOR7SENSORS);
#ifdef SKIP_ASM
/**
 * @todo 82.08% matched.
 */
void SetSensorSensors(SENSOR *psensor, SENSORS sensors)
{
	SENSORS sensorsCur = STRUCT_OFFSET(psensor, 0x558, SENSORS); // sensorsCur = psensor->sensors;

	if (sensorsCur == sensors)
	{
		return;
	}

	if (sensorsCur == SENSORS_SenseEnabled && sensors == SENSORS_SenseTriggered)
	{
		ALARM *palarm = STRUCT_OFFSET(psensor, 0x550, ALARM *);
		if (palarm)
		{
			TriggerAlarm(palarm, ALTK_Trigger);
		}

		// Recheck current sensor state: if it's not SENSORS_SenseEnabled,
		// override the current sensors with the new one.
		sensorsCur = STRUCT_OFFSET(psensor, 0x558, SENSORS);
		if (sensorsCur != SENSORS_SenseEnabled)
		{
			sensors = sensorsCur;
		}
	}

	HandleLoSpliceEvent(psensor, 2, 0, NULL);
	STRUCT_OFFSET(psensor, 0x558, SENSORS) = sensors; // psensor->sensors = sensors;
	STRUCT_OFFSET(psensor, 0x55C, float) = g_clock.t;
}
#endif

INCLUDE_ASM("asm/nonmatchings/P2/sensor", FCheckSensorObject__FP6SENSORP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", FIgnoreSensorObject__FP6SENSORP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", FOnlySensorTriggerObject__FP6SENSORP2SO);

void PauseSensor(SENSOR *psensor)
{
	ASEGA *pasega = PasegaFindAloNearest((ALO *)psensor);
	if (pasega)
	{
		STRUCT_OFFSET(psensor, 0x5CC, float) = STRUCT_OFFSET(pasega, 0x18, float);
		STRUCT_OFFSET(pasega, 0x18, int) = 0;
		STRUCT_OFFSET(psensor, 0x5C8, ASEGA *) = pasega;
	}
}

INCLUDE_ASM("asm/nonmatchings/P2/sensor", UpdateSensor__FP6SENSORf);

void AddSensorTriggerObject(SENSOR *psensor, OID oid)
{
    uint ccur = psensor->ctriggerObjects;
    if (ccur >= 4)
        return;

    psensor->atriggerObjects[ccur] = oid;
    psensor->ctriggerObjects = ccur + 1;
}
void AddSensorNoTriggerObject(SENSOR *psensor, OID oid)
{
    uint ccur = psensor->cnoTriggerObjects;
    if (ccur >= 4)
        return;

    psensor->anoTriggerObjects[ccur] = oid;
    psensor->cnoTriggerObjects = ccur + 1;
}
void AddSensorTriggerClass(SENSOR *psensor, CID cid)
{
    uint ccur = psensor->ctriggerClasses;
    if (ccur >= 4)
        return;

    psensor->atriggerClasses[ccur] = cid;
    psensor->ctriggerClasses = ccur + 1;
}
void AddSensorNoTriggerClass(SENSOR *psensor, CID cid)
{
    uint ccur = psensor->cnoTriggerClasses;
    if (ccur >= 4)
        return;

    psensor->anoTriggerClasses[ccur] = cid;
    psensor->cnoTriggerClasses = ccur + 1;
}
void InitLasen(LASEN *plasen)
{
    InitSensor(plasen);
    STRUCT_OFFSET(plasen, 0xB04, float) = 1.0f;
}

void LoadLasenFromBrx(LASEN *plasen, CBinaryInputStream *pbis)
{
	extern SNIP D_002744B8[2];

	LoadSoFromBrx(plasen, pbis);
	SnipAloObjects(plasen, 2, D_002744B8);
}

INCLUDE_ASM("asm/nonmatchings/P2/sensor", BindLasen__FP5LASEN);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", PostLasenLoad__FP5LASEN);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", UpdateBusyLasenSenseTimes__Fv);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", UpdateLasen__FP5LASENf);

extern int D_002744D0;

void FreezeLasen(LASEN *plasen, int fFreeze)
{
    FreezeSo(plasen, fFreeze);

    if (fFreeze)
    {
        if (STRUCT_OFFSET(plasen, 0xAF8, int))
        {
            RemoveDlEntry((DL *)((char *)plasen->psw + 0x1ca8), plasen);
            STRUCT_OFFSET(plasen, 0xAF8, int) = 0;
        }
    }
    else
    {
        AppendDlEntry((DL *)((char *)plasen->psw + 0x1ca8), plasen);
        STRUCT_OFFSET(plasen, 0xAF8, int) = 1;
    }

    D_002744D0 = 1;
}

INCLUDE_ASM("asm/nonmatchings/P2/sensor", RenderLasenSelf__FP5LASENP2CMP2RO);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", FUN_001afaf8__FP6SENSORP2SO);
#ifdef SKIP_ASM
/**
 * @todo 73.57% matched.
 */
int FUN_001afaf8(SENSOR *psensor, SO *pso)
{
	extern void *g_pjt;
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
    STRUCT_OFFSET(plasen, 0xB08, float) = -1.0f / dtRetract;
}

void ExtendLasen(LASEN *plasen, float dtExpand)
{
    STRUCT_OFFSET(plasen, 0xB08, float) = 1.0f / dtExpand;
}

void InitCamsen(CAMSEN *pcamsen)
{
    InitSensor(pcamsen);
    STRUCT_OFFSET(pcamsen, 0x5D8, int) = -1;
}

extern SNIP D_002744D8[2];

void PostCamsenLoad(CAMSEN *pcamsen)
{
    void *pvt;
    void (*pfn)(CAMSEN *, int);

    PostAloLoad(pcamsen);
    SnipAloObjects(pcamsen, 2, D_002744D8);

    if (STRUCT_OFFSET(pcamsen, 0x5d0, int) == 0)
        STRUCT_OFFSET(pcamsen, 0x5d0, int) = (int)pcamsen;

    if (STRUCT_OFFSET(pcamsen, 0x5d4, int) == 0)
        STRUCT_OFFSET(pcamsen, 0x5d4, int) = STRUCT_OFFSET(pcamsen->psw, 0x1d14, int);

    if (STRUCT_OFFSET(pcamsen, 0x200, void *) != NULL)
        STRUCT_OFFSET(STRUCT_OFFSET(pcamsen, 0x200, void *), 0x44, int) = 0;

    STRUCT_OFFSET(pcamsen, 0x538, ulong) |= ((ulong)0x8000) << 28;

    SetSoConstraints(pcamsen, CT_Locked, NULL, CT_Locked, NULL);

    pvt = STRUCT_OFFSET(pcamsen, 0x0, void *);
    pfn = (void (*)(CAMSEN *, int))STRUCT_OFFSET(pvt, 0x144, void *);
    pfn(pcamsen, STRUCT_OFFSET(pcamsen, 0x560, int));
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
