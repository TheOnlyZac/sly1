#include <act.h>
#include <alo.h>
#include <aseg.h>
#include <math.h>
#include <memory.h>
#include <shadow.h>
#include <shd.h>
#include <target.h>
#include <lookat.h>
#include <find.h>
#include <brx.h>
#include <fader.h>
#include <glob.h>

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

void InvalidateAloLighting(ALO *palo)
{
    int iglobi;

    // palo->globset: count at +0xc, GLOBI array (stride 0x28) at +0x14; invalidate lighting frame at +0x8
    for (iglobi = 0; iglobi < STRUCT_OFFSET(palo, 0x238, int); iglobi++)
    {
        char *pb = STRUCT_OFFSET(palo, 0x240, char *) + iglobi * 0x28;
        *(int *)(pb + 8) = -1;
    }
}

// alo.h declares `void UpdateAloXfWorld__FP3ALO(ALO *palo);` as a C++ function; with that
// declaration in scope, GCC 2.95 mangles a plain `void UpdateAloXfWorld(ALO *)` definition
// to UpdateAloXfWorld__FP3ALO__FP3ALO. Defining the literal symbol with C linkage (void*
// parameter so it does not conflict with the C++ declaration) emits the exact target symbol.
// If alo.h:279 is ever fixed to `void UpdateAloXfWorld(ALO *palo);`, this can become a plain
// C++ `void UpdateAloXfWorld(ALO *palo)` definition (verified to also match).
extern "C" void UpdateAloXfWorld__FP3ALO(void *pvalo)
{
    ALO *palo = (ALO *)pvalo;
    // vtable slot at 0x5c: compiled offset of pfnUpdateLoXfWorldHierarchy in VTLO
    // (the real game slot is probably "update xf world"; the header's VTLO has an extra
    // pfnUpdateLo entry shifting the names, but the compiled offset is what matters).
    void (*pfn)(ALO *) = (void (*)(ALO *))palo->pvtlo->pfnUpdateLoXfWorldHierarchy;

    if (pfn != 0)
    {
        pfn(palo);
    }
}

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

void SetAloVelocityXYZ(ALO *palo, float x, float y, float z)
{
    VECTOR vec;

    vec.x = x;
    vec.y = y;
    vec.z = z;
    ((void (*)(ALO *, VECTOR *))STRUCT_OFFSET(palo->pvtlo, 0x90, void *))(palo, &vec);
}

void SetAloAngularVelocityVec(ALO *palo, VECTOR *pw)
{
    ACT *pactRot;

    STRUCT_OFFSET(palo, 0x160, VU_VECTOR) = *(VU_VECTOR *)pw; // palo->wWorld (angular velocity)
    pactRot = STRUCT_OFFSET(palo, 0x1f0, ACT *); // palo->pactRot
    if (pactRot != NULL)
    {
        AdaptAct(pactRot);
    }

    if (!FIsZeroW(pw))
    {
        ResolveAlo(palo);
    }
}

void SetAloAngularVelocityXYZ(ALO *palo, float x, float y, float z)
{
    VECTOR w;

    w.x = x;
    w.y = y;
    w.z = z;
    (*(void (**)(ALO *, VECTOR *))((char *)palo->pvtlo + 0x94))(palo, &w);
}

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloVelocityLocal__FP3ALOP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/alo", GetAloVelocityLocal__FP3ALOP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/alo", MatchAloOtherObject__FP3ALOT0);

INCLUDE_ASM("asm/nonmatchings/P2/alo", CalculateAloMovement__FP3ALOT0P6VECTORN42);

INCLUDE_ASM("asm/nonmatchings/P2/alo", CalculateAloTransform__FP3ALOT0iP6VECTORP7MATRIX3T3T3);

INCLUDE_ASM("asm/nonmatchings/P2/alo", CalculateAloTransformAdjust__FP3ALOT0P6VECTORP7MATRIX3T2T2);

INCLUDE_ASM("asm/nonmatchings/P2/alo", ConvertAloPos__FP3ALOT0P6VECTORT2);

INCLUDE_ASM("asm/nonmatchings/P2/alo", ConvertAloVec__FP3ALOT0P6VECTORT2);

