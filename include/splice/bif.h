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
 * @enum BIFK
 *
 * @todo Fill in enum.
 */
enum BIFK
{
    // ...
    BIFK_SetCar = 35,
    BIFK_SetCdr = 36,
    // ...
    BIFK_HitTestObjects = 113,
    BIFK_HitTestObjectsFirst = 114,
    // ...
    BIFK_AddO = 99,
    BIFK_EnsureO = 100,
    BIFK_SetO = 101,
    BIFK_GetO = 102,
    // ...
};

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
 * @brief (?) operation kind?
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
