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

//todo implement structs
struct TSURF;
struct TBSP;

struct VOL : public XFM
{
    int ctsurf;
    TSURF *atsurf;
    int ctbsp;
    TBSP *atbsp;
};

#endif // VOL_H
