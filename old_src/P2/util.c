/**
 * @file util.cpp
 *
 * @brief Implements various utility/math functions.
*/
#include <util.h>
#include <cmath>
#include <cstdlib> // todo: implement rng functions to avoid using stdlib

static const float PI = 3.141593;
LM g_lmZeroOne = { 0.0f, 1.0f };

float RadNormalize(float rad)
{
	if ((rad < -PI) || (PI < rad))
	{
		float gMod = GModPositive(rad + PI, 2 * PI);
		return gMod - PI;
	}
	return rad;
}

float GLimitAbs(float g, float absLimit)
{
	if (absLimit < g)
	{
		if (g < -absLimit)
		{
			return -absLimit;
		}
		return absLimit;
	}
	return g;
}

//INCLUDE_ASM(const s32, "P2/util", GSmooth);

//INCLUDE_ASM(const s32, "P2/util", GSmoothA);
//INCLUDE_ASM(const s32, "P2/util", func_001EA720); // Part of GSmoothA

//INCLUDE_ASM(const s32, "P2/util", RadSmooth);

//INCLUDE_ASM(const s32, "P2/util", RadSmoothA);

//INCLUDE_ASM(const s32, "P2/util", PosSmooth);

//INCLUDE_ASM(const s32, "P2/util", SmoothMatrix);

int NRandInRange(int nLow, int nHigh)
{
	if (nLow != nHigh)
	{
		int nRand = rand();
		return nLow + (nRand % 0x95675) % ((nHigh - nLow) + 1);
	}
	return nLow;
}

float GRandInRange(float gLow, float gHigh)
{
	if (gLow != gHigh)
	{
		int nRand = rand();
		return gLow + (gHigh - gLow) * (float)nRand * (float)0x30000000;
	}
	return gLow;
}

float GRandGaussian(float param_1, float param_2, float param_3)
{
	float fVar1;
	float fVar2;
	float fVar3;
	float fVar4;

	fVar3 = -1.0f;
	fVar4 = 0.0f;
	do {
		do {
			fVar1 = (float)GRandInRange(fVar3, 1.0f);
			fVar2 = (float)GRandInRange(fVar3, 1.0f);
			fVar1 = fVar1 * fVar1 + fVar2 * fVar2;
		} while (1.0f < fVar1);
	} while (fVar1 == fVar4);
	fVar3 = logf(fVar1);
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

BOOL FFloatsNear(float g1, float g2, float gEpsilon)
{
	float g1Abs = fabs(g1);
	return (BOOL)(unsigned int)(fabs(g1 - g2) / (float)((unsigned int)(g1Abs < 1.0) * 0x3f800000 | (int)g1Abs * (unsigned int)(g1Abs >= 1.0)) < gEpsilon);
}

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
	return 2; // two solutions: (-b ± radical) / 2a
}

//INCLUDE_ASM(const s32, "P2/util", PrescaleClq);

void CalculateSinCos(float angle, float *sin, float *cos)
{
	uint uVar1;
	float fVar2;
	float fVar3;
	float fVar4;
	float fVar5;

	fVar2 = (angle + PI/2) * 0.3183099;
	uVar1 = (uint)fVar2;
	if (fVar2 < 0.0)
		uVar1 = uVar1 - 1;
	fVar2 = angle - (float)uVar1 * PI;
	if ((uVar1 & 1) != 0)
		fVar2 = -fVar2;
	fVar3 = fVar2 * fVar2;
	fVar4 = fVar2 * fVar3 * fVar3;
	fVar5 = fVar4 * fVar3;
	fVar3 = fVar2 +
		fVar2 * fVar3 * -0.1666666 +
		fVar4 * 0.008333026 +
		fVar5 * -0.0001980741 +
		fVar5 * fVar3 * 2.601887e-06;

	fVar2 = sqrtf(1.0 - fVar3 * fVar3);
	if ((uVar1 & 1) != 0)
		fVar2 = -fVar2;

	*cos = fVar2;
	*sin = fVar3;
}

double GTrunc(double param_1)
{
	ulong uVar1;
	ulong uVar2;
	int iVar3;

	iVar3 = ((uint)((ulong)param_1 >> 0x34) & 0x7ff) - 0x3ff;
	if (iVar3 < 0)
		param_1 = 0.0;
	else
	{
		if (iVar3 < 0x34)
		{
			uVar2 = (ulong)param_1 & 0xfffffffffffff;
			uVar1 = (1 << (long)(0x34 - iVar3)) - 1;
			if ((uVar2 & uVar1) == uVar1)
				param_1 = (double)((ulong)param_1 & 0xfff0000000000000 | uVar2 & ~uVar1) + 1.0;
			else
				param_1 = (double)((ulong)param_1 & 0xfff0000000000000 | uVar2 & ~uVar1);
		}
	}
	return param_1;
}

float GTrunc(float param_1)
{
	uint uVar1;
	int iVar2;
	uint uVar3;
	ulong local_10;

	local_10 = (ulong)(uint)param_1;
	iVar2 = ((uint)((local_10 << 9) >> 0x20) & 0xff) - 0x7f;
	if (iVar2 < 0)
		param_1 = 0.0;
	else
	{
		if (iVar2 < 0x17)
		{
			uVar1 = (int)(1 << (long)(0x17 - iVar2)) - 1;
			uVar3 = (uint)param_1 & 0x7fffff;
			if ((uVar3 & uVar1) == uVar1)
				param_1 = (float)((uint)param_1 & 0xff800000 | uVar3 & ~uVar1) + 1.0f;
			else
				param_1 = (float)((uint)param_1 & 0xff800000 | uVar3 & ~uVar1);
		}
	}
	return param_1;
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

//INCLUDE_ASM(const s32, "P2/util", FitClq);

/**
 * @note Matching 100%
*/
BOOL FCheckLm(LM* plm, float g)
{
	return (plm->gMin < g) && (g < plm->gMax);
}

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

float GLimitLm(LM* plm, float g)
{
	if (g <= plm->gMin)
	{
		return plm->gMin;
	}
	else if (plm->gMax <= g)
	{
		return plm->gMax;
	}
	else
	{
		return g;
	}
}

int SgnCompareG(float* pg1, float* pg2)
{
	int result = 1;
	if ((*pg1 <= *pg2) && (result = -1, *pg2 <= *pg1))
	{
		result = 0;
	}
	return result;
}

/**
 * @note Matching 100%
*/
void Force(void *)
{
	// This function is empty.
	return;
}

//INCLUDE_ASM(const s32, "P2/util", MinimizeRange);
//INCLUDE_ASM(const s32, "P2/util", func_001EB458);
