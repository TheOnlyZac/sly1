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
#include <mark.h>
#include <jt.h>
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

/**
 * Spring step: pos += (target - pos) * k + vel * damp, scaled by dt (roughly). Written with VU0 inline asm
 * (fake data dependencies keep the scheduling). The VU spill stores are artifacts of the original code.
 * Parameter names are guesses.
 */
void SpringCm(float k, float damp, float dt, CM *pcm, VECTOR *ppos, VECTOR *pvel, VECTOR *ptarget)
{
    if (pcm->fCut)
    {
        STRUCT_OFFSET(ppos, 0, qword) = STRUCT_OFFSET(ptarget, 0, qword);
        int d;
        asm("vsub.xyzw $vf1,$vf0,$vf0" : "=r"(d));
        asm("sqc2 $vf1,%0" : "=m"(*pvel) : "r"(d));
        return;
    }
    VECTOR s0, s1, s2;
    int a1, a2, a3, a4, a5, b5, a6, b6, c6, d6, e6, a7, b7, c7;
    asm("mfc1 $2,%1\n\tqmtc2.ni $2,$vf5" : "=r"(a1) : "f"(k) : "$2");
    asm("lqc2 $vf1,%1" : "=r"(a2) : "m"(*ppos), "r"(a1));
    asm("mfc1 $2,%1\n\tlqc2 $vf4,%2\n\tqmtc2.ni $2,$vf6" : "=r"(a3) : "f"(damp), "m"(*ptarget), "r"(a2) : "$2");
    asm("lqc2 $vf2,%1\n\tvsub.xyzw $vf4,$vf4,$vf1" : "=r"(a4) : "m"(*pvel), "r"(a3));
    asm("mfc1 $2,%1\n\tvmulax.xyzw ACC,$vf4,$vf5x\n\tvmaddx.xyzw $vf7,$vf2,$vf6x\n\tqmtc2.ni $2,$vf3" : "=r"(a5) : "f"(dt), "r"(a4) : "$2");
    asm("sqc2 $vf5,%1" : "=r"(b5), "=m"(s2) : "r"(a5));
    asm("vadda.xyzw ACC,$vf2,$vf0\n\tvmaddx.xyzw $vf2,$vf7,$vf3x" : "=r"(a6) : "r"(b5));
    asm("sqc2 $vf6,%1" : "=r"(b6), "=m"(s2) : "r"(a6));
    asm("sqc2 $vf2,%1" : "=r"(c6), "=m"(*pvel) : "r"(b6));
    asm("sqc2 $vf3,%1" : "=r"(d6), "=m"(s2) : "r"(c6));
    asm("sqc2 $vf4,%1" : "=r"(e6), "=m"(s0) : "r"(d6));
    asm("lqc2 $vf1,%1\n\tvadda.xyzw ACC,$vf1,$vf0\n\tvmaddx.xyzw $vf1,$vf2,$vf3x" : "=r"(a7) : "m"(*ppos), "r"(e6));
    asm("sqc2 $vf7,%1" : "=r"(b7), "=m"(s1) : "r"(a7));
    asm("sqc2 $vf1,%1" : "=r"(c7), "=m"(*ppos) : "r"(b7));
}

/**
 * @todo Structure matches but 76 differing lines: the original fills branch delay slots with the VU load (lqc2 vf2) and keeps the constants in other float registers. Switch cases and constants are from the asm; names are guesses.
 */
INCLUDE_ASM("asm/nonmatchings/P2/cm", AdjustCmCpdefi__FP2CMP2SOfP6CPDEFI);
#ifdef SKIP_ASM
void AdjustCmCpdefi(CM *pcm, SO *psoFocus, float dt, CPDEFI *pcpdefi)
{
    VECTOR v;
    CalcCmAdjust(pcm, psoFocus, pcpdefi, &v);
    if (psoFocus == g_pjt)
    {
        switch (STRUCT_OFFSET(psoFocus, 0x268C, int))
        {
        case 0:
            SpringCm(5.0f, -3.5f, dt, pcm, &pcm->dposAdjust, &pcm->vAdjust, &v);
            SpringCm(5.0f, -3.5f, dt, pcm, &pcm->dposFocus, &pcm->vFocus, &D_00248D30);
            break;
        case 1:
            SpringCm(1.0f, -10.0f, dt, pcm, &pcm->dposAdjust, &pcm->vAdjust, &v);
            SpringCm(0.0f, -10.0f, dt, pcm, &pcm->dposFocus, &pcm->vFocus, &pcm->dposFocus);
            break;
        case 2:
            SpringCm(5.0f, -3.5f, dt, pcm, &pcm->dposAdjust, &pcm->vAdjust, &v);
            break;
        }
    }
    else
    {
        SpringCm(5.0f, -3.5f, dt, pcm, &pcm->dposAdjust, &pcm->vAdjust, &v);
        SpringCm(5.0f, -3.5f, dt, pcm, &pcm->dposFocus, &pcm->vFocus, &D_00248D30);
    }
    int d1, d2, d3;
    asm("lqc2 $vf2,%1" : "=r"(d1) : "m"(pcm->dposAdjust));
    asm("lqc2 $vf1,%1" : "=r"(d2) : "m"(pcpdefi->posBase), "r"(d1));
    asm("vadd.xyzw $vf1,$vf1,$vf2" : "=r"(d3) : "r"(d2));
    asm("sqc2 $vf1,%0" : "=m"(pcpdefi->posAdjust) : "r"(d3));
}
#endif

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

/**
 * @todo Structure matches, 36 differing lines of about 72 (register allocation of the qwords and placement of the junk spill stores). VU0 inline asm, vector built with pextlw/pcpyld asm. Computes matRotateToCam and matRotateTiltToCam; names are guesses.
 */
