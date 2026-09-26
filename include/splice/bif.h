/**
 * @file splice/bif.h
 */
#ifndef SPLICE_BIF_H
#define SPLICE_BIF_H

#include "common.h"

// Forward declaration.
class CRef;
class CFrame;

/**
 * @brief Comparison Kind.
 */
enum CMPK
{
    CMPK_L = 0,
    CMPK_LE = 1,
    CMPK_G = 2,
    CMPK_GE = 3,
    CMPK_Max = 4,
};

/**
 * @enum BIFK
 * @brief Built-in function kind.
 */
enum BIFK
{
    BIFK_Nil = -1,
    BIFK_Add = 0,
    BIFK_Subtract = 1,
    BIFK_Multiply = 2,
    BIFK_Divide = 3,
    BIFK_Print = 4,
    BIFK_PrintFrame = 5,
    BIFK_PrintSidebag = 6,
    BIFK_IntEqual = 7,
    BIFK_Less = 8,
    BIFK_LE = 9,
    BIFK_Greater = 10,
    BIFK_GE = 11,
    BIFK_Eqv = 12,
    BIFK_Equal = 13,
    BIFK_IsBoolean = 14,
    BIFK_IsNumber = 15,
    BIFK_IsInteger = 16,
    BIFK_IsFloat = 17,
    BIFK_IsSymbol = 18,
    BIFK_IsVector = 19,
    BIFK_IsMatrix = 20,
    BIFK_IsClq = 21,
    BIFK_IsLm = 22,
    BIFK_IsSmp = 23,
    BIFK_IsList = 24,
    BIFK_IsNull = 25,
    BIFK_IsObject = 26,
    BIFK_IsNullObj = 27,
    BIFK_IsMethod = 28,
    BIFK_IsProcedure = 29,
    BIFK_AreNear = 30,
    BIFK_Not = 31,
    BIFK_Cons = 32,
    BIFK_Car = 33,
    BIFK_Cdr = 34,
    BIFK_SetCar = 35,
    BIFK_SetCdr = 36,
    BIFK_Length = 37,
    BIFK_Nth = 38,
    BIFK_IsMember = 39,
    BIFK_List = 40,
    BIFK_Append = 41,
    BIFK_Map = 42,
    BIFK_Filter = 43,
    BIFK_ForEach = 44,
    BIFK_Eval = 45,
    BIFK_Vector = 46,
    BIFK_Matrix = 47,
    BIFK_Clq = 48,
    BIFK_Lm = 49,
    BIFK_Smp = 50,
    BIFK_GetElement = 51,
    BIFK_RandomSeed = 52,
    BIFK_Random = 53,
    BIFK_Sqrt = 54,
    BIFK_Sin = 55,
    BIFK_Cos = 56,
    BIFK_Tan = 57,
    BIFK_Asin = 58,
    BIFK_Acos = 59,
    BIFK_Atan = 60,
    BIFK_RadNormalize = 61,
    BIFK_Atan2 = 62,
    BIFK_VectorDotProduct = 63,
    BIFK_VectorCrossProduct = 64,
    BIFK_VectorLth = 65,
    BIFK_VectorDistance = 66,
    BIFK_VectorDistanceSquared = 67,
    BIFK_VectorNormalize = 68,
    BIFK_VectorProjectNormal = 69,
    BIFK_VectorProjectTangent = 70,
    BIFK_VectorBallisticVelocity = 71,
    BIFK_VectorRadianNormal = 72,
    BIFK_MatrixTranspose = 73,
    BIFK_MatrixInvert = 74,
    BIFK_MatrixCalculateDmat = 75,
    BIFK_MatrixInterpolateRotate = 76,
    BIFK_MatrixDecomposeToTranslate = 77,
    BIFK_MatrixDecomposeToRotate = 78,
    BIFK_MatrixDecomposeToEuler = 79,
    BIFK_MatrixDecomposeToRadianNormal = 80,
    BIFK_MatrixLookAt = 81,
    BIFK_MatrixTiltUpright = 82,
    BIFK_ClqEvaluate = 83,
    BIFK_ClqEvaluateLm = 84,
    BIFK_ClqFit = 85,
    BIFK_LmLimit = 86,
    BIFK_LmCheck = 87,
    BIFK_Floor = 88,
    BIFK_Ceiling = 89,
    BIFK_Round = 90,
    BIFK_Truncate = 91,
    BIFK_Abs = 92,
    BIFK_Maximum = 93,
    BIFK_Minimum = 94,
    BIFK_Modulo = 95,
    BIFK_CurrentTime = 96,
    BIFK_ScheduleCallback = 97,
    BIFK_DeferObjectUpdate = 98,
    BIFK_AddO = 99,
    BIFK_EnsureO = 100,
    BIFK_SetO = 101,
    BIFK_GetO = 102,
    BIFK_FindObject = 103,
    BIFK_FindObjects = 104,
    BIFK_FindNearestObject = 105,
    BIFK_FindNearestObjects = 106,
    BIFK_FindPlayerObject = 107,
    BIFK_FindWorldObject = 108,
    BIFK_FindCameraObject = 109,
    BIFK_FindClassObjects = 110,
    BIFK_FindObjectsInBoundingBox = 111,
    BIFK_FindObjectsInBoundingSphere = 112,
    BIFK_HitTestObjects = 113,
    BIFK_HitTestObjectsFirst = 114,
    BIFK_ConvertObjectPosition = 115,
    BIFK_ConvertObjectVector = 116,
    BIFK_ConvertObjectMatrix = 117,
    BIFK_NearClipCenter = 118,
    BIFK_StartSound = 119,
    BIFK_StopSound = 120,
    BIFK_StartRumble = 121,
    BIFK_EmitSmokeCloud = 122,
    BIFK_PredictAnimationEffect = 123,
    BIFK_SetMusicReg = 124,
    BIFK_Max = 125,
};

