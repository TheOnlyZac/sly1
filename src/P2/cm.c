/**
 * @todo Mangle all function names.
 */
#include <cm.h>
#include <util.h>
#include <binoc.h>

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

// CM* g_pcm = (CM *)0x0;

INCLUDE_ASM(const s32, "P2/cm", CalcCmAdjust__FP2CMP2SOP6CPDEFIP6VECTOR);

INCLUDE_ASM(const s32, "P2/cm", SpringCm__FfffP2CMP6VECTORP6VECTORP6VECTOR);

INCLUDE_ASM(const s32, "P2/cm", AdjustCmCpdefi__FP2CMP2SOfP6CPDEFI);

INCLUDE_ASM(const s32, "P2/cm", ResetCmAdjust__FP2CMP2SOP6CPDEFI);

INCLUDE_ASM(const s32, "P2/cm", GetCmCpdefi__FP2CMP2SOfP6CPDEFI);

INCLUDE_ASM(const s32, "P2/cm", BuildCmFgfn__FP2CMfP4FGFN);

INCLUDE_ASM(const s32, "P2/cm", RecalcCmFrustrum__FP2CM);

INCLUDE_ASM(const s32, "P2/cm", InitCm__FP2CM);

INCLUDE_ASM(const s32, "P2/cm", SetSwCameraFov__Ff);

INCLUDE_ASM(const s32, "P2/cm", FUN_001437e8);

INCLUDE_ASM(const s32, "P2/cm", FUN_00143810);

INCLUDE_ASM(const s32, "P2/cm", FUN_00143838);

INCLUDE_ASM(const s32, "P2/cm", FUN_00143860);

INCLUDE_ASM(const s32, "P2/cm", FUN_00143888);

void SetSwCameraRgbaFog(SW *psw, RGBA *prgbaFog)
{
    SetCmRgbaFog(g_pcm, prgbaFog);
}

INCLUDE_ASM(const s32, "P2/cm", FUN_001438d8);

INCLUDE_ASM(const s32, "P2/cm", FUN_00143900);

INCLUDE_ASM(const s32, "P2/cm", FUN_00143920);

INCLUDE_ASM(const s32, "P2/cm", FUN_00143940);

INCLUDE_ASM(const s32, "P2/cm", FUN_00143968);

INCLUDE_ASM(const s32, "P2/cm", FUN_00143988);

INCLUDE_ASM(const s32, "P2/cm", FUN_001439a8);

INCLUDE_ASM(const s32, "P2/cm", FUN_001439c8);

INCLUDE_ASM(const s32, "P2/cm", FUN_001439e8);

INCLUDE_ASM(const s32, "P2/cm", SetCmRgbaFog__FP2CMP4RGBA);

INCLUDE_ASM(const s32, "P2/cm", SetCmMrdRatio__FP2CMf);

INCLUDE_ASM(const s32, "P2/cm", ResetCm);

//INCLUDE_ASM(const s32, "P2/cm", ClearCmFadeObjects__FP2CM);
void ClearCmFadeObjects(CM *pcm)
{
    pcm->field77_0x3ac = 0;
}

INCLUDE_ASM(const s32, "P2/cm", AddCmFadeObject);

INCLUDE_ASM(const s32, "P2/cm", RemoveCmFadeObject);

INCLUDE_ASM(const s32, "P2/cm", func_00143BA8);

INCLUDE_ASM(const s32, "P2/cm", UpdateCmFade);

INCLUDE_ASM(const s32, "P2/cm", UpdateCmLast);

INCLUDE_ASM(const s32, "P2/cm", SetupCmRotateToCam);

INCLUDE_ASM(const s32, "P2/cm", ConvertCmScreenToWorld);

INCLUDE_ASM(const s32, "P2/cm", ConvertCmWorldToScreen);

INCLUDE_ASM(const s32, "P2/cm", SetupCm__FP2CM);

INCLUDE_ASM(const s32, "P2/cm", CombineEyeLookAtProj);

INCLUDE_ASM(const s32, "P2/cm", BuildFrustrum);

INCLUDE_ASM(const s32, "P2/cm", UpdateCmMat4);

INCLUDE_ASM(const s32, "P2/cm", DrawCm);

INCLUDE_ASM(const s32, "P2/cm", SetCmPosMat);

INCLUDE_ASM(const s32, "P2/cm", SetCmLookAt);

INCLUDE_ASM(const s32, "P2/cm", ConvertWorldToCylindVelocity);

INCLUDE_ASM(const s32, "P2/cm", ConvertCylindToWorldVelocity);

INCLUDE_ASM(const s32, "P2/cm", ResetCmLookAtSmooth);

INCLUDE_ASM(const s32, "P2/cm", SetCmLookAtSmooth);

INCLUDE_ASM(const s32, "P2/cm", AdjustCmJoy);

INCLUDE_ASM(const s32, "P2/cm", func_00145080);

INCLUDE_ASM(const s32, "P2/cm", SetCmPolicy);

INCLUDE_ASM(const s32, "P2/cm", RevokeCmPolicy);

INCLUDE_ASM(const s32, "P2/cm", FInsideCmMrd);

INCLUDE_ASM(const s32, "P2/cm", DecomposeCylind);

INCLUDE_ASM(const s32, "P2/cm", DecomposeSphere);

INCLUDE_ASM(const s32, "P2/cm", SetCmCut);

INCLUDE_ASM(const s32, "P2/cm", FUN_001455e0);

INCLUDE_ASM(const s32, "P2/cm", FUN_001455f0);

INCLUDE_ASM(const s32, "P2/cm", AdaptCm);

INCLUDE_ASM(const s32, "P2/cm", SetCm);

INCLUDE_ASM(const s32, "P2/cm", PsoEnemyStepguard);

INCLUDE_ASM(const s32, "P2/cm", FUN_00145950);

INCLUDE_ASM(const s32, "P2/cm", FUN_00145b68);

INCLUDE_ASM(const s32, "P2/cm", func_00145DD8);

INCLUDE_ASM(const s32, "P2/cm", FUN_00145de8);

INCLUDE_ASM(const s32, "P2/cm", FUN_00145e68);

INCLUDE_ASM(const s32, "P2/cm", FUN_00145fb8);

INCLUDE_ASM(const s32, "P2/cm", LookkPopCm);

INCLUDE_ASM(const s32, "P2/cm", LookkCurCm);

INCLUDE_ASM(const s32, "P2/cm", SetCmSniperFocus);

INCLUDE_ASM(const s32, "P2/cm", FUN_00146028);

INCLUDE_ASM(const s32, "P2/cm", FUN_00146038);

INCLUDE_ASM(const s32, "P2/cm", cm__static_initialization_and_destruction_0);

INCLUDE_ASM(const s32, "P2/cm", _GLOBAL_$I$StartupCm__Fv);
