#include <splice/sidebag.h>
#include <splice/ref.h>
#include <splice/splotheap.h>
#include <sce/memset.h>
#include <memory.h>

CRef CSidebag::RefAddBinding(int n, CRef *pref)
{
    CRef ref;
    void *psbb = FUN_0011C498();
    STRUCT_OFFSET(psbb, 0x0, int) = n;
    STRUCT_OFFSET(psbb, 0x4, CRef) = *pref;
    STRUCT_OFFSET(psbb, 0xC, void *) = STRUCT_OFFSET(this, 0x0, void *);
    STRUCT_OFFSET(this, 0x0, void *) = psbb;
    ref.SetTag(TAGK_Void);
    return ref;
}

CRef CSidebag::RefSetBinding(int n, CRef *pref)
{
    void *psbb = STRUCT_OFFSET(this, 0x0, void *);
    if (psbb != NULL)
    {
        do
        {
            if (STRUCT_OFFSET(psbb, 0x0, int) == n)
            {
                CRef ref;
                STRUCT_OFFSET(psbb, 0x4, CRef) = *pref;
                ref.SetTag(TAGK_Void);
                return ref;
            }
            psbb = STRUCT_OFFSET(psbb, 0xC, void *);
        } while (psbb != NULL);
    }
    CRef ref;
    ref.SetTag(TAGK_Void);
    return ref;
}

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
