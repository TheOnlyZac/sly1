/**
 * @file bas.cpp
 *
 * @brief Implements for the binary async stream class.
*/
#include <bas.h>
#include <util.h>
#include <cstddef>

CBinaryAsyncStream::CBinaryAsyncStream(void* pvSpool)
{
    m_isector = 0;
    m_abSpool = reinterpret_cast<BYTE*>((reinterpret_cast<intptr_t>(pvSpool) + 0x3fU) & 0xffffffc0);
    m_fd = -1;
    m_pbSpooling = NULL;
    m_pb = NULL;
    m_cbFile = 0;
    m_cbUnspooled = 0;
    m_cbSpooling = 0;
    m_ibCur = 0;
    m_cb = 0;
}

CBinaryAsyncStream::~CBinaryAsyncStream()
{
    Close();
}

void CBinaryAsyncStream::Close()
{
    if (m_bask == BASK_Host) {
        if (-1 < m_fd) {
            //sceClose();
        }
        m_fd = -1;
    }
    else if (m_bask == BASK_Cd) {
        m_isector = 0;
    }
    m_bask = BASK_Nil;
}
