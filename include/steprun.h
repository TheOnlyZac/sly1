/**
 * @file steprun.h
 */
#ifndef STEPRUN_H
#define STEPRUN_H

#include "common.h"
#include <stepcane.h>

// Forward.
struct MRSG;
struct ASEGA;
struct ASEGBL;

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct BLRUN : public BL
{
    // ...
};

void PostStepLoadRun(STEP *pstep, BLRUN *ablrun, ASEGBL **ppasegbl);

void CalculateBlrunV(int cblrun, BLRUN *ablrun, MRSG *amrsgBlend, VECTOR *pv);

void ProjectStepRunPlant(STEP *pstep, BLRUN *ablrun, float uPlant, float rJt, int iblrunWalk, int iblrunRun, VECTOR *pposPlant);

int FIntersectStepRunPlant(STEP *pstep, VECTOR *pposUp, VECTOR *pposDown, float *pu);

int FReblendAbl2D(int cbBl, int c1, int c2, BL *abl);

void AdjustStepRun(STEP *pstep, BLRUN *ablrun, ASEGBL *pasegbl, ASEGA *pasega);

void SetStepRunTarget(STEP *pstep, float rad, float u, BLRUN *ablrun, ASEGBL *pasegbl);

#endif // STEPRUN_H
