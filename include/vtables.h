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

// MARK: SENSOR
struct SENSOR;
struct LASEN;
struct CAMSEN;
struct PRSEN;

/**
 * @brief VT for SENSOR objects.
 * @todo Add parameters.
 */
struct VTSENSOR : VT
{
    /* 0x010 */ void (*pfnInitSensor)(SENSOR *);
    /* 0x014 */ void (*pfnSetLoDefaults)(SENSOR *);
    /* 0x018 */ void (*pfnAddLo)(SENSOR *);
    /* 0x01c */ void (*pfnRemoveLo)(SENSOR *);
    /* 0x020 */ void (*pfnAddAloHierarchy)(SENSOR *);
    /* 0x024 */ void (*pfnRemoveAloHierarchy)(SENSOR *);
    /* 0x028 */ void (*pfnOnSoAdd)(SENSOR *);
    /* 0x02c */ void (*pfnOnSoRemove)(SENSOR *);
    /* 0x030 */ void (*pfnCloneAloHierarchy)(SENSOR *);
    /* 0x034 */ void (*pfnCloneSo)(SENSOR *);
    /* 0x038 */ void (*pfnLoadSoFromBrx)(SENSOR *);
    /* 0x03c */ void (*pfnAddLoRecursive)(SENSOR *);
    /* 0x040 */ void (*pfnRemoveLoRecursive)(SENSOR *);
    /* 0x044 */ void (*pfnHandleAloMessage)(SENSOR *);
    /* 0x048 */ void (*pfnSendSoMessage)(SENSOR *);
    /* 0x04c */ void (*pfnBindAlo)(SENSOR *);
    /* 0x050 */ void (*pfnPostAloLoad)(SENSOR *);
    /* 0x054 */ void (*pfnUpdateSensor)(SENSOR *);
    /* 0x058 */ void (*pfnUpdateSoXfWorld)(SENSOR *);
    /* 0x05c */ void (*pfnUpdateSoXfWorldHierarchy)(SENSOR *);
    /* 0x060 */ void (*pfnFreezeSo)(SENSOR *);
    /* 0x064 */ void (*pfnSetSoParent)(SENSOR *);
    /* 0x068 */ void (*pfnApplySoProxy)(SENSOR *);
    /* 0x06c */ void (*pfnSubscribeLoObject)(SENSOR *);
    /* 0x070 */ void (*pfnUnsubscribeLoObject)(SENSOR *);
    /* 0x074 */ void (*pfnSubscribeLoStruct)(SENSOR *);
    /* 0x078 */ void (*pfnUnsubscribeLoStruct)(SENSOR *);
    /* 0x07c */ void (*pfnProjectSoTransform)(SENSOR *);
    /* 0x080 */ void (*pfnPresetSoAccel)(SENSOR *);
    /* 0x084 */ void (*pfnTranslateSoToPos)(SENSOR *);
    /* 0x088 */ void (*pfnRotateSoToMat)(SENSOR *);
    /* 0x08c */ void (*pfnMatchAloOtherObject)(SENSOR *);
    /* 0x090 */ void (*pfnSetSoVelocityVec)(SENSOR *);
    /* 0x094 */ void (*pfnSetSoAngularVelocityVec)(SENSOR *);
    /* 0x098 */ void (*pfnPredictAloPosition)(SENSOR *);
    /* 0x09c */ void (*pfnPredictAloRotation)(SENSOR *);
    /* 0x0a0 */ void (*pfnRenderAloAll)(SENSOR *);
    /* 0x0a4 */ void (*pfnRenderSoSelf)(SENSOR *);
    /* 0x0a8 */ void (*pfnRenderAloGlobset)(SENSOR *);
    /* 0x0ac */ void (*pfnUpdateAloInfluences)(SENSOR *);
    /* 0x0b0 */ void (*pfnAdjustAloPosition)(SENSOR *);
    /* 0x0b4 */ void (*pfnAdjustAloRotation)(SENSOR *);
    /* 0x0b8 */ void (*pfnUnadjustAloRotation)(SENSOR *);
    /* 0x0bc */ void (*pfnRecacheAloActList)(SENSOR *);
    /* 0x0c0 */ void (*pfnUpdateAloConstraints)(SENSOR *);
    /* 0x0c4 */ void (*pfnFAbsorbSoWkr)(SENSOR *);
    /* 0x0c8 */ void (*pfnUnk_0x0c8)(SENSOR *);
    /* 0x0cc */ void (*pfnDisplaceSo)(SENSOR *);
    /* 0x0d0 */ void (*pfnImpactSo)(SENSOR *);
    /* 0x0d4 */ void (*pfnPivotSo)(SENSOR *);
    /* 0x0d8 */ void (*pfnUpdateSoBounds)(SENSOR *);
    /* 0x0dc */ void (*pfnAddSoExternalAccelerations)(SENSOR *);
    /* 0x0e0 */ void (*pfnCloneSoPhys)(SENSOR *);
    /* 0x0e4 */ void (*pfnRenumberSo)(SENSOR *);
    /* 0x0e8 */ void (*pfnPropagateSoForce)(SENSOR *);
    /* 0x0ec */ void (*pfnDistributeSoEffects)(SENSOR *);
    /* 0x0f0 */ void (*pfnFIgnoreSoIntersection)(SENSOR *);
    /* 0x0f4 */ void (*pfnAddSoXps)(SENSOR *);
    /* 0x0f8 */ void (*pfnAddSoCustomXps)(SENSOR *);
    /* 0x0fc */ void (*pfnAdjustSoXpLocal)(SENSOR *);
    /* 0x100 */ void (*pfnAdjustSoNewXp)(SENSOR *);
    /* 0x104 */ void (*pfnAdjustSoXpVelocity)(SENSOR *);
    /* 0x108 */ void (*pfnAdjustSoDz)(SENSOR *);
    /* 0x10c */ void (*pfnAdjustSoXps)(SENSOR *);
    /* 0x110 */ void (*pfnUpdateSoInternalXps)(SENSOR *);
    /* 0x114 */ void (*pfnNotifySoImpact)(SENSOR *);
    /* 0x118 */ void (*pfnUpdateSoPivots)(SENSOR *);
    /* 0x11c */ void (*pfnUpdateSoImpacts)(SENSOR *);
    /* 0x120 */ void (*pfnUpdateSoPosWorldPrev)(SENSOR *);
    /* 0x124 */ void (*pfnGetSoCpdefi)(SENSOR *);
    /* 0x128 */ void (*pfnAddSoWaterAcceleration)(SENSOR *);
    /* 0x12c */ void (*pfnFInflictSoZap)(SENSOR *);
    /* 0x130 */ void (*pfnSenseSensor)(SENSOR *);
    /* 0x134 */ void (*pfnEnableSensor)(SENSOR *);
    /* 0x138 */ void (*pfnDisableSensor)(SENSOR *);
    /* 0x13c */ void (*pfnOnSensorAlarmTriggered)(SENSOR *);
    /* 0x140 */ void (*pfnSetSensorAlarm)(SENSOR *);
    /* 0x144 */ void (*pfnSetSensorSensors)(SENSOR *);
};

