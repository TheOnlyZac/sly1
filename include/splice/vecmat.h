/**
 * @file splice/vecmat.h
 */
#ifndef SPLICE_VECMAT_H
#define SPLICE_VECMAT_H

#include "common.h"
#include <vec.h>
#include <mat.h>
#include <util.h>

VECTOR *PvectorNew();

void IncrefVector(VECTOR *pvector);

void DecrefVector(VECTOR *pvector);

MATRIX4 *PmatrixNew();

void IncrefMatrix(MATRIX4 *pmatrix);

void DecrefMatrix(MATRIX4 *pmatrix);

CLQ *PclqNew();

void IncrefClq(CLQ *pclq);

void DecrefClq(CLQ *pclq);

LM *PlmNew();

void IncrefLm(LM *plm);

void DecrefLm(LM *plm);

SMP *PsmpNew();

void IncrefSmp(SMP *psmp);

void DecrefSmp(SMP *psmp);

void StartupSpliceStructuredTypeFactories();

void ShutdownSpliceStructuredTypeFactories();

#endif // SPLICE_VECMAT_H