INCLUDE_ASM("asm/nonmatchings/P2/alo", ConvertAloMat__FP3ALOT0P7MATRIX3T2);

int FDrivenAlo(ALO *palo)
{
    ACT *pact;

    pact = STRUCT_OFFSET(palo, 0x1ec, ACT *); // palo->pactPos
    if (pact != NULL && STRUCT_OFFSET(pact, 0x10, char) == ACK_Drive)
    {
        return 1;
    }

    pact = STRUCT_OFFSET(palo, 0x1f0, ACT *); // palo->pactRot
    if (pact != NULL && STRUCT_OFFSET(pact, 0x11, char) == ACK_Drive)
    {
        return 1;
    }

    return 0;
}

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

ASEGD *PasegdEnsureAlo(ALO *palo)
{
    ASEGD *&pasegd = STRUCT_OFFSET(palo, 0x2a0, ASEGD *); // palo->pasegd

    if (!pasegd)
    {
        pasegd = (ASEGD *)PvAllocSwClearImpl(sizeof(ASEGD));

        pasegd->oidAseg = OID_Nil;
        pasegd->iak = IAK_Time;
        pasegd->tLocal = 0.0f;
        pasegd->svtLocal = 1.0f;
    }

    return pasegd;
}

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

SHADOW *PshadowAloEnsure(ALO *palo)
{
    if (!STRUCT_OFFSET(palo, 0x284, SHADOW *))
    {
        SHADOW *pshadow = (SHADOW *)PvAllocSlotheapClearImpl(&STRUCT_OFFSET(palo->psw, 0x1bf4, SLOTHEAP));
        STRUCT_OFFSET(palo, 0x284, SHADOW *) = pshadow;
        InitShadow(pshadow);
        AppendDlEntry(&STRUCT_OFFSET(palo->psw, 0x1c00, DL), STRUCT_OFFSET(palo, 0x284, SHADOW *));
    }
    return STRUCT_OFFSET(palo, 0x284, SHADOW *);
}

extern DL D_00262300;

void SetAloCastShadow(ALO *palo, int fCastShadow)
{
    SHADOW *pshadow;

    if (fCastShadow)
    {
        PshadowAloEnsure(palo);
        return;
    }

    pshadow = STRUCT_OFFSET(palo, 0x284, SHADOW *); // palo->pshadow
    if (pshadow != NULL)
    {
        RemoveDlEntry(&STRUCT_OFFSET(palo->psw, 0x1c00, DL), pshadow);
        AppendDlEntry(&D_00262300, STRUCT_OFFSET(palo, 0x284, SHADOW *));
        STRUCT_OFFSET(palo, 0x284, SHADOW *) = NULL;
    }
}

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
    *pfCastShadow = (STRUCT_OFFSET(palo, 0x284, SHADOW *) != NULL);
}

void GetAloShadowShader(ALO *palo, OID *poidShdShadow)
{
    // palo->pshadow
    SHADOW *pshadow = STRUCT_OFFSET(palo, 0x284, SHADOW *);

    if (pshadow && pshadow->pshd)
    {
        *poidShdShadow = (OID)pshadow->pshd->oid;
    }
    else
    {
        *poidShdShadow = OID_Nil;
    }
}

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

void GetAloShadowConeAngle(ALO *palo, float *pdegConeAngle)
{
    const float RAD_TO_DEG = 57.295776f;
    SHADOW *pshadow = PshadowInferAlo(palo);
    *pdegConeAngle = atan2f(pshadow->sNearRadius / pshadow->sNearCast, 1.0f) * RAD_TO_DEG * 2.0f;
}

void GetAloShadowFrustrumUp(ALO *palo, VECTOR *pvecUp)
{
    SHADOW *pshadow = PshadowInferAlo(palo);
    *(VU_VECTOR *)pvecUp = STRUCT_OFFSET(pshadow, 0x30, VU_VECTOR); // pshadow->vecFrustrumUp
}

INCLUDE_ASM("asm/nonmatchings/P2/alo", GetAloEuler__FP3ALOP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloEuler__FP3ALOP6VECTOR);

extern VTACT D_00219560;

