#include <splice/pair.h>
#include <splice/splotheap.h>
#include <splice/ref.h>
#include <sce/memset.h>

/** @note This flag is required so that we don't compile with exception support in new() */
#define __EMBEDDED_CXX__
#include <new>

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