INCLUDE_ASM("asm/nonmatchings/P2/cm", SetupCmRotateToCam__FP2CM);
#ifdef SKIP_ASM
extern VECTOR g_normalX;
extern VECTOR g_normalZ;
void SetupCmRotateToCam(CM *pcm)
{
    MATRIX3 loc;
    VECTOR v30;
    VECTOR &vNorm = loc.avec[0];
    float x = -pcm->mat.avec[0].x;
    float y = -pcm->mat.avec[0].y;
    float z = 0.0f;
    register qword q __asm__("$2");
    asm("mfc1 $2,%1\n\tmfc1 $3,%2\n\tpextlw $2,$3,$2" : "=r"(q) : "f"(x), "f"(y) : "$3");
    asm("mfc1 $3,%1\n\tpcpyld $2,$3,$2" : "+r"(q) : "f"(z) : "$3");
    qword n = STRUCT_OFFSET(&g_normalX, 0, qword);
    int a1, a2, a3, a4, a5, a6, a7, t;
    float len;
    STRUCT_OFFSET(&v30, 0, qword) = q;
    asm("qmtc2.ni %1,$vf1" : "=r"(a1) : "r"(q));
    asm("vmul.xyz $vf2,$vf1,$vf1\n\tvaddw.x $vf3,$vf0,$vf0w\n\tvadday.x ACC,$vf2,$vf2y\n\tvmaddz.x $vf2,$vf3,$vf2z" : "=r"(a2) : "r"(a1));
    asm("sqc2 $vf1,%1" : "=r"(a3), "=m"(loc.avec[0]) : "r"(a2));
    asm(".word 0x4A0203BD\n\tvwaitq\n\tvaddq.x $vf1,$vf0,Q" : "=r"(a4) : "r"(a3));
    asm("qmfc2.ni %0,$vf1" : "=r"(t) : "r"(a4));
    asm("mtc1 %1,%0" : "=f"(len) : "r"(t));
    asm("qmtc2.ni %1,$vf2" : "=r"(a5) : "r"(q));
    if (len < 0.0001f)
    {
        asm volatile("qmtc2.ni %1,$vf1" : "=r"(a6) : "r"(n), "r"(a5));
    }
    else
    {
        asm volatile("vdiv Q,$vf0w,$vf1x\n\tvwaitq\n\tvmulq.xyzw $vf1,$vf2,Q" : "=r"(a6) : "r"(a5));
    }
    asm volatile("sqc2 $vf1,%0" : "=m"(vNorm) : "r"(a6));
    float m1 = -1.0f;
    int b1, b2, b3, b4, b5, b6, b7, b8, b9;
    asm("lqc2 $vf1,%1" : "=r"(b1) : "m"(pcm->mat.avec[0]));
    asm("lqc2 $vf4,%1" : "=r"(b2) : "m"(g_normalZ), "r"(b1));
    asm("lqc2 $vf5,%1" : "=r"(b3) : "m"(vNorm), "r"(b2));
    asm("qmtc2.ni %1,$vf3" : "=r"(b4) : "r"(m1), "r"(b3));
    STRUCT_OFFSET(pcm, 0x3c0, qword) = STRUCT_OFFSET(pcm, 0xa0, qword);
    asm("vopmula.xyz ACC,$vf4,$vf5\n\tvopmsub.xyz $vf6,$vf5,$vf4\n\tvsub.w $vf6,$vf6,$vf6" : "=r"(b5) : "r"(b4));
    asm("lqc2 $vf2,%1" : "=r"(b6) : "m"(pcm->mat.avec[1]), "r"(b5));
    asm("vmulx.xyzw $vf1,$vf1,$vf3x" : "=r"(b7) : "r"(b6));
    asm("sqc2 $vf6,%1" : "=r"(b8), "=m"(loc.avec[1]) : "r"(b7));
    asm("vmulx.xyzw $vf2,$vf2,$vf3x" : "=r"(b9) : "r"(b8));
    asm("sqc2 $vf4,%1" : "=r"(a7), "=m"(loc.avec[2]) : "r"(b9));
    asm("sqc2 $vf3,%1" : "=r"(a1), "=m"(v30) : "r"(a7));
    asm("sqc2 $vf5,%1" : "=r"(a2), "=m"(pcm->matRotateToCam.avec[0]) : "r"(a1));
    asm("sqc2 $vf6,%1" : "=r"(a3), "=m"(pcm->matRotateToCam.avec[1]) : "r"(a2));
    asm("sqc2 $vf4,%1" : "=r"(a4), "=m"(pcm->matRotateToCam.avec[2]) : "r"(a3));
    asm("sqc2 $vf1,%1" : "=r"(a5), "=m"(pcm->matRotateTiltToCam.avec[0]) : "r"(a4));
    asm("sqc2 $vf2,%1" : "=r"(a6), "=m"(pcm->matRotateTiltToCam.avec[1]) : "r"(a5));
    asm("sqc2 $vf1,%1" : "=r"(a7), "=m"(loc.avec[0]) : "r"(a6));
    asm("sqc2 $vf3,%1" : "=r"(b1), "=m"(v30) : "r"(a7));
    asm("sqc2 $vf2,%1" : "=r"(b2), "=m"(loc.avec[1]) : "r"(b1));
    STRUCT_OFFSET(&loc.avec[2], 0, qword) = STRUCT_OFFSET(pcm, 0xa0, qword);
}
#endif

/**
 * @todo 17 differing lines: the original interleaves the VU loads with the float math, which inline asm cannot reproduce. Names are guesses.
 */
INCLUDE_ASM("asm/nonmatchings/P2/cm", ConvertCmScreenToWorld);
#ifdef SKIP_ASM
extern "C" void ConvertCmScreenToWorld(CM *pcm, VECTOR *pscreen, VECTOR *pworld)
{
    VECTOR v;
    float z = pscreen->z;
    v.x = z;
    v.y = -pscreen->x;
    v.z = pscreen->y;
    if (0.0001f < z)
    {
        v.z = pscreen->y * z;
        v.y = v.y * z;
    }
    v.y = v.y * pcm->xScreenRange;
    v.z = v.z * pcm->yScreenRange;
    asm("lqc2 $vf5,%1\n\tlqc2 $vf4,%2\n\tlqc2 $vf3,%3\n\tlqc2 $vf2,%4\n\tlqc2 $vf1,%5\n\tvmulax.xyz ACC,$vf5,$vf1x\n\tvmadday.xyz ACC,$vf2,$vf1y\n\tvmaddz.xyz $vf1,$vf3,$vf1z\n\tvadd.xyzw $vf1,$vf1,$vf4\n\tsqc2 $vf1,%0" : "=m"(*pworld) : "m"(pcm->mat.avec[0]), "m"(pcm->pos), "m"(pcm->mat.avec[2]), "m"(pcm->mat.avec[1]), "m"(v));
}
#endif

/**
 * VU0 matrix transform written with inline asm (fake data dependencies keep the scheduling).
 * Parameter names are guesses.
 */
