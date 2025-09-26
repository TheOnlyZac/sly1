/**
 * @file shape.h
 */
#ifndef SHAPE_H
#define SHAPE_H

#include "common.h"
#include <crv.h>
#include <bis.h>
#include <alo.h>
#include <lo.h>
#include <dl.h>

/**
 * @class SHAPE
 * @brief Unknown.
 */
struct SHAPE : public LO
{
    CRV *pcrv;
};

void LoadShapeFromBrx(SHAPE *pshape, CBinaryInputStream *pbis);

void SetShapeParent(SHAPE *pshape, ALO *paloParent);

#endif // SHAPE_H
