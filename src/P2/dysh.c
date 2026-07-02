#include <dysh.h>
#include <alo.h>
#include <render.h>
#include <sce/memset.h>

void InitDysh(DYSH* pdysh)
{
    InitAlo((ALO*)pdysh);
}

INCLUDE_ASM("asm/nonmatchings/P2/dysh", SetDyshShadow__FP4DYSHP6SHADOW);

void RenderDyshSelf(DYSH* pdysh, CM* pcm, RO* pro)
{
    RPL rpl;

    if (STRUCT_OFFSET(pdysh, 0x2D0, int))
    {
        void** pvtbl = STRUCT_OFFSET(pdysh, 0x0, void**);
        ((void (*)(DYSH*, RO*))pvtbl[0xAC / 4])(pdysh, pro);

        memset(&rpl, 0, 0x80);
        rpl.pfnDraw = DrawDysh;
        rpl.rp = RP_DynamicTexture;
        DupAloRo((ALO*)pdysh, pro, (RO*)((char*)&rpl + 0x10));
        STRUCT_OFFSET(&rpl, 0x60, DYSH*) = pdysh;
        SubmitRpl(&rpl);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/dysh", DrawDysh__FP3RPL);
