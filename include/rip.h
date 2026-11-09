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
#include <find.h>

// Forward.
struct RO;
struct RIPG;

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
    STRUCT_PADDING(2);
    int cref;
    RIPG *pripg;
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
 * @brief Puff particle.
 * @todo Implement the struct.
 */
struct PUFF : public RIP
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

/**
 * @brief Forces a rip to finish fading within dtFade seconds if it would otherwise last longer.
 * @param prip Rip.
 * @param dtFade Maximum remaining time.
 * @note Fields +0x18 (start time) and +0x1c (lifetime) are inferred.
 */
void ForceRipFade(RIP *prip, float dtFade);

int FBounceRip(RIP *prip, SO *psoOther, VECTOR *ppos, VECTOR *pnormal);

void ProjectRipTransform(RIP *prip, float dt);

void UpdateRip(RIP *prip, float dt);

int FRenderRipPosMat(RIP *prip, CM *pcm, VECTOR *ppos, MATRIX3 *pmat);

void RenderRip(RIP *prip, CM *pcm);

/**
 * @brief Subscribes a rip's message queue to another object's message handler.
 * @param prip Rip.
 * @param ploTarget Object whose handler receives the messages.
 */
void SubscribeRipObject(RIP *prip, LO *ploTarget);

/**
 * @brief Subscribes a callback with context to a rip's message queue.
 * @param prip Rip.
 * @param pfnmq Message callback.
 * @param pvContext Context passed to the callback.
 */
void SubscribeRipStruct(RIP *prip, PFNMQ pfnmq, void *pvContext);

/**
 * @brief Unsubscribes a callback with context from a rip's message queue.
 * @param prip Rip.
 * @param pfnmq Message callback.
 * @param pvContext Context passed to the callback.
 */
void UnsubscribeRipStruct(RIP *prip, PFNMQ pfnmq, void *pvContext);

/**
 * @brief Initializes a droplet particle (InitDroplet).
 * @param pdroplet Particle to initialize.
 * @param ppos Starting position.
 * @param gScale Scale passed through to InitRip.
 * @param psoTouch Object the particle touches (passed through to InitRip).
 * @note Field meanings are guesses; the constants set here are not named.
 */
void InitDroplet(DROPLET *pdroplet, VECTOR *ppos, float gScale, SO *psoTouch);

void TouchDroplet(DROPLET *pdroplet, int fTouching);

void InitBublet(BUBLET *pbublet, VECTOR *ppos, float gScale, SO *psoTouch);

void ProjectBubletTransform(BUBLET *pbublet, float dt);

/**
 * @brief Touch callback for a bublet, forwarding to TouchDroplet with the flag inverted.
 * @param pbublet Bublet particle.
 * @param fTouching Non-zero if currently touching.
 */
void TouchBublet(BUBLET *pbublet, int fTouching);

/**
 * @brief Initializes a ripple particle (calls InitRip then sets type specific defaults).
 * @param pripple Particle to initialize.
 * @param ppos Starting position.
 * @param gScale Scale passed through to InitRip (clamped to 200 before being stored).
 * @param psoTouch Object the particle touches (passed through to InitRip).
 * @note Field meanings and the constants set here are guesses/unnamed.
 */
void InitRipple(RIPPLE *pripple, VECTOR *ppos, float gScale, SO *psoTouch);

/**
 * @brief Initializes a puff particle (calls InitRip then sets type specific defaults).
 * @param ppuff Particle to initialize.
 * @param ppos Starting position.
 * @param gScale Scale passed through to InitRip.
 * @param psoTouch Object the particle touches (passed through to InitRip).
 * @note Field meanings and the constants set here are guesses/unnamed.
 */
void InitPuff(PUFF *ppuff, VECTOR *ppos, float gScale, SO *psoTouch);

/**
 * @brief Initializes a dablet particle (calls InitRip then sets type specific defaults).
 * @param pdablet Particle to initialize.
 * @param ppos Starting position.
 * @param gScale Scale passed through to InitRip.
 * @param psoTouch Object the particle touches (passed through to InitRip).
 * @note Field meanings and the constants set here are guesses/unnamed.
 */
void InitDablet(DABLET *pdablet, VECTOR *ppos, float gScale, SO *psoTouch);

/**
 * @brief Initializes a flake particle (InitFlake).
 * @param pflake Particle to initialize.
 * @param ppos Starting position.
 * @param gScale Scale passed through to InitRip.
 * @param psoTouch Object the particle touches (passed through to InitRip).
 * @note Field meanings are guesses; the constants set here are not named.
 */
void InitFlake(FLAKE *pflake, VECTOR *ppos, float gScale, SO *psoTouch);

void UpdateFlake(FLAKE *pflake, float dt);

void RenderFlake(FLAKE *pflake, CM *pcm);

