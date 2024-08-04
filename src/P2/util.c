#include <util.h>
#include <sce/rand.h>
#include <sce/math.h>

static const float PI = 3.14159265359f;

float RadNormalize(float rad)
{
    if ((rad < -PI) || (PI < rad)) 
    {
        float modpos = GModPositive(rad + PI, 2 * PI);
        rad = modpos - PI;
    }
    return rad;
}

INCLUDE_ASM(const s32, "P2/util", GLimitAbs);

INCLUDE_ASM(const s32, "P2/util", GSmooth__FfffP3SMPPf);

INCLUDE_ASM(const s32, "P2/util", GSmoothA__FffffP4SMPAPf);
INCLUDE_ASM(const s32, "P2/util", func_001EA720);

float RadSmooth(float radCur, float radTarget, float dt, SMP *psmp, float *pdradNext)
{
    float fVar1;
    
    fVar1 = RadNormalize(radTarget - radCur);
    fVar1 = GSmooth(0.0, fVar1, dt, psmp, pdradNext);
    fVar1 = RadNormalize(radCur + fVar1);
    return fVar1;
}

float RadSmoothA(float radCur, float dradCur, float radTarget, float dt, SMPA *psmpa, float *pdradNext)
{
    float fVar1;

    fVar1 = RadNormalize(radTarget - radCur);
    fVar1 = GSmoothA(0.0, dradCur, fVar1, dt, psmpa, pdradNext);
    fVar1 = RadNormalize(radCur + fVar1);
    return fVar1;
}

INCLUDE_ASM(const s32, "P2/util", PosSmooth);

INCLUDE_ASM(const s32, "P2/util", SmoothMatrix);

const int PRIME_MOD = 0x95675;

// Generates a random integer in the range [nLow, nHi]
int NRandInRange(int nLow, int nHi) 
{
    if (nLow == nHi)
    {
        return nLow;
    }

    int randVal = rand();
    randVal = randVal % PRIME_MOD;

    int range = (nHi - nLow) + 1;

    // Return a value within the range [nLow, nHi]
    return nLow + (randVal % range);
}

float GRandInRange(float gHi,float gLow)
{
    int rand_result;
    float delta;
    float result;
    if (gHi != gLow)
    {
        rand_result = rand();
        delta = gLow - gHi;
        result = gHi + delta * (float)rand_result * 4.656613e-10f;
    }
    else
    {
        result = gHi;
    }
    return result;
}

INCLUDE_ASM(const s32, "P2/util", GRandGaussian);

int FFloatsNear(float g1,float g2,float gEpsilon)
{
    float x = 1.0f;
    g2 = g1-g2;
    g1 = g1 > 0.0f ? g1 : -g1;
    g2 = g2 > 0.0f ? g2 : -g2;
    x = g1 > x ? g1 : x;
    

    g2 = g2 / x;
    if(g2 < gEpsilon)
    {
        return 1;
    }    
    return 0;
}

INCLUDE_ASM(const s32, "P2/util", CSolveQuadratic);

INCLUDE_ASM(const s32, "P2/util", PrescaleClq);

INCLUDE_ASM(const s32, "P2/util", CalculateSinCos__FfPfT1);

INCLUDE_ASM(const s32, "P2/util", GTrunc);

INCLUDE_ASM(const s32, "P2/util", GTrunc1);

float GModPositive(float gDividend, float gDivisor)
{
	float result = fmodf(gDividend, gDivisor);
	if (result < 0.0f)
	{
		result += gDivisor;
	}
	return result;
}

void FitClq(float g0, float g1, float u, float gU, CLQ *pclq)
{
    float fVar1;

    pclq->u = g0;
    fVar1 = ((gU - g0) / u - (g1 - g0)) / (u - 1.0f);
    pclq->w = fVar1;
    pclq->v = (g1 - g0) - fVar1;
}

int FCheckLm(LM* plm, float g)
{
	return (plm->gMin < g) && (g < plm->gMax);
}

INCLUDE_ASM(const s32, "P2/util", FCheckAlm);

float GLimitLm(struct LM* plm, float g)
{
	if (g < plm->gMin)
	{
		return plm->gMin;
	}
	if (g > plm->gMax)
	{
		return plm->gMax;
	}
	return g;
}

int SgnCompareG(float *pg1,float *pg2)
{
    int iVar1;
    
    iVar1 = 1;
    if (*pg1 > *pg2)
    {
        return iVar1;
    }
    iVar1 = -1;
    if(*pg2 > *pg1)
    {
        return iVar1;
    }
    return 0;
}

void Force(void *pv)
{
	// Stubbed, does nothing.
}

INCLUDE_ASM(const s32, "P2/util", MinimizeRange);
INCLUDE_ASM(const s32, "P2/util", func_001EB458);
