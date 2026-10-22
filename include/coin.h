/**
 * @file coin.h
 *
 * @brief Coins, keys, and other collectibles.
 */
#ifndef COIN_H
#define COIN_H

#include "common.h"
#include <alo.h>
#include <oid.h>
#include <sm.h>
#include <sw.h>
#include <xform.h>
#include <sound.h>
#include <target.h>

/**
 * @brief DPRIZE state.
 *
 * @note Values based on May 19 build.
 */
enum DPRIZES
{
    DPRIZES_Nil = -1,
    DPRIZES_Normal = 0,
    DPRIZES_Collect = 1,
    DPRIZES_Removed = 2,
    DPRIZES_Fall = 3,
    DPRIZES_Swirl = 4,
    DPRIZES_Stick = 5,
    DPRIZES_Lose = 6,
    DPRIZES_Attract = 7,
    DPRIZES_Max = 8
};

/**
 * @class _DPRIZE
 * @brief Base class for collectibles.
 */
struct DPRIZE : public ALO
{
    /* 0x2d0 */ DPRIZES dprizes;
    /* 0x2d4 */ float tDprizes;
    /* 0x2d8 */ DPRIZES dprizesInit;
    /* 0x2dc */ OID oidInitialState;
    /* 0x2e0 */ float dtInitialSkip;
    /* 0x2e4 */ SM *psm;
    /* 0x2e8 */ SMA *psma;
    /* 0x2ec */ TARGET *ptarget;
    /* 0x2f0 */ VECTOR posCenter;
    /* 0x300 */ VECTOR vCenter;
    /* 0x310 */ VECTOR dvCenter;
    /* 0x320 */ float uGlintChance;
    /* 0x324 */ PNT *ppntFrontGlint;
    /* 0x328 */ PNT *ppntBackGlint;
    /* 0x32c */ int fLeft;
    /* 0x330 */ float tGlint;
    /* 0x334 */ int fNeverReuse;
    /* 0x338 */ int fReuseCandidate;
    /* 0x33c */ int fLastBounce;
    /* 0x340 */ int fUnknown;
    /* 0x344 */ float svLastBounceMax;
    /* 0x348 */ float svLastBounce;
    /* 0x34c */ float sRadiusBounce;
    /* 0x350 */ float sRadiusCollect;
    /* 0x354 */ float rzBounce;
    /* 0x358 */ float rxyBounce;
    /* 0x35c */ float radSmooth;
    /* 0x360 */ VECTOR normalSmooth;
    /* 0x370 */ int fSwirlDone;
    /* 0x374 */ DLE dle;
    /* 0x37c */ int ichkCollected;
    /* 0x380 */ EXPL *pexplCollect;
    /* 0x384 */ EXPL *pexplAttract;
    /* 0x388 */ float svcAttract;
    /* 0x38c */ float cAttract;
};

/**
 * @class COIN
 * @brief Treasure coin.
 */
struct COIN : public DPRIZE
{
    /* 0x390 */ LM lmDtMaxLifetime;
    /* 0x398 */ float tLose;
};

/**
 * @class CHARM
 * @brief Lucky charm worn by Sly and Murray.
 */
struct CHARM : public DPRIZE
{
    //...
};

/**
 * @class KEY
 * @brief Treasure key.
 */
struct KEY : public DPRIZE
{
    // ...
};

/**
 * @brief Initializes a dprize.
 *
 * @param pdprize Dprize to initialize.
 */
void InitDprize(DPRIZE *pdprize);

/**
 * @brief Loads a dprize from an Input Stream.
 *
 * @param pdprize Dprize to load/initialize.
 * @param pbis Binary input Stream.
 */
void LoadDprizeFromBrx(DPRIZE *pdprize, CBinaryInputStream *pbis);

/**
 * @brief Clone a dprize.
 *
 * @param pdprize Dprize clone target.
 * @param pdprizeBase Original dprize to clone.
 *
 * @note ichkCollected and dle will not be overwritten.
 */
void CloneDprize(DPRIZE *pdprize, DPRIZE *pdprizeBase);

/**
 * @brief Sets the state of a given dprize.
 *
 * @param pdprize Dprize whose state to set.
 * @param dprizes New state value.
 *
 */
void SetDprizeDprizes(DPRIZE *pdprize, DPRIZES dprizes);

/**
 * @brief Initializes a coin.
 *
 * @param pcoin Coin to initialize.
 */
void InitCoin(COIN *pcoin);

/**
 * @brief Updates a coin.
 *
 * @param pcoin Coin to update.
 * @param dt Time elapsed since the last frame.
 *
 * @todo Implement this function.
 */
void UpdateCoin(COIN *pcoin, float dt);

// ...

void CreateSwCharm(SW *psw);

/**
 * @brief Adds a life.
 *
 */
void AddLife(void *ptr);

/**
 * @brief Handles when the player touches a coin.
 *
 * @param pcoin Pointer to the coin.
 */
void OnCoinSmack(COIN *pcoin);

/**
 * @brief Sets a coin's dprize state.
 *
 * @param pcoin Coin whose state to update.
 * @param dprizes New state value.
 *
 * @todo Implement this function.
 */
void SetCoinDprizes(COIN *pcoin, DPRIZES dprizes);

/**
 * @brief Initializes a lucky charm.
 *
 * @param pcharm Charm to initialize.
 */
void InitCharm(CHARM *pcharm);

/**
 * @brief Sets a lucky charm's dprize state.
 *
 * @param pcharm Charm whose state to update.
 * @param dprizes New state value.
 *
 * @todo Fill CHARM struct.
 */
void SetCharmDprizes(CHARM *pcharm, DPRIZES dprizes);

/**
 * @brief Initializes a treasure key.
 *
 * @param pcharm Key to initialize.
 */
void InitKey(KEY *pkey);

/**
 * @brief Sets a treasure key's dprize state.
 *
 * @param pkey Key whose state to set.
 * @param dprizes New state value.
 */
void SetKeyDprizes(KEY *pkey, DPRIZES dprizes);

/**
 * @brief Unknown.
 *
 * @todo Investigate this function.
 */
int CpdprizeAttractSwDprizes(SW *psw, CID cid, VECTOR *pposCenter, int cpdprizeMax, DPRIZE **apdprize);

/**
 * @brief Unknown.
 *
 * @todo Investigate this function.
 */
void RemoveSwExtraneousCharms(SW *psw);

extern SNIP s_asnipDprize[5];

#endif // COIN_H
