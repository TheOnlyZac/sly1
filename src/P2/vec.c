#include <vec.h>
#include <util.h>

void SetVectorCylind(VECTOR *pvec, float rad, float sXY, float sZ)
{
    float gSin;
    float gCos;

    CalculateSinCos(rad, &gSin, &gCos);
    pvec->z = sZ;
    pvec->x = gCos * sXY;
    pvec->y = gSin * sXY;
}

void SetVectorSphere(VECTOR *pvec, float radPan, float radTilt, float s)
{
    float gSinPan;
    float gCosPan;
    float gSinTilt;
    float gCosTilt;

    CalculateSinCos(radPan,&gSinPan, &gCosPan);
    CalculateSinCos(radTilt, &gSinTilt, &gCosTilt);
    pvec->z = gSinTilt * s;
    pvec->x = gCosTilt * gCosPan * s;
    pvec->y = gCosTilt * gSinPan * s;
}

INCLUDE_ASM(const s32, "P2/vec", SProjectVector__FP6VECTORT0);

INCLUDE_ASM(const s32, "P2/vec", GetNormalVectors__FP6VECTORN30);

INCLUDE_ASM(const s32, "P2/vec", GetNormalVector__FP6VECTORT0);

INCLUDE_ASM(const s32, "P2/vec", func_001ED900);

INCLUDE_ASM(const s32, "P2/vec", RadBetweenVectors__FP6VECTORN20);

INCLUDE_ASM(const s32, "P2/vec", FindClosestPointBetweenLines__FP6VECTORN30PfT4T0);

INCLUDE_ASM(const s32, "P2/vec", FindClosestPointBetweenLineSegments__FP6VECTORN40PfT0);

INCLUDE_ASM(const s32, "P2/vec", CalculateVectorPanTilt__FP6VECTORPfT1);
#ifdef SKIP_ASM
/**
 * @todo 51.53% matched.
 * Depends on trig functions that aren't implemented.
 */
void CalculateVectorPanTilt(VECTOR* pvec, float* ppan, float* ptilt)
{
    float val;

    if (*ppan != 0.0)
    {
        // val = atan2f(pvec->y, pvec->x);
        // fVar1 = FUN_001ea408(fVar1);
        *ppan = val;
    }
    if (*ptilt != 0.0)
    {
        // val = atan2f(pvec->z, sqrt(pvec->x * pvec->x + pvec->y * pvec->y));
        // val = FUN_001ea408(val); // todo implement function
        *ptilt = val;
    }
    return;
}
#endif // SKIP_ASM

void ConvertDeulToW(VECTOR *peul, VECTOR *pdeul, VECTOR *pw)
{
    float ySin;
    float yCos;
    float zSin;
    float zCos;

    CalculateSinCos(peul->y, &ySin, &yCos);
    CalculateSinCos(peul->z, &zSin, &zCos);

    pw->x = yCos * zCos * pdeul->x - zSin * pdeul->y;
    pw->y = yCos * zSin * pdeul->x + zCos * pdeul->y;
    pw->z = -ySin * pdeul->x + pdeul->z;
}

INCLUDE_ASM(const s32, "P2/vec", FCalculateMuzzleVelocity__FP6VECTORT0fT0P2SO);

INCLUDE_ASM(const s32, "P2/vec", FCalculateMuzzleVelocity1);

int FCalculateMuzzleVelocityAngle(VECTOR *pposLaunch,VECTOR *pposTarget,float radTilt,VECTOR *pvecMuzzle,SO *psoLaunch)
{
  return FCalculateMuzzleVelocity(pposLaunch, pposTarget, radTilt, pvecMuzzle, psoLaunch);
}

INCLUDE_ASM(const s32, "P2/vec", LimitVectorLength);
