/**
 * @file alarm.h
 *
 * @brief Alarm system.
 */
#ifndef ALARM_H
#define ALARM_H

#include "common.h"
#include <break.h>
#include <sound.h>
#include <oid.h>
#include <dl.h>
#include <so.h>

// Forward.
struct SENSOR;

/**
 * @brief Alarm state.
 */
enum ALARMS
{
    ALARMS_Nil = -1,
    ALARMS_Enabled = 0,
    ALARMS_Disabled = 1,
    ALARMS_Triggered = 2,
    ALARMS_Max = 3
};

/**
 * @brief Alarm trigger kind.
 */
enum ALTK
{
    ALTK_Nil = -1,
    ALTK_Trigger = 0,
    ALTK_Untrigger = 1,
    ALTK_Disable = 2,
    ALTK_Max = 3
};

/**
 * @class ALARM
 * @brief Alarm object that controls some sensors.
 */
struct ALARM : public SO
{
    /* 0x550 */ ALARMS alarms; // current alarm state
    float tAlarms;
    SM *psm;
    SMA *psma;
    float dtReset;
    /* 0x564 */ int calbrks;       // count of breakables
    /* 0x568 */ OID aoidAlbrks[4]; // array of breakable OIDs
    /* 0x578 */ int coidSensors;
    /* 0x57c */ OID aoidSensors[16];
    /* 0x5bc */ int cpsensors;
    /* 0x5c0 */ SENSOR *apsensors[16];
    /* 0x600 */ int coidStepguards;
    /* 0x604 */ OID aoidStepguards[6];
    /* 0x61c */ int calbrksDisabled;
    AMB *pambSiren;
    EXC *pexc;
    int fSilent;
    /* 0x62c */ int crsmg;
    /* 0x630 */ RSMG arsmg[8];
    /* 0x6b0 */ int ichkDisabled;
};

/**
 * @class ALARM_BREAKABLE
 * @brief Breakable alarm.
 */
struct ALBRK : public BRK
{
    // ...
    /* 0x6c0 */ ALARM *palarm;
};

void BreakAlbrk(ALBRK *palbrk);

void SetAlbrkAlarm(ALBRK *palbrk, ALARM *palarm);

void InitAlarm(ALARM *palarm);

void PostAlarmLoad(ALARM *palarm);

void CloneAlarm(ALARM *palarm, ALARM *palarmBase);

void UpdateAlarm(ALARM *palarm, float dt);

void PostAlarmLoadCallbackHookup(ALARM *palarm, MSGID msgid, void *pv);

void SetAlarmAlarms(ALARM *palarm, ALARMS alarms);

void TriggerAlarm(ALARM *palarm, ALTK altk);

void DisableAlarmAlbrk(ALARM *palarm);

void EnableAlarmSensors(ALARM *palarm);

void DisableAlarmSensors(ALARM *palarm);

void NotifyAlarmSensorsOnTrigger(ALARM *palarm);

/**
 * @brief Adds a breakable alarm object to the alarm's list.
 *
 * @param palarm Pointer to the alarm.
 * @param oid Object ID of the breakable alarm to add (max 4).
 */
void AddAlarmAlbrk(ALARM *palarm, OID oid);

/**
 * @brief Adds a sensor object to the alarm's sensor list.
 *
 * @param palarm Pointer to the alarm.
 * @param oid Object ID of the sensor to add (max 16).
 */
void AddAlarmSensor(ALARM *palarm, OID oid);

/**
 * @brief Adds a stepguard object to the alarm's stepguard list.
 *
 * @param palarm Pointer to the alarm.
 * @param oid Object ID of the stepguard to add (max 6).
 */
void AddAlarmStepguard(ALARM *palarm, OID oid);

void SetAlarmRsmg(ALARM *palarm, int fOnTrigger, OID oidRoot, OID oidSM, OID oidGoal);

int FGetAlarmSensorList(ALARM *palarm, void *pvstate);

#endif // ALARM_H
