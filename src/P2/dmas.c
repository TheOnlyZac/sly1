#include <dmas.h>
#include <memory.h>
#include <sce/libdma.h>
#include <sdk/ee/eestruct.h>

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

void DMAS::AllocGlobal(int cqw)
{
    m_ab = (uchar *)PvAllocGlobalImpl(cqw * sizeof(QW));
    m_pb = m_ab;
    m_pbMax = m_ab + (cqw * sizeof(QW));
}

void DMAS::AllocSw(int cqw, int bk)
{
    m_ab = (uchar *)PvAllocSwImpl(cqw * sizeof(QW));
    m_pb = m_ab;
    m_pbMax = m_ab + (cqw * sizeof(QW));
}

void DMAS::AllocStack(int cqw)
{
    m_ab = (uchar *)PvAllocStackImpl(cqw * sizeof(QW));
    m_pb = m_ab;
    m_pbMax = m_ab + (cqw * sizeof(QW));
}

void DMAS::AllocStatic(int cqw, QW *aqw)
{
    m_ab = (uchar *)aqw;
    m_pb = (uchar *)aqw;
    m_pbMax = (uchar *)(aqw + cqw);
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

void DMAS::DetachCopySw(int *pcqw, QW **paqw, QW **paqwCopy, int bk)
{
    EndDmaCnt();

    uint cqw = (uint)(m_pb - m_ab) >> 4;
    if (pcqw)
    {
        *pcqw = cqw;
    }
    if (paqw)
    {
        *paqw = (QW *)m_ab;
    }
    if (paqwCopy)
    {
        *paqwCopy = (QW *)PvAllocSwCopyImpl(cqw << 4, m_ab);
    }

    Clear();
}

void DMAS::Send(sceDmaChan *pdc)
{
    EndDmaCnt();
    FlushCache(WRITEBACK_DCACHE);
    sceDmaSend(pdc, m_ab);
    m_pb = m_ab;
}

JUNK_NOP();
JUNK_ADDIU(10);

void DMAS::AddDmaCnt()
{
    EndDmaCnt();
    QW *pqw = (QW *)m_pb;
    m_pqwCnt = pqw;
    m_pb = (uchar *)(pqw + 1);
    m_pqwCnt->aul[0] = 0x10000000;
    m_pqwCnt->aul[1] = 0;
}

/**
 * @todo 86.42% match.
 */
INCLUDE_ASM("asm/nonmatchings/P2/dmas", AddDmaRefs__4DMASiP2QW);
#ifdef SKIP_ASM
void DMAS::AddDmaRefs(int cqw, QW *aqw)
{
    if (m_pqwCnt)
    {
        EndDmaCnt();
    }

    QW *pqw = ((QW *)m_pb)++;
    pqw->aul[0] = cqw | 0x40000000 | ((ulong)aqw << 0x20);
    pqw->aul[1] = 0;

    if (m_pqwCnt)
    {
        QW *pqw = (QW *)m_pb;
        m_pqwCnt = pqw;
        m_pb = (uchar *)(pqw + 1);
        m_pqwCnt->aul[0] = 0x10000000;
        m_pqwCnt->aul[1] = 0;
    }
}
#endif // SKIP_ASM

/**
 * @todo 85.12% match.
 */
INCLUDE_ASM("asm/nonmatchings/P2/dmas", AddDmaCall__4DMASP2QW);
#ifdef SKIP_ASM
void DMAS::AddDmaCall(QW *aqw)
{
    if (m_pqwCnt)
    {
        EndDmaCnt();
    }

    QW *pqw = ((QW *)m_pb)++;
    pqw->aul[0] = ((ulong)aqw << 0x20) | 0x50000000;
    pqw->aul[1] = 0;

    if (m_pqwCnt)
    {
        QW *pqw = (QW *)m_pb;
        m_pqwCnt = pqw;
        m_pb = (uchar *)(pqw + 1);
        m_pqwCnt->aul[0] = 0x10000000;
        m_pqwCnt->aul[1] = 0;
    }
}
#endif // SKIP_ASM

void DMAS::AddDmaRet()
{
    EndDmaCnt();
    QW *pqw = ((QW *)m_pb)++;
    pqw->aul[0] = 0x60000000;
    pqw->aul[1] = 0;
}

void DMAS::AddDmaBulk(int cqw, QW *aqw)
{
    CopyAqw(m_pb, aqw, cqw);
    m_pb += (cqw * sizeof(QW));
}

void DMAS::AddDmaEnd()
{
    EndDmaCnt();
    QW *pqw = ((QW *)m_pb)++;
    pqw->aul[0] = 0x70000000;
    pqw->aul[1] = 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/dmas", EndDmaCnt__4DMAS);

void DMAS::EndPrim()
{
    return;
}

JUNK_WORD(0x00021102);
