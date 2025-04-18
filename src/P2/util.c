#include <gcc/math.h>
#include <sce/rand.h>
#include <util.h>
#include <vec.h>

static const float PI = 3.14159265359f;
const int PRIME_MOD = 0x95675;

float RadNormalize(float rad)
{
    if ((rad < -PI) || (PI < rad))
    {
        float modpos = GModPositive(rad + PI, 2 * PI);
        rad = modpos - PI;
    }
    return rad;
}

float GLimitAbs(float g,float absLimit)
{
    if (g > absLimit)
    {
        g = absLimit;
    }
    else if (g < -absLimit)
    {
        g = -absLimit;
    }
    return g;
}

INCLUDE_ASM(const s32, "P2/util", GSmooth__FfffP3SMPPf);

INCLUDE_ASM(const s32, "P2/util", GSmoothA__FffffP4SMPAPf);
INCLUDE_ASM(const s32, "P2/util", func_001EA720);

float RadSmooth(float radCur, float radTarget, float dt, SMP *psmp, float *pdradNext)
{
    float rad;
    rad = RadNormalize(radTarget - radCur);
    rad = GSmooth(0.0, rad, dt, psmp, pdradNext);
    rad = RadNormalize(radCur + rad);
    return rad;
}

float RadSmoothA(float radCur, float dradCur, float radTarget, float dt, SMPA *psmpa, float *pdradNext)
{
    float rad;
    rad = RadNormalize(radTarget - radCur);
    rad = GSmoothA(0.0, dradCur, rad, dt, psmpa, pdradNext);
    rad = RadNormalize(radCur + rad);
    return rad;
}

INCLUDE_ASM(const s32, "P2/util", PosSmooth);

INCLUDE_ASM(const s32, "P2/util", SmoothMatrix);

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

float GRandInRange(float gHi, float gLow)
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

int FFloatsNear(float g1, float g2, float gEpsilon)
{
    g2 = g1 - g2;
    g1 = g1 > 0.0f ? g1 : -g1;
    g2 = g2 > 0.0f ? g2 : -g2;

    float x = 1.0f;
    x = g1 > x ? g1 : x;

    return (g2 / x) < gEpsilon;
}

/**
 * @todo 94.29% matched
 * https://decomp.me/scratch/A4VOu
 */
INCLUDE_ASM(const s32, "P2/util", CSolveQuadratic__FfffPf);
#ifdef SKIP_ASM
int CSolveQuadratic(float a, float b, float c, float *ax)
{
    float alpha;
    float beta;

    alpha = b * b - 4.f * a * c;
    a = a * 2;

    if (alpha < 0.0f)
    {
        return 0;
    }
    else
    {
        beta = b / a;
        alpha = sqrtf(alpha) / a;
        if (fabsf(alpha) < 0.0001f)
        {
            *ax = -beta;
            return 1;
        }

        *ax = -beta + alpha;
        ax[1] = -beta - alpha;
        return 2;
    }
}
#endif // SKIP_ASM

void PrescaleClq(CLQ *pclqSrc, float ru, float du, CLQ *pclqDst)
{
    pclqDst->w = pclqSrc->w * ru * ru;
    pclqDst->v = (pclqSrc->w + pclqSrc->w) * ru * du + pclqSrc->v * ru;
    pclqDst->u = pclqSrc->w * du * du + pclqSrc->v * du + pclqSrc->u;
}

INCLUDE_ASM(const s32, "P2/util", CalculateSinCos__FfPfT1);

INCLUDE_ASM(const s32, "P2/util", GTrunc); // double version

INCLUDE_ASM(const s32, "P2/util", GTrunc1); // float version

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
    pclq->u = g0;
    float f = ((gU - g0) / u - (g1 - g0)) / (u - 1.0f);
    pclq->w = f;
    pclq->v = (g1 - g0) - f;
}

int FCheckLm(LM *plm, float g)
{
    return (plm->gMin < g) && (g < plm->gMax);
}

bool FCheckAlm(int clm, LM* alm, float g)
{
    for (int i = 0; i < clm; i++)
    {
        if (FCheckLm(alm+i, g) != 0)
        {
            return true;
        }
    }
    return false;
}

float GLimitLm(struct LM *plm, float g)
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

int SgnCompareG(float *pg1, float *pg2)
{
    if (*pg1 > *pg2)
    {
        return 1;
    }
    else if (*pg2 > *pg1)
    {
        return -1;
    }
    return 0;
}

void Force(void *pv)
{
    return;
}

INCLUDE_ASM(const s32, "P2/util", MinimizeRange);
INCLUDE_ASM(const s32, "P2/util", func_001EB458);
