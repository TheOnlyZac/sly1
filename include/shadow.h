/**
 * @file shadow.h
 */
#ifndef SHADOW_H
#define SHADOW_H

#include "common.h"
#include <glob.h>
#include <oid.h>
#include <vec.h>
#include <so.h>
#include <sw.h>

/**
 * @brief Shadow.
 * @todo Implement the struct.
 */
struct SHADOW
{
    // ...
};

void InitShadow(SHADOW *pshadow);

void PostShadowLoad(SHADOW *pshadow);

void InvalidateShadowVifs(SHADOW *pshadow);

void RebuildShadowRegion(SHADOW *pshadow);

void SetShadowShader(SHADOW *pshadow, OID oidShdShadow);

int FShadowRadiusSet(SHADOW *pshadow);

void SetShadowNearRadius(SHADOW *pshadow, float sNearRadius);

void SetShadowFarRadius(SHADOW *pshadow, float sFarRadius);

void SetShadowCastPosition(SHADOW *pshadow, VECTOR *pposCast);

void SetShadowCastNormal(SHADOW *pshadow, VECTOR *pnormalCast);

void SetShadowNearCast(SHADOW *pshadow, float sNearCast);

void SetShadowFarCast(SHADOW *pshadow, float sFarCast);

void SetShadowConeAngle(SHADOW *pshadow, float degConeAngle);

void SetShadowFrustrumUp(SHADOW *pshadow, VECTOR *pvecUp);

int FShadowValid(SHADOW *pshadow, GRFGLOB grfglob);

int FFilterFastShadows(void *pv, SO *pso);

void UpdateShadow(SHADOW *pshadow, float dt);

void RebuildShadowVifs(SHADOW *pshadow);

void DrawShadow(SHADOW *pshadow);

int FShadowIntersectsSphere(SHADOW *pshadow, VECTOR *ppos, float sRadius);

void FindSwShadows(SW *psw, VECTOR *ppos, float sRadius, int cpshadowMax, int *pcpshadow, SHADOW ** apshadow);

#endif // SHADOW_H
