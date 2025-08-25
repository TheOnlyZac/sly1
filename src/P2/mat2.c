/**
 * @note Should be merged with mat1.c and mat_AddMatrix4Matrix4.
 */
#include <mat.h>
#include <sce/memset.h>

extern VECTOR g_normalZ;

INCLUDE_ASM(const s32, "P2/mat2", LoadRotateMatrixRad__FfP6VECTORP7MATRIX3);

INCLUDE_ASM(const s32, "P2/mat2", LoadRotateMatrix__FP6VECTORP7MATRIX3);

INCLUDE_ASM(const s32, "P2/mat2", LoadRotateMatrixEuler__FP6VECTORP7MATRIX3);

INCLUDE_ASM(const s32, "P2/mat2", LoadMatrixFromPosRot__FP6VECTORP7MATRIX3P7MATRIX4);

INCLUDE_ASM(const s32, "P2/mat2", LoadMatrixFromPosRotInverse__FP6VECTORP7MATRIX3P7MATRIX4);

INCLUDE_ASM(const s32, "P2/mat2", LoadMatrixFromPosRotScale__FP6VECTORP7MATRIX3T0P7MATRIX4);

INCLUDE_ASM(const s32, "P2/mat2", junk_00188CC8);

INCLUDE_ASM(const s32, "P2/mat2", CosRotateMatrixMagnitude__FP7MATRIX3);

INCLUDE_ASM(const s32, "P2/mat2", DecomposeRotateMatrixRad__FP7MATRIX3PfP6VECTOR);

INCLUDE_ASM(const s32, "P2/mat2", junk_00188FD0);

INCLUDE_ASM(const s32, "P2/mat2", DecomposeRotateMatrixEuler__FP7MATRIX3P6VECTOR);

INCLUDE_ASM(const s32, "P2/mat2", NormalizeRotateMatrix3__FP7MATRIX3);

INCLUDE_ASM(const s32, "P2/mat2", CalculateDmat__FP7MATRIX3N20);

INCLUDE_ASM(const s32, "P2/mat2", CalculateDmat4__FP7MATRIX4N20);

INCLUDE_ASM(const s32, "P2/mat2", DecomposeRotateMatrixPanTilt__FP7MATRIX3PfT1);

INCLUDE_ASM(const s32, "P2/mat2", LoadRotateMatrixPanTilt__FffP7MATRIX3);

void LoadLookAtMatrix(VECTOR *pdpos, MATRIX3 *pmat)
{
    BuildOrthonormalMatrixZ(pdpos, &g_normalZ, pmat);
}

INCLUDE_ASM(const s32, "P2/mat2", TiltMatUpright__FP7MATRIX3N20);

INCLUDE_ASM(const s32, "P2/mat2", junk_00189430);

INCLUDE_ASM(const s32, "P2/mat2", FInvertMatrix__FiPfT1);

INCLUDE_ASM(const s32, "P2/mat2", FInvertMatrix3__FP7MATRIX3T0);

bool FInvertMatrix4(MATRIX4 *pmatSrc, MATRIX4 *pmatDst)
{
    return FInvertMatrix(4, (float *)pmatSrc, (float *)pmatDst);
}

INCLUDE_ASM(const s32, "P2/mat2", BuildOrthonormalMatrixY__FP6VECTORT0P7MATRIX3);

INCLUDE_ASM(const s32, "P2/mat2", BuildOrthonormalMatrixZ__FP6VECTORT0P7MATRIX3);

INCLUDE_ASM(const s32, "P2/mat2", BuildRotateVectorsMatrix__FP6VECTORT0P7MATRIX3);

void BuildSimpleProjectionMatrix(float rx, float ry, float dxOffset, float dyOffset, float sFar, float sNear, MATRIX4 *pmat)
{
    memset(pmat, 0, sizeof(MATRIX4));

    float zScale = (sFar + sNear) / (sFar - sNear);
    float zTrans = (sFar * (1.0f - zScale));

    pmat->mat[0][0] = rx;
    pmat->mat[2][3] = 1.0f;
    pmat->mat[2][0] = dxOffset;

    pmat->mat[1][1] = ry;
    pmat->mat[2][1] = dyOffset;

    pmat->mat[2][2] = zScale;
    pmat->mat[3][2] = zTrans;
}

INCLUDE_ASM(const s32, "P2/mat2", LoadScaleMatrixScalar__FP6VECTORfP7MATRIX4);

INCLUDE_ASM(const s32, "P2/mat2", LoadScaleMatrixVector__FP6VECTORP7MATRIX3T0P7MATRIX4);

INCLUDE_ASM(const s32, "P2/mat2", LoadRotateVectorMatrix__FP6VECTORT0P7MATRIX3);
