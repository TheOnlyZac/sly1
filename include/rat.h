/**
 * @file rat.h
 *
 * @brief Rats.
 */
#ifndef RAT_H
#define RAT_H

#include "common.h"
#include <flash.h>
#include <bis.h>
#include <so.h>
#include <lo.h>
#include <cm.h>

// Forward.
struct XP;
struct WKR;

/**
 * @brief Rat state.
 */
enum RATS
{
    RATS_Nil = -1,
    RATS_Stopped = 0,
    RATS_Scurry = 1,
    RATS_Flee = 2,
    RATS_Dead = 3,
    RATS_Hidden = 4,
    RATS_Max = 5
};

/**
 * @class RAT
 * @brief Rat animal.
 * @todo Implement the struct.
 */
struct RAT : public SO
{
    // ...
    /* 0x55c */ float tRatSqueak;
    /* 0x560 */ STRUCT_PADDING(43);
    /* 0x608 */ LM lmDtStop;
    /* 0x610 */ STRUCT_PADDING(21);
    /* 0x664 */ int ccoin;
    // ...
};

/**
 * @class RATHOLE
 * @brief Hole where rats come from/go to.
 * @todo Implement the struct.
 */
struct RATHOLE : public LO
{
    // ...
};

void InitRat(RAT *prat);

void LoadRatFromBrx(RAT *prat, CBinaryInputStream *pbis);

void PostRatLoad(RAT *prat);

void OnRatAdd(RAT *prat);

void OnRatRemove(RAT *prat);

void CloneRat(RAT *prat, RAT *pratBase);

void PresetRatAccel(RAT *prat, float dt);

void UpdateRat(RAT *prat, float dt);

void AdjustRatNewXp(RAT *prat, XP *pxp, int ixpd);

void AdjustRatXpVelocity(RAT *prat, XP *pxp, int ixpd);

void RenderRatAll(RAT *prat, CM *pcm, RO *pro);

int FAbsorbRatWkr(RAT *prat, WKR *pwkr);

void ChooseRatFleeTarget(RAT *prat);

void HideRat(RAT *prat, int fHide);

void SetRatRats(RAT *prat, RATS rats);

void OnRatholeAdd(RATHOLE *prathole);

void OnRatholeRemove(RATHOLE *prathole);

#endif // RAT_H
