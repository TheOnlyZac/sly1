/**
 * @file vec.h
 *
 * @brief Declares VECTOR and other related classes/functions.
 */
#ifndef VEC_H
#define VEC_H

#include <so.h>

/**
 * @brief Vector3 with X, Y, and Z
 */
struct VECTOR
{
    float x, y, z;
    float gUnused;
};


struct VU_VECTOR
{
    uint16 data;
}

/**
 * @brief Sets the coordinates of a vector using cylindrical coordinates.
 *
 * @param x X coordinate
 * @param y Y coordinate
 * @param z Z coordinate
 * @param pvec Pointer to the vector
 */
void SetVectorCylind(float x, float y, float z, VECTOR *pvec);

/**
 * @brief Sets the coordinates of a vector using spherical coordinates.
 *
 * @param x X coordinate
 * @param y Y coordinate
 * @param z Z coordinate
 * @param pvec Pointer to the vector
 */
void SetVectorSphere(float z, float y, float x, VECTOR *pvec);

/**
 * @brief Projects one vector onto another using scalar projection.
 *
 * @param pvec1 Vector to project
 * @param pvec2 Vector to project onto
 *
 * @return Scalar projection of vec1 onto vec2
 */
float SProjectVector(VECTOR *pvec1, VECTOR *pvec2);

/**
 * @brief Gets the normal vectors of a vector.
 *
 * @param param_1 Unknown
 * @param param_2 Unknown
 * @param param_3 Unknown
 * @param param_4 Unknown
 *
 * @todo Static analysis
 */
void GetNormalVectors(VECTOR *param_1, VECTOR *param_2, VECTOR *param_3, VECTOR *param_4);

/**
 * @brief Gets the normal vector of a vector.
 *
 * @param pvec Pointer to the vector
 * @param presult Pointer to store the resulting normal vector
 */
void GetNormalVector(VECTOR *pvec, VECTOR *presult);

/**
 * @brief Calculates the angle between vectors in radians.
 *
 * @param param_1 Unknown
 * @param param_2 Unknown
 * @param param_3 Unknown
 *
 * @return Angle between vectors in radians
 */
long RadBetweenVectors(VECTOR *pvec1, VECTOR *pvec2, VECTOR *param_3);

/**
 * @brief Finds the closest point between the lines AB and CD.
 *
 * @param pA Pointer to the first point of line AB
 * @param pB Pointer to the second point of line AB
 * @param pC Pointer to the first point of line CD
 * @param pD Pointer to the second point of line CD
 * @param unk_float1 Unknown float
 * @param unk_float2 Unknown float
 * @param presult Pointer to store the resulting point
 */
void FindClosestPointBetweenLines(VECTOR *pA, VECTOR *pB, VECTOR *pC, VECTOR **pD, float *unk_float1, float *unk_float2, VECTOR *presult);

/**
 * @brief Finds the closest point between two line segments.
 *
 * @todo Static analysis of parameters and return values.
 */
void FindClosestPointBetweenLineSegments(VECTOR *param_1, VECTOR *param_2, VECTOR *param_3, VECTOR *param_4, VECTOR param_5, float *param_6, VECTOR *param_7);

/**
 * @brief Calculates the pan and tilt of a vector
 *
 * @param pvec Pointer to the vector
 * @param ppan Float pointer to store the pan result
 * @param ptilt Float pointer to store the tilt result
 */
void CalculateVectorPanTilt(VECTOR *pvec, float *ppan, float *ptilt);

/**
 * @brief Unknown
 *
 * @param param_1 Unknown vector
 * @param param_2 Unknown vector
 * @param param_3 Unknown vector
 */
void ConvertDeulToW(VECTOR *param_1, VECTOR *param_2, VECTOR *param_3);

/**
 * @brief Calculates the muzzle velocity of a projectile.
 *
 * @param param_1 Initial position
 * @param param_2 Target position
 * @param param_3 Target velocity
 * @param param_4 Unknown
 *
 * @note This is an educated guess and may not be accurate.
 */
bool FCalculateMuzzleVelocity(VECTOR *param_1, VECTOR *param_2, VECTOR *param_3, VECTOR *param_4, SO *param_5);

/**
 * @brief Calculates the muzzle velocity angle of a projectile.
 *
 * @param param_1 Initial position
 * @param param_2 Target position
 * @param param_3 Target velocity
 * @param param_4 Unknown
 *
 * @note The name/paremeters for this function are an educated guess and may not be accurate.
 */
uint32_t FCalculateMuzzleVelocityAngle(VECTOR *param_1, VECTOR *param_2, VECTOR *param_3, VECTOR *param_4, SO *param_5);

/**
 * @brief Limits the length of a vector.
 *
 * @param pvec Pointer to the vector
 * @param glength Length to limit the vector to
 * @param presult Pointer to store the resulting vector
 */
void LimitVectorLength(VECTOR *pvec, float glength, VECTOR *presult);

#endif // VEC_H
