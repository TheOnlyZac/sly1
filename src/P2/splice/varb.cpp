#include <splice/varb.h>
#include <splice/splotheap.h>
#include <sce/memset.h>

/** @note This flag is required so that we don't compile with exception support in new() */
#define __EMBEDDED_CXX__
#include <new>

void CVarb::CloneTo(CVarb *pvarbClone, CFrame *pframeClone)
{
    pvarbClone->m_symid = m_symid;
    m_ref.CloneTo(&pvarbClone->m_ref, pframeClone);

    if (m_pvarbNext)
    {
        CVarb *pvarbNew = PvarbNew();
        m_pvarbNext->CloneTo(pvarbNew, pframeClone);
        pvarbClone->m_pvarbNext = pvarbNew;
    }
}

CVarb *PvarbNew()
{
    CVarb *pvarb = (CVarb *)g_splotheapVarb.PvAllocClear();
    memset(pvarb, 0, sizeof(CVarb));
    new (&pvarb->m_ref) CRef();
    pvarb->m_ref.m_tagk = TAGK_Nil;
    return pvarb;
}

void DeleteVarb(CVarb *pvarb)
{
    pvarb->m_ref.~CRef();
}
