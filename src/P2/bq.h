/**
 * @file bq.h
 *
 * @brief Declares the byte queue class.
*/
#ifndef BQ_H
#define BQ_H

#include <util.h>

/**
 * @brief Byte Queue
*/
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

#endif // BQ_H
