/**
 * @file bez.h
 *
 * @brief Bezier curves.
 *
 * @todo Add documentation.
 */
#ifndef BEZ_H
#define BEZ_H

#include "common.h"
#include <vec.h>
#include <mat.h>

void EvaluateBezierWeightedFloat(float dtSeg, float tSeg, float svt, float g0, float dt0, float gCP0, float g1, float dt1, float gCP1, float *pg, float *pdg, float *pddg);

void EvaluateBezierFloat(float dtSeg, float tSeg, float svt, float g0, float gSlope0, float g1, float gSlope1, float *pg, float *pdg, float *pddg);

void EvaluateBezierPos(float dtSeg, float tSeg, float svt, VECTOR *ppos0, VECTOR *pv0, VECTOR *ppos1, VECTOR *pv1, VECTOR *ppos, VECTOR *pv, VECTOR *pdv);

void EvaluateBezierMat(float dtSeg, float tSeg, float svt, MATRIX3 *pmat0, VECTOR *pw0, MATRIX3 *pmat1, VECTOR *pw1, MATRIX3 *pmat, VECTOR *pw, VECTOR *pdw);

void TesselateBezier(float dtSeg, float tStart, float tEnd, VECTOR *ppos0, VECTOR *pv0, VECTOR *ppos1, VECTOR *pv1, int cpos, VECTOR *apos);

float SBezierPosLength(float dtSeg, float tSeg, VECTOR *ppos0, VECTOR *pv0, VECTOR *ppos1, VECTOR *pv1);

void LimitBezierMulti(int c);

#endif // BEZ_H
