/**
 * @file hide.h
 */
#ifndef HIDE_H
#define HIDE_H

#include "common.h"

/**
 * @todo Implement the HPNT and HSHAPE structs.
 */
struct HPNT;
struct HSHAPE;
struct VECTOR;

// ...

void StartupHide();

void GetHshapeHidePos(HSHAPE *phshape, float s, VECTOR *ppos, float *pf);

void GetHpntClosestHidePos(HPNT *phpnt, VECTOR *ppos, float *pf);

#endif // HIDE_H
