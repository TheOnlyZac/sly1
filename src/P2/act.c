#include <act.h>

INCLUDE_ASM("asm/nonmatchings/P2/act", PactNew__FP2SWP3ALOP5VTACT);

INCLUDE_ASM("asm/nonmatchings/P2/act", PactNewClone__FP3ACTP2SWP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/act", CloneAct__FP3ACTT0);

void InitAct(ACT *pact, ALO *palo)
{
    int du = -1;
    STRUCT_OFFSET(pact, 0x12, char) = du;
    pact->palo = palo;
    STRUCT_OFFSET(pact, 0x13, char) = -1;
    STRUCT_OFFSET(pact, 0x11, char) = du;
    STRUCT_OFFSET(pact, 0x10, char) = du;
}

INCLUDE_ASM("asm/nonmatchings/P2/act", RetractAct__FP3ACTi);

INCLUDE_ASM("asm/nonmatchings/P2/act", GetActPositionGoal__FP3ACTfP6VECTORT2);

INCLUDE_ASM("asm/nonmatchings/P2/act", GetActRotationGoal__FP3ACTfP7MATRIX3P6VECTOR);

void GetActTwistGoal(ACT *pact, float *pradTwist, float *pdradTwist)
{
    *pradTwist = STRUCT_OFFSET(STRUCT_OFFSET(pact->palo, 0x224, uint8_t *), 0x8c, float);
    *(int *)pdradTwist = 0;
}

extern char D_002483D0[];

void GetActScale(ACT *pact, MATRIX3 *pmat)
{
    *(qword *)((char *)pmat + 0x0) = *(qword *)(D_002483D0 + 0x0);
    *(qword *)((char *)pmat + 0x10) = *(qword *)(D_002483D0 + 0x10);
    *(qword *)((char *)pmat + 0x20) = *(qword *)(D_002483D0 + 0x20);
}

float GGetActPoseGoal(ACT *pact, int ipose)
{
    return STRUCT_OFFSET(pact->palo, 0x274, float*)[ipose];
}

INCLUDE_ASM("asm/nonmatchings/P2/act", CalculateActDefaultAck__FP3ACT);

INCLUDE_ASM("asm/nonmatchings/P2/act", SnapAct__FP3ACTi);

INCLUDE_ASM("asm/nonmatchings/P2/act", CalculateAloPositionSpring__FP3ALOfP6VECTORN22);

INCLUDE_ASM("asm/nonmatchings/P2/act", ProjectActPosition__FP3ACT);

INCLUDE_ASM("asm/nonmatchings/P2/act", CalculateAloRotationSpring__FP3ALOfP7MATRIX3P6VECTORT3);

INCLUDE_ASM("asm/nonmatchings/P2/act", ProjectActRotation__FP3ACT);

INCLUDE_ASM("asm/nonmatchings/P2/act", ProjectActPose__FP3ACTi);

INCLUDE_ASM("asm/nonmatchings/P2/act", PredictAloPosition__FP3ALOfP6VECTORT2);

INCLUDE_ASM("asm/nonmatchings/P2/act", PredictAloRotation__FP3ALOfP7MATRIX3P6VECTOR);

void AdaptAct(ACT *pact)
{
    if (STRUCT_OFFSET(pact, 0x10, char) == 7)
        STRUCT_OFFSET(pact, 0x10, char) = 3;
    if (STRUCT_OFFSET(pact, 0x11, char) == 7)
        STRUCT_OFFSET(pact, 0x11, char) = 3;
}

INCLUDE_ASM("asm/nonmatchings/P2/act", InitActval__FP6ACTVALP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/act", GetActvalPositionGoal__FP6ACTVALfP6VECTORT2);

INCLUDE_ASM("asm/nonmatchings/P2/act", GetActvalRotationGoal__FP6ACTVALfP7MATRIX3P6VECTOR);

void GetActvalTwistGoal(ACTVAL *pactval, float *pradTwist, float *pdradTwist)
{
    *pradTwist = pactval->radTwistGoal;
    *pdradTwist = pactval->dradTwistGoal;
}

void GetActvalScale(ACTVAL *pactval, MATRIX3 *pmat)
{
    *(qword *)((uint8_t *)pmat + 0x0) = *(qword *)((uint8_t *)pactval + 0x90);
    *(qword *)((uint8_t *)pmat + 0x10) = *(qword *)((uint8_t *)pactval + 0xA0);
    *(qword *)((uint8_t *)pmat + 0x20) = *(qword *)((uint8_t *)pactval + 0xB0);
}

float GGetActvalPoseGoal(ACTVAL *pactval, int ipose)
{
    return pactval->agPoses[ipose];
}

INCLUDE_ASM("asm/nonmatchings/P2/act", InitActref__FP6ACTREFP3ALO);

void GetActrefPositionGoal(ACTREF *pactref, float dtOffset, VECTOR *ppos, VECTOR *pv)
{
    *(qword *)ppos = *(qword *)STRUCT_OFFSET(pactref, 0x1c, uint8_t *);
    *(qword *)pv = *(qword *)STRUCT_OFFSET(pactref, 0x20, uint8_t *);
    ALO *palo = pactref->palo;
    void (*pfn)(ALO *) = (void (*)(ALO *))STRUCT_OFFSET(STRUCT_OFFSET(palo, 0x0, void *), 0xB0, void *);
    if (pfn)
        pfn(palo);
}

INCLUDE_ASM("asm/nonmatchings/P2/act", GetActrefRotationGoal__FP6ACTREFfP7MATRIX3P6VECTOR);

void GetActrefTwistGoal(ACTREF *pactref, float *pradTwist, float *pdradTwist)
{
    *pradTwist = *pactref->pradTwistGoal;
    *pdradTwist = *pactref->pdradTwistGoal;
}

void GetActrefScale(ACTREF *pactref, MATRIX3 *pmat)
{
    uint8_t *psrc = STRUCT_OFFSET(pactref, 0x34, uint8_t *);
    *(qword *)((uint8_t *)pmat + 0x0) = *(qword *)(psrc + 0x0);
    *(qword *)((uint8_t *)pmat + 0x10) = *(qword *)(psrc + 0x10);
    *(qword *)((uint8_t *)pmat + 0x20) = *(qword *)(psrc + 0x20);
}

float GGetActrefPoseGoal(ACTREF *pactref, int ipose)
{
    return STRUCT_OFFSET(pactref, 0x3c, float*)[ipose];
}

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
