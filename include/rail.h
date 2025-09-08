/**
 * @file rail.h
 */
#ifndef RAIL_H
#define RAIL_H

#include "common.h"
#include <shape.h>
#include <dl.h>

/**
 * @brief Rail.
 */
struct RAIL : public SHAPE
{
    undefined4 unknown;
    DLE dleRail;
    int fSlippery;
    float svMax;
    float rdvGravity;
};

void InitRail(RAIL *prail);

void OnRailAdd(RAIL *prail);

void OnRailRemove(RAIL *prail);

void PostLoadRail(RAIL *prail);

void CloneRail(RAIL *prail, RAIL *prailBase);

#endif // RAIL_H