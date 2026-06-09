/**
 * @file water.h
 *
 * @brief Good ol' H20.
 */
#ifndef WATER_H
#define WATER_H

#include "common.h"
#include <zap.h>
#include <vec.h>
#include <so.h>
#include <mq.h>
#include <freeze.h>

// Forward.
struct XA;
struct XP;

/**
 * @class WATER
 * @brief Water?
 */
struct WATER : public SO
{
    // The span 0x2d0..0x550 holds SO base fields that live past the currently
    // truncated SO size. Rather than redeclare them here (which would pin this
    // struct to the present sizeof(SO) and break the checksum if SO grows),
    // they are reached via STRUCT_OFFSET from water.c until the base structs
    // are fully reversed. WATER's own fields begin at 0x550.
    STRUCT_PADDING(160); // 0x2d0 .. 0x550
    /* 0x550 */ XA *pxaFirst;
    /* 0x554 */ MRG mrg;
    STRUCT_PADDING(8); // 0x564 .. 0x584
    /* 0x584 */ int unk_0x584;
    /* 0x588 */ int unk_0x588;
    STRUCT_PADDING(1); // 0x58c .. 0x590
    /* 0x590 */ ZPD zpd;
};

void InitWater(WATER *pwater);

void PostWaterLoad(WATER *pwater);

void CalculateWaterCurrent(WATER *pwater, VECTOR *ppos, VECTOR *pv, VECTOR *pw);

void UpdateSwXaList(SW *psw, XA **ppxa);

void UpdateWater(WATER *pwater, float dt);

void AddWaterExternalAccelerations(WATER *pwater, XA *pxa, float dt);

void HandleWaterMessage(WATER *pwater, MSGID msgid, void *pv);

void UpdateWaterMergeGroup(WATER *pwater);

float UGetWaterSubmerged(WATER *pwater, SO *pso, VECTOR *pposSurface, VECTOR *pnormalSurface);

void UpdateWaterBounds(WATER *pwater);

int FInflictWaterZap(WATER *pwater, XP *pxp, ZPR *pzpr);

ZPD *PzpdEnsureWater(WATER *pwater, ENSK ensk);

#endif // WATER_H
