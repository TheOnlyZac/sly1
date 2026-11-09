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
#include <brx.h>
#include <light.h>

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

/**
 * @todo ~97% matched (DIFFCOUNT 4). Only the order of three trailing stores differs (0x2354, 0x234C, 0x2350).
 */
INCLUDE_ASM("asm/nonmatchings/P2/sw", InitSw__FP2SW);
#ifdef SKIP_ASM
void SetSwDefaultReverb(SW *psw, REVERBK reverbk, int k);
#define SWSH(off) ((SLOTHEAP *)((char *)psw + (off)))
void InitSw(SW *psw)
{
    InitLo(psw);
    SetSwDefaultReverb(psw, REVERBK_None, 0);
    STRUCT_OFFSET(psw, 0x1AD8, void *) = PvAllocSwImpl(0x4800);
    STRUCT_OFFSET(psw, 0x1ADC, void *) = PvAllocSwClearImpl(0x10000);
    InitSwAoxa(psw);
    CreateSlotheapSw(SWSH(0x1AF0), 0x10, 0x400);
    CreateSlotheapSw(SWSH(0x1AFC), 0xE0, 0x100);
    CreateSlotheapSw(SWSH(0x1B08), 0x10, 0x80);
    CreateSlotheapSw(SWSH(0x1B14), 0x14, 0x400);
    CreateSlotheapSw(SWSH(0x1B2C), 0x140, 0x180);
    CreateSlotheapSwAlign64(SWSH(0x1B40), 0x10C0, 0x80);
    CreateSlotheapSw(SWSH(0x1B4C), 0x580, 0x20);
    CreateSlotheapSw(SWSH(0x1B58), 0xEC, 0x100);
    CreateSlotheapSw(SWSH(0x1B20), 0xD0, 0x400);
    CreateSlotheapSw(SWSH(0x1BA0), 0x90, 0x80);
    CreateSlotheapSw(SWSH(0x1BB8), 0xC, 0x20);
    CreateSlotheapSw(SWSH(0x1B88), 0x40, 0x100);
    CreateSlotheapSw(SWSH(0x1BF4), 0x2E0, 0x20);
    CreateSlotheapSw(SWSH(0x1BD0), 0x70, 0x20);
    CreateSlotheapSw(SWSH(0x1C0C), 0x8, 0x80);
    CreateSlotheapSw(SWSH(0x1C18), 0x14, 0x100);
    STRUCT_OFFSET(psw, 0x1ED4, void *) = PvAllocSwImpl(0x1000);
    InitDl(&psw->dlChild, 0x1C);
    InitDl(&psw->dlMRD, 0x48);
    InitDl(&psw->dlMRDRealClock, 0x48);
    InitDl(&psw->dlBusy, 0x40);
    InitDl(&psw->dlBusySo, 0x414);
    InitDl(&psw->dlRoot, 0x2D0);
    InitDl(&STRUCT_OFFSET(psw, 0x1B64, DL), 0x34);
    InitDl(&STRUCT_OFFSET(psw, 0x1B70, DL), 0x34);
    InitDl(&psw->dlAsegaPending, 0x34);
    InitDl(&psw->dlSma, 0x10);
    InitDl(&STRUCT_OFFSET(psw, 0x1BAC, DL), 0x64);
    InitDl(&STRUCT_OFFSET(psw, 0x1BC4, DL), 0x4);
    InitDl(&psw->dlLight, 0x410);
    InitDl(&STRUCT_OFFSET(psw, 0x1C00, DL), 0xB8);
    InitDl(&STRUCT_OFFSET(psw, 0x1BDC, DL), 0x64);
    InitDl(&psw->dlProxy, 0x2DC);
    InitDl(&psw->dlFly, 0x5DC);
    InitDl(&psw->dlDprize, 0x374);
    InitDl(&psw->dlRat, 0x600);
    InitDl(&psw->dlRathole, 0x90);
    InitDl(&psw->dlDartFree, 0x56C);
    InitDl(&psw->dlSpire, 0x50);
    InitDl(&psw->dlRail, 0x38);
    InitDl(&psw->dlLanding, 0x38);
    InitDl(&psw->dlBusyLasen, 0xAF0);
    InitDl(&psw->dlBlipg, 0x630);
    InitDl(&psw->dlBlipgFree, 0x630);
    InitDl(&psw->dlFader, 0xC);
    InitDl(&psw->dlRealClockFader, 0xC);
    InitDl(&psw->dlCrfod, 0xC10);
    InitDl(&STRUCT_OFFSET(psw, 0x1CD8, DL), 0x34);
    SetSwGravity(psw, (g_grfcht & 4) ? -900.0f : -1500.0f);
    STRUCT_OFFSET(psw, 0x1D64, byte) = 0x10;
    STRUCT_OFFSET(psw, 0x1D65, byte) = 0x10;
    STRUCT_OFFSET(psw, 0x1D66, byte) = 0x40;
    STRUCT_OFFSET(psw, 0x1D68, float) = 50.0f;
    STRUCT_OFFSET(psw, 0x1D70, int) = -1;
    STRUCT_OFFSET(psw, 0x1D74, int) = 0;
    STRUCT_OFFSET(psw, 0x2308, float) = 15.0f;
    STRUCT_OFFSET(psw, 0x230C, float) = 180.0f;
    psw->rDarkenSmooth = 1.0f;
    STRUCT_OFFSET(psw, 0x2354, int) = 1;
    psw->rDarken = 1.0f;
    STRUCT_OFFSET(psw, 0x235C, int) = 0xF03FFFFF;
}
#endif // SKIP_ASM

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

