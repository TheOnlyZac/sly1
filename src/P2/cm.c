/**
 * @todo Mangle all function names in INCLUDE_ASM macros.
 */
#include <cm.h>
#include <util.h>
#include <binoc.h>
#include <clock.h>
#include <light.h>
#include <sw.h>
#include <vis.h>
#include <frm.h>
#include <vifs.h>
#include <memory.h>
#include <math.h>
#include <mat.h>

void SetupCmRotateToCam(CM *pcm);
extern "C" void *memmove(void *pvDst, const void *pvSrc, uint cb);
extern "C" void SetCmLookAt(CM *pcm, VECTOR *peye, VECTOR *pcenter); // signature guessed
extern "C" void SetCmLookAtSmooth(CM *pcm, VECTOR *p1, VECTOR *peye, VECTOR *pcenter, VECTOR *p4, float f0, float f1, float f2, float f3, float f4, float f5); // signature guessed
extern VTCPLCY D_00217398;
extern VTCPLCY D_002173B0;
extern VTCPLCY D_002173C8;
extern VTCPLCY D_002173E0;
extern VTCPLCY D_002173F8;
extern VECTOR D_002618B8;
extern MATRIX3 g_matIdentity;
extern float g_sNearFog;
extern float g_sFarFog;
extern float g_uFogMax;
extern VECTOR g_posEyeDefault;
extern VECTOR g_posCenterDefault;
extern "C" void ConvertCylindToWorldVelocity(VECTOR *pposCenter, VECTOR *ppos, VECTOR *pvel, float s0, float s1, float s2); // signature guessed
extern "C" void ConvertWorldToCylindVelocity(VECTOR *pposCenter, VECTOR *ppos, VECTOR *pvel, float *ps0, float *ps1, float *ps2); // signature guessed

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

void ResetCmAdjust(CM *pcm, SO *psoFocus, CPDEFI *pcpdefi)
{
    CalcCmAdjust(pcm, psoFocus, pcpdefi, &pcm->dposAdjust);
    int d;
    asm("vsub.xyzw $vf1,$vf0,$vf0" : "=r"(d));
    asm("sqc2 $vf1,%0" : "=m"(pcm->vFocus) : "r"(d));
    asm("sqc2 $vf1,%0" : "=m"(pcm->vAdjust) : "r"(d));
    asm("sqc2 $vf1,%0" : "=m"(pcm->dposFocus) : "r"(d));
}

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

void InitCm(CM *pcm)
{
    InitLo(pcm);
    pcm->rMRD = 1.0f;
    pcm->radFOV = 1.0f;
    pcm->radFOV2 = 1.0f;
    STRUCT_OFFSET(pcm, 0x1d0, VECTOR) = D_002618B8; // unnamed field, probably a VECTOR (guess)
    pcm->rAspect = 1.2987013f;
    pcm->sNearClip = 100.0f;
    pcm->sFarClip = 20000.0f;
    pcm->sNearFog = g_sNearFog;
    pcm->sFarFog = g_sFarFog;
    pcm->uFogMax = g_uFogMax;
    pcm->rgbaFog = *(RGBA *)&g_rgbaFog;
    STRUCT_OFFSET(pcm, 0x80, qword) = STRUCT_OFFSET(&g_matIdentity, 0, qword);
    STRUCT_OFFSET(pcm, 0x90, qword) = STRUCT_OFFSET(&g_matIdentity, 0x10, qword);
    STRUCT_OFFSET(pcm, 0xa0, qword) = STRUCT_OFFSET(&g_matIdentity, 0x20, qword);
    RecalcCmFrustrum(pcm);
    pcm->cpman.pvtcplcy = &D_00217398;
    InitCplcy(&pcm->cpman, pcm);
    pcm->cplook.pvtcplcy = &D_002173B0;
    InitCplook(&pcm->cplook, pcm);
    pcm->cpalign.pvtcplcy = &D_002173C8;
    InitCpalign(&pcm->cpalign, pcm);
    pcm->cpaseg.pvtcplcy = &D_002173E0;
    InitCplcy(&pcm->cpaseg, pcm);
    pcm->cptn.pvtcplcy = &D_002173F8;
    InitCplcy(&pcm->cptn, pcm);
    ResetCm(pcm, 1);
}

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

void ResetCm(CM *pcm, int fLookAt)
{
    if (fLookAt)
        SetCmLookAt(pcm, &g_posEyeDefault, &g_posCenterDefault);
    pcm->ccpr = 0;
    SetCpmanCpmt(&pcm->cpman, CPMT_Truck);
    SetCmPolicy(pcm, CPP_Base, &pcm->cpman, 0, 0);
    SetCmCut(pcm, 0);
    pcm->grfzon = 0xFFFFFFF;
    pcm->tJolt = -10.0f;
}

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

void RemoveCmFadeObject(CM *pcm, ALO *palo)
{
    int i;
    for (i = 0; i < pcm->cpaloFade; i++)
    {
        if (palo == pcm->apaloFade[i])
        {
            CopyAb(&pcm->apaloFade[i], &pcm->apaloFade[i + 1], (pcm->cpaloFade - i - 1) * 4);
            pcm->cpaloFade = pcm->cpaloFade - 1;
            return;
        }
    }
}

int FFilterCamera(void *pv, SO *pso)
{
    int f = 0;
    if ((STRUCT_OFFSET(pso, 0x538, ulong) & 0xF00000000) == 0x100000000 || STRUCT_OFFSET(pso, 0x404, int))
        f = 1;
    return f;
}

