#include <bq.h>

void CByteQueue::Init(int cb, void *pv)
{
    m_cb = cb;
    m_ab = (byte *)pv;
    Reset();
}

void CByteQueue::Reset()
{
    m_cbFree = m_cb;
    m_cbDrain = 0;
    m_cbAlloc = 0;
    m_ibAlloc = 0;
    m_ibFree = 0;
    m_cbTotal = 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/bq", CbFill__10CByteQueueiP11CQueueInput);

INCLUDE_ASM("asm/nonmatchings/P2/bq", CbDrain__10CByteQueueiP12CQueueOutput);

extern int D_00249D98[];

int CByteQueue::CbFill(int cb, byte *pb)
{
    int cbRead;

    if (cb == 0)
    {
        cbRead = 0;
    }
    else
    {
        // Stack CQueueInputMemory: vtable ptr (D_00249D98 = __vt_17CQueueInputMemory in
        // rodata), pb @0x4, cb @0x8, ib (read cursor) @0xC, cb remaining @0x10
        struct
        {
            void *pvt;
            byte *pb;
            int cb;
            int ib;
            int cbTotal;
        } qim;

        qim.pb = pb;
        qim.pvt = D_00249D98;
        qim.cbTotal = cb;
        qim.cb = cb;
        qim.ib = 0;
        cbRead = CbFill(cb, (CQueueInput *)&qim);
    }

    return cbRead;
}

void CByteQueue::FreeDrain(int cb)
{
    if (cb == 0)
    {
        cb = m_cbDrain;
        if (cb == 0)
        {
            return;
        }
    }

    m_cbFree += cb;
    m_cbDrain -= cb;
}

INCLUDE_ASM("asm/nonmatchings/P2/bq", CbRead__17CQueueInputMemoryiPv);

INCLUDE_ASM("asm/nonmatchings/P2/bq", CbRead__15CQueueInputFileiPv);

JUNK_WORD(0xAC80000C);
