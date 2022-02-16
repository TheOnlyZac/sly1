#include <alarm.h>

void AddAlarmStepguard(ALARM* palarm, OID poid)
{
    //FUN_00140640(&palarm->field_0x5c0, (long)(int)palarm, poid);
    return;
}

void BreakAlbrk(ACTLA* param_1)
{
    if (*(int*)(param_1 + 0x680) == 0) 
    {
        DisableAlarmAlbrk(*(ALARM**)(param_1 + 0x6c0));
    }
    //BreakBrk((BRK*)param_1);
    return;
}

void CloneAlarm(SO* param_1, SO* param_2)

{
    uint32_t uVar1;

    //uVar1 = param_1 + 0x6b0;
    //CloneSo(param_1, param_2);
    //param_1 + 0x6b0 = uVar1;
    return;
}

void DisableAlarmAlbrk(ALARM* param_1)
{
    param_1->apsensors[0xb] = (SENSOR*)&param_1->apsensors[0xb]->field_0x1;
    return;
}

void DisableAlarmSensors(ALARM* param_1)
{
    int iVar1;
    SENSOR* ppiVar2;
    int iVar2;

    iVar2 = 0;
    if (0 < param_1->field_0x5bc) 
    {
        ppiVar2 = (SENSOR*)&param_1->field_0x5c0;
        do 
        {
            if (ppiVar2 + 0x138 == 0x0) 
            {
                iVar1 = param_1->field_0x5bc;
            }
            else 
            {
                //(**(int**)ppiVar2 + 0x138); GOTTA COME BAK TO THIS
                iVar1 = param_1->field_0x5bc;
            }
            iVar2 = iVar2 + 1;
            ppiVar2 = (SENSOR*)&ppiVar2->field_0x4;
        } while (iVar2 < iVar1);
    }
    return;
}

void EnableAlarmSensors(ALARM* param_1)
{
    int* piVar1;
    int iVar2;
    SENSOR* ppiVar3;
    int iVar3;

    iVar3 = 0;
    if (0 < param_1->field_0x5bc) 
    {
        ppiVar3 = (SENSOR*)&param_1->field_0x5c0;
        do 
        {
            piVar1 = *(int**)ppiVar3;
            if (piVar1[0x158] == -1) 
            {
                if (piVar1 + 0x134 == 0x0) 
                {
                    iVar2 = param_1->field_0x5bc;
                }
                else 
                {
                    //(**(code**)(*piVar1 + 0x134))(piVar1, 0); GOTTA COME BACK TO THIS
                    iVar2 = param_1->field_0x5bc;
                }
            }
            else 
            {
                iVar2 = param_1->field_0x5bc;
            }
            iVar3 = iVar3 + 1;
            ppiVar3 = (SENSOR*)&ppiVar3->field_0x4;
        } while (iVar3 < iVar2);
    }
    return;
}

int FGetAlarmSensorList(ALARM* param_1, void* param_2)
{
    long lVar1;
    SENSOR* ppiVar2;
    int iVar2;

    iVar2 = 0;
    if (0 < param_1->field_0x5bc) 
    {
        ppiVar2 = (SENSOR*)&param_1->field_0x5c0;
        do 
        {
            //lVar1 = FAppendSpliceListElement(param_2, ppiVar2);
            if (lVar1 == 0) 
            {
                return 0;
            }
            iVar2 = iVar2 + 1;
            ppiVar2 = (SENSOR*)&ppiVar2->field_0x4;
        } while (iVar2 < param_1->field_0x5bc);
    }
    return 1;
}
void InitAlarm(ALARM* pAlarm)
{

    uint32_t uVar1 = 0;

    //InitSo((SO*)pAlarm);
    //pAlarm->state = ~ALARMS_Enabled;
    //uVar1 = IchkAllocChkmgr(&g_chkmgr);
    //*(uint32_t*)&pAlarm->arsmg[6].field_0x2 = uVar1;
    return;
}

