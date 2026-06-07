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
    // The fields below 0x550 belong to the SO base, but the engine's base
    // structs are not yet fully reversed (SO is currently truncated), so they
    // are laid out here via padding to land at their true absolute offsets.
    STRUCT_PADDING(36); // 0x2d0 .. 0x360
    /* 0x360 */ float unk_0x360;
    /* 0x364 */ float unk_0x364;
    /* 0x368 */ float mass;
    STRUCT_PADDING(25); // 0x36c .. 0x3d0
    /* 0x3d0 */ float sRadiusBounds;
    /* 0x3d4 */ float unk_0x3d4;
    STRUCT_PADDING(18); // 0x3d8 .. 0x420
    /* 0x420 */ VECTOR4 vecBoundsMin;
    /* 0x430 */ VECTOR4 vecBoundsMax;
    STRUCT_PADDING(62); // 0x440 .. 0x538
    /* 0x538 */ uint64_t grfso;
    STRUCT_PADDING(4); // 0x540 .. 0x550
    /* 0x550 */ XA *pxaFirst;
    /* 0x554 */ MRG mrg;
    STRUCT_PADDING(3); // 0x564 .. 0x570
    /* 0x570 */ VU_VECTOR vecCurrent;
    STRUCT_PADDING(1); // 0x580 .. 0x584
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
