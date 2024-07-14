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
    DPRIZES dprizes; // State
    float tDprizes;
    DPRIZES dprizesInit;
    OID oidInitialState;
    float dtInitialSkip;
    SM *psm; // State machine
    SMA *psma; // State machine action
    TARGET *ptarget;
    VECTOR posCenter;
    VECTOR vCenter;
    VECTOR dvCenter;
    float uGlintChance;
    PNT *ppntFrontGlint;
    PNT *ppntBackGlint;
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
    undefined4 unk_0;
    VECTOR normalSmooth;
    int fSwirlDone;
    DLE dle;
    int ichkCollected;
    EXPL *pexplCollect;
    EXPL *pexplAttract;
    float svcAtract;
    float cAttract;
};

/**
 * @brief Coin.
 */
struct COIN : public DPRIZE
{
    // ...
};

/**
 * @brief Treasure key.
 */
struct KEY : public DPRIZE
{
    // ...
};

#endif // COIN_H
