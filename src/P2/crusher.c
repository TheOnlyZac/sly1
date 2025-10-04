#include <crusher.h>

/**
 * @todo Rename.
 */
extern int DAT_0027c008;

void OnCrfodAdd(CRFOD *pcrfod)
{
    OnStepguardAdd(pcrfod);
    AppendDlEntry(&pcrfod->psw->dlCrfod, pcrfod);
}

void OnCrfodRemove(CRFOD *pcrfod)
{
    OnStepguardRemove(pcrfod);
    RemoveDlEntry(&pcrfod->psw->dlCrfod, pcrfod);
}

void CloneCrfod(CRFOD *pcrfod, CRFOD *pcrfodBase)
{
    DLE dleCrfod = STRUCT_OFFSET(pcrfod, 0xc10, DLE);
    CloneStepguard(pcrfod, pcrfodBase);
    STRUCT_OFFSET(pcrfod, 0xc10, DLE) = dleCrfod;
}

void InitCrfodb(CRFODB *pcrfodb)
{
    InitStepguard(pcrfodb);
    STRUCT_OFFSET(pcrfodb, 0xc24, int) = 1;
    DAT_0027c008 = 0;
}

void PostCrfodbLoad(CRFODB *pcrfodb)
{
    PostStepguardLoad(pcrfodb);
    STRUCT_OFFSET(pcrfodb, 0xc2c, int) = DAT_0027c008++;
}

void CalcHeadingVector(float rad, VECTOR *pvector)
{
    CalculateSinCos(rad, &pvector->y, (float *)pvector);
    pvector->z = 0.0f;
}

INCLUDE_ASM("asm/nonmatchings/P2/crusher", UpdateCrfodbGoal__FP6CRFODBi);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", FDetectCrfodb__FP6CRFODB);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", FAbsorbCrfodbWkr__FP6CRFODBP3WKR);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", FUN_0014bd38);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", SgsNextCrfodkAI__FP6CRFODK);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", FDetectCrfodk__FP6CRFODK);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", FAbsorbCrfodkWkr__FP6CRFODKP3WKR);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", FUN_0014bf88);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", InitCrbrain__FP7CRBRAIN);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", post_load_crbrain);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", FUN_0014c2f0);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", FUN_0014c5e8);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", FUN_0014c668);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", update_crbrain);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", FUN_0014c788);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", FUN_0014c820);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", FUN_0014c838);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", FUN_0014c858);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", FUN_0014cba8);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", FUN_0014cd70);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", FUN_0014cdc8);

INCLUDE_ASM("asm/nonmatchings/P2/crusher", handle_crbrain_message);
