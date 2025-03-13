#include <screen.h>
#include <clock.h>
#include <font.h>

INCLUDE_ASM(const s32, "P2/screen", StartupScreen__Fv);

INCLUDE_ASM(const s32, "P2/screen", PostBlotsLoad__Fv);

INCLUDE_ASM(const s32, "P2/screen", UpdateBlots__Fv);

INCLUDE_ASM(const s32, "P2/screen", ForceHideBlots__Fv);

INCLUDE_ASM(const s32, "P2/screen", ResetBlots__Fv);

INCLUDE_ASM(const s32, "P2/screen", RenderBlots__Fv);

INCLUDE_ASM(const s32, "P2/screen", DrawBlots__Fv);

INCLUDE_ASM(const s32, "P2/screen", InitBlot__FP4BLOT5BLOTK);

void PostBlotLoad(BLOT *pblot)
{
    pblot->pfont = g_pfont;
    *(int*)&pblot->rgba = 0xff808080; // Union?
    pblot->achzDraw[0] = 0;
    pblot->rFontScale = 1.0f;
}

INCLUDE_ASM(const s32, "P2/screen", UpdateBlot__FP4BLOT);

INCLUDE_ASM(const s32, "P2/screen", SetBlotAchzDraw__FP4BLOTPc);

INCLUDE_ASM(const s32, "P2/screen", SetBlotRgba__FP4BLOTUi);

void SetBlotFontScale(float rFontScale, BLOT *pblot)
{
    pblot->rFontScale = rFontScale;
}

INCLUDE_ASM(const s32, "P2/screen", DrawBlot__FP4BLOT);

INCLUDE_ASM(const s32, "P2/screen", func_001AA890);

float DtAppearBlot(BLOT *pblot)
{
    return pblot->dtAppear;
}

float DtVisibleBlot(BLOT *pblot)
{
    return pblot->dtVisible;
}

float DtDisappearBlot(BLOT *pblot)
{
    return pblot->dtDisappear;
}

void SetBlotDtAppear(BLOT *pblot, float dtAppear)
{
    pblot->dtAppear = dtAppear;
}

void SetBlotDtVisible(BLOT *pblot, float dtVisible)
{
    pblot->dtVisible = dtVisible;
}

void SetBlotDtDisappear(BLOT *pblot, float dtDisappear)
{
    pblot->dtDisappear = dtDisappear;
}

INCLUDE_ASM(const s32, "P2/screen", OnBlotReset__FP4BLOT);

INCLUDE_ASM(const s32, "P2/screen", ShowBlot__FP4BLOT);

INCLUDE_ASM(const s32, "P2/screen", HideBlot__FP4BLOT);

INCLUDE_ASM(const s32, "P2/screen", SetBlotBlots__FP4BLOT5BLOTS);

INCLUDE_ASM(const s32, "P2/screen", FIncludeBlotForPeg__FP4BLOTT0);

INCLUDE_ASM(const s32, "P2/screen", ResizeBlot__FP4BLOTff);

INCLUDE_ASM(const s32, "P2/screen", RepositionBlot__FP4BLOT);

INCLUDE_ASM(const s32, "P2/screen", RepositionBlotDependents__FP4BLOT);

INCLUDE_ASM(const s32, "P2/screen", SetBlotClock__FP4BLOTPf);

INCLUDE_ASM(const s32, "P2/screen", PostCtrLoad__FP3CTR);

INCLUDE_ASM(const s32, "P2/screen", UpdateCtr__FP3CTR);

INCLUDE_ASM(const s32, "P2/screen", DrawCtr__FP3CTR);

INCLUDE_ASM(const s32, "P2/screen", RebuildCtrAchzDraw__FP3CTR);

INCLUDE_ASM(const s32, "P2/screen", DtVisibleCtr__FP3CTR);

INCLUDE_ASM(const s32, "P2/screen", FUN_001ab600);

INCLUDE_ASM(const s32, "P2/screen", UpdateTimer__FP5TIMER);

INCLUDE_ASM(const s32, "P2/screen", DrawTimer__FP5TIMER);

void SetTimer(TIMER *ptimer, float dt) {
    float threshold = D_0024CD4C;
    ptimer->pfntnThreshold = (undefined1 *)0;
    ptimer->fThreshold = 0;
    ptimer->dtExpire = 0.0;
    ptimer->pfntnExpire = (undefined1 *)0;
    ptimer->fStopped = 0;
    *(int*)&ptimer->rgba = 0xff808080; // Union?
    ptimer->svt = -1.0;
    ptimer->nSecondsLast = -1;
    ptimer->nTenthsLast = -1;
    ptimer->dtThreshold = threshold;
    ptimer->dt = dt;
    SetTimerTimers(ptimer, TIMERS_Paused);
    RebuildTimerAchzDraw(ptimer, 0.0);
    ptimer->pvttimer->pfnShowBlot(ptimer);
}

