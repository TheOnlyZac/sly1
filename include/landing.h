/**
 * @file landing.h
 */
#ifndef LANDING_H
#define LANDING_H

#include "common.h"
#include <shape.h>
#include <dl.h>

/**
 * @class LANDING
 * @brief Unknown.
 */
struct LANDING : public SHAPE
{
    undefined1 unknown[0x04];
    DLE dleLanding;
};

void OnLandingAdd(LANDING *planding);
void OnLandingRemove(LANDING *planding);
void CloneLanding(LANDING *planding, LANDING *plandingBase);

#endif // LANDING_H
