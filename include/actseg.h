/**
 * @file actseg.h
 *
 * @brief Declarations for actor segments.
*/
#ifndef ACTSEG_H
#define ACTSEG_H

#include "common.h"
#include <act.h>
#include <vec.h>
#include <mat.h>

// Forward.
struct ASEGA;

/**
 * @brief Actor segment.
 * @todo Implement the struct.
 */
struct ACTSEG : public ACT
{
    /* 0x1c */ ASEGA *pasega;
    /* 0x20 */ DLE dleAsega;
    // ...
};

void RetractActseg(ACTSEG *pactseg, GRFRA grfra);

void CloneActseg(ACTSEG *pactseg, ACTSEG *pactsegBase);

void GetActsegPositionGoal(ACTSEG *pactseg, float dtOffset, VECTOR *ppos, VECTOR *pv);

void GetActsegRotationGoal(ACTSEG *pactseg, float dtOffset, MATRIX3 *pmat, VECTOR *pw);

void GetActsegTwistGoal(ACTSEG *pactseg, float *pradTwist, float *pdradTwist);

void GetActsegScale(ACTSEG *pactseg, MATRIX3 *pmat);

float GGetActsegPoseGoal(ACTSEG *pactseg, int ipose);

#endif // ACTSEG_H
