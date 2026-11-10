#include <screen.h>
#include <clock.h>
#include <font.h>
#include <jt.h>
#include <ui.h>
#include <text.h>

INCLUDE_ASM("asm/nonmatchings/P2/screen", StartupScreen__Fv);

void PostBlotsLoad()
{
    for (int i = 0x24; i >= 0; i--)
    {
        BLOT *pblot = D_002486B0[i];
        pblot->pvtblot->pfnPostBlotLoad(pblot);
    }
}

void UpdateBlots()
{
    for (int i = 0x24; i >= 0; i--)
    {
        BLOT *pblot = D_002486B0[i];
        pblot->pvtblot->pfnUpdateBlot(pblot);
    }
    UpdateWipe(&g_wipe, (g_grfjoyt & 4) ? &g_joy : &g_joyZero);
}

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

void DrawBlots()
{
    BLOT **ppblot = D_002486B0;
    for (int i = 0; i < 0x25; i++)
    {
        BLOT *pblot = ppblot[i];
        if (pblot->blots != BLOTS_Hidden)
            pblot->pvtblot->pfnDrawBlot(pblot);
    }
    DrawWipe(&g_wipe);
    FUN_001ae820(&D_00273EB0);
}

void InitBlot(BLOT *pblot, BLOTK blotk)
{
    pblot->bloti = &D_0026C3E0[blotk];
    pblot->dtDisappear = 0.25f;
    pblot->dtAppear = 0.25f;
    pblot->ptNow = &g_clock.tReal;
    pblot->blotk = blotk;
    ResizeBlot(pblot, pblot->width, pblot->height);
    pblot->x = pblot->dx;
    pblot->y = pblot->dy;
}

