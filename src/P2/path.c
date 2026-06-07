#include <path.h>

struct CBSP;
struct CGT;
struct LSG;

CBSP* PcbspExtract(CBSP* pcbsp)
{
    return ((int)pcbsp & 1) ? (CBSP*)0 : pcbsp;
}

CGT* PcgtExtract(CGT* pcgt)
{
    if ((int)pcgt & 1)
        return (CGT*)((int)pcgt & ~1);
    return (CGT*)0;
}

INCLUDE_ASM("asm/nonmatchings/P2/path", PcgtPointInCbspQuick__FP4CBSPP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/path", PcgtPointInCbspSafe__FP4CBSPP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/path", CbskFromG__Ff);

INCLUDE_ASM("asm/nonmatchings/P2/path", ClsgClipEdgeToCbsp__FP4CBSPP6VECTORT1iP3LSG);

INCLUDE_ASM("asm/nonmatchings/P2/path", FClipEdgeToCbsp__FP4CBSPP6VECTORT1);

struct CG;
struct CGV;

int IcgvFromPcgv(CG* pcg, CGV* pcgv)
{
    return ((int)pcgv - STRUCT_OFFSET(pcg, 0x4, int)) >> 5;
}

INCLUDE_ASM("asm/nonmatchings/P2/path", FindPathAStar__FP2CGP3CGVT1iPiPP3CGV);

INCLUDE_ASM("asm/nonmatchings/P2/path", SimplifyApcgvNeighbor__FP4CBSPPiPP3CGV);

INCLUDE_ASM("asm/nonmatchings/P2/path", CposFindPath__FP2CGP6VECTORT1iT1);

INCLUDE_ASM("asm/nonmatchings/P2/path", FindClosestPointInCg__FP2CGP6VECTORT1);

INCLUDE_ASM("asm/nonmatchings/P2/path", LoadPathzoneFromBrx__FP8PATHZONEP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/path", HookupCg__FP2CG);

struct PATHZONE;
struct VECTOR;
extern int CposFindPath(CG *pcg, VECTOR *pvec0, VECTOR *pvec1, int n, VECTOR *pvec2);

int CposFindPathzonePath(PATHZONE *ppathzone, VECTOR *pvec0, VECTOR *pvec1, int n, VECTOR *pvec2)
{
    return CposFindPath((CG *)((char *)ppathzone + 0x34), pvec0, pvec1, n, pvec2);
}

void FindClosestPointInCg(CG *pcg, VECTOR *pvec0, VECTOR *pvec1);

void FindPathzoneClosestPoint(PATHZONE *ppathzone, VECTOR *pvec0, VECTOR *pvec1)
{
    FindClosestPointInCg((CG *)((char *)ppathzone + 0x34), pvec0, pvec1);
}

int ClsgClipEdgeToCbsp(CBSP *pcbsp, VECTOR *pvec0, VECTOR *pvec1, int i, LSG *plsg);

extern "C" int FUN_00191aa8(void *p, VECTOR *pvec0, VECTOR *pvec1, int i, LSG *plsg)
{
    return ClsgClipEdgeToCbsp(STRUCT_OFFSET(p, 0x54, CBSP *), pvec0, pvec1, i, plsg);
}

INCLUDE_ASM("asm/nonmatchings/P2/path", FUN_00191ac8);

INCLUDE_ASM("asm/nonmatchings/P2/path", ChoosePathzoneRandomPoint__FP8PATHZONEP6VECTOR);
