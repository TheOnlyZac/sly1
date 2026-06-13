#include <murray.h>
#include <joy.h>
#include <rwm.h>
#include <vtables.h>

void InitMurray(MURRAY *pmurray)
{
    InitStepguard(pmurray);
    STRUCT_OFFSET(pmurray, 0xbd4, int) = 0; // pmurray->fAutoFadeDying
    STRUCT_OFFSET(pmurray, 0xbd0, float) = 0.0f; // pmurray->uFling
}

extern SNIP D_00269B60[2];

void PostMurrayLoad(MURRAY *pmurray)
{
    PostStepguardLoad(pmurray);
    SnipAloObjects(pmurray, 2, D_00269B60);
    STRUCT_OFFSET(pmurray, 0x5f0, ASEG *) = PasegFindStepguard(pmurray, (OID)0xEF);
    STRUCT_OFFSET(pmurray, 0xc38, ASEG *) = PasegFindStepguard(pmurray, (OID)0x16C);
    STRUCT_OFFSET(pmurray, 0xc3c, ASEG *) = PasegFindStepguard(pmurray, (OID)0x16D);
    STRUCT_OFFSET(pmurray, 0xc40, ASEG *) = PasegFindStepguard(pmurray, (OID)0x16A);
    STRUCT_OFFSET(pmurray, 0xc44, ASEG *) = PasegFindStepguard(pmurray, (OID)0x16B);
}

INCLUDE_ASM("asm/nonmatchings/P2/murray", FUN_0018ffb0);

INCLUDE_ASM("asm/nonmatchings/P2/murray", OnMurrayExitingSgs__FP6MURRAY3SGS);

INCLUDE_ASM("asm/nonmatchings/P2/murray", UpdateMurrayGoal__FP6MURRAYi);

INCLUDE_ASM("asm/nonmatchings/P2/murray", UpdateMurraySgs__FP6MURRAY);

extern "C" int FUN_001c9a48(STEPGUARD *pstepguard, void *pv);

extern "C" int FUN_001903f0(MURRAY *pmurray, void *pv)
{
    if ((g_grfcht & FCHT_Invulnerability) || IsSwHandsOff(STRUCT_OFFSET(pmurray, 0x14, SW *)))
    {
        return 1;
    }
    return FUN_001c9a48(pmurray, pv);
}

extern "C" int FUN_00190450(MURRAY *pmurray, WKR *pwkr)
{
    LO **ppvtable = (LO **)STRUCT_OFFSET(pmurray, 0x0, void *);
    int (*pfn)(MURRAY *, LO *) = (int (*)(MURRAY *, LO *))STRUCT_OFFSET(ppvtable, 0x13c, void *);

    if (pfn(pmurray, pwkr->ploSource))
    {
        return 0;
    }

    STRUCT_OFFSET(pmurray, 0xc34, int) = 0;
    STRUCT_OFFSET(pmurray, 0xc30, LO *) = pwkr->ploSource;

    if (pwkr->ploSource == NULL && pwkr->ploTarget != NULL)
    {
        RWM *prwm = STRUCT_OFFSET(STRUCT_OFFSET(pmurray, 0xc2c, SO *), 0x618, RWM *);
        if (FIsRwmAmmo(prwm, (SO *)pwkr->ploTarget))
        {
            STRUCT_OFFSET(pmurray, 0xc34, int) = 1;
        }
    }

    return FTakeStepguardDamage(pmurray, (ZPR *)pwkr);
}

INCLUDE_ASM("asm/nonmatchings/P2/murray", FAbsorbMurrayWkr__FP6MURRAYP3WKR);

INCLUDE_ASM("asm/nonmatchings/P2/murray", FDetectMurray__FP6MURRAY);

int FCanMurrayAttack(MURRAY *pmurray)
{
    return false;
}

INCLUDE_ASM("asm/nonmatchings/P2/murray", FUN_00190660);

void SetMurrayPursueXfm(MURRAY *pmurray, XFM *pxfm)
{
    STRUCT_OFFSET(pmurray, 0xc28, XFM *) = pxfm; // pmurray->pxfmPursue
}

void SetMurrayPatrolXfm(MURRAY *pmurray, XFM *pxfm)
{
    STRUCT_OFFSET(pmurray, 0xc24, XFM *) = pxfm; // pmurray->pxfmPatrol
}

void CollectMurrayPrize(MURRAY *pmurray, PCK pck, ALO *palo)
{
    CollectPoPrize(pmurray, pck, palo);
    if (pck == PCK_Key)
    {
        SetStepguardSgs(pmurray, SGS_LostPlayer, STRUCT_OFFSET(pmurray, 0x5f0, ASEG *)); // pmurray->pasegCelebrateKey
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/murray", FUN_00190740);

INCLUDE_ASM("asm/nonmatchings/P2/murray", HandleMurrayMessage);
