#include <splice/bif.h>
#include <splice/ref.h>
#include <splice/frame.h>
#include <po.h>
#include <blip.h>

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpAdd__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpSub__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpMult__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpDiv__FiP4CRefP6CFrame);

CRef RefOpPrint(int carg, CRef *aref, CFrame *pframe)
{
    CRef cref = CRef();
    cref.SetTag(TAGK_Void);
    return CRef(cref);
}

CRef RefOpPrintFrame(int carg, CRef *aref, CFrame *pframe)
{
    CRef cref = CRef();
    cref.SetTag(TAGK_Void);
    return CRef(cref);
}

CRef RefOpPrintSidebag(int carg, CRef *aref, CFrame *pframe)
{
    CRef cref = CRef();
    cref.SetTag(TAGK_Void);
    return CRef(cref);
}

CRef RefOpIntEqual(int carg, CRef *aref, CFrame *pframe)
{
    CRef cref = CRef();
    cref.SetBool(aref[0].m_tag.m_n == aref[1].m_tag.m_n);
    return CRef(cref);
}

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefCmp__FP4CRef4CMPK);

CRef RefOpL(int carg, CRef *aref, CFrame *pframe)
{
    return RefCmp(aref, CMPK_L);
}

CRef RefOpLE(int carg, CRef *aref, CFrame *pframe)
{
    return RefCmp(aref, CMPK_LE);
}

CRef RefOpG(int carg, CRef *aref, CFrame *pframe)
{
    return RefCmp(aref, CMPK_G);
}

CRef RefOpGE(int carg, CRef *aref, CFrame *pframe)
{
    return RefCmp(aref, CMPK_GE);
}

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpEqv__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefEqualHelper__FP4CRefT0);

CRef RefOpEqual(int carg, CRef *aref, CFrame *pframe)
{
    return RefEqualHelper(&aref[0], &aref[1]);
}

CRef RefOpIsBoolean(int carg, CRef *aref, CFrame *pframe)
{
    CRef cref = CRef();
    cref.SetBool(aref->m_tagk == TAGK_Bool);
    return CRef(cref);
}

CRef RefOpIsNum(int carg, CRef *aref, CFrame *pframe)
{
    CRef cref = CRef();
    cref.SetBool(aref->m_tagk == TAGK_S32 || aref->m_tagk == TAGK_F32);
    return CRef(cref);
}

CRef RefOpIsFloat(int carg, CRef *aref, CFrame *pframe)
{
    CRef cref = CRef();
    cref.SetBool(aref->m_tagk == TAGK_F32);
    return CRef(cref);
}

CRef RefOpIsInteger(int carg, CRef *aref, CFrame *pframe)
{
    CRef cref = CRef();
    cref.SetBool(aref->m_tagk == TAGK_S32);
    return CRef(cref);
}

CRef RefOpIsSymbol(int carg, CRef *aref, CFrame *pframe)
{
    CRef cref = CRef();
    cref.SetBool(aref->m_tagk == TAGK_Symid);
    return CRef(cref);
}

CRef RefOpIsVector(int carg, CRef *aref, CFrame *pframe)
{
    CRef cref = CRef();
    cref.SetBool(aref->m_tagk == TAGK_Vector);
    return CRef(cref);
}

CRef RefOpIsMatrix(int carg, CRef *aref, CFrame *pframe)
{
    CRef cref = CRef();
    cref.SetBool(aref->m_tagk == TAGK_Matrix);
    return CRef(cref);
}

CRef RefOpIsClq(int carg, CRef *aref, CFrame *pframe)
{
    CRef cref = CRef();
    cref.SetBool(aref->m_tagk == TAGK_Clq);
    return CRef(cref);
}

CRef RefOpIsLm(int carg, CRef *aref, CFrame *pframe)
{
    CRef cref = CRef();
    cref.SetBool(aref->m_tagk == TAGK_Lm);
    return CRef(cref);
}

CRef RefOpIsSmp(int carg, CRef *aref, CFrame *pframe)
{
    CRef cref = CRef();
    cref.SetBool(aref->m_tagk == TAGK_Smp);
    return CRef(cref);
}

CRef RefOpIsList(int carg, CRef *aref, CFrame *pframe)
{
    CRef cref = CRef();
    cref.SetBool(aref->m_tagk == TAGK_Pair || aref->m_tagk == TAGK_None);
    return CRef(cref);
}

CRef RefOpIsNull(int carg, CRef *aref, CFrame *pframe)
{
    CRef cref = CRef();
    cref.SetBool(aref->m_tagk == TAGK_None);
    return CRef(cref);
}

CRef RefOpIsObject(int carg, CRef *aref, CFrame *pframe)
{
    CRef cref = CRef();
    cref.SetBool(aref->m_tagk == TAGK_Basic);
    return CRef(cref);
}

CRef RefOpIsNullObj(int carg, CRef *aref, CFrame *pframe)
{
    CRef cref = CRef();
    cref.SetBool(aref->m_tagk == TAGK_Basic && !aref->m_tag.m_pbasic);
    return CRef(cref);
}

CRef RefOpIsMethod(int carg, CRef *aref, CFrame *pframe)
{
    CRef cref = CRef();
    cref.SetBool(aref->m_tagk == TAGK_Method);
    return CRef(cref);
}

CRef RefOpIsProcedure(int carg, CRef *aref, CFrame *pframe)
{
    CRef cref = CRef();
    cref.SetBool(aref->m_tagk == TAGK_Proc || aref->m_tagk == TAGK_Bifk);
    return CRef(cref);
}

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpAreNear__FiP4CRefP6CFrame);

