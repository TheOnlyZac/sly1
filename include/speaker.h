/**
 * @file speaker.h
 *
 * @brief Sound speaker management.
 */
#ifndef SPEAKER_H
#define SPEAKER_H

#include "common.h"
#include <alo.h>

/**
 * @class SPEAKER
 * @brief Sound speaker.
 * @todo Implement the struct.
 */
struct SMA;

struct SPEAKER : public ALO
{
    /* 0x2d0 */ RGBA rgbaText;
    /* 0x2d4 */ STRUCT_PADDING(24);
    /* 0x334 */ SMA *psmaIdle;
};

// ...

#endif // SPEAKER_H
