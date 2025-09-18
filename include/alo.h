/**
 * @file alo.h
 */
#ifndef ALO_H
#define ALO_H

#include "common.h"
#include <sound.h>
#include <vec.h>
#include <mat.h>
#include <lo.h>
#include <dl.h>

// Forward
struct CBinaryInputStream;
struct SFX;
struct SMPA;
struct MRG;
struct ASEGA;
struct ASEGD;
struct ACT;
struct ACTLY;
struct ACTSEG;
struct ACTADJ;
struct ACTBANK;
struct IKH;
struct ALOX;
struct SHADOW;
struct THROB;
struct POSEC;
struct ACTREF;
struct FADER;
struct PROXY;
struct RO;
struct CM;
struct SMA;
struct TARGET;

typedef int GRFIC;
typedef int GRFTAK;

/**
 * @todo Unknown.
 */
enum ACK
{
    ACK_Nil = -1,
    ACK_None = 0,
    ACK_Spring = 1,
    ACK_Velocity = 2,
    ACK_Smooth = 3,
    ACK_Spline = 4,
    ACK_Drive = 5,
    ACK_SmoothForce = 6,
    ACK_SmoothLock = 7,
    ACK_SpringLock = 8,
    ACK_SmoothNoLock = 9,
    ACK_Max = 10
};

/**
 * @brief Unknown.
 */
enum RTCK
{
    RTCK_Nil = -1,
    RTCK_None = 0,
    RTCK_All = 1,
    RTCK_WorldZ = 2,
    RTCK_LocalX = 3,
    RTCK_LocalY = 4,
    RTCK_LocalZ = 5,
    RTCK_Max = 6
};

/**
 * @brief Unknown.
 */
enum THROBK
{
    THROBK_Nil = -1,
    THROBK_Pipe = 0,
    THROBK_Ninja = 1,
    THROBK_Rail = 2,
    THROBK_Hide = 3,
    THROBK_Foo = 4,
    THROBK_Bar = 5,
    THROBK_Max = 6
};

/**
 * @brief Unknown.
 */
struct THROB
{
    /* 0x00 */ THROBK throbk;
    /* 0x04 */ STRUCT_PADDING(11);
    /* 0x30 */ float dtInOut;
};

/**
 * @brief Unknown.
 */
struct WKR
{
    LO *ploSource;
    LO *ploTarget;
    float sftMax;
    /* 0x0c */ GRFIC grfic;
    GRFTAK grftak;
    float gSort;
};

/**
 * @todo Unknown.
 */
struct FICG
{
    uchar grficSweep;
    uchar grficRush;
    uchar grficSmash;
    uchar grficBomb;
    uchar grficShock;
};

/**
 * @todo Unknown.
*/
struct SNIP
{
    int grfsnip;
    OID oid;
    int ib;
};

/**
 * @brief Transform.
 */
struct XF
{
    MATRIX3 mat;
    VECTOR pos;
    MATRIX3 matWorld;
    VECTOR posWorld;
    VECTOR v;
    VECTOR w;
    VECTOR dv;
    VECTOR dw;
};

/**
 * @class LIGHTWEIGHT
 * @brief Unknown, probably used for instancing LOs.
 *
 * @todo Finish implementing struct.
 */
struct ALO : public LO
{
    /* 0x34 */ DL dlChild;
    DLE dleBusy;
    DLE dleMRD;
    ALO *paloRoot;
    ALO *paloFreezeRoot;
    DLE dleFreeze;
    DL dlFreeze;
    int cpmrg;
    MRG *apmrg;
    float sMRD;
    float sCelBorderMRD;
    int grfzon;
    float dsMRDSnap;
    undefined4 unk_0x9c;
    STRUCT_PADDING(10); // int frz[10];
    XF xf;
    VECTOR posOrig;
    MATRIX3 matOrig;
    VECTOR eulOrig;
    DL dlAct;
    ACT *pactPos;
    ACT *pactRot;
    ACT *pactScale;
    ACT **apactPost;
    ACT *pactRestore;
    ACTLY *pactla;
    ACTBANK *pactbank;
    IKH *pikh;
    CLQ *pclqPosSpring;
    CLQ *pclwPosDamping;
    CLQ *pclqRotSpring;
    CLQ *pclqRotDamping;
    SMPA *psmpaPos;
    SMPA *psmapaRot;
    ALOX *palox;
    /* 0x228 */ int cframeStatic;
    STRUCT_PADDING(22); // GLOBSET globset;
    /* 0x284 */ SHADOW *pshadow;
    /* 0x288 */ THROB *pthrob;
    /* 0x28c */ float sFastShadowRadius;
    /* 0x290 */ float sFastShadowDepth;
    int fRealClock;
    FADER *pfader;
    float dtUpdatePause;
    ASEGD *pasegd;
    float sRadiusRenderSelf;
    float sRadiusRenderAll;
    /* 0x2ac */ SFX *psfx;
    STRUCT_PADDING(25);
    FICG ficg;
    STRUCT_PADDING(1); // ???
    int cposed;
    POSEC *aposec;
    ACTREF *pactrefCombo;
    DLR *pdlrFirst;
    // ???
    ACK ackRot;
    // ???
    // ...
};

