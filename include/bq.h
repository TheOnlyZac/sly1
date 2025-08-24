/**
 * @file bq.h
 *
 * @brief Byte queue.
*/
#ifndef BQ_H
#define BQ_H

#include "common.h"

/**
 * @brief TODO.
 */
class CQueueInput
{
public:
    virtual int CbRead(int cb, void *pv);
};

/**
 * @brief TODO.
 */
class CQueueOutput
{
    // ...
};

/**
 * @brief TODO.
 */
class CQueueInputMemory : public CQueueInput
{
public:
    int CbRead(int cb, void *pv);
};

/**
 * @brief TODO.
 */
class CQueueInputFile : public CQueueInput
{
public:
    int CbRead(int cb, void *pv);
};

/**
 * @brief Byte Queue.
*/
class CByteQueue
{
public:
    byte *m_ab;
    int m_cb;
    int m_ibFree;
    int m_ibAlloc;
    int m_cbFree;
    int m_cbAlloc;
    int m_cbDrain;
    int m_cbTotal;

    /**
     * @brief Initialize the byte queue.
     *
     * @param cb Number of bytes.
     * @param pv Pointer to the data.
     */
    void Init(int cb, void *pv);

    /**
     * @brief Reset the byte queue.
     */
    void Reset();

    /**
     * @brief TODO.
     *
     * @param cb Number of bytes.
     * @param pqi Pointer to the input.
     */
    int CbFill(int cb, CQueueInput *pqi);

    /**
     * @brief TODO.
     *
     * @param cb Number of bytes.
     * @param pqo Pointer to the output.
     */
    int CbDrain(int cb, CQueueOutput *pqo);

    /**
     * @brief TODO.
     *
     * @param cb Number of bytes.
     * @param pb Pointer to the data.
     */
    int CbFill(int cb, byte *pb);

    /**
     * @brief Drain bytes from the byte queue.
     *
     * @param cb Number of bytes to drain.
     */
    void FreeDrain(int cb);
};

#endif // BQ_H