void SetTimerSpeed(TIMER *ptimer, float svt) {
    ptimer->svt = svt;
}

/**
 * @note Matches but there's issues with the signature.
 */
INCLUDE_ASM(const s32, "P2/screen", SetTimerExpire__FP5TIMERfPFP5TIMER9TIMERNOTK_v);
// void SetTimerExpire(TIMER *ptimer, float dt, void *pfntn) {
//     ptimer->dt = dt;
//     ptimer->pfntnThreshold = pfntn;
// }

void StartTimer(TIMER *ptimer) {
    SetTimerTimers(ptimer, TIMERS_Running);
}

void StopTimer(TIMER *ptimer) {
    ptimer->fStopped = 1;
    SetTimerTimers(ptimer, TIMERS_Expired);
}

INCLUDE_ASM(const s32, "P2/screen", RebuildTimerAchzDraw__FP5TIMERf);

void SetTimerTimers(TIMER *ptimer, TIMERS timers) {
    if (ptimer->timers != timers) {
        ptimer->timers = timers;
        ptimer->tTimers = g_clock.t;
    }
}

float DtVisibleTrunkctr(TRUNKCTR *ptrunkctr) {
    return 0.0;
}

float DtVisibleCrusherctr(CRUSHERCTR *pcrusherctr) {
    return 0.0;
}

INCLUDE_ASM(const s32, "P2/screen", func_001ABE60);

INCLUDE_ASM(const s32, "P2/screen", FUN_001abe70);

INCLUDE_ASM(const s32, "P2/screen", FUN_001ac060);

INCLUDE_ASM(const s32, "P2/screen", FUN_001ac0e8);

INCLUDE_ASM(const s32, "P2/screen", PostNoteLoad__FP4NOTE);

INCLUDE_ASM(const s32, "P2/screen", SetNoteAchzDraw__FP4NOTEPc);

INCLUDE_ASM(const s32, "P2/screen", DrawNote__FP4NOTE);

INCLUDE_ASM(const s32, "P2/screen", FUN_001ac888);

INCLUDE_ASM(const s32, "P2/screen", FUN_001ac910);

INCLUDE_ASM(const s32, "P2/screen", FUN_001ac990);

INCLUDE_ASM(const s32, "P2/screen", FUN_001ac9e0);

INCLUDE_ASM(const s32, "P2/screen", FUN_001aca30);

INCLUDE_ASM(const s32, "P2/screen", FUN_001aca68);

INCLUDE_ASM(const s32, "P2/screen", DrawTitle__FP5TITLE);

INCLUDE_ASM(const s32, "P2/screen", PostTotalsLoad__FP6TOTALS);

INCLUDE_ASM(const s32, "P2/screen", FUN_001ace38);

INCLUDE_ASM(const s32, "P2/screen", FUN_001acee0);

INCLUDE_ASM(const s32, "P2/screen", render_level_info_from_id);

INCLUDE_ASM(const s32, "P2/screen", render_level_info);

INCLUDE_ASM(const s32, "P2/screen", render_hideout_world_info);

INCLUDE_ASM(const s32, "P2/screen", SetTotalsBlots__FP6TOTALS5BLOTS);

INCLUDE_ASM(const s32, "P2/screen", ShowTotalsQMARK);

INCLUDE_ASM(const s32, "P2/screen", HideTotalsQMARK);

INCLUDE_ASM(const s32, "P2/screen", DrawTotals__FP6TOTALS);

INCLUDE_ASM(const s32, "P2/screen", FUN_001ad6a8);

INCLUDE_ASM(const s32, "P2/screen", FUN_001ad718);

INCLUDE_ASM(const s32, "P2/screen", FUN_001ad7b0);

INCLUDE_ASM(const s32, "P2/screen", FUN_001ad940);

INCLUDE_ASM(const s32, "P2/screen", FUN_001ad970);

INCLUDE_ASM(const s32, "P2/screen", DrawLetterbox__FP9LETTERBOX);

INCLUDE_ASM(const s32, "P2/screen", FUN_001adc60);

INCLUDE_ASM(const s32, "P2/screen", DrawLogo__FP4LOGO);

INCLUDE_ASM(const s32, "P2/screen", FUN_001adf28);

INCLUDE_ASM(const s32, "P2/screen", FUN_001adff0);

INCLUDE_ASM(const s32, "P2/screen", FUN_001ae130);

INCLUDE_ASM(const s32, "P2/screen", UpdateAttract__FP7ATTRACT);

INCLUDE_ASM(const s32, "P2/screen", func_001AE220);

INCLUDE_ASM(const s32, "P2/screen", DrawLineScreen__FUiUiUiUiUiUiG4RGBAi);
