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
#include <bsp.h>
#include <clip.h>
#include <joy.h>
#include <so.h>
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
extern float D_0026194C;
extern JOY g_joyZero;
extern float R_SetCmSpring;
extern float R_SetCmDamping;
extern VECTOR D_00248D30;
void SpringCm(float f0, float f1, float f2, CM *pcm, VECTOR *p0, VECTOR *p1, VECTOR *p2); // signature from symbol
extern "C" void DecomposeSphere(VECTOR *pvecDelta, VECTOR *pposCenter, float *pradPan, float *pradTilt, float *ps); // signature guessed
extern SMP s_smpSquishEye;
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

void GetCmCpdefi(CM *pcm, SO *psoFocus, float dt, CPDEFI *pcpdefi)
{
    if (psoFocus == pcm->psoFocusPrev)
    {
        *pcpdefi = pcm->cpdefiPrev;
    }
    else
    {
        psoFocus->pvtso->pfnGetSoCpdefi(psoFocus, pcpdefi, dt);
        VECTOR vAdj;
        CalcCmAdjust(pcm, psoFocus, pcpdefi, &vAdj);
        // VU0 vector add: posAdjust = posBase + vAdj
        int d1, d2, d3;
        asm("lqc2 $vf2,%1" : "=r"(d1) : "m"(vAdj));
        asm("lqc2 $vf1,%1" : "=r"(d2) : "m"(pcpdefi->posBase), "r"(d1));
        asm("vadd.xyzw $vf1,$vf1,$vf2" : "=r"(d3) : "r"(d2));
        asm("sqc2 $vf1,%0" : "=m"(pcpdefi->posAdjust) : "r"(d3));
    }
}

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

/**
 * @todo Roughly 50 percent matched, float scheduling differs.
 */
INCLUDE_ASM("asm/nonmatchings/P2/cm", RecalcCmFrustrum__FP2CM);
#ifdef SKIP_ASM
void RecalcCmFrustrum(CM *pcm)
{
    float t = tanf(pcm->radFOV * 0.5f);
    float rAspect = pcm->rAspect;
    float inv = 1.0f / pcm->radFOV;
    pcm->yScreenRange = t;
    pcm->xScreenRange = t * rAspect;
    float r = pcm->rMRD * inv;
    pcm->rMRDAdjust = 1.0f > r ? 1.0f : r;
    pcm->sRadiusNearClip = t * sqrtf(rAspect * rAspect + 1.0f) * pcm->sNearClip + 1.0f;
    BuildSimpleProjectionMatrix(640.0f / (pcm->xScreenRange * 4096.0f), 224.0f / (t * 4096.0f), 0.0f, 0.0f, pcm->sNearClip, pcm->sFarClip, &pcm->matProj);
    BuildCmFgfn(pcm, 1.0f, &pcm->fgfn);
    UpdateCmMat4(pcm);
}
#endif

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

/**
 * @todo Nearly there, 28 differing lines of about 130: only registers differ (pcplcy and pcpdefi swapped). Parameter fClear is a guess.
 */
INCLUDE_ASM("asm/nonmatchings/P2/cm", UpdateCmLast__FP2CMif);
#ifdef SKIP_ASM
void UpdateCmLast(CM *pcm, int fClear, float dt)
{
    if (pcm->fCutNext)
    {
        pcm->fCutNext = 0;
        pcm->fCut = 1;
        pcm->fRadCut = 0;
    }
    if (pcm->ccpr > 0)
    {
        CPLCY *pcplcy = pcm->acpr[0].pcplcy;
        CPLCY *pcplcyPrev = 0;
        SO *psoPrev = 0;
        CPDEFI *pcpdefi;
        if (pcplcy)
        {
            do
            {
                SO *pso = pcm->acpr[0].psoFocus;
                pcpdefi = 0;
                if (pso)
                {
                    pcpdefi = &pcm->cpdefiPrev;
                    if (pso != psoPrev)
                    {
                        pso->pvtso->pfnGetSoCpdefi(pso, pcpdefi, dt);
                        if (pcplcyPrev || pso != pcm->psoFocusPrev)
                            ResetCmAdjust(pcm, pso, pcpdefi);
                        AdjustCmCpdefi(pcm, pso, dt, pcpdefi);
                        pcm->psoFocusPrev = pso;
                        psoPrev = pso;
                    }
                }
                if (pcplcy->pvtcplcy->pfnUpdate)
                    pcplcy->pvtcplcy->pfnUpdate(pcplcy, pcpdefi, (g_grfjoyt & 1) ? &g_joy : &g_joyZero, dt);
                pcplcyPrev = pcplcy;
                if (pcm->ccpr <= 0)
                    break;
                pcplcy = pcm->acpr[0].pcplcy;
            } while (pcplcy != pcplcyPrev);
        }
    }
    if (pcm->fCut)
    {
        SetCmFov(pcm, pcm->radFOV2);
    }
    else if (pcm->radFOV != pcm->radFOV2)
    {
        pcm->radFOV = GSmoothA(pcm->radFOV, STRUCT_OFFSET(pcm, 0x1cc, float), pcm->radFOV2, dt, &STRUCT_OFFSET(pcm, 0x1d0, SMPA), &STRUCT_OFFSET(pcm, 0x1cc, float));
        RecalcCmFrustrum(pcm);
    }
    if (fClear)
    {
        pcm->fCut = pcm->fRadCut = 0;
    }
}
#endif

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

