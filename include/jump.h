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
    undefined4 unk1;
    undefined4 unk2;
    undefined4 unk3;
    undefined4 unk4;
    DLE dleJmt;
    float sRadius;
    OID oidSetIgnoreJt;
    SO *psoSetIgnoreJt;
    // ...
};

void PresetJtAccelJump(JT *pjt);

void UpdateJtActiveJump(JT *pjt, JOY *pjoy);

int FCheckJtSingleEdge(JT *pjt, SO *psoOther, EDGE *pedge, VECTOR *pnormal);

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