extern "C" void ConvertCmWorldToScreen(CM *pcm, VECTOR *pworld, VECTOR *pscreen)
{
    VECTOR vt;
    int d, e;
    MATRIX3 *pmat = &pcm->mat;
    asm("lqc2 $vf1,%1" : "=r"(e) : "m"(pcm->pos));
    asm("lqc2 $vf3,%2" : "=r"(d) : "m"(pcm->pos), "m"(*pworld), "r"(e));
    asm("vsub.xyzw $vf3,$vf3,$vf1\n\tlqc2 $vf4,0x20(%5)\n\tlqc2 $vf2,0x10(%5)\n\tlqc2 $vf1,%3\n\tvmul.xyzw $vf8,$vf1,$vf3\n\tvmaxw.xyzw $vf9,$vf0,$vf0w\n\tvmul.xyzw $vf7,$vf2,$vf3\n\tvmul.xyzw $vf6,$vf4,$vf3\n\tvadday.x ACC,$vf8,$vf8y\n\tvmaddz.x $vf5,$vf9,$vf8z\n\tvaddax.y ACC,$vf7,$vf7x\n\tvmaddz.y $vf5,$vf9,$vf7z\n\tvaddax.z ACC,$vf6,$vf6x\n\tvmaddy.z $vf5,$vf9,$vf6y" : "=r"(e) : "m"(pcm->pos), "m"(*pworld), "m"(pmat->avec[0]), "m"(pmat->avec[1]), "r"(pmat), "r"(d));
    asm("sqc2 $vf5,%0" : "=m"(vt) : "r"(e));
    pscreen->z = vt.x;
    pscreen->y = vt.z;
    pscreen->x = -vt.y;
    pscreen->x = pscreen->x / pcm->xScreenRange;
    pscreen->y = pscreen->y / pcm->yScreenRange;
    if (0.0001f < vt.x)
    {
        pscreen->x = pscreen->x / vt.x;
        pscreen->y = pscreen->y / vt.x;
    }
}

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

/**
 * Builds the four frustum plane normals from the camera matrix and the screen ranges.
 * VU0 inline asm: the chain of fake register dependencies keeps the scheduling, the volatile asms and the
 * split mfc1 asm place the float moves like the original (the assembler accepts vsqrt, no .word needed).
 * Parameter names are guesses.
 */
extern "C" void BuildFrustrum(MATRIX3 *pmat, VECTOR *anormal, float xScale, float yScale)
{
    VECTOR spill;
    register int ch __asm__("$7");
    asm("lqc2 $vf2,%1\n\tqmtc2.ni %3,$vf5\n\tlqc2 $vf1,%2" : "=r"(ch) : "m"(pmat->avec[1]), "m"(pmat->avec[0]), "r"(xScale));
    xScale = -xScale;
    asm volatile("vadda.xyzw ACC,$vf1,$vf0\n\tvmaddx.xyzw $vf1,$vf2,$vf5x" : "=r"(ch) : "r"(ch));
    asm("lqc2 $vf3,%1" : "=r"(ch) : "m"(pmat->avec[2]), "r"(ch));
    asm("vmul.xyz $vf2,$vf1,$vf1\n\tvaddw.x $vf4,$vf0,$vf0w\n\tvadday.x ACC,$vf2,$vf2y\n\tvmaddz.x $vf2,$vf4,$vf2z" : "=r"(ch) : "r"(ch));
    asm("sqc2 $vf5,%1" : "=r"(ch), "=m"(spill) : "r"(ch));
    asm volatile("vsqrt Q,$vf2x\n\tvwaitq\n\tvaddq.x $vf2,$vf0,Q" : "=r"(ch) : "r"(ch));
    asm("vdiv Q,$vf0w,$vf2x\n\tvwaitq\n\tvmulq.xyzw $vf2,$vf1,Q\n\tqmtc2.ni %1,$vf4" : "=r"(ch) : "r"(xScale), "r"(ch));
    asm("vopmula.xyz ACC,$vf3,$vf2\n\tvopmsub.xyz $vf3,$vf2,$vf3\n\tvsub.w $vf3,$vf3,$vf3" : "=r"(ch) : "r"(ch));
    int yb;
    asm("mfc1 %0,%1" : "=r"(yb) : "f"(yScale), "r"(ch));
    asm("sqc2 $vf3,%1" : "=r"(ch), "=m"(anormal[0]) : "r"(ch));
    yScale = -yScale;
    asm("qmtc2.ni %1,$vf6" : "=r"(ch) : "r"(yb), "r"(ch));
    asm("lqc2 $vf1,%1" : "=r"(ch) : "m"(pmat->avec[1]), "r"(ch));
    asm("lqc2 $vf2,%1" : "=r"(ch) : "m"(pmat->avec[0]), "r"(ch));
    asm("vadda.xyzw ACC,$vf2,$vf0\n\tvmaddx.xyzw $vf2,$vf1,$vf4x" : "=r"(ch) : "r"(ch));
    asm("lqc2 $vf3,%1" : "=r"(ch) : "m"(pmat->avec[2]), "r"(ch));
    asm volatile("vmul.xyz $vf1,$vf2,$vf2\n\tvaddw.x $vf5,$vf0,$vf0w\n\tvadday.x ACC,$vf1,$vf1y\n\tvmaddz.x $vf1,$vf5,$vf1z" : "=r"(ch) : "r"(ch));
    asm("sqc2 $vf4,%1" : "=r"(ch), "=m"(spill) : "r"(ch));
    asm("vsqrt Q,$vf1x\n\tvwaitq\n\tvaddq.x $vf1,$vf0,Q\n\tsqc2 $vf6,%2\n\tqmtc2.ni %1,$vf7" : "=r"(ch) : "r"(yScale), "m"(spill), "r"(ch));
    asm("vdiv Q,$vf0w,$vf1x\n\tvwaitq\n\tvmulq.xyzw $vf1,$vf2,Q" : "=r"(ch) : "r"(ch));
    asm("sqc2 $vf7,%1" : "=r"(ch), "=m"(spill) : "r"(ch));
    asm("vopmula.xyz ACC,$vf1,$vf3\n\tvopmsub.xyz $vf1,$vf3,$vf1\n\tvsub.w $vf1,$vf1,$vf1" : "=r"(ch) : "r"(ch));
    asm("sqc2 $vf1,%1" : "=r"(ch), "=m"(anormal[1]) : "r"(ch));
    asm("lqc2 $vf1,%1" : "=r"(ch) : "m"(pmat->avec[2]), "r"(ch));
    asm("lqc2 $vf2,%1" : "=r"(ch) : "m"(pmat->avec[0]), "r"(ch));
    asm("vadda.xyzw ACC,$vf2,$vf0\n\tvmaddx.xyzw $vf2,$vf1,$vf6x" : "=r"(ch) : "r"(ch));
    asm("lqc2 $vf3,%1" : "=r"(ch) : "m"(pmat->avec[1]), "r"(ch));
    asm("vmul.xyz $vf1,$vf2,$vf2\n\tvaddw.x $vf4,$vf0,$vf0w\n\tvadday.x ACC,$vf1,$vf1y\n\tvmaddz.x $vf1,$vf4,$vf1z\n\tvsqrt Q,$vf1x\n\tvwaitq\n\tvaddq.x $vf1,$vf0,Q" : "=r"(ch) : "r"(ch));
    asm("vdiv Q,$vf0w,$vf1x\n\tvwaitq\n\tvmulq.xyzw $vf1,$vf2,Q\n\tvopmula.xyz ACC,$vf1,$vf3\n\tvopmsub.xyz $vf1,$vf3,$vf1\n\tvsub.w $vf1,$vf1,$vf1" : "=r"(ch) : "r"(ch));
    asm("sqc2 $vf1,%1" : "=r"(ch), "=m"(anormal[2]) : "r"(ch));
    asm("lqc2 $vf1,%1" : "=r"(ch) : "m"(pmat->avec[2]), "r"(ch));
    asm("lqc2 $vf2,%1" : "=r"(ch) : "m"(pmat->avec[0]), "r"(ch));
    asm("vadda.xyzw ACC,$vf2,$vf0\n\tvmaddx.xyzw $vf2,$vf1,$vf7x" : "=r"(ch) : "r"(ch));
    asm("lqc2 $vf3,%1" : "=r"(ch) : "m"(pmat->avec[1]), "r"(ch));
    asm("vmul.xyz $vf1,$vf2,$vf2\n\tvaddw.x $vf4,$vf0,$vf0w\n\tvadday.x ACC,$vf1,$vf1y\n\tvmaddz.x $vf1,$vf4,$vf1z\n\tvsqrt Q,$vf1x\n\tvwaitq\n\tvaddq.x $vf1,$vf0,Q" : "=r"(ch) : "r"(ch));
    asm("vdiv Q,$vf0w,$vf1x\n\tvwaitq\n\tvmulq.xyzw $vf1,$vf2,Q\n\tvopmula.xyz ACC,$vf3,$vf1\n\tvopmsub.xyz $vf3,$vf1,$vf3\n\tvsub.w $vf3,$vf3,$vf3" : "=r"(ch) : "r"(ch));
    asm("sqc2 $vf3,%0" : "=m"(anormal[3]) : "r"(ch));
}

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

