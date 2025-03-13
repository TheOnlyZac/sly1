/**
 * @file gs.h
 *
 * @brief Graphics synthesizer.
 */
#ifndef GS_H
#define GS_H

#include "common.h"

struct GSB
{
   int igsMin;
   int igsMac;
   int igsMax;
};

/**
 * @brief Initializes a GSB with the given values.
 *
 * @param pgsb The GSB to initialize.
 * @param igsMin The minimum index.
 * @param igsMax The maximum index.
 */
void InitGsb(GSB *pgsb, int igsMin, int igsMax);

/**
 * @brief Resets the igsMac to the minimum index.
 *
 * @param pGsb The GSB to reset.
 */
void ResetGsb(GSB *pGsb);

/**
 * @brief Allocates a range of indices in the GSB.
 *
 * @param pgsb The GSB to allocate from.
 * @param iCount The number of indices to allocate.
 *
 * @return The old value of igsMac.
 */
int IgsAllocGsb(GSB *pgsb, int iCount);

/**
 *
*/
void ClearFrameBuffers();

#endif // GS_H
