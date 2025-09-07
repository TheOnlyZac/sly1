#include <dmas.h>
#include <sce/libdma.h>
#include <sdk/ee/eestruct.h>

extern sceDmaChan *g_pdcVif0;
extern sceDmaChan *g_pdcVif1;
extern sceDmaChan *g_pdcGiftag;
extern sceDmaChan *g_pdcFromSpr;
extern sceDmaChan *g_pdcToSpr;

void StartupDma()
{
    sceDmaReset(1);
    sceGsResetPath();
    g_pdcVif0 = sceDmaGetChan(0);
    g_pdcVif1 = sceDmaGetChan(1);
    g_pdcGiftag = sceDmaGetChan(2);
    g_pdcFromSpr = sceDmaGetChan(8);
    g_pdcToSpr = sceDmaGetChan(9);
}

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

void DMAS::EndPrim()
{
    return;
}

INCLUDE_ASM(const s32, "P2/dmas", func_00152E20);