/**
 * @brief Touch callback for a flake; removes it when touching.
 * @param pflake Flake particle.
 * @param fTouching Non-zero if currently touching.
 */
void TouchFlake(FLAKE *pflake, int fTouching);

/**
 * @brief Initializes a spark particle (calls InitRip then sets type specific defaults).
 * @param pspark Particle to initialize.
 * @param ppos Starting position.
 * @param gScale Scale passed through to InitRip.
 * @param psoTouch Object the particle touches (passed through to InitRip).
 * @note Field meanings and the constants set here are guesses/unnamed.
 */
void InitSpark(SPARK *pspark, VECTOR *ppos, float gScale, SO *psoTouch);

void RenderSpark(SPARK *pspark, CM *pcm);

void InitBurst(BURST *pburst, VECTOR *ppos, float gScale, SO *psoTouch);

void InitTrail(TRAIL *ptrail, VECTOR *ppos, float gScale, SO *psoTouch);

/**
 * @brief Removal callback for a trail; clears its tracking state.
 * @param ptrail Trail being removed.
 */
void OnTrailRemove(TRAIL *ptrail);

void SetTrailTrls(TRAIL *ptrail, TRLS trls, void *pv);

void DetachTrail(TRAIL *ptrail);

void ProjectTrailTransform(TRAIL *ptrail, float dt);

void RenderTrail(TRAIL *ptrail, CM *pcm);

/**
 * @brief Message handler for a trail: stops tracking when removed, entering water or its rip is removed.
 * @param ptrail Trail.
 * @param msgid Message id.
 * @param pv Message payload (for MSGID_translated, a pointer offset by 0x10 is used as the track target; a guess).
 */
void HandleTrailMessage(TRAIL *ptrail, MSGID msgid, void *pv);

void InitFireball(FIREBALL *pfireball, VECTOR *ppos, float gScale, SO *psoTouch);

void UpdateFireball(FIREBALL *pfireball, float dt);

void InitSmokecloud(SMOKECLOUD *psmokecloud, VECTOR *ppos, float gScale, SO *psoTouch);

void InitSmoketrail(SMOKETRAIL *psmoketrail, VECTOR *ppos, float gScale, SO *psoTouch);

/**
 * @brief Initializes a debris particle (InitDebris).
 * @param pdebris Particle to initialize.
 * @param ppos Starting position.
 * @param gScale Scale passed through to InitRip.
 * @param psoTouch Object the particle touches (passed through to InitRip).
 * @note Field meanings are guesses; the constants set here are not named.
 */
void InitDebris(DEBRIS *pdebris, VECTOR *ppos, float gScale, SO *psoTouch);

void InitSmack(SMACK *psmack, VECTOR *ppos, float gScale, SO *psoTouch);

void ProjectSmackTransform(SMACK *psmack, float dt);

void RenderSmack(SMACK *psmack, CM *pcm);

/**
 * @brief Updates a smack particle; once its lifetime has elapsed it is removed and a callback is invoked.
 * @param psmack Smack particle.
 * @param dt Time step (unused).
 * @note The callback object at +0x130 (function at vtable slot 0x60, argument at +0x134) is a guess.
 */
void UpdateSmack(SMACK *psmack, float dt);

/**
 * @brief Initializes a orbit particle (InitOrbit).
 * @param porbit Particle to initialize.
 * @param ppos Starting position.
 * @param gScale Scale passed through to InitRip.
 * @param psoTouch Object the particle touches (passed through to InitRip).
 * @note Field meanings are guesses; the constants set here are not named.
 */
void InitOrbit(ORBIT *porbit, VECTOR *ppos, float gScale, SO *psoTouch);

void ProjectOrbitTransform(ORBIT *porbit, float dt);

void UpdateOrbit(ORBIT *porbit, float dt);

void RenderOrbit(ORBIT *porbit, CM *pcm);

/**
 * @brief Initializes a ray particle (InitRay).
 * @param pray Particle to initialize.
 * @param ppos Starting position.
 * @param gScale Scale passed through to InitRip.
 * @param psoTouch Object the particle touches (passed through to InitRip).
 * @note Field meanings are guesses; the constants set here are not named.
 */
void InitRay(RAY *pray, VECTOR *ppos, float gScale, SO *psoTouch);

/**
 * @brief Initializes a rose particle (InitRose).
 * @param prose Particle to initialize.
 * @param ppos Starting position.
 * @param gScale Scale passed through to InitRip.
 * @param psoTouch Object the particle touches (passed through to InitRip).
 * @note Field meanings are guesses; the constants set here are not named.
 */
void InitRose(ROSE *prose, VECTOR *ppos, float gScale, SO *psoTouch);

void ProjectRoseTransform(ROSE *prose, float dt);

void UpdateRose(ROSE *prose, float dt);

void RenderRose(ROSE *prose, CM *pcm);