void PostAlarmLoad(ALARM* param_1)
{
    //LinkedListNode* lst_head;
    int iVar1;
    //SMA* uVar2;
    int local_50;
   // LinkedListNode** local_4c;
    OID local_48;
    sw* local_44;
    
    //PostSwCallback(*(SW**)&param_1->field_0x14, PostAlarmLoadCallbackHookup, param_1, 0, (void*)0x0);
    //PostAloLoad((ALO*)param_1);
    //local_50 = &param_1->field_0x34;
    //local_48 = *(OID*)&param_1->field_0x3c;
    //local_44 = DLI::s_pdliFirst;
    //lst_head = *(LinkedListNode**)&param_1->field_0x34;
    //local_4c = (LinkedListNode**)((int)&lst_head->next + local_48);
    //DLI::s_pdliFirst = (SW*)&local_50;

    //while (lst_head != 0x0) 
    {
        //iVar1 = FIsBasicDerivedFrom(lst_head, 0x88);
        if ((iVar1 != 0) && (*(int*)&param_1->field_0x558 == 0)) 
        {
            //&param_1->field_0x558 = lst_head;
        }
        //lst_head = *local_4c;
        //local_4c = (LinkedListNode**)((int)&lst_head->next + local_48);
    }

    if (&param_1->field_0x558 != 0x0) 
    {
       // uVar2 = (SMA*)PsmaApplySm(*(SM**)&param_1->field_0x558, (ALO*)param_1, ~OID_Unknown, 1);
        //&param_1->field_0x55c = uVar2;
        //SnipLo(*(LO**)&param_1->field_0x558);
    }
    //DLI::s_pdliFirst = local_44;
    return;
}

void PostAlarmLoadCallbackHookup(ALARM* alarm, MSGID param_2, void* param_3)
{
    //LinkedListNode* pLVar1;
    int iVar2;
    SENSOR* lst_head;
    uint64_t uVar3;
    int iVar4;
    OID** ppOVar5;
    SENSOR** ppSVar6;
    int iVar7;

    iVar7 = 0;
    iVar4 = 0;
    if (0 < *(int*)&alarm->field_0x564) 
    {
        ppOVar5 = (OID**)&alarm->field_0x568;
        do 
        {
            //pLVar1 = (LinkedListNode*) PloFindSwObject(*(SW**)&alarm->field_0x14, 0x104, *ppOVar5, (Entity*)alarm);
            //if ((pLVar1 != (LinkedListNode*)0x0) && (iVar2 = FIsBasicDerivedFrom(pLVar1, 0x22), iVar2 != 0)) 
            {
                //SetAlbrkAlarm((int)pLVar1, alarm);
                iVar7 = iVar7 + 1;
            }
            iVar4 = iVar4 + 1;
            ppOVar5 = ppOVar5 + 1;
        } while (iVar4 < *(int*)&alarm->field_0x564);
    }
    iVar4 = 0;
    *(int*)&alarm->field_0x564 = iVar7;
    if (0 < *(int*)&alarm->field_0x578) 
    {
        ppOVar5 = (OID**)&alarm->field_0x57c;
        do {
            //lst_head = (SENSOR*) PloFindSwObject(*(SW**)&alarm->field_0x14, 0x104, *ppOVar5, (Entity*)alarm);

            //if ((lst_head != (SENSOR*)0x0) && (iVar7 = FIsBasicDerivedFrom((LinkedListNode*)lst_head, 0x30), iVar7 != 0))
            {
                iVar7 = alarm->field_0x5bc;
                alarm->apsensors[iVar7 + -0xc] = lst_head;
                alarm->field_0x5bc = iVar7 + 1;
                //(*(code*)(*(LinkedListNode**)&lst_head->field_0x0)[0x28].next)(lst_head, alarm); GOTTA COME BACK TO THIS
            }
            iVar4 = iVar4 + 1;
            ppOVar5 = ppOVar5 + 1;
        } while (iVar4 < *(int*)&alarm->field_0x578);
    }
    iVar4 = 0;
    if (0 < (int)alarm->apsensors[4]) {
        ppSVar6 = alarm->apsensors + 5;
        do {
            //pLVar1 = (LinkedListNode*) PloFindSwObject(*(SW**)&alarm->field_0x14, 0x104, (OID*)*ppSVar6, (Entity*)alarm);
            //if ((pLVar1 != (LinkedListNode*)0x0) && (iVar7 = FIsBasicDerivedFrom(pLVar1, 8), iVar7 != 0))
            {
                //AddStepguardAlarm((STEPGUARD*)pLVar1, alarm);
            }
            iVar4 = iVar4 + 1;
            ppSVar6 = ppSVar6 + 1;
        } while (iVar4 < (int)alarm->apsensors[4]);
    }
    //uVar3 = FGetChkmgrIchk((int)&g_chkmgr, *(uint*)&alarm->arsmg[6].field_0x2);
    if (uVar3 == 0) 
    {
        SetAlarmAlarms(alarm, ALARMS_Enabled);
    }
    else 
    {
        SetAlarmAlarms(alarm, ALARMS_Disabled);
    }
    return;
}

