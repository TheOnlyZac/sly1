/**
 * @file vec.h
 *
 * @brief Vector math.
 */
#ifndef VEC_H
#define VEC_H

#include "common.h"

struct SO;

/**
 * @brief Vector3 with X, Y, and Z.
 * @todo This should be 16 bytes in size.
 */
struct VECTOR
{
    float x, y, z;
};

struct VECTOR4
{
    float x, y, z, w;
};

/**
 * @todo Should be 16-byte aligned.
 */
struct VU_VECTOR
{
    ushort data;
};

/**
 * @brief Sets the coordinates of a vector using cylindrical coordinates.
 *
 * @param pvec Pointer to the vector
 * @param rad Degrees in radians
 * @param sXY XY-Scale/Radius
 * @param sZ Z Offset
 */
void SetVectorCylind(VECTOR *pvec, float rad, float sXY, float sZ);

/**
 * @brief Sets the coordinates of a vector using spherical coordinates.
 *
 * @param pvec Pointer to the vector
 * @param radPan Angle around Z axis
 * @param radTilt Angle above horizontal
 * @param s Scale/Radius
 */
void SetVectorSphere(VECTOR *pvec, float radPan, float radTilt, float s);

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
 * @param pvecStart Unknown
 * @param pvecFinish Unknown
 * @param pnormal Unknown
 *
 * @return Angle between vectors in radians.
 */
long RadBetweenVectors(VECTOR *pvecStart, VECTOR *pvecFinish, VECTOR *pnormal);

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
 * @param pradPan Float pointer to store the pan result
 * @param pradTilt Float pointer to store the tilt result
 */
void CalculateVectorPanTilt(VECTOR *pvec, float *pradPan, float *pradTilt);

/**
 * @brief Creates a vector from a rotation vector and an offset vector
 *
 * @details Use the peul vector to define euler angles for a vector,
 * Using the forward vector as a reference direction,
 * pdeul's X is a Rightward offset
 * pdeul's Y is a Forward offset
 * pdeul's Z is a Vertical offset
 *
 * @param peul Rotation vector, defines a "forward"
 * @param pdeul Offset vector
 * @param pw Resultant Vector
 */
void ConvertDeulToW(VECTOR *peul, VECTOR *pdeul, VECTOR *pw);

/**
 * @brief Calculates the muzzle velocity of a projectile.
 *
 * @param pposLaunch Initial position
 * @param pposTarget Target position
 * @param radVert Vertical angle?
 * @param pvecMuzzle Target velocity
 * @param psoLaunch Unknown
 *
 * @note This is an educated guess and may not be accurate.
 */
int FCalculateMuzzleVelocity(VECTOR *pposLaunch,VECTOR *pposTarget,float radVert,VECTOR *pvecMuzzle,SO *psoLaunch);

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
int FCalculateMuzzleVelocityAngle(VECTOR *pposLaunch, VECTOR *pposTarget, float radTilt, VECTOR *pvecMuzzle, SO *psoLaunch);

/**
 * @brief Limits the length of a vector.
 *
 * @param pvec Pointer to the vector
 * @param glength Length to limit the vector to
 * @param presult Pointer to store the resulting vector
 */
void LimitVectorLength(VECTOR *pvec, float glength, VECTOR *presult);

extern VECTOR g_normalX;

/**
 * @brief Normalizes a 3D vector. If magnitude is near zero, defaults to g_normalX.
 *
 * @param pvecOut Pointer to resulting normalized vector.
 * @param pvecIn Pointer to input vector.
 * @param pvecDefault Default normal vector if length < 0.0001f.
 */
static inline void NormalizeVector(VECTOR *pvecOut, const VECTOR *pvecIn, const VECTOR *pvecDefault)
{
    asm (
        ".set push\n"
        ".set noreorder\n"
        ".set noat\n"
        "lqc2    $vf3, %1\n"
        "vmul.xyz $vf1, $vf3, $vf3\n"
        "vaddw.x $vf2, $vf0, $vf0w\n"
        "vadday.x ACC, $vf1, $vf1y\n"
        "vmaddz.x $vf1, $vf2, $vf1z\n"
        "lui     $1, (0x38D1B717 >> 16)\n"
        "ori     $1, $1, (0x38D1B717 & 0xFFFF)\n"
        "mtc1    $1, $f1\n"
        ".word   0x4A0103BD\n"
        "vwaitq\n"
        "vaddq.x $vf1, $vf0, Q\n"
        "lq      $4, -16+%1\n"
        "qmfc2.ni $3, $vf1\n"
        "addiu   $2, $2, %%lo(g_normalX)\n"
        "mtc1    $3, $f0\n"
        "lq      $2, 0($2)\n"
        "c.lt.s  $f0, $f1\n"
        "addiu   $3, $0, 6\n"
        "sq      $4, 16+%0\n"
        "bc1f    1f\n"
        "sw      $3, -16+%0\n"
        "b       2f\n"
        "qmtc2.ni $2, $vf1\n"
        "1:\n"
        "vdiv    Q, $vf0w, $vf1x\n"
        "vwaitq\n"
        "vmulq.xyzw $vf1, $vf3, Q\n"
        "2:\n"
        "sqc2    $vf1, %0\n"
        ".set pop\n"
        : "=m"(*pvecOut)
        : "m"(*pvecIn), "m"(*pvecDefault)
        : "$1", "$3", "$4", "$f0", "$f1", "memory"
    );
}

#endif // VEC_H