void EnsureAloActRestore(ALO *palo)
{
    if (STRUCT_OFFSET(palo, 0x1fc, ACT *) == NULL) // palo->pactRestore
    {
        ACT *pact = PactNew(palo->psw, palo, &D_00219560);
        STRUCT_OFFSET(palo, 0x1fc, ACT *) = pact;
        InsertAloAct(palo, pact);
    }
}

extern VTACT D_0021A790;

void EnsureAloActla(ALO *palo)
{
    if (STRUCT_OFFSET(palo, 0x200, ACT *) == NULL) // palo->pactla
    {
        ACT *pact = PactNew(palo->psw, palo, &D_0021A790);
        STRUCT_OFFSET(palo, 0x200, ACT *) = pact;
        InsertAloAct(palo, pact);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/alo", RecacheAloActList__FP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/alo", InsertAloAct__FP3ALOP3ACT);

INCLUDE_ASM("asm/nonmatchings/P2/alo", ResortAloActList__FP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/alo", PasegaFindAlo__FP3ALO3OID);

INCLUDE_ASM("asm/nonmatchings/P2/alo", PsmaFindAlo__FP3ALO3OID);

ASEGA *PasegaFindAloNearest(ALO *paloLeaf)
{
    while (paloLeaf != NULL)
    {
        ACT *pact = STRUCT_OFFSET(paloLeaf, 0x1ec, ACT *);
        if (pact != NULL && pact->pvtact == &g_vtactseg)
            return STRUCT_OFFSET(pact, 0x1c, ASEGA *);

        pact = STRUCT_OFFSET(paloLeaf, 0x1f0, ACT *);
        if (pact != NULL && pact->pvtact == &g_vtactseg)
            return STRUCT_OFFSET(pact, 0x1c, ASEGA *);

        paloLeaf = paloLeaf->paloParent;
    }
    return NULL;
}

extern VTACT D_002195D8;

void CreateAloActadj(ALO *palo, int nPriority, ACTADJ **ppactadj)
{
    if (palo)
    {
        ACT *pact = PactNew(palo->psw, palo, &D_002195D8);
        pact->nPriority = nPriority;
        InsertAloAct(palo, pact);
        *ppactadj = (ACTADJ *)pact;
    }
}

int FIsAloStatic(ALO *palo)
{
    ALO *paloChild;

    if (!FIsZeroV(&STRUCT_OFFSET(palo, 0x150, VECTOR)))
    {
        return 0;
    }

    if (!FIsZeroW(&STRUCT_OFFSET(palo, 0x160, VECTOR)))
    {
        return 0;
    }

    paloChild = (ALO *)palo->dlChild.head;
    while (paloChild != NULL)
    {
        if (paloChild->pvtlo->grfcid & 1)
        {
            if (!FIsAloStatic(paloChild))
            {
                return 0;
            }
        }
        paloChild = (ALO *)paloChild->dleChild.next;
    }

    return 1;
}

void ResolveAlo(ALO *palo)
{
    if (palo->paloRoot)
    {
        STRUCT_OFFSET(palo->paloRoot, 0x228, int) = 0; // palo->paloRoot->cframeStatic
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloPositionSpring__FP3ALOf);

extern CLQ D_00260E70;
void SetAloPositionSpringDetail(ALO *palo, CLQ *pclq)
{
    CLQ *&pclqDst = STRUCT_OFFSET(palo, 0x20c, CLQ *); // palo->pclqPositionSpring (default &D_00260E70)

    if (pclqDst == &D_00260E70)
    {
        pclqDst = (CLQ *)PvAllocSwImpl(0x10);
    }

    *(VU_VECTOR *)pclqDst = *(VU_VECTOR *)pclq;
}

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloPositionDamping__FP3ALOf);

extern CLQ D_00260E80;
void SetAloPositionDampingDetail(ALO *palo, CLQ *pclq)
{
    CLQ *&pclqDst = STRUCT_OFFSET(palo, 0x210, CLQ *); // palo->pclwPosDamping (real offset 0x210)

    if (pclqDst == &D_00260E80)
    {
        pclqDst = (CLQ *)PvAllocSwImpl(0x10);
    }

    *(VU_VECTOR *)pclqDst = *(VU_VECTOR *)pclq;
}

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloRotationSpring__FP3ALOf);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloRotationSpringDetail__FP3ALOP3CLQ);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloRotationDamping__FP3ALOf);

