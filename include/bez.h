/**
 * @file bez.h
 *
 * @brief Bezier curves.
 *
 * @todo Add function parameters and documentation.
 */
#ifndef BEZ_H
#define BEZ_H

#include "common.h"
#include <vec.h>
#include <mat.h>

void EvaluateBezierWeightedFloat(float, float, float, float, float, float, float, float, float, float *, float *, float *);
void EvaluateBezierFloat(float, float, float, float, float, float, float, float *, float *, float *);
void EvaluateBezierPos(float, float, float, VECTOR *, VECTOR *, VECTOR *, VECTOR *, VECTOR *, VECTOR *, VECTOR *);
void EvaluateBezierMat(float, float, float, MATRIX3 *, VECTOR *, MATRIX3 *, VECTOR *, MATRIX3 *, VECTOR *, VECTOR *);
void TesselateBezier(float, float, float, VECTOR *, VECTOR *, VECTOR *, VECTOR *, int, VECTOR *);
float SBezierPosLength(float, float, VECTOR *, VECTOR *, VECTOR *, VECTOR *);

void LimitBezierMulti(int c, ...);

#endif // BEZ_H
