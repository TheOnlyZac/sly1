#include <sw.h>
#include <ui.h>
#include <frm.h>
#include <util.h>
#include <sound.h>
#include <dialog.h>
#include <989snd.h>
#include <sce/memset.h>

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

INCLUDE_ASM("asm/nonmatchings/P2/sw", SetSwGravity__FP2SWf);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dbac0);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dbae0);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dbb00);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FOverflowSwLo__FP2SWP2LOi);

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

INCLUDE_ASM("asm/nonmatchings/P2/sw", AddSwProxySource__FP2SWP2LOi);

INCLUDE_ASM("asm/nonmatchings/P2/sw", PloGetSwProxySource__FP2SWi);

INCLUDE_ASM("asm/nonmatchings/P2/sw", IntersectSwBoundingBox__FP2SWP2SOP6VECTORT2PFPvP2SO_iPvPiPPP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/sw", IntersectSwBoundingSphere__FP2SWP2SOP6VECTORfPFPvP2SO_iPvPiPPP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/sw", RemoveOxa__FP3OXAPP3OXA);

INCLUDE_ASM("asm/nonmatchings/P2/sw", InitSwAoxa__FP2SW);

INCLUDE_ASM("asm/nonmatchings/P2/sw", AddOxa__FP3OXAPP3OXA);

INCLUDE_ASM("asm/nonmatchings/P2/sw", PoxaAllocSw__FP2SWP2SO);

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

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dd710);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dd758);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dd7a0);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dd7e8);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dd888);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dd8e8);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dd908);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dd928);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dd950);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dd9a0);

INCLUDE_ASM("asm/nonmatchings/P2/sw", FUN_001dd9c0);

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
