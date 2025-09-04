/**
 * @file cnvo.h
 */
#ifndef CNVO_H
#define CNVO_H

#include "common.h"
#include <so.h>

// TODO: What is this? Where should this be defined?
struct XP;

/**
 * @brief Conveyor belt (?)
 * @todo Implement the struct.
 */
struct CNVO : public SO
{
    // ...
    float svBelt;
    float svuAvg;
    float svvAvg;
    // ...
};

void InitCnvo(CNVO *pcnvo);

void LoadCnvoFromBrx(CNVO *pcnvo, CBinaryInputStream *pbis);

void PostCnvoLoad(CNVO *pcnvo);

void AdjustCnvoXpVelocity(CNVO *pcnvo, XP *pxp, int ixpd);

void SetCnvoBeltSpeed(CNVO *pcnvo, float svBelt);

void MatchCnvoScrollerToBeltSpeed(CNVO *pcnvo);

#endif // CNVO_H
