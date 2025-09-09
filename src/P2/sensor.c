#include <sensor.h>

INCLUDE_ASM(const s32, "P2/sensor", InitSensor__FP6SENSOR);

INCLUDE_ASM(const s32, "P2/sensor", SetSensorAlarm__FP6SENSORP5ALARM);

INCLUDE_ASM(const s32, "P2/sensor", SetSensorSensors__FP6SENSOR7SENSORS);

INCLUDE_ASM(const s32, "P2/sensor", FCheckSensorObject__FP6SENSORP2SO);

INCLUDE_ASM(const s32, "P2/sensor", FIgnoreSensorObject__FP6SENSORP2SO);

INCLUDE_ASM(const s32, "P2/sensor", FOnlySensorTriggerObject__FP6SENSORP2SO);

INCLUDE_ASM(const s32, "P2/sensor", PauseSensor__FP6SENSOR);

INCLUDE_ASM(const s32, "P2/sensor", UpdateSensor__FP6SENSORf);

INCLUDE_ASM(const s32, "P2/sensor", AddSensorTriggerObject__FP6SENSOR3OID);

INCLUDE_ASM(const s32, "P2/sensor", AddSensorNoTriggerObject__FP6SENSOR3OID);

INCLUDE_ASM(const s32, "P2/sensor", AddSensorTriggerClass__FP6SENSOR3CID);

INCLUDE_ASM(const s32, "P2/sensor", AddSensorNoTriggerClass__FP6SENSOR3CID);

INCLUDE_ASM(const s32, "P2/sensor", InitLasen__FP5LASEN);

INCLUDE_ASM(const s32, "P2/sensor", LoadLasenFromBrx__FP5LASENP18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/sensor", BindLasen__FP5LASEN);

INCLUDE_ASM(const s32, "P2/sensor", PostLasenLoad__FP5LASEN);

INCLUDE_ASM(const s32, "P2/sensor", UpdateBusyLasenSenseTimes__Fv);

INCLUDE_ASM(const s32, "P2/sensor", UpdateLasen__FP5LASENf);

INCLUDE_ASM(const s32, "P2/sensor", FreezeLasen__FP5LASENi);

INCLUDE_ASM(const s32, "P2/sensor", RenderLasenSelf__FP5LASENP2CMP2RO);

INCLUDE_ASM(const s32, "P2/sensor", FUN_001afaf8);

INCLUDE_ASM(const s32, "P2/sensor", SenseLasen__FP5LASENP7SENSORS);

INCLUDE_ASM(const s32, "P2/sensor", EnableLasen__FP5LASEN5SENSM);

INCLUDE_ASM(const s32, "P2/sensor", DisableLasen__FP5LASEN);

INCLUDE_ASM(const s32, "P2/sensor", OnLasenAlarmTriggered__FP5LASEN);

INCLUDE_ASM(const s32, "P2/sensor", SetLasenSensors__FP5LASEN7SENSORS);

INCLUDE_ASM(const s32, "P2/sensor", SCalcLasenShapeExtent__FP5LASENP5LBEAM);

INCLUDE_ASM(const s32, "P2/sensor", RetractLasen__FP5LASENf);

INCLUDE_ASM(const s32, "P2/sensor", ExtendLasen__FP5LASENf);

INCLUDE_ASM(const s32, "P2/sensor", InitCamsen__FP6CAMSEN);

INCLUDE_ASM(const s32, "P2/sensor", PostCamsenLoad__FP6CAMSEN);

INCLUDE_ASM(const s32, "P2/sensor", UpdateCamsen__FP6CAMSENf);

INCLUDE_ASM(const s32, "P2/sensor", RenderCamsenSelf__FP6CAMSENP2CMP2RO);

INCLUDE_ASM(const s32, "P2/sensor", FIgnoreCamsenIntersection__FP6CAMSENP2SO);

INCLUDE_ASM(const s32, "P2/sensor", FFilterCamsen__FPvP2SO);

INCLUDE_ASM(const s32, "P2/sensor", SenseCamsen__FP6CAMSENP7SENSORS);

INCLUDE_ASM(const s32, "P2/sensor", EnableCamsen__FP6CAMSEN5SENSM);

INCLUDE_ASM(const s32, "P2/sensor", DisableCamsen__FP6CAMSEN);

INCLUDE_ASM(const s32, "P2/sensor", OnCamsenAlarmTriggered__FP6CAMSEN);

INCLUDE_ASM(const s32, "P2/sensor", SetCamsenSensors__FP6CAMSEN7SENSORS);

INCLUDE_ASM(const s32, "P2/sensor", SetCamsenCsdts__FP6CAMSEN5CSDTS);

INCLUDE_ASM(const s32, "P2/sensor", InitPrsen__FP5PRSEN);

INCLUDE_ASM(const s32, "P2/sensor", PostPrsenLoad__FP5PRSEN);

INCLUDE_ASM(const s32, "P2/sensor", UpdatePrsen__FP5PRSENf);

INCLUDE_ASM(const s32, "P2/sensor", SensePrsen__FP5PRSENP7SENSORS);

INCLUDE_ASM(const s32, "P2/sensor", EnablePrsen__FP5PRSEN5SENSM);

INCLUDE_ASM(const s32, "P2/sensor", DisablePrsen__FP5PRSEN);

INCLUDE_ASM(const s32, "P2/sensor", OnPrsenAlarmTriggered__FP5PRSEN);

INCLUDE_ASM(const s32, "P2/sensor", SetPrsenSensors__FP5PRSEN7SENSORS);

INCLUDE_ASM(const s32, "P2/sensor", UpdatePrsenLoopShader__FP5PRSEN);
