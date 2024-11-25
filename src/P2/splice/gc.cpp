#include <splice/gc.h>
#include <splice/splotheap.h>
#include <splice/spliceutils.h>

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
    return (CFrame *)nullptr;
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
    return (CPair *)nullptr;
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
    return (CProc *)nullptr;
}

void CGc::UpdateRecyclable()
{
    g_splotheapPair.UpdateRecyclable();
    g_splotheapFrame.UpdateRecyclable();
    g_splotheapUnk1.UpdateRecyclable();
    g_splotheapProc.UpdateRecyclable();
    g_splotheapMethod.UpdateRecyclable();
}

INCLUDE_ASM(const s32, "P2/splice/gc", MarkLiveObjects__3CGc);

INCLUDE_ASM(const s32, "P2/splice/gc", Collect__3CGc);

// The functions below are compiler generated and their INCLUDE_ASM can just be removed once g_gc is defined
// Currently blocked until references to g_gc are resolved

INCLUDE_ASM(const s32, "P2/splice/gc", gc__static_initialization_and_destruction_0);

INCLUDE_ASM(const s32, "P2/splice/gc", _GLOBAL_$I$g_gc);

INCLUDE_ASM(const s32, "P2/splice/gc", _GLOBAL_$D$g_gc);