void PostBlotLoad(BLOT *pblot)
{
    pblot->pfont = g_pfont;
    *(int*)&pblot->rgba = 0xff808080; // Union?
    pblot->achzDraw[0] = 0;
    pblot->rFontScale = 1.0f;
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", UpdateBlot__FP4BLOT);

void SetBlotAchzDraw(BLOT *pblot, char *pchz)
{
    char *achz;
    if (pchz && strlen(pchz))
    {
        strcpy(pblot->achzDraw, pchz);
        achz = pblot->achzDraw;
    }
    else
    {
        pblot->achzDraw[0] = 0;
        achz = pblot->achzDraw;
    }
    pblot->pfont->PushScaling(pblot->rFontScale, pblot->rFontScale);
    CRichText richtext(achz, pblot->pfont);
    float dx, dy;
    richtext.GetExtents(&dx, &dy, 0.0f);
    ResizeBlot(pblot, dx, dy);
    pblot->pfont->PopScaling();
}

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

void RepositionBlotDependents(BLOT *pblot)
{
    BLOTI *pbloti = D_0026C3E0;
    for (int i = 0; i < 0x25; i++)
    {
        BLOTK blotk = pbloti->blotkPeg;
        pbloti++;
        if (blotk != -1 && D_002486B0[blotk] == pblot)
            RepositionBlot(D_002486B0[i]);
    }
}

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

void UpdateTimer(TIMER *ptimer)
{
    UpdateBlot(ptimer);
    if (ptimer->blots == BLOTS_Hidden)
        return;
    if (ptimer->timers == TIMERS_Expired)
    {
        int f = (g_clock.t - ptimer->tTimers >= 1.0f) ? 1 : 0;
        if (ptimer->blots == BLOTS_Appearing || ptimer->blots == BLOTS_Visible)
        {
            if (ptimer->fStopped || f)
                ptimer->pvttimer->pfnHideBlot(ptimer);
        }
    }
    else
    {
        RebuildTimerAchzDraw(ptimer, g_clock.dt);
    }
}

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

void FUN_001ac060(BLOT *pblot)
{
    int n = STRUCT_OFFSET(pblot, 0x270, int) - 1;
    STRUCT_OFFSET(pblot, 0x270, int) = n;
    if (n <= 0)
    {
        int m = STRUCT_OFFSET(pblot, 0x26c, int) - 1;
        STRUCT_OFFSET(pblot, 0x26c, int) = m;
        if (m <= 0)
        {
            STRUCT_OFFSET(pblot, 0x270, int) = 0;
            STRUCT_OFFSET(pblot, 0x26c, int) = 0;
        }
        else
        {
            STRUCT_OFFSET(pblot, 0x270, int) = STRUCT_OFFSET(pblot, 0x264, int);
        }
    }
    int k = STRUCT_OFFSET(pblot, 0x26c, int) - 1;
    if (k < 0)
        k = 0;
    STRUCT_OFFSET(pblot, 0x278, float) = (float)(k * STRUCT_OFFSET(pblot, 0x264, int) + STRUCT_OFFSET(pblot, 0x270, int)) / (float)STRUCT_OFFSET(pblot, 0x268, int);
    STRUCT_OFFSET(pblot, 0x27c, float) = g_clock.t;
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001ac0e8);

void PostNoteLoad(NOTE *pnote)
{
    PostBlotLoad(pnote);
    pnote->pfont = pnote->pfont->PfontClone(1.25f, 1.25f);
    if (FUN_0015c188(2))
    {
        pnote->pte = &D_002743D0;
        STRUCT_OFFSET(pnote->pte, 0, CFont *) = FUN_0015c1c0(2);
    }
}

/// @todo ~60% matched (register allocation of pnote/pchz is swapped, as in SetBlotAchzDraw).
INCLUDE_ASM("asm/nonmatchings/P2/screen", SetNoteAchzDraw__FP4NOTEPc);
#ifdef SKIP_ASM
void SetNoteAchzDraw(NOTE *pnote, char *pchz)
{
    char *achz = pnote->achzDraw;
    if (pchz && strlen(pchz))
    {
        strcpy(achz, pchz);
        pchz = achz;
    }
    else
    {
        achz[0] = 0;
        pchz = achz;
    }
    float zero = 0.0f;
    pnote->pfont->PushScaling(pnote->rFontScale, pnote->rFontScale);
    CRichText richtext(pchz, pnote->pfont);
    float dx, dy;
    richtext.GetExtents(&dx, &dy, zero);
    float h = zero;
    if (pnote->achzDraw[0])
        h = dy;
    ResizeBlot(pnote, dx, h);
    pnote->pfont->PopScaling();
}
#endif // SKIP_ASM

INCLUDE_ASM("asm/nonmatchings/P2/screen", DrawNote__FP4NOTE);

void FUN_001ac888(BLOT *pblot)
{
    PostBlotLoad(pblot);
    pblot->pfont = pblot->pfont->PfontClone(0.9f, 0.9f);
    *(int *)&pblot->rgba = 0xDF7F7F7F;
    if (FUN_0015c188(2))
    {
        pblot->pte = &D_002743F0;
        STRUCT_OFFSET(pblot->pte, 0, CFont *) = FUN_0015c1c0(2);
    }
}

void FUN_001ac910(TITLE *ptitle, char *pchz)
{
    if (ptitle->blots == BLOTS_Hidden)
    {
        SetBlotAchzDraw(ptitle, pchz);
        return;
    }
    if (ptitle->blots >= 0)
    {
        if (ptitle->blots < 4)
        {
            if (func_001F6738(ptitle->achzDraw, pchz))
            {
                ptitle->pchzReshow = pchz;
                ptitle->fReshow = 1;
                ptitle->pvtblot->pfnSetBlotBlots(ptitle, 3);
            }
        }
    }
}

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

void PostTotalsLoad(TOTALS *ptotals)
{
    PostBlotLoad(ptotals);
    ptotals->pfont = FUN_0015c1c0(0)->PfontClone(1.0f, 1.0f);
    ptotals->rFontScale = 0.8f;
    ptotals->dtDisappear = 0.5f;
    if (FUN_0015c188(2))
    {
        ptotals->pte = &D_00274410;
        STRUCT_OFFSET(ptotals->pte, 0, CFont *) = FUN_0015c1c0(2);
    }
}

void FUN_001ace38(BLOT *pblot, char *pchz)
{
    if (pblot->blots == BLOTS_Hidden)
    {
        SetBlotAchzDraw(pblot, pchz);
        return;
    }
    if (pblot->blots >= 0)
    {
        if (pblot->blots < 4)
        {
            if (!STRUCT_OFFSET(pblot, 0x260, int))
            {
                if (!func_001F6738(pblot->achzDraw, pchz))
                    return;
            }
            STRUCT_OFFSET(pblot, 0x260, int) = 1;
            if (pchz)
                strcpy(&STRUCT_OFFSET(pblot, 0x264, char), pchz);
            else
                STRUCT_OFFSET(pblot, 0x264, char) = 0;
            pblot->pvtblot->pfnSetBlotBlots(pblot, 3);
        }
    }
}

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

void FUN_001ad6a8(BLOT *pblot)
{
    PostBlotLoad(pblot);
    pblot->pfont = FUN_0015c1c0(2)->PfontClone(1.0f, 1.0f);
    pblot->pvtblot->pfnSetBlotAchzDraw(pblot, D_0024CEE0);
    STRUCT_OFFSET(pblot, 0x260, int) = 0;
}

void FUN_001ad718(BLOT *pblot)
{
    UpdateBlot(pblot);
    if (STRUCT_OFFSET(pblot, 0x260, int) && (!g_pjt || STRUCT_OFFSET(g_pjt, 0x2220, int) != 6) &&
        g_ui.tUis == 3 && STRUCT_OFFSET(&g_ui, 0x2c, int) < 2)
    {
        pblot->pvtblot->pfnShowBlot(pblot);
        return;
    }
    pblot->pvtblot->pfnHideBlot(pblot);
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001ad7b0);

void FUN_001ad940(BLOT *pblot)
{
    PostBlotLoad(pblot);
    pblot->dtDisappear = 0.5f;
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001ad970);

INCLUDE_ASM("asm/nonmatchings/P2/screen", DrawLetterbox__FP9LETTERBOX);

void FUN_001adc60(LOGO *plogo)
{
    PostBlotLoad(plogo);
    plogo->pfont = plogo->pfont->PfontClone(D_00274448, D_0027444C);
    if (FUN_0015c1c0(2))
    {
        plogo->pte = &D_00274450;
        STRUCT_OFFSET(plogo->pte, 0, CFont *) = FUN_0015c1c0(2);
    }
    plogo->pshd = PshdFindShader((OID)0x493);
    if (plogo->pshd)
        ResizeBlot(plogo, 366.75f, 165.75f);
    else
        plogo->pvtblot->pfnSetBlotAchzDraw(plogo, D_0024CEF0);
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", DrawLogo__FP4LOGO);

/// @todo ~85% matched (statement scheduling differs around the fReshow store).
INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001adf28);
#ifdef SKIP_ASM
void FUN_001adf28(ATTRACT *pattract)
{
    PostBlotLoad(pattract);
    pattract->pfont = pattract->pfont->PfontClone(D_0027446C, D_00274470);
    if (FUN_0015c1c0(2))
    {
        pattract->pte = &D_00274488;
        STRUCT_OFFSET(pattract->pte, 0, CFont *) = FUN_0015c1c0(2);
    }
    int fJoy = (g_joy.joys == 3);
    pattract->fReshow = 0;
    pattract->fJoyValid = fJoy;
    int f = 0;
    if (D_00269988)
    {
        if (STRUCT_OFFSET(D_00269988, 0xC, float) != 0.0f)
            f = 1;
    }
    pattract->fReshow = f;
    FUN_001adff0(pattract);
}
#endif // SKIP_ASM

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

void UpdateAttract(ATTRACT *pattract)
{
    if (D_00275BF0 == 1)
    {
        int fJoy = (g_joy.joys == 3);
        int f = 0;
        if (D_00269988)
        {
            if (STRUCT_OFFSET(D_00269988, 0xC, float) != 0.0f)
                f = 1;
        }
        if (!fJoy != !pattract->fJoyValid || !f != !pattract->fReshow)
        {
            pattract->fJoyValid = fJoy;
            pattract->fReshow = f;
            FUN_001adff0(pattract);
        }
    }
    UpdateBlot(pattract);
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", DrawAttract__FP7ATTRACT);

INCLUDE_ASM("asm/nonmatchings/P2/screen", DrawLineScreen__FUiUiUiUiUiUiG4RGBAi);

void FUN_001ae510(BLOT *pblot)
{
    char *achz;
    PostBlotLoad(pblot);
    pblot->pfont = FUN_0015c1c0(2);
    if (pblot == (BLOT *)&D_00273C50)
    {
        char *a2 = pblot->achzDraw;
        sprintf(a2, D_0024CF98, 0x4C);
        achz = a2;
    }
    else
    {
        achz = pblot->achzDraw;
        if (pblot == (BLOT *)&D_002739F0)
            sprintf(achz, D_0024CF98, 0x4B);
    }
    pblot->pfont->PushScaling(D_002744A8, D_002744A8);
    pblot->width = pblot->pfont->DxFromPchz(achz);
    pblot->height = (float)STRUCT_OFFSET(pblot->pfont, 8, int) * STRUCT_OFFSET(pblot->pfont, 0x48, float);
    pblot->pfont->PopScaling();
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001ae5e0);

void FUN_001ae758(BLOT *pblot)
{
    char achz[2];
    PostBlotLoad(pblot);
    SetBlotDtAppear(pblot, 0.25f);
    SetBlotDtDisappear(pblot, 0.25f);
    SetBlotDtVisible(pblot, 0.0f);
    pblot->pfont = FUN_0015c1c0(1);
    SetBlotFontScale(pblot, D_002744AC);
    achz[0] = FUN_001aea08();
    achz[1] = 0;
    pblot->pvtblot->pfnSetBlotAchzDraw(pblot, achz);
    pblot->achzDraw[0] = 0;
}

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
