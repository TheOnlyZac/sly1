#pragma once
#include <actseg.h>
#include <clock.h>
#include <game.h>
#include <sensor.h>
#include <sw.h>

typedef uint32_t ALTK;

enum class MSGID // Temporary?
{
    water_entered = 10,
    water_left = 11,
    break_break = 14,
    button_trigger = 12,
    sfx_start = 8,
    break_piece = 15,
    damaged = 23,
    param_read = 24,
    label = 19,
    sma_transition = 20,
    waypoint_transition = 22,
    button_untrigger = 13,
    param_write = 25,
    callback = 0,
    added = 1,
    user_message = 18,
    removed = 2,
    Max = 26,
    waypoint = 21,
    asega_retracted = 6,
    asega_limit = 5,
    rip_removed = 16,
    translated = 3,
    asega_wrapped = 7,
    rotated = 4,
    color_change = 17,
    sfx_end = 9
};

enum class ALARMS
{
    Enabled = 0,
    Disabled = 1,
    Triggered = 2,
    Max = 3
};

struct ALARM 
{
    
    ALARMS alarms_unk;
    float field_0x554;
    undefined4 field_0x558;
    undefined4 field_0x55c;
    undefined4 field_0x560;
    int field_0x564;
    undefined4 field_0x568;
    undefined4 field_0x56c;
    undefined4 field_0x570;
    undefined4 field_0x574;
    undefined4 field_0x578;
    undefined4 field_0x57c;
    ALARMS alarms;
    float tAlarms;
    float dtReset;
    int calbrks;
    int coidSensors;
    undefined4 field_0x5ac;
    undefined4 field_0x5b0;
    undefined4 field_0x5b4;
    undefined4 field_0x5b8;
    undefined4 field_0x5bc;
    byte field_0x5c0;
    byte field_0x5c1;
    byte field_0x5c2;
    int cpsensors;
    struct SENSOR* apsensors[16];
    int coidStepguards;
    int calbrksDisabled;
    int fSilent;
    int crsmg;
    //struct RSMG_22 arsmg[8];
    int ichkDisabled;
};

struct ALBRK
{
    ALARM* palarm;
};

void AddAlarmStepguard(ALARM* palarm, OID poid);
void BreakAlbrk(ACTLA* pactla);
void CloneAlarm(ALARM* palarm, ALARM* palarmBase);
void DisableAlarmAlbrk(ALARM* palarm);
void DisableAlarmSensors(ALARM* palarm);
void EnableAlarmSensors(ALARM* palarm);
int FGetAlarmSensorList(ALARM* palarm, void* pv);
void PostAlarmLoad(ALARM* palarm);
void PostAlarmLoadCallbackHookup(ALARM* palarm, MSGID msgid, void* pv);
void SetAlarmAlarms(ALARM* palarm, ALARMS alarms);
uint32_t SetAlarmRsmg(ALARM* palarm, int param_2, OID param_3, OID param_4, OID param_5);
void SetAlbrkAlarm(ALBRK* palarm, ALARM* param_2);
void TriggerAlarm(ALARM* palarm, ALTK atlk);
//void UpdateAlarm(ALARM* palarm, Entity* param_2);