int FIsZeroV(VECTOR *pv);

int FIsZeroW(VECTOR *pw);

int FIsZeroDv(VECTOR *pdv);

int FIsZeroDw(VECTOR *pdw);

/**
 * @brief Initializes an ALO.
 *
 * @param palo ALO to initialize.
 */
void InitAlo(ALO *palo);

void AddAloHierarchy(ALO *palo);

/**
 * @brief Adds an ALO.
 *
 * @param palo ALO to add.
 */
void OnAloAdd(ALO *palo);

void RemoveAloHierarchy(ALO *palo);

/**
 * @brief Removes an ALO.
 *
 * @param palo ALO to remove.
 */
void OnAloRemove(ALO *palo);

void UpdateAloOrig(ALO *palo);

void SetAloParent(ALO *palo, ALO *paloParent);

void ApplyAloProxy(ALO *palo, PROXY *pproxyApply);

void BindAlo(ALO *palo);

void PostAloLoad(ALO *palo);

void PostAloLoadCallback(ALO *palo, MSGID msgid, void *pvData);

void SnipAloObjects(ALO *palo, int csnip, SNIP *asnip);

void UpdateAloHierarchy(ALO *palo, float dt);

/**
 * @brief Updates an ALO.
 *
 * @param palo ALO to initialize
 */
void UpdateAlo(ALO *palo, float dt);

void InvalidateAloLighting(ALO *palo);

void UpdateAloXfWorld__FP3ALO(ALO * palo);

void UpdateAloXfWorldHierarchy(ALO *palo);

void PresetAloAccel(ALO *palo, float dt);

void ProjectAloTransform(ALO *palo, float dt, int fParentDirty);

void PredictAloTransform(ALO *paloLeaf, ALO *paloBasis, float dtOffset, VECTOR *ppos, MATRIX3 *pmat, VECTOR *pv, VECTOR *pw);

void PredictAloTransformAdjust(ALO *paloLeaf, ALO *paloBasis, float dtOffset, VECTOR *ppos, MATRIX3 *pmat, VECTOR *pv, VECTOR *pw);

void DupAloRo(ALO *palo, RO *proOrig, RO *proDup);

void RenderFastShadow(ALO *palo, CM *pcm, RO *pro);

void RenderAloAll(ALO *palo, CM *pcm, RO *pro);

void RenderAloSelf(ALO *palo, CM *pcm, RO *pro);

void RenderAloGlobset(ALO *palo, CM *pcm, RO *pro);

void RenderAloLine(ALO *palo, CM *pcm, VECTOR *ppos0, VECTOR *ppos1, float rWidth, float uAlpha);

void SetAloOverrideCel(ALO *palo, RGBA *rgba);

void UpdateAloThrob(ALO *palo, float dt);

void SetAloBlotContext(ALO *palo, BLOT *pblot);

void EnsureAloFader(ALO *palo);

/**
 * @brief Fades in an ALO.
 *
 * @param palo ALO to fade in.
 * @param dtFade Time to fade in over.
 */
void FadeAloIn(ALO *palo, float dtFade);

/**
 * @brief Fades out an ALO.
 *
 * @param palo ALO to fade out.
 * @param dtFade Time to fade out over.
 */
void FadeAloOut(ALO *palo, float dtFade);

