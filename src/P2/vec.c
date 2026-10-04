#include <intrinsics.h>
#include <math.h>
#include <util.h>
#include <vec.h>

void SetVectorCylind(VECTOR *pvec, float rad, float sXY, float sZ)
{
    float gSin, gCos;
    CalculateSinCos(rad, &gSin, &gCos);

    pvec->z = sZ;
    pvec->x = gCos * sXY;
    pvec->y = gSin * sXY;
}

void SetVectorSphere(VECTOR *pvec, float radPan, float radTilt, float s)
{
    float gSinPan, gCosPan, gSinTilt, gCosTilt;
    CalculateSinCos(radPan,&gSinPan, &gCosPan);
    CalculateSinCos(radTilt, &gSinTilt, &gCosTilt);

    pvec->z = gSinTilt * s;
    pvec->x = gCosTilt * gCosPan * s;
    pvec->y = gCosTilt * gSinPan * s;
}

INCLUDE_ASM("asm/nonmatchings/P2/vec", SProjectVector__FP6VECTORT0);

INCLUDE_ASM("asm/nonmatchings/P2/vec", GetNormalVectors__FP6VECTORN30);

INCLUDE_ASM("asm/nonmatchings/P2/vec", GetNormalVector__FP6VECTORT0);

JUNK_ADDIU(A0);

INCLUDE_ASM("asm/nonmatchings/P2/vec", RadBetweenVectors__FP6VECTORN20);

INCLUDE_ASM("asm/nonmatchings/P2/vec", FindClosestPointBetweenLines__FP6VECTORN30PfT4T0);

INCLUDE_ASM("asm/nonmatchings/P2/vec", FindClosestPointBetweenLineSegments__FP6VECTORN40PfT0);

void CalculateVectorPanTilt(VECTOR *pvec, float *pradPan, float *pradTilt)
{
    if (pradPan)
    {
        *pradPan = RadNormalize(atan2f(pvec->y, pvec->x));
    }
    if (pradTilt)
    {
        float dXYDist = SQRTF(pvec->x * pvec->x + pvec->y * pvec->y);
        *pradTilt = RadNormalize(atan2f(pvec->z, dXYDist));
    }
}

void ConvertDeulToW(VECTOR *peul, VECTOR *pdeul, VECTOR *pw)
{
    float ySin, yCos, zSin, zCos;
    CalculateSinCos(peul->y, &ySin, &yCos);
    CalculateSinCos(peul->z, &zSin, &zCos);

    pw->x = yCos * zCos * pdeul->x - zSin * pdeul->y;
    pw->y = yCos * zSin * pdeul->x + zCos * pdeul->y;
    pw->z = -ySin * pdeul->x + pdeul->z;
}

INCLUDE_ASM("asm/nonmatchings/P2/vec", FCalculateMuzzleVelocity__FP6VECTORT0fT0P2SO);

INCLUDE_ASM("asm/nonmatchings/P2/vec", FCalculateMuzzleVelocitySpeed__FP6VECTORT0fT0P2SO);

int FCalculateMuzzleVelocityAngle(VECTOR *pposLaunch, VECTOR *pposTarget, float radTilt, VECTOR *pvecMuzzle, SO *psoLaunch)
{
    return FCalculateMuzzleVelocity(pposLaunch, pposTarget, radTilt, pvecMuzzle, psoLaunch);
}

INCLUDE_ASM("asm/nonmatchings/P2/vec", LimitVectorLength__FP6VECTORfT0);