extern CLQ D_00260EA0;
void SetAloRotationDampingDetail(ALO *palo, CLQ *pclq)
{
    CLQ *&pclqDst = STRUCT_OFFSET(palo, 0x218, CLQ *); // palo->pclqRotationDamping (default &D_00260EA0)

    if (pclqDst == &D_00260EA0)
    {
        pclqDst = (CLQ *)PvAllocSwImpl(0x10);
    }

    *(VU_VECTOR *)pclqDst = *(VU_VECTOR *)pclq;
}

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloPositionSmooth__FP3ALOf);

struct SMPA { float ag[4]; };
void SetAloPositionSmoothMaxAccel(ALO *palo, float r)
{
    SMPA smpa = *STRUCT_OFFSET(palo, 0x21c, SMPA *); // copy palo->psmpaPos
    smpa.ag[3] = r * (smpa.ag[0] - smpa.ag[1]) / smpa.ag[2];
    SetAloPositionSmoothDetail(palo, &smpa);
}

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloPositionSmoothDetail__FP3ALOP4SMPA);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloRotationSmooth__FP3ALOf);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloRotationSmoothMaxAccel__FP3ALOf);

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloRotationSmoothDetail__FP3ALOP4SMPA);

void SetAloDefaultAckPos(ALO *palo, ACK ack)
{
    STRUCT_OFFSET(palo, 0x2c9, char) = ack;
}

void SetAloDefaultAckRot(ALO *palo, ACK ack)
{
    STRUCT_OFFSET(palo, 0x2ca, char) = ack;
}

void SetAloRestorePosition(ALO *palo, int fRestore)
{
    SetAloRestorePositionAck(palo, fRestore ? ACK_Spring : ACK_Nil);
}

extern "C" void FUN_0012a3e8(ALO *palo, int unk);

extern "C" void FUN_0012a3c8(ALO *palo, int unk)
{
    FUN_0012a3e8(palo, unk != 0);
}

extern "C" void FUN_0012a3e8(ALO *palo, int n)
{
    STRUCT_OFFSET(palo, 0x2c8, uint64_t) =
        (STRUCT_OFFSET(palo, 0x2c8, uint64_t) & ~((uint64_t)3 << 40)) | ((uint64_t)(n & 3) << 40);
}

extern "C" void FUN_0012a418(ALO *palo, int *pn)
{
    *pn = (int)(STRUCT_OFFSET(palo, 0x2c8, uint64_t) >> 40) & 3;
}

void SetAloRestorePositionAck(ALO *palo, ACK ack)
{
    EnsureAloActRestore(palo);
    // palo->pactRestore (ACT at 0x1FC), ackPos byte at +0x10
    STRUCT_OFFSET(STRUCT_OFFSET(palo, 0x1fc, ACT *), 0x10, char) = ack;
    (*(void (**)(ALO *))((char *)palo->pvtlo + 0xBC))(palo);
}

void SetAloRestoreRotation(ALO *palo, int fRestore)
{
    SetAloRestoreRotationAck(palo, fRestore ? ACK_Spring : ACK_Nil);
}

void SetAloRestoreRotationAck(ALO *palo, ACK ack)
{
    EnsureAloActRestore(palo);
    // palo->pactRestore (ACT at 0x1FC), ackRot byte at +0x11
    STRUCT_OFFSET(STRUCT_OFFSET(palo, 0x1fc, ACT *), 0x11, char) = ack;
    (*(void (**)(ALO *))((char *)palo->pvtlo + 0xBC))(palo);
}

extern "C" void FUN_0012a4e8(ALO *palo, int n)
{
    void *pactrest;

    EnsureAloActRestore(palo);
    pactrest = STRUCT_OFFSET(palo, 0x1fc, void *);
    STRUCT_OFFSET(pactrest, 0x14, int) = n;
    ResortAloActList(palo);
}

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloLookAt__FP3ALO3ACK);

