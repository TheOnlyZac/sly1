#include <shdanim.h>
#include <shd.h>
#include <gs.h>
#include <clock.h>
#include <vtables.h>
#include <glob.h>
#include <render.h>
#include <math.h>

#define TWO_PI 6.2831855f
#define INV_TWO_PI 0.15915494f

extern CLOCK g_clock;
extern VTSAA D_0021E358; // Loop
extern VTSAA D_0021E378; // PingPong
extern VTSAA D_0021E398; // Shuffle
extern VTSAA D_0021E3B8; // Hologram
extern VTSAA D_0021E3D8; // Scroller
extern VTSAA D_0021E3F8; // Circler
extern VTSAA D_0021E418; // Looker
extern VTSAA D_0021E438; // Eyes

int CbFromSaak(SAAK saak)
{
    switch (saak)
    {
        case SAAK_Loop:
        case SAAK_PingPong: return 0x4C;
        case SAAK_Shuffle:
        case SAAK_Hologram: return 0x38;
        case SAAK_Eyes: return 0x78;
        case SAAK_Scroller: return 0x44;
        case SAAK_Circler: return 0x3C;
        case SAAK_Looker: return 0x50;
    }

    return 0;
}

VTSAA *PvtsaaFromSaak(SAAK saak)
{
    switch (saak)
    {
        case SAAK_Loop:     return &D_0021E358;
        case SAAK_PingPong: return &D_0021E378;
        case SAAK_Shuffle:  return &D_0021E398;
        case SAAK_Hologram: return &D_0021E3B8;
        case SAAK_Eyes:     return &D_0021E438;
        case SAAK_Scroller: return &D_0021E3D8;
        case SAAK_Circler:  return &D_0021E3F8;
        case SAAK_Looker:   return &D_0021E418;
    }

    return 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", PsaaLoadFromBrx__FP18CBinaryInputStream);

void InitSaa(SAA *psaa, SAAF *psaaf) 
{
    int grfsai = psaa->sai.grfsai | 0x1;
    psaa->oid = (OID)psaaf->oid;
    psaa->sai.grfsai = grfsai;
    
    if (psaaf->grfsaaf != 0)
    {
        psaa->sai.grfsai = psaa->sai.grfsai | 0x4;
    }
}

void PostSaaLoad(SAA *psaa) 
{
    if (!psaa->sai.pshd)
    {
        psaa->sai.pshd = PshdFindShader(psaa->oid);
    }
}

int FUpdatableSaa(SAA *psaa) 
{
    if (psaa->tUpdates != g_clock.t)
    {
        psaa->tUpdates = g_clock.t;
        return 1;
    }

    return 0;
}

float UCompleteSaa(SAA *psaa) 
{
    return 0.0f;
}

SAI *PsaiFromSaaShd(SAA *psaa, SHD *pshd) 
{
    if (pshd->oid == psaa->oid)
    {
        return &psaa->sai;
    }

    return NULL;
}

void InitLoop(LOOP *ploop, SAAF *psaaf) 
{
    InitSaa(ploop, psaaf);
    ploop->dtLoopMin  = psaaf->dtLoopMin;
    ploop->dtLoopMax  = psaaf->dtLoopMax;
    ploop->dtPauseMin = psaaf->dtPauseMin;
    ploop->dtPauseMax = psaaf->dtPauseMax;
    ploop->iframe = (float)psaaf->dframe;
}

void PostLoopLoad(LOOP *ploop) 
{
    PostSaaLoad(ploop);
    
    if (!ploop->sai.pshd)
        return;

    float rand1 = GRandInRange(ploop->dtLoopMin, ploop->dtLoopMax);
    ploop->dframe = (float)ploop->sai.pshd->cframe / rand1;

    float rand2 = GRandInRange(ploop->dtPauseMin, ploop->dtPauseMax);
    ploop->dtPause = rand2;
    ploop->dtPauseRemaining = rand2;
}

void UpdateLoop(LOOP *ploop, float dt) 
{
    SHD *pshd = ploop->sai.pshd;
    if (!pshd)
        return;

    if (pshd->cframe < 2)
        return;

    if (ploop->dtPauseRemaining > 0.0f)
    {
        ploop->dtPauseRemaining -= dt;
        return;
    }

    ploop->iframe += ploop->dframe * dt;

    if (ploop->iframe >= (float)ploop->sai.pshd->cframe)
    {
        float rand1 = GRandInRange(ploop->dtLoopMin, ploop->dtLoopMax);
        ploop->dframe = (float)ploop->sai.pshd->cframe / rand1;

        float rand2 = GRandInRange(ploop->dtPauseMin, ploop->dtPauseMax);
        ploop->dtPause = rand2;          
        ploop->dtPauseRemaining = rand2;
    }

    ploop->iframe = GModPositive(ploop->iframe, (float)ploop->sai.pshd->cframe);
    SetSaiIframe(&ploop->sai, (int)ploop->iframe);
}

float UCompleteLoop(LOOP *ploop) 
{
    return (ploop->iframe / ploop->dframe) / 
           (((float)ploop->sai.pshd->cframe / ploop->dframe) + ploop->dtPause);
}

void InitPingpong(PINGPONG *ppingpong, SAAF *psaaf) 
{
    InitSaa(ppingpong, psaaf);
    ppingpong->dtLoopMin = psaaf->dtLoopMin;
    ppingpong->dtLoopMax = psaaf->dtLoopMax;
    ppingpong->dtPauseMin = psaaf->dtPauseMin;
    ppingpong->dtPauseMax = psaaf->dtPauseMax;
    ppingpong->iframe = (float)psaaf->dframe;
}

void PostPingpongLoad(PINGPONG *ppingpong) 
{
    PostSaaLoad(ppingpong);
    
    if (!ppingpong->sai.pshd)
        return;

    float rand1 = GRandInRange(ppingpong->dtLoopMin, ppingpong->dtLoopMax);
    ppingpong->dframe = (float)(ppingpong->sai.pshd->cframe * 2) / rand1;

    float rand2 = GRandInRange(ppingpong->dtPauseMin, ppingpong->dtPauseMax);
    ppingpong->dtPause = rand2;
    ppingpong->dtPauseRemaining = rand2;
}

void UpdatePingpong(PINGPONG *ppingpong, float dt) 
{
    if (!ppingpong->sai.pshd || ppingpong->sai.pshd->cframe < 2)
        return;

    if (ppingpong->dtPauseRemaining > 0.0f)
    {
        ppingpong->dtPauseRemaining -= dt;
        return;
    }

    ppingpong->iframe += ppingpong->dframe * dt;

    if (ppingpong->iframe >= (float)ppingpong->sai.pshd->cframe)
    {
        ppingpong->iframe -= ppingpong->dframe * dt;
        ppingpong->dframe = -ppingpong->dframe;
    }

    if (ppingpong->iframe < 0.0f)
    {
        ppingpong->iframe = 0.0f; 
        float rand1 = GRandInRange(ppingpong->dtLoopMin, ppingpong->dtLoopMax);
        ppingpong->dframe = (float)(ppingpong->sai.pshd->cframe * 2) / rand1;

        float rand2 = GRandInRange(ppingpong->dtPauseMin, ppingpong->dtPauseMax);
        ppingpong->dtPause = rand2;         
        ppingpong->dtPauseRemaining = rand2; 
    }

    SetSaiIframe(&ppingpong->sai, (int)ppingpong->iframe);
}

float UCompletePingpong(PINGPONG *ppingpong) 
{
    float absDframe = ppingpong->dframe;
    float progress;

    if (absDframe < 0.0f)
    {
        absDframe = -absDframe;
        progress = (float)(ppingpong->sai.pshd->cframe * 2) - ppingpong->iframe;
    }
    else
    {
        progress = ppingpong->iframe;
    }

    return (progress / absDframe) / 
           (((float)(ppingpong->sai.pshd->cframe * 2) / absDframe) + ppingpong->dtPause);
}

void InitShuffle(SHUFFLE *pshuffle, SAAF *psaaf) 
{
    InitSaa(pshuffle, psaaf);
    pshuffle->dtPauseMin = psaaf->dtLoopMin;
    pshuffle->dtPauseMax = psaaf->dtLoopMax;
}

void UpdateShuffle(SHUFFLE *pshuffle, float dt)
{
    if (!pshuffle->sai.pshd || pshuffle->sai.pshd->cframe < 2)
        return;

    if (pshuffle->dtPause > 0.0f)
    {
        pshuffle->dtPause -= dt;
        return;
    }

    int randFrame = NRandInRange(1, pshuffle->sai.pshd->cframe - 1);
    
    int newIframe = (pshuffle->sai.iframe + randFrame) % pshuffle->sai.pshd->cframe;
    
    SetSaiIframe(&pshuffle->sai, newIframe);

    pshuffle->dtPause = GRandInRange(pshuffle->dtPauseMin, pshuffle->dtPauseMax);
}

void InitHologram(HOLOGRAM *phologram, SAAF *psaaf) 
{
    InitSaa(phologram, psaaf);

    phologram->startAngle = psaaf->dtLoopMin;

    uint count = *(uint *)&psaaf->dtLoopMax;
    phologram->angleStep = TWO_PI / (float)count;

    if (phologram->startAngle == 3.402823466e+38f)
    {
        phologram->startAngle = GRandInRange(0.0f, phologram->angleStep);
    }
}

void PostHologramLoad(HOLOGRAM *phologram) 
{
    PostSaaLoad(phologram);

    if (phologram->sai.pshd != NULL && phologram->sai.pshd->cframe >= 2)
    {
        phologram->angleStepPerFrame = phologram->angleStep / (float)phologram->sai.pshd->cframe;
    }
}

void NotifyHologramRender(HOLOGRAM *phologram, ALO *palo, RPL *prpl) 
{
    if (!phologram->sai.pshd || phologram->sai.pshd->cframe < 2)
        return;

    if (prpl->pfnDraw != DrawGlob)
        return;

    VECTOR *pvec = prpl->palo->dlChild.head ? &prpl->pos : (VECTOR *)((char *)g_pcm + 0x80);

    float angle = atan2f(pvec->y, pvec->x);
    
    int iframe = (int)(GModPositive(phologram->startAngle - angle, phologram->angleStep) / phologram->angleStepPerFrame);

    SetSaiIframe(&phologram->sai, iframe);
}

void InitScroller(SCROLLER *pscroller, SAAF *psaaf) 
{
    InitSaa(pscroller, psaaf);

    pscroller->duSpeed = psaaf->dtLoopMin;
    pscroller->dvSpeed = psaaf->dtLoopMax;
    pscroller->du = psaaf->dtPauseMin;
    pscroller->dv = psaaf->dtPauseMax;
    
    pscroller->sv = 1.0f;
    pscroller->su = 1.0f;
    
    pscroller->sai.grfsai = (pscroller->sai.grfsai & ~1) | 2;
}

void UpdateScroller(SCROLLER *pscroller, float dt) 
{
    if (!pscroller->sai.pshd)
        return;

    float newDu = fmodf(pscroller->sai.txt.du + (pscroller->duSpeed * pscroller->su) * dt, pscroller->du);
    float newDv = fmodf(pscroller->sai.txt.dv + (pscroller->dvSpeed * pscroller->sv) * dt, pscroller->dv);

    SetSaiDuDv(&pscroller->sai, newDu, newDv);
}

float UCompleteScroller(SCROLLER *pscroller) 
{
    float uComp = 0.0f;

    if (pscroller->duSpeed != 0.0f)
    {
        uComp = (pscroller->sai.txt.du / pscroller->du) * 0.5f;
    }
    else
    {
        uComp = 0.5f;
    }

    if (pscroller->dvSpeed != 0.0f)
    {
        uComp += (pscroller->sai.txt.dv / pscroller->dv) * 0.5f;
    }
    else
    {
        uComp += 0.5f;
    }

    return uComp;
}

void SetScrollerMasterSpeeds(SCROLLER *pscroller, float su, float sv) 
{ 
    pscroller->su = su; 
    pscroller->sv = sv; 
}

void InitCircler(CIRCLER *pcircler, SAAF *psaaf) 
{
    InitSaa(pcircler, psaaf);
    
    pcircler->radsSpeed = psaaf->dtLoopMin;
    pcircler->radius = psaaf->dtLoopMax;
    pcircler->duCenter  = psaaf->dtPauseMin;
    pcircler->dvCenter  = psaaf->dtPauseMax;

    pcircler->sai.grfsai = (pcircler->sai.grfsai & ~1) | 2;

}

void UpdateCircler(CIRCLER *pcircler, float dt) 
{
    if (!pcircler->sai.pshd)
        return;

    float angle = RadNormalize(g_clock.t * pcircler->radsSpeed);
    
    float sinOut;
    float cosOut;
    CalculateSinCos(angle, &sinOut, &cosOut);

    sinOut = (sinOut * pcircler->radius) + pcircler->duCenter;
    cosOut = (cosOut * pcircler->radius) + pcircler->dvCenter;

    SetSaiDuDv(&pcircler->sai, sinOut, cosOut);
}

float UCompleteCircler(CIRCLER *pcircler) 
{
    float angle = g_clock.t * pcircler->radsSpeed;
    
    return GModPositive(angle, TWO_PI) * INV_TWO_PI;
}

void InitLooker(LOOKER *plooker, SAAF *psaaf) 
{
    InitSaa(plooker, psaaf);

    plooker->uCenter = psaaf->dtLoopMin;
    plooker->vCenter = psaaf->dtLoopMax;

    plooker->duMin = psaaf->dtPauseMin - psaaf->dtLoopMin;
    plooker->duMax = psaaf->dtPauseMax - psaaf->dtLoopMin;
    plooker->dvMin = psaaf->dtLookMin - psaaf->dtLoopMax;

    plooker->dvMax = psaaf->dtLookMax - psaaf->dtLoopMax;

    plooker->sai.grfsai = (plooker->sai.grfsai & ~1) | 2;
}

void SetLookerSgvr(LOOKER *plooker, SGVR *psgvr, GLOBSET *pglobset, GLOB *pglob, SUBGLOB *psubglob)
{
    STRUCT_OFFSET(psgvr, 0x0, float *) = &STRUCT_OFFSET(plooker, 0x44, float);
    STRUCT_OFFSET(psgvr, 0x4, float *) = &STRUCT_OFFSET(plooker, 0x4C, float);
    STRUCT_OFFSET(psgvr, 0x8, float *) = &STRUCT_OFFSET(plooker, 0x48, float);
}

void SetVecPosad(VECTOR *pvec, POSAD *pposad) 
{
    pvec->x = pposad->x;
    pvec->y = pposad->y;
    pvec->z = pposad->z;
}

void SetUvPuvqd(UVF *puv, UVQ *puvqd) 
{
    puv->u = puvqd->u;
    puv->v = puvqd->v;
}

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", NotifyLookerRender__FP6LOOKERP3ALOP3RPL);

JUNK_ADDIU(60);
JUNK_WORD(0x0003100B);

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", FUN_001b5b58);

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", FUN_001b5c40);
