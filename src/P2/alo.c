#include <alo.h>
#include <act.h>
#include <shd.h>
#include <shadow.h>
#include <target.h>

extern VTACT g_vtactseg;
extern SHADOW s_shadow;

INCLUDE_ASM("asm/nonmatchings/P2/alo", FIsZeroV__FP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/alo", FIsZeroW__FP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/alo", FIsZeroDv__FP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/alo", FIsZeroDw__FP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/alo", InitAlo__FP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/alo", AddAloHierarchy__FP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/alo", OnAloAdd__FP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/alo", RemoveAloHierarchy__FP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/alo", OnAloRemove__FP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/alo", UpdateAloOrig__FP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloParent__FP3ALOT0);

INCLUDE_ASM("asm/nonmatchings/P2/alo", ApplyAloProxy__FP3ALOP5PROXY);

INCLUDE_ASM("asm/nonmatchings/P2/alo", BindAlo__FP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/alo", PostAloLoad__FP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/alo", PostAloLoadCallback__FP3ALO5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SnipAloObjects__FP3ALOiP4SNIP);

INCLUDE_ASM("asm/nonmatchings/P2/alo", UpdateAloHierarchy__FP3ALOf);

INCLUDE_ASM("asm/nonmatchings/P2/alo", UpdateAlo__FP3ALOf);

INCLUDE_ASM("asm/nonmatchings/P2/alo", InvalidateAloLighting__FP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/alo", UpdateAloXfWorld__FP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/alo", UpdateAloXfWorldHierarchy__FP3ALO);

void PresetAloAccel(ALO *palo, float dt)
{
    return;
}

INCLUDE_ASM("asm/nonmatchings/P2/alo", ProjectAloTransform__FP3ALOfi);

INCLUDE_ASM("asm/nonmatchings/P2/alo", PredictAloTransform__FP3ALOT0fP6VECTORP7MATRIX3T3T3);

INCLUDE_ASM("asm/nonmatchings/P2/alo", PredictAloTransformAdjust__FP3ALOT0fP6VECTORP7MATRIX3T3T3);

INCLUDE_ASM("asm/nonmatchings/P2/alo", DupAloRo__FP3ALOP2ROT1);

INCLUDE_ASM("asm/nonmatchings/P2/alo", RenderFastShadow__FP3ALOP2CMP2RO);

INCLUDE_ASM("asm/nonmatchings/P2/alo", RenderAloAll__FP3ALOP2CMP2RO);

INCLUDE_ASM("asm/nonmatchings/P2/alo", RenderAloSelf__FP3ALOP2CMP2RO);

INCLUDE_ASM("asm/nonmatchings/P2/alo", RenderAloGlobset__FP3ALOP2CMP2RO);

INCLUDE_ASM("asm/nonmatchings/P2/alo", RenderAloLine__FP3ALOP2CMP6VECTORT2ff);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloOverrideCel__FP3ALOG4RGBA);

INCLUDE_ASM("asm/nonmatchings/P2/alo", FUN_00126ab0);

INCLUDE_ASM("asm/nonmatchings/P2/alo", UpdateAloThrob__FP3ALOf);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloBlotContext__FP3ALOP4BLOT);

INCLUDE_ASM("asm/nonmatchings/P2/alo", EnsureAloFader__FP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/alo", FadeAloIn__FP3ALOf);

INCLUDE_ASM("asm/nonmatchings/P2/alo", FadeAloOut__FP3ALOf);

INCLUDE_ASM("asm/nonmatchings/P2/alo", AdjustAloRtckMat__FP3ALOP2CM4RTCKP6VECTORP7MATRIX4);

INCLUDE_ASM("asm/nonmatchings/P2/alo", CloneAloHierarchy__FP3ALOT0);

INCLUDE_ASM("asm/nonmatchings/P2/alo", CloneAlo__FP3ALOT0);

INCLUDE_ASM("asm/nonmatchings/P2/alo", HandleAloMessage__FP3ALO5MSGIDPv);

INCLUDE_ASM("asm/nonmatchings/P2/alo", TranslateAloToPos__FP3ALOP6VECTOR);

JUNK_ADDIU(20);
JUNK_ADDIU(20);

INCLUDE_ASM("asm/nonmatchings/P2/alo", RotateAloToMat__FP3ALOP7MATRIX3);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloVelocityVec__FP3ALOP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloVelocityXYZ__FP3ALOfff);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloAngularVelocityVec__FP3ALOP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloAngularVelocityXYZ__FP3ALOfff);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloVelocityLocal__FP3ALOP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/alo", GetAloVelocityLocal__FP3ALOP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/alo", MatchAloOtherObject__FP3ALOT0);

