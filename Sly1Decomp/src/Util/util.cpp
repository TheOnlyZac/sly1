#include "util.h"

float GLimitLm(LM* plm, float g)
{
	float result;
	result = plm->gMin;
	if ((result <= g) &&
		(result = plm->gMax, g <= plm->gMax))
	{
		result = g;
	}
	return result;
}
