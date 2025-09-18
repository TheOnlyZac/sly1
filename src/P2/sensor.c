#include <sensor.h>
#include <so.h>
#include <lo.h>
#include <alarm.h>
#include <game.h>

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
 * @brief Sets the sensor's state and handles triggering the sensor's alarm.
 *
 * @param psensor Pointer to the sensor.
 * @param sensors New sensor state.
 *
 * If the sensor is transitioning from SENSORS_SenseEnabled to SENSORS_SenseTriggered,
 * it will trigger the associated alarm if one is set. If the sensor's state changes,
 * it will also notify any listeners of the change via an LO splice event.
 *
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

	HandleLoSpliceEvent(psensor, 2, 0, (void **)0);
	STRUCT_OFFSET(psensor, 0x558, SENSORS) = sensors; // psensor->sensors = sensors;
	STRUCT_OFFSET(psensor, 0x55C, float) = g_clock.t;
}
#endif

INCLUDE_ASM("asm/nonmatchings/P2/sensor", FCheckSensorObject__FP6SENSORP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", FIgnoreSensorObject__FP6SENSORP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", FOnlySensorTriggerObject__FP6SENSORP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", PauseSensor__FP6SENSOR);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", UpdateSensor__FP6SENSORf);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", AddSensorTriggerObject__FP6SENSOR3OID);
#ifdef SKIP_ASM
/**
 * @brief Add an object ID to the sensor's trigger list.
 *
 * @param psensor Pointer to the sensor.
 * @param oid Object ID to add.
 *
 * @todo 100% matched but sensor struct offsets are wrong.
 * Doesn't match with STRUCT_OFFSET macro due to regswaps.
 */
void AddSensorTriggerObject(SENSOR *psensor, OID oid)
{
	uint ccur = psensor->ctriggerObjects;
	if (ccur >= 4)
		return;

	psensor->atriggerObjects[ccur] = oid;
	psensor->ctriggerObjects = ccur + 1;
}
#endif

INCLUDE_ASM("asm/nonmatchings/P2/sensor", AddSensorNoTriggerObject__FP6SENSOR3OID);
#ifdef SKIP_ASM
/**
 * @brief Add an object ID to the sensor's no-trigger list.
 *
 * @param psensor Pointer to the sensor.
 * @param oid Object ID to add.
 *
 * @todo 100% matched but sensor struct offsets are wrong.
 * Doesn't match with STRUCT_OFFSET macro due to regswaps.
 */
void AddSensorNoTriggerObject(SENSOR *psensor, OID oid)
{
	uint ccur = psensor->cnoTriggerObjects;
	if (ccur >= 4)
		return;

	psensor->anoTriggerObjects[ccur] = oid;
	psensor->cnoTriggerObjects = ccur + 1;
}
#endif

INCLUDE_ASM("asm/nonmatchings/P2/sensor", AddSensorTriggerClass__FP6SENSOR3CID);
#ifdef SKIP_ASM
/**
 * @brief Add a class ID to the sensor's trigger class list.
 *
 * @param psensor Pointer to the sensor.
 * @param cid Class ID to add.
 *
 * @todo 100% matched but sensor struct offsets are wrong.
 * Doesn't match with STRUCT_OFFSET macro due to regswaps.
 */
void AddSensorTriggerClass(SENSOR *psensor, CID cid)
{
	uint ccur = psensor->ctriggerClasses;
	if (ccur >= 4)
		return;

	psensor->atriggerClasses[ccur] = cid;
	psensor->ctriggerClasses = ccur + 1;
}
#endif

INCLUDE_ASM("asm/nonmatchings/P2/sensor", AddSensorNoTriggerClass__FP6SENSOR3CID);
#ifdef SKIP_ASM
/**
 * @brief Add a class ID to the sensor's no-trigger class list.
 *
 * @param psensor Pointer to the sensor.
 * @param cid Class ID to add.
 *
 * @todo 100% matched but sensor struct offsets are wrong.
 * Doesn't match with STRUCT_OFFSET macro due to regswaps.
 */
void AddSensorNoTriggerClass(SENSOR *psensor, CID cid)
{
	uint ccur = psensor->cnoTriggerClasses;
	if (ccur >= 4)
		return;

	psensor->anoTriggerClasses[ccur] = cid;
	psensor->cnoTriggerClasses = ccur + 1;
}
#endif

INCLUDE_ASM("asm/nonmatchings/P2/sensor", InitLasen__FP5LASEN);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", LoadLasenFromBrx__FP5LASENP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", BindLasen__FP5LASEN);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", PostLasenLoad__FP5LASEN);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", UpdateBusyLasenSenseTimes__Fv);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", UpdateLasen__FP5LASENf);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", FreezeLasen__FP5LASENi);

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

INCLUDE_ASM("asm/nonmatchings/P2/sensor", RetractLasen__FP5LASENf);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", ExtendLasen__FP5LASENf);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", InitCamsen__FP6CAMSEN);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", PostCamsenLoad__FP6CAMSEN);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", UpdateCamsen__FP6CAMSENf);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", RenderCamsenSelf__FP6CAMSENP2CMP2RO);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", FIgnoreCamsenIntersection__FP6CAMSENP2SO);

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
