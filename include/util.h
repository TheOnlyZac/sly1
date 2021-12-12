#pragma once

typedef bool BOOL;

/* Limit */
struct LM
{
	float gMin, gMax;

	inline LM(float min = 0, float max = 1)
	{
		gMin = min;
		gMax = max;
	}
};

static inline LM g_lmZeroOne(0, 1);

float GLimitLm(LM* plm, float g);
float GLimitAbs(float g, float absLimit);
BOOL FCheckLm(LM* plm, float g);
BOOL FCheckAlm(int clm, LM* alm, float g);
BOOL FFloatsNear(float g1, float g2, float gEpsilon);
float GModPositive(float gDividend, float gDivisor);
int CSolveQuadratic(float a, float b, float c, float* ax);
float GRandInRange(float gLow, float gHigh);
int NRandInRange(int nLow, int nHigh);
float RadNormalize(float rad);
int SgnCompareG(float* pg1, float* pg2);