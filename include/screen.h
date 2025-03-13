/**
 * @file screen.h
 *
 * @brief GUI elements.
 */
#ifndef SCREEN_H
#define SCREEN_H

#include "common.h"
#include <font.h>
#include <game.h>
#include <shd.h>

class CTextEdge; // Forward declaration

// MARK: Blot

enum BLOTE
{
    BLOTE_Nil = -1,
    BLOTE_Left = 0,
    BLOTE_Right = 1,
    BLOTE_Top = 2,
    BLOTE_Bottom = 3,
    BLOTE_Max = 4
};

enum BLOTK
{
    BLOTK_Nil = -1,
    // ...
    BLOTK_Max = 0x1d
};

enum BLOTS
{
    BLOTS_Nil = -1,
    BLOTS_Hidden = 0,
    BLOTS_Appearing = 1,
    BLOTS_Visible = 2,
    BLOTS_Disappearing = 3,
    BLOTS_Max = 4
};

struct BLOTI
{
    float x, y;
    BLOTE blote;
    BLOTK blotkPeg;
    BLOTE blotePeg;
};

/**
 * @brief User interface state.
 */
enum UIS
{
    UIS_Nil = -1,
    UIS_Splash = 0,
    UIS_Attract = 1,
    UIS_Playing = 2,
    UIS_Pausing = 3,
    UIS_Paused = 4,
    UIS_Unpausing = 5,
    UIS_WorldMap = 6,
    // todo What is 7?
    UIS_Wiping = 8,
    UIS_Max = 9
};

struct BLOT
{
    union
    {
        VTBLOT *pvtblot;
        VTNOTE *pvtnote;
        VTBINOC *pvtbinoc;
        VTTIMER *pvttimer;
    };
    CFont *pfont;
    undefined1 achzDraw[512];
    RGBA rgba;
    float rFontScale;
    CTextEdge *pte;
    BLOTK blotk;
    BLOTI *bloti;
    float x, y;
    float xOn, yOn;
    float dx, dy;
    float width, height;
    float uOn;
    float dtAppear;
    float dtVisible;
    float dtDisappear;
    float dtBlotsExtra;
    BLOTS blots;
    float tBlots;
    float *ptNow;
    int fActive;
};

// MARK: Timer

/**
 * @brief Timer state.
 */
enum TIMERS
{
    TIMERS_Nil = -1,
    TIMERS_Expired = 0,
    TIMERS_Paused = 1,
    TIMERS_Running = 2,
    TIMERS_Max = 3
};

struct TIMER : public BLOT
{
    TIMERS timers;
    float tTimers;
    float dt;
    float svt;
    int nSecondsLast;
    int nTenthsLast;
    float dtThreshold;
    RGBA rgbaThreshold;
    void *pfntnThreshold; // should be a function pointer
    int fThreshold;
    float dtExpire;
    void *pfntnExpire; // should be a function pointer
    int fStopped;
};

// MARK: Counters

struct CTR : public BLOT
{
    int nDisplay;
    int *pnActual;
    int *pnTotal;
    float dgDisplayMax;
    float uRemain;
    void *pfnsmack; // should be a function pointer
    void *pv;
};

struct TRUNKCTR : public CTR
{
};
struct CRUSHERCTR : public CTR
{
};
struct LIFECTR : public CTR
{
};
struct CLUECTR : public CTR
{
};
struct KEYCTR : public CTR
{
};
struct COINCTR : public CTR
{
};

extern LIFECTR g_lifectr;
extern CLUECTR g_cluectr;
extern KEYCTR g_keyctr;
extern COINCTR g_coinctr;

// MARK: Totals

struct TOTALS : public BLOT
{
    int fReshow;
    GRFLS grflsReshow;
};

extern TOTALS g_totals;

// MARK: Note

struct NOTE : public BLOT
{
    undefined1 padding_0[24];
    struct NOTE *unk278;
};

extern NOTE g_note;

// MARK: Letterbox

struct LETTERBOX : public BLOT
{
    // empty
};

// MARK: Title

struct TITLE : public BLOT
{
    int fReshow;
    char *pchzReshow;
};

// MARK: Attract

struct ATTRACT : public BLOT
{
    int fJoyValid;
    int fReshow;
    char *pchzReshow;
};

// MARK: Logo

struct LOGO : public BLOT
{
    SHD *pshd;
};

// MARK: CTextEdge

class CTextEdge
{
    CFont *m_pfont;
    char m_ch;
    // 3 empty bytes for alignment
    float m_dxExtra;
    float m_dyExtra;
    float m_rxScaling;
    float m_ryScaling;
    RGBA m_rgba;
};

// Global blots
extern LIFECTR g_lifectr;
extern CLUECTR g_cluectr;
extern KEYCTR g_keyctr;
extern COINCTR g_coinctr;

