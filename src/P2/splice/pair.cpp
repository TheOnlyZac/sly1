#include <splice/pair.h>
#include <splice/splotheap.h>
#include <sce/memset.h>

void CPair::CloneTo(CPair *ppairClone, CFrame *pframeClone)
{
    m_ref.CloneTo(&ppairClone->m_ref, pframeClone);

    if (m_ppairNext)
    {
        CPair *ppairNew = PpairNew();
        m_ppairNext->CloneTo(ppairNew, pframeClone);
        ppairClone->m_ppairNext = ppairNew;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/splice/pair", PpairNew__Fv);
#ifdef SKIP_ASM
/**
 * @todo 89.50% matched.
 */
CPair *PpairNew()
{
    CPair *ppair = (CPair *)g_splotheapPair.PvAllocClear();
    memset(ppair, 0, 0xC);
    CRef *pref = new CRef();
    STRUCT_OFFSET(ppair, 0, int) = -1;
    return ppair;
}
#endif

void DeletePair(CPair *ppair)
{
    ppair->m_ref.~CRef();
}
