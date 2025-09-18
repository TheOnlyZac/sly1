/**
 * @file vtables.h
 *
 * @brief Manually crafted vtables for various structs.
 */
#ifndef VTABLES_H
#define VTABLES_H

#include <cid.h>
#include <mq.h>

typedef int GRFCID;

/**
 * @brief Generic VT struct. Used to determine which VTables an entity inherits at runtime.
 */
struct VT
{
    VT *pvtSuper;
    CID cid;
    GRFCID grfcid;
    int cb;
};

struct CBinaryInputStream;
struct LO;

/**
 * @brief VT for LO objects.
 */
struct VTLO
{
    VT *pvtSuper;
    CID cid;
    int grfcid;
    int cb;

    void (*pfnInitLo)(LO *);
    void (*pfnSetLoDefaults)(LO *);
    void (*pfnAddLo)(LO *);
    void (*pfnRemoveLo)(LO *);
    void (*pfnAddLoHierarchy)(LO *);
    void (*pfnRemoveLoHierarchy)(LO *);
    void (*pfnOnLoAdd)(LO *);
    void (*pfnOnLoRemove)(LO *);
    void (*pfnCloneLoHierarchy)(LO *, LO *);
    void (*pfnCloneLo)(LO *, LO *);
    void (*pfnLoadLoFromBrx)(LO *, CBinaryInputStream *);
    void (*pfnAddLoRecursive)(/* @todo: null in release & proto? */);
    void (*pfnRemoveLoRecursive)(/* @todo: null in release & proto? */);
    void (*pfnHandleLoMessage)(LO *, MSGID, void *);
    void (*pfnSendLoMessage)(LO *, MSGID, void *);
    void (*pfnBindLo)(LO *);
    void (*pfnPostLoLoad)(LO *);

    /**
     * @todo From prototype, not confirmed if in release
     */
    void (*pfnUpdateLo)();
    void (*pfnUpdateLoXfWorld)();
    void (*pfnUpdateLoXfWorldHierarchy)();
    void (*pfnFreezeLo)();
    void (*pfnSetLoParent)();
    void (*pfnApplyLoProxy)();
    void (*pfnSubscribeLoObject)();
    void (*pfnUnsubscribeLoObject)();
    void (*pfnSubscribeLoStruct)();
    void (*pfnUnsubscribeLoStruct)();
    void (*pfnGetLoParams)();
    void (*pfnUpdateLoLiveEdit)();
};

/**
 * @brief VT for basic objects.
 */
struct VTBASIC
{
    VT *pvtSuper;
    CID cid;
};

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

struct VTTOTALS
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
    int (*pfnFIncludeBlotForPeg)(BLOT *);
};

struct GAME;

/**
 * @brief VT for the game struct.
 */
struct VTGAME
{
    // ...
};

/**
 * @brief VT for a waypoint related struct.
 */
struct VTWPSG
{
    // ...
};

/**
 * @brief VT for a shader related struct.
 */
struct VTSAA
{
    // ...
};

/**
 * @brief VT for an act related struct.
 */
struct VTACT
{
    // ...
};

#endif // VTABLES_H
