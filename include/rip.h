/**
 * @file rip.h
 *
 * @brief Particle system (?)
 */
#ifndef RIP_H
#define RIP_H

#include "common.h"
#include <blip.h>
#include <vec.h>
#include <so.h>
#include <lo.h>
#include <cm.h>

// Forward.
struct RO;

// TODO: Does this belong here or puffer.h?
struct PUFF;

// TODO: Add to vtables.
struct VTRIP;

/**
 * @brief (?) particle type?
 * @note All of these values are taken straight
 * from the prototype so they may be incorrect.
 */
enum RIPT
{
    RIPT_Nil = -1,
    RIPT_Rip = 0,
    RIPT_Shadow = 1,
    RIPT_Droplet = 2,
    RIPT_Bublet = 3,
    RIPT_Ripple = 4,
    RIPT_Puff = 5,
    RIPT_Dablet = 6,
    RIPT_Flake = 7,
    RIPT_Spark = 8,
    RIPT_Burst = 9,
    RIPT_Trail = 10,
    RIPT_Fireball = 11,
    RIPT_SmokeCloud = 12,
    RIPT_SmokeTrail = 13,
    RIPT_Debris = 14,
    RIPT_Orbit = 15,
    RIPT_Smack = 16,
    RIPT_Ray = 17,
    RIPT_Rose = 18,
    RIPT_Flying = 19,
    RIPT_Stuck = 20,
    RIPT_Leaf = 21,
    RIPT_Flame = 22,
    RIPT_Bullet = 23,
    RIPT_Shrapnel = 24,
    RIPT_Glint = 25,
    RIPT_Match = 26,
    RIPT_Emitter = 27,
    RIPT_Max = 28
};

/**
 * @brief (?) type?
 */
enum RIPGT
{
    RIPGT_Nil = -1,
    RIPGT_Default = 0,
    RIPGT_Bounce = 1,
    RIPGT_Loot = 2,
    RIPGT_Max = 3
};

/**
 * @brief Rose state.
 */
enum ROSES
{
    ROSES_Nil = -1,
    ROSES_Closing = 0,
    ROSES_Spinning = 1,
    ROSES_Opening = 2,
    ROSES_Max = 3
};

/**
 * @brief Unknown.
 */