/**
 * @todo Structure matches, 16 differing lines of about 74 (branch delay slot fill: the original puts lqc2 vf4 and sqc2 vf5 in the delay slots and hoists the 1e-4 constant after vmaddz). VU0 inline asm, names guessed.
 */
INCLUDE_ASM("asm/nonmatchings/P2/cm", ConvertWorldToCylindVelocity);
#ifdef SKIP_ASM
extern "C" void ConvertWorldToCylindVelocity(VECTOR *pposCenter, VECTOR *ppos, VECTOR *pvel, float *ps0, float *ps1, float *ps2)
{
    MATRIX3 mat;
    VECTOR d;
    VECTOR r;
    int a1, a2, a3, a4, a5, a6, t;
    float len;
    asm("lqc2 $vf2,%1" : "=r"(a1) : "m"(*pposCenter));
    asm("lqc2 $vf1,%1" : "=r"(a2) : "m"(*ppos), "r"(a1));
    asm("vsub.xyzw $vf1,$vf1,$vf2" : "=r"(a3) : "r"(a2));
    asm("sqc2 $vf1,%0" : "=m"(d) : "r"(a3));
    LoadLookAtMatrix(&d, &mat);
    asm("lqc2 $vf1,%1" : "=r"(a4) : "m"(d));
    asm("vmul.xyz $vf1,$vf1,$vf1\n\tvaddw.x $vf2,$vf0,$vf0w\n\tvadday.x ACC,$vf1,$vf1y\n\tvmaddz.x $vf1,$vf2,$vf1z" : "=r"(a5) : "r"(a4));
    asm(".word 0x4A0103BD\n\tvwaitq\n\tvaddq.x $vf1,$vf0,Q" : "=r"(a6) : "r"(a5));
    asm("qmfc2.ni %0,$vf1" : "=r"(t) : "r"(a6));
    asm("mtc1 %1,%0" : "=f"(len) : "r"(t));
    if (len < 0.0001f)
    {
        *ps2 = *ps0 = *ps1 = 0.0f;
    }
    else
    {
        int b1, b2, b3, b4, b5, b6, b7, b8, b9;
        asm("lqc2 $vf4,%1" : "=r"(b1) : "m"(*pvel));
        asm("lqc2 $vf3,%1" : "=r"(b2) : "m"(mat.avec[0]), "r"(b1));
        asm("lqc2 $vf2,%1" : "=r"(b3) : "m"(mat.avec[1]), "r"(b2));
        asm("lqc2 $vf1,%1" : "=r"(b4) : "m"(mat.avec[2]), "r"(b3));
        asm("vmul.xyzw $vf8,$vf3,$vf4\n\tvmaxw.xyzw $vf9,$vf0,$vf0w\n\tvmul.xyzw $vf7,$vf2,$vf4\n\tvmul.xyzw $vf6,$vf1,$vf4\n\tvadday.x ACC,$vf8,$vf8y\n\tvmaddz.x $vf5,$vf9,$vf8z\n\tvaddax.y ACC,$vf7,$vf7x\n\tvmaddz.y $vf5,$vf9,$vf7z\n\tvaddax.z ACC,$vf6,$vf6x\n\tvmaddy.z $vf5,$vf9,$vf6y" : "=r"(b5) : "r"(b4));
        asm("sqc2 $vf5,%1" : "=r"(b6), "=m"(r) : "r"(b5));
        if (len < 100.0f)
            len = 100.0f;
        float rx = r.x, ry = r.y, rz = r.z;
        *ps2 = rx;
        *ps0 = ry / len;
        *ps1 = rz / len;
    }
}
#endif

/**
 * @todo Structure matches, 14 differing lines of about 52 (scheduling of compiler epilogue loads and spill stores around the VU asm). The VU vector is built with pextlw/pcpyld inline asm because no C source form was found that emits them. Names guessed.
 */
