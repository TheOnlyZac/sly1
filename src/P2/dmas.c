#include <dmas.h>
#include <sce/libdma.h>
#include <sdk/ee/eestruct.h>
#include <memory.h>

extern sceDmaChan *g_pdcVif0;
extern sceDmaChan *g_pdcVif1;
extern sceDmaChan *g_pdcGif;
extern sceDmaChan *g_pdcFromSpr;
extern sceDmaChan *g_pdcToSpr;

void StartupDma()
{
    sceDmaReset(1);
    sceGsResetPath();
    g_pdcVif0 = sceDmaGetChan(0);
    g_pdcVif1 = sceDmaGetChan(1);
    g_pdcGif = sceDmaGetChan(2);
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
    m_pbMax = NULL;
    m_ab = NULL;
    m_pqwCnt = NULL;
    m_pb = NULL;
}

void DMAS::Reset()
{
    m_pqwCnt = NULL;
    m_pb = m_ab;
}

INCLUDE_ASM("asm/nonmatchings/P2/dmas", AllocGlobal__4DMASi);

INCLUDE_ASM("asm/nonmatchings/P2/dmas", AllocSw__4DMASii);

INCLUDE_ASM("asm/nonmatchings/P2/dmas", AllocStack__4DMASi);

void DMAS::AllocStatic(int c, QW *aqw)
{
    m_ab = (uchar *)aqw;
    m_pb = (uchar *)aqw;
    m_pbMax = (uchar *)(aqw + c);
}

void DMAS::Detach(int *pcqw, QW **paqw)
{
    EndDmaCnt();
    if (pcqw)
    {
        *pcqw = (uint)(m_pb - m_ab) >> 4;
    }
    if (paqw)
    {
        *paqw = (QW *)m_ab;
    }
    Clear();
}

INCLUDE_ASM("asm/nonmatchings/P2/dmas", DetachCopySw__4DMASPiPP2QWT2i);

void DMAS::Send(sceDmaChan *chan)
{
    EndDmaCnt();
    FlushCache(WRITEBACK_DCACHE);
    sceDmaSend(chan, m_ab);
    m_pb = m_ab;
}

JUNK_NOP();
JUNK_ADDIU(10);

void DMAS::AddDmaCnt()
{
    EndDmaCnt();
    QW *pqw = (QW *)m_pb;
    m_pqwCnt = pqw;
    m_pb += sizeof(QW);
    pqw->aul[0] = 0x10000000;
    m_pqwCnt->aul[1] = 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/dmas", AddDmaRefs__4DMASiP2QW);

INCLUDE_ASM("asm/nonmatchings/P2/dmas", AddDmaCall__4DMASP2QW);

void DMAS::AddDmaRet()
{
    EndDmaCnt();
    uchar *pb = m_pb;
    m_pb = pb + 0x10;
    *(ulong *)pb = 0x60000000;
    *(ulong *)(pb + 8) = 0;
}

void DMAS::AddDmaBulk(int c, QW *aqw)
{
    CopyAqw(m_pb, aqw, c);
    m_pb += c * sizeof(QW);
}

void DMAS::AddDmaEnd()
{
    EndDmaCnt();
    QW *pqw = (QW *)m_pb;
    m_pb += sizeof(QW);
    pqw->aul[0] = 0x70000000;
    pqw->aul[1] = 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/dmas", EndDmaCnt__4DMAS);

void DMAS::EndPrim()
{
    return;
}

JUNK_WORD(0x00021102);
