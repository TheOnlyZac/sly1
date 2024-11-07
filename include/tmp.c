struct save_struct;
void DecrementSwHandsOff(SW *);
void FUN_0018c178(save_struct *, int);

extern BLOT BLOT_00272930;

void SetUiUis(UI *pui, UIS uis)
{
    UIS newUis;
    float uPause;
    UIS lastUis;

    newUis = uis;
    if ((uis == UIS_Pausing) && (newUis = pui->uisPlaying, newUis == UIS_Nil))
    {
        newUis = uis;
    }
    lastUis = pui->uis;
    if (lastUis == newUis)
    {
        return;
    }
    if (lastUis == UIS_Splash)
    {
    LAB_001e9778:
        pui->uis = newUis;
    }
    else
    {
        if (lastUis == UIS_Attract)
        {
            g_unkblot10.pvtnote->pfnShowBlot(&g_unkblot10);
            (*(BLOT_00272930.pvtblot)->pfnHideBlot)(0x272930);
            (**(code **)(BLOT_00272930.achzDraw[152] + 0x3c))(0x272b98);
            DecrementSwHandsOff(g_psw);
            goto LAB_001e9778;
        }
        pui->uis = newUis;
    }
    pui->tUis = g_clock.tReal;
    switch (newUis)
    {
    case UIS_Splash:
    if (g_save?.field6_0x18 == 0)
    {
        FUN_0018c178(0x264a40, 1);
    }
    SetWipeWipes((WIPE *)&g_pwipe, WIPES_Idle);
    uPause = 1.0;
    goto LAB_001e9870;
    case UIS_Attract:
        SetUiUPause(pui, 1.0);
        (*(BLOT_00272930.pvtblot)->pfnShowBlot)(0x272930);
        (**(code **)(BLOT_00272930.achzDraw[152] + 0x38))(0x272b98);
        IncrementSwHandsOff(g_psw);
        vibration_flip_on();
        break;
    case UIS_Playing:
        uPause = 1.0;
        goto LAB_001e9870;
    case UIS_Pausing:
        SetUiUPause(pui, 1.0);
        g_iexcHyst = 0xffffff9c;
        break;
    case UIS_Unpausing:
    case 7:
        uPause = 0.0;
    LAB_001e9870:
        SetUiUPause(pui, uPause);
        break;
    case UIS_Wiping:
        (*(g_lifectr.pvtblot)->pfnHideBlot)(0x26c6c8);
        (**(code **)(g_lifectr.achzDraw[158] + 0x3c))(0x26c948);
        (*(g_keyctr.pvtblot)->pfnHideBlot)(0x26cbc8);
        (**(code **)(g_keyctr.achzDraw[158] + 0x3c))(0x26ce48);
    }
    return;
}
