#include <splicemap.h>
#include <splice/gc.h>

INCLUDE_ASM("asm/nonmatchings/P2/splicemap", LoadSwSpliceFromBrx__FP2SWP18CBinaryInputStream);

CFrame *PframeFromIsplice(int isplice, SW *psw)
{
    CFrame *pframe;

    if (isplice == -1)
        return NULL;

    pframe = *(CFrame **)((uint8_t *)STRUCT_OFFSET(psw, 0x1EF4, void *) + isplice * 8 + 4);
    if (pframe != NULL)
        g_gc.AddRootFrame(pframe);

    return pframe;
}

INCLUDE_ASM("asm/nonmatchings/P2/splicemap", RefEvalModule__FiP2SW);
