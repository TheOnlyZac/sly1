/**
 * @file surf.h
 *
 * @brief Surface?
 */
#ifndef SURF_H
#define SURF_H

#include "common.h"
#include <vec.h>
#include <geom.h>

// todo define struct
struct TBSP;

struct SUR
{
    int cb;
    void *pvSrc;
    void *pvDst;
    int cvtx;
};

struct SURF
{
    VECTOR normal;
    float gDot;
    EDGE *pedge;
    EDGE *pedgeOther;
    short grfsurf;
    short ipos;
};

struct TSURF
{
    float gDot;
    undefined4 unk1;
    undefined4 unk2;
    undefined4 unk3;
    VECTOR normal;
};

#endif // SURF_H
