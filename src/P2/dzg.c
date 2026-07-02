#include <dzg.h>
#include <memory.h>
#include <sce/memset.h>

void InitDzg(DZG *pdzg, int cpxp)
{
    int c;

    memset(pdzg, 0, sizeof(DZG));
    c = cpxp * 2;
    pdzg->cdzMax = c;
    pdzg->adz = (DZ *)PvAllocStackImpl(c * 0x60);
    memset(pdzg->adz, 0, c * 0x60);
    InitDl(&pdzg->dlPos, 0x4C);
    InitDl(&pdzg->dlZero, 0x4C);
    InitDl(&pdzg->dlMax, 0x4C);
    InitDl(&pdzg->dlUncat, 0x4C);
    pdzg->aagPos = (float *)PvAllocStackImpl(c * c * 4);
    pdzg->aagPosCrout = (float *)PvAllocStackImpl(c * c * 4);
    pdzg->asdv = (float *)PvAllocStackImpl(cpxp * 8);
    pdzg->adsfPos = (float *)PvAllocStackImpl(cpxp * 8);
}

INCLUDE_ASM("asm/nonmatchings/P2/dzg", ClearDzgSolution__FP3DZG);

INCLUDE_ASM("asm/nonmatchings/P2/dzg", AppendDzgDz__FP3DZGP2DZ);

INCLUDE_ASM("asm/nonmatchings/P2/dzg", FillDzgDz__FP3DZGiP2DZiPP2XPPiPPP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/dzg", EnforceDzgDz__FP3DZGP2DZ);

INCLUDE_ASM("asm/nonmatchings/P2/dzg", SolveDzg__FP3DZGiiPP2XPPiPPP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/dzg", SolveDzgFric__FP3DZGiiPP2XPPiPPP2SOf);

INCLUDE_ASM("asm/nonmatchings/P2/dzg", ApplyDzg__FP3DZGiPiPPP2SOff);

INCLUDE_ASM("asm/nonmatchings/P2/dzg", SolveInequalities__FiPfN21);
