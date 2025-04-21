#include <ui.h>
#include <screen.h>

INCLUDE_ASM(const s32, "P2/ui", StartupUi__Fv);

INCLUDE_ASM(const s32, "P2/ui", InitUi__FP2UI);

INCLUDE_ASM(const s32, "P2/ui", PostUiLoad__FP2UI);

INCLUDE_ASM(const s32, "P2/ui", UpdateUi__FP2UI);

INCLUDE_ASM(const s32, "P2/ui", PushUiActiveBlot__FP2UIP4BLOT);

INCLUDE_ASM(const s32, "P2/ui", PopUiActiveBlot__FP2UI);

void DrawUi() {
    DrawBlots();
}

void RenderUi() {
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

INCLUDE_ASM(const s32, "P2/ui", SetUiUis__FP2UI3UIS);

INCLUDE_ASM(const s32, "P2/ui", SetUiUPause__FP2UIf);

INCLUDE_ASM(const s32, "P2/ui", FUN_001e9970__Fv);

INCLUDE_ASM(const s32, "P2/ui", FUN_001e9a10__Fv);

INCLUDE_ASM(const s32, "P2/ui", FUN_001e9a68__Fv);

INCLUDE_ASM(const s32, "P2/ui", FUN_001e9ad8__Fv);

INCLUDE_ASM(const s32, "P2/ui", check_anticrack_collectibles_Fv);
