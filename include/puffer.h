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
struct PUFFC : public ALO
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
