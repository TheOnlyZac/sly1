#include <alarm.h>
#include <chkpnt.h>
#include <button.h>
#include <spliceobj.h>

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
    palarm->alarms = ALARMS_Nil;
    palarm->ichkDisabled = IchkAllocChkmgr(&g_chkmgr);
}

INCLUDE_ASM("asm/nonmatchings/P2/alarm", PostAlarmLoad__FP5ALARM);

void CloneAlarm(ALARM *palarm, ALARM *palarmBase)
{
    int ichkDisabled = palarm->ichkDisabled;
    CloneSo(palarm, palarmBase);
    palarm->ichkDisabled = ichkDisabled;
}

INCLUDE_ASM("asm/nonmatchings/P2/alarm", UpdateAlarm__FP5ALARMf);

INCLUDE_ASM("asm/nonmatchings/P2/alarm", PostAlarmLoadCallbackHookup__FP5ALARM5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/alarm", SetAlarmAlarms__FP5ALARM6ALARMS);

void TriggerAlarm(ALARM *palarm, ALTK altk)
{
    ALARMS alarms;

    switch (altk)
    {
        case ALTK_Trigger:
        {
            alarms = ALARMS_Triggered;
            break;
        }
        case ALTK_Untrigger:
        {
            alarms = ALARMS_Enabled;
            break;
        }
        case ALTK_Disable:
        {
            alarms = ALARMS_Disabled;
            break;
        }
        default:
        {
            return;
        }
    }

    SetAlarmAlarms(palarm, alarms);
}

void DisableAlarmAlbrk(ALARM *palarm)
{
    palarm->calbrksDisabled++;
}

INCLUDE_ASM("asm/nonmatchings/P2/alarm", EnableAlarmSensors__FP5ALARM);

INCLUDE_ASM("asm/nonmatchings/P2/alarm", DisableAlarmSensors__FP5ALARM);

INCLUDE_ASM("asm/nonmatchings/P2/alarm", NotifyAlarmSensorsOnTrigger__FP5ALARM);

void AddAlarmAlbrk(ALARM *palarm, OID oid)
{
    if ((uint)palarm->calbrks < 4) // Max 4 breakable alarms
    {
        // Add new breakable object ID to the list
        palarm->aoidAlbrks[palarm->calbrks++] = oid;
    }
}

void AddAlarmSensor(ALARM *palarm, OID oid)
{
    if ((uint)palarm->coidSensors < 16) // Max 16 sensors
    {
        // Add new sensor object ID to the list
        palarm->aoidSensors[palarm->coidSensors++] = oid;
    }
}

void AddAlarmStepguard(ALARM *palarm, OID oid)
{
    if ((uint)palarm->coidStepguards < 6) // Max 6 stepguards
    {
        // Add new stepguard object ID to the list
        palarm->aoidStepguards[palarm->coidStepguards++] = oid;
    }
}

void SetAlarmRsmg(ALARM *palarm, int fOnTrigger, OID oidRoot, OID oidSM, OID oidGoal)
{
    FAddRsmg(palarm->arsmg, 8, &palarm->crsmg, fOnTrigger, oidRoot, oidSM, oidGoal);
}

int FGetAlarmSensorList(ALARM *palarm, void *pvstate)
{
    for (int i = 0; i < palarm->cpsensors; i++)
    {
        if (FAppendSpliceListElement(pvstate, &palarm->apsensors[i]) == 0)
        {
            return 0;
        }
    }

    return 1;
}
