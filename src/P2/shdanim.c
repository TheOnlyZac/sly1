#include <shdanim.h>
#include <shd.h>
#include <gs.h>
#include <clock.h>
#include <glob.h>
#include <render.h>
#include <math.h>
#include <eyes.h>
#include <memory.h>

#define TWO_PI 6.2831855f
#define INV_TWO_PI 0.15915494f

extern VTSAA g_vtloop;
extern VTSAA g_vtpingpong;
extern VTSAA g_vtshuffle;
extern VTSAA g_vthologram;
extern VTSAA g_vtscroller;
extern VTSAA g_vtcircler;
extern VTSAA g_vtlooker;
extern VTSAA g_vteyes;

int CbFromSaak(SAAK saak)
{
    switch (saak)
    {
        case SAAK_Loop:     return sizeof(LOOP);
        case SAAK_PingPong: return sizeof(PINGPONG);
        case SAAK_Shuffle:  return sizeof(SHUFFLE);
        case SAAK_Hologram: return sizeof(HOLOGRAM);
        case SAAK_Eyes:     return sizeof(EYES);
        case SAAK_Scroller: return sizeof(SCROLLER);
        case SAAK_Circler:  return sizeof(CIRCLER);
        case SAAK_Looker:   return sizeof(LOOKER);
    }

    return 0;
}

VTSAA *PvtsaaFromSaak(SAAK saak)
{
    switch (saak)
    {
        case SAAK_Loop:     return &g_vtloop;
        case SAAK_PingPong: return &g_vtpingpong;
        case SAAK_Shuffle:  return &g_vtshuffle;
        case SAAK_Hologram: return &g_vthologram;
        case SAAK_Eyes:     return &g_vteyes;
        case SAAK_Scroller: return &g_vtscroller;
        case SAAK_Circler:  return &g_vtcircler;
        case SAAK_Looker:   return &g_vtlooker;
    }

    return 0;
}

SAA *PsaaLoadFromBrx(CBinaryInputStream *pbis)
{
    SAAK saak = (SAAK)pbis->U16Read();
    if (saak != SAAK_None)
    {
        SAA *psaa = (SAA *)PvAllocSwClearImpl(CbFromSaak(saak));
        psaa->pvtsaa = PvtsaaFromSaak(saak);
        psaa->saak = saak;

        SAAF saaf;
        pbis->Read(sizeof(SAAF), &saaf);
        psaa->pvtsaa->pfnInitSaa(psaa, &saaf);
        return psaa;
    }

    return NULL;
}

