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
 * 
*/
void ClearFrameBuffers();

#endif // GS_H