INCLUDE_ASM("asm/nonmatchings/P2/cm", ConvertCylindToWorldVelocity);
#ifdef SKIP_ASM
extern "C" void ConvertCylindToWorldVelocity(VECTOR *pposCenter, VECTOR *ppos, VECTOR *pvel, float s0, float s1, float s2)
{
    MATRIX3 mat;
    VECTOR d;
    int a1, a2, a3, a4, a5, a6, a7, a8;
    asm("lqc2 $vf2,%1" : "=r"(a1) : "m"(*pposCenter));
    asm("lqc2 $vf1,%1" : "=r"(a2) : "m"(*ppos), "r"(a1));
    asm("vsub.xyzw $vf1,$vf1,$vf2" : "=r"(a3) : "r"(a2));
    asm("sqc2 $vf1,%0" : "=m"(d) : "r"(a3));
    LoadLookAtMatrix(&d, &mat);
    int t;
    float len;
    asm("lqc2 $vf1,%1" : "=r"(a4) : "m"(d));
    asm("vmul.xyz $vf1,$vf1,$vf1\n\tvaddw.x $vf3,$vf0,$vf0w\n\tvadday.x ACC,$vf1,$vf1y\n\tvmaddz.x $vf1,$vf3,$vf1z" : "=r"(a5) : "r"(a4));
    asm("lqc2 $vf2,%1" : "=r"(a6) : "m"(mat.avec[0]), "r"(a5));
    asm(".word 0x4A0103BD\n\tvwaitq\n\tvaddq.x $vf1,$vf0,Q" : "=r"(a7) : "r"(a6));
    asm("lqc2 $vf4,%1" : "=r"(a8) : "m"(mat.avec[1]), "r"(a7));
    asm("qmfc2.ni %0,$vf1" : "=r"(t) : "r"(a8));
    asm("mtc1 %1,%0" : "=f"(len) : "r"(t));
    float v0 = len * s0;
    float v1 = len * s1;
    register qword q __asm__("$2");
    asm volatile("mfc1 $2,%1\n\tmfc1 $3,%2\n\tpextlw $2,$3,$2" : "=r"(q) : "f"(s2), "f"(v0) : "$3");
    asm("mfc1 $3,%1\n\tpcpyld $2,$3,$2" : "+r"(q) : "f"(v1) : "$3");
    VECTOR s1v, s2v;
    STRUCT_OFFSET(&s1v, 0, qword) = q;
    STRUCT_OFFSET(&s2v, 0, qword) = q;
    int b1, b2;
    asm("lqc2 $vf3,%1\n\tqmtc2.ni %2,$vf1" : "=r"(b1) : "m"(mat.avec[2]), "r"(q));
    asm("vmulax.xyz ACC,$vf2,$vf1x\n\tvmadday.xyz ACC,$vf4,$vf1y\n\tvmaddz.xyz $vf2,$vf3,$vf1z" : "=r"(b2) : "r"(b1));
    asm("sqc2 $vf2,%0" : "=m"(*pvel) : "r"(b2));
}
#endif

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

/**
 * VU0 vector math written with inline asm (fake data dependencies keep the scheduling).
 * Parameter names are guesses. psXY receives the XY length, pz the Z component.
 */
extern "C" void DecomposeCylind(VECTOR *ptarget, VECTOR *pcenter, float *pradPan, float *psXY, float *pz)
{
    VECTOR d;
    if (pcenter)
    {
        int a, b, c;
        asm("lqc2 $vf1,%1" : "=r"(a) : "m"(*ptarget));
        asm("lqc2 $vf2,%1" : "=r"(b) : "m"(*pcenter), "r"(a));
        asm("vsub.xyzw $vf1,$vf1,$vf2" : "=r"(c) : "r"(b));
        asm("sqc2 $vf1,%0" : "=m"(d) : "r"(c));
    }
    else
    {
        STRUCT_OFFSET(&d, 0, qword) = STRUCT_OFFSET(ptarget, 0, qword);
    }
    if (pradPan)
        *pradPan = RadNormalize(atan2f(d.y, d.x));
    int a0;
    asm("lqc2 $vf1,%1" : "=r"(a0) : "m"(d));
    if (psXY)
    {
        int a, t;
        asm("vmul.xy $vf1,$vf1,$vf1\n\tvaddy.x $vf1,$vf1,$vf1y\n\t.word 0x4A0103BD\n\tvwaitq\n\tvaddq.x $vf1,$vf0,Q" : "=r"(a) : "r"(a0));
        asm("qmfc2.ni %0,$vf1" : "=r"(t) : "r"(a));
        *(int *)psXY = t;
    }
    if (pz)
        *pz = d.z;
}

/**
 * VU0 vector math written with inline asm (fake data dependencies keep the scheduling).
 * The empty asm at the end only stops gcc from filling the last branch delay slot, so the
 * assembler puts the VU load there like the original. Parameter names are guesses.
 */
extern "C" void DecomposeSphere(VECTOR *ptarget, VECTOR *pcenter, float *pradPan, float *pradTilt, float *ps)
{
    VECTOR d;
    if (pcenter)
    {
        int a, b, c;
        asm("lqc2 $vf1,%1" : "=r"(a) : "m"(*ptarget));
        asm("lqc2 $vf2,%1" : "=r"(b) : "m"(*pcenter), "r"(a));
        asm("vsub.xyzw $vf1,$vf1,$vf2" : "=r"(c) : "r"(b));
        asm("sqc2 $vf1,%0" : "=m"(d) : "r"(c));
    }
    else
    {
        STRUCT_OFFSET(&d, 0, qword) = STRUCT_OFFSET(ptarget, 0, qword);
    }
    if (pradPan)
        *pradPan = RadNormalize(atan2f(d.y, d.x));
    int a0;
    asm("lqc2 $vf1,%1" : "=r"(a0) : "m"(d));
    if (pradTilt)
    {
        int a, t, a2;
        float dxy;
        asm("vmul.xy $vf1,$vf1,$vf1\n\tvaddy.x $vf1,$vf1,$vf1y" : "=r"(a2) : "r"(a0));
        float dz = d.z;
        asm(".word 0x4A0103BD\n\tvwaitq\n\tvaddq.x $vf1,$vf0,Q" : "=r"(a) : "r"(a2));
        asm("qmfc2.ni %0,$vf1" : "=r"(t) : "r"(a));
        asm("mtc1 %1,%0" : "=f"(dxy) : "r"(t));
        *pradTilt = RadNormalize(atan2f(dz, dxy));
    }
    int a1;
    asm("lqc2 $vf1,%1" : "=r"(a1) : "m"(d));
    if (ps)
    {
        int a, t;
        asm("vmul.xyz $vf1,$vf1,$vf1\n\tvaddw.x $vf2,$vf0,$vf0w\n\tvadday.x ACC,$vf1,$vf1y\n\tvmaddz.x $vf1,$vf2,$vf1z\n\t.word 0x4A0103BD\n\tvwaitq\n\tvaddq.x $vf1,$vf0,Q" : "=r"(a) : "r"(a1));
        asm("qmfc2.ni %0,$vf1" : "=r"(t) : "r"(a));
        *(int *)ps = t;
    }
    asm("");
}

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

