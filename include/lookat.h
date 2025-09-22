/**
 * @file lookat.h
 */
#ifndef LOOKAT_H
#define LOOKAT_H

#include "common.h"
#include <util.h>
#include <vec.h>
#include <mat.h>
#include <alo.h>

/**
 * @brief Actor Look At (?)
 */
struct ACTLA
{
    int fUseTarget;
    ALO *paloTarget;
    VECTOR posTargetLocal;
    float sIgnore;
    int nPriorityEnabled;
    int nPriorityDisabled;
    int fPaused;
    CLQ clqPanToPan;
    LM lmPan;
    CLQ clqTiltToTilt;
    LM lmTilt;
};

void InitActla(ACTLA *pactla, ALO *palo);

void SetActlaTarget(ACTLA *pactla, ALO *paloTarget, VECTOR *pposLocal);

ALO *PaloGetActlaTarget(ACTLA *pactla);

void UpdateActla(ACTLA *pactla, float dt);

void GetActlaRotationGoal(ACTLA *pactla, float dtOffset, MATRIX3 *pmat, VECTOR *pw);

#endif // LOOKAT_H