/**
 * @brief Uniform Float Operation Kind.
 */
enum UFOK
{
    UFOK_Sqrt = 0,
    UFOK_Sin = 1,
    UFOK_Cos = 2,
    UFOK_Tan = 3,
    UFOK_Asin = 4,
    UFOK_Acos = 5,
    UFOK_Atan = 6,
    UFOK_RadNormalize = 7,
    UFOK_Max = 8,
};

/**
 * @brief Function pointer for built-in function dispatch.
 */
typedef CRef (*PFNBIF)(int, CRef *, CFrame *);

/**
 * @brief A single entry in the global BIF dispatch table.
 */
struct BIF
{
    PFNBIF pfnbif;
    int crefReq;
    int fVarArg;
};

/**
 * @brief Table of built-in functions.
 */
extern BIF g_mpbifkbif[];

CRef RefOpAdd(int carg, CRef *aref, CFrame *pframe);

CRef RefOpSub(int carg, CRef *aref, CFrame *pframe);

CRef RefOpMult(int carg, CRef *aref, CFrame *pframe);

CRef RefOpDiv(int carg, CRef *aref, CFrame *pframe);

CRef RefOpPrint(int carg, CRef *aref, CFrame *pframe);

CRef RefOpPrintFrame(int carg, CRef *aref, CFrame *pframe);

CRef RefOpPrintSidebag(int carg, CRef *aref, CFrame *pframe);

CRef RefOpIntEqual(int carg, CRef *aref, CFrame *pframe);

CRef RefCmp(CRef *aref, CMPK cmpk);

CRef RefOpL(int carg, CRef *aref, CFrame *pframe);

CRef RefOpLE(int carg, CRef *aref, CFrame *pframe);

CRef RefOpG(int carg, CRef *aref, CFrame *pframe);

CRef RefOpGE(int carg, CRef *aref, CFrame *pframe);

CRef RefOpEqv(int carg, CRef *aref, CFrame *pframe);

CRef RefEqualHelper(CRef *prefA, CRef *prefB);

CRef RefOpEqual(int carg, CRef *aref, CFrame *pframe);

CRef RefOpIsBoolean(int carg, CRef *aref, CFrame *pframe);

CRef RefOpIsNum(int carg, CRef *aref, CFrame *pframe);

CRef RefOpIsFloat(int carg, CRef *aref, CFrame *pframe);

CRef RefOpIsInteger(int carg, CRef *aref, CFrame *pframe);

CRef RefOpIsSymbol(int carg, CRef *aref, CFrame *pframe);

CRef RefOpIsVector(int carg, CRef *aref, CFrame *pframe);

CRef RefOpIsMatrix(int carg, CRef *aref, CFrame *pframe);

CRef RefOpIsClq(int carg, CRef *aref, CFrame *pframe);

CRef RefOpIsLm(int carg, CRef *aref, CFrame *pframe);

CRef RefOpIsSmp(int carg, CRef *aref, CFrame *pframe);

CRef RefOpIsList(int carg, CRef *aref, CFrame *pframe);

CRef RefOpIsNull(int carg, CRef *aref, CFrame *pframe);

CRef RefOpIsObject(int carg, CRef *aref, CFrame *pframe);

