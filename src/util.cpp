#include <util.h>

#include <math.h>
#include <stdlib.h>

static constexpr float PI = 3.141593;

/* Clamp the float to fall inside range given by the limit */
float GLimitLm(LM* plm, float g)
{
	float result = plm->gMin;

	if ((result <= g) &&
		(result = plm->gMax, g <= plm->gMax))
	{
		result = g;
	}

	return result;
}

/* Clamp the float to fall within the range [-absLimit, absLimit] */
float GLimitAbs(float g, float absLimit)
{
	if (g <= absLimit)
	{
		if (g < -absLimit)
		{
			g = -absLimit;
		}
		return g;
	}
	return absLimit;
}

/* Check whether the given float falls within the given limit */
BOOL FCheckLm(LM* plm, float g)

{
	if ((plm->gMin < g) && (g < plm->gMax))
	{
		return true;
	}
	return false;
}

/* Check whether the given float falls within any of the given limits */
BOOL FCheckAlm(int clm, LM* alm, float g)
{
	int lmCur = 0;
	if (0 < clm)
	{
		do
		{
			if (FCheckLm(alm, g)) return true;
			lmCur++;
			alm++;
		} while (lmCur < clm);
	}
	return false;
}

float GModPositive(float gDividend, float gDivisor)
{
	float result = fmodf(gDividend, gDivisor);
	if (result < 0.0)
	{
		result += gDivisor;
	}
	return result;
}

/* Check whether the given floats are near each other based on the given epsilon */
BOOL FFloatsNear(float g1, float g2, float gEpsilon)

{
	float g1Abs = fabs(g1);
	return (BOOL)(unsigned int)(fabs(g1 - g2) / (float)((unsigned int)(g1Abs < 1.0) * 0x3f800000 | (int)g1Abs * (unsigned int)(g1Abs >= 1.0)) < gEpsilon);
}

/* Finds solutions using the quadratic equation. Stores the solutions in ax
   and returns the number of solutions (0, 1, or 2) */
int CSolveQuadratic(float a, float b, float c, float* ax)
{
	float bsquaredMinus4ac = (b * b) - 4.0 * a * c;
	if (bsquaredMinus4ac < 0.0)
	{
		return 0; // no solutions, radicand is negative
	}

	float bsquaredMinus4acOver2a = sqrt(bsquaredMinus4ac) / (2 * a);
	float bOver2a = b / (2 * a);
	if (fabs(bsquaredMinus4acOver2a) < 0.0001)
	{
		*ax = -bOver2a;
		return 1; // one solution: -b / 2a
	}

	ax[1] = -bOver2a - bsquaredMinus4acOver2a;
	*ax = -bOver2a + bsquaredMinus4acOver2a;
	return 2; // two solutions: (-b ± radical) / 2a
}

/* Get a random float that falls between the given values */
float GRandInRange(float gLow, float gHigh)
{
	float result = gLow;
	if (gLow != gHigh)
	{
		int nRand = rand();
		result = gLow + (gHigh - gLow) * (float)nRand * (float)0x30000000;
	}
	return result;
}

/* Get a random int that falls between the given values */
int NRandInRange(int nLow, int nHigh)
{
	int result = nLow;
	if (nLow != nHigh)
	{
		int nRand = rand();
		result = nLow + (nRand % 0x95675) % ((nHigh - nLow) + 1);
	}
	return result;
}

float RadNormalize(float rad)
{
	float result = rad;
	if ((rad < -PI) || (PI < rad))
	{
		float gMod = GModPositive(rad + PI, 2 * PI);
		result = gMod - PI;
	}
	return result;
}

/* Compare the sign of the given two floats */
int SgnCompareG(float* pg1, float* pg2)
{
	int result = 1;
	if ((*pg1 <= *pg2) && (result = -1, *pg2 <= *pg1))
	{
		return 0;
	}
	return result;
}