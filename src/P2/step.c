#include <step.h>
#include <mat.h>
#include <math.h>

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

void UpdateStepMatTarget(STEP *pstep)
{
    extern VECTOR g_normalZ;
    LoadRotateMatrixRad(*(float *)((uint8_t *)(pstep) + 0x638), &g_normalZ, (MATRIX3 *)((uint8_t *)(pstep) + 0x660));
}

void AdjustStepXpVelocity(STEP *pstep, XP *pxp, int ixpd)
{
    if ((*(int (**)(STEP *))((char *)pstep->pvtlo + 0x168))(pstep))
        AdjustStepXpVelocityBase(pstep, pxp, ixpd);
}

INCLUDE_ASM("asm/nonmatchings/P2/step", UpdateStepXfWorld__FP4STEP);

INCLUDE_ASM("asm/nonmatchings/P2/step", AdjustStepXpVelocityBase__FP4STEPP2XPi);

INCLUDE_ASM("asm/nonmatchings/P2/step", AdjustStepXps__FP4STEP);

void AddStepCustomXps(STEP *pstep, SO *psoOther, int cbspPruned, BSP *abspPruned, BSP *pbspPruned, XP **ppxpFirst)
{
    AddStepCustomXpsBase(pstep, psoOther, pbspPruned, ppxpFirst);
}

INCLUDE_ASM("asm/nonmatchings/P2/step", AddStepCustomXpsBase__FP4STEPP2SOP3BSPPP2XP);

void FixStepAngularVelocity(STEP *pstep)
{
    qword local;
    float radTarget;

    local = STRUCT_OFFSET(pstep, 0x160, qword);
    radTarget = atan2f(STRUCT_OFFSET(pstep, 0xd4, float), STRUCT_OFFSET(pstep, 0xd0, float));
    RadSmooth(radTarget, STRUCT_OFFSET(pstep, 0x638, float), 0.0f,
              (SMP *)((uint8_t *)pstep + 0x6e0), (float *)((uint8_t *)&local + 8));
    (*(void (**)(STEP *, qword *))((uint8_t *)pstep->pvtlo + 0x94))(pstep, &local);
}

INCLUDE_ASM("asm/nonmatchings/P2/step", PredictStepRotation__FP4STEPfP7MATRIX3P6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/step", SetStepSpinRatio__FP4STEPf);

INCLUDE_ASM("asm/nonmatchings/P2/step", SetStepGravityRatio__FP4STEPf);
