#include <actseg.h>
#include <clock.h>
#include <game.h>
#include <sensor.h>
#include <sw.h>

typedef uint32_t ALTK;

enum MSGID //This will be here temporarily
{
    MSGID_water_entered = 10,
    MSGID_water_left = 11,
    MSGID_break_break = 14,
    MSGID_button_trigger = 12,
    MSGID_sfx_start = 8,
    MSGID_break_piece = 15,
    MSGID_damaged = 23,
    MSGID_param_read = 24,
    MSGID_label = 19,
    MSGID_sma_transition = 20,
    MSGID_waypoint_transition = 22,
    MSGID_button_untrigger = 13,
    MSGID_param_write = 25,
    MSGID_callback = 0,
    MSGID_added = 1,
    MSGID_user_message = 18,
    MSGID_removed = 2,
    MSGID_Max = 26,
    MSGID_waypoint = 21,
    MSGID_asega_retracted = 6,
    MSGID_asega_limit = 5,
    MSGID_rip_removed = 16,
    MSGID_translated = 3,
    MSGID_asega_wrapped = 7,
    MSGID_rotated = 4,
    MSGID_color_change = 17,
    MSGID_sfx_end = 9
};

enum ALARMS
{
    ALARMS_Disabled = 1,
    ALARMS_Max = 3,
    ALARMS_Enabled = 0,
    ALARMS_Triggered = 2
};

struct ALARM 
{
    
    enum ALARMS state;
    float field_0x554;
    byte field_0x555;
    byte field_0x556;
    byte field_0x557;
    byte field_0x558;
    byte field_0x559;
    byte field_0x55a;
    byte field_0x55b;
    byte field_0x55c;
    byte field_0x55d;
    byte field_0x55e;
    byte field_0x55f;
    byte field_0x560;
    byte field_0x561;
    byte field_0x562;
    byte field_0x563;
    byte field_0x564;
    byte field_0x565;
    byte field_0x566;
    byte field_0x567;
    byte field_0x568;
    byte field_0x569;
    byte field_0x56a;
    byte field_0x56b;
    byte field_0x56c;
    byte field_0x56d;
    byte field_0x56e;
    byte field_0x56f;
    byte field_0x570;
    byte field_0x571;
    byte field_0x572;
    byte field_0x573;
    byte field_0x574;
    byte field_0x575;
    byte field_0x576;
    byte field_0x577;
    byte field_0x578;
    byte field_0x579;
    byte field_0x57a;
    byte field_0x57b;
    byte field_0x57c;
    byte field_0x57d;
    byte field_0x57e;
    byte field_0x57f;
    enum ALARMS alarms;
    float tAlarms;
    float dtReset;
    int calbrks;
    int coidSensors;
    byte field_0x5ac;
    byte field_0x5ad;
    byte field_0x5ae;
    byte field_0x5af;
    byte field_0x5b0;
    byte field_0x5b1;
    byte field_0x5b2;
    byte field_0x5b3;
    byte field_0x5b4;
    byte field_0x5b5;
    byte field_0x5b6;
    byte field_0x5b7;
    byte field_0x5b8;
    byte field_0x5b9;
    byte field_0x5ba;
    byte field_0x5bb;
    byte field_0x5bc;
    byte field_0x5bd;
    byte field_0x5be;
    byte field_0x5bf;
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
void UpdateAlarm(ALARM* palarm, Entity* param_2);
