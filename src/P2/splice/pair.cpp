#include <splice/pair.h>
#include <splice/splotheap.h>
#include <splice/ref.h>
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

/**
 * Placement new without non-throwing decorator, which assumes unconditional success
 * and forces the compiler to emit a call without any checks.
 * @todo: should probably find a more generic/global place to put this?
 */
inline void *operator new(uint, void *place)
{
    return place;
}

CPair *PpairNew()
{
    CPair *ppair = (CPair *)g_splotheapPair.PvAllocClear();
    memset(ppair, 0, sizeof(CPair));

    /* Initialize the cref with operator new */
    new (ppair) CRef();
    ppair->m_ref.m_tagk = TAGK_Nil;

    return ppair;
}

void DeletePair(CPair *ppair)
{
    ppair->m_ref.~CRef();
}
