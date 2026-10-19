/**
 * @file include/sdk/ee/libipu.h
 *
 * @brief Image Processing Unit library.
 */
#ifndef SCE_LIBIPU_H
#define SCE_LIBIPU_H

#include "types.h"

extern "C"
{
    /**
     * @brief 16x16 macroblock decoded RGB32 pixel buffer (256 pixels).
     */
    struct sceIpuRGB32 {
        uint pix[256];
    };
}

#endif // SCE_LIBIPU_H
