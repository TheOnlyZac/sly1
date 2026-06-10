#include <splice/frame.h>
#include <splice/ref.h>
#include <splice/splotheap.h>
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

INCLUDE_ASM("asm/nonmatchings/P2/splice/frame", RefAddBinding__6CFrameUiP4CRef);

INCLUDE_ASM("asm/nonmatchings/P2/splice/frame", RefSetBinding__6CFrameUiP4CRef);

int CFrame::FFindBinding(uint symid, int fRecursive, CRef *pref)
{
    CRef *prefFound = PrefFindBinding(symid, fRecursive);
    if (prefFound != NULL)
    {
        if (pref != NULL)
        {
            *pref = *prefFound;
        }
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/splice/frame", PrefFindBinding__6CFrameUii);

void CFrame::CloneTo(CFrame *pframeClone)
{
    pframeClone->m_cpframeParent = m_cpframeParent;
    CopyAb(pframeClone->m_apframeParent, m_apframeParent, m_cpframeParent * 4);
    // binding-node list head at +0x14 (same node type as CSidebag)
    if (STRUCT_OFFSET(this, 0x14, void *) != NULL)
    {
        void *psbb = FUN_0011C498();
        FUN_0011C418(STRUCT_OFFSET(this, 0x14, void *), psbb, pframeClone);
        STRUCT_OFFSET(pframeClone, 0x14, void *) = psbb;
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
