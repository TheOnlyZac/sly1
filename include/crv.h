/**
 * @file crv.h
 */
#ifndef CRV_H
#define CRV_H

#include "common.h"
#include <vec.h>

/**
 * @brief (?) kind.
 */
enum CRVK
{
    CRVK_Nil = -1,
    CRVK_Linear = 0,
    CRVK_Cubic = 1,
    CRVK_Max = 2
};

/**
 * @brief Unknown.
 */
struct CRV
{
    undefined4 unknown;
    CRVK crvk;
    int fClosed;
    int ccv;
    float *mpicvu;
    float *mpicvs;
    VECTOR *mpicvpos;
};

// ...

#endif // CRV_H