void InitSaa(SAA *psaa, SAAF *psaaf)
{
    psaa->oid = (OID)psaaf->oid;
    psaa->sai.grfsai |= 0x1;

    if (psaaf->fInstanced != 0)
    {
        psaa->sai.grfsai |= 0x4;
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
    if (psaa->tUpdated != g_clock.t)
    {
        psaa->tUpdated = g_clock.t;
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
    ploop->dtLoopMin = psaaf->loopf.dtLoopMin;
    ploop->dtLoopMax = psaaf->loopf.dtLoopMax;
    ploop->dtPauseMin = psaaf->loopf.dtPauseMin;
    ploop->dtPauseMax = psaaf->loopf.dtPauseMax;
    ploop->gframe = (float)psaaf->loopf.iframeStart;
}

void PostLoopLoad(LOOP *ploop)
{
    PostSaaLoad(ploop);

    if (!ploop->sai.pshd)
        return;

    float rand1 = GRandInRange(ploop->dtLoopMin, ploop->dtLoopMax);
    ploop->sviframe = (float)ploop->sai.pshd->cframe / rand1;

    float rand2 = GRandInRange(ploop->dtPauseMin, ploop->dtPauseMax);
    ploop->dtPauseRequested = rand2;
    ploop->dtPause = rand2;
}

void UpdateLoop(LOOP *ploop, float dt)
{
    SHD *pshd = ploop->sai.pshd;
    if (!pshd)
        return;

    if (pshd->cframe < 2)
        return;

    if (ploop->dtPause > 0.0f)
    {
        ploop->dtPause -= dt;
        return;
    }

    ploop->gframe += ploop->sviframe * dt;

    if (ploop->gframe >= (float)ploop->sai.pshd->cframe)
    {
        float rand1 = GRandInRange(ploop->dtLoopMin, ploop->dtLoopMax);
        ploop->sviframe = (float)ploop->sai.pshd->cframe / rand1;

        float rand2 = GRandInRange(ploop->dtPauseMin, ploop->dtPauseMax);
        ploop->dtPauseRequested = rand2;
        ploop->dtPause = rand2;
    }

    ploop->gframe = GModPositive(ploop->gframe, (float)ploop->sai.pshd->cframe);
    SetSaiIframe(&ploop->sai, (int)ploop->gframe);
}

float UCompleteLoop(LOOP *ploop)
{
    return (ploop->gframe / ploop->sviframe) /
           (((float)ploop->sai.pshd->cframe / ploop->sviframe) + ploop->dtPauseRequested);
}

void InitPingpong(PINGPONG *ppingpong, SAAF *psaaf)
{
    InitSaa(ppingpong, psaaf);
    ppingpong->dtPingpongMin = psaaf->pingpongf.dtPingpongMin;
    ppingpong->dtPingpongMax = psaaf->pingpongf.dtPingpongMax;
    ppingpong->dtPauseMin = psaaf->pingpongf.dtPauseMin;
    ppingpong->dtPauseMax = psaaf->pingpongf.dtPauseMax;
    ppingpong->gframe = (float)psaaf->pingpongf.iframeStart;
}

void PostPingpongLoad(PINGPONG *ppingpong)
{
    PostSaaLoad(ppingpong);

    if (!ppingpong->sai.pshd)
        return;

    float rand1 = GRandInRange(ppingpong->dtPingpongMin, ppingpong->dtPingpongMax);
    ppingpong->sviframe = (float)(ppingpong->sai.pshd->cframe * 2) / rand1;

    float rand2 = GRandInRange(ppingpong->dtPauseMin, ppingpong->dtPauseMax);
    ppingpong->dtPauseRequested = rand2;
    ppingpong->dtPause = rand2;
}

void UpdatePingpong(PINGPONG *ppingpong, float dt)
{
    if (!ppingpong->sai.pshd || ppingpong->sai.pshd->cframe < 2)
        return;

    if (ppingpong->dtPause > 0.0f)
    {
        ppingpong->dtPause -= dt;
        return;
    }

    ppingpong->gframe += ppingpong->sviframe * dt;

    if (ppingpong->gframe >= (float)ppingpong->sai.pshd->cframe)
    {
        ppingpong->gframe -= ppingpong->sviframe * dt;
        ppingpong->sviframe = -ppingpong->sviframe;
    }

    if (ppingpong->gframe < 0.0f)
    {
        ppingpong->gframe = 0.0f;
        float rand1 = GRandInRange(ppingpong->dtPingpongMin, ppingpong->dtPingpongMax);
        ppingpong->sviframe = (float)(ppingpong->sai.pshd->cframe * 2) / rand1;

        float rand2 = GRandInRange(ppingpong->dtPauseMin, ppingpong->dtPauseMax);
        ppingpong->dtPauseRequested = rand2;
        ppingpong->dtPause = rand2;
    }

    SetSaiIframe(&ppingpong->sai, (int)ppingpong->gframe);
}

float UCompletePingpong(PINGPONG *ppingpong)
{
    float absDframe = ppingpong->sviframe;
    float progress;

    if (absDframe < 0.0f)
    {
        absDframe = -absDframe;
        progress = (float)(ppingpong->sai.pshd->cframe * 2) - ppingpong->gframe;
    }
    else
    {
        progress = ppingpong->gframe;
    }

    return (progress / absDframe) / 
           (((float)(ppingpong->sai.pshd->cframe * 2) / absDframe) + ppingpong->dtPauseRequested);
}

void InitShuffle(SHUFFLE *pshuffle, SAAF *psaaf)
{
    InitSaa(pshuffle, psaaf);
    pshuffle->dtPauseMin = psaaf->shufflef.dtPauseMin;
    pshuffle->dtPauseMax = psaaf->shufflef.dtPauseMax;
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

    phologram->dradAdjust = psaaf->hologramf.dradAdjust;
    phologram->dradSymmetry = TWO_PI / (float)psaaf->hologramf.cSymmetry;

    if (phologram->dradAdjust == 3.402823466e+38f)
    {
        phologram->dradAdjust = GRandInRange(0.0f, phologram->dradSymmetry);
    }
}

void PostHologramLoad(HOLOGRAM *phologram)
{
    PostSaaLoad(phologram);

    if (phologram->sai.pshd != NULL && phologram->sai.pshd->cframe >= 2)
    {
        phologram->dradFrame = phologram->dradSymmetry / (float)phologram->sai.pshd->cframe;
    }
}

void NotifyHologramRender(HOLOGRAM *phologram, ALO *palo, RPL *prpl)
{
    if (!phologram->sai.pshd || phologram->sai.pshd->cframe < 2)
        return;

    if (prpl->pfnDraw != DrawGlob)
        return;

    VECTOR *pvec = prpl->palo->dlChild.head ? &prpl->pos : &STRUCT_OFFSET(g_pcm, 0x80, VECTOR);
    float angle = atan2f(pvec->y, pvec->x);
    int iframe = (int)(GModPositive(phologram->dradAdjust - angle, phologram->dradSymmetry) / phologram->dradFrame);
    SetSaiIframe(&phologram->sai, iframe);
}

void InitScroller(SCROLLER *pscroller, SAAF *psaaf)
{
    InitSaa(pscroller, psaaf);
    pscroller->svu = psaaf->scrollerf.svu;
    pscroller->svv = psaaf->scrollerf.svv;
    pscroller->duMod = psaaf->scrollerf.duMod;
    pscroller->dvMod = psaaf->scrollerf.dvMod;
    pscroller->svvMaster = 1.0f;
    pscroller->svuMaster = 1.0f;
    pscroller->sai.grfsai = (pscroller->sai.grfsai & ~1) | 2;
}

void UpdateScroller(SCROLLER *pscroller, float dt)
{
    if (!pscroller->sai.pshd)
        return;

    float newDu = fmodf(pscroller->sai.txt.du + (pscroller->svu * pscroller->svuMaster) * dt, pscroller->duMod);
    float newDv = fmodf(pscroller->sai.txt.dv + (pscroller->svv * pscroller->svvMaster) * dt, pscroller->dvMod);

    SetSaiDuDv(&pscroller->sai, newDu, newDv);
}

float UCompleteScroller(SCROLLER *pscroller)
{
    float uComp = 0.0f;

    if (pscroller->svu != 0.0f)
    {
        uComp = (pscroller->sai.txt.du / pscroller->duMod) * 0.5f;
    }
    else
    {
        uComp = 0.5f;
    }

    if (pscroller->svv != 0.0f)
    {
        uComp += (pscroller->sai.txt.dv / pscroller->dvMod) * 0.5f;
    }
    else
    {
        uComp += 0.5f;
    }

    return uComp;
}

void SetScrollerMasterSpeeds(SCROLLER *pscroller, float su, float sv)
{ 
    pscroller->svuMaster = su;
    pscroller->svvMaster = sv;
}

void InitCircler(CIRCLER *pcircler, SAAF *psaaf)
{
    InitSaa(pcircler, psaaf);
    pcircler->sw = psaaf->circlerf.sw;
    pcircler->sRadius = psaaf->circlerf.sRadius;
    pcircler->du = psaaf->circlerf.du;
    pcircler->dv = psaaf->circlerf.dv;
    pcircler->sai.grfsai = (pcircler->sai.grfsai & ~1) | 2;
}

void UpdateCircler(CIRCLER *pcircler, float dt)
{
    if (!pcircler->sai.pshd)
        return;

    float angle = RadNormalize(g_clock.t * pcircler->sw);

    float sinOut, cosOut;
    CalculateSinCos(angle, &sinOut, &cosOut);

    sinOut = (sinOut * pcircler->sRadius) + pcircler->du;
    cosOut = (cosOut * pcircler->sRadius) + pcircler->dv;
    SetSaiDuDv(&pcircler->sai, sinOut, cosOut);
}

float UCompleteCircler(CIRCLER *pcircler)
{
    float angle = g_clock.t * pcircler->sw;
    return GModPositive(angle, TWO_PI) * INV_TWO_PI;
}

void InitLooker(LOOKER *plooker, SAAF *psaaf)
{
    InitSaa(plooker, psaaf);
    plooker->uCenter = psaaf->lookerf.uCenter;
    plooker->vCenter = psaaf->lookerf.vCenter;
    plooker->duMin = psaaf->lookerf.uMin - psaaf->lookerf.uCenter;
    plooker->duMax = psaaf->lookerf.uMax - psaaf->lookerf.uCenter;
    plooker->dvMin = psaaf->lookerf.vMin - psaaf->lookerf.vCenter;
    plooker->dvMax = psaaf->lookerf.vMax - psaaf->lookerf.vCenter;
    plooker->sai.grfsai = (plooker->sai.grfsai & ~1) | 2;
}

void SetLookerSgvr(LOOKER *plooker, SGVR *psgvr, GLOBSET *pglobset, GLOB *pglob, SUBGLOB *psubglob)
{
    psgvr->pcvtx = &plooker->cvtx;
    psgvr->ppposad = &plooker->pposad;
    psgvr->ppuvqd = &plooker->puvqd;
}

void SetVecPosad(VECTOR *pvec, POSAD *pposad)
{
    pvec->x = pposad->x;
    pvec->y = pposad->y;
    pvec->z = pposad->z;
}

void SetUvPuvqd(UVF *puv, UVQD *puvqd)
{
    puv->u = puvqd->u;
    puv->v = puvqd->v;
}

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", NotifyLookerRender__FP6LOOKERP3ALOP3RPL);

JUNK_ADDIU(60);
JUNK_WORD(0x0003100B);

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", FUN_001b5b58);

INCLUDE_ASM("asm/nonmatchings/P2/shdanim", FUN_001b5c40);
