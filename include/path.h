/**
 * @file path.h
 */
#ifndef PATH_H
#define PATH_H

#include "common.h"

struct CG;
struct VECTOR;

int CposFindPath(CG *pcg, VECTOR *pvec0, VECTOR *pvec1, int n, VECTOR *pvec2);

void FindClosestPointInCg(CG *pcg, VECTOR *pvec0, VECTOR *pvec1);

#endif // PATH_H
