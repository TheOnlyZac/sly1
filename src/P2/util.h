/**
 * @file util.h
 *
 * @brief Declarations for utility functions.
*/
#ifndef UTIL_H
#define UTIL_H

#include <types.h>

/**
 * @brief Limits for a float
*/
struct LM
{
	float gMin, gMax;
};

// Global variables
extern LM g_lmZeroOne; // Limits with the range [0, 1]

/**
 * @brief Normalizes a float to the range [-PI, PI].
 *
 * @param rad The float to normalize
 *
 * @retval The normalized float
*/
float RadNormalize(float rad);

/**
 * @brief Clamps the float to the inteval [-absLimit, absLimit]
 *
 * @param g The float to clamp
 * @param absLimit The limit to clamp to
 *
 * @retval The clamped float
*/
float GLimitAbs(float g, float absLimit);

//float GSmooth(float gCur, float gTarget, float dt, SMP* psmp, float* pdgNext);
//float GSmoothA(float gCur, float dgCur, float gTarget, float dt, SMPA* psmpa, float* pdgNext);
//float RadSmooth(float radCur, float radTarget, float dt, SMP* psmp, float* pdradNext);
//float RadSmoothA(float radCur, float dradCur, float radTarget, float dt, SMPA* psmpa, float* pdradNext);
//void SmoothMatrix(MAT* pmatPrev, MAT* pmatNext, SMP* psmp, float dt, MAT* pmatSmooth, VECTOR* pwSmooth);
//VU_VECTOR PosSmooth(VU_VECTOR posCur, VU_VECTOR posTarget, float dt, SMP* psmp, VECTOR* pv);

/**
 * @brief Gets a random int that falls between the given values.
 *
 * @param nLow The lower bound
 * @param nHigh The upper bound
 *
 * @retval A random int that falls between the given values
*/
int NRandInRange(int nLow, int nHigh);

/**
 * @brief Gets a random float that falls between the given values.
 *
 * @param gLow The lower bound
 * @param gHigh The upper bound
 *
 * @retval A random float that falls between the given values
*/
float GRandInRange(float gLow, float gHigh);

/**
 * @brief Returns a random number from the Gaussian distribution.
 *
 * @param gMean The mean of the distribution
 * @param gDeviation The standard deviation of the distribution
 * @param gLimit The limit of the distribution
 *
 * @retval A random number from the Gaussian distribution
*/
float GRandGaussian(float gMean, float gDeviation, float gLimit);

/**
 * @brief Checks if two floats are within a given epsilon of each other.
 *
 * @param g1 The first float
 * @param g2 The second float
 * @param gEpsilon The epsilon
 *
 * @retval true if the floats are within the epsilon of each other
 * @retval false otherwise
*/
BOOL FFloatsNear(float g1, float g2, float gEpsilon);

/**
 * @brief Solves a quadratic equation.
 *
 * A quadratic equation is of the form ax^2 + bx + c = 0. The solutions (if any)
 * are stored in the given array.
 *
 * @param a The coefficient of the x^2 term
 * @param b The coefficient of the x term
 * @param c The constant term
 * @param ax The array to store the solutions in
 *
 * @return The number of solutions found (0, 1, or 2)
*/
int CSolveQuadratic(float a, float b, float c, float* ax);

//void PrescaleClq(CLQ* pclqSrc, float ru, float du, CLQ* pclqDst);

/**
 * @brief Calculates the sine and cosine of a given angle.
 *
 * @param rad The angle
 * @param pgSin The pointer to store the sine in
 * @param pgCos The pointer to store the cosine in
*/
void CalculateSinCos(float rad, float* pgSin, float* pgCos);

/**
 * @brief Truncates a double precision floating point number to an integer value,
 * rounding up if the fractional part is exactly 0.5.
 *
 * @param g The double precision floating point number to truncate
*/
double GTrunc(double g);

/**
 * @brief Truncates a single precision floating point number to an integer value,
 * rounding up if the fractional part is exactly 0.5.
 *
 * @param g The single precision floating point number to truncate
*/
float GTrunc(float g);

/**
 * @brief Calculates the positive remainder of dividing the dividend by the divisor.
 *
 * If the result is negative, it is adjusted to be positive by adding the divisor.
 *
 * @param gDividend The dividend.
 * @param gDivisor The divisor.
 *
 * @return The positive remainder of the division.
*/
float GModPositive(float gDividend, float gDivisor);

//void FitClq(float g0, float g1, float u, float gU, CLQ* pclq);

/**
 * @brief Checks if a float falls within the given limit.
 *
 * @param plm Pointer to the limit
 * @param g The float to check
*/
BOOL FCheckLm(LM* plm, float g);

/**
 * @brief Checks if a float falls within any of the given limits.
 *
 * @param clm The number of limits
 * @param alm Array of limits
 * @param g The float to check
*/
BOOL FCheckAlm(int clm, LM* alm, float g);

/**
 * @brief Clamps a float to fall within the given limit.
 *
 * @param plm Pointer to the limit
 * @param g The float to clamp
*/
float GLimitLm(LM* plm, float g);

/**
 * @brief Compares the sign of two floats.
 *
 * @param pg1 Pointer to the first float
 * @param pg2 Pointer to the second float
 *
 * @retval 1 if the signs are the same
 * @retval -1 if the signs are different
 * @retval 0 if either float is 0
*/
int SgnCompareG(float* pg1, float* pg2);

/**
 * @brief Stubbed function, does nothing.
 *
 * @param pv Pointer to some data
*/
void Force(void* pv);

//void MinimizeRange(PFNGG pfn, void* pv, float g, float dg, float gMin, float gMax, float* pgDom, float* pgRng);

//int CSolveClq(CLQ* pclq, float g, float* ag);
//float DtSmooth(float gCur, float gTarget, SMP* psmp, float* pdg);
//void ExtendRange(PFNGG pfn, void* pv, float g, float dg, float gMax, float* pgMic, float* pgMac);
//int NRoundG(float g);
//void SmoothMulti(int c, float dt, float r);

#endif // UTIL_H
