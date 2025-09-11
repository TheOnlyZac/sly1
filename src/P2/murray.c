#include <murray.h>

void InitMurray(MURRAY *pmurray)
{
    InitStepguard(pmurray);
    STRUCT_OFFSET(pmurray, 0xbd4, int) = 0; // pmurray->fAutoFadeDying
    STRUCT_OFFSET(pmurray, 0xbd0, float) = 0.0f; // pmurray->uFling
}

INCLUDE_ASM("asm/nonmatchings/P2/murray", PostMurrayLoad__FP6MURRAY);

INCLUDE_ASM("asm/nonmatchings/P2/murray", FUN_0018ffb0);

INCLUDE_ASM("asm/nonmatchings/P2/murray", OnMurrayExitingSgs__FP6MURRAY3SGS);

INCLUDE_ASM("asm/nonmatchings/P2/murray", UpdateMurrayGoal__FP6MURRAYi);

INCLUDE_ASM("asm/nonmatchings/P2/murray", UpdateMurraySgs__FP6MURRAY);

INCLUDE_ASM("asm/nonmatchings/P2/murray", FUN_001903f0);

INCLUDE_ASM("asm/nonmatchings/P2/murray", FUN_00190450);

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