void StartupScreen();

void PostBlotsLoad();

void UpdateBlots();

void ForceHideBlots();

void ResetBlots();

void RenderBlots();

void DrawBlots();

void InitBlot(BLOT *pblot, BLOTK blotk);

void PostBlotLoad(BLOT *pblot);

void UpdateBlot(BLOT *pblot);

void SetBlotAchzDraw(BLOT *pblot, char *achzDraw);

void FUN_001aa5a0(undefined1 *param_1);

void SetBlotFontScale(float rFontScale, BLOT *pblot);

void DrawBlot(BLOT *pblot);

float DtAppearBlot(BLOT *pblot);

float DtVisibleBlot(BLOT *pblot);

float DtDisappearBlot(BLOT *pblot);

void SetBlotDtAppear(BLOT *pblot, float dtAppear);

void SetBlotDtVisible(BLOT *pblot, float dtVisible);

void SetBlotDtDisappear(BLOT *pblot, float dtDisappear);

void OnBlotReset(BLOT *pblot);

void ShowBlot(BLOT *pblot);

void HideBlot(BLOT *pblot);

void SetBlotBlots(BLOT *pblot, BLOTS blots);

int pfnFIncludeBlotForPeg(BLOT *pblot, BLOT *pblotOther);

void ResizeBlot(BLOT *pblot, float dx, float dy);

void RepositionBlot(BLOT *pblot);

void RepositionBlotDependents(BLOT *pblot);

void SetBlotClock(BLOT *pblot, float *pt);

void PostCtrLoad(CTR *pctr);

void UpdateCtr(CTR *pctr);

void DrawCtr(CTR *pctr);

void RebuildCtrAchzDraw(CTR *pctr);

float DtVisibleCtr(CTR *pctr);

void FUN_001ab600(BLOT *pblot);

void UpdateTimer(TIMER *ptimer);

void DrawTimer(TIMER *ptimer);

void SetTimer(TIMER *ptimer, float dt);

void SetTimerSpeed(TIMER *ptimer, float svt);

void SetTimerExpire(TIMER *ptimer, float dt, void *pfntn);

void StartTimer(TIMER *ptimer);

void StartTimer(TIMER *ptimer);

void RebuildTimerAchzDraw(TIMER *ptimer, float dt);

void SetTimerTimers(TIMER *ptimer, TIMERS timers);

float DtVisibleTrunkctr(TRUNKCTR *ptrunkctr);

float DtVisibleCrusherctr(CRUSHERCTR *pcrusherctr);

void FUN_001abe70(BLOT *pblot);

void FUN_001ac060(BLOT *pblot);

void FUN_001ac0e8(int param_1);

void PostNoteLoad();

void PostNoteLoad(BLOT *pblot);

void SetNoteAchzDraw(NOTE *pnote, char *pchz);

void DrawNote(BLOT *pblot);

void FUN_001ac888(BLOT *pblot);

void FUN_001ac910(undefined8 param_1, char *param_2);

void FUN_001ac990(BLOT *pblot, int param_2);

undefined4 FUN_001ac9e0(BLOT *pblot, BLOT *pblotOther);

void FUN_001aca30(BLOT *pblot);

void FUN_001aca68(BLOT *pblot);

void DrawTitle(TITLE *ptitle);

void PostTotalsLoad(TOTALS *ptotals);

void FUN_001ace38(undefined8 param_1, long param_2);

ulong FUN_001acee0(char *pchz, uint *param_2, ulong param_3);

void render_level_info_from_id(BLOT *pblot, uint level_id);

void render_level_info(BLOT *pblot, uint world_id, uint map_id);

void render_hideout_world_info(BLOT *pblot, int world_id);

void SetTotalsBlots(TOTALS *ptotals, BLOTS blots);

void ShowTotals(TOTALS *ptotals);

void HideTotals(TOTALS *ptotals);

void DrawTotals(TOTALS *ptotals);

void FUN_001ad6a8(undefined8 param_1);

void FUN_001ad718(BLOT *pblot);

void FUN_001ad7b0(int param_1);

void FUN_001ad940(BLOT *pblot);

void FUN_001ad970(BLOT *pblot, uint blots);

void DrawLetterbox(LETTERBOX *pletterbox);

void FUN_001adc60(undefined8 param_1);

void DrawLogo(LOGO *ploto);

void FUN_001adf28(BLOT *pblot);

void FUN_001adff0(BLOT *pblot);

void FUN_001ae130(BLOT *pblot, int param_2);

void UpdateAttract(ATTRACT *pattract);

void DrawLineScreen(uint x1, uint y1, uint z1, uint x2, uint y2, uint z2, RGBA *rgba, int fDepthTest);

#endif // SCREEN_H
