#include <bsp.h>
#include <memory.h>

INCLUDE_ASM("asm/nonmatchings/P2/bsp", ClsgClipEdgeToBsp__FP3BSPP6VECTORT1PiiP3LSG);

INCLUDE_ASM("asm/nonmatchings/P2/bsp", PruneBsp__FP3BSPP6VECTORfPP3BSP);

INCLUDE_ASM("asm/nonmatchings/P2/bsp", PbspPointInBspQuick__FP6VECTORP3BSP);

void CloneBspc(GEOM *pgeomSrc, BSPC *pbspcSrc, GEOM *pgeomDst, BSPC *pbspcDst)
{
    int ibsp;

    pbspcDst->cbsp = pbspcSrc->cbsp;
    pbspcDst->cbspFull = pbspcSrc->cbspFull;
    pbspcDst->absp = (BSP *)PvAllocSwImpl(pbspcSrc->cbsp * sizeof(BSP));

    for (ibsp = 0; ibsp < pbspcDst->cbsp; ibsp++)
    {
        BSP *pbspSrc = &pbspcSrc->absp[ibsp];
        BSP *pbspDst = &pbspcDst->absp[ibsp];

        pbspDst->psurf = (SURF *)((int)pgeomDst->asurf + ((int)pbspSrc->psurf - (int)pgeomSrc->asurf));
        pbspDst->pbspNeg = pbspSrc->pbspNeg
            ? (BSP *)((int)pbspcDst->absp + ((int)pbspSrc->pbspNeg - (int)pbspcSrc->absp))
            : NULL;
        pbspDst->pbspPos = pbspSrc->pbspPos
            ? (BSP *)((int)pbspcDst->absp + ((int)pbspSrc->pbspPos - (int)pbspcSrc->absp))
            : NULL;
    }
}
