#include <sb.h>
#include <asega.h>
#include <memcard.h>
#include <sw.h>
#include <ui.h>

void PostSbgLoad(SBG* psbg) 
{
    PostStepguardLoad(psbg);
    FUN_001ddc38(STRUCT_OFFSET(psbg, 0x14, SW *),  psbg);
}

undefined4 FUN_001a9928(SBG* pSbg) {
    if (IsSwHandsOff__FP2SW(STRUCT_OFFSET(pSbg, 0x14, SW *)) == 0) {
        return STRUCT_OFFSET(pSbg, 0xC24, int);
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

void OnSbgEnteringSgs(SBG* pSbg, SGS sgs, ASEG* pAseg) {
    OnStepguardEnteringSgs(pSbg, sgs, pAseg);
    if (STRUCT_OFFSET(pSbg, 0x724, int) == 0xB) {
        DefeatBossFromWid(4);
        FUN_0018c7f8(&g_save);
    }
}

void UpdateSbg__FP3SBGf(SBG* psbg, float dt) 
{
    ASEGA *pasega;

    UpdateStepguard(psbg, dt);
    pasega = STRUCT_OFFSET(psbg,0xC20,ASEGA *);
    if ((pasega != 0) && (STRUCT_OFFSET(pasega,0x18,float) == 0.0f)) 
    {
        RetractAsega(pasega);
        STRUCT_OFFSET(psbg,0xC20,ASEGA *) = 0;
    }
}

void FUN_001a9a98() 
{
    typedef void (*VFn)(BLOT**);
    if (FUN_001e9970() != 0) 
    {
        STRUCT_OFFSET(g_unkblot7, 0x38, VFn)(&g_unkblot7);
        return;
    }
    STRUCT_OFFSET(g_unkblot7, 0x3C, VFn)(&g_unkblot7);
}

INCLUDE_ASM("asm/nonmatchings/P2/sb", FAbsorbSbgWkr__FP3SBGP3WKR);

void FUN_001a9c58(SBG *psbg, int a, int b, int c)
{
    STRUCT_OFFSET(psbg, 0xC14, int) = a;
    STRUCT_OFFSET(psbg, 0xC18, int) = b;
    STRUCT_OFFSET(psbg, 0xC1C, int) = c;
}