void SetAloLookAtIgnore(ALO *palo, float sIgnore)
{
    EnsureAloActla(palo);
    STRUCT_OFFSET(STRUCT_OFFSET(palo, 0x200, void *), 0x40, float) = sIgnore;
}

void GetAloLookAtIgnore(ALO *palo, float *psIgnore)
{
    void *pactla = STRUCT_OFFSET(palo, 0x200, void *);
    float sIgnore = 0.0f;

    if (pactla)
        sIgnore = STRUCT_OFFSET(pactla, 0x40, float);

    *psIgnore = sIgnore;
}

void SetAloLookAtPanFunction(ALO *palo, CLQ *pclq)
{
    EnsureAloActla(palo);
    STRUCT_OFFSET(STRUCT_OFFSET(palo, 0x200, void *), 0x50, qword) = STRUCT_OFFSET(pclq, 0x0, qword);
}

void GetAloLookAtPanFunction(ALO *palo, CLQ *pclq)
{
    extern CLQ D_00275C40;
    void *pactla = STRUCT_OFFSET(palo, 0x200, void *);
    CLQ *pclqSrc;

    if (pactla)
        pclqSrc = &STRUCT_OFFSET(pactla, 0x50, CLQ);
    else
        pclqSrc = &D_00275C40;

    *(VU_VECTOR *)pclq = *(VU_VECTOR *)pclqSrc;
}

void SetAloLookAtPanLimits(ALO *palo, LM *plm)
{
    EnsureAloActla(palo);
    STRUCT_OFFSET(STRUCT_OFFSET(palo, 0x200, void *), 0x60, LM) = *plm;
}

void GetAloLookAtPanLimits(ALO *palo, LM *plm)
{
    void *pactla = STRUCT_OFFSET(palo, 0x200, void *);
    LM *plmSrc;

    if (pactla)
        plmSrc = &STRUCT_OFFSET(pactla, 0x60, LM);
    else
        plmSrc = &g_lmZeroOne;

    *plm = *plmSrc;
}

void SetAloLookAtTiltFunction(ALO *palo, CLQ *pclq)
{
    EnsureAloActla(palo);
    STRUCT_OFFSET(STRUCT_OFFSET(palo, 0x200, void *), 0x70, qword) = STRUCT_OFFSET(pclq, 0x0, qword);
}

extern qword D_00275C40;
void GetAloLookAtTiltFunction(ALO *palo, CLQ *pclq)
{
    void *pactla = STRUCT_OFFSET(palo, 0x200, void *);
    qword *pqSrc;

    if (pactla)
        pqSrc = &STRUCT_OFFSET(pactla, 0x70, qword);
    else
        pqSrc = &D_00275C40;

    *(qword *)pclq = *pqSrc;
}

void SetAloLookAtTiltLimits(ALO *palo, LM *plm)
{
    EnsureAloActla(palo);
    STRUCT_OFFSET(STRUCT_OFFSET(palo, 0x200, void *), 0x80, LM) = *plm;
}

void GetAloLookAtTiltLimits(ALO *palo, LM *plm)
{
    void *pactla = STRUCT_OFFSET(palo, 0x200, void *);
    LM *plmSrc;

    if (pactla)
        plmSrc = &STRUCT_OFFSET(pactla, 0x80, LM);
    else
        plmSrc = &g_lmZeroOne;

    *plm = *plmSrc;
}

void SetAloLookAtEnabledPriority(ALO *palo, int nPriority)
{
    EnsureAloActla(palo);
    STRUCT_OFFSET(STRUCT_OFFSET(palo, 0x200, void *), 0x44, int) = nPriority;
}

void GetAloLookAtEnabledPriority(ALO *palo, int *pnPriority)
{
    void *pactla = STRUCT_OFFSET(palo, 0x200, void *);
    int nPriority = 0;

    if (pactla)
        nPriority = STRUCT_OFFSET(pactla, 0x44, int);

    *pnPriority = nPriority;
}

void SetAloLookAtDisabledPriority(ALO *palo, int nPriority)
{
    EnsureAloActla(palo);
    STRUCT_OFFSET(STRUCT_OFFSET(palo, 0x200, void *), 0x48, int) = nPriority;
}

