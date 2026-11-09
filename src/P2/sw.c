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
#include <memory.h>
#include <mark.h>
#include <po.h>
#include <jt.h>
#include <jump.h>
#include <pipe.h>
#include <target.h>
#include <hide.h>
#include <shd.h>
#include <splice/spliceutils.h>
#include <joy.h>
#include <cm.h>
#include <clock.h>
#include <screen.h>

// LsFromWid is still an unmangled INCLUDE_ASM symbol in game.c, so call it by its raw label.
extern int *LsFromWidRaw(WID wid) __asm__("LsFromWid");
typedef void (*PFNLOX)(LO *);
extern SW *g_psw;
extern BLOT D_002721D0;
EXC *PexcSetExcitement(int iexc);
void UnsetExcitementHyst(EXC *pexc);
void SetAMRegister(int reg, unsigned char value);
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

/**
 * @todo ~65% matched. Logic is right; only register allocation and the clamp codegen differ.
 */
INCLUDE_ASM("asm/nonmatchings/P2/sw", SetupBulkDataFromBrx__FiP18CBinaryInputStream);
#ifdef SKIP_ASM
void SetupBulkDataFromBrx(int fLoadBulkData, CBinaryInputStream *pbis)
{
    int cb;
    int nSig;
    if (pbis->m_bisk == BISK_Cd)
    {
        if (!fLoadBulkData)
        {
            pbis->DecrementCdReadLimit(g_cbBulkDataReadAdjustment);
            pbis->m_cbRemaining -= g_cbBulkDataReadAdjustment;
        }
        cb = pbis->S32Read();
        nSig = pbis->S32Read();
    }
    else
    {
        cb = pbis->S32Read();
        nSig = pbis->S32Read();
        if (nSig != g_nBulkDataSig)
            fLoadBulkData = 1;
        if (!fLoadBulkData)
        {
            int c = pbis->m_cbRemaining - g_cbBulkDataReadAdjustment;
            if (c < fLoadBulkData)
                c = fLoadBulkData;
            pbis->m_cbRemaining = c;
        }
    }
    g_pbBulkData = (byte *)PvAllocSwImpl(cb);
    g_nBulkDataSig = nSig;
    g_cbBulkData = cb;
    g_fLoadBulkData = fLoadBulkData;
}
#endif // SKIP_ASM

void LoadBulkDataFromBrx(CBinaryInputStream *pbis)
{
    if (g_fLoadBulkData)
    {
        g_cbBulkDataReadAdjustment = pbis->m_cbRemaining;
        pbis->Align(16);
        pbis->Read(g_cbBulkData, g_pbBulkData);
    }
}

/**
 * @todo 40% matched. The target builds the vector in registers (pextlw/pcpyld) before the quadword store.
 */
INCLUDE_ASM("asm/nonmatchings/P2/sw", SetSwGravity__FP2SWf);
#ifdef SKIP_ASM
void SetSwGravity(SW *psw, float z)
{
    VECTOR v;
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = z;
    v.gUnused = 0.0f;
    STRUCT_OFFSET(psw, 0x1EE0, qword) = *(qword *)&v;
}
#endif // SKIP_ASM

/**
 * @todo 75% matched. Only the argument masking before the call differs (andi vs daddu).
 */
INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dbac0);
#ifdef SKIP_ASM
extern "C" void FUN_001dbac0(SW *psw, int reg, unsigned char value)
{
    SetAMRegister(reg, value);
}
#endif // SKIP_ASM

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
    return (plo->pvtlo->grfcid & 2) && psw->cpsoRoot >= 0xF7 && !fHiPri;
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

/**
 * @todo Code below produces identical instructions (cmp.sh MATCH) but enabling it makes the
 * assembler insert 3 nops in the later INCLUDE_ASM LoadSwFromBrx, which breaks the checksum.
 * Cause unknown, so it stays disabled.
 */
