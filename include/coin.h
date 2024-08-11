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
#include <xform.h>

// Forward declarations
struct DPRIZE;
struct COIN;
struct KEY;
struct CHARM;

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
 * @brief DPRIZE.
 *
 * Base class for coins, keys, and other collectibles.
 */
struct DPRIZE : public ALO
{
    OID oidInitialState;
    float tDprizes;
    DPRIZES dprizesInit;
    DPRIZES dprizes; // State
    float dtInitialSkip;
    SM *psm; // State machine
    SMA *psma; // State machine action
    TARGET *ptarget;
    VECTOR posCenter;
    VECTOR vCenter;
    VECTOR dvCenter;
    PNT *ppntFrontGlint;
    PNT *ppntBackGlint;
    int fLeft;
    float uGlintChance;
    float tGlint;
    undefined4 unk_0[4];
    int fNeverReuse;
    int fReuseCandidate;
    int fLastBounce;
    float svLastBounceMax;
    float svLastBounce;
    float sRadiusBounce;
    float sRadiusCollect;
    float rzBounce;
    float rxyBounce;
    float radSmooth;
    VECTOR normalSmooth;
    int fSwirlDone;
    undefined4 unk_1; 
    DLE dle;
    int ichkCollected;
    EXPL *pexplCollect;
    EXPL *pexplAttract;
    float svcAttract;
    float cAttract;
};

/**
 * @brief Coin.
 */
struct COIN : public DPRIZE
{
    LM lmDtMaxLifetime;
    float tLose;
};

/**
 * @brief Treasure key.
 */
struct KEY : public DPRIZE
{
    // ...
};


/**
 * @brief Charm.
 */
struct CHARM : public DPRIZE
{

};

/**
 * @brief Initializes a DPrize
 *
 * @param pdprize DPrize to initialize
 */
void InitDprize(DPRIZE *pdprize);

/**
 * @brief Loads a DPrize from an Input Stream
 *
 * @param pdprize DPrize to initialize
 * @param pbis Input Stream
 */
void LoadDprizeFromBrx(DPRIZE *pdprize, CBinaryInputStream *pbis);

/**
 * @brief Initializes a DPrize
 *
 * @param pdprize DPrize to initialize
 */
void InitCoin(COIN *pcoin);

/**
 * @brief Add a life
 *
 */
void AddLife(void *ptr);

/**
 * @brief Initializes a Charm
 *
 * @param pcharm Charm to initialize
 */
void InitCharm(CHARM *pcharm);

/**
 * @brief Initializes a Charm
 *
 * @param pcharm Charm to initialize
 */
void InitKey(KEY *pkey);


extern SNIP s_asnipDprize[5];

#endif // COIN_H