/**
 * @brief VT for LASEN objects.
 * @todo Add parameters.
 */
struct VTLASEN : VT
{
    /* 0x010 */ void (*pfnInitLasen)(LASEN *);
    /* 0x014 */ void (*pfnSetLoDefaults)(LASEN *);
    /* 0x018 */ void (*pfnAddLo)(LASEN *);
    /* 0x01c */ void (*pfnRemoveLo)(LASEN *);
    /* 0x020 */ void (*pfnAddAloHierarchy)(LASEN *);
    /* 0x024 */ void (*pfnRemoveAloHierarchy)(LASEN *);
    /* 0x028 */ void (*pfnOnSoAdd)(LASEN *);
    /* 0x02c */ void (*pfnOnSoRemove)(LASEN *);
    /* 0x030 */ void (*pfnCloneAloHierarchy)(LASEN *);
    /* 0x034 */ void (*pfnCloneSo)(LASEN *);
    /* 0x038 */ void (*pfnLoadLasenFromBrx)(LASEN *);
    /* 0x03c */ void (*pfnAddLoRecursive)(LASEN *);
    /* 0x040 */ void (*pfnRemoveLoRecursive)(LASEN *);
    /* 0x044 */ void (*pfnHandleAloMessage)(LASEN *);
    /* 0x048 */ void (*pfnSendSoMessage)(LASEN *);
    /* 0x04c */ void (*pfnBindLasen)(LASEN *);
    /* 0x050 */ void (*pfnPostLasenLoad)(LASEN *);
    /* 0x054 */ void (*pfnUpdateLasen)(LASEN *);
    /* 0x058 */ void (*pfnUpdateSoXfWorld)(LASEN *);
    /* 0x05c */ void (*pfnUpdateSoXfWorldHierarchy)(LASEN *);
    /* 0x060 */ void (*pfnFreezeLasen)(LASEN *);
    /* 0x064 */ void (*pfnSetSoParent)(LASEN *);
    /* 0x068 */ void (*pfnApplySoProxy)(LASEN *);
    /* 0x06c */ void (*pfnSubscribeLoObject)(LASEN *);
    /* 0x070 */ void (*pfnUnsubscribeLoObject)(LASEN *);
    /* 0x074 */ void (*pfnSubscribeLoStruct)(LASEN *);
    /* 0x078 */ void (*pfnUnsubscribeLoStruct)(LASEN *);
    /* 0x07c */ void (*pfnProjectSoTransform)(LASEN *);
    /* 0x080 */ void (*pfnPresetSoAccel)(LASEN *);
    /* 0x084 */ void (*pfnTranslateSoToPos)(LASEN *);
    /* 0x088 */ void (*pfnRotateSoToMat)(LASEN *);
    /* 0x08c */ void (*pfnMatchAloOtherObject)(LASEN *);
    /* 0x090 */ void (*pfnSetSoVelocityVec)(LASEN *);
    /* 0x094 */ void (*pfnSetSoAngularVelocityVec)(LASEN *);
    /* 0x098 */ void (*pfnPredictAloPosition)(LASEN *);
    /* 0x09c */ void (*pfnPredictAloRotation)(LASEN *);
    /* 0x0a0 */ void (*pfnRenderAloAll)(LASEN *);
    /* 0x0a4 */ void (*pfnRenderLasenSelf)(LASEN *);
    /* 0x0a8 */ void (*pfnRenderAloGlobset)(LASEN *);
    /* 0x0ac */ void (*pfnUpdateAloInfluences)(LASEN *);
    /* 0x0b0 */ void (*pfnAdjustAloPosition)(LASEN *);
    /* 0x0b4 */ void (*pfnAdjustAloRotation)(LASEN *);
    /* 0x0b8 */ void (*pfnUnadjustAloRotation)(LASEN *);
    /* 0x0bc */ void (*pfnRecacheAloActList)(LASEN *);
    /* 0x0c0 */ void (*pfnUpdateAloConstraints)(LASEN *);
    /* 0x0c4 */ void (*pfnFAbsorbSoWkr)(LASEN *);
    /* 0x0c8 */ void (*pfnUnk_0x0c8)(); // NOTE: Not in the prototype.
    /* 0x0cc */ void (*pfnDisplaceSo)(LASEN *);
    /* 0x0d0 */ void (*pfnImpactSo)(LASEN *);
    /* 0x0d4 */ void (*pfnPivotSo)(LASEN *);
    /* 0x0d8 */ void (*pfnUpdateSoBounds)(LASEN *);
    /* 0x0dc */ void (*pfnAddSoExternalAccelerations)(LASEN *);
    /* 0x0e0 */ void (*pfnCloneSoPhys)(LASEN *);
    /* 0x0e4 */ void (*pfnRenumberSo)(LASEN *);
    /* 0x0e8 */ void (*pfnPropagateSoForce)(LASEN *);
    /* 0x0ec */ void (*pfnDistributeSoEffects)(LASEN *);
    /* 0x0f0 */ void (*pfnFIgnoreSoIntersection)(LASEN *);
    /* 0x0f4 */ void (*pfnAddSoXps)(LASEN *);
    /* 0x0f8 */ void (*pfnAddSoCustomXps)(LASEN *);
    /* 0x0fc */ void (*pfnAdjustSoXpLocal)(LASEN *);
    /* 0x100 */ void (*pfnAdjustSoNewXp)(LASEN *);
    /* 0x104 */ void (*pfnAdjustSoXpVelocity)(LASEN *);
    /* 0x108 */ void (*pfnAdjustSoDz)(LASEN *);
    /* 0x10c */ void (*pfnAdjustSoXps)(LASEN *);
    /* 0x110 */ void (*pfnUpdateSoInternalXps)(LASEN *);
    /* 0x114 */ void (*pfnNotifySoImpact)(LASEN *);
    /* 0x118 */ void (*pfnUpdateSoPivots)(LASEN *);
    /* 0x11c */ void (*pfnUpdateSoImpacts)(LASEN *);
    /* 0x120 */ void (*pfnUpdateSoPosWorldPrev)(LASEN *);
    /* 0x124 */ void (*pfnGetSoCpdefi)(LASEN *);
    /* 0x128 */ void (*pfnAddSoWaterAcceleration)(LASEN *);
    /* 0x12c */ void (*pfnFInflictSoZap)(LASEN *);
    /* 0x130 */ void (*pfnSenseLasen)(LASEN *);
    /* 0x134 */ void (*pfnEnableLasen)(LASEN *);
    /* 0x138 */ void (*pfnDisableLasen)(LASEN *);
    /* 0x13c */ void (*pfnOnLasenAlarmTriggered)(LASEN *);
    /* 0x140 */ void (*pfnSetSensorAlarm)(LASEN *);
    /* 0x144 */ void (*pfnSetLasenSensors)(LASEN *, int);
};

