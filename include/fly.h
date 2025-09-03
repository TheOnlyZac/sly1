/**
 * @file fly.h
 *
 * @brief Flying animals.
 */
#ifndef FLY_H
#define FLY_H

#include "common.h"
#include <target.h>
#include <flash.h>
#include <sound.h>
#include <bis.h>
#include <vec.h>
#include <cm.h>
#include <dl.h>
#include <so.h>

// Forward.
struct WKR;
struct SOP;

/**
 * @brief Flying animal kind.
 */
enum FLYK
{
    FLYK_Nil = -1,
    FLYK_Insect = 0,
    FLYK_Pigeon = 1,
    FLYK_Max = 2
};

/**
 * @brief Flying animal state.
 */
enum FLYS
{
    FLYS_Nil = -1,
    FLYS_Wander = 0,
    FLYS_Dying = 1,
    FLYS_Dead = 2,
    FLYS_Attract = 3,
    FLYS_Stuck = 4,
    FLYS_Land = 5,
    FLYS_Ground = 6,
    FLYS_Max = 7
};

/**
 * @brief Flying animal.
 */
struct FLY : public SO
{
    // ...
    FLYK flyk;
    FLYS flys;
    float tFlys;
    float tFlysnext;
    FLYS flysInit;
    int cpaloRender;
    int ipaloRender;
    ALO *apaloRender[16];
    int cpaloRenderGround;
    ALO *apaloRenderGround[8];
    ALO *paloRenderDead;
    EXPL *pexpl;
    TARGET *ptarget;
    DLE dleFly;
    AMB *pambBuzz;
    // ...
};

void InitFly(FLY *pfly);

void LoadFlyFromBrx(FLY *pfly, CBinaryInputStream *pbis);

void CloneFly(FLY *pfly, FLY *pflyBase);

void FreezeFly(FLY *pfly, int fFreeze);

void PostFlyLoad(FLY *pfly);

void PresetFlyAccel(FLY *pfly, float dt);

void UpdateFly(FLY *pfly, float dt);

void RenderFlySelf(FLY *pfly, CM *pcm, RO *pro);

int FAbsorbFlyWkr(FLY *pfly, WKR *pwkr);

void GetFlyParams(FLY *pfly, SOP **ppsop);

void SetFlyFlys(FLY *pfly, FLYS flys);

void EmitFlyDroppings(FLY *pfly);

int FFindFlyClosestLandingPos(FLY *pfly, VECTOR *ppos);

FLYS FlysAttemptedFlyLanding(FLY *pfly);

int FShouldFlyFlee(FLY *pfly);

int FFilterFly(void *pv, SO *pso);

int FCheckFlyOpenSpaceBelow(FLY *pfly);

#endif // FLY_H
