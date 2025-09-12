/**
 * @file alo.h
 */
#ifndef ALO_H
#define ALO_H

#include "common.h"
#include <vec.h>
#include <mat.h>
#include <lo.h>
#include <dl.h>

// Forward
struct CBinaryInputStream;
struct SFX;
struct SMPA;
struct MRG;
struct ASEGD;
struct ACT;
struct ACTLY;
struct ACTBANK;
struct IKH;
struct ALOX;
struct SHADOW;
struct THROB;
struct POSEC;
struct ACTREF;
struct FADER;

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
    DL dlChild;
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
    PADDING(frz, 10); // int frz[10]; // Freeze-related?
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
    int cframeStatic;
    PADDING(globset, 22); // GLOBSET globset;
    SHADOW *pshadow;
    THROB *pthrob;
    float sFastShadowRadius;
    float sFastShadowDepth;
    int fRealClock;
    FADER *pfader;
    float dtUpdatePause;
    ASEGD *pasegd;
    float sRadiusRenderSelf;
    float sRadiusRenderAll;
    SFX *psfx;
    PADDING(padding2, 25);
    FICG ficg;
    PADDING(padding3, 1); // ???
    int cposed;
    POSEC *aposec;
    ACTREF *pactrefCombo;
    DLR *pdlrFirst;
    // ???
    ACK ackRot;
    // ???
    // ...
};

/**
 * @brief Initializes an ALO.
 *
 * @param palo ALO to initialize
 */
void InitAlo(ALO *palo);

/**
 * @brief unknown
 */
void SnipAloObjects(ALO *palo, int csnip, SNIP *asnip);

/**
 * @brief Updates an ALO.
 *
 * @param palo ALO to initialize
 */
void UpdateAlo(ALO *palo, float dt);

/**
 * @brief Clones an ALO.
 *
 */
void CloneAlo(ALO *palo, ALO *paloBase);

/**
 * Fades in an ALO.
 */
void FadeAloIn(ALO *palo, float dtFade);

/**
 * Fades out an ALO.
 */
void FadeAloOut(ALO *palo, float dtFade);

/**
 * @brief unknown
 */
void LoadAloFromBrx(ALO *palo, CBinaryInputStream *pbis);

/**
 * @brief unknown
 */
void SetAloTargetHitTest(ALO *palo, int fHitTest);

#endif // ALO_H
