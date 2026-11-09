/**
 * @file sw.h
 *
 * @brief Scene world?
 */
#ifndef SW_H
#define SW_H

#include "common.h"
#include <slotheap.h>
#include <light.h>
#include <game.h>
#include <bis.h>
#include <vec.h>
#include <lo.h>
#include <mq.h>
#include <cm.h>

typedef void (*PFNFILTER)(void *, SO *); // TODO: Figure out if this is correct.

// Forward.
struct OXA;
struct VISMAP;
struct SPLC;

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
    /* 0x1afc */ STRUCT_PADDING(3); // Likely a SLOTHEAP.
    /* 0x1b08 */ SLOTHEAP slotheapXa;
    /* 0x1b14 */ SLOTHEAP slotheapMq;
    /* 0x1b20 */ STRUCT_PADDING(14);
    /* 0x1b58 */ SLOTHEAP slotheapAsega;
    /* 0x1b64 */ STRUCT_PADDING(6);
    /* 0x1b7c */ DL dlAsegaPending;
    /* 0x1b88 */ SLOTHEAP slotheapSma;
    /* 0x1b94 */ DL dlSma;
    /* 0x1ba0 */ STRUCT_PADDING(18);
    /* 0x1be8 */ DL dlLight;
    /* 0x1bf4 */ STRUCT_PADDING(6);
    /* 0x1c0c */ SLOTHEAP slotheapStso;
    /* 0x1c18 */ SLOTHEAP slotheapFader;
    /* 0x1c24 */ DL dlFader;
    /* 0x1c30 */ DL dlRealClockFader;
    /* 0x1c3c */ DL dlProxy;
    /* 0x1c48 */ DL dlFly;
    /* 0x1c54 */ DL dlDprize;
    /* 0x1c60 */ DL dlRat;
    /* 0x1c6c */ DL dlRathole;
    /* 0x1c78 */ DL dlDartFree;
    /* 0x1c84 */ DL dlSpire;
    /* 0x1c90 */ DL dlRail;
    /* 0x1c9c */ DL dlLanding;
    /* 0x1ca8 */ DL dlBusyLasen;
    /* 0x1cb4 */ DL dlBlipg;
    /* 0x1cc0 */ DL dlBlipgFree;
    /* 0x1ccc */ DL dlCrfod;
    /* 0x1cd8 */ STRUCT_PADDING(4);
    /* 0x1ce8 */ LO *aploStock[29];
    /* 0x1d5c */ STRUCT_PADDING(3);
    /* 0x1d68 */ LSM lsmDefault;
    /* 0x1d70 */ STRUCT_PADDING(85);
    /* 0x1ec4 */ VISMAP *pvismap;
    /* 0x1ec8 */ MQ *pmqCallbackFirst;
    /* 0x1ecc */ MQ *pmqCallbackLast;
    /* 0x1ed0 */ STRUCT_PADDING(8);
    /* 0x1ef0 */ int csplcSplice;
    /* 0x1ef4 */ SPLC *asplcSplice;
    /* 0x1ef8 */ uint symidScheduledCallbackList;
    /* 0x1efc */ STRUCT_PADDING(263);
    /* 0x2318 */ float gexcMenu;
    /* 0x231c */ int cHandsOff;
    /* 0x2320 */ STRUCT_PADDING(11);
    /* 0x234c */ float rDarken;
    /* 0x2350 */ float rDarkenSmooth;
    // ...

    // MISALIGNED:
    void (*pcbUpdate)(float fDelta);
};

/**
 * @brief Proxy source list entry (count and clone array). Name is a guess.
 */
struct PSL
{
    /* 0x00 */ int cplo;
    /* 0x04 */ LO **aplo;
};

/**
 * @brief Unknown.
 * @todo Implement the struct and figure out where it belongs.
 */
struct XA
{
    /* 0x00 */ STRUCT_PADDING(1);
    /* 0x04 */ SO *pso;
    /* 0x08 */ STRUCT_PADDING(1);
    /* 0x0c */ XA *pxaNextTarget;
}; // 0x10 bytes.

/**
 * @brief Unknown.
 * @todo Implement the struct and figure out where it belongs.
 */
struct STSO
{
    /* 0x00 */ SO *psoTouch;
    /* 0x04 */ STSO *pstsoNext;
}; // 0x08 bytes.

extern SW *g_psw;

void InitSwDlHash(SW *psw);

void InitSw(SW *psw);

void DeleteSw(SW *psw);

