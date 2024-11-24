#include "common.h"
#include <dmas.h>

INCLUDE_ASM(const s32, "P2/dmas", StartupDma__Fv);

DMAS::DMAS()
{
    m_fPad = 0;
    m_fEndPrim = 0;
    Clear();
}

void DMAS::Clear()
{
    m_pbMax = (uchar*)nullptr;
    m_ab = (uchar*)nullptr;
    m_pqwCnt = (QW*)nullptr;
    m_pb = (uchar*)nullptr;
}

void DMAS::Reset()
{
    m_pqwCnt = (QW*)nullptr;
    m_pb = m_ab;
}

INCLUDE_ASM(const s32, "P2/dmas", AllocGlobal__4DMASi);

INCLUDE_ASM(const s32, "P2/dmas", AllocSw__4DMASii);

INCLUDE_ASM(const s32, "P2/dmas", AllocStack__4DMASi);

INCLUDE_ASM(const s32, "P2/dmas", AllocStatic__4DMASiP2QW);

void DMAS::Detach(int* arg0, QW** arg1)
{
    EndDmaCnt();
    if (arg0 != nullptr)
    {
        *arg0 = (uint)(m_pb - m_ab) >> 4;
    }
    if (arg1 != nullptr)
    {
        *arg1 = (QW*)m_ab;
    }
    Clear();
}

INCLUDE_ASM(const s32, "P2/dmas", DetachCopySw__4DMASPiPP2QWT2i);

void DMAS::Send(sceDmaChan* chan)
{
    EndDmaCnt();
    FlushCache(WRITEBACK_DCACHE);
    sceDmaSend(chan, m_ab);
    m_pb = m_ab;
}

INCLUDE_ASM(const s32, "P2/dmas", func_00152B30);

INCLUDE_ASM(const s32, "P2/dmas", AddDmaCnt__4DMAS);

INCLUDE_ASM(const s32, "P2/dmas", AddDmaRefs__4DMASiP2QW);

INCLUDE_ASM(const s32, "P2/dmas", AddDmaCall__4DMASP2QW);

INCLUDE_ASM(const s32, "P2/dmas", AddDmaRet__4DMAS);

INCLUDE_ASM(const s32, "P2/dmas", AddDmaBulk__4DMASiP2QW);

INCLUDE_ASM(const s32, "P2/dmas", AddDmaEnd__4DMAS);

INCLUDE_ASM(const s32, "P2/dmas", EndDmaCnt__4DMAS);

void DMAS::EndPrim(void)
{
    return;
}

INCLUDE_ASM(const s32, "P2/dmas", func_00152E20);
