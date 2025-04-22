/**
 * @file bq.h
 *
 * @brief Byte queue.
*/
#ifndef BQ_H
#define BQ_H

#include "common.h"
#include <util.h>

/**
 * @brief Byte Queue
*/
class CByteQueue {
    byte *m_ab;
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
