/**
 * @file puffer.h
 *
 * @brief Piranha Lake in Vicious Voodoo (believed to be formerly called "Pufferfish Pond").
 */
#ifndef PUFFER_H
#define PUFFER_H

#include "common.h"
#include <stepguard.h>
#include <water.h>
#include <bis.h>
#include <joy.h>
#include <so.h>
#include <mq.h>

/**
 * @class PUFFER
 * @brief Piranha fish used in Piranha Lake.
 * @todo Implement the struct.
 */
struct PUFFER : public PO
{
    // ...
};

/**
 * @class PUFFER_COLLECTION
 * @brief Collection of piranha fish.
 * @todo Implement the struct.
 */
struct PUFFC : public STEPGUARD
{
    // ...
};

/**
 * @class PUFFER_BRAIN
 * @brief AI controller for piranha fish.
 * @todo Implement the struct.
 */
struct PUFFB : public ALO
{
    // ...
};

/**
 * @class PUFFER_TORCH
 * @brief Tiki torch object in Piranha Lake.
 * @todo Implement the struct.
 */
struct PUFFT : public SO
{
    // ...
};

extern float D_0026A718;
extern float D_0026A71C;
extern SNIP D_0026A728[1];
extern int D_0026A720;
extern float D_0026A838;
extern float D_0026A83C;
extern float D_0024C868;
extern float D_0026A840;
extern SNIP D_0026A8E0[3];
extern PUFFER *g_ppuffer; // guess

void OnDifficultyPlayerDeathRaw(float scalar, struct DIFFICULTY *pdifficulty) __asm__("OnDifficultyPlayerDeath"); // unmangled in original

void FUN_001c8920(STEPGUARD *pstepguard);
void FUN_001973d8(PUFFER *ppuffer);
void FUN_00197a08(PUFFER *ppuffer, PUFFC *ppuffc);
struct WKR;
ALO *PaloAbsorbWkr(WKR *pwkr, int i, ALO **ppalo);

void InitPuffer(PUFFER *ppuffer);

void LoadPufferFromBrx(PUFFER *ppuffer, CBinaryInputStream *pbis);

void PostPufferLoad(PUFFER *ppuffer);

void PresetPufferAccel(PUFFER *ppuffer, float dt);

int FFilterPuffer(PUFFER *ppuffer, SO *psoOther);

void UpdatePuffer(PUFFER *ppuffer, float dt);

PUFFT *PpufftChoosePuffer(PUFFER *ppuffer);

void OnPufferActive(PUFFER *ppuffer, int fActive, PO *ppoOther);

void UpdatePufferActive(PUFFER *ppuffer, JOY *pjoy, float dt);

void AddPufferWaterAcceleration(PUFFER *ppuffer, WATER *pwater, float dt);

void HandlePufferMessage(PUFFER *ppuffer, MSGID msgid, void *pv);

void PostPuffcLoad(PUFFC *ppuffc);

void PresetPuffcAccel(PUFFC *ppuffc, float dt);

void UpdatePuffcGoal(PUFFC *ppuffc, int fEnter);

void OnPuffcExitingSgs(PUFFC *ppuffc, SGS sgsNext);

void OnPuffcEnteringSgs(PUFFC *ppuffc, SGS sgsPrev, ASEG *pasegOverride);

void UpdatePuffcSgs(PUFFC *ppuffc);

void HandlePuffcMessage(PUFFC *ppuffc, MSGID msgid, void *pv);

void UpdatePuffc(PUFFC *ppuffc, float dt);

int FCanPuffcAttack(PUFFC *ppuffc);

void PostPuffbLoad(PUFFB *ppuffb);

#endif // PUFFER_H
