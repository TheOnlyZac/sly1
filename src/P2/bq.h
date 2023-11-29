#pragma once

typedef unsigned char BYTE; //todo mode to util header

class CByteQueue {
    BYTE* m_ab;
    int m_cb;
    int m_ibFree;
    int m_ibAlloc;
    int m_cbFree;
    int m_cbAlloc;
    int m_cbDrain;
    int m_cbTotal;

    // todo: class methods
};
