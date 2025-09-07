/**
 * @file shape.h
 */
#ifndef SHAPE_H
#define SHAPE_H

#include "common.h"
#include <crv.h>
#include <lo.h>
#include <dl.h>

/**
 * @brief Unknown.
 */
struct SHAPE : public LO
{
    CRV *pcrv;
    DLE dleShape;
};

#endif // SHAPE_H
