/**
 * @file solve.h
 */
#ifndef SOLVE_H
#define SOLVE_H

#include <so.h>
#include <dl.h>
#include <vec.h>

typedef int GRFSG;

/**
 * @brief Unknown.
 */
enum DZK
{
    DZK_Normal = 0,
    DZK_Friction = 1,
    DZK_Equality = 2,
};

/**
 * @brief Unknown.
 */
struct FX
{
    VECTOR dv;
    VECTOR dw;
};

/**
 * @brief Unknown.
 */
struct XP
{
    // ...
};

/**
 * @brief Unknown.
 *
 * @todo Based on the May 19 prototype.
 * May be incomplete and/or inaccurate.
 */
struct DZ
{
    XP *pxp;
    undefined1 unknown[12];
    VECTOR f;
    FX *aafx[2];
    DZK dzk;
    int fMax;
    float sfMax;
    float sf;
    float sdv;
    float dsdv;
    VECTOR *mpipxpdv;
    float *mpidzg;
    DZ *pdzOther;
    DLE dle;
    // ...
};

void RenumberSo(SO *pso, int *pcpso, SO **apso);

void CalculateSoEffect(SO *pso, VECTOR *ppos, FX *pfx, VECTOR *pdv);

void PropagateSoForce(SO *psoRoot, GRFSG grfsg, XP *pxp, int ixpd, DZ *pdz, FX *afx);

void DistributeSoEffects(SO *psoRoot, GRFSG grfsg, int cpso, SO **apso, FX *afx);

void SolveSwGroup(SW *psw, int cpsoRoot, SO **apsoRoot, int cpxp, XP **apxp, float dt, GRFSG grfsg);

int CpxpBuildXpArray(int cpso, SO **apso, int cpxpMax, XP **apxp);

void BuildContactGroup(SO *psoSeed, int *pcpso, SO **apso, int *pcpsoLocked, SO **apsoLocked);

void SplitSoFreeze(SO *pso, int fFreeze);

void SortSwGroup(int cpso, SO **apso);

void SplitSwGroup(SW *psw, int cpso, SO **apso, float dt, GRFSG grfsg);

void SolveSw(SW *psw, float dt, GRFSG grfsg);

#endif // SOLVE_H