INCLUDE_ASM("asm/nonmatchings/P2/sw", ClearSwCallbacks__FP2SWiPFPv5MSGIDPv_vPv5MSGIDT3);
#ifdef SKIP_ASM
void ClearSwCallbacks(SW *psw, GRFCMQ grfcmq, PFNMQ pfnmq, void *pvContext, MSGID msgid, void *pvCallbackData)
{
    MQ *pmqPrev = 0;
    MQ *pmqRemoved = 0;
    MQ *pmq = psw->pmqCallbackFirst;
    while (pmq)
    {
        MQ *pmqNext = pmq->pmqNext;
        for (int grf = 1; grf < 0x10; grf <<= 1)
        {
            if (grfcmq & grf)
            {
                switch (grf)
                {
                case 1:
                    if (pmq->pfnmq != pfnmq)
                        goto nomatch;
                    break;
                case 2:
                    if (pmq->pvContext != pvContext)
                        goto nomatch;
                    break;
                case 4:
                    if (pmq->msgid != msgid)
                        goto nomatch;
                    break;
                case 8:
                    if (pmq->pvCallbackData != pvCallbackData)
                        goto nomatch;
                    break;
                }
            }
        }
        if (pmqPrev)
            pmqPrev->pmqNext = pmqNext;
        else
            psw->pmqCallbackFirst = pmqNext;
        if (!pmqNext)
            psw->pmqCallbackLast = pmqPrev;
        pmq->pmqNext = pmqRemoved;
        pmqRemoved = pmq;
        goto next;
    nomatch:
        pmqPrev = pmq;
    next:
        pmq = pmqNext;
    }
    FreeSwMqList(psw, pmqRemoved);
}
#endif // SKIP_ASM

void ProcessSwCallbacks(SW *psw)
{
    while (psw->pmqCallbackFirst)
    {
        MQ *pmq = psw->pmqCallbackFirst;
        if (pmq == psw->pmqCallbackLast)
            psw->pmqCallbackLast = 0;
        psw->pmqCallbackFirst = pmq->pmqNext;
        pmq->pmqNext = 0;
        pmq->pfnmq(pmq->pvContext, pmq->msgid, pmq->pvCallbackData);
        FreeSwMqList(psw, pmq);
    }
}

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

void AddSwProxySource(SW *psw, LO *plo, int cpsl)
{
    PSL psl;
    psl.cplo = cpsl - 1;
    if (psl.cplo > 0)
    {
        psl.aplo = (LO **)PvAllocSwImpl(psl.cplo * 4);
        for (int i = 0; i < psl.cplo; i++)
        {
            psl.aplo[i] = PloCloneLo(plo, psw, 0);
        }
    }
    int n = STRUCT_OFFSET(psw, 0x1EFC, int);
    STRUCT_OFFSET(psw, 0x1F00 + n * 8, PSL) = psl;
    STRUCT_OFFSET(psw, 0x1EFC, int) = n + 1;
}

LO *PloGetSwProxySource(SW *psw, int ipsl)
{
    int *p = (int *)((char *)psw + 0x1F00 + ipsl * 8);
    int n = p[0] - 1;
    p[0] = n;
    return ((LO **)p[1])[n];
}

