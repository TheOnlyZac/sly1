#include <splice/frame.h>
#include <splice/spliceutils.h>
#include <splice/varb.h>
#include <sce/memset.h>
#include <memory.h>

void CFrame::SetSingleParent(CFrame *pframeParent)
{
    m_apframeParent[0] = pframeParent;
    m_cpframeParent = 1;
}

void CFrame::AddParent(CFrame *pframeParent)
{
    m_apframeParent[m_cpframeParent++] = pframeParent;
}

CRef CFrame::RefAddBinding(SYMID symid, CRef *pref)
{
    CRef cref;
    CVarb *pvarb = PvarbNew();
    pvarb->m_symid = symid;
    pvarb->m_ref = *pref;
    pvarb->m_pvarbNext = m_pvarb;
    m_pvarb = pvarb;

    cref.SetTag(TAGK_Void);
    return cref;
}

CRef CFrame::RefSetBinding(SYMID symid, CRef *pref)
{
    CRef cref;

    /* Update the symbol if we find it */
    CRef *prefBound = PrefFindBinding(symid, true);
    if (prefBound != NULL)
    {
        *prefBound = *pref;
    }

    cref.SetTag(TAGK_Void);
    return cref;
}

int CFrame::FFindBinding(SYMID symid, int fRecursive, CRef *pref)
{
    CRef *prefBound = PrefFindBinding(symid, fRecursive);
    if (prefBound != NULL)
    {
        if (pref != NULL)
        {
            *pref = *prefBound;
        }
        return true;
    }

    return false;
}

CRef *CFrame::PrefFindBinding(SYMID symid, int fRecursive)
{
    /* Set this flag to true while we are searching for bindings in case there is a loop
     * in the frame DAG. */
    m_fVisited = true;
    CRef *prefFound = NULL;

    /* First search for bindings in this frame */
    for (CVarb *pvarb = m_pvarb; pvarb != NULL; pvarb = pvarb->m_pvarbNext)
    {
        if (pvarb->m_symid == symid)
        {
            prefFound = &pvarb->m_ref;
            goto done;
        }
    }

    /* If we didn't find the binding, recurse on the parent frames */
    if (fRecursive)
    {
        for (int ipframe = 0; ipframe < m_cpframeParent; ipframe++)
        {
            CFrame *pframeParent = m_apframeParent[ipframe];
            if (pframeParent->m_fVisited)
            {
                continue;
            }

            prefFound = pframeParent->PrefFindBinding(symid, fRecursive);
            if (!prefFound)
            {
                continue;
            }

            goto done;
        }
    }

done:
    m_fVisited = false;
    return prefFound;
}

void CFrame::CloneTo(CFrame *pframeClone)
{
    pframeClone->m_cpframeParent = m_cpframeParent;
    CopyAb(pframeClone->m_apframeParent, m_apframeParent, m_cpframeParent * sizeof(CFrame *));

    if (m_pvarb != NULL)
    {
        CVarb *pvarbNew = PvarbNew();
        m_pvarb->CloneTo(pvarbNew, pframeClone);
        pframeClone->m_pvarb = pvarbNew;
    }
}

CFrame *PframeNew()
{
    CFrame *pframe = (CFrame *)g_splotheapFrame.PvAllocClear();
    memset(pframe, 0, 0x1c);
    return pframe;
}

void DeleteFrame(CFrame *pframe)
{
    return;
}
