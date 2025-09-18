#ifndef SENSOR_H
#define SENSOR_H

#include "common.h"
#include <alarm.h>
#include <oid.h>
#include <so.h>
#include <cm.h>

// Forward.
struct RO;

/**
 * @brief Sensor state.
 */
enum SENSORS
{
    SENSORS_Nil = -1,
    SENSORS_SenseEnabling = 0,
    SENSORS_SenseEnabled = 1,
    SENSORS_SenseTriggered = 2,
    SENSORS_SenseDisabling = 3,
    SENSORS_DamageEnabling = 4,
    SENSORS_DamageEnabled = 5,
    SENSORS_DamageTriggered = 6,
    SENSORS_DamageDisabling = 7,
    SENSORS_Disabled = 8,
    SENSORS_Max = 9
};

/**
 * @brief Sensor mode.
 */
enum SENSM
{
    SENSM_Nil = -1,
    SENSM_SenseOnly = 0,
    SENSM_DamageTarget = 1,
    SENSM_Max = 2
};


/**
 * @brief (?) state.
 */
enum CSDTS
{
    CSDTS_Nil = -1,
    CSDTS_Focus = 0,
    CSDTS_Zap = 1,
    CSDTS_Unfocus = 2,
    CSDTS_Max = 3,
};

/**
 * @class _SENSOR
 * @brief Base class for security sensors.
 * @todo Implement the struct.
 */
struct SENSOR : public SO
{
    /* 0x550 */ ALARM *palarm; // Pointer to the alarm this sensor is associated with.
    STRUCT_PADDING(1);
    /* 0x558 */ SENSORS sensors; // Current sensor state.
    STRUCT_PADDING(2);
    /* 0x564 */ uint ctriggerObjects; // Current count of trigger object IDs.
    /* 0x568 */ OID atriggerObjects[4]; // Array of trigger object IDs.
    STRUCT_PADDING(4);
    /* 0x578 */ uint cnoTriggerObjects; // Current count of no-trigger object IDs.
    /* 0x57C */ OID anoTriggerObjects[4]; // Array of no-trigger object IDs.
    STRUCT_PADDING(4);
    /* 0x58c */ uint ctriggerClasses; // Current count of trigger class IDs.
    /* 0x590 */ CID atriggerClasses[4]; // Array of trigger class IDs.
    STRUCT_PADDING(4);
    /* 0x5a0 */ uint cnoTriggerClasses; // Current count of no-trigger class IDs.
    /* 0x5a4 */ CID anoTriggerClasses[4]; // Array of no-trigger class IDs.
};

/**
 * @class LASER_SENSOR
 * @brief Laser sensor for alarm systems.
 * @todo Implement the struct.
 */
struct LASEN : public SENSOR
{
    // ...
};

/**
 * @class CAMERA_SENSOR
 * @brief Camera sensor for alarm system.
 * @todo Implement the struct.
 */
struct CAMSEN : public SENSOR
{
    // ...
};

/**
 * @class PRESSURE_SENSOR
 * @brief Pressusre sensor for alarm systems.
 * @todo Implement the struct.
 */
struct PRSEN : public SENSOR
{
    // ...
};

/**
 * @brief Laser beam?
 * @todo Implement the struct.
 */
struct LBEAM
{
    // ...
};

void InitSensor(SENSOR *psensor);

void SetSensorAlarm(SENSOR *psensor, ALARM *palarm);

void SetSensorSensors(SENSOR *psensor, SENSORS sensors);

int FCheckSensorObject(SENSOR *psensor, SO *psoOther);

int FIgnoreSensorObject(SENSOR *psensor, SO *psoOther);

int FOnlySensorTriggerObject(SENSOR *psensor, SO *psoOther);

void PauseSensor(SENSOR *psensor);

void UpdateSensor(SENSOR *psensor, float dt);

/**
 * @brief Add an object ID to the sensor's trigger list.
 *
 * @param psensor Pointer to the sensor.
 * @param oid Object ID to add.
 */
void AddSensorTriggerObject(SENSOR *psensor, OID oid);

/**
 * @brief Add an object ID to the sensor's no-trigger list.
 *
 * @param psensor Pointer to the sensor.
 * @param oid Object ID to add.
 */
void AddSensorNoTriggerObject(SENSOR *psensor, OID oid);

/**
 * @brief Add a class ID to the sensor's trigger class list.
 *
 * @param psensor Pointer to the sensor.
 * @param cid Class ID to add.
 */
void AddSensorTriggerClass(SENSOR *psensor, CID cid);

/**
 * @brief Add a class ID to the sensor's no-trigger class list.
 *
 * @param psensor Pointer to the sensor.
 * @param cid Class ID to add.
 */
void AddSensorNoTriggerClass(SENSOR *psensor, CID cid);

void InitLasen(LASEN *plasen);

void LoadLasenFromBrx(LASEN *plasen, CBinaryInputStream *pbis);

void BindLasen(LASEN *plasen);

void PostLasenLoad(LASEN *plasen);

void UpdateBusyLasenSenseTimes();

void UpdateLasen(LASEN *plasen, float dt);

void FreezeLasen(LASEN *plasen, int fFreeze);

void RenderLasenSelf(LASEN *plasen, CM *pcm, RO *pro);

int FFilterLasen(void *pv, SO *pso);

void SenseLasen(LASEN *plasen, SENSORS *psensors);

void EnableLasen(LASEN *plasen, SENSM sensm);

void DisableLasen(LASEN *plasen);

void OnLasenAlarmTriggered(LASEN *plasen);

void SetLasenSensors(LASEN *plasen, SENSORS sensors);

float SCalcLasenShapeExtent(LASEN *plasen, LBEAM *plbeam);

void RetractLasen(LASEN *plasen, float dtRetract);

void ExtendLasen(LASEN *plasen, float dtExpand);


void InitCamsen(CAMSEN *pcamsen);

void PostCamsenLoad(CAMSEN *pcamsen);

void UpdateCamsen(CAMSEN *pcamsen, float dt);

void RenderCamsenSelf(CAMSEN *pcamsen, CM *pcm, RO *pro);

int FIgnoreCamsenIntersection(CAMSEN *pcamsen, SO *psoOther);

int FFilterCamsen(void *pv, SO *pso);

void SenseCamsen(CAMSEN *pcamsen, SENSORS *psensors);

void EnableCamsen(CAMSEN *pcamsen, SENSM sensm);

void DisableCamsen(CAMSEN *pcamsen);

void OnCamsenAlarmTriggered(CAMSEN *pcamsen);

void SetCamsenSensors(CAMSEN *pcamsen, SENSORS sensors);

void SetCamsenCsdts(CAMSEN *pcamsen, CSDTS csdts);


void InitPrsen(PRSEN *pprsen);

void PostPrsenLoad(PRSEN *pprsen);

void UpdatePrsen(PRSEN *pprsen, float dt);

void SensePrsen(PRSEN *pprsen, SENSORS *psensors);

void EnablePrsen(PRSEN *pprsen, SENSM sensm);

void DisablePrsen(PRSEN *pprsen);

void OnPrsenAlarmTriggered(PRSEN *pprsen);

void SetPrsenSensors(PRSEN *pprsen, SENSORS sensors);

void UpdatePrsenLoopShader(PRSEN *pprsen);

#endif // SENSOR_H
