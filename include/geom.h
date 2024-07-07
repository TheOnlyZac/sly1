/**
 * @file geom.h
 *
 * @brief Geometry.
 */
#ifndef GEOM_H
#define GEOM_H

#include "common.h"

/**
 * @brief Edge
 *
 * Represents an edge in a geometry.
 */
struct EDGE
{
    ushort aipos[2];
    ushort aisurf[2];
    EDGE *pedgeNext;
    EDGE *pedgeOtherNext;
};

/**
 * @brief Geometry

 *
 * @todo Implement struct.
 */
struct GEOM
{
    // ...
};

#endif // GEOM_H
