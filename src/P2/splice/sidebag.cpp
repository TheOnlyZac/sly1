#include <splice/sidebag.h>
#include <splice/ref.h>
#include <splice/splotheap.h>
#include <sce/memset.h>
#include <memory.h>

INCLUDE_ASM("asm/nonmatchings/P2/splice/sidebag", RefAddBinding__8CSidebagiP4CRef);

INCLUDE_ASM("asm/nonmatchings/P2/splice/sidebag", RefSetBinding__8CSidebagiP4CRef);

bool CSidebag::FFindBinding(int n, CRef *pref)
{
    // The sidebag is really a single pointer to a list of 0x10-byte nodes
    // { int n; CRef ref; node *pNext } (see FUN_0011C498); reach the fields
    // via STRUCT_OFFSET so the declared (placeholder) layout stays intact.
    void *psbb;
    for (psbb = STRUCT_OFFSET(this, 0x0, void *); psbb != NULL; psbb = STRUCT_OFFSET(psbb, 0xC, void *))
    {
        if (STRUCT_OFFSET(psbb, 0x0, int) == n)
        {
            if (pref != NULL)
            {
                *pref = STRUCT_OFFSET(psbb, 0x4, CRef);
            }
            return true;
        }
    }
    return false;
}

void CSidebag::CloneTo(CSidebag *psidebagClone)
{
    void *psbb = FUN_0011C498();
    FUN_0011C418(STRUCT_OFFSET(this, 0x0, void *), psbb, NULL);
    STRUCT_OFFSET(psidebagClone, 0x0, void *) = psbb;
}

CSidebag *PsidebagNew()
{
    CSidebag *psidebag = (CSidebag *)PvAllocSwClearImpl(4);
    memset(psidebag, 0, 4);
    return psidebag;
}