CRef RefOpIsNullObj(int carg, CRef *aref, CFrame *pframe);

CRef RefOpIsMethod(int carg, CRef *aref, CFrame *pframe);

CRef RefOpIsProcedure(int carg, CRef *aref, CFrame *pframe);

CRef RefOpAreNear(int carg, CRef *aref, CFrame *pframe);

CRef RefOpNot(int carg, CRef *aref, CFrame *pframe);

CRef RefOpCons(int carg, CRef *aref, CFrame *pframe);

CRef RefOpCar(int carg, CRef *aref, CFrame *pframe);

CRef RefOpCdr(int carg, CRef *aref, CFrame *pframe);

CRef RefOpSetCadr(int carg, CRef *aref, CFrame *pframe, BIFK bifk);

CRef RefOpSetCar(int carg, CRef *aref, CFrame *pframe);

CRef RefOpSetCdr(int carg, CRef *aref, CFrame *pframe);

CRef RefOpLength(int carg, CRef *aref, CFrame *pframe);

CRef RefOpNth(int carg, CRef *aref, CFrame *pframe);

CRef RefOpIsMember(int carg, CRef *aref, CFrame *pframe);

CRef RefOpList(int carg, CRef *aref, CFrame *pframe);

CRef RefOpAppend(int carg, CRef *aref, CFrame *pframe);

CRef RefOpMap(int carg, CRef *aref, CFrame *pframe);

CRef RefOpFilter(int carg, CRef *aref, CFrame *pframe);

CRef RefOpForEach(int carg, CRef *aref, CFrame *pframe);

CRef RefOpEval(int carg, CRef *aref, CFrame *pframe);

CRef RefOpVector(int carg, CRef *aref, CFrame *pframe);

CRef RefOpMatrix(int carg, CRef *aref, CFrame *pframe);

CRef RefOpSetMusicRegister(int carg, CRef *aref, CFrame *pframe);

CRef RefOpClq(int carg, CRef *aref, CFrame *pframe);

CRef RefOpLm(int carg, CRef *aref, CFrame *pframe);

CRef RefOpSmp(int carg, CRef *aref, CFrame *pframe);

CRef RefOpGetElement(int carg, CRef *aref, CFrame *pframe);

CRef RefOpRandomSeed(int carg, CRef *aref, CFrame *pframe);

CRef RefOpRandom(int carg, CRef *aref, CFrame *pframe);

CRef RefUfo(CRef *pref, UFOK ufok);

CRef RefOpSqrt(int carg, CRef *aref, CFrame *pframe);

CRef RefOpSin(int carg, CRef *aref, CFrame *pframe);

CRef RefOpCos(int carg, CRef *aref, CFrame *pframe);

CRef RefOpTan(int carg, CRef *aref, CFrame *pframe);

CRef RefOpAsin(int carg, CRef *aref, CFrame *pframe);

CRef RefOpAcos(int carg, CRef *aref, CFrame *pframe);

CRef RefOpAtan(int carg, CRef *aref, CFrame *pframe);

CRef RefOpRadNormalize(int carg, CRef *aref, CFrame *pframe);

CRef RefOpAtan2(int carg, CRef *aref, CFrame *pframe);

CRef RefOpVectorDotProduct(int carg, CRef *aref, CFrame *pframe);

CRef RefOpVectorCrossProduct(int carg, CRef *aref, CFrame *pframe);

CRef RefOpVectorLth(int carg, CRef *aref, CFrame *pframe);

CRef RefOpVectorDistance(int carg, CRef *aref, CFrame *pframe);

CRef RefOpVectorDistanceSquared(int carg, CRef *aref, CFrame *pframe);

CRef RefOpVectorNormalize(int carg, CRef *aref, CFrame *pframe);

CRef RefOpVectorProjectNormal(int carg, CRef *aref, CFrame *pframe);

CRef RefOpVectorProjectTangent(int carg, CRef *aref, CFrame *pframe);

CRef RefOpVectorBallisticVelocity(int carg, CRef *aref, CFrame *pframe);

CRef RefOpVectorRadianNormal(int carg, CRef *aref, CFrame *pframe);

CRef RefOpMatrixTranspose(int carg, CRef *aref, CFrame *pframe);

CRef RefOpMatrixInvert(int carg, CRef *aref, CFrame *pframe);

CRef RefOpMatrixCalculateDmat(int carg, CRef *aref, CFrame *pframe);

CRef RefOpMatrixInterpolateRotate(int carg, CRef *aref, CFrame *pframe);