/**
 * @todo 26 differing lines of about 70, only instruction scheduling and a register choice differ. VU0 math as inline asm with fake dependencies, names are guesses. Mangled name would be AdaptCm__FP2CMP6VECTORff, rename the symbol when matched.
 */
INCLUDE_ASM("asm/nonmatchings/P2/cm", AdaptCm);
#ifdef SKIP_ASM
void AdaptCm(CM *pcm, VECTOR *pposFocus, float fx, float fy)
{
    VECTOR dir, p2, vt;
    MATRIX3 *pmat = &pcm->mat;
    float s1, s2;
    int a1, a2, a3, a4, a5, a6, b6, c6, d6, e6, a7, a8, a9, b9, c9, d9, a10, b10, a11;
    float x = -fx * pcm->xScreenRange;
    float y = fy * pcm->yScreenRange;
    STRUCT_OFFSET(pcm, 0x240, qword) = STRUCT_OFFSET(&D_00248D30, 0, qword);
    dir.x = 1.0f;
    dir.y = x;
    dir.z = y;
    asm("lqc2 $vf5,%1" : "=r"(a1) : "m"(pcm->mat.avec[0]), "m"(dir));
    asm("lqc2 $vf4,0x20(%1)" : "=r"(a2) : "r"(pmat), "r"(a1));
    asm("lqc2 $vf1,0x10(%1)" : "=r"(a3) : "r"(pmat), "r"(a2));
    asm("lqc2 $vf2,%1\n\tvmulax.xyz ACC,$vf5,$vf2x\n\tvmadday.xyz ACC,$vf1,$vf2y\n\tvmaddz.xyz $vf2,$vf4,$vf2z" : "=r"(a4) : "m"(dir), "r"(a3));
    asm("mfc1 $2,%1\n\tqmtc2.ni $2,$vf3" : "=r"(a5) : "f"(100.0f), "r"(a4) : "$2");
    asm("lqc2 $vf1,%1\n\tvadda.xyzw ACC,$vf1,$vf0\n\tvmaddx.xyzw $vf1,$vf2,$vf3x" : "=r"(a6) : "m"(pcm->pos), "r"(a5));
    asm("sqc2 $vf3,%1" : "=r"(b6), "=m"(vt) : "r"(a6));
    asm("sqc2 $vf1,%1" : "=r"(c6), "=m"(p2) : "r"(b6));
    FindClosestPointOnLine(pposFocus, &pcm->pos, &p2, &s1, &s2);
    float t = 1.0f - s1;
    asm("lqc2 $vf1,%1" : "=r"(a7) : "m"(*pposFocus), "f"(s1));
    asm("lqc2 $vf2,%1" : "=r"(a8) : "m"(pcm->pos), "r"(a7));
    asm("mfc1 $2,%1\n\tqmtc2.ni $2,$vf5" : "=r"(a9) : "f"(s1), "r"(a8) : "$2");
    asm("lqc2 $vf4,%1" : "=r"(b9) : "m"(p2), "r"(a9));
    asm("mfc1 $2,%1\n\tqmtc2.ni $2,$vf3" : "=r"(c9) : "f"(t), "r"(b9) : "$2");
    asm("vmulax.xyzw ACC,$vf2,$vf3x\n\tvmaddx.xyzw $vf2,$vf4,$vf5x" : "=r"(d9) : "r"(c9));
    asm("sqc2 $vf3,%1" : "=r"(a10), "=m"(vt) : "r"(d9));
    asm("vsub.xyzw $vf1,$vf2,$vf1" : "=r"(b10) : "r"(a10));
    asm("sqc2 $vf5,%1" : "=r"(a11), "=m"(vt) : "r"(b10));
    asm("sqc2 $vf1,%1" : "=r"(d6), "=m"(pcm->dposCenter) : "r"(a11));
    asm("sqc2 $vf2,%1" : "=r"(e6), "=m"(p2) : "r"(d6));
}
#endif

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

/**
 * @todo Structure matches, 41 differing lines of about 135 (float register allocation: sInv/uBest and the two constants land in swapped registers, plus one delay slot fill). Searches 9 arcs around ppos for the nearest obstruction free point using FUN_00145810; names guessed, D_00261928 is the weight table.
 */
INCLUDE_ASM("asm/nonmatchings/P2/cm", FUN_00145950);
#ifdef SKIP_ASM
extern float D_00261928[9];
extern float D_00249E4C;
extern "C" void FUN_00145950(int cpv, void **apv, VECTOR *ppos, VECTOR *pposOut, float sRadius)
{
    VECTOR dir;
    VECTOR pos;
    VECTOR posBest;
    VECTOR s;
    float u0, u1;
    float sInv = 5.0f / sRadius;
    float uBest = D_00249E4C;
    STRUCT_OFFSET(&posBest, 0, qword) = STRUCT_OFFSET(ppos, 0, qword);
    for (int i = 0; i < 9; i++)
    {
        float w = D_00261928[i];
        float radTilt = (float)(i - 4) * 0.39269908f;
        for (int j = 0; (float)j < w; j++)
        {
            SetVectorSphere(&dir, ((float)j * 3.14159265f) / w, radTilt, sRadius);
            int a, b, c;
            asm("lqc2 $vf1,%1" : "=r"(a) : "m"(*ppos));
            asm("lqc2 $vf2,%1" : "=r"(b) : "m"(dir), "r"(a));
            asm("vadd.xyzw $vf1,$vf1,$vf2" : "=r"(c) : "r"(b));
            asm("sqc2 $vf1,%0" : "=m"(pos) : "r"(c));
            if (FUN_00145810(cpv, apv, ppos, &pos, &u0, &u1, sInv + sInv))
            {
                if (0.0f < u0)
                    u0 = u0 + sInv;
                if (u0 < uBest)
                {
                    uBest = u0;
                    float t = 1.0f - uBest;
                    int d1, d2, d3, d4, d5, d6;
                    asm("lqc2 $vf1,%1" : "=r"(d1) : "m"(pos));
                    asm("lqc2 $vf3,%1" : "=r"(d2) : "m"(*ppos), "r"(d1));
                    asm("mfc1 $2,%1\n\tqmtc2.ni $2,$vf4" : "=r"(d3) : "f"(uBest), "r"(d2) : "$2");
                    asm("mfc1 $2,%1\n\tqmtc2.ni $2,$vf2" : "=r"(d4) : "f"(t), "r"(d3) : "$2");
                    asm("vmulax.xyzw ACC,$vf3,$vf2x\n\tvmaddx.xyzw $vf3,$vf1,$vf4x" : "=r"(d5) : "r"(d4));
                    asm("sqc2 $vf2,%1" : "=r"(d6), "=m"(s) : "r"(d5));
                    asm("sqc2 $vf3,%1" : "=r"(d1), "=m"(posBest) : "r"(d6));
                    asm("sqc2 $vf4,%1" : "=r"(d2), "=m"(s) : "r"(d1));
                }
            }
        }
    }
    STRUCT_OFFSET(pposOut, 0, qword) = STRUCT_OFFSET(&posBest, 0, qword);
}
#endif

