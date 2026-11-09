#include <screen.h>
#include <clock.h>
#include <font.h>

INCLUDE_ASM("asm/nonmatchings/P2/screen", StartupScreen__Fv);

void PostBlotsLoad()
{
    for (int i = 0x24; i >= 0; i--)
    {
        BLOT *pblot = D_002486B0[i];
        pblot->pvtblot->pfnPostBlotLoad(pblot);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", UpdateBlots__Fv);

void ForceHideBlots()
{
    for (int i = 0x24; i >= 0; i--)
    {
        BLOT *pblot = D_002486B0[i];
        pblot->pvtblot->pfnSetBlotBlots(pblot, 0);
    }
}

void ResetBlots()
{
    int i = 0x24;
    BLOT **ppblot = D_002486B0;
    do
    {
        BLOT *pblot = *ppblot;
        ppblot++;
        i--;
        pblot->pvtblot->pfnOnBlotReset(pblot);
    } while (i >= 0);
}

void RenderBlots()
{
    int i = 0x24;
    BLOT **ppblot = D_002486B0;
    do
    {
        BLOT *pblot = *ppblot;
        i--;
        ppblot++;
        if (pblot->blots != BLOTS_Hidden && pblot->pvtblot->pfnRenderBlot)
            pblot->pvtblot->pfnRenderBlot(pblot);
    } while (i >= 0);
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", DrawBlots__Fv);

INCLUDE_ASM("asm/nonmatchings/P2/screen", InitBlot__FP4BLOT5BLOTK);

void PostBlotLoad(BLOT *pblot)
{
    pblot->pfont = g_pfont;
    *(int*)&pblot->rgba = 0xff808080; // Union?
    pblot->achzDraw[0] = 0;
    pblot->rFontScale = 1.0f;
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", UpdateBlot__FP4BLOT);

INCLUDE_ASM("asm/nonmatchings/P2/screen", SetBlotAchzDraw__FP4BLOTPc);

INCLUDE_ASM("asm/nonmatchings/P2/screen", SetBlotRgba__FP4BLOTUi);

void SetBlotFontScale(BLOT *pblot, float rFontScale)
{
    pblot->rFontScale = rFontScale;
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", DrawBlot__FP4BLOT);

JUNK_ADDIU(10);

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

void OnBlotReset(BLOT *pblot)
{
    pblot->pvtblot->pfnSetBlotBlots(pblot, 0);
}

void ShowBlot(BLOT *pblot)
{
    switch (pblot->blots)
    {
    case BLOTS_Hidden:
    case BLOTS_Disappearing:
        pblot->pvtblot->pfnSetBlotBlots(pblot, BLOTS_Appearing);
        break;
    case BLOTS_Visible:
        pblot->tBlots = *pblot->ptNow;
        break;
    }
}

void HideBlot(BLOT *pblot)
{
    if (pblot->blots < BLOTS_Disappearing)
    {
        if (pblot->blots > BLOTS_Hidden)
            pblot->pvtblot->pfnSetBlotBlots(pblot, BLOTS_Disappearing);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", SetBlotBlots__FP4BLOT5BLOTS);

int FIncludeBlotForPeg(BLOT *pblot, BLOT *pblotOther)
{
    int f = 0;
    if (((uint)(pblot->blots - 1) < 2 && (uint)(pblotOther->blots - 1) < 2) ||
        (pblot->blots == BLOTS_Disappearing && pblotOther->blots == pblot->blots) ||
        (pblotOther->blots == BLOTS_Disappearing && pblot->blots == BLOTS_Visible))
    {
        f = 1;
    }
    return f;
}

void ResizeBlot(BLOT *pblot, float dx, float dy)
{
    if (0.0f <= dx)
        pblot->width = dx;
    if (0.0f <= dy)
        pblot->height = dy;
    RepositionBlot(pblot);
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", RepositionBlot__FP4BLOT);

INCLUDE_ASM("asm/nonmatchings/P2/screen", RepositionBlotDependents__FP4BLOT);

void SetBlotClock(BLOT *pblot, float *pt)
{
    if (pblot->ptNow != pt)
    {
        if (!pt)
            pt = &g_clock.tReal;
        pblot->tBlots = *pt;
    }
    pblot->ptNow = pt;
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", PostCtrLoad__FP3CTR);

INCLUDE_ASM("asm/nonmatchings/P2/screen", UpdateCtr__FP3CTR);

INCLUDE_ASM("asm/nonmatchings/P2/screen", DrawCtr__FP3CTR);

INCLUDE_ASM("asm/nonmatchings/P2/screen", RebuildCtrAchzDraw__FP3CTR);

float DtVisibleCtr(CTR *pctr)
{
    float dt = 0.0f;
    if (g_clock.fEnabled)
        dt = 2.5f;
    return dt;
}

void FUN_001ab600(BLOT *pblot)
{
    PostBlotLoad(pblot);
    pblot->pfont = FUN_0015c1c0(2);
    TIMER *ptimer = (TIMER *)pblot;
    ptimer->nSecondsLast = -1;
    ptimer->nTenthsLast = -1;
    ptimer->dtThreshold = D_0024CD48;
    ptimer->fStopped = 1;
    SetTimerTimers(ptimer, TIMERS_Expired);
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", UpdateTimer__FP5TIMER);

INCLUDE_ASM("asm/nonmatchings/P2/screen", DrawTimer__FP5TIMER);

void SetTimer(TIMER *ptimer, float dt)
{
    float threshold = D_0024CD4C;
    ptimer->pfntnThreshold = NULL;
    ptimer->fThreshold = 0;
    ptimer->dtExpire = 0.0;
    ptimer->pfntnExpire = NULL;
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

void SetTimerSpeed(TIMER *ptimer, float svt)
{
    ptimer->svt = svt;
}

/**
 * @brief Sets the time until the timer expires, and callback function.
 */
void SetTimerExpire(TIMER *ptimer, float dt, void *pfntn)
{
    STRUCT_OFFSET(ptimer, 0x288, float) = dt; // ptimer->dt = dt;
    STRUCT_OFFSET(ptimer, 0x28c, void *) = pfntn; // ptimer->pfntnThreshold = pfntn;
}

void StartTimer(TIMER *ptimer)
{
    SetTimerTimers(ptimer, TIMERS_Running);
}

void StopTimer(TIMER *ptimer)
{
    ptimer->fStopped = 1;
    SetTimerTimers(ptimer, TIMERS_Expired);
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", RebuildTimerAchzDraw__FP5TIMERf);

void SetTimerTimers(TIMER *ptimer, TIMERS timers)
{
    if (ptimer->timers != timers)
    {
        ptimer->timers = timers;
        ptimer->tTimers = g_clock.t;
    }
}

float DtVisibleTrunkctr(TRUNKCTR *ptrunkctr)
{
    return 0.0f;
}

float DtVisibleCrusherctr(CRUSHERCTR *pcrusherctr)
{
    return 0.0f;
}

/**
 * @todo Rename function.
 */
float FUN_001ABE60()
{
    return 0.0f;
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001abe70);

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001ac060);

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001ac0e8);

INCLUDE_ASM("asm/nonmatchings/P2/screen", PostNoteLoad__FP4NOTE);

INCLUDE_ASM("asm/nonmatchings/P2/screen", SetNoteAchzDraw__FP4NOTEPc);

INCLUDE_ASM("asm/nonmatchings/P2/screen", DrawNote__FP4NOTE);

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001ac888);

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001ac910);

void FUN_001ac990(BLOT *pblot, BLOTS blots)
{
    if (STRUCT_OFFSET(pblot, 0x260, int) && !blots)
    {
        STRUCT_OFFSET(pblot, 0x260, int) = 0;
        SetBlotAchzDraw(pblot, STRUCT_OFFSET(pblot, 0x264, char *));
        blots = BLOTS_Appearing;
    }
    SetBlotBlots(pblot, blots);
}

int FUN_001ac9e0(BLOT *pblot, BLOT *pblotOther)
{
    int f = 0;
    if (FIncludeBlotForPeg(pblot, pblotOther) || STRUCT_OFFSET(pblot, 0x260, int))
        f = 1;
    return f;
}

void FUN_001aca30(BLOT *pblot)
{
    if (pblot->blots != BLOTS_Disappearing || !STRUCT_OFFSET(pblot, 0x260, int))
        ShowBlot(pblot);
}

void FUN_001aca68(BLOT *pblot)
{
    if (pblot->blots == BLOTS_Disappearing && STRUCT_OFFSET(pblot, 0x260, int))
        STRUCT_OFFSET(pblot, 0x260, int) = 0;
    else
        HideBlot(pblot);
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", DrawTitle__FP5TITLE);

INCLUDE_ASM("asm/nonmatchings/P2/screen", PostTotalsLoad__FP6TOTALS);

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001ace38);

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001acee0);

void render_level_info_from_id(BLOT *pblot, int level_id)
{
    if (level_id != -1)
        render_level_info(pblot, level_id >> 8, level_id & 0xff);
    else
        pblot->pvtblot->pfnSetBlotAchzDraw(pblot, D_0024CE00);
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", render_level_info);

INCLUDE_ASM("asm/nonmatchings/P2/screen", render_hideout_world_info);

void SetTotalsBlots(TOTALS *ptotals, BLOTS blots)
{
    if (ptotals->fReshow)
    {
        if (blots == BLOTS_Hidden)
        {
            ptotals->fReshow = 0;
            SetBlotAchzDraw(ptotals, &STRUCT_OFFSET(ptotals, 0x264, char));
            blots = BLOTS_Appearing;
        }
    }
    if (blots == BLOTS_Hidden)
        STRUCT_OFFSET(ptotals, 0x464, int) = 0;
    SetBlotBlots(ptotals, blots);
}

void ShowTotals(TOTALS *ptotals)
{
    if (ptotals->blots != BLOTS_Disappearing || !ptotals->fReshow)
        ShowBlot(ptotals);
}

void HideTotals(TOTALS *ptotals)
{
    if (ptotals->blots == BLOTS_Disappearing && ptotals->fReshow)
        ptotals->fReshow = 0;
    else
        HideBlot(ptotals);
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", DrawTotals__FP6TOTALS);

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001ad6a8);

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001ad718);

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001ad7b0);

void FUN_001ad940(BLOT *pblot)
{
    PostBlotLoad(pblot);
    pblot->dtDisappear = 0.5f;
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001ad970);

INCLUDE_ASM("asm/nonmatchings/P2/screen", DrawLetterbox__FP9LETTERBOX);

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001adc60);

INCLUDE_ASM("asm/nonmatchings/P2/screen", DrawLogo__FP4LOGO);

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001adf28);

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001adff0);

void FUN_001ae130(BLOT *pblot, BLOTS blots)
{
    if (STRUCT_OFFSET(pblot, 0x268, int) && !blots)
    {
        STRUCT_OFFSET(pblot, 0x268, int) = 0;
        FUN_001adff0(pblot);
        blots = BLOTS_Appearing;
    }
    SetBlotBlots(pblot, blots);
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", UpdateAttract__FP7ATTRACT);

INCLUDE_ASM("asm/nonmatchings/P2/screen", DrawAttract__FP7ATTRACT);

INCLUDE_ASM("asm/nonmatchings/P2/screen", DrawLineScreen__FUiUiUiUiUiUiG4RGBAi);

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001ae510);

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001ae5e0);

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001ae758);

void FUN_001ae7f8(BLOT *pblot, BLOTS blots)
{
    if (!blots)
        STRUCT_OFFSET(pblot, 0x260, int) = 0;
    SetBlotBlots(pblot, blots);
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001ae820);

char FUN_001aea08()
{
    return D_002744B0[(int)(g_clock.tReal * 5.0f) % strlen(D_002744B0)];
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001aea70);

JUNK_WORD(0xE48C0000);
JUNK_WORD(0xE48C0008);

void FUN_001aec90()
{
    FUN_001aea70(1, 0xFFFF);
}
