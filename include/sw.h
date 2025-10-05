/**
 * @file sw.h
 *
 * @brief Scene world?
 */
#ifndef SW_H
#define SW_H

#include "common.h"
#include <slotheap.h>
#include <game.h>
#include <bis.h>
#include <vec.h>
#include <lo.h>
#include <mq.h>
#include <cm.h>

typedef void (*PFNFILTER)(void *, SO *); // TODO: Figure out if this is correct.

// Forward.
struct XA;
struct OXA;
struct STSO;
struct VISMAP;

/**
 * @class WORLD
 *
 * @brief Not fully understood, but everything in the
 * game world is owned by an instance of this struct.
 *
 * @todo Add the rest of the fields.
 */
struct SW : public LO
{
    /* 0x34   */ int cpsoAll;
    /* 0x38   */ int cpsoRoot;
    /* 0x3c   */ DL dlRoot;
    /* 0x48   */ DL dlChild;
    /* 0x54   */ DL dlMRD;
    /* 0x60   */ DL dlBusy;
    /* 0x6c   */ DL dlBusySo;
    /* 0x78   */ DL dlMRDRealClock;
    /* 0x84   */ DL adlHash[512];
    /* 0x1884 */ LO *aploCidHead[154];
    /* 0x1aec */ int fAaoxValid;
    /* 0x1af0 */ SLOTHEAP slotheapOx;
    /* 0x1afc */ STRUCT_PADDING(23);
    /* 0x1b58 */ SLOTHEAP slotheapAsega;
    /* 0x1b64 */ STRUCT_PADDING(6);
    /* 0x1b7c */ DL dlAsegaPending;
    /* 0x1b88 */ STRUCT_PADDING(24);
    /* 0x1be8 */ DL dlLight;
    /* 0x1bf4 */ STRUCT_PADDING(18);
    /* 0x1c3c */ DL dlProxy;
    /* 0c1c48 */ DL dlFly;
    /* 0x1c54 */ DL dlDprize;
    /* 0x1c60 */ DL dlRat;
    /* 0x1c6c */ DL dlRathole;
    /* 0x1c78 */ DL dlDartFree;
    /* 0x1c84 */ DL dlSpire;
    /* 0x1c90 */ DL dlRail;
    /* 0x1c9c */ DL dlLanding;
    /* 0x1ca8 */ STRUCT_PADDING(9);
    /* 0x1ccc */ DL dlCrfod;
    /* 0x1cd8 */ STRUCT_PADDING(123);
    /* 0x1ec4 */ VISMAP *pvismap;

    // MISALIGNED:
    void (*pcbUpdate)(float fDelta);
};

extern SW *g_psw;

void InitSwDlHash(SW *psw);

void InitSw(SW *psw);

void DeleteSw(SW *psw);

void SetupBulkDataFromBrx(int fLoadBulkData, CBinaryInputStream *pbis);

void LoadBulkDataFromBrx(CBinaryInputStream *pbis);

void SetSwGravity(SW *psw, float z);

// TODO: Add unknown functions here.

int FOverflowSwLo(SW *psw, LO *plo, int fHiPri);

XA *PxaAllocSw(SW *psw);

void FreeSwXaList(SW *psw, XA *pxaFirst);

MQ *PmqAllocSw(SW *psw);

void FreeSwMqList(SW *psw, MQ *pmq);

void EnsureSwCallback(SW *psw, PFNMQ pfnmq, void *pvContext, MSGID msgid, void *pvCallbackData);

void PostSwCallback(SW *psw, PFNMQ pfnmq, void *pvContext, MSGID msgid, void *pvCallbackData);

void ClearSwCallbacks(SW *psw, GRFCMQ grfcmq, PFNMQ pfnmq, void *pvContext, MSGID msgid, void *pvCallback);

void ProcessSwCallbacks(SW *psw);

void ProcessSwSpliceScheduledCallbacks(SW *psw, float dt);

STSO *PstsoAllocSw(SW *psw);

void FreeSwStsoList(SW *psw, STSO *pstsoFirst);

void AddSwProxySource(SW *psw, LO *ploProxySource, int cploClone);

LO *PloGetSwProxySource(SW *psw, int ipsl);

void IntersectSwBoundingBox(SW *psw, SO *psoIntersect, VECTOR *ppos1, VECTOR *ppos2, PFNFILTER pfn, void *pvContext, int *pcpso, SO ***papso);

void IntersectSwBoundingSphere(SW *psw, SO *psoIntersect, VECTOR *pposCenter, float sRadius, PFNFILTER pfn, void *pvContext, int *pcpso, SO ***papso);

void RemoveOxa(OXA *poxa, OXA **ppoxaFirst);

void InitSwAoxa(SW *psw);

void AddOxa(OXA *poxa, OXA **ppoxaFirst);

OXA *PoxaAllocSw(SW *psw, SO *pso);

void FreeSwPoxa(SW *psw, OXA *poxa);

void CreateSwDefaultLights(SW *psw);

void CreateSwPrizes(SW *psw);

void LoadSwFromBrx(SW *psw, CBinaryInputStream *pbis);

int FClipLineHomogeneous(VECTOR4 *apos);

void DrawLineWorld(VECTOR *ppos1, VECTOR *ppos2, RGBA *rgba, CM *pcm, int fDepthTest);

void DrawAxesWorld(VECTOR *ppos, MATRIX3 *pmat, float sScale, CM *pcm, int fDepthTest);

void DrawBezWorld(VECTOR *ppos0, VECTOR *pv0, VECTOR *ppos1, VECTOR *pv1, float dtSeg, RGBA *rgba, CM *pcm, int fDepthTest);

void SetSwIllum(SW *psw, float uMidtone);

void SetSwIllumShadow(SW *psw, float uShadow);

void SetSwExcitement(SW *psw, float gexcMenu);

int FLevelSwVisited(SW *psw, WID wid);

int FLevelSwPrimary(SW *psw, WID wid);

int FLevelSwSecondary(SW *psw, WID wid);

int FLevelSwTertiary(SW *psw, WID wid);

// TODO: Add unknown functions here.

void SetSwPlayerSuck(SW *psw, float uSuck);

void GetSwPlayerSuck(SW *psw, float *puSuck);

void IncrementSwHandsOff(SW *psw);

void DecrementSwHandsOff(SW *psw);

int FUN_001dda80(SW *psw); // Unknown

void IsSwVagPlaying(SW *psw, int *pfPlaying);

void SetSwDarken(SW *psw, float rDarken);

void SetSwDarkenSmooth(SW *psw, float rDarkenSmooth);

void CancelSwDialogPlaying(SW *psw);

#endif // SW_H
