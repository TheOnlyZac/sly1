/**
 * @todo Mangle all function names in INCLUDE_ASM macros.
 */
#include <cm.h>
#include <util.h>
#include <binoc.h>
#include <clock.h>
#include <light.h>

// todo fix data and rodata
// VECTOR4 g_posEyeDefault = { 0.0f, -2000.0f, 500.0f, 0.0f };
// VECTOR4 g_posCenterDefault = { 0.0f, 0.0f, 0.0f, 0.0f };

// float g_sNearFog = 500.0f;
// float g_sFarFog = 20000.0f;
// float g_uFogMax = 0.5f;
// RGBA g_rgbaFog = { 0, 0, 0, 0 };

// VECTOR4 D_002618B8 = { 0.5f, 0.0f, 0.1f, 10.0f }; // unknown

// float DT_CmJoltMax = 0.5f;
// float SW_CmJolt = 50.0f;
// CLQ s_clqUToUJolt = { 1.0f, -2.0f, 1.0f, 0.0f };
// VECTOR4 s_dposJolt = { 0.0f, 0.0f, 0.0f, 0.0f };
// VECTOR4 s_rotJolt = { 0.05f, 0.0f, 0.0f, 0.0f };

// VECTOR4 s_vecRange = { 0.0f, 0.0f, 0.0f, 0.0f };
// VECTOR4 s_vecOffset = { 0.0f, 0.0f, 0.0f, 0.0f };

// float R_SetCmSpring = 15.0f;
// float R_SetCmDamping = -8.0f;

// float D_00261928[] = { 1.0f, 5.0f, 10.0f, 12.0f, 15.0f, 12.0f, 10.0f, 5.0f, 1.0f }; // array of 9 floats
// float D_0026194C = 250.0f;
// float D_00261950 = 1500.0f;

// SMP s_smpSquishEye = { 2500.0f, 0.0f, 0.25f };
// SMP unk_padding = { 0.0f, 0.0f, 0.0f }; // needed to align next variables

// float D_00261970 = -250.0f;
// float D_00261974 = 250.0f;
// float D_00261978 = 250.0f;
// float D_0026197C = 0.0f;
// float D_00261980 = 250.0f;
// float D_00261984 = 250.0f;
// float D_00261988 = 250.0f;
// float D_0026198C = 0.0f;

// CM* g_pcm = NULL;

void StartupCm()
{
    return;
}

void CalcCmAdjust(CM *pcm, SO *psoFocus, CPDEFI *pcpdefi, VECTOR *pdpos)
{
    SetVectorCylind(pdpos, pcpdefi->radHome + 3.14159265359f, pcpdefi->sAdjust, 0);
}

