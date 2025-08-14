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
    uint8_t unk_uint8_Pad[0x14];         // 0x0 - 0x13 Padding?
    SW* pSw;                             // 0x14
    uint8_t unk_uint8_Pad1[0x2b - 0x18]; // 0x18-0x2b Pading?
    CFrame* pCFrame;                     // 0x2c
    uint8_t unk_uint_Pad2[0x2cf - 0x31]; // 0x31 - 0x2cf Padding?
    DPRIZES dprizes;                     // 0x2d0
};

/**
 * @brief Charm.
 */
struct CHARM : public DPRIZE
{
    //...
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
 * @brief Clone a DPrize
 *
 * @param pdprize DPrize clone target
 * @param pdprizeBase DPrize clone source
 *
 * @note ichkCollected and dle will not be overwritten
 */
void CloneDprize(DPRIZE *pdprize, DPRIZE *pdprizeBase);

/**
 * @brief Sets the DPRIZES enum of a given DPRIZE.
 *
 * @param pdprize DPRIZE whose enum needs to be set.
 * @param dprizes New DPRIZES value.
 *
 */
void SetDprizeDprizes(DPRIZE *pdprize, DPRIZES dprizes);

/**
 * @brief Initializes a DPrize
 *
 * @param pdprize DPrize to initialize
 */
void InitCoin(COIN *pcoin);

/**
 * @brief Updates the coin.
 *
 * @param pcoin Pointer to the coin.
 * @param dt Time elapsed since the last frame.
 *
 * @todo Implement this function.
 */
void UpdateCoin(COIN *pcoin, float dt);

// ...

/**
 * @brief Add a life
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
 * @brief Sets the coin's Dprizes enum.
 *
 * @param pcoin Pointer to the coin.
 * @param dprizes The new prize.
 *
 * @todo Implement this function.
 */
void SetCoinDprizes(COIN *pcoin, DPRIZES dprizes);

/**
 * @brief Initializes a Charm
 *
 * @param pcharm Charm to initialize
 */
void InitCharm(CHARM *pcharm);

/**
 * @brief Sets the Charm's Dprizes enum.
 *
 * @param pcharm Pointer to the charm.
 * @param dprizes The new prize.
 *
 * @todo Fill CHARM struct.
 */
void SetCharmDprizes(CHARM *pcharm, DPRIZES dprizes);

/**
 * @brief Initializes a Charm
 *
 * @param pcharm Charm to initialize
 */
void InitKey(KEY *pkey);


void SetKeyDprizes(KEY *pkey, DPRIZES dprizes);

int CpdprizeAttractSwDprizes(SW *psw, CID cid, VECTOR *pposCenter, int cpdprizeMax, DPRIZE **apdprize);

void RemoveSwExtraneousCharms(SW *psw);

extern SNIP s_asnipDprize[5];

#endif // COIN_H
