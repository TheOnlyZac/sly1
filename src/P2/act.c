#include <act.h>

INCLUDE_ASM("asm/nonmatchings/P2/act", PactNew__FP2SWP3ALOP5VTACT);

INCLUDE_ASM("asm/nonmatchings/P2/act", PactNewClone__FP3ACTP2SWP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/act", CloneAct__FP3ACTT0);

INCLUDE_ASM("asm/nonmatchings/P2/act", InitAct__FP3ACTP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/act", RetractAct__FP3ACTi);

INCLUDE_ASM("asm/nonmatchings/P2/act", GetActPositionGoal__FP3ACTfP6VECTORT2);

INCLUDE_ASM("asm/nonmatchings/P2/act", GetActRotationGoal__FP3ACTfP7MATRIX3P6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/act", GetActTwistGoal__FP3ACTPfT1);

INCLUDE_ASM("asm/nonmatchings/P2/act", GetActScale__FP3ACTP7MATRIX3);

INCLUDE_ASM("asm/nonmatchings/P2/act", GGetActPoseGoal__FP3ACTi);

INCLUDE_ASM("asm/nonmatchings/P2/act", CalculateActDefaultAck__FP3ACT);

INCLUDE_ASM("asm/nonmatchings/P2/act", SnapAct__FP3ACTi);

INCLUDE_ASM("asm/nonmatchings/P2/act", CalculateAloPositionSpring__FP3ALOfP6VECTORN22);

INCLUDE_ASM("asm/nonmatchings/P2/act", ProjectActPosition__FP3ACT);

INCLUDE_ASM("asm/nonmatchings/P2/act", CalculateAloRotationSpring__FP3ALOfP7MATRIX3P6VECTORT3);

INCLUDE_ASM("asm/nonmatchings/P2/act", ProjectActRotation__FP3ACT);

INCLUDE_ASM("asm/nonmatchings/P2/act", ProjectActPose__FP3ACTi);

INCLUDE_ASM("asm/nonmatchings/P2/act", PredictAloPosition__FP3ALOfP6VECTORT2);

INCLUDE_ASM("asm/nonmatchings/P2/act", PredictAloRotation__FP3ALOfP7MATRIX3P6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/act", AdaptAct__FP3ACT);

INCLUDE_ASM("asm/nonmatchings/P2/act", InitActval__FP6ACTVALP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/act", GetActvalPositionGoal__FP6ACTVALfP6VECTORT2);

INCLUDE_ASM("asm/nonmatchings/P2/act", GetActvalRotationGoal__FP6ACTVALfP7MATRIX3P6VECTOR);

void GetActvalTwistGoal(ACTVAL *pactval, float *pradTwist, float *pdradTwist)
{
    *pradTwist = pactval->radTwistGoal;
    *pdradTwist = pactval->dradTwistGoal;
}

INCLUDE_ASM("asm/nonmatchings/P2/act", GetActvalScale__FP6ACTVALP7MATRIX3);

float GGetActvalPoseGoal(ACTVAL *pactval, int ipose)
{
    return pactval->agPoses[ipose];
}

INCLUDE_ASM("asm/nonmatchings/P2/act", InitActref__FP6ACTREFP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/act", GetActrefPositionGoal__FP6ACTREFfP6VECTORT2);

INCLUDE_ASM("asm/nonmatchings/P2/act", GetActrefRotationGoal__FP6ACTREFfP7MATRIX3P6VECTOR);

void GetActrefTwistGoal(ACTREF *pactref, float *pradTwist, float *pdradTwist)
{
    *pradTwist = *pactref->pradTwistGoal;
    *pdradTwist = *pactref->pdradTwistGoal;
}

INCLUDE_ASM("asm/nonmatchings/P2/act", GetActrefScale__FP6ACTREFP7MATRIX3);

INCLUDE_ASM("asm/nonmatchings/P2/act", GGetActrefPoseGoal__FP6ACTREFi);

INCLUDE_ASM("asm/nonmatchings/P2/act", InitActadj__FP6ACTADJP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/act", GetActadjPositionGoal__FP6ACTADJfP6VECTORT2);

INCLUDE_ASM("asm/nonmatchings/P2/act", GetActadjRotationGoal__FP6ACTADJfP7MATRIX3P6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/act", GetActadjTwistGoal__FP6ACTADJPfT1);

INCLUDE_ASM("asm/nonmatchings/P2/act", GetActadjScale__FP6ACTADJP7MATRIX3);

float GGetActadjPoseGoal(ACTADJ *pactadj, int ipose)
{
    return 0.0f;
}

void InitActbank(ACTBANK *pactbank, ALO *palo)
{
    InitAct(pactbank, palo);
    pactbank->uBank = 1.0f;
    pactbank->dtPredict = 0.25f;
}

INCLUDE_ASM("asm/nonmatchings/P2/act", GetActbankRotationGoal__FP7ACTBANKfP7MATRIX3P6VECTOR);