void SetupBulkDataFromBrx(int fLoadBulkData, CBinaryInputStream *pbis);

void LoadBulkDataFromBrx(CBinaryInputStream *pbis);

void SetSwGravity(SW *psw, float z);

// TODO: Add unknown functions here.

/**
 * @brief Checks whether adding another object of this class would overflow the world.
 * @param psw World.
 * @param plo Object whose class flags are checked (flag 2 of its VT).
 * @param fHiPri Non-zero if the object is high priority.
 * @return Non-zero when the root object count is at least 247, the class has flag 2
 * and the object is not high priority. Meaning of the flag is a guess.
 */
int FOverflowSwLo(SW *psw, LO *plo, int fHiPri);

XA *PxaAllocSw(SW *psw);

void FreeSwXaList(SW *psw, XA *pxaFirst);

MQ *PmqAllocSw(SW *psw);

void FreeSwMqList(SW *psw, MQ *pmq);

void EnsureSwCallback(SW *psw, PFNMQ pfnmq, void *pvContext, MSGID msgid, void *pvCallbackData);

void PostSwCallback(SW *psw, PFNMQ pfnmq, void *pvContext, MSGID msgid, void *pvCallbackData);

/**
 * @brief Removes (and frees) queued callbacks that match every criterion selected in `grfcmq`.
 * @param psw World.
 * @param grfcmq Bit mask of criteria: 1 = pfnmq, 2 = pvContext, 4 = msgid, 8 = pvCallbackData.
 * @param pfnmq Callback to match when bit 1 is set.
 * @param pvContext Context to match when bit 2 is set.
 * @param msgid Message id to match when bit 4 is set.
 * @param pvCallbackData Callback data to match when bit 8 is set.
 * @note The meaning of the GRFCMQ bits is inferred from the assembly.
 */
void ClearSwCallbacks(SW *psw, GRFCMQ grfcmq, PFNMQ pfnmq, void *pvContext, MSGID msgid, void *pvCallback);

/**
 * @brief Dispatches and frees every queued world callback message.
 * @param psw World.
 */
void ProcessSwCallbacks(SW *psw);

void ProcessSwSpliceScheduledCallbacks(SW *psw, float dt);

STSO *PstsoAllocSw(SW *psw);

void FreeSwStsoList(SW *psw, STSO *pstsoFirst);

/**
 * @brief Registers a proxy source in the world's proxy source list, creating
 * `cploClone - 1` extra clones of it.
 * @param psw World.
 * @param ploProxySource Object used as the proxy source.
 * @param cploClone Total number of copies requested (the clone array holds one fewer).
 * @note Parameter names and the PSL layout are guesses from the assembly.
 */
void AddSwProxySource(SW *psw, LO *ploProxySource, int cploClone);

/**
 * @brief Pops the next clone from proxy source list entry `ipsl`.
 * @param psw World.
 * @param ipsl Index of the proxy source list entry.
 * @return The popped clone object.
 */
LO *PloGetSwProxySource(SW *psw, int ipsl);

void IntersectSwBoundingBox(SW *psw, SO *psoIntersect, VECTOR *ppos1, VECTOR *ppos2, PFNFILTER pfn, void *pvContext, int *pcpso, SO ***papso);

void IntersectSwBoundingSphere(SW *psw, SO *psoIntersect, VECTOR *pposCenter, float sRadius, PFNFILTER pfn, void *pvContext, int *pcpso, SO ***papso);

/**
 * @brief Unlinks an OXA from a doubly linked list.
 * @param poxa Element to remove.
 * @param ppoxaFirst Pointer to the list head, updated if `poxa` was first.
 */
void RemoveOxa(OXA *poxa, OXA **ppoxaFirst);

/**
 * @brief Allocates the world's array of 256 OXAs and links them into a free list.
 * @param psw World.
 */
void InitSwAoxa(SW *psw);

/**
 * @brief Pushes an OXA onto the front of a doubly linked list.
 * @param poxa Element to add.
 * @param ppoxaFirst Pointer to the list head.
 */
void AddOxa(OXA *poxa, OXA **ppoxaFirst);

/**
 * @brief Takes an OXA from the world's free list, moves it to the used list and assigns it to `pso`.
 * @param psw World.
 * @param pso Object the OXA is for.
 * @return The allocated OXA.
 */
OXA *PoxaAllocSw(SW *psw, SO *pso);

