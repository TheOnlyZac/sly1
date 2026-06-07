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

void PushCplookLookk(CPLOOK *pcplook, LOOKK lookk)
{
    int clookk = STRUCT_OFFSET(pcplook, 0x40, int);
    if ((unsigned int)clookk < 4)
    {
        STRUCT_OFFSET_INDEX(pcplook, 0x30, LOOKK, clookk) = lookk;
        STRUCT_OFFSET(pcplook, 0x40, int) = clookk + 1;
    }
}

LOOKK LookkPopCplook(CPLOOK *pcplook)
{
    int n = STRUCT_OFFSET(pcplook, 0x40, int);
    if (n <= 0)
        return (LOOKK)-1;
    n = n - 1;
    STRUCT_OFFSET(pcplook, 0x40, int) = n;
    LOOKK *a = &STRUCT_OFFSET(pcplook, 0x30, LOOKK);
    return a[n];
}

LOOKK LookkCurCplook(CPLOOK *pcplook)
{
    int n = STRUCT_OFFSET(pcplook, 0x40, int);
    if (n <= 0)
        return (LOOKK)-1;
    int i = n - 1;
    LOOKK *a = &STRUCT_OFFSET(pcplook, 0x30, LOOKK);
    return a[i];
}

INCLUDE_ASM("asm/nonmatchings/P2/cplcy", InitCplook);

INCLUDE_ASM("asm/nonmatchings/P2/cplcy", FUN_001496c0);

INCLUDE_ASM("asm/nonmatchings/P2/cplcy", UpdateCplook);

INCLUDE_ASM("asm/nonmatchings/P2/cplcy", FUN_0014a7b8);

INCLUDE_ASM("asm/nonmatchings/P2/cplcy", InitCpalign);

extern "C" void ResetCmLookAtSmooth(CM *pcm, void *pv);

void FUN_0014a8d0(CPALIGN *pcpalign)
{
    CM *pcm = pcpalign->pcm;
    ResetCmLookAtSmooth(pcm, (void *)((uint8_t *)STRUCT_OFFSET(pcm, 0x3DC, void *) + 0x370));
}

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