INCLUDE_ASM("asm/nonmatchings/P2/cm", UpdateCmFade);

INCLUDE_ASM("asm/nonmatchings/P2/cm", UpdateCmLast);

INCLUDE_ASM("asm/nonmatchings/P2/cm", SetupCmRotateToCam__FP2CM);

INCLUDE_ASM("asm/nonmatchings/P2/cm", ConvertCmScreenToWorld);

INCLUDE_ASM("asm/nonmatchings/P2/cm", ConvertCmWorldToScreen);

void SetupCm(CM *pcm)
{
    SetupCmRotateToCam(pcm);
    if (g_psw)
    {
        VECTOR pos;
        *(qword *)&pos = *(qword *)&pcm->pos;
        GRFZON grfzon;
        ClipVismapPointNoHop(g_psw->pvismap, &pos, &grfzon);
        if (grfzon)
            pcm->grfzon = grfzon;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/cm", CombineEyeLookAtProj);

INCLUDE_ASM("asm/nonmatchings/P2/cm", BuildFrustrum);

INCLUDE_ASM("asm/nonmatchings/P2/cm", UpdateCmMat4__FP2CM);

void DrawCm(CM *pcm)
{
    g_vifs.AddDmaCnt();
    g_vifs.AddVifBaseOffset(0, 0);
    g_vifs.AddVifUnpack(UPK_V4_32, 4, &pcm->matWorldToClip, 4);
    g_vifs.AddVifUnpack(UPK_V4_32, 4, &pcm->matClipToWorld, 8);
    g_vifs.EndDmaCnt();
}

void SetCmPosMat(CM *pcm, VECTOR *ppos, MATRIX3 *pmat)
{
    if (ppos)
        *(qword *)&pcm->pos = *(qword *)ppos;
    if (pmat)
    {
        *(qword *)&pcm->mat = *(qword *)pmat;
        STRUCT_OFFSET(pcm, 0x90, qword) = STRUCT_OFFSET(pmat, 0x10, qword);
        STRUCT_OFFSET(pcm, 0xa0, qword) = STRUCT_OFFSET(pmat, 0x20, qword);
    }
    UpdateCmMat4(pcm);
    pcm->swPanMat = pcm->swTiltPos = pcm->sv = pcm->swPanPos = pcm->swTiltMat = 0.0f;
}

void SetCmLookAt(CM *pcm, VECTOR *peye, VECTOR *pcenter)
{
    SetCmLookAtSmooth(pcm, 0, peye, pcenter, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

INCLUDE_ASM("asm/nonmatchings/P2/cm", ConvertWorldToCylindVelocity);

INCLUDE_ASM("asm/nonmatchings/P2/cm", ConvertCylindToWorldVelocity);

void ResetCmLookAtSmooth(CM *pcm, VECTOR *pposCenter)
{
    VECTOR vel;
    ConvertCylindToWorldVelocity(&pcm->posCenterPrev, &pcm->pos, &vel, pcm->swTiltPos, pcm->sv, pcm->swPanMat);
    ConvertWorldToCylindVelocity(pposCenter, &pcm->pos, &vel, &pcm->swTiltPos, &pcm->sv, &pcm->swPanMat);
    *(qword *)&pcm->posCenterPrev = *(qword *)pposCenter;
}

INCLUDE_ASM("asm/nonmatchings/P2/cm", SetCmLookAtSmooth);

void AdjustCmJoy(CM *pcm, JOY *pjoy, JOYID joyid, float *prad)
{
    float rad;
    switch (joyid)
    {
    case JOYID_Left:
        rad = atan2f(-pjoy->x, pjoy->y);
        break;
    case JOYID_Right:
        rad = atan2f(-pjoy->x2, pjoy->y2);
        break;
    default:
        rad = 0.0f;
        break;
    }
    *prad = RadNormalize(rad + atan2f(pcm->mat.avec[0].y, pcm->mat.avec[0].x));
}

JUNK_WORD(0x0000102D);

INCLUDE_ASM("asm/nonmatchings/P2/cm", SetCmPolicy__FP2CM3CPPP5CPLCYP2SOPv);
#ifdef SKIP_ASM
void SetCmPolicy(CM *pcm, CPP cpp, CPLCY *pcplcy, SO *psoFocus, void *pv)
{
    int i = 0;
    while (i < pcm->ccpr && pcm->acpr[i].cpp >= cpp)
        i++;
    memmove(&pcm->acpr[i + 1], &pcm->acpr[i], (pcm->ccpr - i) * sizeof(CPR));
    pcm->acpr[i].cpp = cpp;
    pcm->acpr[i].pcplcy = pcplcy;
    pcm->acpr[i].psoFocus = psoFocus;
    pcm->acpr[i].pv = pv;
    pcm->ccpr++;
    if (pcplcy->pvtcplcy->pfnAdd)
        pcplcy->pvtcplcy->pfnAdd(pcplcy, pv);
    if (i == 0)
    {
        if (pcm->ccpr >= 2)
        {
            CPLCY *pcplcyOld = pcm->acpr[1].pcplcy;
            if (pcplcyOld->pvtcplcy->pfnDeactivate)
                pcplcyOld->pvtcplcy->pfnDeactivate(pcplcyOld, pcm->acpr[1].pv);
        }
        pcm->tActivateCplcy = g_clock.t;
        if (pcplcy->pvtcplcy->pfnActivate)
            pcplcy->pvtcplcy->pfnActivate(pcplcy, pv);
    }
}
#endif

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
