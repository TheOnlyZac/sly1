/**
 * @file stream.h
 *
 * @brief Output stream.
 */
#ifndef STREAM_H
#define STREAM_H

#include "common.h"

/**
 * @brief Output stream.
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

    /**
     * @brief Create a new output stream that writes to a file.
     *
     * @param fd File descriptor.
     */
    OSTRM(int fd);

    /**
     * @brief Create a new output stream that writes to a buffer.
     *
     * @param abDest Pointer to the destination.
     * @param cbDest Size of the destination in bytes.
     */
    OSTRM(void *abDest, int cbDest);

    ~OSTRM();

    int CbWrite(void *ab, int cb);

    void Flush();
};

#endif // STREAM_H
