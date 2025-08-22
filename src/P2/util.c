#include <gcc/math.h>
#include <sce/rand.h>
#include <util.h>
#include <vec.h>

static const float PI = 3.14159265359f;
const int PRIME_MOD = 0x95675;

#ifdef SKIP_ASM
LM g_lmZeroOne = {0.0f, 1.0f};
#endif

float RadNormalize(float rad)
{
    if ((rad < -PI) || (PI < rad))
    {
        float modpos = GModPositive(rad + PI, 2 * PI);
        rad = modpos - PI;
    }
    return rad;
}

float GLimitAbs(float g, float absLimit)
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

INCLUDE_ASM(const s32, "P2/util", GRandGaussian__Ffff);
#ifdef SKIP_ASM
/**
 * @todo 64.35% matched.
 * log function needs to be defined. Does it use sce math lib?
 */
float GRandGaussian(float param_1, float param_2, float param_3)
{
    float fVar1;
    float fVar2;
    float fVar3;
    float fVar4;

    fVar3 = -1.0f;
    fVar4 = 0.0f;
    do
    {
        do
        {
            fVar1 = (float)GRandInRange(fVar3, 1.0f);
            fVar2 = (float)GRandInRange(fVar3, 1.0f);
            fVar1 = fVar1 * fVar1 + fVar2 * fVar2;
        } while (1.0f < fVar1);
    } while (fVar1 == fVar4);
    // fVar3 = logf(fVar1);
    fVar4 = param_1 + param_2 * fVar2 * sqrtf((fVar3 * -2.0f) / fVar1);
    fVar3 = fVar4;
    if (param_3 != 0.0f)
    {
        fVar3 = param_1 - param_3;
        if ((param_1 - param_3 <= fVar4) && (fVar3 = fVar4, param_1 + param_3 < fVar4))
            fVar3 = param_1 + param_3;
    }
    return fVar3;
}
#endif // SKIP_ASM

int FFloatsNear(float g1, float g2, float gEpsilon)
{
    g2 = g1 - g2;
    g1 = g1 > 0.0f ? g1 : -g1;
    g2 = g2 > 0.0f ? g2 : -g2;

    float x = 1.0f;
    x = g1 > x ? g1 : x;

    return (g2 / x) < gEpsilon;
}

INCLUDE_ASM(const s32, "P2/util", CSolveQuadratic__FfffPf);
#ifdef SKIP_ASM
/**
 * @todo 95.96% matched.
 *
 * Compiler is using bc1f instead of bc1fl for (alpha < 0.0f) branch.
 *
 * https://decomp.me/scratch/A4VOu
 */
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
#ifdef SKIP_ASM
/**
 * @tod 86.55% matched.
 */
void CalculateSinCos(float angle, float *sin, float *cos)
{
    // Constants from the assembly (hex to float)
    const float PI_OVER_2 = 1.57079637051f; // 0x3FC90FDB
    const float INV_PI = 0.31830987334f;    // 0x3EA2F983
    const float PI = 3.14159274101f;        // 0x40490FDB

    // Polynomial coefficients (from hex in asm)
    const float C1 = -0.1666666279f;   // 0xBE2AAAA4
    const float C2 = 0.00833302546f;   // 0x3C08873E
    const float C3 = -0.000198074187f; // 0xB94FB21F
    const float C4 = 2.601887e-06f;    // 0x362E9C14

    float x = (angle + PI_OVER_2) * INV_PI;
    int n = (int)x;
    if (x < 0.0f)
        n -= 1;
    int odd = n & 1;
    float xn = (float)n;
    float theta = angle - xn * PI;
    if (odd)
        theta = -theta;

    float theta2 = theta * theta;
    float s = theta;
    float t = theta2 * theta;
    float u = t * theta2;
    float v = u * theta2;
    float w = v * theta2;

    float result = s + t * C1 + u * C2 + v * C3 + w * C4;

    float result2 = 1.0f - result * result;
    if (odd)
        result2 = -result2;

    *sin = result;
    *cos = result2;
}
#endif // SKIP_ASM

INCLUDE_ASM(const s32, "P2/util", GTrunc__Fd); // double version
#ifdef SKIP_ASM
/**
 * @todo 34.18% matched.
 */
double GTrunc(double param_1)
{
    union
    {
        double d;
        ulong u;
    } conv;
    conv.d = param_1;

    int exp = (int)((conv.u >> 52) & 0x7FF) - 0x3FF;
    if (exp < 0)
        return 0.0;
    if (exp >= 52)
        return param_1;

    ulong mask = (1ULL << (52 - exp)) - 1;
    ulong frac = conv.u & 0xFFFFFFFFFFFFF;
    ulong intpart = conv.u & ~mask;

    if ((frac & mask) == mask)
    {
        // Special case: all masked bits set, round up
        intpart += (1ULL << (52 - exp));
        // Clear fraction bits
        intpart &= ~mask;
    }

    conv.u = intpart;
    return conv.d;
}
#endif

INCLUDE_ASM(const s32, "P2/util", GTrunc__Ff); // float version
#ifdef SKIP_ASM
/**
 * @todo 36.07% matched.
 */
float GTrunc(float param_1)
{
    union
    {
        float f;
        uint u;
    } conv;
    conv.f = param_1;

    int exp = ((conv.u >> 23) & 0xFF) - 0x7F;
    if (exp < 0)
        return 0.0f;
    if (exp >= 0x17)
        return param_1;

    uint mask = (1u << (0x17 - exp)) - 1;
    uint frac = conv.u & 0x7FFFFF;
    if ((frac & mask) == mask)
    {
        // All masked bits set, round up
        conv.u = (conv.u & 0xFF800000) | (frac & ~mask);
        conv.f += 1.0f;
        return conv.f;
    }
    else
    {
        conv.u = (conv.u & 0xFF800000) | (frac & ~mask);
        return conv.f;
    }
}
#endif // SKIP_ASM

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

bool FCheckAlm(int clm, LM *alm, float g)
{
    for (int i = 0; i < clm; i++)
    {
        if (FCheckLm(alm + i, g) != 0)
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