void AdjustAloRtckMat(ALO *palo, CM *pcm, RTCK rtck, VECTOR *pposCenter, MATRIX4 *pmat);

void CloneAloHierarchy(ALO *palo, ALO *paloBase);

/**
 * @brief Clones an ALO.
 *
 * @param palo ALO to clone to.
 * @param paloBase Base ALO to clone from.
 */
void CloneAlo(ALO *palo, ALO *paloBase);

void HandleAloMessage(ALO *palo, MSGID msgid, void *pv);

void TranslateAloToPos(ALO *palo, VECTOR *ppos);

void RotateAloToMat(ALO *palo, MATRIX3 *pmat);

void SetAloVelocityVec(ALO *palo, VECTOR *pv);

void SetAloVelocityXYZ(ALO *palo, float x, float y, float z);

void SetAloAngularVelocityVec(ALO *palo, VECTOR *pw);

void SetAloAngularVelocityXYZ(ALO *palo, float x, float y, float z);

void SetAloVelocityLocal(ALO *palo, VECTOR *pvec);

void GetAloVelocityLocal(ALO *palo, VECTOR *pvec);

void MatchAloOtherObject(ALO *palo, ALO *paloOther);

void CalculateAloMovement(ALO *paloLeaf, ALO *paloBasis, VECTOR *ppos, VECTOR *pv, VECTOR *pw, VECTOR *pdv, VECTOR *pdw);

void CalculateAloTransform(ALO *paloLeaf, ALO *paloBasis, int cpaloPredict, VECTOR *apos, MATRIX3 *amat, VECTOR *av, VECTOR *aw);

void CalculateAloTransformAdjust(ALO *paloLeaf, ALO *paloBasis, VECTOR *ppos, MATRIX3 *pmat, VECTOR *pv, VECTOR *pw);

void ConvertAloPos(ALO *paloFrom, ALO *paloTo, VECTOR *pposFrom, VECTOR *pposTo);

void ConvertAloVec(ALO *paloFrom, ALO *paloTo, VECTOR *pvecFrom, VECTOR *pvecTo);

void ConvertAloMat(ALO *paloFrom, ALO *paloTo, MATRIX3 *pmatFrom, MATRIX3 *pmatTo);

int FDrivenAlo(ALO *palo);

void RetractAloDrive(ALO *palo);

void ConvertAloMovement(ALO *paloFrom, ALO *paloTo, VECTOR *ppos, VECTOR *pvFrom, VECTOR *pwFrom, VECTOR *pdvFrom, VECTOR *pdwFrom, VECTOR *pvTo, VECTOR *pwTo, VECTOR *pdvTo, VECTOR *pdwTo);

void CalculateAloDrive(ALO *palo, CLQ *pclqHoming, LM *plmHoming, float dt, float radPanCur, float *pradPanTarget, float *pradTiltTarget, float *psvTarget);

int FGetAloChildrenList(ALO *palo, void *pvstate);

ACTSEG *PactsegNewAlo(ALO *palo);

/**
 * @brief Loads an ALO from a BRX file.
 *
 * @param palo ALO to load into.
 * @param pbis Binary input stream to read from.
 */
void LoadAloFromBrx(ALO *palo, CBinaryInputStream *pbis);

void LoadAloAloxFromBrx(ALO *palo, CBinaryInputStream *pbis);

void BindAloAlox(ALO *palo);

void AdjustAloRotation(ALO *palo, MATRIX3 *pmat, VECTOR *pw);

void UnadjustAloRotation(ALO *palo, MATRIX3 *pmat);

void SetAloInitialVelocity(ALO *palo, VECTOR *pv);

void SetAloInitialAngularVelocity(ALO *palo, VECTOR *pw);

ASEGD *PasegdEnsureAlo(ALO *palo);

void SetAloFastShadowRadius(ALO *palo, float sRadius);

void GetAloFastShadowRadius(ALO *palo, float *psRadius);

void SetAloFastShadowDepth(ALO *palo, float sDepth);

void GetAloFastShadowDepth(ALO *palo, float *psDepth);

SHADOW *PshadowAloEnsure(ALO *palo);

void SetAloCastShadow(ALO *palo, int fCastShadow);

void SetAloShadowShader(ALO *palo, OID oidShdShadow);

