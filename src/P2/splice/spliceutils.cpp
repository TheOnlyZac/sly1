#include <splice/spliceutils.h>
#include <splice/frame.h>
#include <splice/gc.h>
#include <splice/pair.h>
#include <splice/splotheap.h>
#include <splice/vecmat.h>
#include <splice/varb.h>

extern CGc g_gc;

void StartupSplice()
{
    g_gc.Startup();

    g_splotheapPair.Startup(sizeof(CPair), 0x2000);
    g_splotheapPair.m_pfndelete = reinterpret_cast<PFNDELETE>(DeletePair);

    g_splotheapFrame.Startup(sizeof(CFrame), 0x190);
    g_splotheapFrame.m_pfndelete = reinterpret_cast<PFNDELETE>(DeleteFrame);

    g_splotheapVarb.Startup(sizeof(CVarb), 0x800);
    g_splotheapVarb.m_pfndelete = reinterpret_cast<PFNDELETE>(DeleteVarb);

    g_splotheapProc.Startup(sizeof(CProc), 0x800);
    StartupSpliceStructuredTypeFactories();

    g_splotheapMethod.Startup(sizeof(CMethod), 0x80);
}

void ShutdownSplice()
{
    g_splotheapPair.Shutdown();
    g_splotheapFrame.Shutdown();
    g_splotheapVarb.Shutdown();
    g_splotheapProc.Shutdown();
    ShutdownSpliceStructuredTypeFactories();
    g_splotheapMethod.Shutdown();
    g_gc.Shutdown();
}

INCLUDE_ASM("asm/nonmatchings/P2/splice/spliceutils", spliceutils__static_initialization_and_destruction_0);

INCLUDE_ASM("asm/nonmatchings/P2/splice/spliceutils", _GLOBAL_$I$g_splotheapPair);

INCLUDE_ASM("asm/nonmatchings/P2/splice/spliceutils", _GLOBAL_$D$g_splotheapPair);
