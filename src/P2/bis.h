#pragma once
#include <bas.h>
#include <cat.h>
#include <prog.h>
#include <iostream>
#include <fstream>
#include <stdint.h>

typedef unsigned char byte;

// Types of binary stream to open up
enum class BISK : int{
    Nil = -1,
    Host = 0,
    Cd = 1,
    Mem = 2,
    Max = 3
};

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
    struct CProg* m_pprog;
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

    std::ifstream file; /* WE NEED THIS TO LOAD FILES */

    CBinaryInputStream(std::string fileName); // Used for file object

    int  FOpenFile(CFileLocation* pfl);
    int  FOpenSector(uint32_t isector, uint32_t cb); 
    void OpenMemory(int cb, void* pv);
    void DecrementCdReadLimit(int cb);

    void Read(int cb, void *pv);
    void Read_Modified(int cb, void* pv); // Used for file object
    void Align(int n);
    void Align_Modified(int n); // Used for file object
    byte U8Read();
    byte U8Read_Modified(); // Used for file object
    uint16_t U16Read();
    uint16_t U16Read_Modified(); // Used for file object
    uint32_t U32Read();
    uint32_t U32Read_Modified(); // Used for file object
    int8_t S8Read();
    int8_t S8Read_Modified(); // Used for file object
    int16_t S16Read();
    int16_t S16Read_Modified(); // Used for file object
    int32_t S32Read();
    int32_t S32Read_Modified(); // Used for file object
    float F32Read();
    float F32Read_Modified(); // Used for file object
    void ReadStringSw(char** pachz);
    void Close();
    void Close_Modified(); // Used for file object

    ~CBinaryInputStream();
};

static uint32_t g_fCdAvailable;
