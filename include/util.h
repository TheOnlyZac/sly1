#pragma once

/* Limit */
struct LM
{
	float gMin, gMax;
	//float u4ag;

	inline LM(float min = 0, float max = 1)
	{
		gMin = min;
		gMax = max;
	}
};

static inline LM g_lmZeroOne(0, 1);

float GLimitLm(LM* plm, float g);
float GLimitAbs(float g, float absLimit);
float GModPositive(float gDividend, float gDivisor);

//float GRandInRange(float gLo, float gHi);
//int NRandInRange(int nLo, int nHi);
