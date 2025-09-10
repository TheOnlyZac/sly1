#include <vec.h>
#include <util.h>
#include <math.h>

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

INCLUDE_ASM("asm/nonmatchings/P2/vec", func_001ED900);

INCLUDE_ASM("asm/nonmatchings/P2/vec", RadBetweenVectors__FP6VECTORN20);

INCLUDE_ASM("asm/nonmatchings/P2/vec", FindClosestPointBetweenLines__FP6VECTORN30PfT4T0);

INCLUDE_ASM("asm/nonmatchings/P2/vec", FindClosestPointBetweenLineSegments__FP6VECTORN40PfT0);

INCLUDE_ASM("asm/nonmatchings/P2/vec", CalculateVectorPanTilt__FP6VECTORPfT1);
#ifdef SKIP_ASM
/**
 * @todo 92.50% matched.
 * https://decomp.me/scratch/iS3Fn
 *
 * Register usage doesn't exactly match the original
 * and the sqrt.s instruction isn't matching properly.
 *
 * atan2f is not implemented?
 */
void CalculateVectorPanTilt(VECTOR *pvec, float *ppan, float *ptilt)
{
    if (ppan)
    {
        *ppan = RadNormalize(atan2f(pvec->y, pvec->x));
    }
    if (ptilt)
    {
        float denom;
        float sum = pvec->x * pvec->x + pvec->y * pvec->y;
        __asm__ volatile ("sqrt.s %0, %1" : "=f"(denom) : "f"(sum));
        *ptilt = RadNormalize(atan2f(pvec->z, denom));
    }
}
#endif // SKIP_ASM

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

INCLUDE_ASM("asm/nonmatchings/P2/vec", FCalculateMuzzleVelocity1);

int FCalculateMuzzleVelocityAngle(VECTOR *pposLaunch, VECTOR *pposTarget, float radTilt, VECTOR *pvecMuzzle, SO *psoLaunch)
{
    return FCalculateMuzzleVelocity(pposLaunch, pposTarget, radTilt, pvecMuzzle, psoLaunch);
}

INCLUDE_ASM("asm/nonmatchings/P2/vec", LimitVectorLength);
