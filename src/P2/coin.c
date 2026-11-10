#include <coin.h>
#include <chkpnt.h>
#include <bis.h>
#include <sw.h>
#include <clock.h>
#include <mq.h>
#include <sm.h>
#include <screen.h>
#include <game.h>
#include <basic.h>
#include <rip.h>
#include <util.h>
#include <sound.h>
#include <po.h>
#include <difficulty.h>
#include <memcard.h>
#include <so.h>
#include <find.h>
#include <cid.h>

extern "C" void func_001E02C8(void *, int);
extern int D_00270458;
extern int D_00275C34;
extern char D_00261AD0[]; // unknown, rip vtable?
extern char D_00261B60[]; // unknown, rip vtable?

// Packed so stores compile to swl/swr like the original OnCoinSmack.
struct UNALIGNED_FLOAT
{
    float f;
} __attribute__((packed));

void InitDprize(DPRIZE *pdprize)
{
    pdprize->dprizesInit = DPRIZES_Normal;
    pdprize->svcAttract = 30.0f;
    pdprize->oidInitialState = OID_Nil;
    pdprize->dprizes = DPRIZES_Nil;
    InitAlo(pdprize);
    AppendDlEntry(&pdprize->psw->dlDprize, pdprize);
    pdprize->ichkCollected = IchkAllocChkmgr(&g_chkmgr);
    pdprize->ficg.grficSmash = 0x10;
    pdprize->ficg.grficRush = 0x10;
    pdprize->ficg.grficSweep = 0x10;
    pdprize->ficg.grficBomb = 0x10;
    pdprize->fUnknown = 1;
}

void LoadDprizeFromBrx(DPRIZE *pdprize, CBinaryInputStream *pbis)
{
    SetAloTargetHitTest(pdprize, 1);
    LoadAloFromBrx(pdprize, pbis);
    SnipAloObjects(pdprize, 5, s_asnipDprize);
}

void CloneDprize(DPRIZE *pdprize, DPRIZE *pdprizeBase)
{
    int ichkCollected = pdprize->ichkCollected;
    DLE dle = pdprize->dle;
    CloneAlo(pdprize, pdprizeBase);
    pdprize->dle = dle;
    pdprize->ichkCollected = ichkCollected;
}

void PostDprizeLoad(DPRIZE *pdprize)
{
    PostAloLoad(pdprize);
    pdprize->ptarget = (TARGET *)PloFindSwObjectByClass(pdprize->psw, 1, (CID)0x75, pdprize);
    if (pdprize->ptarget)
    {
        pdprize->ptarget->pvtlo->pfnRemoveLo(pdprize->ptarget);
    }
    if (((g_pgsCur->gameworldCur << 8) | g_pgsCur->worldlevelCur) != 0x308 &&
        FGetChkmgrIchk(&g_chkmgr, pdprize->ichkCollected))
    {
        pdprize->dprizesInit = DPRIZES_Removed;
    }
    PVTDPRIZE(pdprize)->pfnSetDprizeDprizes(pdprize, pdprize->dprizesInit);
}

INCLUDE_ASM("asm/nonmatchings/P2/coin", ProjectDprizeTransform__FP6DPRIZEfi);

