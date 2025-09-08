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
 * @brief Point.
 */
struct PNT : public LO
{
    VECTOR posLocal;
};

void LoadPntFromBrx(PNT *ppnt, CBinaryInputStream *pbis);

void GetPntPos(PNT *ppnt, VECTOR *ppos);

void SetPntParent(PNT *ppnt, ALO *paloParent);

void ApplyPntProxy(PNT *ppnt, PROXY *pproxyApply);

#endif // PNT_H
