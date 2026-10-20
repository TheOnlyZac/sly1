/**
 * @file asega.h
 */
#ifndef ASEGA_H
#define ASEGA_H

#include "common.h"
#include <basic.h>
#include <dl.h>

// Forward.
struct ACTSEG;

/**
 * @class ANIMATION_SEGMENT_APPLICATION
 * @brief Unknown.
 */
struct ASEG;

struct ASEGA : public BASIC
{
    /* 0x08 */ ASEG *paseg;
    /* 0x0c */ ALO *paloRoot;
    /* 0x10 */ STRUCT_PADDING(5);
    /* 0x24 */ char fHandsOff;
    /* 0x25 */ undefined1 unk1;
    /* 0x26 */ undefined1 unk2;
    /* 0x27 */ undefined1 unk3;
    /* 0x28 */ ACTSEG *pactsegError;
    /* 0x2c */ STRUCT_PADDING(6);
    /* 0x44 */ DL dlActseg;
    // ...
};

// ...

void RetractAsega(ASEGA *pasega);
void SubscribeAsegaObject(ASEGA *pasega, LO *plo);

#endif // ASEGA_H
