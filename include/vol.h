/**
 * @file vol.h
 *
 * @brief Volume object.
 *
 * @note Not referenced in any debug symbols, but it doesn't make sense
 * to put the VOL struct anywhere else.
 */
#ifndef VOL_H
#define VOL_H

#include "common.h"
#include <xform.h>

/**
 * @class VOLUME
 * @brief Volume in space defined by transform, tsurf, and tbsp.
 */
struct VOL : public XFM
{
    int ctsurf;
    TSURF *atsurf;
    int ctbsp;
    TBSP *atbsp;
};

#endif // VOL_H
