#include <coin.h>
#include <chkpnt.h>

void InitDprize(DPRIZE *pdprize)
{
    pdprize->dprizesInit = DPRIZES_Normal;
    pdprize->dprizes = DPRIZES_Nil;
    pdprize->svcAttract = 30.0;
    pdprize->oidInitialState = OID_Nil;
    InitAlo((ALO *)pdprize);
    AppendDlEntry(&pdprize->psw->dlDprize, pdprize);
    pdprize->ichkCollected = IchkAllocChkmgr(&g_chkmgr);
    pdprize->ficg.grficSmash = '\x10';
    pdprize->ficg.grficRush = '\x10';
    pdprize->ficg.grficSweep = '\x10';
    pdprize->ficg.grficBomb = '\x10';
    pdprize->fLastBounce = 1;
}

INCLUDE_ASM(const s32, "P2/coin", LoadDprizeFromBrx__FP6DPRIZEP18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/coin", CloneDprize__FP6DPRIZET0);

INCLUDE_ASM(const s32, "P2/coin", PostDprizeLoad__FP6DPRIZE);

INCLUDE_ASM(const s32, "P2/coin", ProjectDprizeTransform__FP6DPRIZEfi);

INCLUDE_ASM(const s32, "P2/coin", FFilterDprizeObjects__FP6DPRIZEP2SO);

INCLUDE_ASM(const s32, "P2/coin", CheckDprizeBounce__FP6DPRIZE);

INCLUDE_ASM(const s32, "P2/coin", CheckDprizeCollect__FP6DPRIZE);

INCLUDE_ASM(const s32, "P2/coin", FAbsorbDprizeWkr__FP6DPRIZEP3WKR);

INCLUDE_ASM(const s32, "P2/coin", UpdateDprize__FP6DPRIZEf);

INCLUDE_ASM(const s32, "P2/coin", RenderDprizeAll__FP6DPRIZEP2CMP2RO);

INCLUDE_ASM(const s32, "P2/coin", SetDprizeDprizes__FP6DPRIZE7DPRIZES);

void InitCoin(COIN *pcoin)
{
    InitDprize((DPRIZE *)pcoin);
    pcoin->sRadiusBounce = 45.0f;
    pcoin->svLastBounceMax = 250.0f;
    pcoin->sRadiusCollect = 50.0f;
    pcoin->svLastBounce = 50.0f;
    pcoin->rxyBounce = 0.6f;
    pcoin->rzBounce = 0.75f;
    pcoin->uGlintChance = 0.25f;
    (pcoin->lmDtMaxLifetime).gMin = 8.0f;
    (pcoin->lmDtMaxLifetime).gMax = 10.0f;
}

INCLUDE_ASM(const s32, "P2/coin", FUN_00147ed0);

INCLUDE_ASM(const s32, "P2/coin", FUN_00147ef8);

INCLUDE_ASM(const s32, "P2/coin", UpdateCoin__FP4COINf);

INCLUDE_ASM(const s32, "P2/coin", CreateSwCharm__FP2SW);

INCLUDE_ASM(const s32, "P2/coin", AddLife__FPv);

INCLUDE_ASM(const s32, "P2/coin", OnCoinSmack__FP4COIN);

INCLUDE_ASM(const s32, "P2/coin", SetCoinDprizes__FP4COIN7DPRIZES);

void InitCharm(CHARM *pcharm)
{
    InitDprize((DPRIZE *)pcharm);
    pcharm->sRadiusBounce = 60.0f;
    pcharm->sRadiusCollect = 60.0f;
    pcharm->svLastBounceMax = 300.0f;
    pcharm->svLastBounce = 0.0f;
    pcharm->rxyBounce = .75f;
    pcharm->rzBounce = 0.5f;
    pcharm->uGlintChance = 0.35f;
}

INCLUDE_ASM(const s32, "P2/coin", SetCharmDprizes__FP5CHARM7DPRIZES);

void InitKey(KEY *pkey)
{
    InitDprize((DPRIZE *)pkey);
    LS *pLVar1 = g_plsCur;
    pkey->sRadiusBounce = 35.0f;
    pkey->sRadiusCollect = 35.0f;
    pkey->svLastBounceMax = 500.0f;
    pkey->svLastBounce = 250.0f;
    pkey->rxyBounce = 0.6f;
    pkey->rzBounce = 0.6f;
    pkey->uGlintChance = 0.75f;
    if ((pLVar1->fls & FLS_KeyCollected) != 0) 
    {
        pkey->dprizesInit = DPRIZES_Removed;
    }
}

INCLUDE_ASM(const s32, "P2/coin", SetKeyDprizes__FP3KEY7DPRIZES);

INCLUDE_ASM(const s32, "P2/coin", FUN_00148698);

INCLUDE_ASM(const s32, "P2/coin", FUN_00148718);

INCLUDE_ASM(const s32, "P2/coin", FUN_00148748);

INCLUDE_ASM(const s32, "P2/coin", FUN_00148770);

INCLUDE_ASM(const s32, "P2/coin", FUN_00148828);

INCLUDE_ASM(const s32, "P2/coin", FUN_00148888);

INCLUDE_ASM(const s32, "P2/coin", func_00148910);

INCLUDE_ASM(const s32, "P2/coin", FUN_00148938);

INCLUDE_ASM(const s32, "P2/coin", CpdprizeAttractSwDprizes__FP2SW3CIDP6VECTORiPP6DPRIZE);

INCLUDE_ASM(const s32, "P2/coin", RemoveSwExtraneousCharms__FP2SW);

INCLUDE_ASM(const s32, "P2/coin", FUN_00148d90);

INCLUDE_ASM(const s32, "P2/coin", FUN_00148e18);

INCLUDE_ASM(const s32, "P2/coin", FUN_00148e40);

INCLUDE_ASM(const s32, "P2/coin", FUN_00148ef8);

INCLUDE_ASM(const s32, "P2/coin", increment_and_show_life_count);

INCLUDE_ASM(const s32, "P2/coin", CollectLifetkn__FP7LIFETKN);

INCLUDE_ASM(const s32, "P2/coin", FUN_00149168);

INCLUDE_ASM(const s32, "P2/coin", break_bottle);