/**
 * @todo Structure matches, 125 differing lines of about 155 (callee saved register numbering of csbi/apv pointer/constants differs, which shifts most lines). Pushes the camera out of up to 0x40 SBI sphere/BSP hits by solving inequalities. FInsideCmMrd style VU0 inline asm, names guessed. SBI in mark.h was padded to its real size 0x30.
 */
INCLUDE_ASM("asm/nonmatchings/P2/cm", FUN_00145b68);
#ifdef SKIP_ASM
extern "C" void FUN_00145b68(CM *pcm, int cpv, void **apv, float (*pfn)(CM *, VECTOR *, VECTOR *, SBI *), VECTOR *ppos, VECTOR *pdir, VECTOR *pout, float sRadius, float sMax)
{
    SBI asbi[64];
    VECTOR vec;
    VECTOR spill;
    int csbi = 0;
    for (int i = cpv; i > 0; i--)
    {
        void *pv = *apv++;
        if (STRUCT_OFFSET(pv, 0x538, BSP *))
            csbi += CsbiIntersectSphereBsp(ppos, sRadius, STRUCT_OFFSET(pv, 0x534, int), STRUCT_OFFSET(pv, 0x538, BSP *), 0, (GEOM *)((char *)pv + 0x50c), 0x40 - csbi, &asbi[csbi]);
    }
    if (csbi == 0)
    {
        STRUCT_OFFSET(pout, 0, qword) = STRUCT_OFFSET(pdir, 0, qword);
        return;
    }
    InitStackImpl();
    float *aag = (float *)PvAllocStackImpl(csbi * csbi * 4);
    float *ag = (float *)PvAllocStackImpl(csbi * 4);
    float *agSoln = (float *)PvAllocStackImpl(csbi * 4);
    VECTOR *pvec = &vec;
    float *pa = aag;
    for (int i = 0; i < csbi; i++)
    {
        VECTOR *pni = &asbi[i].normal;
        SBI *psbi = asbi;
        for (int j = 0; j < csbi; j++, psbi++)
        {
            int a, b, t, u;
            asm("lqc2 $vf1,0(%1)" : "=r"(a) : "r"(&psbi->normal));
            asm("lqc2 $vf2,0(%1)" : "=r"(b) : "r"(pni), "r"(a));
            asm("vmul.xyz $vf2,$vf2,$vf1\n\tvaddw.x $vf3,$vf0,$vf0w\n\tvadday.x ACC,$vf2,$vf2y\n\tvmaddz.x $vf2,$vf3,$vf2z" : "=r"(t) : "r"(b));
            asm("qmfc2.ni %0,$vf2" : "=r"(u) : "r"(t));
            *(int *)pa++ = u;
        }
    }
    float *pg = ag;
    for (int i = 0; i < csbi; i++)
        *pg++ = pfn(pcm, ppos, pdir, &asbi[i]);
    SolveInequalities(csbi, aag, ag, agSoln);
    STRUCT_OFFSET(&vec, 0, qword) = STRUCT_OFFSET(&D_00248D30, 0, qword);
    float *ps = agSoln;
    SBI *psb = asbi;
    for (int i = 0; i < csbi; i++, psb++)
    {
        float f = *ps++;
        int a, b, c, d, e;
        asm("lqc2 $vf2,%1" : "=r"(a) : "m"(vec));
        asm("mfc1 $3,%1\n\tqmtc2.ni $3,$vf3" : "=r"(b) : "f"(f), "r"(a) : "$3");
        asm("sqc2 $vf3,%1" : "=r"(c), "=m"(spill) : "r"(b));
        asm("lqc2 $vf1,0(%1)" : "=r"(d) : "r"(&psb->normal), "r"(c));
        asm("vadda.xyzw ACC,$vf2,$vf0\n\tvmaddx.xyzw $vf2,$vf1,$vf3x" : "=r"(e) : "r"(d));
        asm("sqc2 $vf2,%1" : "=r"(a), "=m"(vec) : "r"(e));
    }
    LimitVectorLength(pvec, sMax, pvec);
    FreeStackImpl();
    int a, b, c;
    asm("lqc2 $vf1,%1" : "=r"(a) : "m"(*pdir));
    asm("lqc2 $vf2,%1" : "=r"(b) : "m"(vec), "r"(a));
    asm("vadd.xyzw $vf1,$vf1,$vf2" : "=r"(c) : "r"(b));
    asm("sqc2 $vf1,%0" : "=m"(*pout) : "r"(c));
}
#endif

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

/**
 * @todo Structure matches, about 44 differing lines of about 84 (callee saved register order of ppos vs the clock pointer, and relocation noise for the two callback addresses). Moves the camera along a velocity, pushing it out of nearby objects (FUN_00145b68). VU0 inline asm, names guessed.
 */
