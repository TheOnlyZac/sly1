/**
 * @file stream.h
 */
#ifndef STREAM_H
#define STREAM_H

#include "common.h"

/**
 * @brief Output stream.
 *
 * @note Based on May proto.
 */
struct OSTRM
{
    uchar *m_abDest;
    int m_cbDest;
    int m_ibCur;
    int m_fd;
    int m_cbWritten;
    int m_cbBuffered;
    uchar m_abBuffered[1024];
};

#endif // STREAM_H
