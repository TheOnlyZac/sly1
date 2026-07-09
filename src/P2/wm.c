#include <wm.h>
#include <game.h>
#include <wipe.h>

extern int D_00275BF0;

int FUN_001f0468(void)
{
    if (D_00275BF0 != 2)
        return STRUCT_OFFSET(g_pgsCur, 0x19DC, int);
    return 10;
}

INCLUDE_ASM("asm/nonmatchings/P2/wm", FUN_001f0490);

INCLUDE_ASM("asm/nonmatchings/P2/wm", FUN_001f0580);

INCLUDE_ASM("asm/nonmatchings/P2/wm", PostWmLoad__FP2WM);

INCLUDE_ASM("asm/nonmatchings/P2/wm", BindWm__FP2WM);

INCLUDE_ASM("asm/nonmatchings/P2/wm", RefreshWmMoveStats__FP2WM10WORLDLEVEL);

extern WORLDLEVEL D_00276250;
extern int D_00276654;

void ThrowWmDisplayState(WM *pwm, WORLDLEVEL worldlevel, int fReverse)
{
    D_00276250 = worldlevel;
    D_00276654 = fReverse;
}

INCLUDE_ASM("asm/nonmatchings/P2/wm", CatchWmDisplayState__FP2WM);

INCLUDE_ASM("asm/nonmatchings/P2/wm", UpdateWm__FP2WMf);

void RenderWmAll(WM *pwm, CM *pcm, RO *pro)
{
    RO ro;
    float sNearFog = g_pcm->fgfn.sNearFog;
    float duFogPlusClipBias = g_pcm->fgfn.duFogPlusClipBias;

    SetCmFov(g_pcm, 1.0f);
    DupAloRo((ALO *)pwm, pro, &ro);
    LoadMatrixFromPosRot((VECTOR *)((char *)pcm + 0x40), (MATRIX3 *)((char *)pcm + 0x80), &ro.mat);
    RenderAloAll((ALO *)pwm, pcm, &ro);
    SetCmFov(g_pcm, sNearFog);
    g_pcm->fgfn.duFogPlusClipBias = duFogPlusClipBias;
}

INCLUDE_ASM("asm/nonmatchings/P2/wm", HandleWmMessage__FP2WM5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/wm", SetWmWms__FP2WM3WMS);

void ShowWm(WM *pwm, WORLDLEVEL worldlevel, WMS wmsActive)
{
    switch (STRUCT_OFFSET(pwm, 0x2D0, WMS))
    {
    case WMS_Hidden:
    case WMS_Disappearing:
        STRUCT_OFFSET(pwm, 0x2DC, WORLDLEVEL) = worldlevel;
        STRUCT_OFFSET(pwm, 0x2E0, WMS) = wmsActive;
        SetWmWms(pwm, WMS_Appearing);
        break;

    case WMS_Manual:
        STRUCT_OFFSET(pwm, 0x2DC, WORLDLEVEL) = worldlevel;
        if (wmsActive == WMS_Warping)
            SetWmWms(pwm, WMS_Warping);
        break;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/wm", HideWm__FP2WM);

INCLUDE_ASM("asm/nonmatchings/P2/wm", MoveWm__FP2WM3WMD);

INCLUDE_ASM("asm/nonmatchings/P2/wm", GetWmWorldPosScreen__FP2WM10WORLDLEVELP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/wm", SetWmCursor__FP2WM10WORLDLEVEL);

INCLUDE_ASM("asm/nonmatchings/P2/wm", PostWmcLoad__FP3WMC);

INCLUDE_ASM("asm/nonmatchings/P2/wm", UpdateWmcActive__FP3WMCP3JOY);

INCLUDE_ASM("asm/nonmatchings/P2/wm", OnWmcActive__FP3WMCi);

INCLUDE_ASM("asm/nonmatchings/P2/wm", DrawWmFan__FffffiG4RGBAT5i);

INCLUDE_ASM("asm/nonmatchings/P2/wm", DrawWmc__FP3WMC);

INCLUDE_ASM("asm/nonmatchings/P2/wm", wm__static_initialization_and_destruction_0);

JUNK_WORD(0xE48C0000);
JUNK_WORD(0xE48C0008);

INCLUDE_ASM("asm/nonmatchings/P2/wm", _GLOBAL_$I$U_WmFadedLevels);
