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
#include <joy.h>
#include <wipe.h>
#include <oid.h>

struct SHD; // Forward declaration.
SHD *PshdFindShader(OID oid);
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

struct BLOT
{
    union
    {
        VTBLOT *pvtblot;
        VTNOTE *pvtnote;
        VTBINOC *pvtbinoc;
        VTTIMER *pvttimer;
        VTTOTALS *pvttotals;
    };
    CFont *pfont;
    char achzDraw[512];
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
    void (*pfnsmack)(void *);
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
    STRUCT_PADDING(6);
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

/**
 * @brief Calls the post-load virtual on every global blot, in reverse order.
 */
void PostBlotsLoad();

/**
 * @brief Updates every global blot (in reverse order) and then the screen wipe, using the joy state when its flag is set.
 */
void UpdateBlots();

/**
 * @brief Sets every global blot to the hidden state immediately.
 */
void ForceHideBlots();

/**
 * @brief Calls the reset virtual on every global blot.
 */
void ResetBlots();

/**
 * @brief Calls the render virtual on every global blot that is not hidden.
 */
void RenderBlots();

/**
 * @brief Draws every non-hidden global blot, then the wipe and the extra overlay (FUN_001ae820).
 */
void DrawBlots();

/**
 * @brief Initialises a blot from its BLOTI table entry: default appear/disappear times, clock, and size.
 * @param pblot Blot to initialise.
 * @param blotk Blot kind, indexes the BLOTI table (D_0026C3E0).
 */
void InitBlot(BLOT *pblot, BLOTK blotk);

void PostBlotLoad(BLOT *pblot);

void UpdateBlot(BLOT *pblot);

void SetBlotAchzDraw(BLOT *pblot, char *achzDraw);

void FUN_001aa5a0(undefined1 *param_1);

void SetBlotFontScale(BLOT *pblot, float rFontScale);

void DrawBlot(BLOT *pblot);

float DtAppearBlot(BLOT *pblot);

float DtVisibleBlot(BLOT *pblot);

float DtDisappearBlot(BLOT *pblot);

void SetBlotDtAppear(BLOT *pblot, float dtAppear);

void SetBlotDtVisible(BLOT *pblot, float dtVisible);

void SetBlotDtDisappear(BLOT *pblot, float dtDisappear);

/**
 * @brief Resets a blot by setting it to the hidden state via its vtable.
 * @param pblot Blot to reset.
 */
void OnBlotReset(BLOT *pblot);

/**
 * @brief Makes a blot appear. If already visible, restarts its visible timer.
 * @param pblot Blot to show.
 */
void ShowBlot(BLOT *pblot);

/**
 * @brief Starts disappearing a blot that is appearing or visible.
 * @param pblot Blot to hide.
 */
void HideBlot(BLOT *pblot);

void SetBlotBlots(BLOT *pblot, BLOTS blots);

/**
 * @brief Decides whether another blot may be pegged to this one, based on both blot states.
 * @param pblot Blot.
 * @param pblotOther Other blot.
 * @return 1 if included, otherwise 0.
 */
int FIncludeBlotForPeg(BLOT *pblot, BLOT *pblotOther);

/**
 * @brief Sets a blot's size (negative values leave the dimension unchanged) and repositions it.
 * @param pblot Blot to resize.
 * @param dx New width, ignored if negative.
 * @param dy New height, ignored if negative.
 */
void ResizeBlot(BLOT *pblot, float dx, float dy);

void RepositionBlot(BLOT *pblot);

/**
 * @brief Repositions every global blot that is pegged to the given blot.
 * @param pblot Blot whose dependents should be repositioned.
 */
void RepositionBlotDependents(BLOT *pblot);

extern BLOT *D_002486B0[];
extern int D_00273C50;
extern int D_002739F0;
extern char D_0024CF98[];
extern float D_002744A8;
extern float D_00274448;
extern float D_0027444C;
extern CTextEdge D_00274450;
extern char D_0024CEF0[];
extern float D_0027446C;
extern float D_00274470;
extern CTextEdge D_00274488;
extern char *D_00269988;
extern int D_00275BF0;
extern char D_0024CEE0[];
extern CTextEdge D_002743D0;
extern CTextEdge D_002743F0;
extern CTextEdge D_00274410;
extern "C" int FUN_0015c188(int);
extern BLOTI D_0026C3E0[];
extern int D_00273EB0;
extern "C" void FUN_001ae820(void *);
extern float D_002744AC;
extern JOY g_joyZero;
extern "C" int func_001F6738(char *, char *);
extern char D_0024CE00[];
extern char *D_002744B0;
extern "C" void FUN_001aea70(int, int);
extern float D_0024CD48;
extern "C" CFont *FUN_0015c1c0(int);

/**
 * @brief Sets the clock a blot reads time from, defaulting to the global real-time clock when null.
 * @param pblot Blot to modify.
 * @param pt Pointer to the time source, or null for g_clock.tReal.
 */
void SetBlotClock(BLOT *pblot, float *pt);

void PostCtrLoad(CTR *pctr);

void UpdateCtr(CTR *pctr);

void DrawCtr(CTR *pctr);

void RebuildCtrAchzDraw(CTR *pctr);

/**
 * @brief Returns how long a counter stays visible.
 * @param pctr Counter.
 * @return 2.5 seconds when the clock is enabled, otherwise 0.
 */
float DtVisibleCtr(CTR *pctr);

/**
 * @brief Post-load setup for a timer blot (guess: PostTimerLoad).
 * @param pblot Timer blot; typed as BLOT, name and signature are a guess.
 */
void FUN_001ab600(BLOT *pblot);

/**
 * @brief Per-frame timer update: hides the timer after it expires (or when stopped) and rebuilds its text while running.
 * @param ptimer Timer blot.
 */
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

/**
 * @brief Steps a nested countdown stored at 0x264..0x270 and writes a progress fraction at 0x278 (guess: some counter blot).
 * @param pblot Blot; real type unknown.
 */
void FUN_001ac060(BLOT *pblot);

void FUN_001ac0e8(int param_1);

/**
 * @brief Post-load setup for the note blot: clones the font at 1.25 scale and sets up the text edge.
 * @param pnote Note blot.
 */
void PostNoteLoad(NOTE *pnote);

void SetNoteAchzDraw(NOTE *pnote, char *pchz);

void DrawNote(BLOT *pblot);

/**
 * @brief Post-load setup for a blot with a 0.9 scale font clone and a colour (guess: title blot).
 * @param pblot Blot; type is a guess.
 */
void FUN_001ac888(BLOT *pblot);

/**
 * @brief Title blot text setter: shows the new text immediately if hidden, otherwise queues a reshow of it (name is a guess).
 * @param ptitle Title blot.
 * @param pchz New text.
 */
void FUN_001ac910(TITLE *ptitle, char *pchz);

/**
 * @brief Blot state setter with a reshow flag at 0x260 (guess: title-like blot).
 * @param pblot Blot; type is a guess.
 * @param blots New blot state.
 */
void FUN_001ac990(BLOT *pblot, BLOTS blots);

/**
 * @brief Returns true if the blot should be pegged/included, or if a flag at 0x260 is set (guess).
 * @param pblot Blot.
 * @param pblotOther Other blot.
 * @return 1 or 0.
 */
int FUN_001ac9e0(BLOT *pblot, BLOT *pblotOther);

/**
 * @brief Show function that skips showing while disappearing with a reshow flag at 0x260 (guess: title blot).
 * @param pblot Blot; type is a guess.
 */
void FUN_001aca30(BLOT *pblot);

/**
 * @brief Hide function that clears the reshow flag at 0x260 instead of hiding when disappearing (guess: title blot).
 * @param pblot Blot; type is a guess.
 */
void FUN_001aca68(BLOT *pblot);

void DrawTitle(TITLE *ptitle);

/**
 * @brief Post-load setup for the totals blot: font clone, font scale 0.8, disappear time 0.5 and text edge.
 * @param ptotals Totals blot.
 */
void PostTotalsLoad(TOTALS *ptotals);

/**
 * @brief Sets the blot text, or queues a reshow of new text while the blot is not hidden (guess: totals/title blot).
 * @param pblot Blot; type is a guess.
 * @param pchz New text, may be null.
 */
void FUN_001ace38(BLOT *pblot, char *pchz);

ulong FUN_001acee0(char *pchz, uint *param_2, ulong param_3);

/**
 * @brief Renders level info for a packed level id (world in the high bits, map in the low byte); -1 draws a fallback string.
 * @param pblot Blot to draw into.
 * @param level_id Packed id, or -1.
 * @note Name is a community name; the argument packing is inferred from the asm.
 */
extern "C" void render_level_info_from_id(BLOT *pblot, int level_id);

extern "C" void render_level_info(BLOT *pblot, uint world_id, uint map_id);

void render_hideout_world_info(BLOT *pblot, int world_id);

/**
 * @brief Sets the totals blot state, clearing pending reshow data when hiding.
 * @param ptotals Totals blot.
 * @param blots New blot state.
 * @note Field offsets 0x264/0x464 are not yet named in TOTALS.
 */
void SetTotalsBlots(TOTALS *ptotals, BLOTS blots);

/**
 * @brief Shows the totals blot unless it is disappearing with a reshow pending.
 * @param ptotals Totals blot.
 */
void ShowTotals(TOTALS *ptotals);

/**
 * @brief Hides the totals blot, or cancels a pending reshow if it is already disappearing.
 * @param ptotals Totals blot.
 */
void HideTotals(TOTALS *ptotals);

void DrawTotals(TOTALS *ptotals);

/**
 * @brief Post-load setup for a blot: font clone, initial text from D_0024CEE0 and cleared reshow flag (guess).
 * @param pblot Blot; type is a guess.
 */
void FUN_001ad6a8(BLOT *pblot);

/**
 * @brief Update for a blot with a reshow flag at 0x260: shows or hides it depending on the UI state (guess: totals/title blot).
 * @param pblot Blot; type is a guess.
 * @note g_ui offsets 4 and 0x2c are not matched to named UI fields.
 */
void FUN_001ad718(BLOT *pblot);

void FUN_001ad7b0(int param_1);

/**
 * @brief Post-load setup: default blot load plus dtDisappear = 0.5 (name and type are a guess).
 * @param pblot Blot.
 */
void FUN_001ad940(BLOT *pblot);

/**
 * @brief Blot state setter that clears the flag at 0x260 when hiding (guess).
 * @param pblot Blot; type is a guess.
 * @param blots New blot state.
 */
void FUN_001ae7f8(BLOT *pblot, BLOTS blots);

void FUN_001ad970(BLOT *pblot, uint blots);

void DrawLetterbox(LETTERBOX *pletterbox);

/**
 * @brief Post-load setup for the logo blot (guess: PostLogoLoad): font clone, text edge, looks up shader OID 0x493 and sizes the blot to it, or falls back to text.
 * @param plogo Logo blot.
 */
void FUN_001adc60(LOGO *plogo);

void DrawLogo(LOGO *ploto);

extern "C" void FUN_001adf28(ATTRACT *pattract);

extern "C" void FUN_001adff0(BLOT *pblot);

/**
 * @brief Blot state setter that clears the flag at 0x268 and calls FUN_001adff0 when hiding (guess: attract blot).
 * @param pblot Blot; type is a guess.
 * @param blots New blot state.
 */
void FUN_001ae130(BLOT *pblot, BLOTS blots);

/**
 * @brief Per-frame update for the attract blot: refreshes joypad/idle flags and rebuilds the text when they change.
 * @param pattract Attract blot.
 * @note D_00275BF0 and D_00269988 are unidentified globals.
 */
void UpdateAttract(ATTRACT *pattract);

void DrawLineScreen(uint x1, uint y1, uint z1, uint x2, uint y2, uint z2, RGBA *rgba, int fDepthTest);

/**
 * @brief Returns a character cycling through a string, advancing five times per second of real time.
 * @return Character from the string at (int)(tReal * 5) % strlen. Name/purpose are a guess.
 */
char FUN_001aea08();

/**
 * @brief Calls FUN_001aea70(1, 0xFFFF). Meaning is unknown.
 */
void FUN_001aec90();

/**
 * @brief Post-load setup for a blot that shows one cycling character (guess).
 * @param pblot Blot; type is a guess.
 */
void FUN_001ae758(BLOT *pblot);

/**
 * @brief Post-load for a one-line label blot (two known instances formatted with sprintf); sizes it from the font (guess).
 * @param pblot Blot; type is a guess.
 */
void FUN_001ae510(BLOT *pblot);

#endif // SCREEN_H