void SetAlarmAlarms(ALARM* alarm, ALARMS state)
{
    SENSOR* pSVar1;
    uint64_t uVar2;
    int iVar3;
    ALARMS current_state;

    current_state = alarm->state;
    if (current_state == state) 
    {
        return;
    }
    if (-1 < (int)current_state) 
    {
        if ((int)current_state < 2) 
        {
            alarm->state = state;
            goto LAB_00123914;
        }
        if (current_state != ALARMS_Triggered) 
        {
            alarm->state = state;
            goto LAB_00123914;
        }
        //StopSound((long)(int)alarm->apsensors[0xc], 0);
        //UnsetExcitement((long)(int)alarm->apsensors[0xd]);
        //TriggerRsmg(*(SW**)&alarm->field_0x14, (int)alarm->apsensors[0xf], (OID**)&alarm->coidStepguards, (Entity*)alarm, 0);
        if (state != ALARMS_Disabled) 
        {
            alarm->state = state;
            goto LAB_00123914;
        }
        //OnGameAlarmDisabled((int)&DAT_002623d8);
    }
    alarm->state = state;
LAB_00123914:
    *&alarm->field_0x554 = g_clock.t;
    if (state == ALARMS_Disabled) 
    {
        if (&alarm->field_0x55c != 0x0) 
        {
            //SeekSma(*(SMA**)&alarm->field_0x55c, 0x220);
        }
        //DisableAlarmSensors(alarm);
        //uVar2 = FGetChkmgrIchk((int)&g_chkmgr, *(uint*)&alarm->arsmg[6].field_0x2);
        if (uVar2 == 0) 
        {
            //HandleLoSpliceEvent((LO*)alarm, 3, 0, (void**)0x0);
            //iVar3 = *(int*)&alarm->arsmg[6].field_0x2;
        }
        else {
            //HandleLoSpliceEvent(alarm, 0x16, 0, (void**)0x0);
            //iVar3 = *(int*)&alarm->arsmg[6].field_0x2;
        }
        //SetChkmgrIchk(&g_chkmgr, iVar3);
    }
    else {
        if ((int)state < 2) 
        {
            if (state == ALARMS_Enabled) 
            {
                if (&alarm->field_0x55c != 0x0) 
                {
                    //SetSmaGoal(&alarm->field_0x55c, 0x21a);
                }
                //EnableAlarmSensors(alarm);
            }
        }
        else 
        {
            if (state == ALARMS_Triggered) 
            {
                if (&alarm->field_0x55c == 0x0) 
                {
                    pSVar1 = alarm->apsensors[0xe];
                }
                else 
                {
                    //SetSmaGoal(&alarm->field_0x55c, 0x21f);
                    pSVar1 = alarm->apsensors[0xe];
                }
                if (pSVar1 == 0x0) 
                {
                    //StartSound(SFXID_EnvAlarmSounding, (AMB**)(alarm->apsensors + 0xc), (ALO*)alarm, (VECTOR*)0x0, 8000.0, 5000.0, 1.0, 0.0, 0.0, (LM*)0x0, (LM*)0x0);
                }
                //pSVar1 = PexcSetExcitement(0x6b);
                alarm->apsensors[0xd] = pSVar1;
                //NotifyAlarmSensorsOnTrigger(alarm);
                //TriggerRsmg(&alarm->field_0x14, (int)alarm->apsensors[0xf], (OID**)&alarm->coidStepguards, (Entity*)alarm, 1);
                //HandleLoSpliceEvent((LO*)alarm, 2, 0, 0x0);
                //OnGameAlarmTriggered((int)&DAT_002623d8);
            }
        }
    }
    return;
}

