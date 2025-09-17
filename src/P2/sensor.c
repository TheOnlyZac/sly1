#include <sensor.h>

INCLUDE_ASM("asm/nonmatchings/P2/sensor", InitSensor__FP6SENSOR);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", SetSensorAlarm__FP6SENSORP5ALARM);

INCLUDE_ASM("asm/nonmatchings/P2/sensor", SetSensorSensors__FP6SENSOR7SENSORS);

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

INCLUDE_ASM("asm/nonmatchings/P2/sensor", FUN_001afaf8);

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
