/**
 * @file bas.h
 *
 * @brief Binary Async Stream.
*/
#ifndef BAS_H
#define BAS_H

#include "common.h"
#include <util.h>
#include <cat.h>

/**
 * @brief Binary Async Stream Kind.
*/
enum BASK
{
    BASK_Nil = -1,
    BASK_Host = 0,
    BASK_Cd = 1,
    BASK_Max = 2
};

/**
 * @brief Binary Async Stream.
 */
class CBinaryAsyncStream
{
public:
    BASK m_bask;
    int m_fd;
    uint m_isector;
    int m_cbSpooling;
    byte* m_pbSpooling;
    byte* m_abSpool;
    int m_cb;
    byte* m_pb;
    int m_ibCur;
    int m_cbUnspooled;
    int m_cbFile;

    /**
     * @brief Constructs a new CBinaryAsyncStream.
     *
     * @param pvSpool Pointer to the spool
     */
    CBinaryAsyncStream(void* pvSpool);

    /**
     * @brief Destroys the CBinaryAsyncStream.
     */
    ~CBinaryAsyncStream();

    /**
     * @brief Opens the file at the given location.
     *
     * First checks if the file is open and the CD is available.
     *
     * @param pfl Pointer to the file location.
     *
     * @retval false File is not open.
     * @retval true File is open.
     */
    bool FOpenFile(CFileLocation *pfl);

    /**
     * @brief Opens the sector at the given location.
     *
     * @param isector Sector to open.
     * @param cb Number of bytes to read.
     *
     * @retval false Sector is not open.
     * @retval true Sector is open.
     */
    bool FOpenSector(uint isector, uint cb);

    /**
     * @brief Closes the stream.
     */
    void Close();

    /**
     * @brief Start spooling.
     */
    void StartSpooling();

    /**
     * @brief TODO.
     */
    bool FSpooling();

    /**
     * @brief Check if spooling is complete.
     */
    bool FSpoolingComplete();

    /**
     * @brief Finish spooling.
     */
    void FinishSpooling();

    /**
     * @brief TODO.
     */
    void Spool();

    /**
     * @brief Skip bytes.
     */
    void Skip(int cb);
};

#endif // BAS_H
