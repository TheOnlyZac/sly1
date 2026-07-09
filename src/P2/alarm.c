#include <alarm.h>
#include <chkpnt.h>
#include <button.h>
#include <sensor.h>

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

INCLUDE_ASM("asm/nonmatchings/P2/alarm", PostAlarmLoad__FP5ALARM);

void CloneAlarm(ALARM *palarm, ALARM *palarmBase)
{
    int ichkDisabled = STRUCT_OFFSET(palarm, 0x6b0, int); // palarm->ichkDisabled
    CloneSo(palarm, palarmBase);
    STRUCT_OFFSET(palarm, 0x6b0, int) = ichkDisabled; // palarm->ichkDisabled
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

void EnableAlarmSensors(ALARM *palarm)
{
    int i;

    for (i = 0; i < STRUCT_OFFSET(palarm, 0x5bc, int); i++)
    {
        SENSOR *psensor = ((SENSOR **)((uint8_t *)palarm + 0x5c0))[i];
        if (STRUCT_OFFSET(psensor, 0x560, int) == -1)
        {
            void (*pfn)(SENSOR *, int) = (void (*)(SENSOR *, int))STRUCT_OFFSET(psensor->pvtlo, 0x134, void *);
            if (pfn != 0)
            {
                pfn(psensor, 0);
            }
        }
    }
}

void DisableAlarmSensors(ALARM *palarm)
{
    int ipsensor;

    for (ipsensor = 0; ipsensor < STRUCT_OFFSET(palarm, 0x5bc, int); ipsensor++) // palarm->cpsensors
    {
        SENSOR *psensor = STRUCT_OFFSET_INDEX(palarm, 0x5c0, SENSOR *, ipsensor); // palarm->apsensors[ipsensor]
        void **ppvtable = (void **)STRUCT_OFFSET(psensor, 0x0, void *);
        void (*pfn)(SENSOR *) = (void (*)(SENSOR *))STRUCT_OFFSET(ppvtable, 0x138, void *);

        if (pfn != NULL)
            pfn(psensor);
    }
}

void NotifyAlarmSensorsOnTrigger(ALARM *palarm)
{
    int ipsensor;

    for (ipsensor = 0; ipsensor < STRUCT_OFFSET(palarm, 0x5bc, int); ipsensor++) // palarm->cpsensors
    {
        SENSOR *psensor = STRUCT_OFFSET_INDEX(palarm, 0x5c0, SENSOR *, ipsensor); // palarm->apsensors[ipsensor]
        void **ppvtable = (void **)STRUCT_OFFSET(psensor, 0x0, void *);
        void (*pfn)(SENSOR *) = (void (*)(SENSOR *))STRUCT_OFFSET(ppvtable, 0x13c, void *);

        if (pfn != NULL)
            pfn(psensor);
    }
}

void AddAlarmAlbrk(ALARM *palarm, OID oid)
{
    uint calbrks = STRUCT_OFFSET(palarm, 0x564, int); // palarm->calbrks

    if (calbrks < 4) // Max 4 breakable alarms
    {
        // Add new breakable object ID to the list
        STRUCT_OFFSET_INDEX(palarm, 0x568, OID, calbrks) = oid; // palarm->aoidAlbrks[calbrks]
        STRUCT_OFFSET(palarm, 0x564, int) = calbrks + 1;        // palarm->calbrks
    }
}

void AddAlarmSensor(ALARM *palarm, OID oid)
{
    uint coidSensors = STRUCT_OFFSET(palarm, 0x578, int); // palarm->coidSensors

    if (coidSensors < 16) // Max 16 sensors
    {
        // Add new sensor object ID to the list
        STRUCT_OFFSET_INDEX(palarm, 0x57c, OID, coidSensors) = oid; // palarm->aoidSensors[coidSensors]
        STRUCT_OFFSET(palarm, 0x578, int) = coidSensors + 1; // palarm->coidSensors
    }
}

void AddAlarmStepguard(ALARM *palarm, OID oid)
{
    uint coidStepguards = STRUCT_OFFSET(palarm, 0x600, int); // palarm->coidStepguards

    if (coidStepguards < 6) // Max 6 stepguards
    {
        // Add new stepguard object ID to the list
        STRUCT_OFFSET_INDEX(palarm, 0x604, OID, coidStepguards) = oid; // palarm->aoidStepguards[coidStepguards]
        STRUCT_OFFSET(palarm, 0x600, int) = coidStepguards + 1; // palarm->coidStepguards
    }
}

void SetAlarmRsmg(ALARM *palarm, int fOnTrigger, OID oidRoot, OID oidSM, OID oidGoal)
{
    // palarm->arsmg & palarm->crsmg
    FAddRsmg(&STRUCT_OFFSET(palarm, 0x630, RSMG), 8, &STRUCT_OFFSET(palarm, 0x62c, int), fOnTrigger, oidRoot, oidSM, oidGoal);
}

INCLUDE_ASM("asm/nonmatchings/P2/alarm", FGetAlarmSensorList__FP5ALARMPv);