/**
 * @todo Structure matches, register assignment differs (out/proj/matB/temp swapped). Mangled name would be CombineEyeLookAtProj__FP6VECTORP7MATRIX3P7MATRIX4T2; rename the symbol when matched.
 */
INCLUDE_ASM("asm/nonmatchings/P2/cm", CombineEyeLookAtProj);
#ifdef SKIP_ASM
void CombineEyeLookAtProj(VECTOR *ppos, MATRIX3 *pmat, MATRIX4 *pmatProj, MATRIX4 *pmatOut)
{
    MATRIX4 matA;
    MATRIX4 matB;
    LoadIdentityMatrix4(&matA);
    for (int i = 0; i < 3; i++)
    {
        matA.aag[0][i] = -pmat->aag[1][i];
        matA.aag[1][i] = -pmat->aag[2][i];
        matA.aag[2][i] = pmat->aag[0][i];
        matA.aag[3][i] = (&ppos->x)[i];
    }
    FInvertMatrix4(&matA, &matB);
    *pmatOut = *pmatProj * matB;
}
#endif

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

/**
 * @todo Close, 13 differing lines of about 100 (loop register allocation and memmove address setup).
 */
INCLUDE_ASM("asm/nonmatchings/P2/cm", SetCmPolicy__FP2CM3CPPP5CPLCYP2SOPv);
#ifdef SKIP_ASM
void SetCmPolicy(CM *pcm, CPP cpp, CPLCY *pcplcy, SO *psoFocus, void *pv)
{
    int i;
    for (i = 0; i < pcm->ccpr; i++)
        if (pcm->acpr[i].cpp < cpp)
            break;
    char *pc = (char *)pcm + (i << 4);
    memmove(pc + 0x3e4, pc + 0x3d4, (pcm->ccpr - i) * 16);
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

void RevokeCmPolicy(CM *pcm, GRFRCP grfrcp, CPP cpp, CPLCY *pcplcy, SO *psoFocus, void *pv)
{
    CPR *pcprDst = pcm->acpr;
    CPR *pcprSrc = pcm->acpr;
    CPLCY *pcplcyTop = 0;
    void *pvTop = 0;
    int i;
    for (i = 0; i < pcm->ccpr; i++, pcprSrc++)
    {
        if ((!(grfrcp & 1) || cpp == pcprSrc->cpp) &&
            ((grfrcp & 2) == 0 || pcplcy == pcprSrc->pcplcy) &&
            ((grfrcp & 4) == 0 || psoFocus == pcprSrc->psoFocus) &&
            ((grfrcp & 8) == 0 || pv == pcprSrc->pv))
        {
            if (i == 0)
            {
                pvTop = pcprSrc->pv;
                pcplcyTop = pcprSrc->pcplcy;
            }
            if (pcprSrc->pcplcy->pvtcplcy->pfnRemove)
                pcprSrc->pcplcy->pvtcplcy->pfnRemove(pcprSrc->pcplcy, pcprSrc->pv);
        }
        else
        {
            *pcprDst = *pcprSrc;
            pcprDst++;
        }
    }
    pcm->ccpr = pcprDst - pcm->acpr;
    if (pcplcyTop)
    {
        if (pcplcyTop->pvtcplcy->pfnDeactivate)
            pcplcyTop->pvtcplcy->pfnDeactivate(pcplcyTop, pvTop);
        if (pcm->ccpr > 0)
        {
            pcm->tActivateCplcy = g_clock.t;
            CPLCY *pcplcyNew = pcm->acpr[0].pcplcy;
            if (pcplcyNew->pvtcplcy->pfnActivate)
                pcplcyNew->pvtcplcy->pfnActivate(pcplcyNew, pcm->acpr[0].pv);
        }
    }
}

/**
 * Hack: the original passes the first vector in a VU register (VU_VECTOR), so it is a qword here,
 * and the VU0 dot product is written with inline asm. Parameter names are guesses.
 */
extern "C" int FInsideCmMrd(CM *pcm, qword vDelta, float sOffset, float sScale, float *puFrac)
{
    float r = pcm->rMRDAdjust;
    int t;
    float dist2;
    float m;
    asm("qmtc2.ni %1,$vf3\n\tvmul.xyz $vf1,$vf3,$vf3\n\tvaddw.x $vf2,$vf0,$vf0w\n\tvadday.x ACC,$vf1,$vf1y\n\tvmaddz.x $vf1,$vf2,$vf1z" : "=r"(t) : "r"(vDelta));
    m = sScale * r;
    asm("qmfc2.ni $2,$vf1\n\tmtc1 $2,%0" : "=f"(dist2) : "r"(t), "f"(m) : "$2");
    float a = m + sOffset;
    float a2 = a * a;
    if (a2 < dist2)
        return 0;
    float b = a - r * 400.0f;
    b = b * b;
    float u;
    if (b < dist2)
        u = (a2 - dist2) / (a2 - b);
    else
        u = 1.0f;
    *puFrac = u;
    return 1;
}

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

/**
 * @todo Four differing lines: the original loads R_SetCmDamping before copying the position and R_SetCmSpring after (argument load order). VU adds are inline asm with fake dependencies. Parameter names are guesses.
 */
INCLUDE_ASM("asm/nonmatchings/P2/cm", SetCm);
#ifdef SKIP_ASM
extern "C" void SetCm(CM *pcm, float fx, float fy, VECTOR *pdpos, VECTOR *ppos)
{
    STRUCT_OFFSET(pcm, 0x40, qword) = *(qword *)ppos;
    SpringCm(R_SetCmSpring, R_SetCmDamping, g_clock.dt, pcm, &pcm->dposCenter, &pcm->vCenter, &D_00248D30);
    VECTOR v;
    int d1, d2, d3;
    asm("lqc2 $vf2,%1" : "=r"(d1) : "m"(pcm->dposCenter));
    asm("lqc2 $vf1,%1" : "=r"(d2) : "m"(*pdpos), "r"(d1));
    asm("vadd.xyzw $vf1,$vf1,$vf2" : "=r"(d3) : "r"(d2));
    asm("sqc2 $vf1,%0" : "=m"(v) : "r"(d3));
    float radPan, radTilt, s;
    DecomposeSphere(&v, ppos, &radPan, &radTilt, &s);
    radPan = radPan + atanf(fx * pcm->xScreenRange);
    radTilt = radTilt - atanf(fy * pcm->yScreenRange);
    LoadRotateMatrixPanTilt(radPan, radTilt, &pcm->mat);
    UpdateCmMat4(pcm);
}
#endif

/**
 * Clips the edge against the BSPs of each object and looks for a gap longer than sMin.
 * Parameter names are guesses, the objects are unidentified (BSP root at 0x538).
 */
extern "C" int FUN_00145810(int cpv, void **apv, VECTOR *ppos1, VECTOR *ppos2, float *pu0, float *pu1, float sMin)
{
    LSG alsg[64];
    int c = 0;
    for (int i = 0; i < cpv; i++)
        c += ClsgClipEdgeToBsp(STRUCT_OFFSET(apv[i], 0x538, BSP *), ppos1, ppos2, 0, 0x40 - c, &alsg[c]);
    c = ClsgMergeAlsg(c, alsg);
    float u0, u1;
    int i;
    for (i = 0; i <= c; i++)
    {
        u0 = (i > 0) ? alsg[i - 1].au[1] : 0.0f;
        u1 = (i < c) ? alsg[i].au[0] : 1.0f;
        if (sMin < u1 - u0)
            break;
    }
    if (i > c)
        return 0;
    if (pu0)
        *pu0 = u0;
    if (pu1)
        *pu1 = u1;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/P2/cm", FUN_00145950);

INCLUDE_ASM("asm/nonmatchings/P2/cm", FUN_00145b68);

int FUN_00145dd8(void *punk, SO *pso)
{
    return STRUCT_OFFSET(pso, 0x538, int) != 0;
}

/**
 * VU0 dot product written with inline asm. The unused second parameter and the names are guesses.
 */
extern "C" float FUN_00145de8(CM *pcm, void *pvUnused, VECTOR *pvecA, void *pb)
{
    float dgNext;
    GSmooth(STRUCT_OFFSET(pb, 0x20, float), pcm->sRadiusNearClip - D_0026194C, g_clock.dtReal, &s_smpSquishEye, &dgNext);
    int t;
    float dg = dgNext;
    asm("lqc2 $vf2,%1\n\tlqc2 $vf1,%2\n\tvmul.xyz $vf2,$vf2,$vf1\n\tvaddw.x $vf3,$vf0,$vf0w\n\tvadday.x ACC,$vf2,$vf2y\n\tvmaddz.x $vf2,$vf3,$vf2z" : "=r"(t) : "m"(*pvecA), "m"(STRUCT_OFFSET(pb, 0x10, VECTOR)));
    int d;
    asm("qmfc2.ni %0,$vf2" : "=r"(d) : "r"(t));
    float dot;
    asm("mtc1 %1,%0" : "=f"(dot) : "r"(d));
    return dot - dg;
}

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
