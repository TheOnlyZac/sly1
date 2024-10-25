/**
 * @file gs.h
 *
 * @brief Graphics Synthesizer.
 */
#ifndef SCE_GS_H
#define SCE_GS_H

#include "common.h"

extern "C"
{
    struct sceGsTex0
    {
        undefined4 unk_0x0;
        undefined4 unk_0x4;
    };

    struct sceGsTex2
    {
        undefined4 unk_0x0;
        undefined4 unk_0x4;
    };
}

#endif // SCE_GS_H