INCLUDE_ASM("asm/nonmatchings/P2/alo", CalculateAloMovement__FP3ALOT0P6VECTORN42);

INCLUDE_ASM("asm/nonmatchings/P2/alo", CalculateAloTransform__FP3ALOT0iP6VECTORP7MATRIX3T3T3);

INCLUDE_ASM("asm/nonmatchings/P2/alo", CalculateAloTransformAdjust__FP3ALOT0P6VECTORP7MATRIX3T2T2);

INCLUDE_ASM("asm/nonmatchings/P2/alo", ConvertAloPos__FP3ALOT0P6VECTORT2);

INCLUDE_ASM("asm/nonmatchings/P2/alo", ConvertAloVec__FP3ALOT0P6VECTORT2);

INCLUDE_ASM("asm/nonmatchings/P2/alo", ConvertAloMat__FP3ALOT0P7MATRIX3T2);

INCLUDE_ASM("asm/nonmatchings/P2/alo", FDrivenAlo__FP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/alo", RetractAloDrive__FP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/alo", ConvertAloMovement__FP3ALOT0P6VECTORN82);

INCLUDE_ASM("asm/nonmatchings/P2/alo", CalculateAloDrive__FP3ALOP3CLQP2LMffPfN25);

INCLUDE_ASM("asm/nonmatchings/P2/alo", FGetAloChildrenList__FP3ALOPv);

ACTSEG *PactsegNewAlo(ALO *palo)
{
    return (ACTSEG *)PactNew(palo->psw, palo, &g_vtactseg);
}

INCLUDE_ASM("asm/nonmatchings/P2/alo", LoadAloFromBrx__FP3ALOP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/alo", LoadAloAloxFromBrx__FP3ALOP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/alo", BindAloAlox__FP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/alo", AdjustAloRotation__FP3ALOP7MATRIX3P6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/alo", UnadjustAloRotation__FP3ALOP7MATRIX3);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloInitialVelocity__FP3ALOP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloInitialAngularVelocity__FP3ALOP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/alo", PasegdEnsureAlo__FP3ALO);

void SetAloFastShadowRadius(ALO *palo, float sRadius)
{
    // palo->sFastShadowRadius
    STRUCT_OFFSET(palo, 0x28c, float) = sRadius * 0.01f;
}

void GetAloFastShadowRadius(ALO *palo, float *psRadius)
{
    // palo->sFastShadowRadius
    *psRadius = STRUCT_OFFSET(palo, 0x28c, float) * 100.0f;
}

void SetAloFastShadowDepth(ALO *palo, float sDepth)
{
    // palo->sFastShadowDepth
    STRUCT_OFFSET(palo, 0x290, float) = sDepth * 0.01f;
}

void GetAloFastShadowDepth(ALO *palo, float *psDepth)
{
    // palo->sFastShadowDepth
    *psDepth = STRUCT_OFFSET(palo, 0x290, float) * 100.0f;
}

INCLUDE_ASM("asm/nonmatchings/P2/alo", PshadowAloEnsure__FP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloCastShadow__FP3ALOi);

void SetAloShadowShader(ALO *palo, OID oidShdShadow)
{
    SHADOW *pshadow = PshadowAloEnsure(palo);
    SetShadowShader(pshadow, oidShdShadow);
}

void SetAloShadowNearRadius(ALO *palo, float sNearRadius)
{
    SHADOW *pshadow = PshadowAloEnsure(palo);
    SetShadowNearRadius(pshadow, sNearRadius);
}

void SetAloShadowFarRadius(ALO *palo, float sFarRadius)
{
    SHADOW *pshadow = PshadowAloEnsure(palo);
    SetShadowFarRadius(pshadow, sFarRadius);
}

void SetAloShadowNearCast(ALO *palo, float sNearCast)
{
    SHADOW *pshadow = PshadowAloEnsure(palo);
    SetShadowNearCast(pshadow, sNearCast);
}

