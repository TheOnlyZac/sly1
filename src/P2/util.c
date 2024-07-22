#include <util.h>
#include <sce/rand.h>

static const float PI = 3.14159265359f;

float RadNormalize(float rad)
{
  if ((rad < -PI) || (PI < rad)) {
    float modpos = GModPositive(rad + PI, 2 * PI);
    rad = modpos - PI;
  }
  return rad;
}

INCLUDE_ASM(const s32, "P2/util", GLimitAbs);

INCLUDE_ASM(const s32, "P2/util", GSmooth);

INCLUDE_ASM(const s32, "P2/util", GSmoothA);
INCLUDE_ASM(const s32, "P2/util", func_001EA720);

INCLUDE_ASM(const s32, "P2/util", RadSmooth);

INCLUDE_ASM(const s32, "P2/util", RadSmoothA);

INCLUDE_ASM(const s32, "P2/util", PosSmooth);

INCLUDE_ASM(const s32, "P2/util", SmoothMatrix);

const int PRIME_MOD = 0x95675;

// Generates a random integer in the range [nLow, nHi]
int NRandInRange(int nLow, int nHi) {
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

INCLUDE_ASM(const s32, "P2/util", GRandInRange);

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

INCLUDE_ASM(const s32, "P2/util", GModPositive__Fff);

INCLUDE_ASM(const s32, "P2/util", FitClq);

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

INCLUDE_ASM(const s32, "P2/util", SgnCompareG);

void Force(void *pv)
{
	// Stubbed, does nothing.
}

INCLUDE_ASM(const s32, "P2/util", MinimizeRange);
INCLUDE_ASM(const s32, "P2/util", func_001EB458);
