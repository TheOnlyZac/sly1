/**
 * @file stepcane.h
 */
#ifndef STEPCANE_H
#define STEPCANE_H

#include "common.h"
#include <target.h>
#include <break.h>
#include <joy.h>
#include <jt.h>

// Forward.
struct ASEGBL;

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct BL
{
    // ...
};

void SetJtJtcs(JT *pjt, JTCS jtcs);

void UpdateJtCane(JT *pjt);

void UpdateJtActiveCane(JT *pjt, JOY *pjoy);

void ChooseJtAttackTarget(JT *pjt, GRFTAK grftak, VECTOR *pposNaturalLocal, float dtProj, float dradMax, TARGET **pptarget, VECTOR *pdposProj);

void ChooseJtSweepTarget(JT *pjt, BL *ablSweep, ASEGBL *pasegbl);

void ChooseJtRushTarget(JT *pjt);

void ChooseJtSmashTarget(JT *pjt);

#endif // STEPCANE_H