void SetAloShadowFarCast(ALO *palo, float sFarCast)
{
    SHADOW *pshadow = PshadowAloEnsure(palo);
    SetShadowFarCast(pshadow, sFarCast);
}

void SetAloShadowConeAngle(ALO *palo, float degConeAngle)
{
    SHADOW *pshadow = PshadowAloEnsure(palo);
    SetShadowConeAngle(pshadow, degConeAngle);
}

void SetAloShadowFrustrumUp(ALO *palo, VECTOR *pvecUp)
{
    SHADOW *pshadow = PshadowAloEnsure(palo);
    SetShadowFrustrumUp(pshadow, pvecUp);
}

void SetAloDynamicShadowObject(ALO *palo, OID oidDysh)
{
    SHADOW *pshadow = PshadowAloEnsure(palo);
    STRUCT_OFFSET(pshadow, 0xb0, OID) = oidDysh; // pshadow->oidDysh
}

SHADOW *PshadowInferAlo(ALO *palo)
{
    // palo->pshadow
    if (STRUCT_OFFSET(palo, 0x284, SHADOW *))
    {
        return STRUCT_OFFSET(palo, 0x284, SHADOW *);
    }

    InitShadow(&s_shadow);
    return &s_shadow;
}

void GetAloCastShadow(ALO *palo, int *pfCastShadow)
{
    // palo->pshadow
    *pfCastShadow = (STRUCT_OFFSET(palo, 0x284, SHADOW *) != (SHADOW *)nullptr);
}

/**
 * @todo 63.18% match.
 * https://decomp.me/scratch/AqBOS
 */
INCLUDE_ASM("asm/nonmatchings/P2/alo", GetAloShadowShader__FP3ALOP3OID);
#ifdef SKIP_ASM
void GetAloShadowShader(ALO *palo, OID *poidShdShadow)
{
    SHADOW *pshadow = STRUCT_OFFSET(palo, 0x284, SHADOW *);

    if (!pshadow || !pshadow->pshd)
    {
        *poidShdShadow = OID_Nil;
        return;
    }

    *poidShdShadow = (OID)(pshadow->pshd->oid);
}
#endif // SKIP_ASM

void GetAloShadowNearRadius(ALO *palo, float *psNearRadius)
{
    SHADOW *pshadow = PshadowInferAlo(palo);
    *psNearRadius = pshadow->sNearRadius;
}

void GetAloShadowFarRadius(ALO *palo, float *psFarRadius)
{
    SHADOW *pshadow = PshadowInferAlo(palo);
    *psFarRadius = pshadow->sFarRadius;
}

void GetAloShadowNearCast(ALO *palo, float *psNearCast)
{
    SHADOW *pshadow = PshadowInferAlo(palo);
    *psNearCast = pshadow->sNearCast;
}

void GetAloShadowFarCast(ALO *palo, float *psFarCast)
{
    SHADOW *pshadow = PshadowInferAlo(palo);
    *psFarCast = pshadow->sFarCast;
}

INCLUDE_ASM("asm/nonmatchings/P2/alo", GetAloShadowConeAngle__FP3ALOPf);

