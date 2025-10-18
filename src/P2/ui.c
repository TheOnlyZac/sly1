#include <ui.h>
#include <clock.h>
#include <sound.h>
#include <screen.h>

void StartupUi()
{
    InitUi(&g_ui);
}

void InitUi(UI *pui)
{
    pui->unk6 = -1;
    pui->tUis = -1;
    SetUiUis(pui, UIS_Pausing);
    pui->cpblotActive = 0;
    pui->unk5 = 1;
}

void PostUiLoad(UI *pui)
{
    SetUiUis(pui, UIS_Pausing);
}

INCLUDE_ASM("asm/nonmatchings/P2/ui", UpdateUi__FP2UI);

INCLUDE_ASM("asm/nonmatchings/P2/ui", PushUiActiveBlot__FP2UIP4BLOT);

INCLUDE_ASM("asm/nonmatchings/P2/ui", PopUiActiveBlot__FP2UI);

void DrawUi()
{
    DrawBlots();
}

void RenderUi()
{
    RenderBlots();
}

void ResetUi(UI *pui)
{
    while (pui->unk5 >= 2)
    {
        PopUiActiveBlot(pui);
    }

    pui->unk5 = 1;
    pui->cpblotActive = 0;
    pui->unk6 = -1;

    SetRumbleRums(g_joy.prumble, RUMS_Stop);
    ResetBlots();
}

INCLUDE_ASM("asm/nonmatchings/P2/ui", SetUiUis__FP2UI3UIS);

void SetUiUPause(UI *pui, float uPause)
{
    if (g_clock.t > 0.0f)
    {
        float vol = (1.0f - uPause) * 0.6f + uPause;
        SetMvgkRvol(4, MVGK_Music, vol);
        SetMvgkRvol(4, MVGK_Effects, vol);
    }

    SetClockRate(uPause);
}

INCLUDE_ASM("asm/nonmatchings/P2/ui", FUN_001e9970__Fv);

INCLUDE_ASM("asm/nonmatchings/P2/ui", FUN_001e9a10__Fv);

INCLUDE_ASM("asm/nonmatchings/P2/ui", FUN_001e9a68__Fv);

INCLUDE_ASM("asm/nonmatchings/P2/ui", FUN_001e9ad8__Fv);

INCLUDE_ASM("asm/nonmatchings/P2/ui", check_anticrack_collectibles_Fv);
