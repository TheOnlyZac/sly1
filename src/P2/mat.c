#include <mat.h>
#include <sce/memset.h>

extern VECTOR g_normalZ;

INCLUDE_ASM(const s32, "P2/mat", PostCopyMatrix3__7MATRIX4);

INCLUDE_ASM(const s32, "P2/mat", __as__7MATRIX4RC7MATRIX3);

INCLUDE_ASM(const s32, "P2/mat", MatMulMatTransMat__FRC7MATRIX3T0);

INCLUDE_ASM(const s32, "P2/mat", LoadIdentityMatrix4__FP7MATRIX4);

INCLUDE_ASM(const s32, "P2/mat", __ml__FRC7MATRIX4G8VU_FLOAT);

INCLUDE_ASM(const s32, "P2/mat", __ml__FRC7MATRIX4T0);

INCLUDE_ASM(const s32, "P2/mat", junk_001886F8);

INCLUDE_ASM(const s32, "P2/mat", MultiplyMatrix4Vector__FP7MATRIX4P6VECTORfT1);

INCLUDE_ASM(const s32, "P2/mat", __ml__FRC7MATRIX4G10VU_VECTOR4);

INCLUDE_ASM(const s32, "P2/mat", TransposeMatrix4__FP7MATRIX4T0);

INCLUDE_ASM(const s32, "P2/mat", AddMatrix4Matrix4__FP7MATRIX4N20);

INCLUDE_ASM(const s32, "P2/mat", junk_00188848);

INCLUDE_ASM(const s32, "P2/mat", LoadRotateMatrixRad__FfP6VECTORP7MATRIX3);

INCLUDE_ASM(const s32, "P2/mat", LoadRotateMatrix__FP6VECTORP7MATRIX3);

INCLUDE_ASM(const s32, "P2/mat", LoadRotateMatrixEuler__FP6VECTORP7MATRIX3);

INCLUDE_ASM(const s32, "P2/mat", LoadMatrixFromPosRot__FP6VECTORP7MATRIX3P7MATRIX4);

INCLUDE_ASM(const s32, "P2/mat", LoadMatrixFromPosRotInverse__FP6VECTORP7MATRIX3P7MATRIX4);

INCLUDE_ASM(const s32, "P2/mat", LoadMatrixFromPosRotScale__FP6VECTORP7MATRIX3T0P7MATRIX4);

INCLUDE_ASM(const s32, "P2/mat", junk_00188CC8);

INCLUDE_ASM(const s32, "P2/mat", CosRotateMatrixMagnitude__FP7MATRIX3);

INCLUDE_ASM(const s32, "P2/mat", DecomposeRotateMatrixRad__FP7MATRIX3PfP6VECTOR);

INCLUDE_ASM(const s32, "P2/mat", junk_00188FD0);

INCLUDE_ASM(const s32, "P2/mat", DecomposeRotateMatrixEuler__FP7MATRIX3P6VECTOR);

INCLUDE_ASM(const s32, "P2/mat", NormalizeRotateMatrix3__FP7MATRIX3);

INCLUDE_ASM(const s32, "P2/mat", CalculateDmat__FP7MATRIX3N20);

INCLUDE_ASM(const s32, "P2/mat", CalculateDmat4__FP7MATRIX4N20);

INCLUDE_ASM(const s32, "P2/mat", DecomposeRotateMatrixPanTilt__FP7MATRIX3PfT1);

INCLUDE_ASM(const s32, "P2/mat", LoadRotateMatrixPanTilt__FffP7MATRIX3);

void LoadLookAtMatrix(VECTOR *pdpos, MATRIX3 *pmat)
{
    BuildOrthonormalMatrixZ(pdpos, &g_normalZ, pmat);
}

INCLUDE_ASM(const s32, "P2/mat", TiltMatUpright__FP7MATRIX3N20);

INCLUDE_ASM(const s32, "P2/mat", junk_00189430);

INCLUDE_ASM(const s32, "P2/mat", FInvertMatrix__FiPfT1);

INCLUDE_ASM(const s32, "P2/mat", FInvertMatrix3__FP7MATRIX3T0);

bool FInvertMatrix4(MATRIX4 *pmatSrc, MATRIX4 *pmatDst)
{
    return FInvertMatrix(4, (float *)pmatSrc, (float *)pmatDst);
}

INCLUDE_ASM(const s32, "P2/mat", BuildOrthonormalMatrixY__FP6VECTORT0P7MATRIX3);

INCLUDE_ASM(const s32, "P2/mat", BuildOrthonormalMatrixZ__FP6VECTORT0P7MATRIX3);

INCLUDE_ASM(const s32, "P2/mat", BuildRotateVectorsMatrix__FP6VECTORT0P7MATRIX3);

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

INCLUDE_ASM(const s32, "P2/mat", LoadScaleMatrixScalar__FP6VECTORfP7MATRIX4);

INCLUDE_ASM(const s32, "P2/mat", LoadScaleMatrixVector__FP6VECTORP7MATRIX3T0P7MATRIX4);

INCLUDE_ASM(const s32, "P2/mat", LoadRotateVectorMatrix__FP6VECTORT0P7MATRIX3);
