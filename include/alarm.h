/**
 * @file alarm.h
 *
 * @brief Alarm system.
 */
#ifndef ALARM_H
#define ALARM_H

#include "common.h"
#include <sensor.h>
#include <break.h>
#include <sound.h>
#include <oid.h>
#include <dl.h>
#include <so.h>

/**
 * @brief Unknown.
 * @todo Move elsewhere?
 */
struct EXC
{
    int iexc;
    DLE dle;
};

/**
 * @brief Alarm State.
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
 * @brief Alarm Trigger Kind.
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
 * @brief Unknown.
 */
struct ALBRK : public BRK
{
    // ...
};

/**
 * @brief Alarm.
 */
struct ALARM : public SO
{
    ALARMS alarms;
    float tAlarms;
    SM *psm;
    SMA *psma;
    float dtReset;
    int calbrks;
    OID aoidAlbrks[4];
    int coidSensors;
    OID aoidSensors[16];
    int cpsensors;
    SENSOR *apsensors[16];
    int coidStepguards;
    OID aoidStepguards[6];
    int calbrksDisabled;
    AMB *pambSiren;
    EXC *pexc;
    int fSilent;
    int crsmg;
    RSMG arsmg[8];
    int ichkDisabled;
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

void AddAlarmAlbrk(ALARM *palarm, OID oid);

void AddAlarmSensor(ALARM *palarm, OID oid);

void AddAlarmStepguard(ALARM *palarm, OID oid);

void SetAlarmRsmg(ALARM *palarm, int fOnTrigger, OID oidRoot, OID oidSM, OID oidGoal);

int FGetAlarmSensorList(ALARM *palarm, void *pvstate);

#endif // ALARM_H
