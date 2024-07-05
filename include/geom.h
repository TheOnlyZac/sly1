/**
 * @file geom.h
 */
#ifndef GEOM_H
#define GEOM_H

#include "common.h"

struct EDGE
{
    ushort aipos[2];
    ushort aisurf[2];
    EDGE *pedgeNext;
    EDGE *pedgeOtherNext;
};

#endif // GEOM_H