enum TRLS
{
    TRLS_Nil = -1,
    TRLS_None = 0,
    TRLS_TrackingRip = 1,
    TRLS_TrackingAlo = 2,
    TRLS_ChainingRip = 3,
    TRLS_Max = 4
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct RIP
{
    // ...
};

/**
 * @brief (?) group?
 * @todo Implement the struct.
 */
struct RIPG : public SO
{
    // ...
};

/**
 * @brief Rose.
 * @todo Implement the struct.
 */
struct ROSE : public RIP
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct DROPLET : public RIP
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct BUBLET : public RIP
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct RIPPLE : public RIP
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct DABLET : public RIP
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct FLAKE : public RIP
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct SPARK : public RIP
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct BURST : public RIP
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct TRAIL : public RIP
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct FIREBALL : public RIP
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct SMOKETRAIL : public TRAIL
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct DEBRIS : public RIP
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct SMOKECLOUD : public RIP
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct SMACK : public RIP
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct ORBIT : public RIP
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct RAY : public SPARK
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct FLYING : public RIP
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct STUCK : public RIP
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct LEAF : public RIP
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct FLAME : public RIP
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct BULLET : public RIP
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct SHRAPNEL : public RIP
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct GLINT : public RIP
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct MATCH : public RIP
{
    // ...
};

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct REMIT : public RIP
{
    // ...
};

/**
 * @brief Unknown.
 */
struct HP
{
    VECTOR pos;
    VECTOR posHull;
    float radHull;
    float sEdge;
    float sCorner;
    int xhpKey;
};

RIPG *PripgNew(SW *psw, RIPGT ripgt);

void InitRipg(RIPG *pripg);

void SetRipgEmitb(RIPG *pripg, EMITB *pemitb);

void OnRipgRemove(RIPG *pripg);

void ProjectRipgTransform(RIPG *pripg, float dt, int fForce);

void UpdateRipgBounds(RIPG *pripg);

void UpdateRipg(RIPG *pripg, float dt);

void BounceRipgRips(RIPG *pripg);

void RenderRipgSelf(RIPG *pripg, CM *pcm, RO *pro);

VTRIP *PvtripFromRipt(RIPT ript);

RIP *PripNewRipg(RIPT ript, RIPG *pripg);

void InitRip(RIP *prip, VECTOR *ppos, float gScale, SO *psoTouch);

void RemoveRip(RIP *prip);

void AddRipRef(RIP *prip);

void ReleaseRip(RIP *prip);

void TouchRip(RIP *prip, int fTouching);

void ForceRipFade(RIP *prip, float dtFade);

int FBounceRip(RIP *prip, SO *psoOther, VECTOR *ppos, VECTOR *pnormal);

void ProjectRipTransform(RIP *prip, float dt);

void UpdateRip(RIP *prip, float dt);

int FRenderRipPosMat(RIP *prip, CM *pcm, VECTOR *ppos, MATRIX3 *pmat);

void RenderRip(RIP *prip, CM *pcm);

void SubscribeRipObject(RIP *prip, LO *ploTarget);

void SubscribeRipStruct(RIP *prip, PFNMQ pfnmq, void *pvContext);

void UnsubscribeRipStruct(RIP *prip, PFNMQ pfnmq, void *pvContext);

void InitDroplet(DROPLET *pdroplet, VECTOR *ppos, float gScale, SO *psoTouch);

void TouchDroplet(DROPLET *pdroplet, int fTouching);

void InitBublet(BUBLET *pbublet, VECTOR *ppos, float gScale, SO *psoTouch);

void ProjectBubletTransform(BUBLET *pbublet, float dt);

void TouchBublet(BUBLET *pbublet, int fTouching);

void InitRipple(RIPPLE *pripple, VECTOR *ppos, float gScale, SO *psoTouch);

void InitPuff(PUFF *ppuff, VECTOR *ppos, float gScale, SO *psoTouch);

void InitDablet(DABLET *pdablet, VECTOR *ppos, float gScale, SO *psoTouch);

void InitFlake(FLAKE *pflake, VECTOR *ppos, float gScale, SO *psoTouch);

void UpdateFlake(FLAKE *pflake, float dt);

void RenderFlake(FLAKE *pflake, CM *pcm);

void TouchFlake(FLAKE *pflake, int fTouching);

void InitSpark(SPARK *pspark, VECTOR *ppos, float gScale, SO *psoTouch);

void RenderSpark(SPARK *pspark, CM *pcm);

void InitBurst(BURST *pburst, VECTOR *ppos, float gScale, SO *psoTouch);

void InitTrail(TRAIL *ptrail, VECTOR *ppos, float gScale, SO *psoTouch);

void OnTrailRemove(TRAIL *ptrail);

void SetTrailTrls(TRAIL *ptrail, TRLS trls, void *pv);

void DetachTrail(TRAIL *ptrail);

void ProjectTrailTransform(TRAIL *ptrail, float dt);

void RenderTrail(TRAIL *ptrail, CM *pcm);

void HandleTrailMessage(TRAIL *ptrail, MSGID msgid, void *pv);

void InitFireball(FIREBALL *pfireball, VECTOR *ppos, float gScale, SO *psoTouch);

void UpdateFireball(FIREBALL *pfireball, float dt);

void InitSmokecloud(SMOKECLOUD *psmokecloud, VECTOR *ppos, float gScale, SO *psoTouch);

void InitSmoketrail(SMOKETRAIL *psmoketrail, VECTOR *ppos, float gScale, SO *psoTouch);

void InitDebris(DEBRIS *pdebris, VECTOR *ppos, float gScale, SO *psoTouch);

void InitSmack(SMACK *psmack, VECTOR *ppos, float gScale, SO *psoTouch);

void ProjectSmackTransform(SMACK *psmack, float dt);

void RenderSmack(SMACK *psmack, CM *pcm);

void UpdateSmack(SMACK *psmack, float dt);

void InitOrbit(ORBIT *porbit, VECTOR *ppos, float gScale, SO *psoTouch);

void ProjectOrbitTransform(ORBIT *porbit, float dt);

void UpdateOrbit(ORBIT *porbit, float dt);

void RenderOrbit(ORBIT *porbit, CM *pcm);

void InitRay(RAY *pray, VECTOR *ppos, float gScale, SO *psoTouch);

void InitRose(ROSE *prose, VECTOR *ppos, float gScale, SO *psoTouch);

void ProjectRoseTransform(ROSE *prose, float dt);

void UpdateRose(ROSE *prose, float dt);

void RenderRose(ROSE *prose, CM *pcm);

void SetRoseRoses(ROSE *prose, ROSES roses);

int SgnCmpHp(void *pv0, void *pv1);

int ChpBuildConvexHullScreen(VECTOR *pposCenter, int chp, HP *ahp);

int ChpBuildConvexHullXY(MATRIX4 *pdmat, int chp, HP *ahp);

void PostFlyingEmit(FLYING *pflying, EMITB *pemitb);

void RenderFlying(FLYING *pflying, CM *pcm);

void CreateStuck(RIP *pripSrc, ALO *paloRender, SO *psoOther, VECTOR *ppos, VECTOR *pnormal, STUCK **ppstuck);

int FBounceFlying(FLYING *pflying, SO *psoOther, VECTOR *ppos, VECTOR *pnormal);

void UpdateStuck(STUCK *pstuck, float dt);

void RenderStuck(STUCK *pstuck, CM *pcm);

void PostLeafEmit(LEAF *pleaf, EMITB *pemitb);

void ProjectLeafTransform(LEAF *pleaf, float dt);

int FBounceLeaf(LEAF *pleaf, SO *psoOther, VECTOR *ppos, VECTOR *pnormal);

int FFilterFlameObjects(void *pv, SO *pso);

void PostFlameEmit(FLAME *pflame, EMITB *pemitb);

void PostBulletEmit(BULLET *pbullet, EMITB *pemitb);

void RenderBullet(BULLET *pbullet, CM *pcm);

int FBounceBullet(BULLET *pbullet, SO *psoOther, VECTOR *ppos, VECTOR *pnormal);

void PostShrapnelEmit(SHRAPNEL *pshrapnel, EMITB *pemitb);

int FBounceShrapnel(SHRAPNEL *pshrapnel, SO *psoOther, VECTOR *ppos, VECTOR *pnormal);

void RenderShrapnel(SHRAPNEL *pshrapnel, CM *pcm);

void InitGlint(GLINT *pglint, VECTOR *ppos, float gScale, SO *psoTouch);

void RenderGlint(GLINT *pglint, CM *pcm);

void InitMatch(MATCH *pmatch, VECTOR *ppos, float gScale, SO *psoTouch);

void LaunchMatch(MATCH *pmatch);

void ProjectMatchTransform(MATCH *pmatch, float dt);

void UpdateMatch(MATCH *pmatch, float dt);

void RenderMatch(MATCH *pmatch, CM *pcm);

void PostRemitEmit(REMIT *premit, EMITB *pemitb);

void UpdateRemit(REMIT *premit, float dt);

#endif // RIP_H
