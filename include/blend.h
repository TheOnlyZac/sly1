/**
 * @file blend.h
 */
#ifndef BLEND_H
#define BLEND_H

#include "common.h"
#include <alo.h>
#include <oid.h>

// Forward.
struct ASEGBL;
struct EA;

/**
 * @brief Unknown.
 */
struct MRSG
{
    float t;
    float dt;
};

void VerifyAeaEquivalence(int cea0, EA *aea0, int cea1, EA *aea1);

void EnsureAsegBlendDynamic(ALO *palo, int cbBl, int cbl, void *abl, int cmrsgc, int *mpimrsgcib, int *mpimrsgccmrsg, ASEGBL **ppasegbl);

void FillBlAmrsg(int cbBl, int cbl, void *abl, int ibMrsg, int coid, OID *aoid);

void CalculateBlendAmrsg(int cbBl, int cbl, void *abl, int ibMrsg, int cmrsg, MRSG *amrsg, float *ptMax);

int ImrsgLookUp(float t, float tMax, int cmrsg, MRSG *amrsg, float *pdtBest);

void ReblendAsegbl(ASEGBL *pasegbl, int cbBl, int cbl, void *abl);

void SetAsegblSlerp(ASEGBL *pasegbl, ALO *palo);

#endif // BLEND_H