void GetAloLookAtDisabledPriority(ALO *palo, int *pnPriority)
{
    void *pactla = STRUCT_OFFSET(palo, 0x200, void *);
    int nPriority = 0;

    if (pactla)
        nPriority = STRUCT_OFFSET(pactla, 0x48, int);

    *pnPriority = nPriority;
}

extern "C" void FUN_0012a810(ALO *palo, int n)
{
    void *pactla;

    EnsureAloActla(palo);
    pactla = STRUCT_OFFSET(palo, 0x200, void *);
    STRUCT_OFFSET(pactla, 0x20, int) = n;
}

void FUN_0012a848(ALO *palo, int *pn)
{
    void *pactla = STRUCT_OFFSET(palo, 0x200, void *);
    int n = -1;

    if (pactla)
        n = STRUCT_OFFSET(pactla, 0x20, int);

    *pn = n;
}

extern "C" void FUN_0012a860(ALO *palo, ALO *paloTarget)
{
    extern VECTOR D_00248D30;
    SetActlaTarget(STRUCT_OFFSET(palo, 0x200, ACTLA *), paloTarget, &D_00248D30);
}

extern "C" void FUN_0012a888(ALO *palo, ALO **ppaloTarget)
{
    *ppaloTarget = PaloGetActlaTarget(STRUCT_OFFSET(palo, 0x200, ACTLA *));
}

void FUN_0012a8b8(ALO *palo)
{
    void *pactla = STRUCT_OFFSET(palo, 0x200, void*);
    STRUCT_OFFSET(pactla, 0x4C, int) = 0;
}

extern "C" void FUN_0012a8c8(ALO *palo)
{
    void *pactla = STRUCT_OFFSET(palo, 0x200, void *);
    STRUCT_OFFSET(pactla, 0x4C, int) = 1;
}

INCLUDE_ASM("asm/nonmatchings/P2/alo", SetAloRotationMatchesVelocity__FP3ALOff3ACK);

TARGET *PtargetEnsureAlo(ALO *palo)
{
    TARGET *ptarget = (TARGET *)PloFindSwObject(palo->psw, 0x102, (OID)0x22a, palo);

    if (ptarget == NULL)
    {
        ptarget = (TARGET *)PloNew((CID)0x75, palo->psw, palo, (OID)0x22a, -1);
    }

    return ptarget;
}

void SetAloTargetAttacks(ALO *palo, GRFTAK grftak)
{
    TARGET *ptarget = PtargetEnsureAlo(palo);
    if (grftak != -1)
    {
        STRUCT_OFFSET(ptarget, 0x88, GRFTAK) = grftak; // ptarget->grftak
    }
}

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

void SetAloSndRepeat(ALO *palo, LM *plm)
{
    EnsureAloSfx(palo);
    STRUCT_OFFSET(palo, 0x2ac, SFX *)->lmRepeat = *plm; // palo->psfx
}

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

