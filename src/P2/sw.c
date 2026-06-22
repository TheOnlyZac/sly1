#include <sw.h>
#include <ui.h>
#include <frm.h>
#include <util.h>
#include <sound.h>
#include <dialog.h>
#include <989snd.h>
#include <sce/memset.h>
#include <game.h>
#include <difficulty.h>
#include <bbmark.h>
#include <coin.h>
#include <screen.h>
#include <prompt.h>
#include <memory.h>
#include <bez.h>

extern SW *g_psw;
extern int g_fLoadDebugInfo;
extern byte *g_pbBulkData;
extern int g_fLoadBulkData;
extern int g_cbBulkData;
extern int g_nBulkDataSig;
extern int g_cbBulkDataReadAdjustment;

void InitSwDlHash(SW *psw)
{
    DL *pdl = psw->adlHash;

    for (uint i = 0; i < 512; i++)
    {
        InitDl(pdl, sizeof(DL));
        pdl++;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/sw", InitSw__FP2SW);

INCLUDE_ASM("asm/nonmatchings/P2/sw", DeleteSw__FP2SW);

INCLUDE_ASM("asm/nonmatchings/P2/sw", SetupBulkDataFromBrx__FiP18CBinaryInputStream);

void LoadBulkDataFromBrx(CBinaryInputStream *pbis)
{
    if (g_fLoadBulkData)
    {
        g_cbBulkDataReadAdjustment = pbis->m_cbRemaining;
        pbis->Align(16);
        pbis->Read(g_cbBulkData, g_pbBulkData);
    }
}

static inline VU_VECTOR VuVectorXyz(float x, float y, float z)
{
    VU_VECTOR v;
    qword tmp;
    asm("mfc1 %0, %2\n\tmfc1 %1, %3\n\tpextlw %0, %1, %0\n\tmfc1 %1, %4\n\tpcpyld %0, %1, %0"
        : "=r"(v.data), "=r"(tmp)
        : "f"(x), "f"(y), "f"(z));
    return v;
}

void SetSwGravity(SW *psw, float z)
{
    union
    {
        qword q;
        float af[4];
    } u;

    u.q = VuVectorXyz(0.0f, 0.0f, z).data;
    STRUCT_OFFSET(psw, 0x1EE0, qword) = u.q; // vecGravity = (0, 0, z, junk)
}

extern "C" void FUN_001dbac0(SW *psw, int reg, int value)
{
    SetAMRegister__FiUc(reg, value);
}

int FUN_001dbae0(SW *psw, int reg)
{
    return GetAMRegister(reg);
}

void FUN_001dbb00(SW *psw, int reg, int value)
{
    UpdateAMRegister(reg, value);
}

int FOverflowSwLo(SW *psw, LO *plo, int fHiPri)
{
    int fOverflow = 0;

    if ((plo->pvtlo->grfcid & 2) && psw->cpsoRoot >= 247)
    {
        int fLow = (fHiPri == 0);
        fOverflow = fLow;
    }

    return fOverflow;
}

XA *PxaAllocSw(SW *psw)
{
    XA *pxa = (XA *)PvAllocSlotheapImpl(&psw->slotheapXa);
    memset(pxa, 0, sizeof(XA));
    return pxa;
}

void FreeSwXaList(SW *psw, XA *pxaFirst)
{
    while (pxaFirst)
    {
        XA *pxa = pxaFirst->pxaNextTarget;
        FreeSlotheapPv(&psw->slotheapXa, pxaFirst);
        pxaFirst = pxa;
    }
}

MQ *PmqAllocSw(SW *psw)
{
    MQ *pmq = (MQ *)PvAllocSlotheapImpl(&psw->slotheapMq);
    memset(pmq, 0, sizeof(MQ));
    return pmq;
}

void FreeSwMqList(SW *psw, MQ *pmqFirst)
{
    while (pmqFirst)
    {
        MQ *pmq = pmqFirst->pmqNext;
        FreeSlotheapPv(&psw->slotheapMq, pmqFirst);
        pmqFirst = pmq;
    }
}

void EnsureSwCallback(SW *psw, PFNMQ pfnmq, void *pvContext, MSGID msgid, void *pvCallbackData)
{
    MQ *pmq = psw->pmqCallbackFirst;

    while (pmq)
    {
        if (pmq->pfnmq == pfnmq && pmq->pvContext == pvContext &&
            pmq->msgid == msgid && pmq->pvCallbackData == pvCallbackData)
        {
            return;
        }

        pmq = pmq->pmqNext;
    }

    PostSwCallback(psw, pfnmq, pvContext, msgid, pvCallbackData);
}

void PostSwCallback(SW *psw, PFNMQ pfnmq, void *pvContext, MSGID msgid, void *pvCallbackData)
{
    MQ *pmq = PmqAllocSw(psw);
    pmq->pfnmq = pfnmq;
    pmq->pvContext = pvContext;
    pmq->msgid = msgid;
    pmq->pvCallbackData = pvCallbackData;

    if (psw->pmqCallbackLast)
    {
        psw->pmqCallbackLast->pmqNext = pmq;
    }
    else
    {
        psw->pmqCallbackFirst = pmq;
    }

    psw->pmqCallbackLast = pmq;
}

INCLUDE_ASM("asm/nonmatchings/P2/sw", ClearSwCallbacks__FP2SWiPFPv5MSGIDPv_vPv5MSGIDT3);

INCLUDE_ASM("asm/nonmatchings/P2/sw", ProcessSwCallbacks__FP2SW);

INCLUDE_ASM("asm/nonmatchings/P2/sw", ProcessSwSpliceScheduledCallbacks__FP2SWf);

STSO *PstsoAllocSw(SW *psw)
{
    STSO *pstso = (STSO *)PvAllocSlotheapImpl(&psw->slotheapStso);
    memset(pstso, 0, sizeof(STSO));
    return pstso;
}

void FreeSwStsoList(SW *psw, STSO *pstsoFirst)
{
    while (pstsoFirst)
    {
        STSO *pstso = pstsoFirst->pstsoNext;
        FreeSlotheapPv(&psw->slotheapStso, pstsoFirst);
        pstsoFirst = pstso;
    }
}

struct PSL
{
    int cplo;
    LO **aplo;
} __attribute__((packed));

INCLUDE_ASM("asm/nonmatchings/P2/sw", AddSwProxySource__FP2SWP2LOi);
#ifdef SKIP_ASM
void AddSwProxySource(SW *psw, LO *ploProxySource, int cploClone)
{
    PSL psl;

    cploClone -= 1;
    psl.cplo = cploClone;

    if (cploClone > 0)
    {
        LO **aplo = (LO **)PvAllocSwImpl(cploClone << 2);
        psl.aplo = aplo;

        if (cploClone > 0)
        {
            int i = 0;
            do
            {
                aplo[i] = PloCloneLo(ploProxySource, psw, NULL);
                i++;
            } while (i < cploClone);
        }
    }

    int cpsl = STRUCT_OFFSET(psw, 0x1EFC, int);
    STRUCT_OFFSET(psw, cpsl * 8 + 0x1F00, PSL) = psl;
    STRUCT_OFFSET(psw, 0x1EFC, int) = cpsl + 1;
}
#endif // SKIP_ASM

LO *PloGetSwProxySource(SW *psw, int ipsl)
{
    // Proxy-source list at SW+0x1F00: array of 8-byte {int cplo; LO **aplo} pairs
    // (count cpsl lives at 0x1EFC; see AddSwProxySource).
    int *p = &STRUCT_OFFSET(psw, ipsl * 8 + 0x1F00, int);
    int c = p[0] - 1;
    LO **aplo = (LO **)p[1];
    int i = c * 4;
    asm volatile(""); // scheduling barrier: preserve the original count-store ordering
    p[0] = c;
    return *(LO **)(i + (int)aplo);
}

INCLUDE_ASM("asm/nonmatchings/P2/sw", IntersectSwBoundingBox__FP2SWP2SOP6VECTORT2PFPvP2SO_iPvPiPPP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/sw", IntersectSwBoundingSphere__FP2SWP2SOP6VECTORfPFPvP2SO_iPvPiPPP2SO);

void RemoveOxa(OXA *poxa, OXA **ppoxaFirst)
{
    if (poxa->poxaNext != NULL)
    {
        poxa->poxaNext->poxaPrev = poxa->poxaPrev;
    }

    if (poxa->poxaPrev != NULL)
    {
        poxa->poxaPrev->poxaNext = poxa->poxaNext;
    }
    else
    {
        *ppoxaFirst = poxa->poxaNext;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/sw", InitSwAoxa__FP2SW);

void AddOxa(OXA *poxa, OXA **ppoxaFirst)
{
    poxa->poxaNext = *ppoxaFirst;
    poxa->poxaPrev = NULL;
    if (*ppoxaFirst != NULL)
    {
        (*ppoxaFirst)->poxaPrev = poxa;
    }
    *ppoxaFirst = poxa;
}

OXA *PoxaAllocSw(SW *psw, SO *pso)
{
    OXA *poxa = STRUCT_OFFSET(psw, 0x1AE4, OXA *);
    RemoveOxa(poxa, &STRUCT_OFFSET(psw, 0x1AE4, OXA *));
    AddOxa(poxa, &STRUCT_OFFSET(psw, 0x1AE8, OXA *));
    poxa->pso = pso;
    return poxa;
}

INCLUDE_ASM("asm/nonmatchings/P2/sw", FreeSwPoxa__FP2SWP3OXA);

INCLUDE_ASM("asm/nonmatchings/P2/sw", CreateSwDefaultLights__FP2SW);

/**
 * @todo Rename.
 */
void FUN_001dccc0(CBinaryInputStream *pbis)
{
    int count = pbis->U32Read();
    
    if (g_fLoadDebugInfo == 0)
        return;

    for (int i = 1; i < count; i++)
    {
        pbis->Unknown1();
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/sw", CreateSwPrizes__FP2SW);

INCLUDE_ASM("asm/nonmatchings/P2/sw", LoadSwFromBrx__FP2SWP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FClipLineHomogeneous__FP7VECTOR4);

INCLUDE_ASM("asm/nonmatchings/P2/sw", DrawLineWorld__FP6VECTORT0G4RGBAP2CMi);

void DrawLineWorld(VECTOR *ppos1, VECTOR *ppos2, RGBA rgba, CM *pcm, int fDepthTest);

INCLUDE_ASM("asm/nonmatchings/P2/sw", DrawAxesWorld__FP6VECTORP7MATRIX3fP2CMi);
#ifdef SKIP_ASM
void DrawAxesWorld(VECTOR *ppos, MATRIX3 *pmat, float sScale, CM *pcm, int fDepthTest)
{
    VECTOR4 apos[10];
    RGBA rgba;

    TesselateBezier(sScale, 0.0f, sScale, ppos, (VECTOR *)pmat,
                    (VECTOR *)((char *)0), (VECTOR *)((char *)0), 10, (VECTOR *)apos);

    rgba = *(RGBA *)pcm;

    for (int i = 1; i < 10; i++)
    {
        DrawLineWorld((VECTOR *)&apos[i - 1], (VECTOR *)&apos[i], rgba,
                      (CM *)(long)fDepthTest, 1);
    }
}
#endif // SKIP_ASM

void SetSwIllum(SW *psw, float uMidtone)
{
    psw->lsmDefault.uMidtone = uMidtone;
    g_cframeStaticLightsInvalid = g_cframe;
}

void SetSwIllumShadow(SW *psw, float uShadow)
{
    psw->lsmDefault.uShadow = uShadow;
    g_cframeStaticLightsInvalid = g_cframe;
}

void SetSwExcitement(SW *psw, float gexcMenu)
{
    psw->gexcMenu = gexcMenu;
    g_iexcHyst = -100;
    SetMvgkRvol(7, MVGK_Music, 1.0f);
    snd_SetGlobalExcite((int)(psw->gexcMenu + 0.5f));
}

int FLevelSwVisited(SW *psw, WID wid)
{
    return GrflsFromWid(wid) & 1;
}

int FLevelSwPrimary(SW *psw, WID wid)
{
    return GrflsFromWid(wid) & 2;
}

int FLevelSwSecondary(SW *psw, WID wid)
{
    return GrflsFromWid(wid) & 4;
}

int FLevelSwTertiary(SW *psw, WID wid)
{
    return GrflsFromWid(wid) & 8;
}

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dd710);

uint GrflsLevelCompletionFromWid(int wid) __asm__("get_level_completion_by_id");

extern "C" int FUN_001dd758(SW *psw, int wid)
{
    uint grfls = GrflsLevelCompletionFromWid(wid);
    uint f = 0;
    uint mask = grfls & 3;

    if (grfls & 4)
    {
        LS *pls = g_plsCur;
        f = (mask & pls->fls) ^ mask;
        f = f < 1;
    }

    return f;
}

uint GrflsLevelCompletionFromWid(int wid) __asm__("get_level_completion_by_id");

extern "C" int FUN_001dd7a0(SW *psw, int wid)
{
    uint grfls = GrflsLevelCompletionFromWid(wid);
    int f = 0;
    uint mask = grfls & 7;

    if (grfls & 8)
    {
        uint t = mask & g_plsCur->fls;
        f = (t ^ mask) < 1;
    }

    return f;
}

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dd7e8);

extern int *PlsFromWid(WID wid) __asm__("LsFromWid");

extern "C" int FUN_001dd888(SW *psw, WID wid, int nKey)
{
    int *pls = PlsFromWid(wid);
    if (pls != NULL)
    {
        int *p = pls + 0x11;
        int i = 0;
        do
        {
            if (p[0] == nKey)
                return p[1];
            i++;
            p += 2;
        } while ((unsigned)i < 4);
    }
    return 0;
}

int FUN_001dd8e8(SW *psw, GAMEWORLD gameworld)
{
    return g_pgsCur->aws[gameworld].fws & 0x1;
}

int FUN_001dd908(SW *psw, GAMEWORLD gameworld)
{
    return g_pgsCur->aws[gameworld].fws & 0x20;
}

int FUN_001dd928(SW *psw)
{
    return CalculatePercentCompletion(g_pgsCur);
}

extern "C" void FUN_001dd950(SW *psw, int nLow, int nHigh, VECTOR *pposCenter)
{
    int cpdprize = NRandInRange(nLow, nHigh);

    if (cpdprize != 0)
    {
        CpdprizeAttractSwDprizes(g_psw, (CID)0x58, pposCenter, cpdprize, NULL);
    }
}

void FUN_001dd9a0(float nParam)
{
    ChangeSuck(nParam, &g_difficulty);
}

void FUN_001dd9c0(void *pv, float *pu)
{
    *pu = g_plsCur->uSuck;
}

void SetSwPlayerSuck(SW *psw, float uSuck)
{
    g_plsCur->unk_suck_0x10 = GLimitLm(&g_lmZeroOne, uSuck);
}

void GetSwPlayerSuck(SW *psw, float *puSuck)
{
    // TODO: This should be "uSuck"?
    *puSuck = g_plsCur->unk_suck_0x10;
}

void IncrementSwHandsOff(SW *psw)
{
    if (++psw->cHandsOff == 1)
    {
        AddGrfusr(2);
    }
}

void DecrementSwHandsOff(SW *psw)
{
    if (psw->cHandsOff-- == 1)
    {
        RemoveGrfusr(2);
    }
}

int IsSwHandsOff(SW *psw)
{
    return psw->cHandsOff > 0;
}

void IsSwVagPlaying(SW *psw, int *pfPlaying)
{
    *pfPlaying = FVagPlaying();
}

void SetSwDarken(SW *psw, float rDarken)
{
    psw->rDarkenSmooth = rDarken;
    psw->rDarken = rDarken;
}

void SetSwDarkenSmooth(SW *psw, float rDarkenSmooth)
{
    psw->rDarkenSmooth = rDarkenSmooth;
}

void CancelSwDialogPlaying(SW *psw)
{
    if (g_pdialogPlaying && STRUCT_OFFSET(g_pdialogPlaying, 0x2d4, DIALOGS) != 4 &&
       (STRUCT_OFFSET(g_pdialogPlaying, 0x2d0, DIALOGK) - 1u) < 2)
    {
        PopUiActiveBlot(&g_ui);
    }
}

typedef struct
{
    int n;
} __attribute__((packed)) UNALIGNED_INT;

extern PROMPT D_0026FF68;

extern "C" void FUN_001ddb20(SW *psw, PRK prk, int oid)
{
    PROMPT *pprompt = &D_0026FF68;

    STRUCT_OFFSET(pprompt, 0x280, UNALIGNED_INT).n = oid;
    SetPrompt(pprompt, PRP_Basic, prk);
}

extern BLOT D_002721D0;

extern "C" void FUN_001ddb58(SW *psw)
{
    if (++STRUCT_OFFSET(psw, 0x2320, int) == 1)
    {
        SetBlotDtVisible(&D_002721D0, 0.0f);
        D_002721D0.pvtblot->pfnShowBlot(&D_002721D0);
    }
}

extern BLOT D_002721D0;

extern "C" void FUN_001ddbb8(SW *psw)
{
    if (--STRUCT_OFFSET(psw, 0x2320, int) == 0)
    {
        D_002721D0.pvtblot->pfnHideBlot(&D_002721D0);
    }
}
JUNK_WORD(0x0002102a);

EXC *PexcSetExcitement(int gexc);

EXC *FUN_001ddbf8(SW *psw, int gexc)
{
    return PexcSetExcitement(gexc);
}

void UnsetExcitementHyst(EXC *pexc);

void FUN_001ddc18(SW *psw, EXC *pexc)
{
    UnsetExcitementHyst(pexc);
}

void FUN_001ddc38(void *pv, void *pvBlot)
{
    STRUCT_OFFSET(pv, 0x2324, void *) = pvBlot;
}

extern "C" void FUN_001ddc40(void *pv)
{
    typedef void (*PFNBLOT)(void *);

    void *pvBlot = STRUCT_OFFSET(pv, 0x2324, void *); // blot/vtable'd object set by FUN_001ddc38
    if (pvBlot != NULL)
    {
        PFNBLOT pfn = STRUCT_OFFSET(STRUCT_OFFSET(pvBlot, 0x0, void *), 0xC8, PFNBLOT);
        if (pfn != NULL)
        {
            pfn(pvBlot);
        }
    }
}

void FUN_001ddc78(void *pv, int n)
{
    STRUCT_OFFSET(pv, 0x235C, int) |= (1 << n);
}

void FUN_001ddc90(void *pv, int n)
{
    STRUCT_OFFSET(pv, 0x235C, int) &= ~(1 << n);
}

void FUN_001ddcb0(void *pv, int *pccharm)
{
    *pccharm = g_pgsCur->ccharm;
}

void FUN_001ddcc8(void *pv, int *pclife)
{
    *pclife = g_pgsCur->clife;
}