/**
 * @brief Frees an OXA: releases its OX list, clears its rows and columns in the world's pair
 * matrix and moves it back to the free list.
 * @param psw World.
 * @param poxa OXA to free.
 * @note Roles of the matrix at SW+0x1ADC and the ALO flag at +0x538 are guesses.
 */
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
/**
 * @brief Stores `plo` at SW offset 0x2324 (some tracked object; name unknown).
 */
void FUN_001ddc38(SW *psw, LO *plo);

/**
 * @brief Checks a level's completion flags (flag 4 of its completion) against the current level state.
 * @param psw World (unused).
 * @param wid Level id.
 * @return Non-zero if flag 4 is set and the low 2 completion flags are all set in the current level state.
 * @note Meaning is a guess; likely a secondary-objective check.
 */
int FUN_001dd758(SW *psw, WID wid);

/**
 * @brief Like FUN_001dd758 but flag 8 and the low 3 completion flags.
 * @param psw World (unused).
 * @param wid Level id.
 * @return Non-zero if flag 8 is set and the low 3 completion flags are set in the current level state.
 */
int FUN_001dd7a0(SW *psw, WID wid);

/**
 * @brief Looks up a scene variable by id in a level state.
 * @param psw World (unused).
 * @param wid Level id.
 * @param id Variable id to look for in the (id, value) pairs at LS+0x44.
 * @return The value, or 0 if not found. Name and meaning are guesses.
 */
int FUN_001dd888(SW *psw, WID wid, int id);

/**
 * @brief Calculates the percent completion of the current game state (discards the result).
 * @note Probably a script callback wrapper; the return value handling is a guess.
 */
void FUN_001dd928();

/**
 * @brief Randomly picks a count in [nLow, nHigh] and attracts that many dprizes (cid 0x58) to a position.
 * @param psw World (unused, g_psw is used).
 * @param nLow Minimum count.
 * @param nHigh Maximum count.
 * @param ppos Center position.
 * @note Parameter names are guesses.
 */
void FUN_001dd950(SW *psw, int nLow, int nHigh, VECTOR *ppos);

/**
 * @brief Increments the SW counter at 0x2320 and, when it becomes 1, shows a blot.
 * @param psw World.
 */
void FUN_001ddb58(SW *psw);

/**
 * @brief Decrements the SW counter at 0x2320 and, when it reaches 0, hides a blot.
 * @param psw World.
 */
void FUN_001ddbb8(SW *psw);

/**
 * @brief Calls PexcSetExcitement(n), discarding the result.
 * @param pv Unused.
 * @param n Excitement index.
 */
void FUN_001ddbf8(void *pv, int n);

/**
 * @brief Calls UnsetExcitementHyst(pexc).
 * @param pv Unused.
 * @param pexc Excitement to unset.
 */
void FUN_001ddc18(void *pv, EXC *pexc);

/**
 * @brief Calls the virtual function at VT offset 0xC8 of the object stored at SW offset 0x2324, if any.
 * @param psw World.
 */
void FUN_001ddc40(SW *psw);

/**
 * @brief Clears bit `n` of the flags at SW offset 0x235C.
 * @param pv World.
 * @param n Bit index.
 */
void FUN_001ddc90(void *pv, int n);

/**
 * @brief Sets (or updates) a scene variable of a level state.
 * @param psw World (unused).
 * @param wid Level id.
 * @param id Variable id. Takes the first free slot (id 0) or the slot already holding `id`.
 * @param value Value to store.
 * @note Name and meaning are guesses.
 */
void FUN_001dd7e8(SW *psw, WID wid, int id, int value);

/**
 * @brief Writes the current charm count to `*pn`.
 * @param pv Unused.
 * @param pn Output.
 */
void FUN_001ddcb0(void *pv, int *pn);

/**
 * @brief Writes the current life count to `*pn`.
 * @param pv Unused.
 * @param pn Output.
 */
void FUN_001ddcc8(void *pv, int *pn);

void SetSwPlayerSuck(SW *psw, float uSuck);

void GetSwPlayerSuck(SW *psw, float *puSuck);

void IncrementSwHandsOff(SW *psw);

void DecrementSwHandsOff(SW *psw);

/**
 * @note Not in the prototype, so name is unofficial.
 */
int IsSwHandsOff(SW *psw);

void IsSwVagPlaying(SW *psw, int *pfPlaying);

void SetSwDarken(SW *psw, float rDarken);

void SetSwDarkenSmooth(SW *psw, float rDarkenSmooth);

void CancelSwDialogPlaying(SW *psw);

#endif // SW_H
