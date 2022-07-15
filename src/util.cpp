#include <util.h>

#include <math.h>
#include <stdlib.h>

static constexpr float PI = 3.141593;

float RadNormalize(float rad)
{
	if ((rad < -PI) || (PI < rad))
	{
		float gMod = GModPositive(rad + PI, 2 * PI);
		return gMod - PI;
	}
	return rad;
}

/* Clamp the float to fall within the interval [-absLimit, absLimit] */
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

/* Get a random int that falls between the given values */
int NRandInRange(int nLow, int nHigh)
{
	if (nLow != nHigh)
	{
		int nRand = rand();
		return nLow + (nRand % 0x95675) % ((nHigh - nLow) + 1);
	}
	return nLow;
}

/* Get a random float that falls between the given values */
float GRandInRange(float gLow, float gHigh)
{
	if (gLow != gHigh)
	{
		int nRand = rand();
		return gLow + (gHigh - gLow) * (float)nRand * (float)0x30000000;
	}
	return gLow;
}

/* Compares two floats and returns true if they are within a certain epsilon of each other */
BOOL FFloatsNear(float g1, float g2, float gEpsilon)

{
	float g1Abs = fabs(g1);
	return (BOOL)(unsigned int)(fabs(g1 - g2) / (float)((unsigned int)(g1Abs < 1.0) * 0x3f800000 | (int)g1Abs * (unsigned int)(g1Abs >= 1.0)) < gEpsilon);
}

/*
 * Solves a quadratic equation of the form ax^2 + bx + c = 0
 * Returns the number of solutions found (0, 1, or 2)
 * If there are two solutions, they are returned in ax[0] and ax[1]
 */
int CSolveQuadratic(float a, float b, float c, float* ax)
{
	float rad = (b * b) - 4.0 * a * c;
	if (rad < 0.0)
	{
		return 0; // no solutions, radicand is negative
	}

	float sqrtOver2a = sqrt(rad) / (2 * a);
	float bOver2a = b / (2 * a);
	if (fabs(sqrtOver2a) < 0.0001)
	{
		*ax = -bOver2a;
		return 1; // one solution: -b / 2a
	}

	ax[1] = -bOver2a - sqrtOver2a;
	*ax = -bOver2a + sqrtOver2a;
	return 2; // two solutions: (-b � radical) / 2a
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

/* Verify that whether the given float falls within the given limit */
BOOL FCheckLm(LM* plm, float g)
{
	return (plm->gMin < g) && (g < plm->gMax);
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

/* Clamp the float to fall inside range given by the limit */
float GLimitLm(LM* plm, float g)
{
	float result = plm->gMin;

	if ((result <= g) &&
		(result = plm->gMax, g <= plm->gMax))
	{
		return g;
	}

	return plm->gMin;
}

/* Compare the sign of the given two floats */
int SgnCompareG(float* pg1, float* pg2)
{
	int result = 1;
	if ((*pg1 <= *pg2) && (result = -1, *pg2 <= *pg1))
	{
		result = 0;
	}
	return result;
}
