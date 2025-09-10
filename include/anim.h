/**
 * @file anim.h
 *
 * @brief Animation.
 *
 * @todo Implement structs.
 */
#ifndef ANIM_H
#define ANIM_H

#include "common.h"
#include <lo.h>

// Forward declarations.
struct ASEG;
struct ASEGA;
struct ASEGD;
struct ASEGBL;

/**
 * @class ANIMATION_SEGMENT
 * @brief Object representing an animation segment.
 */
struct ASEG : public LO
{
    // ...
};

/**
 * @class ANIMATION_SEGMENT_APPLICATION
 * @brief Unknown.
 */
struct ASEGA : public BASIC
{
    // ...
};

/**
 * @brief Animation segment something(?).
 */
struct ASEGD
{
    // ...
};

/**
 * @class ASEGBL
 * @brief Animation segment blend(?).
 */
struct ASEGBL : public ASEG
{
    // ...
};

#endif // ANIM_H
