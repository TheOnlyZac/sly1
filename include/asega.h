/**
 * @file asega.h
 */
#ifndef ASEGA_H
#define ASEGA_H

#include "common.h"
#include <basic.h>

/**
 * @class ANIMATION_SEGMENT_APPLICATION
 * @brief Unknown.
 */
struct ASEGA : public BASIC
{
    /* 0x08 */ STRUCT_PADDING(7);
    /* 0x24 */ char fHandsOff;
    // ...
};

// ...

void RetractAsega(ASEGA *pasega);

#endif // ASEGA_H
