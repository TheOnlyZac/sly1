/**
 * @todo Mangle all function names in INCLUDE_ASM macros.
 */
#include <cplcy.h>

extern "C" void InitCplcy(CPLCY *pcplcy, CM *pcm)
{
    pcplcy->pcm = pcm;
}

extern "C" int FActiveCplcy(CPLCY *pcplcy)
{
    return STRUCT_OFFSET(pcplcy->pcm, 0x3D8, CPLCY *) == pcplcy;
}

extern "C" void SetCpmanCpmt(CPMAN *pcpman, CPMT cpmt)
{
    pcpman->cpmt = cpmt;
}

void FUN_001493c0(void)
{
}

INCLUDE_ASM("asm/nonmatchings/P2/cplcy", PosCplookAnchor);

INCLUDE_ASM("asm/nonmatchings/P2/cplcy", FUN_00149458);

INCLUDE_ASM("asm/nonmatchings/P2/cplcy", plays_binoc_sfx);

INCLUDE_ASM("asm/nonmatchings/P2/cplcy", PushCplookLookk__FP6CPLOOK5LOOKK);

INCLUDE_ASM("asm/nonmatchings/P2/cplcy", LookkPopCplook__FP6CPLOOK);

INCLUDE_ASM("asm/nonmatchings/P2/cplcy", LookkCurCplook__FP6CPLOOK);

INCLUDE_ASM("asm/nonmatchings/P2/cplcy", InitCplook);

INCLUDE_ASM("asm/nonmatchings/P2/cplcy", FUN_001496c0);

INCLUDE_ASM("asm/nonmatchings/P2/cplcy", UpdateCplook);

INCLUDE_ASM("asm/nonmatchings/P2/cplcy", FUN_0014a7b8);

INCLUDE_ASM("asm/nonmatchings/P2/cplcy", InitCpalign);

INCLUDE_ASM("asm/nonmatchings/P2/cplcy", FUN_0014a8d0);

INCLUDE_ASM("asm/nonmatchings/P2/cplcy", UpdateCpalign);

void FUN_0014aa90(int *param_1, int param_2)
{
    param_1[2] = param_2;
}

void FUN_0014aa98(void *p)
{
    STRUCT_OFFSET(p, 0x8, int) = 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/cplcy", UpdateCpaseg);
