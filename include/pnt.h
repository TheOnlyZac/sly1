/**
 * @file pnt.h
 *
 * @brief Points.
 */
#ifndef PNT_H
#define PNT_H

#include "common.h"
#include <proxy.h>
#include <vec.h>
#include <bis.h>
#include <alo.h>
#include <lo.h>

/**
 * @class POINT
 * @brief Object defined only by a point in space.
 */
struct PNT : public LO
{
    /* 0x34 */ STRUCT_PADDING(3); // This could be a vector, something like posGlobal?
    /* 0x40 */ VECTOR posLocal;
};

/**
 * @class POINT_WITH_SPEED
 * @brief Object defined by a point in space with a velocity.
 */
struct PNTSV : PNT
{
    // ...
};

/**
 * @class POINT_WITH_DISTANCE
 * @brief Object defined by a point in space with a distance.
 */
struct PNTS : PNT
{
    // ...
};

/**
 * @class POINT_WITH_VECTOR
 * @brief Object defined by a point in space with a vector.
 */
struct PNTVEC : PNT
{
    // ...
};

void LoadPntFromBrx(PNT *ppnt, CBinaryInputStream *pbis);

void GetPntPos(PNT *ppnt, VECTOR *ppos);

void SetPntParent(PNT *ppnt, ALO *paloParent);

void ApplyPntProxy(PNT *ppnt, PROXY *pproxyApply);

#endif // PNT_H