INCLUDE_ASM("asm/nonmatchings/P2/alo", GetAloShadowFrustrumUp__FP3ALOP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/alo", GetAloEuler__FP3ALOP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloEuler__FP3ALOP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/alo", EnsureAloActRestore__FP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/alo", EnsureAloActla__FP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/alo", RecacheAloActList__FP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/alo", InsertAloAct__FP3ALOP3ACT);

INCLUDE_ASM("asm/nonmatchings/P2/alo", ResortAloActList__FP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/alo", PasegaFindAlo__FP3ALO3OID);

INCLUDE_ASM("asm/nonmatchings/P2/alo", PsmaFindAlo__FP3ALO3OID);

INCLUDE_ASM("asm/nonmatchings/P2/alo", PasegaFindAloNearest__FP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/alo", CreateAloActadj__FP3ALOiPP6ACTADJ);

INCLUDE_ASM("asm/nonmatchings/P2/alo", FIsAloStatic__FP3ALO);

void ResolveAlo(ALO *palo)
{
    if (palo->paloRoot)
    {
        STRUCT_OFFSET(palo->paloRoot, 0x228, int) = 0; // palo->paloRoot->cframeStatic
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloPositionSpring__FP3ALOf);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloPositionSpringDetail__FP3ALOP3CLQ);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloPositionDamping__FP3ALOf);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloPositionDampingDetail__FP3ALOP3CLQ);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloRotationSpring__FP3ALOf);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloRotationSpringDetail__FP3ALOP3CLQ);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloRotationDamping__FP3ALOf);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloRotationDampingDetail__FP3ALOP3CLQ);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloPositionSmooth__FP3ALOf);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloPositionSmoothMaxAccel__FP3ALOf);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloPositionSmoothDetail__FP3ALOP4SMPA);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloRotationSmooth__FP3ALOf);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloRotationSmoothMaxAccel__FP3ALOf);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloRotationSmoothDetail__FP3ALOP4SMPA);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloDefaultAckPos__FP3ALO3ACK);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloDefaultAckRot__FP3ALO3ACK);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloRestorePosition__FP3ALOi);

INCLUDE_ASM("asm/nonmatchings/P2/alo", FUN_0012a3c8);

INCLUDE_ASM("asm/nonmatchings/P2/alo", FUN_0012a3e8);

INCLUDE_ASM("asm/nonmatchings/P2/alo", FUN_0012a418);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloRestorePositionAck__FP3ALO3ACK);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloRestoreRotation__FP3ALOi);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloRestoreRotationAck__FP3ALO3ACK);

INCLUDE_ASM("asm/nonmatchings/P2/alo", FUN_0012a4e8);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloLookAt__FP3ALO3ACK);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloLookAtIgnore__FP3ALOf);

INCLUDE_ASM("asm/nonmatchings/P2/alo", GetAloLookAtIgnore__FP3ALOPf);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloLookAtPanFunction__FP3ALOP3CLQ);

INCLUDE_ASM("asm/nonmatchings/P2/alo", GetAloLookAtPanFunction__FP3ALOP3CLQ);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloLookAtPanLimits__FP3ALOP2LM);

INCLUDE_ASM("asm/nonmatchings/P2/alo", GetAloLookAtPanLimits__FP3ALOP2LM);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloLookAtTiltFunction__FP3ALOP3CLQ);

INCLUDE_ASM("asm/nonmatchings/P2/alo", GetAloLookAtTiltFunction__FP3ALOP3CLQ);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloLookAtTiltLimits__FP3ALOP2LM);

INCLUDE_ASM("asm/nonmatchings/P2/alo", GetAloLookAtTiltLimits__FP3ALOP2LM);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloLookAtEnabledPriority__FP3ALOi);

INCLUDE_ASM("asm/nonmatchings/P2/alo", GetAloLookAtEnabledPriority__FP3ALOPi);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloLookAtDisabledPriority__FP3ALOi);

INCLUDE_ASM("asm/nonmatchings/P2/alo", GetAloLookAtDisabledPriority__FP3ALOPi);

INCLUDE_ASM("asm/nonmatchings/P2/alo", FUN_0012a810);

INCLUDE_ASM("asm/nonmatchings/P2/alo", FUN_0012a848);

INCLUDE_ASM("asm/nonmatchings/P2/alo", FUN_0012a860);

INCLUDE_ASM("asm/nonmatchings/P2/alo", FUN_0012a888);

INCLUDE_ASM("asm/nonmatchings/P2/alo", FUN_0012a8b8);

INCLUDE_ASM("asm/nonmatchings/P2/alo", FUN_0012a8c8);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloRotationMatchesVelocity__FP3ALOff3ACK);

INCLUDE_ASM("asm/nonmatchings/P2/alo", PtargetEnsureAlo__FP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloTargetAttacks__FP3ALOi);

void SetAloTargetRadius(ALO *palo, float sRadiusTarget)
{
    TARGET *ptarget = PtargetEnsureAlo(palo);
    STRUCT_OFFSET(ptarget, 0x8c, float) = sRadiusTarget; // ptarget->sRadiusTarget
}

