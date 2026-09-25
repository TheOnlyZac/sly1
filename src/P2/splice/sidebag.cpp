#include <splice/sidebag.h>
#include <splice/ref.h>
#include <splice/varb.h>
#include <sce/memset.h>
#include <memory.h>

CRef CSidebag::RefAddBinding(int symid, CRef *pref)
{
    CRef ref;

    CVarb *pvarbNew = PvarbNew();
    pvarbNew->m_symid = symid;
    pvarbNew->m_ref = *pref;
    pvarbNew->m_pvarbNext = m_pvarb;
    m_pvarb = pvarbNew;

    ref.SetTag(TAGK_Void);
    return ref;
}

CRef CSidebag::RefSetBinding(int symid, CRef *pref)
{
    for (CVarb *pvarb = m_pvarb; pvarb != NULL; pvarb = pvarb->m_pvarbNext)
    {
        if (pvarb->m_symid == symid)
        {
            CRef ref;
            pvarb->m_ref = *pref;
            ref.SetTag(TAGK_Void);
            return ref;
        }
    }

    CRef ref;
    ref.SetTag(TAGK_Void);
    return ref;
}

int CSidebag::FFindBinding(int symid, CRef *pref)
{
    for (CVarb *pvarb = m_pvarb; pvarb != NULL; pvarb = pvarb->m_pvarbNext)
    {
        if (pvarb->m_symid == symid)
        {
            if (pref != NULL)
            {
                *pref = pvarb->m_ref;
            }
            return 1;
        }
    }

    return 0;
}

void CSidebag::CloneTo(CSidebag *psidebagClone)
{
    CVarb *pvarbNew = PvarbNew();
    m_pvarb->CloneTo(pvarbNew, NULL);
    psidebagClone->m_pvarb = pvarbNew;
}

CSidebag *PsidebagNew()
{
    CSidebag *psidebag = (CSidebag *)PvAllocSwClearImpl(sizeof(CSidebag));
    memset(psidebag, 0, 4);
    return psidebag;
}
