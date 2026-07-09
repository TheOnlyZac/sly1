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

CRef CFrame::RefAddBinding(uint symid, CRef *pref)
{
    CRef ref;
    void *psbb = FUN_0011C498();
    STRUCT_OFFSET(psbb, 0x0, uint) = symid;
    STRUCT_OFFSET(psbb, 0x4, CRef) = *pref;
    STRUCT_OFFSET(psbb, 0xC, void *) = STRUCT_OFFSET(this, 0x14, void *);
    STRUCT_OFFSET(this, 0x14, void *) = psbb;
    ref.SetTag(TAGK_Void);
    return ref;
}

CRef CFrame::RefSetBinding(uint symid, CRef *pref)
{
    CRef ref;
    CRef *prefFound = PrefFindBinding(symid, 1);
    if (prefFound != NULL)
    {
        *prefFound = *pref;
    }
    ref.SetTag(TAGK_Void);
    return ref;
}

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
