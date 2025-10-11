#include <splice/sidebag.h>
#include <sce/memset.h>
#include <memory.h>

INCLUDE_ASM("asm/nonmatchings/P2/splice/sidebag", RefAddBinding__8CSidebagiP4CRef);

INCLUDE_ASM("asm/nonmatchings/P2/splice/sidebag", RefSetBinding__8CSidebagiP4CRef);

INCLUDE_ASM("asm/nonmatchings/P2/splice/sidebag", FFindBinding__8CSidebagiP4CRef);

INCLUDE_ASM("asm/nonmatchings/P2/splice/sidebag", CloneTo__8CSidebagP8CSidebag);

CSidebag *PsidebagNew()
{
    CSidebag *psidebag = (CSidebag *)PvAllocSwClearImpl(4);
    memset(psidebag, 0, 4);
    return psidebag;
}
