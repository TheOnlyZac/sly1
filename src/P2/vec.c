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

INCLUDE_ASM(const s32, "P2/vec", SProjectVector);

INCLUDE_ASM(const s32, "P2/vec", GetNormalVectors);

INCLUDE_ASM(const s32, "P2/vec", GetNormalVector);

INCLUDE_ASM(const s32, "P2/vec", func_001ED900);

INCLUDE_ASM(const s32, "P2/vec", RadBetweenVectors);

INCLUDE_ASM(const s32, "P2/vec", FindClosestPointBetweenLines);

INCLUDE_ASM(const s32, "P2/vec", FindClosestPointBetweenLineSegments);

INCLUDE_ASM(const s32, "P2/vec", CalculateVectorPanTilt);

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