INCLUDE_ASM("asm/nonmatchings/P2/sw", IntersectSwBoundingBox__FP2SWP2SOP6VECTORT2PFPvP2SO_iPvPiPPP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/sw", IntersectSwBoundingSphere__FP2SWP2SOP6VECTORfPFPvP2SO_iPvPiPPP2SO);

void RemoveOxa(OXA *poxa, OXA **ppoxaFirst)
{
    if (poxa->poxaNext)
        poxa->poxaNext->poxaPrev = poxa->poxaPrev;
    if (poxa->poxaPrev)
        poxa->poxaPrev->poxaNext = poxa->poxaNext;
    else
        *ppoxaFirst = poxa->poxaNext;
}

void InitSwAoxa(SW *psw)
{
    STRUCT_OFFSET(psw, 0x1AE4, OXA *) = STRUCT_OFFSET(psw, 0x1AE0, OXA *) = (OXA *)PvAllocSwClearImpl(0x1000);
    for (int i = 0; i < 256; i++)
    {
        OXA *poxa = STRUCT_OFFSET(psw, 0x1AE0, OXA *) + i;
        poxa->poxaPrev = (i > 0) ? poxa - 1 : 0;
        poxa->poxaNext = (i < 255) ? poxa + 1 : 0;
    }
}

void AddOxa(OXA *poxa, OXA **ppoxaFirst)
{
    poxa->poxaNext = *ppoxaFirst;
    poxa->poxaPrev = 0;
    if (*ppoxaFirst)
        (*ppoxaFirst)->poxaPrev = poxa;
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

void FreeSwPoxa(SW *psw, OXA *poxa)
{
    OX *pox = poxa->pox;
    while (pox)
    {
        SO *pso = pox->psoOther;
        OX *poxNext = pox->poxNext;
        OX *poxOther = PoxRemoveSw(psw, STRUCT_OFFSET(pso, 0x480, OXA *), poxa);
        if (pox->pxp)
        {
            FreeSwXpList(psw, pox->pxp);
            if (!(STRUCT_OFFSET(pox->psoOther, 0x538, long) & ((long)0x8000 << 40)))
                ResolveAlo((ALO *)pox->psoOther);
            if (!(STRUCT_OFFSET(poxOther->psoOther, 0x538, long) & ((long)0x8000 << 40)))
                ResolveAlo((ALO *)poxOther->psoOther);
        }
        poxOther->pxp = 0;
        pox->pxp = 0;
        FreeSlotheapPv(&psw->slotheapOx, pox);
        pox = poxNext;
        FreeSlotheapPv(&psw->slotheapOx, poxOther);
    }
    poxa->pox = 0;
    OXA **ppoxaUsed = &STRUCT_OFFSET(psw, 0x1AE8, OXA *);
    OXA **ppoxaFree = &STRUCT_OFFSET(psw, 0x1AE4, OXA *);
    OXA *poxaUsed = *ppoxaUsed;
    int ipoxa = poxa - STRUCT_OFFSET(psw, 0x1AE0, OXA *);
    while (poxaUsed)
    {
        int jpoxa = poxaUsed - STRUCT_OFFSET(psw, 0x1AE0, OXA *);
        byte *pb = STRUCT_OFFSET(psw, 0x1ADC, byte *);
        byte *p1 = pb + jpoxa * 256 + ipoxa;
        byte *p2 = pb + ipoxa * 256 + jpoxa;
        *p1 = 0;
        *p2 = 0;
        poxaUsed = poxaUsed->poxaNext;
    }
    poxa->pso = 0;
    RemoveOxa(poxa, ppoxaUsed);
    AddOxa(poxa, ppoxaFree);
}

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

struct PRIZEQ
{
    CID cid;
    int c;
};
struct PRIZEQS
{
    PRIZEQ a[2];
};
extern PRIZEQS D_0024DC98;
void CreateSwPrizes(SW *psw)
{
    uint i = 0;
    PRIZEQS q = D_0024DC98;
    for (; i < 2; i++)
    {
        DPRIZE *pdprize = (DPRIZE *)psw->dlDprize.head;
        while (pdprize)
        {
            if (STRUCT_OFFSET(pdprize, 0x334, int) == 0 && pdprize->pvtlo->cid == q.a[i].cid)
                break;
            pdprize = STRUCT_OFFSET(pdprize, 0x374, DPRIZE *);
        }
        if (pdprize)
        {
            for (int j = 0; j < q.a[i].c; j++)
            {
                DPRIZE *pdprizeClone = (DPRIZE *)PloCloneLo(pdprize, psw, 0);
                pdprizeClone->dprizesInit = (DPRIZES)2;
                PFNLOX pfn = STRUCT_OFFSET(pdprizeClone->pvtlo, 0x4C, PFNLOX);
                if (pfn)
                    pfn(pdprizeClone);
                STRUCT_OFFSET(pdprizeClone->pvtlo, 0x50, PFNLOX)(pdprizeClone);
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/sw", LoadSwFromBrx__FP2SWP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FClipLineHomogeneous__FP7VECTOR4);

INCLUDE_ASM("asm/nonmatchings/P2/sw", DrawLineWorld__FP6VECTORT0G4RGBAP2CMi);

INCLUDE_ASM("asm/nonmatchings/P2/sw", DrawAxesWorld__FP6VECTORP7MATRIX3fP2CMi);

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

/**
 * @todo 60% matched. Target uses movz on the second flag test.
 */
INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dd710);
#ifdef SKIP_ASM
extern "C" int FUN_001dd710(SW *psw, WID wid)
{
    int fls = GetLevelCompletionById(wid);
    return (fls & 2) && (g_plsCur->fls & 1) ? 1 : 0;
}
#endif // SKIP_ASM

int FUN_001dd758(SW *psw, WID wid)
{
    int fls = GetLevelCompletionById(wid);
    int grf = fls & 3;
    return (fls & 4) && (grf & g_plsCur->fls) == grf;
}

int FUN_001dd7a0(SW *psw, WID wid)
{
    int fls = GetLevelCompletionById(wid);
    int grf = fls & 7;
    return (fls & 8) && (grf & g_plsCur->fls) == grf;
}

struct SCV
{
    int id;
    int value;
};
void FUN_001dd7e8(SW *psw, WID wid, int id, int value)
{
    LS *pls = (LS *)LsFromWidRaw(wid);
    if (pls)
    {
        SCV *pfree = 0;
        SCV *a = (SCV *)((char *)pls + 0x44);
        for (uint i = 0; i < 4; i++)
        {
            SCV *p = &a[i];
            if (!pfree && p->id == 0)
            {
                pfree = p;
                continue;
            }
            if (p->id == id)
            {
                pfree = p;
                break;
            }
        }
        if (pfree)
        {
            pfree->id = id;
            pfree->value = value;
        }
    }
}

int FUN_001dd888(SW *psw, WID wid, int id)
{
    LS *pls = (LS *)LsFromWidRaw(wid);
    if (pls)
    {
        uint i = 0;
        int *p = (int *)((char *)pls + 0x44);
        do
        {
            if (p[0] == id)
                return p[1];
            i++;
            p += 2;
        } while (i < 4);
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

void FUN_001dd928()
{
    CalculatePercentCompletion(g_pgsCur);
}

void FUN_001dd950(SW *psw, int nLow, int nHigh, VECTOR *ppos)
{
    int n = NRandInRange(nLow, nHigh);
    if (n)
        CpdprizeAttractSwDprizes(g_psw, (CID)0x58, ppos, n, 0);
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

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001ddb20);

void FUN_001ddb58(SW *psw)
{
    if (++STRUCT_OFFSET(psw, 0x2320, int) == 1)
    {
        SetBlotDtVisible(&D_002721D0, 0.0f);
        D_002721D0.pvtblot->pfnShowBlot(&D_002721D0);
    }
}

void FUN_001ddbb8(SW *psw)
{
    if (--STRUCT_OFFSET(psw, 0x2320, int) == 0)
        D_002721D0.pvtblot->pfnHideBlot(&D_002721D0);
}
JUNK_WORD(0x0002102a);

void FUN_001ddbf8(void *pv, int n)
{
    PexcSetExcitement(n);
}

void FUN_001ddc18(void *pv, EXC *pexc)
{
    UnsetExcitementHyst(pexc);
}

void FUN_001ddc38(SW *psw, LO *plo)
{
    STRUCT_OFFSET(psw, 0x2324, LO *) = plo;
}

void FUN_001ddc40(SW *psw)
{
    LO *plo = STRUCT_OFFSET(psw, 0x2324, LO *);
    if (plo)
    {
        PFNLOX pfn = STRUCT_OFFSET(plo->pvtlo, 0xC8, PFNLOX);
        if (pfn)
            pfn(plo);
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

void FUN_001ddcb0(void *pv, int *pn)
{
    *pn = g_pgsCur->ccharm;
}

void FUN_001ddcc8(void *pv, int *pn)
{
    *pn = g_pgsCur->clife;
}