int FFilterDprizeObjects(DPRIZE *pdprize, SO *pso)
{
    if ((STRUCT_OFFSET(pso, 0x538, uint64_t) & 0x80000000000) || FIsBasicDerivedFrom(pso->paloRoot, CID_PO) ||
        FIsBasicDerivedFrom(pso->paloRoot, CID_SWP) || FIsBasicDerivedFrom(pso->paloRoot, CID_TZP) ||
        FIsBasicDerivedFrom(pso->paloRoot, CID_MISSILE) || FIsBasicDerivedFrom(pso->paloRoot, CID_SQUISH))
        return 0;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/P2/coin", CheckDprizeBounce__FP6DPRIZE);

INCLUDE_ASM("asm/nonmatchings/P2/coin", CheckDprizeCollect__FP6DPRIZE);

int FAbsorbDprizeWkr(DPRIZE *pdprize, WKR *pwkr)
{
    if (pdprize->fUnknown && (pwkr->grfic & 0x10))
    {
        PVTDPRIZE(pdprize)->pfnSetDprizeDprizes(pdprize, DPRIZES_Collect);
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/P2/coin", UpdateDprize__FP6DPRIZEf);

INCLUDE_ASM("asm/nonmatchings/P2/coin", RenderDprizeAll__FP6DPRIZEP2CMP2RO);

INCLUDE_ASM("asm/nonmatchings/P2/coin", SetDprizeDprizes__FP6DPRIZE7DPRIZES);

void InitCoin(COIN *pcoin)
{
    InitDprize(pcoin);
    pcoin->sRadiusBounce = 45.0f;
    pcoin->svLastBounceMax = 250.0f;
    pcoin->sRadiusCollect = 50.0f;
    pcoin->svLastBounce = 50.0f;
    pcoin->rxyBounce = 0.6f;
    pcoin->rzBounce = 0.75f;
    pcoin->uGlintChance = 0.25f;
    pcoin->lmDtMaxLifetime.gMin = 8.0f;
    pcoin->lmDtMaxLifetime.gMax = 10.0f;
}

void FUN_00147ed0(COIN *pcoin)
{
    PVTDPRIZE(pcoin)->pfnSetDprizeDprizes(pcoin, DPRIZES_Removed);
}

void FUN_00147ef8(COIN *pcoin, MSGID msgid, void *pv)
{
    HandleAloMessage(pcoin, msgid, pv);
    if (msgid == MSGID_sma_transition && pv == pcoin->psma)
    {
        OID oid;
        GetSmaCur((SMA *)pv, &oid);
        if (oid == (OID)0x263)
        {
            void *pobj = STRUCT_OFFSET(pcoin->psw, 0x1d60, void *);
            if (pobj)
            {
                int args[20];
                args[1] = (int)pcoin;
                args[0] = 1;
                (*(void (***)(void *, void *))pobj)[0x7c / 4](pobj, args);
            }
            PostSwCallback(pcoin->psw, (PFNMQ)FUN_00147ed0, pcoin, MSGID_callback, 0);
        }
    }
}

void UpdateCoin(COIN *pcoin, float dt)
{
    UpdateDprize(pcoin, dt);
    if (pcoin->dprizes == DPRIZES_Normal && pcoin->fReuseCandidate)
    {
        if (D_00270458 != 2)
        {
            pcoin->tLose -= g_clock.dt;
        }
        if (pcoin->tLose <= 0.0f)
        {
            PVTDPRIZE(pcoin)->pfnSetDprizeDprizes(pcoin, DPRIZES_Lose);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/coin", CreateSwCharm__FP2SW);

void AddLife(void *ptr)
{
    int new_clife = g_pgsCur->clife + 1;
    int capped_clife = 99;
    if (new_clife < 99)
    {
        capped_clife = new_clife;
    }
    g_pgsCur->clife = capped_clife;
}

void OnCoinSmack(COIN *pcoin)
{
    if (++g_pgsCur->ccoin < 100)
        return;

    if (g_pgsCur->ccharm < CcharmMost())
    {
        // Give the player a charm and reset the coin count
        g_pgsCur->ccoin = 0;
        COINCTR *pcoinctr = &g_coinctr;
        ((UNALIGNED_FLOAT *)&pcoinctr->dgDisplayMax)->f = 250.0f; // swl/swr store
        pcoinctr->pfnsmack = CreateSwCharm;
        pcoinctr->pv = pcoin->psw;
    }
    else if (g_pgsCur->clife < 99)
    {
        // Give the player a life and reset the coin count
        g_pgsCur->ccoin = 0;
        g_coinctr.dgDisplayMax = 250.0f;
        g_coinctr.pv = NULL;
        g_coinctr.pfnsmack = AddLife;
        g_lifectr.pvtblot->pfnShowBlot(&g_lifectr);
    }
    else
    {
        // Clamp coin count to 99
        g_pgsCur->ccoin = 99;
    }
}

void SetCoinDprizes(COIN *pcoin, DPRIZES dprizes)
{
    if (pcoin->dprizes == dprizes)
        return;

    switch (dprizes)
    {
    case DPRIZES_Normal:
        if (pcoin->fReuseCandidate)
        {
            pcoin->tLose = GRandInRange(pcoin->lmDtMaxLifetime.gMin, pcoin->lmDtMaxLifetime.gMax);
        }
        break;
    case DPRIZES_Collect:
    {
        RIP *prip = PripNewRipg(RIPT_Smack, 0);
        if (prip)
        {
            STRUCT_OFFSET(prip, 0x134, COIN *) = pcoin;
            STRUCT_OFFSET(prip, 0x130, void *) = &D_00261AD0;
            (*(void (***)(RIP *, float, void *, int))prip)[0](prip, 1.0f, (char *)pcoin + 0x140, 0);
            STRUCT_OFFSET(prip, 0x20, COIN *) = pcoin;
            STRUCT_OFFSET(prip, 0x50, qword) = STRUCT_OFFSET(pcoin, 0x110, qword);
            STRUCT_OFFSET(prip, 0x60, qword) = STRUCT_OFFSET(pcoin, 0x120, qword);
            STRUCT_OFFSET(prip, 0x70, qword) = STRUCT_OFFSET(pcoin, 0x130, qword);
        }
        else
        {
            OnCoinSmack(pcoin);
        }
        g_coinctr.pvtblot->pfnShowBlot(&g_coinctr);
        StartSound(SFXID_Collect_Coin, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        if (pcoin->pexplCollect)
        {
            int args[20];
            args[1] = (int)pcoin;
            args[0] = 1;
            (*(void (***)(void *, void *))pcoin->pexplCollect)[0x7c / 4](pcoin->pexplCollect, args);
        }
        dprizes = DPRIZES_Removed;
        break;
    }
    }
    SetDprizeDprizes(pcoin, dprizes);
}

void InitCharm(CHARM *pcharm)
{
    InitDprize(pcharm);
    pcharm->sRadiusBounce = 60.0f;
    pcharm->sRadiusCollect = 60.0f;
    pcharm->svLastBounceMax = 300.0f;
    pcharm->svLastBounce = 0.0f;
    pcharm->rxyBounce = 0.75f;
    pcharm->rzBounce = 0.5f;
    pcharm->uGlintChance = 0.35f;
}

void SetCharmDprizes(CHARM *pcharm, DPRIZES dprizes)
{
    if (pcharm->dprizes == dprizes)
        return;

    if (dprizes == DPRIZES_Collect)
    {
        dprizes = DPRIZES_Swirl;
        StartSound(SFXID_Collect_Charm, NULL, pcharm, NULL, 1500.0f, 0.0f, 1, 0.0f, 0.0f, NULL,
                   NULL);
        HandleLoSpliceEvent(pcharm, 2, 0, NULL);
    }

    SetDprizeDprizes(pcharm, dprizes);
}

void InitKey(KEY *pkey)
{
    InitDprize(pkey);
    pkey->sRadiusBounce = 35.0f;
    pkey->sRadiusCollect = 35.0f;
    pkey->svLastBounceMax = 500.0f;
    pkey->svLastBounce = 250.0f;
    pkey->rxyBounce = 0.6f;
    pkey->rzBounce = 0.6f;
    pkey->uGlintChance = 0.75f;

    if (g_plsCur->fls & FLS_KeyCollected)
    {
        pkey->dprizesInit = DPRIZES_Removed;
    }
}

void SetKeyDprizes(KEY *pkey, DPRIZES dprizes)
{
    if (pkey->dprizes == dprizes)
        return;

    if (dprizes == DPRIZES_Collect)
    {
        if (!(g_plsCur->fls & FLS_KeyCollected))
        {
            g_plsCur->fls = (FLS)(g_plsCur->fls | FLS_KeyCollected);
            int ckey = g_pwsCur->ckey;
            g_pwsCur->ckey = ckey + 1;
            if (D_00275C34)
                g_pwsCur->ckey = ckey;
        }
        g_keyctr.pvtblot->pfnShowBlot(&g_keyctr);
        PO *ppo = PpoCur();
        if (ppo)
        {
            (*(void (***)(PO *, int, KEY *))ppo)[0x148 / 4](ppo, 0, pkey);
        }
        HandleLoSpliceEvent(pkey, 2, 0, 0);
        dprizes = DPRIZES_Removed;
        OnDifficultyCollectKey(&g_difficulty);
        FUN_0018c7f8(&g_save);
    }
    SetDprizeDprizes(pkey, dprizes);
}

void FUN_00148698(DPRIZE *pdprize)
{
    InitDprize(pdprize);
    pdprize->sRadiusBounce = 60.0f;
    pdprize->sRadiusCollect = 60.0f;
    pdprize->svLastBounceMax = 500.0f;
    pdprize->svLastBounce = 250.0f;
    pdprize->rxyBounce = 0.6f;
    pdprize->rzBounce = 0.6f;
    pdprize->uGlintChance = 0.75f;
    if (STRUCT_OFFSET(&g_note, 0x268, int) == 0)
    {
        pdprize->dprizesInit = DPRIZES_Removed;
    }
}

void FUN_00148718(DPRIZE *pdprize)
{
    PostDprizeLoad(pdprize);
    STRUCT_OFFSET(&g_note, 0x270, DPRIZE *) = pdprize;
}

void FUN_00148748(DPRIZE *pdprize)
{
    PVTDPRIZE(pdprize)->pfnSetDprizeDprizes(pdprize, DPRIZES_Removed);
}

void FUN_00148770(DPRIZE *pdprize, MSGID msgid, void *pv)
{
    HandleAloMessage(pdprize, msgid, pv);
    if (msgid == MSGID_sma_transition && pv == pdprize->psma)
    {
        OID oid;
        GetSmaCur((SMA *)pv, &oid);
        if (oid == (OID)0x263)
        {
            void *pobj = STRUCT_OFFSET(pdprize->psw, 0x1d60, void *);
            if (pobj)
            {
                int args[20];
                args[1] = (int)pdprize;
                args[0] = 1;
                (*(void (***)(void *, void *))pobj)[0x7c / 4](pobj, args);
            }
            PostSwCallback(pdprize->psw, (PFNMQ)FUN_00148748, pdprize, MSGID_callback, 0);
        }
    }
}

void FUN_00148828(DPRIZE *pdprize, float dt)
{
    UpdateDprize(pdprize, dt);
    if (pdprize->dprizes == DPRIZES_Normal && STRUCT_OFFSET(pdprize->psw, 0x2308, float) <= g_clock.t)
    {
        PVTDPRIZE(pdprize)->pfnSetDprizeDprizes(pdprize, DPRIZES_Lose);
    }
}

void FUN_00148888(DPRIZE *pdprize, DPRIZES dprizes)
{
    if (pdprize->dprizes == dprizes)
        return;

    if (dprizes == DPRIZES_Collect)
    {
        func_001E02C8(&g_note, 2);
        if (pdprize->pexplCollect)
        {
            int args[20];
            args[0] = dprizes;
            args[1] = (int)pdprize;
            (*(void (***)(void *, void *))pdprize->pexplCollect)[0x7c / 4](pdprize->pexplCollect, args);
        }
        dprizes = DPRIZES_Removed;
    }
    SetDprizeDprizes(pdprize, dprizes);
}

int SgnCompareSdprize(const void *pv1, const void *pv2)
{
    return (*(float *)pv1 < *(float *)pv2) ? 1 : -1;
}

INCLUDE_ASM("asm/nonmatchings/P2/coin", FUN_00148938);

INCLUDE_ASM("asm/nonmatchings/P2/coin", CpdprizeAttractSwDprizes__FP2SW3CIDP6VECTORiPP6DPRIZE);

void RemoveSwExtraneousCharms(SW *psw)
{
    GS *pgs = g_pgsCur;
    if (((pgs->gameworldCur << 8) | pgs->worldlevelCur) == 0x308)
        return;

    if (pgs->ccharm < CcharmMost() && STRUCT_OFFSET(&g_note, 0x260, int) < 2)
        return;

    // 0x56 is the release CID for CHARM (header enum differs)
    for (DPRIZE *pdprize = (DPRIZE *)psw->dlDprize.head; pdprize != 0; pdprize = (DPRIZE *)pdprize->dle.next)
    {
        if (FIsBasicDerivedFrom(pdprize, (CID)0x56))
        {
            PVTDPRIZE(pdprize)->pfnSetDprizeDprizes(pdprize, DPRIZES_Removed);
        }
    }
}

/**
 * @todo 98% matched (2 differing lines of 38): svLastBounce store is scheduled after sRadiusCollect.
 */
INCLUDE_ASM("asm/nonmatchings/P2/coin", FUN_00148d90__FP7LIFETKN);
#ifdef SKIP_ASM
void FUN_00148d90(LIFETKN *plifetkn)
{
    InitDprize(plifetkn);
    plifetkn->sRadiusBounce = 45.0f;
    plifetkn->svLastBounce = 50.0f;
    plifetkn->svLastBounceMax = 250.0f;
    plifetkn->rxyBounce = 0.05f;
    plifetkn->rzBounce = 0.5f;
    plifetkn->lmDtMaxLifetime.gMin = 4.0f;
    plifetkn->sRadiusCollect = 50.0f;
    plifetkn->uGlintChance = 0.0f;
    plifetkn->lmDtMaxLifetime.gMax = 6.0f;
}
#endif

void FUN_00148e18(LIFETKN *plifetkn)
{
    PVTDPRIZE(plifetkn)->pfnSetDprizeDprizes(plifetkn, DPRIZES_Removed);
}

void FUN_00148e40(LIFETKN *plifetkn, MSGID msgid, void *pv)
{
    HandleAloMessage(plifetkn, msgid, pv);
    if (msgid == MSGID_sma_transition && pv == plifetkn->psma)
    {
        OID oid;
        GetSmaCur((SMA *)pv, &oid);
        if (oid == (OID)0x263)
        {
            void *pobj = STRUCT_OFFSET(plifetkn->psw, 0x1d60, void *);
            if (pobj)
            {
                int args[20];
                args[1] = (int)plifetkn;
                args[0] = 1;
                (*(void (***)(void *, void *))pobj)[0x7c / 4](pobj, args);
            }
            PostSwCallback(plifetkn->psw, (PFNMQ)FUN_00148e18, plifetkn, MSGID_callback, 0);
        }
    }
}

void FUN_00148ef8(LIFETKN *plifetkn, float dt)
{
    UpdateDprize(plifetkn, dt);
    if (plifetkn->dprizes == DPRIZES_Normal && plifetkn->fReuseCandidate)
    {
        if (D_00270458 != 2)
        {
            plifetkn->tLose -= g_clock.dt;
        }
        if (plifetkn->tLose <= 0.0f)
        {
            PVTDPRIZE(plifetkn)->pfnSetDprizeDprizes(plifetkn, DPRIZES_Lose);
        }
    }
}

void increment_and_show_life_count(void *pv)
{
    g_lifectr.pvtblot->pfnShowBlot(&g_lifectr);
    int clife = g_pgsCur->clife;
    if (clife < 99)
    {
        g_pgsCur->clife = clife + 1;
        g_lifectr.dgDisplayMax = 250.0f;
        g_lifectr.pfnsmack = 0;
        g_lifectr.pv = 0;
    }
    else
    {
        g_pgsCur->clife = 99;
    }
}

void SetLifetknDprizes(LIFETKN *plifetkn, DPRIZES dprizes)
{
    if (plifetkn->dprizes == dprizes)
        return;

    switch (dprizes)
    {
    case DPRIZES_Normal:
        if (plifetkn->fReuseCandidate)
        {
            plifetkn->tLose = GRandInRange(plifetkn->lmDtMaxLifetime.gMin, plifetkn->lmDtMaxLifetime.gMax);
        }
        break;
    case DPRIZES_Collect:
    {
        RIP *prip = PripNewRipg(RIPT_Smack, 0);
        if (prip)
        {
            STRUCT_OFFSET(prip, 0x134, LIFETKN *) = plifetkn;
            STRUCT_OFFSET(prip, 0x130, void *) = &D_00261B60;
            (*(void (***)(RIP *, float, void *, int))prip)[0](prip, 1.0f, (char *)plifetkn + 0x140, 0);
            STRUCT_OFFSET(prip, 0x20, LIFETKN *) = plifetkn;
            STRUCT_OFFSET(prip, 0x50, qword) = STRUCT_OFFSET(plifetkn, 0x110, qword);
            STRUCT_OFFSET(prip, 0x60, qword) = STRUCT_OFFSET(plifetkn, 0x120, qword);
            STRUCT_OFFSET(prip, 0x70, qword) = STRUCT_OFFSET(plifetkn, 0x130, qword);
        }
        else
        {
            increment_and_show_life_count(plifetkn);
        }
        g_lifectr.pvtblot->pfnShowBlot(&g_lifectr);
        SetChkmgrIchk(&g_chkmgr, plifetkn->ichkCollected);
        StartSound(SFXID_Collect_Life, 0, 0, 0, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, 0, 0);
        if (plifetkn->pexplCollect)
        {
            int args[20];
            args[1] = (int)plifetkn;
            args[0] = 1;
            (*(void (***)(void *, void *))plifetkn->pexplCollect)[0x7c / 4](plifetkn->pexplCollect, args);
        }
        dprizes = DPRIZES_Removed;
        break;
    }
    }
    SetDprizeDprizes(plifetkn, dprizes);
}

void FUN_00149168(DPRIZE *pdprize)
{
    InitDprize(pdprize);
    pdprize->fUnknown = 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/coin", break_bottle);