uint32_t SetAlarmRsmg(ALARM* param_1, int param_2, OID param_3, OID param_4, OID param_5)
{
    uint32_t uVar1;

    //uVar1 = FAddRsmg((RSMG*)&param_1->coidStepguards, 8, (int*)(param_1->apsensors + 0xf), param_2, param_3, param_4, param_5);
    return uVar1;
}

void SetAlbrkAlarm(ALBRK* param_1, ALARM* param_2)
{
    *(ALARM**)(param_1 + 0x6c0) = param_2;
    return;
}

void TriggerAlarm(ALARM* alarm, ALTK atlk)
{
    ALARMS state;

    if (atlk == 1) 
    {
        state = ALARMS_Enabled;
    }
    else 
    {
        if ((int)atlk < 2) 
        {
            if (atlk != 0) 
            {
                return;
            }
            state = ALARMS_Triggered;
        }
        else 
        {
            if (atlk != 2) 
            {
                return;
            }
            state = ALARMS_Disabled;
        }
    }
    SetAlarmAlarms(alarm, state);
    return;
}

void UpdateAlarm(ALARM* param_1, Entity* param_2)
{
    //LinkedListNode* lst_head;
    int iVar1;
    OID** ppOVar2;
    int iVar3;

    //UpdateSo();
    if (*(int*)&param_2->field_0x550 == 2) 
    {
        if (*(float*)&param_2->field_0x560 == 0.0) 
        {
            iVar1 = *(int*)&param_2->field_0x564;
        }
        else 
        {
            if (*(float*)&param_2->field_0x560 < g_clock.t - *(float*)&param_2->field_0x554) 
            {
                SetAlarmAlarms((ALARM*)param_2, ALARMS_Enabled);
                return;
            }
            iVar1 = *(int*)&param_2->field_0x564;
        }
    }
    else 
    {
        iVar1 = *(int*)&param_2->field_0x564;
    }
    if (iVar1 < 1) 
    {
        iVar3 = *(int*)&param_2->field_0x550;
    }
    else 
    {
        if (*(int*)&param_2->field_0x61c == iVar1) 
        {
            SetAlarmAlarms((ALARM*)param_2, ALARMS_Disabled);
            return;
        }
        iVar3 = *(int*)&param_2->field_0x550;
    }
    //if (((iVar3 == 2) && (g_pjt->state == JTS_Celebrate)) && (iVar3 = 0, 0 < iVar1)) 
    {
        ppOVar2 = (OID**)&param_2->field_0x568;
        do 
        {
            //lst_head = (LinkedListNode*) PloFindSwObject(param_2->entity_list_pointer, 0x104, *ppOVar2, param_2);

            //if (lst_head == (LinkedListNode*)0x0) 
            {
                iVar1 = *(int*)&param_2->field_0x564;
            }
            //else 
            {
                //iVar1 = FIsBasicDerivedFrom(lst_head, 0x22);
                if (iVar1 == 0) 
                {
                    iVar1 = *(int*)&param_2->field_0x564;
                }
                else 
                {
                    //(*(code*)lst_head->next[0x26].next)(lst_head); //GOTTA COME BACK TO THIS
                    iVar1 = *(int*)&param_2->field_0x564;
                }
            }
            iVar3 = iVar3 + 1;
            ppOVar2 = ppOVar2 + 1;
        } while (iVar3 < iVar1);
    }
    return;
}