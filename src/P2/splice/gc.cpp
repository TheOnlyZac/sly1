#include <splice/gc.h>
#include <splice/splotheap.h>
#include <splice/spliceutils.h>
#include <splice/ref.h>
#include <splice/pair.h>
#include <splice/sidebag.h>
#include <splice/varb.h>
#include <sw.h>

CGc::CGc()
{
    return;
}

CGc::~CGc()
{
    return;
}

void CGc::Startup()
{
    m_cpframeRoot = 0;
    m_cpsidebagRoot = 0;
}

void CGc::Shutdown() {}

void CGc::AddRootFrame(CFrame *pframe)
{
    for (int i = 0; i < m_cpframeRoot; ++i)
    {
        if (m_apframeRoot[i] == pframe)
        {
            return;
        }
    }
    m_apframeRoot[m_cpframeRoot++] = pframe;
}

void CGc::AddRootSidebag(CSidebag *psidebag)
{
    m_apsidebagRoot[m_cpsidebagRoot++] = psidebag;
}

void CGc::PushFrame(CFrame *pframe)
{
    m_apframeStack[m_cpframeStack++] = pframe;
}

CFrame *CGc::PframePop()
{
    if (m_cpframeStack >= 1)
    {
        return m_apframeStack[--m_cpframeStack];
    }
    return NULL;
}

void CGc::PushPair(CPair *ppair)
{
    m_appairStack[m_cppairStack++] = ppair;
}

CPair *CGc::PpairPop()
{
    if (m_cppairStack >= 1)
    {
        return m_appairStack[--m_cppairStack];
    }
    return NULL;
}

void CGc::PushProc(CProc *pproc)
{
    m_approcStack[m_cpprocStack++] = pproc;
}

CProc *CGc::PprocPop()
{
    if (m_cpprocStack >= 1)
    {
        return m_approcStack[--m_cpprocStack];
    }
    return NULL;
}

void CGc::UpdateRecyclable()
{
    g_splotheapPair.UpdateRecyclable();
    g_splotheapFrame.UpdateRecyclable();
    g_splotheapVarb.UpdateRecyclable();
    g_splotheapProc.UpdateRecyclable();
    g_splotheapMethod.UpdateRecyclable();
}

void CGc::MarkLiveObjects()
{
    CFrame *pframe;
    CProc *pproc;
    CPair *ppair;

    /* This runs continuously in a loop until we exhaust all frames, procs, and pairs.
     * It looks to be an unrolled recursion, where newly explored values get pushed to
     * respective stacks and then be explored one at a time in the loop. */
    while (true)
    {
        /* Check top frame */
        pframe = PframePop();
        if (pframe != NULL)
        {
            for (CVarb *pvarb = pframe->m_pvarb; pvarb != NULL; pvarb = pvarb->m_pvarbNext)
            {
                MarkPvAlive(pvarb);
                CRef *pref = &pvarb->m_ref;
                switch (pref->m_tagk)
                {
                    case TAGK_Pair:
                    {
                        ppair = pref->m_tag.m_ppair;
                        if (FIsPvGarbage(ppair))
                        {
                            MarkPvAlive(ppair);
                            PushPair(ppair);
                        }
                        break;
                    }
                    case TAGK_Proc:
                    {
                        pproc = pref->m_tag.m_pproc;
                        if (FIsPvGarbage(pproc))
                        {
                            MarkPvAlive(pproc);
                            PushProc(pproc);
                        }
                        break;
                    }
                    case TAGK_Method:
                    {
                        MarkPvAlive(pref->m_tag.m_pmethod);
                        break;
                    }
                }
            }

            for (int i = 0; i < pframe->m_cpframeParent; i++)
            {
                CFrame *pparent = pframe->m_apframeParent[i];
                if (FIsPvGarbage(pparent))
                {
                    MarkPvAlive(pparent);
                    PushFrame(pparent);
                }
            }
            continue;
        }

        /* Check top proc */
        pproc = PprocPop();
        if (pproc != NULL)
        {
            for (ppair = pproc->m_ppair; ppair != NULL; ppair = ppair->m_ppairNext)
            {
                MarkPvAlive(ppair);
            }

            ppair = pproc->m_ppairCodeExpr;
            if (FIsPvGarbage(ppair))
            {
                MarkPvAlive(ppair);
                PushPair(ppair);
            }

            pframe = pproc->m_pframe;
            if (FIsPvGarbage(pframe))
            {
                MarkPvAlive(pframe);
                PushFrame(pframe);
            }
            continue;
        }

        /* Check top pair */
        ppair = PpairPop();
        if (ppair != NULL)
        {
            switch (ppair->m_ref.m_tagk)
            {
                case TAGK_Pair:
                {
                    CPair *ppairChild = ppair->m_ref.m_tag.m_ppair;
                    if (FIsPvGarbage(ppairChild))
                    {
                        MarkPvAlive(ppairChild);
                        PushPair(ppairChild);
                    }
                    break;
                }
                case TAGK_Proc:
                {
                    pproc = ppair->m_ref.m_tag.m_pproc;
                    if (FIsPvGarbage(pproc))
                    {
                        MarkPvAlive(pproc);
                        PushProc(pproc);
                    }
                    break;
                }
                case TAGK_Method:
                {
                    MarkPvAlive(ppair->m_ref.m_tag.m_pmethod);
                    break;
                }
            }

            ppair = ppair->m_ppairNext;
            if (ppair != NULL && FIsPvGarbage(ppair))
            {
                MarkPvAlive(ppair);
                PushPair(ppair);
            }
            continue;
        }

        break;
    }
}

