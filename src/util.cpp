#include <util.h>
#include <math.h>

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
	float g1Abs = abs(g1);
	return (BOOL)(unsigned int)(abs(g1 - g2) / (float)((unsigned int)(g1Abs < 1.0) * 0x3f800000 | (int)g1Abs * (unsigned int)(g1Abs >= 1.0)) < gEpsilon);
}