/**
 * @brief VT for CAMSEN objects.
 * @todo Add parameters.
 */
struct VTCAMSEN : VT
{
    /* 0x010 */ void (*pfnInitCamsen)(CAMSEN *);
    /* 0x014 */ void (*pfnSetLoDefaults)(CAMSEN *);
    /* 0x018 */ void (*pfnAddLo)(CAMSEN *);
    /* 0x01c */ void (*pfnRemoveLo)(CAMSEN *);
    /* 0x020 */ void (*pfnAddAloHierarchy)(CAMSEN *);
    /* 0x024 */ void (*pfnRemoveAloHierarchy)(CAMSEN *);
    /* 0x028 */ void (*pfnOnSoAdd)(CAMSEN *);
    /* 0x02c */ void (*pfnOnSoRemove)(CAMSEN *);
    /* 0x030 */ void (*pfnCloneAloHierarchy)(CAMSEN *);
    /* 0x034 */ void (*pfnCloneSo)(CAMSEN *);
    /* 0x038 */ void (*pfnLoadSoFromBrx)(CAMSEN *);
    /* 0x03c */ void (*pfnAddLoRecursive)(CAMSEN *);
    /* 0x040 */ void (*pfnRemoveLoRecursive)(CAMSEN *);
    /* 0x044 */ void (*pfnHandleAloMessage)(CAMSEN *);
    /* 0x048 */ void (*pfnSendSoMessage)(CAMSEN *);
    /* 0x04c */ void (*pfnBindAlo)(CAMSEN *);
    /* 0x050 */ void (*pfnPostCamsenLoad)(CAMSEN *);
    /* 0x054 */ void (*pfnUpdateCamsen)(CAMSEN *);
    /* 0x058 */ void (*pfnUpdateSoXfWorld)(CAMSEN *);
    /* 0x05c */ void (*pfnUpdateSoXfWorldHierarchy)(CAMSEN *);
    /* 0x060 */ void (*pfnFreezeSo)(CAMSEN *);
    /* 0x064 */ void (*pfnSetSoParent)(CAMSEN *);
    /* 0x068 */ void (*pfnApplySoProxy)(CAMSEN *);
    /* 0x06c */ void (*pfnSubscribeLoObject)(CAMSEN *);
    /* 0x070 */ void (*pfnUnsubscribeLoObject)(CAMSEN *);
    /* 0x074 */ void (*pfnSubscribeLoStruct)(CAMSEN *);
    /* 0x078 */ void (*pfnUnsubscribeLoStruct)(CAMSEN *);
    /* 0x07c */ void (*pfnProjectSoTransform)(CAMSEN *);
    /* 0x080 */ void (*pfnPresetSoAccel)(CAMSEN *);
    /* 0x084 */ void (*pfnTranslateSoToPos)(CAMSEN *);
    /* 0x088 */ void (*pfnRotateSoToMat)(CAMSEN *);
    /* 0x08c */ void (*pfnMatchAloOtherObject)(CAMSEN *);
    /* 0x090 */ void (*pfnSetSoVelocityVec)(CAMSEN *);
    /* 0x094 */ void (*pfnSetSoAngularVelocityVec)(CAMSEN *);
    /* 0x098 */ void (*pfnPredictAloPosition)(CAMSEN *);
    /* 0x09c */ void (*pfnPredictAloRotation)(CAMSEN *);
    /* 0x0a0 */ void (*pfnRenderAloAll)(CAMSEN *);
    /* 0x0a4 */ void (*pfnRenderCamsenSelf)(CAMSEN *);
    /* 0x0a8 */ void (*pfnRenderAloGlobset)(CAMSEN *);
    /* 0x0ac */ void (*pfnUpdateAloInfluences)(CAMSEN *);
    /* 0x0b0 */ void (*pfnAdjustAloPosition)(CAMSEN *);
    /* 0x0b4 */ void (*pfnAdjustAloRotation)(CAMSEN *);
    /* 0x0b8 */ void (*pfnUnadjustAloRotation)(CAMSEN *);
    /* 0x0bc */ void (*pfnRecacheAloActList)(CAMSEN *);
    /* 0x0c0 */ void (*pfnUpdateAloConstraints)(CAMSEN *);
    /* 0x0c4 */ void (*pfnFAbsorbSoWkr)(CAMSEN *);
    /* 0x0c8 */ void (*pfnUnk_0x0c8)(CAMSEN *); // NOTE: Not in the prototype.
    /* 0x0cc */ void (*pfnDisplaceSo)(CAMSEN *);
    /* 0x0d0 */ void (*pfnImpactSo)(CAMSEN *);
    /* 0x0d4 */ void (*pfnPivotSo)(CAMSEN *);
    /* 0x0d8 */ void (*pfnUpdateSoBounds)(CAMSEN *);
    /* 0x0dc */ void (*pfnAddSoExternalAccelerations)(CAMSEN *);
    /* 0x0e0 */ void (*pfnCloneSoPhys)(CAMSEN *);
    /* 0x0e4 */ void (*pfnRenumberSo)(CAMSEN *);
    /* 0x0e8 */ void (*pfnPropagateSoForce)(CAMSEN *);
    /* 0x0ec */ void (*pfnDistributeSoEffects)(CAMSEN *);
    /* 0x0f0 */ void (*pfnFIgnoreCamsenIntersection)(CAMSEN *);
    /* 0x0f4 */ void (*pfnAddSoXps)(CAMSEN *);
    /* 0x0f8 */ void (*pfnAddSoCustomXps)(CAMSEN *);
    /* 0x0fc */ void (*pfnAdjustSoXpLocal)(CAMSEN *);
    /* 0x100 */ void (*pfnAdjustSoNewXp)(CAMSEN *);
    /* 0x104 */ void (*pfnAdjustSoXpVelocity)(CAMSEN *);
    /* 0x108 */ void (*pfnAdjustSoDz)(CAMSEN *);
    /* 0x10c */ void (*pfnAdjustSoXps)(CAMSEN *);
    /* 0x110 */ void (*pfnUpdateSoInternalXps)(CAMSEN *);
    /* 0x114 */ void (*pfnNotifySoImpact)(CAMSEN *);
    /* 0x118 */ void (*pfnUpdateSoPivots)(CAMSEN *);
    /* 0x11c */ void (*pfnUpdateSoImpacts)(CAMSEN *);
    /* 0x120 */ void (*pfnUpdateSoPosWorldPrev)(CAMSEN *);
    /* 0x124 */ void (*pfnGetSoCpdefi)(CAMSEN *);
    /* 0x128 */ void (*pfnAddSoWaterAcceleration)(CAMSEN *);
    /* 0x12c */ void (*pfnFInflictSoZap)(CAMSEN *);
    /* 0x130 */ void (*pfnSenseCamsen)(CAMSEN *);
    /* 0x134 */ void (*pfnEnableCamsen)(CAMSEN *);
    /* 0x138 */ void (*pfnDisableCamsen)(CAMSEN *);
    /* 0x13c */ void (*pfnOnCamsenAlarmTriggered)(CAMSEN *);
    /* 0x140 */ void (*pfnSetSensorAlarm)(CAMSEN *);
    /* 0x144 */ void (*pfnSetCamsenSensors)(CAMSEN *, int);
};

