#include <stream.h>

OSTRM::OSTRM(int fd)
{
    m_fd = fd;
    m_abDest = 0;
    m_cbDest = 0;
    m_ibCur = 0;
    m_cbWritten = 0;
    m_cbBuffered = 0;
}

OSTRM::OSTRM(void *abDest, int cbDest)
{
    m_abDest = (uchar *)abDest;
    m_cbDest = cbDest;
    m_fd = -1;
    m_ibCur = 0;
    m_cbWritten = 0;
    m_cbBuffered = 0;
}

OSTRM::~OSTRM()
{
    Flush();
}

INCLUDE_ASM(const s32, "P2/stream", CbWrite__5OSTRMPvi);

INCLUDE_ASM(const s32, "P2/stream", Flush__5OSTRM);
