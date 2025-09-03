/**
 * @file xform.h
 *
 * @brief Transform.
 */
#ifndef XFORM_H
#define XFORM_H

#include "common.h"
#include <vec.h>
#include <mat.h>
#include <alo.h>
#include <util.h>
#include <dl.h>
#include <geom.h>
#include <game.h>
#include <oid.h>
#include <anim.h>
#include <wipe.h>
#include <bis.h>
#include <proxy.h>
#include <rs.h>

// Forward declarations
struct XF;
struct XFM;
struct EXPL;
struct EXPLG;
struct EXPLO;
struct EXPLS;
struct EXPLSO;
struct EXPLSTE;
struct PNT;
struct CAMERA;

/**
 * @brief Transform (?).
 */
struct XFM : public LO
{
    VECTOR posLocal;
    MATRIX3 matLocal;
};

struct EXPL : public XFM
{
    // ...
};

struct EXPLG : public EXPL
{
    // ...
};

struct EXPLO : public EXPL
{
    // ...
};

struct EXPLS : public EXPLO
{
    // ...
};

struct EXPLSO
{
    // ...
};

struct EXPLSTE
{
    // ...
};

/**
 * @brief Warp.
 */
struct WARP : XFM
{
    WID widMenu;
    undefined4 unk0_0x4;
    undefined4 unk1_0x8;
    undefined4 unk2_0xC;
    VECTOR v;
    int fDefault;
    float radCmInit;
    int cpaseg;
    ASEG **apaseg;
    int coidHide;
    OID *aoidHide;
    int coidShowWhenDifficult;
    OID aoidShowWhenDifficult[4];
    OID oidAlias;
    int crsmg;
    RSMG arsmg[4];
    undefined4 unk3;
    undefined4 unk4;
    undefined4 unk5;
};

/**
 * @brief Point.
 */
struct PNT : public LO
{
    VECTOR posLocal;
};

/**
 * @brief Camera.
 *
 * @note Not the same as the game camera CM. More research needed.
 * Might be in the wrong header.
 */
struct CAMERA : public ALO
{
    OID oidTarget;
    PNT *ppntTarget;
    ALO *paloTarget;
    undefined4 unk_1;
    VECTOR posEye;
    VECTOR vecView;
    VECTOR vecUp;
    int fSetCplcy;
    undefined4 unk_2;
    undefined4 unk_3;
    undefined4 unk_4;
};

enum EXITS
{
    EXITS_Nil = -1,
    EXITS_Blocked = 0,
    EXITS_Unblocked = 1,
    EXITS_Disabled = 2,
    EXITS_Enabled = 3,
    EXITS_Totals = 4,
    EXITS_Exiting = 5,
    EXITS_Max = 6
};

enum EDK
{
    EDK_Nil = -1,
    EDK_DestinationKey = 0,
    EDK_CurrentKey = 1,
    EDK_Max = 2
};

struct EXIT : public ALO
{
    int fDefault;
    EXITS exits;
    EXITS fKeyed;
    float fFollowDefault;
    int fTotals;
    float tExits;
    int ctsurf;
    TSURF *atsurf;
    int ctbsp;
    TBSP *atbsp;
    WID widWarp;
    OID oidWarp;
    EDK edkAlt;
    WID widAlt;
    OID oidAlt;
    int cpaseg;
    ASEG *apaseg;
    WIPEK wipek;
    float tWipe;
    float dtUnblock;
    float dtTriggerWipe;
};

void InitXfm(XFM *pxfm);

void LoadXfmFromBrx(XFM *pxfm, CBinaryInputStream *pbis);

void SetXfmParent(XFM *pxfm, ALO *paloParent);

void ApplyXfmProxy(XFM *pxfm, PROXY *pproxyApply);

void ConvertXfmWorldToLocal(XFM *pxfm, VECTOR *pposWorld, VECTOR *pposLocal);

void GetXfmPos(XFM *xfm, VECTOR *ppos);

void GetXfmMat(XFM *pxfm, MATRIX3 *pmat);

WARP *PwarpFromOid(OID oid, OID oidContext);

void LoadWarpFromBrx(WARP *pwarp, CBinaryInputStream *pbis);

void CloneWarp(WARP *pwarp, WARP *pwarpBase);

void PostWarpLoad(WARP *pwarp);

void TriggerWarp(WARP *pwarp);

void SetWarpRsmg(WARP *pwarp, int fOnTrigger, OID oidRoot, OID oidSM, OID oidGoal);

void TeleportSwPlayer(SW *psw, OID oidWarp, OID oidWarpContext);

EXIT *PexitDefault();

void TriggerDefaultExit(int fInhibitAsegs, WIPEK wipek);

void LoadExitFromBrx(EXIT *pexit, CBinaryInputStream *pbis);

void PostExitLoad(EXIT *pexit);

/**
 * @brief Sets the EXIT state.
 *
 * @param pexit Pointer to the EXIT.
 * @param exits EXIT state.
*/
void SetExitExits(EXIT *pexit, EXITS exits);

void TriggerExit(EXIT *pexit);

void WipeExit(EXIT *pexit);

void UpdateExit(float dt, EXIT *pexit);

void InitCamera(CAMERA *pcamera);

void PostCameraLoad(CAMERA *camera);

void EnableCamera(CAMERA *pcamera);

#endif // XFORM_H
