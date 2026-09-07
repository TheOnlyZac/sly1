/**
 * @file hide.h
 */
#ifndef HIDE_H
#define HIDE_H

#include "common.h"
#include <shape.h>
#include <vec.h>
#include <bis.h>
#include <so.h>

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
    // ...
};

/**
 * @brief Unknown.
 */
struct HPNT : public PNT
{
    // ...
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

void InitHshape(HSHAPE *phshape);

void OnHshapeAdd(HSHAPE *phshape);

void OnHshapeRemove(HSHAPE *phshape);

void BindHshape(HSHAPE *phshape);

void CloneHshape(HSHAPE *phshape, HSHAPE *phshapeBase);

void GetHshapeHidePos(HSHAPE *phshape, float sParam, VECTOR *pposHide, float *pradTarget);

void GetHshapeClosestHidePos(HSHAPE *phshape, float *psParamHshape, VECTOR *pposHide, float *pradTarget);

void InitHpnt(HPNT *phpnt);

void OnHpntAdd(HPNT *phpnt);

void OnHpntRemove(HPNT *phpnt);

void BindHpnt(HPNT *phpnt);

void CloneHpnt(HPNT *phpnt, HPNT *phpntBase);

void GetHpntClosestHidePos(HPNT *phpnt, VECTOR *ppos, float *pradTarget);

void InitHbsk(HBSK *phbsk);

void LoadHbskFromBrx(HBSK *phbsk, CBinaryInputStream *pbis);

void OnHbskAdd(HBSK *phbsk);

void OnHbskRemove(HBSK *phbsk);

void CloneHbsk(HBSK *phbsk, HBSK *phbskBase);

int FIgnoreHbskIntersection(HBSK *phbsk, SO *psoOther);

void PresetHbskAccel(HBSK *phbsk, float dt);

void SetHbskHbsks(HBSK *phbsk, HBSKS hbsks);

int CdartStuckHbsk(HBSK *phbsk);

DART *PdartOldestHbskStuck(HBSK *phbsk);

void GetHbskClosestHidePos(HBSK *phbsk, VECTOR *ppos, float *prad);

#endif // HIDE_H