void SetRoseRoses(ROSE *prose, ROSES roses);

/**
 * @brief Comparison callback for sorting hull points by the float at +0x20.
 * @param pv0 First element.
 * @param pv1 Second element.
 * @return -1 if the first is smaller, otherwise 1 (never 0).
 */
int SgnCmpHp(const void *pv0, const void *pv1);

int ChpBuildConvexHullScreen(VECTOR *pposCenter, int chp, HP *ahp);

int ChpBuildConvexHullXY(MATRIX4 *pdmat, int chp, HP *ahp);

/**
 * @brief Copies emitter parameters into a flying particle after emit.
 * @param pflying Flying particle.
 * @param pemitb Emitter that spawned it.
 * @note The meaning of the copied fields (emitter +0x1dc/+0x1f0) is a guess.
 */
void PostFlyingEmit(FLYING *pflying, EMITB *pemitb);

void RenderFlying(FLYING *pflying, CM *pcm);

void CreateStuck(RIP *pripSrc, ALO *paloRender, SO *psoOther, VECTOR *ppos, VECTOR *pnormal, STUCK **ppstuck);

int FBounceFlying(FLYING *pflying, SO *psoOther, VECTOR *ppos, VECTOR *pnormal);

/**
 * @brief Updates a stuck particle; removes it when its attached object leaves the world.
 * @param pstuck Stuck particle.
 * @param dt Time step.
 * @note The object pointer at +0x120 is a guess.
 */
void UpdateStuck(STUCK *pstuck, float dt);

void RenderStuck(STUCK *pstuck, CM *pcm);

void PostLeafEmit(LEAF *pleaf, EMITB *pemitb);

void ProjectLeafTransform(LEAF *pleaf, float dt);

int FBounceLeaf(LEAF *pleaf, SO *psoOther, VECTOR *ppos, VECTOR *pnormal);

/**
 * @brief Filter for flame collisions: skips objects with a certain SO flag bit set and the flame's own owner.
 * @param pv Flame particle (the owner pointer at +0x7c is a guess).
 * @param pso Candidate object.
 * @return Non-zero if the object should be considered.
 */
int FFilterFlameObjects(void *pv, SO *pso);

void PostFlameEmit(FLAME *pflame, EMITB *pemitb);

/**
 * @brief Post-emit setup for a bullet: converts the emit position to world space and copies emitter parameters.
 * @param pbullet Bullet particle.
 * @param pemitb Emitter that spawned it.
 */
void PostBulletEmit(BULLET *pbullet, EMITB *pemitb);

void RenderBullet(BULLET *pbullet, CM *pcm);

int FBounceBullet(BULLET *pbullet, SO *psoOther, VECTOR *ppos, VECTOR *pnormal);

void PostShrapnelEmit(SHRAPNEL *pshrapnel, EMITB *pemitb);

/**
 * @brief Bounce test for shrapnel; never bounces off STEP figures, otherwise defers to FBounceRip.
 * @param pshrapnel Shrapnel particle.
 * @param psoOther Object hit.
 * @param ppos Hit position.
 * @param pnormal Hit normal.
 * @return Non-zero if the particle bounced.
 */
int FBounceShrapnel(SHRAPNEL *pshrapnel, SO *psoOther, VECTOR *ppos, VECTOR *pnormal);

void RenderShrapnel(SHRAPNEL *pshrapnel, CM *pcm);

void InitGlint(GLINT *pglint, VECTOR *ppos, float gScale, SO *psoTouch);

void RenderGlint(GLINT *pglint, CM *pcm);

/**
 * @brief Initializes a match particle (calls InitRip then sets type specific defaults).
 * @param pmatch Particle to initialize.
 * @param ppos Starting position.
 * @param gScale Scale passed through to InitRip and stored in the particle.
 * @param psoTouch Object the particle touches (passed through to InitRip).
 * @note Field meanings and the constants set here are guesses/unnamed.
 */
void InitMatch(MATCH *pmatch, VECTOR *ppos, float gScale, SO *psoTouch);

void LaunchMatch(MATCH *pmatch);

void ProjectMatchTransform(MATCH *pmatch, float dt);

void UpdateMatch(MATCH *pmatch, float dt);

/**
 * @brief Renders a match; skipped until its start time has been reached.
 * @param pmatch Match particle.
 * @param pcm Camera.
 */
void RenderMatch(MATCH *pmatch, CM *pcm);

/**
 * @brief Post-emit setup for a remit: looks up the target object and copies a float from the emitter.
 * @param premit Remit particle.
 * @param pemitb Emitter that spawned it.
 * @note Names of the looked up object (OID at emitter +0x1f0) are guesses.
 */
void PostRemitEmit(REMIT *premit, EMITB *pemitb);

void UpdateRemit(REMIT *premit, float dt);

#endif // RIP_H
