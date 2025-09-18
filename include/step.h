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
    ALO *paloLeftFoot;
    ALO *paloRightFoot;
    ALO *paloLeftHand;
    ALO *paloRightHand;
    ALO *paloLeftHeel;
    ALO *paloRightHeel;
    ALO *paloLeftBall;
    ALO *paloRightBall;
    float radJoy;
    float uJoyDeflect;
    float radTarget;
    float uTarget;
    VECTOR vTarget;
    float zBaseTarget;
    undefined4 unk_0x614[3];
    MATRIX3 matTarget;
    int fBaseXp;
    float tBaseXp;
    undefined4 unk_0x658[2];
    VECTOR posBaseXp;
    VECTOR normalBaseXp;
    SO *psoBaseXp;
    float uFootFall;
    float tLastFootfall;
    float dzBase;
    int iposBase;
    VECTOR *pposBase;
    VECTOR *pposBumper;
    SO *psoPhys;
    SMP smpSpin;
    undefined4 unk_0x6ac;
    CLQ clqDradToURun;
    float rGravity;
    SMP smpCompress;
    SMP smpExpand;
    undefined4 unk_0x6dc;
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
