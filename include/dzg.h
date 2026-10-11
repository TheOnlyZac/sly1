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
    /* 0x00 */ int cdzMax;
    /* 0x04 */ int cdz;
    /* 0x08 */ DZ *adz;
    /* 0x0c */ DL dlPos;
    /* 0x18 */ DL dlZero;
    /* 0x24 */ DL dlMax;
    /* 0x30 */ DL dlUncat;
    /* 0x3c */ int cdzPos;
    /* 0x40 */ float *aagPos;
    /* 0x44 */ float *aagPosCrout;
    /* 0x48 */ float *asdv;
    /* 0x4c */ float *adsfPos;
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