void GetAloSndRepeat(ALO *palo, LM *plmRepeat)
{
    // palo->psfx
    if (STRUCT_OFFSET(palo, 0x2ac, SFX *))
    {
        *plmRepeat = STRUCT_OFFSET(palo, 0x2ac, SFX *)->lmRepeat;
    }
    else
    {
        plmRepeat->gMin = -1.0f;
        plmRepeat->gMax = -1.0f;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/alo", StartAloSound__FP3ALO5SFXIDfffP2LM);

void StopAloSound(ALO *palo)
{
    // palo->psfx
    if (STRUCT_OFFSET(palo, 0x2ac, SFX *))
    {
        StopSound(STRUCT_OFFSET(palo, 0x2ac, SFX *)->pamb, 0);
    }
}

extern qword D_00261000[4];

void EnsureAloThrob(ALO *palo)
{
    THROB *&pthrob = STRUCT_OFFSET(palo, 0x288, THROB *);

    if (!pthrob)
    {
        qword *pdst = (qword *)PvAllocSwImpl(0x40);
        pthrob = (THROB *)pdst;
        pdst[0] = D_00261000[0];
        pdst[1] = D_00261000[1];
        pdst[2] = D_00261000[2];
        pdst[3] = D_00261000[3];
        pthrob->throbk = (THROBK)-1;
    }
}

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

void SetAloThrobInColor(ALO *palo, VECTOR *phsvInColor)
{
    EnsureAloThrob(palo);
    // palo->pthrob->hsvInColor
    STRUCT_OFFSET(STRUCT_OFFSET(palo, 0x288, THROB *), 0x10, VU_VECTOR) = *(VU_VECTOR *)phsvInColor;
}

extern VU_VECTOR D_00248D30;
void GetAloThrobInColor(ALO *palo, VECTOR *phsvInColor)
{
    THROB *pthrob = STRUCT_OFFSET(palo, 0x288, THROB *); // palo->pthrob
    VU_VECTOR *pqSrc;

    if (pthrob)
        pqSrc = &STRUCT_OFFSET(pthrob, 0x10, VU_VECTOR); // pthrob->hsvInColor
    else
        pqSrc = &D_00248D30;

    *(VU_VECTOR *)phsvInColor = *pqSrc;
}

void SetAloThrobOutColor(ALO *palo, VECTOR *phsvOutColor)
{
    EnsureAloThrob(palo);
    // palo->pthrob->hsvOutColor
    STRUCT_OFFSET(STRUCT_OFFSET(palo, 0x288, THROB *), 0x20, VU_VECTOR) = *(VU_VECTOR *)phsvOutColor;
}

void GetAloThrobOutColor(ALO *palo, VECTOR *phsvOutColor)
{
    THROB *pthrob = STRUCT_OFFSET(palo, 0x288, THROB *); // palo->throb
    VU_VECTOR *pvuvec;

    if (pthrob != 0)
    {
        pvuvec = &STRUCT_OFFSET(pthrob, 0x20, VU_VECTOR);
    }
    else
    {
        pvuvec = &D_00248D30;
    }

    *(VU_VECTOR *)phsvOutColor = *pvuvec;
}

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

void SetAloInteractCane(ALO *palo, GRFIC grfic)
{
    STRUCT_OFFSET(palo, 0x2b2, char) = grfic;
    STRUCT_OFFSET(palo, 0x2b1, char) = grfic;
    STRUCT_OFFSET(palo, 0x2b0, char) = grfic;
}

void GetAloInteractCane(ALO *palo, GRFIC *pgrfic)
{
    *pgrfic = STRUCT_OFFSET(palo, 0x2B0, uchar);
}

void SetAloInteractCaneSweep(ALO *palo, GRFIC grfic)
{
    STRUCT_OFFSET(palo, 0x2b0, char) = grfic;
}

void GetAloInteractCaneSweep(ALO *palo, GRFIC *pgrfic)
{
    *pgrfic = STRUCT_OFFSET(palo, 0x2B0, uchar);
}

void SetAloInteractCaneRush(ALO *palo, GRFIC grfic)
{
    STRUCT_OFFSET(palo, 0x2b1, char) = grfic;
}

void GetAloInteractCaneRush(ALO *palo, GRFIC *pgrfic)
{
    *pgrfic = STRUCT_OFFSET(palo, 0x2B1, uchar);
}

void SetAloInteractCaneSmash(ALO *palo, GRFIC grfic)
{
    STRUCT_OFFSET(palo, 0x2b2, char) = grfic;
}

void GetAloInteractCaneSmash(ALO *palo, GRFIC *pgrfic)
{
    *pgrfic = STRUCT_OFFSET(palo, 0x2B2, uchar);
}

void SetAloInteractBomb(ALO *palo, GRFIC grfic)
{
    STRUCT_OFFSET(palo, 0x2B3, uchar) = grfic;
}

void GetAloInteractBomb(ALO *palo, GRFIC *pgrfic)
{
    *pgrfic = STRUCT_OFFSET(palo, 0x2B3, uchar);
}

void SetAloInteractShock(ALO *palo, GRFIC grfic)
{
    STRUCT_OFFSET(palo, 0x2b4, char) = grfic;
}

void GetAloInteractShock(ALO *palo, GRFIC *pgrfic)
{
    *pgrfic = STRUCT_OFFSET(palo, 0x2B4, uchar);
}

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
