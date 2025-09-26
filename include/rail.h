/**
 * @file rail.h
 */
#ifndef RAIL_H
#define RAIL_H

#include "common.h"
#include <shape.h>
#include <dl.h>

/**
 * @class RAIL
 * @brief Rail that JT can walk/slide on.
 * @todo Check if the field names are correct.
 */
struct RAIL : public SHAPE
{
    /* 0x38 */ DLE dleRail;
    /* 0x40 */ int fSlippery;
    /* 0x44 */ float svMax;
    /* 0x48 */ float rdvGravity;
    /* 0x4c */ float unk1;
    /* 0x50 */ undefined4 unk2;
    /* 0x54 */ OID oid;
    /* 0x58 */ LO *plo;
};

void InitRail(RAIL *prail);

void OnRailAdd(RAIL *prail);

void OnRailRemove(RAIL *prail);

void PostLoadRail(RAIL *prail);

void CloneRail(RAIL *prail, RAIL *prailBase);

#endif // RAIL_H
