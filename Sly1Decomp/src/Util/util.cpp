#include "util.h"

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