/**
 * @brief VT for PRSEN objects.
 * @todo Add parameters.
 */
struct VTPRSEN : VT
{
    /* 0x010 */ void (*pfnInitPrsen)(PRSEN *);
    /* 0x014 */ void (*pfnSetLoDefaults)(PRSEN *);
    /* 0x018 */ void (*pfnAddLo)(PRSEN *);
    /* 0x01c */ void (*pfnRemoveLo)(PRSEN *);
    /* 0x020 */ void (*pfnAddAloHierarchy)(PRSEN *);
    /* 0x024 */ void (*pfnRemoveAloHierarchy)(PRSEN *);
    /* 0x028 */ void (*pfnOnSoAdd)(PRSEN *);
    /* 0x02c */ void (*pfnOnSoRemove)(PRSEN *);
    /* 0x030 */ void (*pfnCloneAloHierarchy)(PRSEN *);
    /* 0x034 */ void (*pfnCloneSo)(PRSEN *);
    /* 0x038 */ void (*pfnLoadSoFromBrx)(PRSEN *);
    /* 0x03c */ void (*pfnAddLoRecursive)(PRSEN *);
    /* 0x040 */ void (*pfnRemoveLoRecursive)(PRSEN *);
    /* 0x044 */ void (*pfnHandleAloMessage)(PRSEN *);
    /* 0x048 */ void (*pfnSendSoMessage)(PRSEN *);
    /* 0x04c */ void (*pfnBindAlo)(PRSEN *);
    /* 0x050 */ void (*pfnPostPrsenLoad)(PRSEN *);
    /* 0x054 */ void (*pfnUpdatePrsen)(PRSEN *);
    /* 0x058 */ void (*pfnUpdateSoXfWorld)(PRSEN *);
    /* 0x05c */ void (*pfnUpdateSoXfWorldHierarchy)(PRSEN *);
    /* 0x060 */ void (*pfnFreezeSo)(PRSEN *);
    /* 0x064 */ void (*pfnSetSoParent)(PRSEN *);
    /* 0x068 */ void (*pfnApplySoProxy)(PRSEN *);
    /* 0x06c */ void (*pfnSubscribeLoObject)(PRSEN *);
    /* 0x070 */ void (*pfnUnsubscribeLoObject)(PRSEN *);
    /* 0x074 */ void (*pfnSubscribeLoStruct)(PRSEN *);
    /* 0x078 */ void (*pfnUnsubscribeLoStruct)(PRSEN *);
    /* 0x07c */ void (*pfnProjectSoTransform)(PRSEN *);
    /* 0x080 */ void (*pfnPresetSoAccel)(PRSEN *);
    /* 0x084 */ void (*pfnTranslateSoToPos)(PRSEN *);
    /* 0x088 */ void (*pfnRotateSoToMat)(PRSEN *);
    /* 0x08c */ void (*pfnMatchAloOtherObject)(PRSEN *);
    /* 0x090 */ void (*pfnSetSoVelocityVec)(PRSEN *);
    /* 0x094 */ void (*pfnSetSoAngularVelocityVec)(PRSEN *);
    /* 0x098 */ void (*pfnPredictAloPosition)(PRSEN *);
    /* 0x09c */ void (*pfnPredictAloRotation)(PRSEN *);
    /* 0x0a0 */ void (*pfnRenderAloAll)(PRSEN *);
    /* 0x0a4 */ void (*pfnRenderSoSelf)(PRSEN *);
    /* 0x0a8 */ void (*pfnRenderAloGlobset)(PRSEN *);
    /* 0x0ac */ void (*pfnUpdateAloInfluences)(PRSEN *);
    /* 0x0b0 */ void (*pfnAdjustAloPosition)(PRSEN *);
    /* 0x0b4 */ void (*pfnAdjustAloRotation)(PRSEN *);
    /* 0x0b8 */ void (*pfnUnadjustAloRotation)(PRSEN *);
    /* 0x0bc */ void (*pfnRecacheAloActList)(PRSEN *);
    /* 0x0c0 */ void (*pfnUpdateAloConstraints)(PRSEN *);
    /* 0x0c4 */ void (*pfnFAbsorbSoWkr)(PRSEN *);
    /* 0x0c8 */ void (*pfnUnk_0x0c8)(PRSEN *);
    /* 0x0cc */ void (*pfnDisplaceSo)(PRSEN *);
    /* 0x0d0 */ void (*pfnImpactSo)(PRSEN *);
    /* 0x0d4 */ void (*pfnPivotSo)(PRSEN *);
    /* 0x0d8 */ void (*pfnUpdateSoBounds)(PRSEN *);
    /* 0x0dc */ void (*pfnAddSoExternalAccelerations)(PRSEN *);
    /* 0x0e0 */ void (*pfnCloneSoPhys)(PRSEN *);
    /* 0x0e4 */ void (*pfnRenumberSo)(PRSEN *);
    /* 0x0e8 */ void (*pfnPropagateSoForce)(PRSEN *);
    /* 0x0ec */ void (*pfnDistributeSoEffects)(PRSEN *);
    /* 0x0f0 */ void (*pfnFIgnoreSoIntersection)(PRSEN *);
    /* 0x0f4 */ void (*pfnAddSoXps)(PRSEN *);
    /* 0x0f8 */ void (*pfnAddSoCustomXps)(PRSEN *);
    /* 0x0fc */ void (*pfnAdjustSoXpLocal)(PRSEN *);
    /* 0x100 */ void (*pfnAdjustSoNewXp)(PRSEN *);
    /* 0x104 */ void (*pfnAdjustSoXpVelocity)(PRSEN *);
    /* 0x108 */ void (*pfnAdjustSoDz)(PRSEN *);
    /* 0x10c */ void (*pfnAdjustSoXps)(PRSEN *);
    /* 0x110 */ void (*pfnUpdateSoInternalXps)(PRSEN *);
    /* 0x114 */ void (*pfnNotifySoImpact)(PRSEN *);
    /* 0x118 */ void (*pfnUpdateSoPivots)(PRSEN *);
    /* 0x11c */ void (*pfnUpdateSoImpacts)(PRSEN *);
    /* 0x120 */ void (*pfnUpdateSoPosWorldPrev)(PRSEN *);
    /* 0x124 */ void (*pfnGetSoCpdefi)(PRSEN *);
    /* 0x128 */ void (*pfnAddSoWaterAcceleration)(PRSEN *);
    /* 0x12c */ void (*pfnFInflictSoZap)(PRSEN *);
    /* 0x130 */ void (*pfnSensePrsen)(PRSEN *);
    /* 0x134 */ void (*pfnEnablePrsen)(PRSEN *);
    /* 0x138 */ void (*pfnDisablePrsen)(PRSEN *);
    /* 0x13c */ void (*pfnOnPrsenAlarmTriggered)(PRSEN *);
    /* 0x140 */ void (*pfnSetSensorAlarm)(PRSEN *);
    /* 0x144 */ void (*pfnSetPrsenSensors)(PRSEN *, int);
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
