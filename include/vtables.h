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


/*****************************************************************
 * BASIC-DERIVED VTABLES
 *****************************************************************/

struct CBinaryInputStream;
struct LO;
struct ALO;
struct SO;

/**
 * @brief VT for basic objects.
 */
struct VTBASIC
{
    VT *pvtSuper;
    CID cid;
};

/**
 * @brief VT for LO objects.
 */
struct VTLO : VT
{
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
    void (*pfnUpdateLoXfWorld)(LO *);
    void (*pfnUpdateLoXfWorldHierarchy)();
    void (*pfnFreezeLo)();
    void (*pfnSetLoParent)();
    void (*pfnApplyLoProxy)();
    void (*pfnSubscribeLoObject)();
    void (*pfnUnsubscribeLoObject)();
    void (*pfnSubscribeLoStruct)();
    void (*pfnUnsubscribeLoStruct)();
};

/**
 * @brief VT for ALO objects.
 * @todo Verify the fields and add parameters.
 */
struct VTALO : VT
{
    void (*pfnInitAlo)(ALO *);
    void (*pfnSetLoDefaults)(ALO *);
    void (*pfnAddLo)(ALO *);
    void (*pfnRemoveLo)(ALO *);
    void (*pfnAddAloHierarchy)(ALO *);
    void (*pfnRemoveAloHierarchy)(ALO *);
    void (*pfnOnAloAdd)(ALO *);
    void (*pfnOnAloRemove)(ALO *);
    void (*pfnCloneAloHierarchy)(ALO *);
    void (*pfnCloneAlo)(ALO *);
    void (*pfnLoadAloFromBrx)(ALO *);
    void (*pfnAddLoRecursive)(ALO *);
    void (*pfnRemoveLoRecursive)(ALO *);
    void (*pfnHandleAloMessage)(ALO *);
    void (*pfnSendLoMessage)(ALO *);
    void (*pfnBindAlo)(ALO *);
    void (*pfnPostAloLoad)(ALO *);
    void (*pfnUpdateAlo)(ALO *);
    void (*pfnUpdateAloXfWorld)(ALO *);
    void (*pfnUpdateAloXfWorldHierarchy)(ALO *);
    void (*pfnFreezeAlo)(ALO *);
    void (*pfnSetAloParent)(ALO *);
    void (*pfnApplyAloProxy)(ALO *);
    void (*pfnSubscribeLoObject)(ALO *);
    void (*pfnUnsubscribeLoObject)(ALO *);
    void (*pfnSubscribeLoStruct)(ALO *);
    void (*pfnUnsubscribeLoStruct)(ALO *);
    void (*pfnProjectAloTransform)(ALO *);
    void (*pfnPresetAloAccel)(ALO *);
    void (*pfnTranslateAloToPos)(ALO *);
    void (*pfnRotateAloToMat)(ALO *);
    void (*pfnMatchAloOtherObject)(ALO *);
    void (*pfnSetAloVelocityVec)(ALO *);
    void (*pfnSetAloAngularVelocityVec)(ALO *);
    void (*pfnPredictAloPosition)(ALO *);
    void (*pfnPredictAloRotation)(ALO *);
    void (*pfnRenderAloAll)(ALO *);
    void (*pfnRenderAloSelf)(ALO *);
    void (*pfnRenderAloGlobset)(ALO *);
    void (*pfnUpdateAloInfluences)(ALO *);
    void (*pfnAdjustAloPosition)(ALO *);
    void (*pfnAdjustAloRotation)(ALO *);
    void (*pfnUnadjustAloRotation)(ALO *);
    void (*pfnRecacheAloActList)(ALO *);
    void (*pfnUpdateAloConstraints)(ALO *);
    void (*pfnFAbsorbAloWkr)(ALO *);
};

/**
 * @brief VT for SO objects.
 * @todo Verify the fields and add parameters.
 */
