#include <splice/gc.h>
#include <splice/splotheap.h>
#include <splice/spliceutils.h>

CGc g_gc;

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
    g_splotheapUnk1.UpdateRecyclable();
    g_splotheapProc.UpdateRecyclable();
    g_splotheapMethod.UpdateRecyclable();
}

INCLUDE_ASM("asm/nonmatchings/P2/splice/gc", MarkLiveObjects__3CGc);

INCLUDE_ASM("asm/nonmatchings/P2/splice/gc", Collect__3CGc);
