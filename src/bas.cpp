#include <bas.h>

CBinaryAsyncStream::CBinaryAsyncStream(void* pvSpool)
{
    this->m_isector = 0;
    this->m_abSpool = (BYTE*)((int)pvSpool + 0x3fU & 0xffffffc0);
    this->m_fd = -1;
    this->m_pbSpooling = NULL;
    this->m_pb = NULL;
    this->m_cbFile = 0;
    this->m_cbUnspooled = 0;
    this->m_cbSpooling = 0;
    this->m_ibCur = 0;
    this->m_cb = 0;
}
