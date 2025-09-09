/**
 * @file keyhole.h
 */
#ifndef KEYHOLE_H
#define KEYHOLE_H

#include "common.h"
#include <bis.h>
#include <lo.h>

/**
 * @brief Key hole.
 * @todo Implement the struct.
 */
struct KEYHOLE : public LO
{
    // ...
};

void InitKeyhole(KEYHOLE *pkeyhole);

void LoadKeyholeFromBrx(KEYHOLE *pkeyhole, CBinaryInputStream *pbis);

void DrawKeyholeMask(KEYHOLE *pkeyhole, float x, float y, float rScale, float uAlpha);

void DrawKeyhole(KEYHOLE *pkeyhole, float uClosed);

#endif // KEYHOLE_H
