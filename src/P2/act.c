#include <act.h>
#include <slotheap.h>
#include <sw.h>
#include <memory.h>
#include <alo.h>

ACT *PactNew(SW *psw, ALO *palo, VTACT *pvtact)
{
    ACT *pact = (ACT *)PvAllocSlotheapClearImpl((SLOTHEAP *)((uint8_t *)psw + 0x1B20));
    pact->pvtact = pvtact;
    (*(void (**)(ACT *, ALO *))pvtact)(pact, palo);
    return pact;
}

extern VTACT D_00219560;

ACT *PactNewClone(ACT *pactBase, SW *psw, ALO *palo)
{
    ACT *pact = PactNew(psw, palo, &D_00219560);
    (*(void (**)(ACT *, ACT *))((uint8_t *)pact->pvtact + 4))(pact, pactBase);
    return pact;
}

void CloneAct(ACT *pact, ACT *pactBase)
{
    DLE dleSav = pact->dleAlo;
    ALO *paloSav = pact->palo;
    CopyAb(pact, pactBase, STRUCT_OFFSET(g_psw, 0x1B20, int));
    pact->dleAlo = dleSav;
    pact->palo = paloSav;
}

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

void SnapAct(ACT *pact, int fForce)
{
    VECTOR pos;
    VECTOR v;
    MATRIX3 mat;
    ALO *palo = pact->palo;

    if (pact == STRUCT_OFFSET(palo, 0x1ec, ACT *) &&
        (fForce != 0 || STRUCT_OFFSET(pact, 0x10, char) == 2))
    {
        (*(void (**)(ACT *, float, VECTOR *, VECTOR *))((char *)pact->pvtact + 0x10))(pact, 0.0f, &pos, &v);
        (*(void (**)(ALO *, VECTOR *))((char *)palo->pvtlo + 0x84))(palo, &pos);
        (*(void (**)(ALO *, VECTOR *))((char *)palo->pvtlo + 0x90))(palo, &v);
    }
    if (pact == STRUCT_OFFSET(palo, 0x1f0, ACT *) &&
        (fForce != 0 || STRUCT_OFFSET(pact, 0x11, char) == 2))
    {
        (*(void (**)(ACT *, float, MATRIX3 *, VECTOR *))((char *)pact->pvtact + 0x14))(pact, 0.0f, &mat, &pos);
        (*(void (**)(ALO *, MATRIX3 *))((char *)palo->pvtlo + 0x88))(palo, &mat);
        (*(void (**)(ALO *, VECTOR *))((char *)palo->pvtlo + 0x94))(palo, &pos);
    }
}

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

void InitActval(ACTVAL *pactval, ALO *palo)
{
    uint8_t *psen;

    InitAct(pactval, palo);
    *(qword *)((uint8_t *)pactval + 0x20) = *(qword *)((uint8_t *)palo + 0x190);
    *(qword *)((uint8_t *)pactval + 0x40) = *(qword *)((uint8_t *)palo + 0x1a0);
    *(qword *)((uint8_t *)pactval + 0x50) = *(qword *)((uint8_t *)palo + 0x1b0);
    *(qword *)((uint8_t *)pactval + 0x60) = *(qword *)((uint8_t *)palo + 0x1c0);
    psen = STRUCT_OFFSET(palo, 0x224, uint8_t *);
    if (psen != 0 && (STRUCT_OFFSET(psen, 0xb0, int) & 0x20))
    {
        pactval->radTwistGoal = STRUCT_OFFSET(psen, 0x8c, float);
    }
    *(qword *)((uint8_t *)pactval + 0x90) = *(qword *)(D_002483D0 + 0x0);
    *(qword *)((uint8_t *)pactval + 0xa0) = *(qword *)(D_002483D0 + 0x10);
    *(qword *)((uint8_t *)pactval + 0xb0) = *(qword *)(D_002483D0 + 0x20);
    STRUCT_OFFSET(pactval, 0xc0, int) = STRUCT_OFFSET(palo, 0x26c, int);
    STRUCT_OFFSET(pactval, 0xc4, int) = STRUCT_OFFSET(palo, 0x274, int);
}

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

extern VECTOR D_00248D30;

void InitActref(ACTREF *pactref, ALO *palo)
{
    uint8_t *psen;

    InitAct(pactref, palo);
    STRUCT_OFFSET(pactref, 0x1c, uint8_t *) = (uint8_t *)palo + 0x190;
    STRUCT_OFFSET(pactref, 0x24, uint8_t *) = (uint8_t *)palo + 0x1a0;
    STRUCT_OFFSET(pactref, 0x38, uint8_t *) = (uint8_t *)palo + 0x26c;
    STRUCT_OFFSET(pactref, 0x20, VECTOR *) = &D_00248D30;
    STRUCT_OFFSET(pactref, 0x28, VECTOR *) = &D_00248D30;
    STRUCT_OFFSET(pactref, 0x3c, float *) = STRUCT_OFFSET(palo, 0x274, float *);
    psen = STRUCT_OFFSET(palo, 0x224, uint8_t *);
    if (psen != 0 && (STRUCT_OFFSET(psen, 0xb0, int) & 0x20))
    {
        STRUCT_OFFSET(pactref, 0x30, VECTOR *) = &D_00248D30;
        STRUCT_OFFSET(pactref, 0x2c, uint8_t *) = psen + 0x8c;
    }
    STRUCT_OFFSET(pactref, 0x34, char *) = D_002483D0;
}

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
