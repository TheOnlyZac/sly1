#include <splice/frame.h>
#include <splice/splotheap.h>
#include <sce/memset.h>

void CFrame::SetSingleParent(CFrame *pframeParent)
{
    m_apframeParent[0] = pframeParent;
    m_cpframeParent = 1;
}

void CFrame::AddParent(CFrame *pframeParent)
{
    m_apframeParent[m_cpframeParent++] = pframeParent;
}

INCLUDE_ASM("asm/nonmatchings/P2/splice/frame", RefAddBinding__6CFrameUiP4CRef);

INCLUDE_ASM("asm/nonmatchings/P2/splice/frame", RefSetBinding__6CFrameUiP4CRef);

INCLUDE_ASM("asm/nonmatchings/P2/splice/frame", FFindBinding__6CFrameUiiP4CRef);

INCLUDE_ASM("asm/nonmatchings/P2/splice/frame", PrefFindBinding__6CFrameUii);

INCLUDE_ASM("asm/nonmatchings/P2/splice/frame", CloneTo__6CFrameP6CFrame);

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