void SetAloShadowNearRadius(ALO *palo, float sNearRadius);

void SetAloShadowFarRadius(ALO *palo, float sFarRadius);

void SetAloShadowNearCast(ALO *palo, float sNearCast);

void SetAloShadowFarCast(ALO *palo, float sFarCast);

void SetAloShadowConeAngle(ALO *palo, float degConeAngle);

void SetAloShadowFrustrumUp(ALO *palo, VECTOR *pvecUp);

void SetAloDynamicShadowObject(ALO *palo, OID oidDysh);

SHADOW *PshadowInferAlo(ALO *palo);

void GetAloCastShadow(ALO *palo, int *pfCastShadow);

void GetAloShadowShader(ALO *palo, OID *poidShdShadow);

void GetAloShadowNearRadius(ALO *palo, float *psNearRadius);

void GetAloShadowFarRadius(ALO *palo, float *psFarRadius);

void GetAloShadowNearCast(ALO *palo, float *psNearCast);

void GetAloShadowFarCast(ALO *palo, float *psFarCast);

void GetAloShadowConeAngle(ALO *palo, float *pdegConeAngle);

void GetAloShadowFrustrumUp(ALO *palo, VECTOR *pvecUp);

void GetAloEuler(ALO *palo, VECTOR *peul);

void SetAloEuler(ALO *palo, VECTOR *peul);

void EnsureAloActRestore(ALO *palo);

void EnsureAloActla(ALO *palo);

void RecacheAloActList(ALO *palo);

void InsertAloAct(ALO *palo, ACT *pact);

void ResortAloActList(ALO *palo);

ASEGA *PasegaFindAlo(ALO *palo, OID oidAseg);

SMA *PsmaFindAlo(ALO *palo, OID oidSm);

ASEGA *PasegaFindAloNearest(ALO *paloLeaf);

void CreateAloActadj(ALO *palo, int nPriority, ACTADJ **ppactadj);

int FIsAloStatic(ALO *palo);

void ResolveAlo(ALO *palo);

void SetAloPositionSpring(ALO *palo, float r);

void SetAloPositionSpringDetail(ALO *palo, CLQ *pclq);

void SetAloPositionDamping(ALO *palo, float r);

void SetAloPositionDampingDetail(ALO *palo, CLQ *pclq);

void SetAloRotationSpring(ALO *palo, float r);

void SetAloRotationSpringDetail(ALO *palo, CLQ *pclq);

void SetAloRotationDamping(ALO *palo, float r);

void SetAloRotationDampingDetail(ALO *palo, CLQ *pclq);

void SetAloPositionSmooth(ALO *palo, float r);

void SetAloPositionSmoothMaxAccel(ALO *palo, float r);

void SetAloPositionSmoothDetail(ALO *palo, SMPA *psmpa);

void SetAloRotationSmooth(ALO *palo, float r);

void SetAloRotationSmoothMaxAccel(ALO *palo, float r);

void SetAloRotationSmoothDetail(ALO *palo, SMPA *psmpa);

void SetAloDefaultAckPos(ALO *palo, ACK ack);

void SetAloDefaultAckRot(ALO *palo, ACK ack);

void SetAloRestorePosition(ALO *palo, int fRestore);

void SetAloNoFreeze(ALO *palo, int fNoFreeze);

void SetAloRestorePositionAck(ALO *palo, ACK ack);

void SetAloRestoreRotation(ALO *palo, int fRestore);

void SetAloRestoreRotationAck(ALO *palo, ACK ack);

void SetAloLookAt(ALO *palo, ACK ack);

void SetAloLookAtIgnore(ALO *palo, float sIgnore);

void GetAloLookAtIgnore(ALO *palo, float *psIgnore);

void SetAloLookAtPanFunction(ALO *palo, CLQ *pclq);

void GetAloLookAtPanFunction(ALO *palo, CLQ *pclq);

void SetAloLookAtPanLimits(ALO *palo, LM *plm);

void GetAloLookAtPanLimits(ALO *palo, LM *plm);

void SetAloLookAtTiltFunction(ALO *palo, CLQ *pclq);

void GetAloLookAtTiltFunction(ALO *palo, CLQ *pclq);

