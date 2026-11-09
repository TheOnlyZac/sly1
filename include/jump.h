/**
 * @file jump.h
 */
#ifndef JUMP_H
#define JUMP_H

#include "common.h"
#include <mark.h>
#include <vec.h>
#include <joy.h>
#include <pnt.h>
#include <jt.h>
#include <lo.h>
#include <so.h>

// Forward.
struct XP;

/**
 * @class JUMP_TARGET
 * @brief Target point for a jump.
 * @todo Implement the struct.
 */
struct JMT : public PNT
{
    /* 0x50 */ DLE dleJmt;
    /* 0x58 */ float sRadius;
    /* 0x5c */ OID oidSetIgnoreJt;
    /* 0x60 */ SO *psoSetIgnoreJt;
    // ...
};

void PresetJtAccelJump(JT *pjt);

void UpdateJtActiveJump(JT *pjt, JOY *pjoy);

int FCheckJtSingleEdge(JT *pjt, SO *psoOther, EDGE *pedge, VECTOR *pnormal);

/**
 * @brief Checks whether an edge with the given normal can be grabbed.
 *
 * Builds a coordinate frame at the edge and sweeps 11 pairs of probe points (from a table of
 * offsets) through the nearby objects. A hit in either of the first two probes rejects the edge.
 * Later hits only count when the z component of the first clipped normal is above 0.7.
 *
 * @param pjt Sly.
 * @param pposEdge Position of the edge.
 * @param pnormal Normal of the edge.
 * @return 1 if at least two of the later probes count as hits, otherwise 0.
 *
 * @note The probe table layout, the object lists read from the JT and what the 0.7 threshold means are
 * inferred from the asm.
 */
int FCheckJtEdgeNormal(JT *pjt, VECTOR *pposEdge, VECTOR *pnormal);

int FCheckJtEdgeGrab(JT *pjt, SO *psoOther, VECTOR *pposEdge, XPK xpk, void *pv, VECTOR *pnormal);

XP *PxpFindJtBestEdge(JT *pjt, int *pixpdBest, VECTOR *pnormalBest);

JTS JtsResetJt(JT *pjt);

void HandleJtDiveEffect(JT *pjt);

void UpdateJtJump(JT *pjt);

int FTimeJtJumpToTarget(JT *pjt, VECTOR *pposJt, VECTOR *pvJt, VECTOR *pposTarget, VECTOR *pvTarget, float *pdtProject);

void GetJtJumpVelocity(JT *pjt, VECTOR *pv);

void GetJtJumpToTargetVelocity(JT *pjt, VECTOR *pv);

void GetJtJumpBoostVelocity(JT *pjt, VECTOR *pv);

void StartupJmt();

void ResetJmtList();

void OnJmtAdd(JMT *pjmt);

void OnJmtRemove(JMT *pjmt);

void CloneJmt(JMT *pjmt, JMT *pjmtBase);

void PostJmtLoad(JMT *pjmt);

#endif // JUMP_H