INCLUDE_ASM("asm/nonmatchings/P2/cm", FUN_00145e68);
#ifdef SKIP_ASM
extern VECTOR D_00261970;
extern VECTOR D_00261980;
extern float D_00261950;
extern "C" void FUN_00145b68(CM *pcm, int cpv, void **apv, float (*pfn)(CM *, VECTOR *, VECTOR *, SBI *), VECTOR *ppos, VECTOR *pdir, VECTOR *pout, float sRadius, float sMax);
extern "C" float FUN_00145de8(CM *pcm, void *pvUnused, VECTOR *pvecA, void *pb);
extern "C" void FUN_00145e68(CM *pcm, VECTOR *ppos, VECTOR *ppos2, VECTOR *pposOut)
{
    CLOCK *pclk = &g_clock;
    VECTOR vel;
    VECTOR out;
    VECTOR box0;
    VECTOR box1;
    VECTOR spill;
    int cpso;
    SO **apso;
    int a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12;
    asm("lqc2 $vf1,%1" : "=r"(a1) : "m"(*ppos));
    asm("lqc2 $vf2,%1" : "=r"(a2) : "m"(D_00261980), "r"(a1));
    asm("lqc2 $vf3,%1" : "=r"(a3) : "m"(*ppos2), "r"(a2));
    asm("vadd.xyzw $vf2,$vf1,$vf2" : "=r"(a4) : "r"(a3));
    asm("vsub.xyzw $vf3,$vf3,$vf1" : "=r"(a5) : "r"(a4));
    asm("lqc2 $vf4,%1" : "=r"(a6) : "m"(D_00261970), "r"(a5));
    asm("move $5,%1\n\tqmtc2.ni $5,$vf5\n\tvdiv Q,$vf0w,$vf5x\n\tvwaitq\n\tvmulq.xyzw $vf3,$vf3,Q\n\tvadd.xyzw $vf1,$vf1,$vf4" : "=r"(a7) : "r"(STRUCT_OFFSET(pclk, 0x14, int)), "r"(a6) : "$5");
    asm("sqc2 $vf3,%1" : "=r"(a8), "=m"(vel) : "r"(a7));
    asm("sqc2 $vf1,%1" : "=r"(a9), "=m"(box0) : "r"(a8));
    asm("sqc2 $vf2,%1" : "=r"(a10), "=m"(box1) : "r"(a9));
    asm("sqc2 $vf5,%1" : "=r"(a11), "=m"(spill) : "r"(a10));
    InitStackImpl();
    IntersectSwBoundingBox(g_psw, 0, &box0, &box1, (PFNFILTER)FUN_00145dd8, 0, &cpso, &apso);
    int b1, b2, b3, b4, b5, b6;
    float len;
    int t;
    asm("lqc2 $vf1,%1" : "=r"(b1) : "m"(vel));
    asm("vmul.xyz $vf1,$vf1,$vf1\n\tvaddw.x $vf2,$vf0,$vf0w\n\tvadday.x ACC,$vf1,$vf1y\n\tvmaddz.x $vf1,$vf2,$vf1z\n\t.word 0x4A0103BD\n\tvwaitq\n\tvaddq.x $vf1,$vf0,Q" : "=r"(b2) : "r"(b1));
    asm("qmfc2.ni %0,$vf1" : "=r"(t) : "r"(b2));
    asm("mtc1 %1,%0" : "=f"(len) : "r"(t));
    FUN_00145b68(pcm, cpso, (void **)apso, (float (*)(CM *, VECTOR *, VECTOR *, SBI *))FUN_00145de8, ppos, &vel, &out, D_0026194C, len + D_00261950);
    int c1, c2, c3, c4, c5;
    int dt = STRUCT_OFFSET(pclk, 0x14, int);
    asm("qmtc2.ni %1,$vf3" : "=r"(c1) : "r"(dt));
    asm("lqc2 $vf1,%1" : "=r"(c2) : "m"(*ppos), "r"(c1));
    asm("lqc2 $vf2,%1" : "=r"(c3) : "m"(out), "r"(c2));
    asm("vadda.xyzw ACC,$vf1,$vf0\n\tvmaddx.xyzw $vf1,$vf2,$vf3x" : "=r"(c4) : "r"(c3));
    asm("sqc2 $vf3,%1" : "=r"(c5), "=m"(spill) : "r"(c4));
    asm("sqc2 $vf1,%0" : "=m"(*pposOut) : "r"(c5));
    FreeStackImpl();
}
#endif

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

/**
 * @todo Two differing lines of 36: the original schedules daddu $3,0 (result init) after vmaxw, we emit it one slot earlier. Frustum sphere test, names are guesses.
 */
INCLUDE_ASM("asm/nonmatchings/P2/cm", FUN_00146038);
#ifdef SKIP_ASM
// FInsideCmMrd called with fewer args here, alias with a guessed shorter signature
extern "C" int FInsideCmMrd3(CM *pcm, qword vDelta, float sOffset, float *puFrac) __asm__("FInsideCmMrd");
extern "C" int FUN_00146038(CM *pcm, VECTOR *ppos, float sRadius)
{
    // VU0 inline asm with fake dependencies through $2, see SpringCm
    register int ch __asm__("$2");
    VECTOR spill;
    float u;
    qword vDelta;
    asm("mfc1 $2,%1" : "=r"(ch) : "f"(sRadius));
    asm("qmtc2.ni $2,$vf4\n\tvmaxw.xyzw $vf5,$vf0,$vf0w" : "=r"(ch) : "r"(ch));
    int r = 0;
    asm("lqc2 $vf2,%1" : "=r"(ch) : "m"(*ppos), "r"(ch), "r"(r));
    asm("lqc2 $vf1,%1" : "=r"(ch) : "m"(STRUCT_OFFSET(pcm, 0x40, VECTOR)), "r"(ch));
    asm("vsub.xyzw $vf6,$vf2,$vf1" : "=r"(ch) : "r"(ch));
    asm("lqc2 $vf3,%1" : "=r"(ch) : "m"(STRUCT_OFFSET(pcm, 0x50, VECTOR)), "r"(ch));
    asm("lqc2 $vf2,%1" : "=r"(ch) : "m"(STRUCT_OFFSET(pcm, 0x60, VECTOR)), "r"(ch));
    asm("lqc2 $vf1,%1" : "=r"(ch) : "m"(STRUCT_OFFSET(pcm, 0x70, VECTOR)), "r"(ch));
    asm("vmulax.xyzw ACC,$vf3,$vf6x\n\tvmadday.xyzw ACC,$vf2,$vf6y\n\tvmaddaz.xyzw ACC,$vf1,$vf6z\n\tvmsubax.xyzw ACC,$vf5,$vf4x\n\tvnop\n\tvnop\n\tvnop\n\tvnop\n\tcfc2.ni $2,$vi17\n\txori $2,$2,0xF0" : "=r"(ch) : "r"(ch));
    asm("sqc2 $vf4,%0" : "=m"(spill) : "r"(ch));
    if (ch == 0)
    {
        asm volatile("qmfc2.ni %0,$vf6" : "=r"(vDelta));
        r = FInsideCmMrd3(pcm, vDelta, sRadius, &u) != 0;
    }
    asm("");
    return r;
}
#endif

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
