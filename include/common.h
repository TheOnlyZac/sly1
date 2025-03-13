/**
 * @file common.h
 *
 * @brief Common header file.
 */
#ifndef COMMON_H
#define COMMON_H

#include "include_asm.h"
#include "include_rodata.h"
#include "types.h"
#include "vtables.h"
#include "spaprops.h"

extern int _gpReg; // Global pointer register

/**
 * @brief RGBA color value.
 */
struct RGBA
{
    uchar bRed;
    uchar bGreen;
    uchar bBlue;
    uchar bAlpha;

    inline void operator=(const int rgba)
    {
        bRed = (rgba >> 24) & 0xFF;
        bGreen = (rgba >> 16) & 0xFF;
        bBlue = (rgba >> 8) & 0xFF;
        bAlpha = rgba & 0xFF;
    }
};

#endif /* COMMON_H */
