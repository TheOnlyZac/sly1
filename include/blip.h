/**
 * @file blip.h
 */
#ifndef BLIP_H
#define BLIP_H

#include "common.h"
#include <flash.h>
#include <alo.h>
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
struct BLIPP
{
    /* 0x00 */ float x;
    /* 0x04 */ float y;
    /* 0x08 */ float z;
    /* 0x0c */ float tCreated;
};

/**
 * @brief Unknown.
 */
struct BLIPV
{
    /* 0x00 */ float x;
    /* 0x04 */ float y;
    /* 0x08 */ float z;
    /* 0x0c */ float tDestroy;
};

/**
 * @brief Unknown.
 */
struct BLIPX
{
    /* 0x00 */ uint irgba;
    /* 0x04 */ uint itex0;
    /* 0x08 */ float swRoll;
    /* 0x0c */ float radRoll;
};

/**
 * @brief Unknown.
 */
struct BLIPF
{
    /* 0x000 */ BLIPP ablipp[44];
    /* 0x2c0 */ BLIPV ablipv[44];
    /* 0x580 */ BLIPX ablipx[44];
};

/**
 * @class BLIPG
 * @brief Unknown.
 */
struct BLIPG : public ALO
{
    // ...
};

/**
 * @brief Unknown.
 */
struct BLIPSP
{
    // ...
};

/**
 * @brief Unknown.
 */
struct BLIP
{
    /* 0x0000 */ BLIPF ablipf[2];
    /* 0x1080 */ int iblipfLatest;
    /* 0x1084 */ int cblipe;
    /* 0x1088 */ BLIPSP *pblipsp;
    /* 0x108c */ BLIPG *pblipg;
    /* 0x1090 */ DLE dle;
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
