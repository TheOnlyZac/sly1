#include <dysh.h>
#include <alo.h>

void InitDysh(DYSH* pdysh)
{
    InitAlo((ALO*)pdysh);
}

INCLUDE_ASM("asm/nonmatchings/P2/dysh", SetDyshShadow__FP4DYSHP6SHADOW);

INCLUDE_ASM("asm/nonmatchings/P2/dysh", RenderDyshSelf__FP4DYSHP2CMP2RO);

INCLUDE_ASM("asm/nonmatchings/P2/dysh", DrawDysh__FP3RPL);