CRef RefOpMatrixDecomposeToTranslate(int carg, CRef *aref, CFrame *pframe);

CRef RefOpMatrixDecomposeToRotate(int carg, CRef *aref, CFrame *pframe);

CRef RefOpMatrixDecomposeToEuler(int carg, CRef *aref, CFrame *pframe);

CRef RefOpMatrixDecomposeToRadianNormal(int carg, CRef *aref, CFrame *pframe);

CRef RefOpMatrixLookAt(int carg, CRef *aref, CFrame *pframe);

CRef RefOpMatrixTiltUpright(int carg, CRef *aref, CFrame *pframe);

CRef RefOpClqEvaluate(int carg, CRef *aref, CFrame *pframe);

CRef RefOpClqEvaluateLm(int carg, CRef *aref, CFrame *pframe);

CRef RefOpClqFit(int carg, CRef *aref, CFrame *pframe);

CRef RefOpLmLimit(int carg, CRef *aref, CFrame *pframe);

CRef RefOpLmCheck(int carg, CRef *aref, CFrame *pframe);

CRef RefOpFloor(int carg, CRef *aref, CFrame *pframe);

CRef RefOpCeiling(int carg, CRef *aref, CFrame *pframe);

CRef RefOpRound(int carg, CRef *aref, CFrame *pframe);

CRef RefOpTruncate(int carg, CRef *aref, CFrame *pframe);

CRef RefOpAbs(int carg, CRef *aref, CFrame *pframe);

CRef RefOpMaximum(int carg, CRef *aref, CFrame *pframe);

CRef RefOpMinimum(int carg, CRef *aref, CFrame *pframe);

CRef RefOpModulo(int carg, CRef *aref, CFrame *pframe);

CRef RefOpCurrentTime(int carg, CRef *aref, CFrame *pframe);

CRef RefOpScheduleCallback(int carg, CRef *aref, CFrame *pframe);

CRef RefOpDeferObjectUpdate(int carg, CRef *aref, CFrame *pframe);

CRef RefOpObjectOption(int carg, CRef *aref, CFrame *pframe, BIFK bifk);

CRef RefOpAddO(int carg, CRef *aref, CFrame *pframe);

CRef RefOpEnsureO(int carg, CRef *aref, CFrame *pframe);

CRef RefOpSetO(int carg, CRef *aref, CFrame *pframe);

CRef RefOpGetO(int carg, CRef *aref, CFrame *pframe);

CRef RefPairFromAplo(int cplo, LO **aplo);

CRef RefOpFindObject(int carg, CRef *aref, CFrame *pframe);

CRef RefOpFindObjects(int carg, CRef *aref, CFrame *pframe);

CRef RefOpFindNearestObject(int carg, CRef *aref, CFrame *pframe);

CRef RefOpFindNearestObjects(int carg, CRef *aref, CFrame *pframe);

CRef RefOpFindPlayerObject(int carg, CRef *aref, CFrame *pframe);

CRef RefOpFindWorldObject(int carg, CRef *aref, CFrame *pframe);

CRef RefOpFindCameraObject(int carg, CRef *aref, CFrame *pframe);

CRef RefOpFindClassObjects(int carg, CRef *aref, CFrame *pframe);

CRef RefOpFindObjectsInBoundingBox(int carg, CRef *aref, CFrame *pframe);

CRef RefOpFindObjectsInBoundingSphere(int carg, CRef *aref, CFrame *pframe);

CRef RefOpHitTestObjectsImpl(BIFK bifk, int carg, CRef *aref, CFrame *pframe);

CRef RefOpHitTestObjects(int carg, CRef *aref, CFrame *pframe);

CRef RefOpHitTestObjectsFirst(int carg, CRef *aref, CFrame *pframe);

CRef RefOpConvertObjectPosition(int carg, CRef *aref, CFrame *pframe);

CRef RefOpConvertObjectVector(int carg, CRef *aref, CFrame *pframe);

CRef RefOpConvertObjectMatrix(int carg, CRef *aref, CFrame *pframe);

CRef RefOpNearClipCenter(int carg, CRef *aref, CFrame *pframe);

CRef RefOpStartSound(int carg, CRef *aref, CFrame *pframe);

CRef RefOpStopSound(int carg, CRef *aref, CFrame *pframe);

CRef RefOpStartRumble(int carg, CRef *aref, CFrame *pframe);

CRef RefOpEmitSmokeCloud(int carg, CRef *aref, CFrame *pframe);

CRef RefOpPredictAnimationEffect(int carg, CRef *aref, CFrame *pframe);

#endif // SPLICE_BIF_H
