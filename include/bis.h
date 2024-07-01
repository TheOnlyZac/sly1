/**
 * @file bis.h
 */
#ifndef BIS_H
#define BIS_H

#include "common.h"
#include <prog.h>

/**
 * @brief Binary Input Stream Kind
 *
 * Types of binary stream that can be opened
*/
enum BISK
{
    BISK_Nil = -1,
    BISK_Host = 0,
    BISK_Cd = 1,
    BISK_Mem = 2,
    BISK_Max = 3
};

/**
 * @brief File Location
 *
 * Represents the location of a file on the disc.
*/
class CFileLocation
{
    // todo Implement class.
    // Also it maybe isn't supposed to be in this file.
};

/**
 * @brief Binary Input Stream
 *
 * Used to read binary data from files on the disc.
*/
class CBinaryInputStream
{
public:
    int m_grfbis;
    enum BISK m_bisk;
    byte* m_abSpool;
    int m_cbSpool;
    int m_cbFile;
    int m_cbRemaining; /* File Stream Remaining Bytes. */
    byte* m_pb; /* File Stream Position */
    int m_cb; /* File Stream Size */
    byte* m_pbRaw;
    int m_cbRaw;
    int m_grfDecomp;
    int m_cbSpillOver;
    CProg* m_pprog;
    uint64_t m_tickWait;
    int m_fd;
    int m_cbAsyncComplete;
    int m_cbAsyncRequest;
    int m_cbAsyncRemaining;
    int m_cbPartialRead;
    uint32_t m_isector; /* Sector Offset in ISO */
    int m_cbuf;
    int m_cbufFill;
    int m_ibufMic;
    int m_ibufMac;

    /**
     * @brief Constructs a new CBinaryInputStream.
     *
     * @param fileName Name of the file to open
     *
     * @todo Implement this constructor.
    */
    CBinaryInputStream(const char* fileName); // Used for file object

    /**
     * @brief Destroys the CBinaryInputStream.
    */
    ~CBinaryInputStream();

    /**
     * @brief Opens the file at the given location.
     *
     * First checks if the file is open and the CD is available.
     *
     * @param pfl Pointer to the file location
     *
     * @retval 0 File is not open
     * @retval 1 File is open
    */
    int  FOpenFile(CFileLocation* pfl);

    /**
     * @brief Opens the sector at the given location.
     *
     * @param isector Sector to open
     * @param cb Number of bytes to read
     *
     * @retval 0 Sector is not open
     * @retval 1 Sector is open
    */
    int  FOpenSector(uint32_t isector, uint32_t cb);

    /**
     * @brief Opens a certain number of bytes in memory.
     *
     * @param cb Number of bytes to open
     * @param pv Pointer to the memory location
    */
    void OpenMemory(int cb, void* pv);

    /**
     * @brief Decrements the number of async bytes remaining.
     *
     * @param cb Number of bytes to decrement
    */
    void DecrementCdReadLimit(int cb);

    /**
     * @brief Reads a certain number of bytes from the stream.
     *
     * Will read a certain number of bytes from the stream and store them at the
     * given location.
     *
     * @param cb Number of bytes to read
     * @param pv Pointer to the memory location
    */
    void Read(int cb, void *pv);

    /**
     * @brief Aligns the stream to a certain number of bytes.
     *
     * @param n Number of bytes to align to
    */
    void Align(int n);

    /**
     * @brief Reads a byte from the stream.
     *
     * @return The byte read
    */
    byte U8Read();

    /**
     * @brief Reads a 16-bit unsigned integer from the stream.
     *
     * @return The 16-bit unsigned integer read
    */
    uint16_t U16Read();

    /**
     * @brief Reads a 32-bit unsigned integer from the stream.
     *
     * @return The 32-bit unsigned integer read
    */
    uint32_t U32Read();

    /**
     * @brief Reads a 8-bit signed integer from the stream.
     *
     * @return The 8-bit signed integer read
    */
    int8_t S8Read();

    /**
     * @brief Reads a 16-bit signed integer from the stream.
     *
     * @return The 16-bit signed integer read
    */
    int16_t S16Read();

    /**
     * @brief Reads a 32-bit signed integer from the stream.
     *
     * @return The 32-bit signed integer read
    */
    int32_t S32Read();

    /**
     * @brief Reads a 32-bit floating point number from the stream.
     *
     * @return The 32-bit floating point number read
    */
    float F32Read();

    /**
     * @brief Reads a string from the stream.
     *
     * @param pachz Pointer where the string will be stored
    */
    void ReadStringSw(char** pachz);

    /**
     * @brief Closes the stream.
    */
    void Close();
};

#endif // BIS_H
