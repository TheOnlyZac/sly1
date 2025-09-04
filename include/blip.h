/**
 * @file blip.h
 */
#ifndef BLIP_H
#define BLIP_H

#include "common.h"
#include <flash.h>
#include <mat.h>
#include <vec.h>
#include <oid.h>
#include <shd.h>
#include <sw.h>
#include <cm.h>

// Forward.
struct EMITB;
struct RPL;

typedef int GRFZON;

/**
 * @todo Move elsewhere?
 */
struct VU_FLOAT
{
    uint16_t data;
};

/**
 * @brief Unknown.
 */
enum BLIPOK
{
    BLIPOK_Nil = -1,
    BLIPOK_Fixed = 0,
    BLIPOK_Flying = 1,
    BLIPOK_Rolling = 2,
    BLIPOK_Max = 3
};

/**
 * @brief Unknown.
 */
struct BLIP
{
    // ...
};

/**
 * @brief Unknown.
 */
struct BLIPG
{
    // ...
};

/**
 * @brief Unknown.
 */
struct BLIPP
{
    // ...
};

/**
 * @brief Unknown.
 */
struct BLIPV
{
    // ...
};

/**
 * @brief Unknown.
 */
struct BLIPX
{
    // ...
};

void BuildBlipAqwGifs(int alpha_b, QW **paqw);

void StartupBlips();

BLIP *PblipNew(BLIPG *pblipg);

void RemoveBlip(BLIP *pblip);

BLIPG *PblipgNew(SW *psw);

void InitBlipg(BLIPG *pblipg);

void OnBlipgAdd(BLIPG *pblipg);

void OnBlipgRemove(BLIPG *pblipg);

void SetBlipgShader(BLIPG *pblipg, OID oid);

void PropagateBlipgShader(BLIPG *pblipg);

void SetBlipgEmitb(BLIPG *pblipg, EMITB *pemitb);

void UpdateBlipg(BLIPG *pblipg, float dt);

void SubscribeBlipgObject(BLIPG *pblipg, LO *ploTarget);

int CblipeProjectBlipTransformAccel(MATRIX4 *pmat4Dv, VU_FLOAT dt, BLIPP *ablipp, BLIPV *ablipv, BLIPX *ablipx, int cblipe, BLIPOK blipok, VECTOR *pposMin, VECTOR *pposMax);

void ProjectBlipgTransformAccel(BLIPG *pblipg, float dt);

void ProjectBlipgTransform(BLIPG *pblipg, float dt, int fForce);

void RenderBlipgSelf(BLIPG *pblipg, CM *pcm, RO *pro);

void DrawBlipg(RPL *prpl);

void PropagateBlipgShaders(GRFZON grfzon);

#endif // BLIP_H
