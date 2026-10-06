#include <sb.h>
#include <asega.h>
#include <memcard.h>
#include <game.h>
#include <sw.h>
#include <ui.h>

void PostSbgLoad(SBG *psbg) 
{
    PostStepguardLoad(psbg);
    FUN_001ddc38(psbg->psw,  psbg);
}

int FUN_001a9928(SBG *psbg) 
{
    if (IsSwHandsOff(psbg->psw) == 0) 
    {
        return STRUCT_OFFSET(psbg, 0xC24, int);
    }
    return 0;
}

void UpdateSbgGoal(SBG *psbg, int fEnter) 
{
    int vectorCheck;

    UpdateStepguardGoal(psbg, fEnter);
    if (STRUCT_OFFSET(psbg, 0x724, SGS) == SGS_Stun) 
    {
        typedef int (*VFn)(SBG*);
        vectorCheck = STRUCT_OFFSET(STRUCT_OFFSET(psbg, 0x0, SBG *), 0x198, VFn)(psbg);
        if (vectorCheck != 0) 
        {
            SetStepguardGoal(psbg, &STRUCT_OFFSET(vectorCheck, 0x140, VECTOR));
        }
    }
}

void UpdateSbgSgs(SBG *psbg)
{
    UpdateStepguardSgs(psbg);

    if (STRUCT_OFFSET(psbg, 0x724, SGS) == SGS_Stun)
    {
        LookStepguardAtGoal(psbg);
    }
}

void OnSbgEnteringSgs(SBG *psbg, SGS sgs, ASEG *paseg) 
{
    OnStepguardEnteringSgs(psbg, sgs, paseg);
    if (STRUCT_OFFSET(psbg, 0x724, int) == 0xB) 
    {
        DefeatBossFromWorld(GAMEWORLD_Snow);
        FUN_0018c7f8(&g_save);
    }
}

void UpdateSbg(SBG *psbg, float dt) 
{
    UpdateStepguard(psbg, dt);
    ASEGA *pasega = STRUCT_OFFSET(psbg, 0xC20, ASEGA *);
    if (pasega != 0 && STRUCT_OFFSET(pasega, 0x18, float) == 0.0f) 
    {
        RetractAsega(pasega);
        STRUCT_OFFSET(psbg, 0xC20, ASEGA *) = 0;
    }
}

void FUN_001a9a98() 
{
    if (FUN_001e9970() != 0) 
    {
        g_unkblot7.pvtblot->pfnShowBlot(&g_unkblot7);
        return;
    }
    g_unkblot7.pvtblot->pfnHideBlot(&g_unkblot7);
}

INCLUDE_ASM("asm/nonmatchings/P2/sb", FAbsorbSbgWkr__FP3SBGP3WKR);

void FUN_001a9c58(SBG *psbg, int a, int b, int c)
{
    STRUCT_OFFSET(psbg, 0xC14, int) = a;
    STRUCT_OFFSET(psbg, 0xC18, int) = b;
    STRUCT_OFFSET(psbg, 0xC1C, int) = c;
}
