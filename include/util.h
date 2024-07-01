/**
 * @file util.h
 *
 * @brief Declarations for utility functions.
*/
#ifndef UTIL_H
#define UTIL_H

#include "common.h"

/**
 * @brief Limits for a float.
*/
struct LM
{
	float gMin, gMax;
};

/**
 * @brief Vector struct.
*/
struct VECTOR {
	float x, y, z, gUnused;
};

/**
 * @brief Checks if a float falls within the given limit.
 *
 * @param plm Pointer to the limit
 * @param g The float to check
*/
int FCheckLm(LM* plm, float g);

/**
 * @brief Stubbed function, does nothing.
*/
void Force(void *pv);

#endif // UTIL_H
