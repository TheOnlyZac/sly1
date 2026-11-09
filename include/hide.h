/**
 * @file hide.h
 */
#ifndef HIDE_H
#define HIDE_H

#include "common.h"
#include <shape.h>
#include <vec.h>
#include <bis.h>
#include <pnt.h>
#include <so.h>
#include <dl.h>
#include <find.h>

/**
 * @brief Unknown.
 */
enum HBSKS
{
    HBSKS_Nil = -1,
    HBSKS_Available = 0,
    HBSKS_InUse = 1,
    HBSKS_Max = 2,
};

/**
 * @brief Hide shape?
 */
struct HSHAPE : public SHAPE
{
    /* 0x38 */ DLE dleHshape;
    /* 0x40 */ STRUCT_PADDING(1);
    /* 0x44 */ OID oidTarget;
    /* 0x48 */ LO *ploTarget;
    /* 0x4c */ int unk4c;
    /* 0x50 */ int unk50;
    /* 0x54 */ STRUCT_PADDING(1);
    /* 0x58 */ float unk58;
};

/**
 * @brief Unknown.
 */
struct HPNT : public PNT
{
    /* 0x50 */ DLE dleHpnt;
    /* 0x58 */ STRUCT_PADDING(2);
    /* 0x60 */ OID oidTarget;
    /* 0x64 */ LO *ploTarget;
    /* 0x68 */ int unk68;
    /* 0x6c */ STRUCT_PADDING(1);
    /* 0x70 */ float unk70;
};

/**
 * @brief Unknown.
 */
struct HBSK : public SO
{
    // ...
};

// Forward declaration.
struct DART;

void StartupHide();

void ResetHideList();

/**
 * @brief Initializes a hide shape with defaults (no target, flags 1 and 3, and a max float limit).
 *
 * @param phshape Hide shape to initialize.
 */
void InitHshape(HSHAPE *phshape);

/**
 * @brief Adds the hide shape to the global hide list when it is added to the world.
 */
void OnHshapeAdd(HSHAPE *phshape);

/**
 * @brief Removes the hide shape from the global hide list when it is removed from the world.
 */
void OnHshapeRemove(HSHAPE *phshape);

/**
 * @brief Looks up the target object by its OID and clears one of its fields.
 *
 * Does nothing if no target OID is set.
 *
 * @param phshape Hide shape to bind.
 */
void BindHshape(HSHAPE *phshape);

/**
 * @brief Clones a hide shape, keeping its own list entry.
 *
 * @param phshape Destination hide shape.
 * @param phshapeBase Hide shape to copy from.
 */
void CloneHshape(HSHAPE *phshape, HSHAPE *phshapeBase);

void GetHshapeHidePos(HSHAPE *phshape, float sParam, VECTOR *pposHide, float *pradTarget);

void GetHshapeClosestHidePos(HSHAPE *phshape, float *psParamHshape, VECTOR *pposHide, float *pradTarget);

/**
 * @brief Initializes a hide point with defaults (no target, one flag, and a max float limit).
 *
 * @param phpnt Hide point to initialize.
 */
void InitHpnt(HPNT *phpnt);

/**
 * @brief Adds the hide point to the global hide list when it is added to the world.
 */
void OnHpntAdd(HPNT *phpnt);

/**
 * @brief Removes the hide point from the global hide list when it is removed from the world.
 */
void OnHpntRemove(HPNT *phpnt);

/**
 * @brief Looks up the target object by its OID and clears one of its fields.
 *
 * Does nothing if no target OID is set.
 *
 * @param phpnt Hide point to bind.
 */
void BindHpnt(HPNT *phpnt);

/**
 * @brief Clones a hide point, keeping its own list entry.
 *
 * @param phpnt Destination hide point.
 * @param phpntBase Hide point to copy from.
 */
void CloneHpnt(HPNT *phpnt, HPNT *phpntBase);

void GetHpntClosestHidePos(HPNT *phpnt, VECTOR *ppos, float *pradTarget);

/**
 * @brief Initializes a hide basket with spring, damping and smoothing defaults.
 *
 * @param phbsk Hide basket to initialize.
 */
void InitHbsk(HBSK *phbsk);

void LoadHbskFromBrx(HBSK *phbsk, CBinaryInputStream *pbis);

/**
 * @brief Adds the hide basket to the global hide list when it is added to the world.
 */
void OnHbskAdd(HBSK *phbsk);

/**
 * @brief Removes the hide basket from the global hide list when it is removed from the world.
 */
void OnHbskRemove(HBSK *phbsk);

/**
 * @brief Clones a hide basket, keeping its own list entry.
 *
 * @param phbsk Destination hide basket.
 * @param phbskBase Hide basket to copy from.
 */
void CloneHbsk(HBSK *phbsk, HBSK *phbskBase);

/**
 * @brief Checks whether an intersection with another object should be ignored.
 *
 * Always ignored when the other object is the player (g_pjt) and this basket is the one it is in.
 *
 * @param phbsk Hide basket.
 * @param psoOther Object it is intersecting.
 * @return 1 to ignore the intersection, otherwise the generic SO result.
 */
int FIgnoreHbskIntersection(HBSK *phbsk, SO *psoOther);

void PresetHbskAccel(HBSK *phbsk, float dt);

void SetHbskHbsks(HBSK *phbsk, HBSKS hbsks);

int CdartStuckHbsk(HBSK *phbsk);

DART *PdartOldestHbskStuck(HBSK *phbsk);

void GetHbskClosestHidePos(HBSK *phbsk, VECTOR *ppos, float *prad);

#endif // HIDE_H