void CGc::Collect()
{
    g_splotheapPair.UnmarkAll();
    g_splotheapFrame.UnmarkAll();
    g_splotheapVarb.UnmarkAll();
    g_splotheapProc.UnmarkAll();
    g_splotheapMethod.UnmarkAll();

    int i = m_cpframeRoot;
    m_cpframeStack = 0;
    m_cppairStack = 0;
    m_cpprocStack = 0;

    /* This loop iteration structure looks weird but it seems to be required to match */
    while (--i >= 0)
    {
        CFrame *pframe = m_apframeRoot[i];
        if (FIsPvGarbage(pframe))
        {
            MarkPvAlive(pframe);
            PushFrame(pframe);
        }
    }

    /* Same comment as above on the loop structure */
    int j = m_cpsidebagRoot;
    while (--j >= 0)
    {
        CSidebag *psidebag = m_apsidebagRoot[j];
        for (CVarb *pvarb = psidebag->m_pvarb; pvarb != NULL; pvarb = pvarb->m_pvarbNext)
        {
            MarkPvAlive(pvarb);
            CRef *pref = &pvarb->m_ref;
            switch (pref->m_tagk)
            {
                case TAGK_Pair:
                {
                    CPair *ppair = pref->m_tag.m_ppair;
                    if (FIsPvGarbage(ppair))
                    {
                        MarkPvAlive(ppair);
                        PushPair(ppair);
                    }
                    break;
                }
                case TAGK_Proc:
                {
                    CProc *pproc = pref->m_tag.m_pproc;
                    if (FIsPvGarbage(pproc))
                    {
                        MarkPvAlive(pproc);
                        PushProc(pproc);
                    }
                    break;
                }
                case TAGK_Method:
                {
                    MarkPvAlive(pref->m_tag.m_pmethod);
                    break;
                }
            }
        }
    }

    for (MQ *pmq = g_psw->pmqCallbackFirst; pmq != NULL; pmq = pmq->pmqNext)
    {
        if (pmq->pfnmq == (PFNMQ)PostSpliceEventCallback)
        {
            CPair *ppair = (CPair *)pmq->pvCallbackData;
            if (ppair != NULL && FIsPvGarbage(ppair))
            {
                MarkPvAlive(ppair);
                PushPair(ppair);
            }
        }
    }

    MarkLiveObjects();
    g_splotheapPair.FreeGarbage();
    g_splotheapFrame.FreeGarbage();
    g_splotheapVarb.FreeGarbage();
    g_splotheapProc.FreeGarbage();
    g_splotheapMethod.FreeGarbage();
}

CGc g_gc;
