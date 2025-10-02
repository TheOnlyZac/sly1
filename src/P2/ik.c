#include <ik.h>

void RenderIkhSelf(IKH *pikh, CM *pcm, RO *pro)
{
    RenderSoSelf(pikh, pcm, pro);
}

void RenderLikhSelf(LIKH *plikh, CM *pcm, RO *pro)
{
    RenderAloSelf(plikh, pcm, pro);
}

INCLUDE_ASM("asm/nonmatchings/P2/ik", SolveAloIK__FP3ALO);
