/**
 * @file step.h
 */
#ifndef STEP_H
#define STEP_H

#include "common.h"
#include <po.h>
#include <so.h>
#include <sm.h>
#include <cm.h>
#include <bsp.h>
#include <dzg.h>
#include <alo.h>
#include <util.h>

// Forward.
struct FX;
struct XP;
struct SFF;

typedef int GRFSG;
typedef int GRFADJ;

/**
 * @brief STEP_FIGURE
 * @brief Moving/waking characters.
 */
struct STEP : public PO
{
    /* 0x610 */ ALO *paloLeftFoot;
    /* 0x614 */ ALO *paloRightFoot;
    /* 0x618 */ ALO *paloLeftHand;
    /* 0x61c */ ALO *paloRightHand;
    /* 0x620 */ ALO *paloLeftHeel;
    /* 0x624 */ ALO *paloRightHeel;
    /* 0x628 */ ALO *paloLeftBall;
    /* 0x62c */ ALO *paloRightBall;
    /* 0x630 */ float radJoy;
    /* 0x634 */ float uJoyDeflect;
    /* 0x638 */ float radTarget;
    /* 0x63c */ float uTarget;
    /* 0x640 */ VECTOR vTarget;
    /* 0x650 */ float zBaseTarget; // TODO: Unused?
    /* 0x654 */ STRUCT_PADDING(3);
    /* 0x660 */ MATRIX3 matTarget;
    /* 0x690 */ int fBaseXp;
    /* 0x694 */ float tBaseXp;
    /* 0x698 */ STRUCT_PADDING(2);
    /* 0x6a0 */ VECTOR posBaseXp;
    /* 0x6b0 */ VECTOR normalBaseXp;
    /* 0x6c0 */ SO *psoBaseXp;
    /* 0x6c4 */ float uFootFall;
    /* 0x6c8 */ float tLastFootfall;
    /* 0x6cc */ float dzBase;
    /* 0x6d0 */ int iposBase;
    /* 0x6d4 */ VECTOR *pposBase;
    /* 0x6d8 */ VECTOR *pposBumper;
    /* 0x6dc */ SO *psoPhys;
    /* 0x6e0 */ SMP smpSpin;
    /* 0x6ec */ STRUCT_PADDING(1);
    /* 0x6f0 */ CLQ clqDradToURun;
    /* 0x700 */ float rGravity;
    /* 0x704 */ SMP smpCompress;
    /* 0x710 */ SMP smpExpand;
    /* 0x71c */ STRUCT_PADDING(1);
};

void InitStep(STEP *pstep);

void PostStepLoad(STEP *pstep);

void LimitStepHands(STEP *pstep, int fLimit);

void RetractStepExtremity(STEP *pstep, ALO *paloExtrem, float sRadius, ALO *paloAdjust, ALO *paloIkh);

void RenderStepSelf(STEP *pstep, CM *pcm, RO *pro);

void ReadStepJoystick(STEP *pstep, JOY *pjoy);

void UpdateStepFootfall(STEP *pstep, float u, SFF *psff);

void UpdateStepPhys(STEP *pstep);

void SetStepPhys(STEP *pstep, SO *pso, int fForceSnap);

void UpdateStep(STEP *pstep, float dt);

CT CtTorqueStep(STEP *pstep);

void PropagateStepForce(STEP *pstep, GRFSG grfsg, XP *pxp, int ixpd, DZ *pdz, FX *afx);

void RotateStepToMat(STEP *pstep, MATRIX3 *pmat);

void CloneStepPhys(STEP *pstep, SO *psoPhys, int cposExtra);

void PresetStepAccel(STEP *pstep, float dt);

void PresetStepAccelBase(STEP *pstep);

int FCheckStepXpBase(STEP *pstep, XP *pxp, int ixpd);

void AdjustStepNewXp(STEP *pstep, XP *pxp, int ixpd);

void AdjustStepDz(STEP *pstep, GRFADJ grfadj, DZ *pdz, int ixpd, float dt);

void AdjustStepDzBase(STEP *pstep, GRFADJ grfadj, DZ *pdz, int ixpd);

void UpdateStepMatTarget(STEP *pstep);

void AdjustStepXpVelocity(STEP *pstep, XP *pxp, int ixpd);

void UpdateStepXfWorld(STEP *pstep);

void AdjustStepXpVelocityBase(STEP *pstep, XP *pxp, int ixpd);

void AdjustStepXps(STEP *pstep);

void AddStepCustomXps(STEP *pstep, SO *psoOther, int cbspPruned, BSP *abspPruned, BSP *pbspPruned, XP **ppxpFirst);

void AddStepCustomXpsBase(STEP *pstep, SO *psoOther, BSP *pbspPruned, XP **ppxpFirst);

void FixStepAngularVelocity(STEP *pstep);

void PredictStepPosition(STEP *pstep, float dtOffset, VECTOR *ppos, VECTOR *pv);

void PredictStepRotation(STEP *pstep, float dtOffset, MATRIX3 *pmat, VECTOR *pw);

void SetStepSpinRatio(STEP *pstep, float r);

void SetStepGravityRatio(STEP *pstep, float rGravity);

#endif // STEP_H
