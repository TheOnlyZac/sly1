#pragma once
#include <vec.h>

typedef bool BOOL;
typedef unsigned int uint;
typedef unsigned long ulong;

typedef unsigned char byte;
typedef unsigned char BYTE;
typedef unsigned int undefined4;

/* Limit */
struct LM
{
	float gMin, gMax;

	constexpr LM(float min = 0, float max = 1):
		gMin(min), gMax(max)
	{}
};
extern LM g_lmZeroOne;

float RadNormalize(float rad);
float GLimitAbs(float g, float absLimit);
//float GSmooth(float gCur, float gTarget, float dt, SMP* psmp, float* pdgNext);
//float GSmoothA(float gCur, float dgCur, float gTarget, float dt, SMPA* psmpa, float* pdgNext);
//float RadSmooth(float radCur, float radTarget, float dt, SMP* psmp, float* pdradNext);
//float RadSmoothA(float radCur, float dradCur, float radTarget, float dt, SMPA* psmpa, float* pdradNext);
//void SmoothMatrix(MAT* pmatPrev, MAT* pmatNext, SMP* psmp, float dt, MAT* pmatSmooth, VECTOR* pwSmooth);
//VU_VECTOR PosSmooth(VU_VECTOR posCur, VU_VECTOR posTarget, float dt, SMP* psmp, VECTOR* pv);
int NRandInRange(int nLow, int nHigh);
float GRandInRange(float gLow, float gHigh);
float GRandGaussian(float gMean, float gDeviation, float gLimit);
BOOL FFloatsNear(float g1, float g2, float gEpsilon);
int CSolveQuadratic(float a, float b, float c, float* ax);
//void PrescaleClq(CLQ* pclqSrc, float ru, float du, CLQ* pclqDst);
void CalculateSinCos(float rad, float* pgSin, float* pgCos);
double GTrunc(double g);
float GTrunc(float g);
float GModPositive(float gDividend, float gDivisor);
//void FitClq(float g0, float g1, float u, float gU, CLQ* pclq);
BOOL FCheckLm(LM* plm, float g);
BOOL FCheckAlm(int clm, LM* alm, float g);
float GLimitLm(LM* plm, float g);
int SgnCompareG(float* pg1, float* pg2);
void Force(void* pv);
//void MinimizeRange(PFNGG pfn, void* pv, float g, float dg, float gMin, float gMax, float* pgDom, float* pgRng);

//int CSolveClq(CLQ* pclq, float g, float* ag);
//float DtSmooth(float gCur, float gTarget, SMP* psmp, float* pdg);
//void ExtendRange(PFNGG pfn, void* pv, float g, float dg, float gMax, float* pgMic, float* pgMac);
//int NRoundG(float g);
//void SmoothMulti(int c, float dt, float r);