struct VTSO : VT
{
    void (*pfnInitSo)(SO *);
    void (*pfnSetLoDefaults)(LO *);
    void (*pfnAddLo)(LO *);
    void (*pfnRemoveLo)(LO *);
    void (*pfnAddLoHierarchy)(LO *);
    void (*pfnRemoveLoHierarchy)(LO *);
    void (*pfnOnSoAdd)(SO *);
    void (*pfnOnSoRemove)(SO *);
    void (*pfnCloneAloHierarchy)(ALO *);
    void (*pfnCloneSo)(SO *);
    void (*pfnLoadSoFromBrx)(SO *, CBinaryInputStream *);
    void (*pfnAddLoRecursive)();
    void (*pfnRemoveLoRecursive)();
    void (*pfnHandleAloMessage)();
    void (*pfnSendSoMessage)();
    void (*pfnBindAlo)();
    void (*pfnPostAloLoad)();
    void (*pfnUpdateSo)();
    void (*pfnUpdateSoXfWorld)();
    void (*pfnUpdateSoXfWorldHierarchy)();
    void (*pfnFreezeSo)();
    void (*pfnSetSoParent)();
    void (*pfnApplySoProxy)();
    void (*pfnSubscribeLoObject)();
    void (*pfnUnsubscribeLoObject)();
    void (*pfnSubscribeLoStruct)();
    void (*pfnUnsubscribeLoStruct)();
    void (*pfnUpdateLoLiveEdit)();
    void (*pfnProjectSoTransform)();
    void (*pfnPresetSoAccel)();
    void (*pfnTranslateSoToPos)();
    void (*pfnRotateSoToMat)();
    void (*pfnMatchAloOtherObject)();
    void (*pfnSetSoVelocityVec)();
    void (*pfnSetSoAngularVelocityVec)();
    void (*pfnPredictAloPosition)();
    void (*pfnPredictAloRotation)();
    void (*pfnRenderAloAll)();
    void (*pfnRenderSoSelf)();
    void (*pfnRenderAloGlobset)();
    void (*pfnUpdateAloInfluences)();
    void (*pfnAdjustAloPosition)();
    void (*pfnAdjustAloRotation)();
    void (*pfnUnadjustAloRotation)();
    void (*pfnRecacheAloActList)();
    void (*pfnUpdateAloConstraints)();
    void (*pfnFAbsorbSoWkr)();
    void (*pfnDisplaceSo)();
    void (*pfnImpactSo)();
    void (*pfnPivotSo)();
    void (*pfnUpdateSoBounds)(SO *);
    void (*pfnAddSoExternalAccelerations)();
    void (*pfnCloneSoPhys)();
    void (*pfnRenumberSo)();
    void (*pfnPropagateSoForce)();
    void (*pfnDistributeSoEffects)();
    void (*pfnFIgnoreSoIntersection)();
    void (*pfnAddSoXps)();
    void (*pfnAddSoCustomXps)();
    void (*pfnAdjustSoXpLocal)();
    void (*pfnAdjustSoNewXp)();
    void (*pfnAdjustSoXpVelocity)();
    void (*pfnAdjustSoDz)();
    void (*pfnAdjustSoXps)();
    void (*pfnUpdateSoInternalXps)();
    void (*pfnNotifySoImpact)();
    void (*pfnUpdateSoPivots)();
    void (*pfnUpdateSoImpacts)();
    void (*pfnUpdateSoPosWorldPrev)(SO *);
    void (*pfnGetSoCpdefi)();
    void (*pfnAddSoWaterAcceleration)();
    void (*pfnFInflictSoZap)();
};

/*****************************************************************
 * BLOT-DERIVED VTABLES
 *****************************************************************/

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

/**
 * @brief VT for the totals blot.
 */
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

struct GOMER;

/**
 * @brief VT for the gomer struct.
 */
struct VTGOMER
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

struct SAA;
struct SAAF;
struct SAI;
struct ALO;
struct RPL;
struct SHD;
struct SGVR;
struct GLOBSET;
struct GLOB;
struct SUBGLOB;

/**
 * @brief VT for SAA struct.
 */
struct VTSAA
{
    void (*pfnInit)(SAA*, SAAF*);
    void (*pfnPostLoad)(SAA*);
    void (*pfnUpdate)(SAA*, float);
    float (*pfnUComplete)(SAA*);
    void (*pfnNotifyRender)(SAA*, ALO*, RPL*);
    SAI* (*pfnPsaiFromSaaShd)(SAA*, SHD*);
    void (*pfnSetSgvr)(SAA*, SGVR*, GLOBSET*, GLOB*, SUBGLOB*);
    void* pfnUnk1C;
};

/**
 * @brief VT for an act related struct.
 */
struct VTACT
{
    // ...
};

#endif // VTABLES_H