extern int g_grfdfl;
extern VECTOR g_vecHighlight;
extern float g_degHighlight;
extern float g_gMidtone;
extern float g_degMidtone;
extern float g_gShadow;
extern float g_degShadow;
extern VECTOR D_00275670;
extern VECTOR D_00275680;
extern LM D_00275690;
extern LM D_00275698;
extern LM D_002756A0;
typedef void (*PFNLIGHTVEC)(LIGHT *, VECTOR *);
void CreateSwDefaultLights(SW *psw)
{
    LIGHT *plight;
    if (g_grfdfl & 1)
    {
        plight = (LIGHT *)PloNew((CID)0x51, psw, 0, (OID)0x201, -1);
        SetLightHighlightColor(plight, &g_vecHighlight);
        SetLightHighlightAngle(plight, g_degHighlight);
        SetLightMidtoneStrength(plight, g_gMidtone);
        SetLightMidtoneAngle(plight, g_degMidtone);
        SetLightShadowStrength(plight, g_gShadow);
        SetLightShadowAngle(plight, g_degShadow);
        SetLightDirection(plight, &D_00275670);
    }
    if (g_grfdfl & 2)
    {
        plight = (LIGHT *)PloNew((CID)0x51, psw, 0, (OID)0x201, -1);
        SetLightKind(plight, (LIGHTK)1);
        SetLightHighlightColor(plight, &g_vecHighlight);
        SetLightHighlightAngle(plight, g_degHighlight);
        SetLightMidtoneStrength(plight, g_gMidtone);
        SetLightMidtoneAngle(plight, g_degMidtone);
        SetLightShadowStrength(plight, g_gShadow);
        SetLightShadowAngle(plight, g_degShadow);
        SetLightFallOff(plight, &D_00275690);
        STRUCT_OFFSET(plight->pvtlo, 0x84, PFNLIGHTVEC)(plight, &D_00275680);
    }
    if (g_grfdfl & 4)
    {
        plight = (LIGHT *)PloNew((CID)0x51, psw, 0, (OID)0x201, -1);
        SetLightKind(plight, (LIGHTK)2);
        SetLightHighlightColor(plight, &g_vecHighlight);
        SetLightHighlightAngle(plight, g_degHighlight);
        SetLightMidtoneStrength(plight, g_gMidtone);
        SetLightMidtoneAngle(plight, g_degMidtone);
        SetLightShadowStrength(plight, g_gShadow);
        SetLightShadowAngle(plight, g_degShadow);
        SetLightDirection(plight, &D_00275670);
        SetLightFallOff(plight, &D_00275698);
        STRUCT_OFFSET(plight->pvtlo, 0x84, PFNLIGHTVEC)(plight, &D_00275680);
    }
    if (g_grfdfl & 8)
    {
        plight = (LIGHT *)PloNew((CID)0x51, psw, 0, (OID)0x201, -1);
        SetLightKind(plight, (LIGHTK)3);
        SetLightHighlightColor(plight, &g_vecHighlight);
        SetLightHighlightAngle(plight, g_degHighlight);
        SetLightMidtoneStrength(plight, g_gMidtone);
        SetLightMidtoneAngle(plight, g_degMidtone);
        SetLightShadowStrength(plight, g_gShadow);
        SetLightShadowAngle(plight, g_degShadow);
        SetLightDirection(plight, &D_00275670);
        SetLightFallOff(plight, &D_002756A0);
        STRUCT_OFFSET(plight->pvtlo, 0x84, PFNLIGHTVEC)(plight, &D_00275680);
    }
}

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
