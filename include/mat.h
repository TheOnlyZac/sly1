/**
 * @file mat.h
 *
 * @brief 3x3 and 4x4 matrix types.
*/
#ifndef MAT_H
#define MAT_H

#include <vec.h>

/**
 * @brief 4x4 Matrix
*/
struct MATRIX4
{
	float mat[4][4];
};

/**
 * @brief 3x3 Matrix
*/
struct MATRIX3
{
	float mat[3][3];
};

void PostCopyMatrix3(MATRIX4 *pmat);

MATRIX3 *MatMulMatTransMat(MATRIX3 *matLeft, MATRIX3 *matRight);

void LoadIdentityMatrix4(MATRIX4 *pmat);

void MultiplyMatrix4Vector(MATRIX4 *pmat4, VECTOR *pvecIn, float gImplied, VECTOR *pvecOut);

void TransposeMatrix4(MATRIX4 *pmatSrc, MATRIX4 *pmatDst);

void AddMatrix4Matrix4(MATRIX4 *pmatLeft, MATRIX4 *pmatRight, MATRIX4 *pmatDst);

void LoadRotateMatrixRad(float rad, VECTOR *pnormal, MATRIX3 *pmat);

void LoadRotateMatrix(VECTOR *pvec, MATRIX3 *pmat);

void LoadRotateMatrixEuler(VECTOR *peul, MATRIX3 *pmatRot);

void LoadMatrixFromPosRot(VECTOR *ppos, MATRIX3 *pmat, MATRIX4 *pmatDst);

void LoadMatrixFromPosRotInverse(VECTOR *pposSrc, MATRIX3 *pmatSrc, MATRIX4 *pmatDst);

void LoadMatrixFromPosRotScale(VECTOR *pvecPos, MATRIX3 *pmatRot, VECTOR *pvecScale, MATRIX4 *pmat);

float CosRotateMatrixMagnitude(MATRIX3 *pmat);

void DecomposeRotateMatrixRad(MATRIX3 *pmat, float *prad, VECTOR *pnormal);

void DecomposeRotateMatrixEuler(MATRIX3 *pmat, VECTOR *peul);

void NormalizeRotateMatrix3(MATRIX3 *pmat);

void CalculateDmat(MATRIX3 *pmat0, MATRIX3 *pmat1, MATRIX3 *pdmat);

void CalculateDmat4(MATRIX4 *pmat0, MATRIX4 *pmat1, MATRIX4 *pdmat);

void DecomposeRotateMatrixPanTilt(MATRIX3 *pmat, float *pradPan, float *pradTilt);

void LoadRotateMatrixPanTilt(float radPan, float radTilt, MATRIX3 *pmat);

void LoadLookAtMatrix(VECTOR *pdpos, MATRIX3 *pmat);

void TiltMatUpright(MATRIX3 *pmat, MATRIX3 *pdmat, MATRIX3 *pmatUpright);

bool FInvertMatrix(int c, float *aagSrc, float *aagDst);

bool FInvertMatrix3(MATRIX3 *pmatSrc, MATRIX3 *pmatDst);

bool FInvertMatrix4(MATRIX4 *pmatSrc, MATRIX4 *pmatDst);

void BuildOrthonormalMatrixY(VECTOR *pvecX, VECTOR *pvecY, MATRIX3 *pmat);

void BuildOrthonormalMatrixZ(VECTOR *pvecX, VECTOR *pvecZ, MATRIX3 *pmat);

void BuildRotateVectorsMatrix(VECTOR *pvec1, VECTOR *pvec2, MATRIX3 *pmat);

/**
 * @brief Creates a perspective projection matrix with optional center offsets.
 *
 * @param rx Horizontal field-of-view scale.
 * @param ry Vertical field-of-view scale.
 * @param dxOffset Horizontal offset of the projection center.
 * @param dyOffset Vertical offset of the projection center.
 * @param sFar Far plane distance.
 * @param sNear Near plane distance.
 * @param pmat Pointer to the output.
 */
void BuildSimpleProjectionMatrix(float rx, float ry, float dxOffset, float dyOffset, float sFar, float sNear, MATRIX4 *pmat);

void LoadScaleMatrixScalar(VECTOR *ppos, float rScale, MATRIX4 *pmatScale);

void LoadScaleMatrixVector(VECTOR *ppos, MATRIX3 *pmat, VECTOR *pvecScale, MATRIX4 *pmatScale);

void LoadRotateVectorMatrix(VECTOR *pvecFrom, VECTOR *pvecTo, MATRIX3 *pmat);

#endif // MAT_H
