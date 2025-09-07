/**
 * @file dzg.h
 */
#ifndef DZG_H
#define DZG_H

#include "common.h"
#include <so.h>
#include <dl.h>

// Forward.
struct XP;

typedef int GRFSG;

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct DZ
{
    // ...
};

/**
 * @brief Unknown.
 */
struct DZG
{
    int cdzMax;
    int cdz;
    DZ *adz;
    DL dlPos;
    DL dlZero;
    DL dlMax;
    DL dlUncat;
    int cdzPos;
    float *aagPos;
    float *aagPosCrout;
    float *asdv;
    float *adsfPos;
};

void InitDzg(DZG *pdzg, int cpxp);

void ClearDzgSolution(DZG *pdzg);

void AppendDzgDz(DZG *pdzg, DZ *pdzOther);

void FillDzgDz(DZG *pdzg, GRFSG grfsg, DZ *pdzForce, int cpxp, XP **apxp, int *acpso, SO ***aapso);

void EnforceDzgDz(DZG *pdzg, DZ *pdzAdd);

void SolveDzg(DZG *pdzg, GRFSG grfsg, int cpxp, XP **apxp, int *acpso, SO ***aapso);

void SolveDzgFric(DZG *pdzg, GRFSG grfsg, int cpxp, XP **apxp, int *acpso, SO ***aapso, float dt);

void ApplyDzg(DZG *pdzg, int cpsoRoot, int *acpso, SO ***aapso, float sdvMax, float sdwMax);

void SolveInequalities(int c, float *aag, float *ag, float *agSoln);

#endif // DZG_H
