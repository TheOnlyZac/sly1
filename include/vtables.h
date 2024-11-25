/**
 * @file vtables.h
 *
 * @brief Manually crafted vtables for various structs.
 */
#ifndef VTABLES_H
#define VTABLES_H

struct BLOT;

/**
 * @brief VT for generic blots.
 */
struct VTBLOT
{
    void (*pfnInitBlot)(BLOT *);
    void (*pfnPostBlotLoad)(BLOT *);
    void (*pfnUpdateBlot)(BLOT *);
    void (*pfnOnBlotActive)(BLOT *);
    void (*pfnUpdateBlotActive)(BLOT *);
    void (*pfnOnBlotReset)(BLOT *);
    void (*pfnOnBlotPush)(BLOT *);
    void (*pfnOnBlotPop)(BLOT *);
    void (*pfnSetBlotAchzDraw)(BLOT *, const char *);
    void (*pfnDrawBlot)(BLOT *);
    void (*pfnRenderBlot)(BLOT *);
    void (*pfnDtAppearBlot)(BLOT *);
    void (*pfnDtVisibleBlot)(BLOT *);
    void (*pfnDtDisappearBlot)(BLOT *);
    void (*pfnShowBlot)(BLOT *);
    void (*pfnHideBlot)(BLOT *);
    void (*pfnSetBlotBlots)(BLOT *);
    void (*pfnSetBlotClock)(BLOT *);
    int  (*pfnFIncludeBlotForPeg)(BLOT *);
};

/**
 * @brief VT for the note blot.
 */
struct VTNOTE
{
    void (*pfnInitBlot)(BLOT *);
    void (*pfnPostNoteLoad)(BLOT *);
    void (*pfnUpdateBlot)(BLOT *);
    void (*pfnOnBlotActive)(BLOT *);
    void (*pfnUpdateBlotActive)(BLOT *);
    void (*pfnOnBlotReset)(BLOT *);
    void (*pfnOnBlotPush)(BLOT *);
    void (*pfnOnBlotPop)(BLOT *);
    void (*pfnSetNoteAchzDraw)(BLOT *, const char *);
    void (*pfnDrawNote)(BLOT *);
    void (*pfnRenderBlot)(BLOT *);
    void (*pfnDtAppearBlot)(BLOT *);
    void (*pfnDtVisibleBlot)(BLOT *);
    void (*pfnDtDisappearBlot)(BLOT *);
    void (*pfnShowBlot)(BLOT *);
    void (*pfnHideBlot)(BLOT *);
    void (*pfnSetBlotBlots)(BLOT *);
    void (*pfnSetBlotClock)(BLOT *);
    int  (*pfnFIncludeBlotForPeg)(BLOT *);
};

/**
 * @brief VT for the binoc blot.
 */
struct VTBINOC
{
    void (*pfnInitBinoc)(BLOT *);
    void (*pfnPostBinocLoad)(BLOT *);
    void (*pfnUpdateBlot)(BLOT *);
    void (*pfnOnBinocActive)(BLOT *);
    void (*pfnUpdateBinocActive)(BLOT *);
    void (*pfnOnBinocReset)(BLOT *);
    void (*pfnOnBinocPush)(BLOT *);
    void (*pfnOnBinocPop)(BLOT *);
    void (*pfnSetBinocAchzDraw)(BLOT *, const char *);
    void (*pfnDrawBinoc)(BLOT *);
    void (*pfnRenderBlot)(BLOT *);
    void (*pfnDtAppearBinoc)(BLOT *);
    void (*pfnDtVisibleBlot)(BLOT *);
    void (*pfnDtDisappearBinoc)(BLOT *);
    void (*pfnShowBlot)(BLOT *);
    void (*pfnHideBlot)(BLOT *);
    void (*pfnSetBinocBlots)(BLOT *);
    void (*pfnSetBlotClock)(BLOT *);
    int  (*pfnFIncludeBlotForPeg)(BLOT *);
};

/**
 * @brief VT for the timer blot.
 */
struct VTTIMER
{
    void (*pfnInitBlot)(BLOT *);
    void (*pfnPostTimerLoad)(BLOT *);
    void (*pfnUpdateTimer)(BLOT *);
    void (*pfnOnBlotActive)(BLOT *);
    void (*pfnUpdateBlotActive)(BLOT *);
    void (*pfnOnBlotReset)(BLOT *);
    void (*pfnOnBlotPush)(BLOT *);
    void (*pfnOnBlotPop)(BLOT *);
    void (*pfnSetBlotAchzDraw)(BLOT *, const char *);
    void (*pfnDrawTimer)(BLOT *);
    void (*pfnRenderBlot)(BLOT *);
    void (*pfnDtAppearBlot)(BLOT *);
    void (*pfnDtVisibleBlot)(BLOT *);
    void (*pfnDtDisappearBlot)(BLOT *);
    void (*pfnShowBlot)(BLOT *);
    void (*pfnHideBlot)(BLOT *);
    void (*pfnSetBlotBlots)(BLOT *);
    void (*pfnSetBlotClock)(BLOT *);
    int  (*pfnFIncludeBlotForPeg)(BLOT *);
};

struct GAME;

/**
 * @brief VT for the game struct.
 */
struct VTGAME
{
    // ...
};

#endif // VTABLES_H