void SetAloLookAtTiltLimits(ALO *palo, LM *plm);

void GetAloLookAtTiltLimits(ALO *palo, LM *plm);

void SetAloLookAtEnabledPriority(ALO *palo, int nPriority);

void GetAloLookAtEnabledPriority(ALO *palo, int *pnPriority);

void SetAloLookAtDisabledPriority(ALO *palo, int nPriority);

void GetAloLookAtDisabledPriority(ALO *palo, int *pnPriority);

void SetAloRotationMatchesVelocity(ALO *palo, float uBank, float dtPredict, ACK ackRot);

TARGET *PtargetEnsureAlo(ALO *palo);

void SetAloTargetAttacks(ALO *palo, GRFTAK grftak);

void SetAloTargetRadius(ALO *palo, float sRadiusTarget);

void SetAloTargetHitTest(ALO *palo, int fHitTest);

void SetAloScrollingMasterSpeeds(ALO *palo, float svu, float svv);

void SetAloEyesClosed(ALO *palo, float uClosed);

void EnsureAloSfx(ALO *palo);

void SetAloSfxid(ALO *palo, SFXID sfxid);

void SetAloSfxidSpl(ALO *palo, SFXID sfxid);

void GetAloSfxid(ALO *palo, SFXID *psfxid);

void SetAloSStart(ALO *palo, float sStart);

void GetAloSStart(ALO *palo, float *psStart);

void SetAloSFull(ALO *palo, float sFull);

void SetAloSndRepeat(ALO *palo, LM *plm);

void GetAloSFull(ALO *palo, float *psFull);

void SetAloUVolume(ALO *palo, float uVol);

void SetAloUDoppler(ALO *palo, float uDoppler);

void GetAloUDoppler(ALO *palo, float *puDoppler);

void SetAloUVolumeSpl(ALO *palo, float uVol);

void GetAloUVolume(ALO *palo, float *puVol);

void SetAloUPitch(ALO *palo, float uPitch);

void SetAloUPitchSpl(ALO *palo, float uPitch);

void GetAloUPitch(ALO *palo, float *puPitch);

void GetAloSndRepeat(ALO *palo, LM *plmRepeat);

void StartAloSound(ALO *palo, SFXID sfxid, float sStart, float sFull, float uVol, LM *plmRepeat);

void StopAloSound(ALO *palo);

void EnsureAloThrob(ALO *palo);

void SetAloThrobKind(ALO *palo, THROBK throbk);

void GetAloThrobKind(ALO *palo, THROBK *pthrobk);

void SetAloThrobInColor(ALO *palo, VECTOR *phsvInColor);

void GetAloThrobInColor(ALO *palo, VECTOR *phsvInColor);

void SetAloThrobOutColor(ALO *palo, VECTOR *phsvOutColor);

void GetAloThrobOutColor(ALO *palo, VECTOR *phsvOutColor);

void SetAloThrobDtInOut(ALO *palo, float dtInOut);

void GetAloThrobDtInOut(ALO *palo, float *pdtInOut);

void SetAloInteractCane(ALO *palo, GRFIC grfic);

void GetAloInteractCane(ALO *palo, GRFIC *pgrfic);

void SetAloInteractCaneSweep(ALO *palo, GRFIC grfic);

void GetAloInteractCaneSweep(ALO *palo, GRFIC *pgrfic);

void SetAloInteractCaneRush(ALO *palo, GRFIC grfic);

void GetAloInteractCaneRush(ALO *palo, GRFIC *pgrfic);

void SetAloInteractCaneSmash(ALO *palo, GRFIC grfic);

void GetAloInteractCaneSmash(ALO *palo, GRFIC *pgrfic);

void SetAloInteractBomb(ALO *palo, GRFIC grfic);

void GetAloInteractBomb(ALO *palo, GRFIC *pgrfic);

void SetAloInteractShock(ALO *palo, GRFIC grfic);

void GetAloInteractShock(ALO *palo, GRFIC *pgrfic);

int FAbsorbAloWkr(ALO *palo, WKR *pwkr);

void SetAloPoseCombo(ALO *palo, OID oidCombo);

void SetAloForceCameraFade(ALO *palo, int fFade);

void SetAloRealClock(ALO *palo, int fRealClock);

#endif // ALO_H
