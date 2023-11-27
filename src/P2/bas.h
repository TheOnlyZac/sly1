#pragma once
#include <stdint.h>
#include <util.h>

enum class BASK : int
{
    Nil = -1,
    Cd = 1,
    Host = 0,
    Max = 2
};

class CBinaryAsyncStream
{
public:
    BASK m_bask;
    int m_fd;
    uint32_t m_isector;
    int m_cbSpooling;
    BYTE* m_pbSpooling;
    BYTE* m_abSpool;
    int m_cb;
    BYTE* m_pb;
    int m_ibCur;
    int m_cbUnspooled;
    int m_cbFile;

    CBinaryAsyncStream(void* pvSpool); // constructor
    ~CBinaryAsyncStream(); // todo destructor

    void Close(); // todo
};

