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
 * @class _DPRIZE
 * @brief Base class for collectibles.
 */
struct DPRIZE : public ALO
{
    OID oidInitialState;
    float tDprizes;
    DPRIZES dprizesInit;
    DPRIZES dprizes; // State
    float dtInitialSkip;
    SM *psm;   // State machine
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
 * @class COIN
 * @brief Treasure coin.
 */
struct COIN : public DPRIZE
{
    LM lmDtMaxLifetime;
    float tLose;
};

/**
 * @class KEY
 * @brief Treasure key.
 */
struct KEY : public DPRIZE
{
    undefined1 padding1[0x14];         // 0x0 - 0x13 Padding?
    SW* pSw;                             // 0x14
    undefined1 padding2[0x2b - 0x18]; // 0x18-0x2b Pading?
    CFrame* pCFrame;                     // 0x2c
    undefined1 padding3[0x2cf - 0x31]; // 0x31 - 0x2cf Padding?
    DPRIZES dprizes;                     // 0x2d0
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
