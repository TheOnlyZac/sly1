#include <bez.h>
#include <crv.h>

INCLUDE_ASM("asm/nonmatchings/P2/bez", EvaluateBezierWeightedFloat__FfffffffffPfN29);

INCLUDE_ASM("asm/nonmatchings/P2/bez", EvaluateBezierFloat__FfffffffPfN27);

INCLUDE_ASM("asm/nonmatchings/P2/bez", EvaluateBezierPos__FfffP6VECTORN63);

INCLUDE_ASM("asm/nonmatchings/P2/bez", EvaluateBezierMat__FfffP7MATRIX3P6VECTORT3T4T3T4T4);

void TesselateBezier(float dtSeg, float tStart, float tEnd, VECTOR *ppos0, VECTOR *pv0, VECTOR *ppos1, VECTOR *pv1, int cpos, VECTOR *apos)
{
    float step = (tEnd - tStart) / (float)(cpos - 1);
    float tCurrent = tStart;

    for (int i = 0; i < cpos; i++)
    {
        EvaluateBezierPos(dtSeg, tCurrent, 1.0f, ppos0, pv0, ppos1, pv1, &apos[i], NULL, NULL);
        tCurrent += step;
    }
}

float SBezierPosLength(float dtSeg, float tSeg, VECTOR *ppos0, VECTOR *pv0, VECTOR *ppos1, VECTOR *pv1)
{
    VECTOR apos[20];
    TesselateBezier(dtSeg, 0.0f, tSeg, ppos0, pv0, ppos1, pv1, 20, apos);
    return SMeasureApos(sizeof(apos) / sizeof(apos[0]), apos, NULL);
}

INCLUDE_ASM("asm/nonmatchings/P2/bez", LimitBezierMulti__Fie);
