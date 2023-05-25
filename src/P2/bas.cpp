#include <bas.h>

CBinaryAsyncStream::CBinaryAsyncStream(void* pvSpool)
{
    m_isector = 0;
    m_abSpool = (BYTE*)((intptr_t)pvSpool + 0x3fU & 0xffffffc0);
    m_fd = -1;
    m_pbSpooling = NULL;
    m_pb = NULL;
    m_cbFile = 0;
    m_cbUnspooled = 0;
    m_cbSpooling = 0;
    m_ibCur = 0;
    m_cb = 0;
}

void CBinaryAsyncStream::Close()
{
    if (m_bask == BASK::Host) {
        if (-1 < m_fd) {
            //sceClose();
        }
        m_fd = -1;
    }
    else if (m_bask == BASK::Cd) {
        m_isector = 0;
    }
    m_bask = BASK::Nil;
}

CBinaryAsyncStream::~CBinaryAsyncStream()
{
    Close();
}
