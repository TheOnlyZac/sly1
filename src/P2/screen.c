#include <screen.h>
#include <clock.h>
#include <font.h>
#include <vtables.h>
#include <frm.h>
#include <gifs.h>
#include <shd.h>
#include <wipe.h>

INCLUDE_ASM("asm/nonmatchings/P2/screen", StartupScreen__Fv);

void PostBlotsLoad()
{
    extern BLOT *D_002486B0[];

    for (int i = 0x24; i >= 0; i--)
    {
        BLOT *pblot = D_002486B0[i];
        ((VTBLOT *)pblot->pvtblot)->pfnPostBlotLoad(pblot);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", UpdateBlots__Fv);

void ForceHideBlots()
{
    extern BLOT *D_002486B0[];

    for (int i = 0x24; i >= 0; i--)
    {
        BLOT *pblot = D_002486B0[i];
        ((void (*)(BLOT *, BLOTS))pblot->pvtblot->pfnSetBlotBlots)(pblot, BLOTS_Hidden);
    }
}

void ResetBlots(void)
{
    extern BLOT *D_002486B0[];
    
    for (int i = 0; i < 0x25; i++)
    {
        BLOT *pblot = D_002486B0[i];
        ((VTBLOT *)pblot->pvtblot)->pfnOnBlotReset(pblot);
    }
}

void RenderBlots()
{
    extern BLOT *D_002486B0[];

    BLOT **ppblot = D_002486B0;

    for (int i = 0x24; i >= 0; i--)
    {
        BLOT *pblot = *ppblot;
        ppblot++;

        if (pblot->blots != BLOTS_Hidden)
        {
            if (((VTBLOT *)pblot->pvtblot)->pfnRenderBlot != NULL)
                ((VTBLOT *)pblot->pvtblot)->pfnRenderBlot(pblot);
        }
    }
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
    ((void (*)(BLOT *, BLOTS))pblot->pvtblot->pfnSetBlotBlots)(pblot, BLOTS_Hidden);
}

void ShowBlot(BLOT *pblot)
{
    switch (pblot->blots)
    {
    case BLOTS_Hidden:
    case BLOTS_Disappearing:
        ((void (*)(BLOT *, BLOTS))pblot->pvtblot->pfnSetBlotBlots)(pblot, BLOTS_Appearing);
        break;
    case BLOTS_Visible:
        pblot->tBlots = *pblot->ptNow;
        break;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", HideBlot__FP4BLOT);

INCLUDE_ASM("asm/nonmatchings/P2/screen", SetBlotBlots__FP4BLOT5BLOTS);

INCLUDE_ASM("asm/nonmatchings/P2/screen", FIncludeBlotForPeg__FP4BLOTT0);

void ResizeBlot(BLOT *pblot, float dx, float dy)
{
    if (dx >= 0.0f)
        pblot->width = dx;
    if (dy >= 0.0f)
        pblot->height = dy;
    RepositionBlot(pblot);
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", RepositionBlot__FP4BLOT);

INCLUDE_ASM("asm/nonmatchings/P2/screen", RepositionBlotDependents__FP4BLOT);

INCLUDE_ASM("asm/nonmatchings/P2/screen", SetBlotClock__FP4BLOTPf);

INCLUDE_ASM("asm/nonmatchings/P2/screen", PostCtrLoad__FP3CTR);

INCLUDE_ASM("asm/nonmatchings/P2/screen", UpdateCtr__FP3CTR);

INCLUDE_ASM("asm/nonmatchings/P2/screen", DrawCtr__FP3CTR);

INCLUDE_ASM("asm/nonmatchings/P2/screen", RebuildCtrAchzDraw__FP3CTR);

float DtVisibleCtr(CTR *pctr)
{
    return g_clock.fEnabled ? 2.5f : 0.0f;
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001ab600);

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

void FUN_001ac060(TIMER *ptimer)
{
    int n = STRUCT_OFFSET(ptimer, 0x270, int) - 1;
    STRUCT_OFFSET(ptimer, 0x270, int) = n;
    if (n <= 0)
    {
        int s = STRUCT_OFFSET(ptimer, 0x26c, int) - 1;
        STRUCT_OFFSET(ptimer, 0x26c, int) = s;
        if (s <= 0)
        {
            STRUCT_OFFSET(ptimer, 0x270, int) = 0;
            STRUCT_OFFSET(ptimer, 0x26c, int) = 0;
        }
        else
        {
            STRUCT_OFFSET(ptimer, 0x270, int) = STRUCT_OFFSET(ptimer, 0x264, int);
        }
    }

    {
        int tmp = STRUCT_OFFSET(ptimer, 0x26c, int) - 1;
        int num = (tmp > -1 ? tmp : 0) * STRUCT_OFFSET(ptimer, 0x264, int) + STRUCT_OFFSET(ptimer, 0x270, int);
        STRUCT_OFFSET(ptimer, 0x278, float) = (float)num / (float)STRUCT_OFFSET(ptimer, 0x268, int);
        STRUCT_OFFSET(ptimer, 0x27c, float) = g_clock.t;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001ac0e8);

extern CFont *D_002743D0;

void PostNoteLoad(NOTE *pnote)
{
    CFont *pfont;
    void *pv;

    PostBlotLoad(pnote);
    pfont = STRUCT_OFFSET(pnote, 0x4, CFont *);
    pv = STRUCT_OFFSET(pfont, 0x4c, void *);
    STRUCT_OFFSET(pnote, 0x4, int) =
        (*(int (**)(void *, float, float))((uint8_t *)pv + 0xc))(
            (uint8_t *)pfont + STRUCT_OFFSET(pv, 0x8, short), 1.25f, 1.25f);
    if (FUN_0015c188(2))
    {
        STRUCT_OFFSET(pnote, 0x210, CFont **) = &D_002743D0;
        *STRUCT_OFFSET(pnote, 0x210, CFont **) = FUN_0015c1c0(2);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", SetNoteAchzDraw__FP4NOTEPc);

INCLUDE_ASM("asm/nonmatchings/P2/screen", DrawNote__FP4NOTE);

extern CFont *D_002743F0;

void FUN_001ac888(BLOT *pblot)
{
    CFont *pfont;
    void *pv;

    PostBlotLoad(pblot);
    pfont = STRUCT_OFFSET(pblot, 0x4, CFont *);
    pv = STRUCT_OFFSET(pfont, 0x4c, void *);
    STRUCT_OFFSET(pblot, 0x4, int) =
        (*(int (**)(void *, float, float))((uint8_t *)pv + 0xc))(
            (uint8_t *)pfont + STRUCT_OFFSET(pv, 0x8, short), 0.9f, 0.9f);
    STRUCT_OFFSET(pblot, 0x208, unsigned int) = 0xDF7F7F7F;
    if (FUN_0015c188(2))
    {
        STRUCT_OFFSET(pblot, 0x210, CFont **) = &D_002743F0;
        *STRUCT_OFFSET(pblot, 0x210, CFont **) = FUN_0015c1c0(2);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001ac910);

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001ac990);

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001ac9e0);

void FUN_001aca30(BLOT *pblot)
{
    if (STRUCT_OFFSET(pblot, 0x250, int) == 3 && STRUCT_OFFSET(pblot, 0x260, int) != 0)
        return;
    ShowBlot(pblot);
}

void FUN_001aca68(BLOT *pblot)
{
    if (STRUCT_OFFSET(pblot, 0x250, int) == 3 && STRUCT_OFFSET(pblot, 0x260, int) != 0)
    {
        STRUCT_OFFSET(pblot, 0x260, int) = 0;
        return;
    }
    HideBlot(pblot);
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", DrawTitle__FP5TITLE);

extern CFont *D_00274410;

void PostTotalsLoad(TOTALS *ptotals)
{
    PostBlotLoad((BLOT *)ptotals);
    CFont *pfont = FUN_0015c1c0(0);
    void *pv = STRUCT_OFFSET(pfont, 0x4c, void *);
    STRUCT_OFFSET(ptotals, 0x4, int) =
        (*(int (**)(void *, float, float))((uint8_t *)pv + 0xc))(
            (uint8_t *)pfont + STRUCT_OFFSET(pv, 0x8, short), 1.0f, 1.0f);
    STRUCT_OFFSET(ptotals, 0x20c, float) = 0.8f;
    STRUCT_OFFSET(ptotals, 0x248, float) = 0.5f;
    if (FUN_0015c188(2))
    {
        STRUCT_OFFSET(ptotals, 0x210, CFont **) = &D_00274410;
        *STRUCT_OFFSET(ptotals, 0x210, CFont **) = FUN_0015c1c0(2);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001ace38);

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001acee0);

INCLUDE_ASM("asm/nonmatchings/P2/screen", render_level_info_from_id);

INCLUDE_ASM("asm/nonmatchings/P2/screen", render_level_info);

INCLUDE_ASM("asm/nonmatchings/P2/screen", render_hideout_world_info);

void SetTotalsBlots(TOTALS *ptotals, BLOTS blots)
{
    if (ptotals->fReshow && blots == BLOTS_Hidden)
    {
        ptotals->fReshow = 0;
        SetBlotAchzDraw(ptotals, (char *)&ptotals->grflsReshow);
        blots = BLOTS_Appearing;
    }

    if (blots == BLOTS_Hidden)
        STRUCT_OFFSET(ptotals, 0x464, int) = 0;

    SetBlotBlots(ptotals, blots);
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", ShowTotalsQMARK);

INCLUDE_ASM("asm/nonmatchings/P2/screen", HideTotalsQMARK);

INCLUDE_ASM("asm/nonmatchings/P2/screen", DrawTotals__FP6TOTALS);

extern char D_0024CEE0[];

void FUN_001ad6a8(BLOT *pblot)
{
    PostBlotLoad(pblot);
    CFont *pfont = FUN_0015c1c0(2);
    void *pv = STRUCT_OFFSET(pfont, 0x4c, void *);
    STRUCT_OFFSET(pblot, 0x4, int) =
        (*(int (**)(void *, float, float))((uint8_t *)pv + 0xc))(
            (uint8_t *)pfont + STRUCT_OFFSET(pv, 0x8, short), 1.0f, 1.0f);
    ((VTBLOT *)pblot->pvtblot)->pfnSetBlotAchzDraw(pblot, D_0024CEE0);
    STRUCT_OFFSET(pblot, 0x260, int) = 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001ad718);

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001ad7b0);

void FUN_001ad940(BLOT *pblot)
{
    PostBlotLoad(pblot);
    pblot->dtDisappear = 0.5f;
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001ad970);

void DrawLetterbox(LETTERBOX *pletterbox)
{
    float u = pletterbox->uOn * 66.400009f;
    float v = 492.80002f - u;

    g_gifs.AddPrimPack(6, 7, 0x44441EE);
    g_gifs.PackAD(0x47, 0x30000);
    g_gifs.PackAD(0x42, 0x44);
    g_gifs.PackRGBA(0x80000000);
    g_gifs.PackXYZF(0x6C00, 0x7900, 0xFFFFFF0, 0);
    g_gifs.PackXYZF(0x9400, (int)((u * 0.45454547f + 1936.0f) * 16.0f), 0xFFFFFF0, 0);
    g_gifs.PackXYZF(0x6C00, (int)((v * 0.45454547f + 1936.0f) * 16.0f), 0xFFFFFF0, 0);
    g_gifs.PackXYZF(0x9400, 0x8700, 0xFFFFFF0, 0);
}

extern float D_00274448;
extern float D_0027444C;
extern CFont *D_00274450;
extern char D_0024CEF0[];

void FUN_001adc60(BLOT *pblot)
{
    PostBlotLoad(pblot);
    CFont *pfont = STRUCT_OFFSET(pblot, 0x4, CFont *);
    void *pv = STRUCT_OFFSET(pfont, 0x4c, void *);
    STRUCT_OFFSET(pblot, 0x4, int) =
        (*(int (**)(void *, float, float))((uint8_t *)pv + 0xc))(
            (uint8_t *)pfont + STRUCT_OFFSET(pv, 0x8, short), D_00274448, D_0027444C);
    if (FUN_0015c1c0(2))
    {
        STRUCT_OFFSET(pblot, 0x210, CFont **) = &D_00274450;
        *STRUCT_OFFSET(pblot, 0x210, CFont **) = FUN_0015c1c0(2);
    }

    SHD *pshd = PshdFindShader((OID)0x493);
    STRUCT_OFFSET(pblot, 0x260, SHD *) = pshd;
    if (pshd != NULL)
    {
        ResizeBlot(pblot, 366.75f, 165.75f);
    }
    else
    {
        ((void (*)(BLOT *, char *))((VTBLOT *)pblot->pvtblot)->pfnSetBlotAchzDraw)(pblot, D_0024CEF0);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", DrawLogo__FP4LOGO);

extern float D_0027446C;
extern float D_00274470;
extern CFont *D_00274488;
extern void *D_00269988;

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001adf28);

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001adff0);

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001ae130);

INCLUDE_ASM("asm/nonmatchings/P2/screen", UpdateAttract__FP7ATTRACT);

INCLUDE_ASM("asm/nonmatchings/P2/screen", DrawAttract__FP7ATTRACT);

INCLUDE_ASM("asm/nonmatchings/P2/screen", DrawLineScreen__FUiUiUiUiUiUiG4RGBAi);

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001ae510);

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001ae5e0);

extern float D_002744AC;

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
    ((void (*)(BLOT *, char *))((VTBLOT *)pblot->pvtblot)->pfnSetBlotAchzDraw)(pblot, achz);
    pblot->achzDraw[0] = 0;
}

void FUN_001ae7f8(CTR *pctr, BLOTS blots)
{
    if (blots == BLOTS_Hidden)
        pctr->nDisplay = 0;

    SetBlotBlots(pctr, blots);
}

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001ae820);

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001aea08);

INCLUDE_ASM("asm/nonmatchings/P2/screen", FUN_001aea70);

JUNK_WORD(0xE48C0000);
JUNK_WORD(0xE48C0008);

void FUN_001aec90(void)
{
    FUN_001aea70(1, 0xFFFF);
}