CRef RefOpNot(int carg, CRef *aref, CFrame *pframe)
{
    CRef cref = CRef();
    cref.SetBool(aref->m_tagk == TAGK_Bool && !aref->m_tag.m_bool);
    return CRef(cref);
}

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpCons__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpCar__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpCdr__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpSetCadr__FiP4CRefP6CFrame4BIFK);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpSetCar__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpSetCdr__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpLength__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpNth__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpIsMember__FiP4CRefP6CFrame);

CRef RefOpList(int carg, CRef *aref, CFrame *pframe)
{
    return CRef(*aref);
}

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpAppend__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpMap__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpFilter__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpForEach__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpEval__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpVector__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpMatrix__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpSetMusicRegister__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpClq__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpLm__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpSmp__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpGetElement__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpRandomSeed__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpRandom__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefUfo__FP4CRef4UFOK);

CRef RefOpSqrt(int carg, CRef *aref, CFrame *pframe)
{
    return RefUfo(aref, UFOK_Sqrt);
}

CRef RefOpSin(int carg, CRef *aref, CFrame *pframe)
{
    return RefUfo(aref, UFOK_Sin);
}

CRef RefOpCos(int carg, CRef *aref, CFrame *pframe)
{
    return RefUfo(aref, UFOK_Cos);
}

CRef RefOpTan(int carg, CRef *aref, CFrame *pframe)
{
    return RefUfo(aref, UFOK_Tan);
}

CRef RefOpAsin(int carg, CRef *aref, CFrame *pframe)
{
    return RefUfo(aref, UFOK_Asin);
}

CRef RefOpAcos(int carg, CRef *aref, CFrame *pframe)
{
    return RefUfo(aref, UFOK_Acos);
}

CRef RefOpAtan(int carg, CRef *aref, CFrame *pframe)
{
    return RefUfo(aref, UFOK_Atan);
}

CRef RefOpRadNormalize(int carg, CRef *aref, CFrame *pframe)
{
    return RefUfo(aref, UFOK_RadNormalize);
}

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpAtan2__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpVectorDotProduct__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpVectorCrossProduct__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpVectorLth__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpVectorDistance__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpVectorDistanceSquared__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpVectorNormalize__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpVectorProjectNormal__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpVectorProjectTangent__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpVectorBallisticVelocity__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpVectorRadianNormal__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpMatrixTranspose__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpMatrixInvert__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpMatrixCalculateDmat__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpMatrixInterpolateRotate__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpMatrixDecomposeToTranslate__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpMatrixDecomposeToRotate__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpMatrixDecomposeToEuler__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpMatrixDecomposeToRadianNormal__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpMatrixLookAt__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpMatrixTiltUpright__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpClqEvaluate__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpClqEvaluateLm__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpClqFit__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpLmLimit__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpLmCheck__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpFloor__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpCeiling__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpRound__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpTruncate__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpAbs__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpMaximum__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpMinimum__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpModulo__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpCurrentTime__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpScheduleCallback__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpDeferObjectUpdate__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpObjectOption__FiP4CRefP6CFrame4BIFK);

CRef RefOpAddO(int carg, CRef *aref, CFrame *pframe)
{
    return RefOpObjectOption(carg, aref, pframe, BIFK_AddO);
}

CRef RefOpEnsureO(int carg, CRef *aref, CFrame *pframe)
{
    return RefOpObjectOption(carg, aref, pframe, BIFK_EnsureO);
}

CRef RefOpSetO(int carg, CRef *aref, CFrame *pframe)
{
    return RefOpObjectOption(carg, aref, pframe, BIFK_SetO);
}

CRef RefOpGetO(int carg, CRef *aref, CFrame *pframe)
{
    return RefOpObjectOption(carg, aref, pframe, BIFK_GetO);
}

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefPairFromAplo__FiPP2LO);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpFindObject__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpFindObjects__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpFindNearestObject__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpFindNearestObjects__FiP4CRefP6CFrame);

CRef RefOpFindPlayerObject(int carg, CRef *aref, CFrame *pframe)
{
    CRef cref = CRef();
    cref.SetBasic(PpoCur());
    return CRef(cref);
}

CRef RefOpFindWorldObject(int carg, CRef *aref, CFrame *pframe)
{
    CRef cref = CRef();
    cref.SetBasic(g_psw);
    return CRef(cref);
}

CRef RefOpFindCameraObject(int carg, CRef *aref, CFrame *pframe)
{
    CRef cref = CRef();
    cref.SetBasic(g_pcm);
    return CRef(cref);
}

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpFindClassObjects__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpFindObjectsInBoundingBox__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpFindObjectsInBoundingSphere__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpHitTestObjectsImpl__F4BIFKiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpHitTestObjects__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpHitTestObjectsFirst__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpConvertObjectPosition__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpConvertObjectVector__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpConvertObjectMatrix__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpNearClipCenter__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpStartSound__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpStopSound__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpStartRumble__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpEmitSmokeCloud__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", RefOpPredictAnimationEffect__FiP4CRefP6CFrame);

INCLUDE_ASM("asm/nonmatchings/P2/splice/bif", __8VU_FLOATf);

VU_VECTOR::VU_VECTOR(const VECTOR &vec)
{
    data = *(qword *)&vec;
}

VECTOR &VECTOR::operator=(VU_VECTOR vuvec)
{
    *(qword *)this = vuvec.data;
    return *this;
}

VU_VECTOR operator*(VU_FLOAT f, VU_VECTOR v)
{
    VU_VECTOR r;
    asm("qmtc2.ni %1, $vf1\n\t"
        "qmtc2.ni %2, $vf2\n\t"
        "vmulx.xyzw $vf1, $vf2, $vf1\n\t"
        "qmfc2.ni %0, $vf1"
        : "=r"(r.data)
        : "r"(f.data), "r"(v.data));
    return r;
}
