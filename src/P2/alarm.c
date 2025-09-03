#include <alarm.h>
#include <chkpnt.h>
#include <button.h>

void BreakAlbrk(ALBRK *palbrk)
{
    if (STRUCT_OFFSET(palbrk, 0x680, int) == 0)
    {
        DisableAlarmAlbrk(STRUCT_OFFSET(palbrk, 0x6c0, ALARM *)); // palbrk->palarm
    }

    BreakBrk(palbrk);
}

void SetAlbrkAlarm(ALBRK *palbrk, ALARM *palarm)
{
    STRUCT_OFFSET(palbrk, 0x6c0, ALARM *) = palarm; // palbrk->palarm
}

void InitAlarm(ALARM *palarm)
{
    InitSo(palarm);
    STRUCT_OFFSET(palarm, 0x550, ALARMS) = ALARMS_Nil; // palarm->alarms
    STRUCT_OFFSET(palarm, 0x6b0, int) = IchkAllocChkmgr(&g_chkmgr); // palarm->ichkDisabled
}

INCLUDE_ASM(const s32, "P2/alarm", PostAlarmLoad__FP5ALARM);

void CloneAlarm(ALARM *palarm, ALARM *palarmBase)
{
    int ichkDisabled = STRUCT_OFFSET(palarm, 0x6b0, int); // palarm->ichkDisabled
    CloneSo(palarm, palarmBase);
    STRUCT_OFFSET(palarm, 0x6b0, int) = ichkDisabled; // palarm->ichkDisabled
}

INCLUDE_ASM(const s32, "P2/alarm", UpdateAlarm__FP5ALARMf);

INCLUDE_ASM(const s32, "P2/alarm", PostAlarmLoadCallbackHookup__FP5ALARM5MSGIDPv);

INCLUDE_ASM(const s32, "P2/alarm", SetAlarmAlarms__FP5ALARM6ALARMS);

void TriggerAlarm(ALARM *palarm, ALTK altk)
{
    ALARMS alarms;

    switch (altk)
    {
        case ALTK_Trigger:
            alarms = ALARMS_Triggered;
            break;
        case ALTK_Untrigger:
            alarms = ALARMS_Enabled;
            break;
        case ALTK_Disable:
            alarms = ALARMS_Disabled;
            break;
        default:
            return;
    }

    SetAlarmAlarms(palarm, alarms);
}

void DisableAlarmAlbrk(ALARM *palarm)
{
    STRUCT_OFFSET(palarm, 0x61c, int)++; // palarm->calbrksDisabled
}

INCLUDE_ASM(const s32, "P2/alarm", EnableAlarmSensors__FP5ALARM);

INCLUDE_ASM(const s32, "P2/alarm", DisableAlarmSensors__FP5ALARM);

INCLUDE_ASM(const s32, "P2/alarm", NotifyAlarmSensorsOnTrigger__FP5ALARM);

INCLUDE_ASM(const s32, "P2/alarm", AddAlarmAlbrk__FP5ALARM3OID);

INCLUDE_ASM(const s32, "P2/alarm", AddAlarmSensor__FP5ALARM3OID);

INCLUDE_ASM(const s32, "P2/alarm", AddAlarmStepguard__FP5ALARM3OID);

void SetAlarmRsmg(ALARM *palarm, int fOnTrigger, OID oidRoot, OID oidSM, OID oidGoal)
{
    // palarm->arsmg & palarm->crsmg
    FAddRsmg(&STRUCT_OFFSET(palarm, 0x630, RSMG), 8, &STRUCT_OFFSET(palarm, 0x62c, int), fOnTrigger, oidRoot, oidSM, oidGoal);
}

INCLUDE_ASM(const s32, "P2/alarm", FGetAlarmSensorList__FP5ALARMPv);