void SetAloTargetHitTest(ALO *palo, int fHitTest)
{
    TARGET *ptarget = PtargetEnsureAlo(palo);
    STRUCT_OFFSET(ptarget, 0x90, int) = fHitTest; // ptarget->fHitTest
}

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloScrollingMasterSpeeds__FP3ALOff);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloEyesClosed__FP3ALOf);

void EnsureAloSfx(ALO *palo)
{
    // palo->psfx
    if (!STRUCT_OFFSET(palo, 0x2ac, SFX *))
    {
        NewSfx(&STRUCT_OFFSET(palo, 0x2ac, SFX *));
    }
}

void SetAloSfxid(ALO *palo, SFXID sfxid)
{
    EnsureAloSfx(palo);
    STRUCT_OFFSET(palo, 0x2ac, SFX *)->sfxid = sfxid; // palo->psfx
}

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloSfxidSpl__FP3ALO5SFXID);

void GetAloSfxid(ALO *palo, SFXID *psfxid)
{
    SFXID sfxid = SFXID_Nil;
    if (STRUCT_OFFSET(palo, 0x2ac, SFX *)) // palo->psfx
    {
        sfxid = STRUCT_OFFSET(palo, 0x2ac, SFX *)->sfxid;
    }

    *psfxid = sfxid;
}

void SetAloSStart(ALO *palo, float sStart)
{
    EnsureAloSfx(palo);
    STRUCT_OFFSET(palo, 0x2ac, SFX *)->sStart = sStart; // palo->psfx
}

void GetAloSStart(ALO *palo, float *psStart)
{
    float sStart = 3000.0f;
    if (STRUCT_OFFSET(palo, 0x2ac, SFX *)) // palo->psfx
    {
        sStart = STRUCT_OFFSET(palo, 0x2ac, SFX *)->sStart;
    }

    *psStart = sStart;
}

void SetAloSFull(ALO *palo, float sFull)
{
    EnsureAloSfx(palo);
    STRUCT_OFFSET(palo, 0x2ac, SFX *)->sFull = sFull; // palo->psfx
}

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloSndRepeat__FP3ALOP2LM);

void GetAloSFull(ALO *palo, float *psFull)
{
    float sFull = 300.0f;
    if (STRUCT_OFFSET(palo, 0x2ac, SFX *)) // palo->psfx
    {
        sFull = STRUCT_OFFSET(palo, 0x2ac, SFX *)->sFull;
    }

    *psFull = sFull;
}

void SetAloUVolume(ALO *palo, float uVol)
{
    EnsureAloSfx(palo);
    STRUCT_OFFSET(palo, 0x2ac, SFX *)->uVol = uVol; // palo->psfx
}

void SetAloUDoppler(ALO *palo, float uDoppler)
{
    EnsureAloSfx(palo);
    STRUCT_OFFSET(palo, 0x2ac, SFX *)->uDoppler = uDoppler; // palo->psfx
}

void GetAloUDoppler(ALO *palo, float *puDoppler)
{
    float uDoppler = 0.0f;
    if (STRUCT_OFFSET(palo, 0x2ac, SFX *)) // palo->psfx
    {
        uDoppler = STRUCT_OFFSET(palo, 0x2ac, SFX *)->uDoppler;
    }

    *puDoppler = uDoppler;
}

void SetAloUVolumeSpl(ALO *palo, float uVol)
{
    // palo->psfx
    if (STRUCT_OFFSET(palo, 0x2ac, SFX *) && STRUCT_OFFSET(palo, 0x2ac, SFX *)->pamb)
    {
        SetPambVol(STRUCT_OFFSET(palo, 0x2ac, SFX *)->pamb, uVol);
    }
}

void GetAloUVolume(ALO *palo, float *puVol)
{
    float uVol = 1.0f;
    if (STRUCT_OFFSET(palo, 0x2ac, SFX *)) // palo->psfx
    {
        uVol = STRUCT_OFFSET(palo, 0x2ac, SFX *)->uVol;
    }

    *puVol = uVol;
}

void SetAloUPitch(ALO *palo, float uPitch)
{
    EnsureAloSfx(palo);
    STRUCT_OFFSET(palo, 0x2ac, SFX *)->uPitch = uPitch; // palo->psfx
}

