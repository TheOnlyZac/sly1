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
 * @class BOMB
 * @brief Bomb (?).
 * @todo Implement the struct.
 */
struct BOMB : public SO
{
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
