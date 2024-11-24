#include "common.h"
#include <sce/memset.h>
#include <splice/proc.h>
#include <splice/splotheap.h>

void CProc::CloneTo(CProc *pprocClone, CFrame *pframeClone)
{
    if (pframeClone == nullptr)
    {
        pframeClone = m_pframe;
    }
    pprocClone->m_pframe = pframeClone;
    pprocClone->m_ppair = m_ppair;
    pprocClone->m_crefReq = m_crefReq;
    pprocClone->m_fVarArg = m_fVarArg;
    pprocClone->m_ppairCodeExpr = m_ppairCodeExpr;
}

// todo: matches but blocked by references in CRef::CloneTo and RefEvalLambda
INCLUDE_ASM(const s32, "P2/splice/proc", PprocNew__Fv);
// static CProc* PprocNew() {
//     CProc* proc = (CProc*)g_splotheapProc.PvAllocClear();
//     memset(proc, 0, sizeof(CProc));
//     return proc;
// }