void SetAloUPitchSpl(ALO *palo, float uPitch)
{
    // palo->psfx
    if (STRUCT_OFFSET(palo, 0x2ac, SFX *) && STRUCT_OFFSET(palo, 0x2ac, SFX *)->pamb)
    {
        SetPambFrq(STRUCT_OFFSET(palo, 0x2ac, SFX *)->pamb, uPitch);
    }
}

void GetAloUPitch(ALO *palo, float *puPitch)
{
    float uPitch = 0.0f;
    if (STRUCT_OFFSET(palo, 0x2ac, SFX *)) // palo->psfx
    {
        uPitch = STRUCT_OFFSET(palo, 0x2ac, SFX *)->uPitch;
    }

    *puPitch = uPitch;
}

INCLUDE_ASM("asm/nonmatchings/P2/alo", GetAloSndRepeat__FP3ALOP2LM);

INCLUDE_ASM("asm/nonmatchings/P2/alo", StartAloSound__FP3ALO5SFXIDfffP2LM);

void StopAloSound(ALO *palo)
{
    // palo->psfx
    if (STRUCT_OFFSET(palo, 0x2ac, SFX *))
    {
        StopSound(STRUCT_OFFSET(palo, 0x2ac, SFX *)->pamb, 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/alo", EnsureAloThrob__FP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloThrobKind__FP3ALO6THROBK);

void GetAloThrobKind(ALO *palo, THROBK *pthrobk)
{
    THROBK throbk = THROBK_Nil;
    if (STRUCT_OFFSET(palo, 0x288, THROB *)) // palo->throb
    {
        throbk = STRUCT_OFFSET(palo, 0x288, THROB *)->throbk;
    }

    *pthrobk = throbk;
}

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloThrobInColor__FP3ALOP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/alo", GetAloThrobInColor__FP3ALOP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloThrobOutColor__FP3ALOP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/alo", GetAloThrobOutColor__FP3ALOP6VECTOR);

void SetAloThrobDtInOut(ALO *palo, float dtInOut)
{
    EnsureAloThrob(palo);
    STRUCT_OFFSET(palo, 0x288, THROB *)->dtInOut = dtInOut;
}

void GetAloThrobDtInOut(ALO *palo, float *pdtInOut)
{
    float dtInOut = 0.0f;
    if (STRUCT_OFFSET(palo, 0x288, THROB *)) // palo->throb
    {
        dtInOut = STRUCT_OFFSET(palo, 0x288, THROB *)->dtInOut;
    }

    *pdtInOut = dtInOut;
}

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloInteractCane__FP3ALOi);

INCLUDE_ASM("asm/nonmatchings/P2/alo", GetAloInteractCane__FP3ALOPi);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloInteractCaneSweep__FP3ALOi);

INCLUDE_ASM("asm/nonmatchings/P2/alo", GetAloInteractCaneSweep__FP3ALOPi);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloInteractCaneRush__FP3ALOi);

INCLUDE_ASM("asm/nonmatchings/P2/alo", GetAloInteractCaneRush__FP3ALOPi);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloInteractCaneSmash__FP3ALOi);

INCLUDE_ASM("asm/nonmatchings/P2/alo", GetAloInteractCaneSmash__FP3ALOPi);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloInteractBomb__FP3ALOi);

INCLUDE_ASM("asm/nonmatchings/P2/alo", GetAloInteractBomb__FP3ALOPi);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloInteractShock__FP3ALOi);

INCLUDE_ASM("asm/nonmatchings/P2/alo", GetAloInteractShock__FP3ALOPi);

int FAbsorbAloWkr(ALO *palo, WKR *pwkr)
{
    return (pwkr->grfic != 0);
}

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloPoseCombo__FP3ALO3OID);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloForceCameraFade__FP3ALOi);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloRealClock__FP3ALOi);

INCLUDE_ASM("asm/nonmatchings/P2/alo", FUN_0012b550);

INCLUDE_ASM("asm/nonmatchings/P2/alo", FUN_0012b590);

INCLUDE_ASM("asm/nonmatchings/P2/alo", FUN_0012b5b8);

JUNK_ADDIU(10);
JUNK_WORD(0x7c450000);
JUNK_WORD(0x48220800);

INCLUDE_ASM("asm/nonmatchings/P2/alo", FUN_0012b6b8);

INCLUDE_ASM("asm/nonmatchings/P2/alo", anticrack_itm_firewall);