INCLUDE_ASM("asm/nonmatchings/P2/cm", SpringCm__FfffP2CMP6VECTORP6VECTORP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/cm", AdjustCmCpdefi__FP2CMP2SOfP6CPDEFI);

INCLUDE_ASM("asm/nonmatchings/P2/cm", ResetCmAdjust__FP2CMP2SOP6CPDEFI);

INCLUDE_ASM("asm/nonmatchings/P2/cm", GetCmCpdefi__FP2CMP2SOfP6CPDEFI);

void BuildCmFgfn(CM *pcm, float uFog, FGFN *pfgfn)
{
    FitRecipFunction(
        1.0f, 4080.0f,
        pcm->sFarFog / pcm->sNearFog, (1.0f - pcm->uFogMax * uFog) * 4080.0f,
        &pfgfn->duFogBias, &pfgfn->ruFog
    );

    pfgfn->duFogBias = pfgfn->duFogBias + 8388608.0f;
    pfgfn->sNearFog = pcm->sNearFog;
    pfgfn->duFogPlusClipBias = pfgfn->duFogBias + 36864.0f;
}

INCLUDE_ASM("asm/nonmatchings/P2/cm", RecalcCmFrustrum__FP2CM);

INCLUDE_ASM("asm/nonmatchings/P2/cm", InitCm__FP2CM);

void SetSwCameraFov(float fov)
{
    SetCmFov(g_pcm, fov);
}

void SetSwCameraNearClip(float sNearClip)
{
    SetCmNearClip(g_pcm, sNearClip);
}

void SetSwCameraFarClip(float sFarClip)
{
    SetCmFarClip(g_pcm, sFarClip);
}

void SetSwCameraNearFog(float sNearFog)
{
    SetCmNearFog(g_pcm, sNearFog);
}

void SetSwCameraFarFog(float sFarFog)
{
    SetCmFarFog(g_pcm, sFarFog);
}

void SetSwCameraUFogMax(float uFogMax)
{
    SetCmUFogMax(g_pcm, uFogMax);
}

void SetSwCameraRgbaFog(SW *psw, RGBA *prgbaFog)
{
    SetCmRgbaFog(g_pcm, prgbaFog);
}

void SetSwCameraMrdRatio(float ratio)
{
    SetCmMrdRatio(g_pcm, ratio);
}

void SetCmPos(CM *pcm, VECTOR *ppos)
{
    SetCmPosMat(pcm, ppos, NULL);
}

void SetCmMat(CM *pcm, MATRIX3 *pmat)
{
    SetCmPosMat(pcm, NULL, pmat);
}

void SetCmFov(CM *pcm, float fov)
{
    pcm->radFOV = fov;
    pcm->radFOV2 = fov;
    pcm->unk = 0;
    RecalcCmFrustrum(pcm);
}

void SetCmNearClip(CM *pcm, float sNearClip)
{
    pcm->sNearClip = sNearClip;
    RecalcCmFrustrum(pcm);
}

void SetCmFarClip(CM *pcm, float sFarClip)
{
    pcm->sFarClip = sFarClip;
    RecalcCmFrustrum(pcm);
}

void SetCmNearFog(CM *pcm, float sNearFog)
{
    pcm->sNearFog = sNearFog;
    RecalcCmFrustrum(pcm);
}

void SetCmFarFog(CM *pcm, float sFarFog)
{
    pcm->sFarFog = sFarFog;
    RecalcCmFrustrum(pcm);
}

void SetCmUFogMax(CM *pcm, float uFogMax)
{
    pcm->uFogMax = uFogMax;
    RecalcCmFrustrum(pcm);
}

void SetCmRgbaFog(CM *pcm, RGBA *prgbaFog)
{
    pcm->rgbaFog = *prgbaFog;
    RecalcCmFrustrum(pcm);
}

void SetCmMrdRatio(CM *pcm, float rMRD)
{
    pcm->rMRD = rMRD;
    RecalcCmFrustrum(g_pcm);
}

INCLUDE_ASM("asm/nonmatchings/P2/cm", ResetCm__FP2CMi);

void ClearCmFadeObjects(CM *pcm)
{
    pcm->cpaloFade = 0;
}

void AddCmFadeObject(CM *pcm, ALO *palo)
{
    if ((uint)pcm->cpaloFade < 8)
    {
        pcm->apaloFade[pcm->cpaloFade++] = palo;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/cm", RemoveCmFadeObject__FP2CMP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/cm", FFilterCamera__FPvP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/cm", UpdateCmFade);

INCLUDE_ASM("asm/nonmatchings/P2/cm", UpdateCmLast);

INCLUDE_ASM("asm/nonmatchings/P2/cm", SetupCmRotateToCam);

INCLUDE_ASM("asm/nonmatchings/P2/cm", ConvertCmScreenToWorld);

INCLUDE_ASM("asm/nonmatchings/P2/cm", ConvertCmWorldToScreen);

INCLUDE_ASM("asm/nonmatchings/P2/cm", SetupCm__FP2CM);

INCLUDE_ASM("asm/nonmatchings/P2/cm", CombineEyeLookAtProj);

INCLUDE_ASM("asm/nonmatchings/P2/cm", BuildFrustrum);

INCLUDE_ASM("asm/nonmatchings/P2/cm", UpdateCmMat4);

INCLUDE_ASM("asm/nonmatchings/P2/cm", DrawCm__FP2CM);

INCLUDE_ASM("asm/nonmatchings/P2/cm", SetCmPosMat__FP2CMP6VECTORP7MATRIX3);

INCLUDE_ASM("asm/nonmatchings/P2/cm", SetCmLookAt);

INCLUDE_ASM("asm/nonmatchings/P2/cm", ConvertWorldToCylindVelocity);

INCLUDE_ASM("asm/nonmatchings/P2/cm", ConvertCylindToWorldVelocity);

INCLUDE_ASM("asm/nonmatchings/P2/cm", ResetCmLookAtSmooth__FP2CMP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/cm", SetCmLookAtSmooth);

INCLUDE_ASM("asm/nonmatchings/P2/cm", AdjustCmJoy__FP2CMP3JOY5JOYIDPf);

JUNK_WORD(0x0000102D);

INCLUDE_ASM("asm/nonmatchings/P2/cm", SetCmPolicy__FP2CM3CPPP5CPLCYP2SOPv);

INCLUDE_ASM("asm/nonmatchings/P2/cm", RevokeCmPolicy__FP2CMi3CPPP5CPLCYP2SOPv);

INCLUDE_ASM("asm/nonmatchings/P2/cm", FInsideCmMrd);

INCLUDE_ASM("asm/nonmatchings/P2/cm", DecomposeCylind);

INCLUDE_ASM("asm/nonmatchings/P2/cm", DecomposeSphere);

void SetCmCut(CM *pcm, float *pradCut)
{
    pcm->fCut = 1;
    if (pradCut)
    {
        pcm->fRadCut = 1;
        pcm->radCut = *pradCut;
    }
}

void EnableCmNextCut(CM *pcm)
{
    pcm->fCutNext = 1;
}

void ClearCmCut(CM *pcm)
{
    SetCmCut(pcm, 0);
}

INCLUDE_ASM("asm/nonmatchings/P2/cm", AdaptCm);

INCLUDE_ASM("asm/nonmatchings/P2/cm", SetCm);

INCLUDE_ASM("asm/nonmatchings/P2/cm", FUN_00145810);

INCLUDE_ASM("asm/nonmatchings/P2/cm", FUN_00145950);

INCLUDE_ASM("asm/nonmatchings/P2/cm", FUN_00145b68);

int FUN_00145dd8(void *punk, SO *pso)
{
    return STRUCT_OFFSET(pso, 0x538, int) != 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/cm", FUN_00145de8);

INCLUDE_ASM("asm/nonmatchings/P2/cm", FUN_00145e68);

void PushLookkCm(CM *pcm, LOOKK lookk)
{
    PushCplookLookk(&pcm->cplook, lookk);
}

LOOKK LookkPopCm(CM *pcm)
{
    return LookkPopCplook(&pcm->cplook);
}

LOOKK LookkCurCm(CM *pcm)
{
    return LookkCurCplook(&pcm->cplook);
}

void SetCmSniperFocus(CM *pcm, ALO *palo, float rScreen, float sRadius)
{
    pcm->cplook.paloFocusSniper = palo;
    pcm->cplook.rScreenSniper = rScreen;
    pcm->cplook.sRadiusSniper = sRadius;
}

void JoltCm(CM *pcm)
{
    pcm->tJolt = g_clock.t;
}

INCLUDE_ASM("asm/nonmatchings/P2/cm", FUN_00146038);

/**
 * @todo This is a compiler generated function. Remove once data is migrated.
 */
void cm__static_initialization_and_destruction_0(int __initialize_p, int __priority)
{
    if ((__priority == 0xFFFF) && (__initialize_p != 0))
    {
        g_rgbaFog = 0x80303030;
    }
}

/**
 * @todo This is a compiler generated function. Remove once data is migrated.
 */
void _GLOBAL_$I$StartupCm()
{
    cm__static_initialization_and_destruction_0(1, 0xffff);
}
