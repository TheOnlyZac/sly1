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
 * @brief Animation segment.
 */
struct ASEG : public LO
{
    // ...
};

/**
 * @brief Animation segment something(?).
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
 * @brief Animation segment blend.
 */
struct ASEGBL : public ASEG
{
    // ...
};

#endif // ANIM_H
