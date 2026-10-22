/**
 * @file bomb.h
 */
#ifndef BOMB_H
#define BOMB_H

#include "common.h"
#include <difficulty.h>
#include <sound.h>
#include <so.h>
#include <po.h>
#include <mq.h>

// Forward.
struct WKR;

/**
 * @brief Bomb detonation type?
 */
enum BDT
{
    BDT_Nil = -1,
    BDT_Impact = 0,
    BDT_Timed = 1,
    BDT_PropImpact = 2,
    BDT_Manual = 3,
    BDT_Player = 4,
    BDT_Max = 5,
};

/**
 * @class BOMB
 * @brief Bomb (?).
 * @todo Implement the struct.
 */
struct BOMB : public SO
{
    /* 0x550 */ BDT bdt;
    /* 0x554 */ float tDetonate;
    // ...
    /* 0x680 */ SFX *psfxDet;
    // ...
};

void InitBomb(BOMB *pbomb);

void LoadBombFromBrx(BOMB *pbomb, CBinaryInputStream *pbis);

void CloneBomb(BOMB *pbomb, BOMB *pbombBase);

void PostBombLoad(BOMB *pbomb);

void HandleBombMessage(BOMB *pbomb, MSGID msgid, void *pv);

void UpdateBomb(BOMB *pbomb, float dt);

int FAbsorbBombWkr(BOMB *pbomb, WKR *pwkr);

void PrimeBomb(BOMB *pbomb, float dt);

void ApplyBombThrow(BOMB *pbomb, PO *ppo);

void DetonateBomb(BOMB *pbomb);

SFX *PsfxEnsureBomb(BOMB *pbomb, ENSK ensk);

#endif // BOMB_H
