#include <step.h>

INCLUDE_ASM("asm/nonmatchings/P2/step", InitStep__FP4STEP);

INCLUDE_ASM("asm/nonmatchings/P2/step", PostStepLoad__FP4STEP);

INCLUDE_ASM("asm/nonmatchings/P2/step", LimitStepHands__FP4STEPi);

// TODO: This might be "RetractStepExtremity". Further research needed.
INCLUDE_ASM("asm/nonmatchings/P2/step", FUN_001c4618);

INCLUDE_ASM("asm/nonmatchings/P2/step", FUN_001c4790);

INCLUDE_ASM("asm/nonmatchings/P2/step", FUN_001c4848);

void RenderStepSelf__FP4STEPP2CMP2RO(STEP *pstep, CM *pcm, RO *pro)
{
    RenderSoSelf(pstep, pcm, pro);
}

INCLUDE_ASM("asm/nonmatchings/P2/step", ReadStepJoystick__FP4STEPP3JOY);

INCLUDE_ASM("asm/nonmatchings/P2/step", UpdateStepFootfall__FP4STEPfP3SFF);

INCLUDE_ASM("asm/nonmatchings/P2/step", UpdateStepPhys__FP4STEP);

INCLUDE_ASM("asm/nonmatchings/P2/step", SetStepPhys__FP4STEPP2SOi);

void UpdateStep(STEP *pstep, float dt)
{
    UpdatePo(pstep, dt);
    UpdateStepPhys(pstep);
}

CT CtTorqueStep(STEP *pstep)
{
    return CT_Locked;
}

INCLUDE_ASM("asm/nonmatchings/P2/step", PropagateStepForce__FP4STEPiP2XPiP2DZP2FX);

INCLUDE_ASM("asm/nonmatchings/P2/step", RotateStepToMat__FP4STEPP7MATRIX3);

INCLUDE_ASM("asm/nonmatchings/P2/step", CloneStepPhys__FP4STEPP2SOi);

void PresetStepAccel(STEP *pstep, float dt)
{
    PresetSoAccel(pstep, dt);
    PresetStepAccelBase(pstep);
}

INCLUDE_ASM("asm/nonmatchings/P2/step", PresetStepAccelBase__FP4STEP);

INCLUDE_ASM("asm/nonmatchings/P2/step", FCheckStepXpBase__FP4STEPP2XPi);

INCLUDE_ASM("asm/nonmatchings/P2/step", AdjustStepNewXp__FP4STEPP2XPi);

void AdjustStepDz(STEP *pstep, GRFADJ grfadj, DZ *pdz, int ixpd, float dt)
{
    AdjustStepDzBase(pstep, grfadj, pdz, ixpd);
}

void AdjustStepDzBase(STEP *pstep, GRFADJ grfadj, DZ *pdz, int ixpd)
{
    return;
}

INCLUDE_ASM("asm/nonmatchings/P2/step", UpdateStepMatTarget__FP4STEP);

INCLUDE_ASM("asm/nonmatchings/P2/step", AdjustStepXpVelocity__FP4STEPP2XPi);

INCLUDE_ASM("asm/nonmatchings/P2/step", UpdateStepXfWorld__FP4STEP);

INCLUDE_ASM("asm/nonmatchings/P2/step", AdjustStepXpVelocityBase__FP4STEPP2XPi);

INCLUDE_ASM("asm/nonmatchings/P2/step", AdjustStepXps__FP4STEP);

INCLUDE_ASM("asm/nonmatchings/P2/step", AddStepCustomXps__FP4STEPP2SOiP3BSPT3PP2XP);

INCLUDE_ASM("asm/nonmatchings/P2/step", AddStepCustomXpsBase__FP4STEPP2SOP3BSPPP2XP);

INCLUDE_ASM("asm/nonmatchings/P2/step", FixStepAngularVelocity__FP4STEP);

INCLUDE_ASM("asm/nonmatchings/P2/step", PredictStepRotation__FP4STEPfP7MATRIX3P6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/step", SetStepSpinRatio__FP4STEPf);

INCLUDE_ASM("asm/nonmatchings/P2/step", SetStepGravityRatio__FP4STEPf);
