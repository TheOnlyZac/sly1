#include <coin.h>
#include <chkpnt.h>
#include <bis.h>
#include <sw.h>
#include <screen.h>

void InitDprize(DPRIZE *pdprize)
{
    pdprize->dprizesInit = DPRIZES_Normal;
    pdprize->dprizes = DPRIZES_Nil;
    pdprize->svcAttract = 30.0f;
    pdprize->oidInitialState = OID_Nil;
    InitAlo(pdprize);
    AppendDlEntry(&pdprize->psw->dlDprize, pdprize);
    pdprize->ichkCollected = IchkAllocChkmgr(&g_chkmgr);
    pdprize->ficg.grficSmash = '\x10';
    pdprize->ficg.grficRush = '\x10';
    pdprize->ficg.grficSweep = '\x10';
    pdprize->ficg.grficBomb = '\x10';
    pdprize->fLastBounce = 1;
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

INCLUDE_ASM("asm/nonmatchings/P2/coin", PostDprizeLoad__FP6DPRIZE);

INCLUDE_ASM("asm/nonmatchings/P2/coin", ProjectDprizeTransform__FP6DPRIZEfi);

INCLUDE_ASM("asm/nonmatchings/P2/coin", FFilterDprizeObjects__FP6DPRIZEP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/coin", CheckDprizeBounce__FP6DPRIZE);

INCLUDE_ASM("asm/nonmatchings/P2/coin", CheckDprizeCollect__FP6DPRIZE);

INCLUDE_ASM("asm/nonmatchings/P2/coin", FAbsorbDprizeWkr__FP6DPRIZEP3WKR);

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

extern "C" {
void FUN_00147ed0(DPRIZE *pdprize)
{
    (*(void (**)(DPRIZE *, DPRIZES))((char *)pdprize->pvtlo + 0xCC))(pdprize, DPRIZES_Removed);
}
}

INCLUDE_ASM("asm/nonmatchings/P2/coin", FUN_00147ef8);

INCLUDE_ASM("asm/nonmatchings/P2/coin", UpdateCoin__FP4COINf);

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

INCLUDE_ASM("asm/nonmatchings/P2/coin", OnCoinSmack__FP4COIN);
#ifdef SKIP_ASM
/**
 * @todo 91.21% matched.
 */
void OnCoinSmack(COIN *pcoin)
{
    g_pgsCur->ccoin++;

    if (g_pgsCur->ccoin < 100)
        return;

    if (g_pgsCur->ccharm < CcharmMost())
    {
        // Give the player a charm and reset the coin count
        g_pgsCur->ccoin = 0;
        g_coinctr.dgDisplayMax = 250.0f;
        g_coinctr.pfnsmack = CreateSwCharm;
        g_coinctr.pv = pcoin->psw;
    }
    else
    {
        if (g_pgsCur->clife < 99)
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
}
#endif

INCLUDE_ASM("asm/nonmatchings/P2/coin", SetCoinDprizes__FP4COIN7DPRIZES);

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
    // if (pcharm->dprizes == dprizes)
    if (STRUCT_OFFSET(pcharm, 0x2d0, DPRIZES) == dprizes)
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

INCLUDE_ASM("asm/nonmatchings/P2/coin", SetKeyDprizes__FP3KEY7DPRIZES);

INCLUDE_ASM("asm/nonmatchings/P2/coin", FUN_00148698);

void PostDprizeLoad(DPRIZE *pdprize);

extern "C" void FUN_00148718(DPRIZE *pdprize)
{
    PostDprizeLoad(pdprize);
    STRUCT_OFFSET(&g_note, 0x270, DPRIZE *) = pdprize;
}

extern "C" {
void FUN_00148748(void *param_1)
{
    (*(void (**)(void *, int))(*(int *)param_1 + 0xCC))(param_1, 2);
}
}

INCLUDE_ASM("asm/nonmatchings/P2/coin", FUN_00148770);

INCLUDE_ASM("asm/nonmatchings/P2/coin", FUN_00148828);

INCLUDE_ASM("asm/nonmatchings/P2/coin", FUN_00148888);

int FUN_00148910(float *pf0, float *pf1)
{
    return (*pf0 < *pf1) ? 1 : -1;
}

INCLUDE_ASM("asm/nonmatchings/P2/coin", FUN_00148938);

INCLUDE_ASM("asm/nonmatchings/P2/coin", CpdprizeAttractSwDprizes__FP2SW3CIDP6VECTORiPP6DPRIZE);

INCLUDE_ASM("asm/nonmatchings/P2/coin", RemoveSwExtraneousCharms__FP2SW);

INCLUDE_ASM("asm/nonmatchings/P2/coin", FUN_00148d90);

extern "C" {
void FUN_00148e18(void *param_1)
{
    (*(void (**)(void *, int))(*(int *)param_1 + 0xCC))(param_1, 2);
}
}

INCLUDE_ASM("asm/nonmatchings/P2/coin", FUN_00148e40);

INCLUDE_ASM("asm/nonmatchings/P2/coin", FUN_00148ef8);

INCLUDE_ASM("asm/nonmatchings/P2/coin", increment_and_show_life_count);

INCLUDE_ASM("asm/nonmatchings/P2/coin", CollectLifetkn__FP7LIFETKN);

void FUN_00149168(DPRIZE *param_1)
{
    InitDprize(param_1);
    *(int *)((uint8_t *)param_1 + 0x340) = 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/coin", break_bottle);
