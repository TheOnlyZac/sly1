#pragma once
#include <bis.h>
#include <bq.h>
#include <clock.h>
#include <cat.h>
#include <gs.h>
#include <joy.h>
#include <difficulty.h>
#include <game.h>
#include <iostream>
#include <util.h>

/**
 * Mpeg Audio State
*/
enum MAUDS
{
    MAUDS_Dead = 0,
    MAUDS_FillPreface = 1,
    MAUDS_FillIop = 2,
    MAUDS_Play = 3,
    MAUDS_Pmaudse = 4,
    MAUDS_Max = 5
};

/**
 * MPEG video info
*/
struct sceMpeg {
    int width;
    int height;
    int frameCount;
    undefined4 field_0xc; // unknown
    long pts;
    long dts;
    unsigned long flags;
    long pts2nd;
    long dts2nd;
    unsigned long flags2nd;
    void* sys;
};

/**
 * QueueOutput IOP
 * Todo: Inherit from CQueueOutput class once that exists
*/
class CQueueOutputIop /* : public CQueueOutput */
{
private:
    unsigned int field_0x4;
    int m_cb;
    int m_ibFree;
    int m_ibAlloc;
    int m_cbFree;
    int m_cbAlloc;
    int m_cbTotal;
};

/**
 * MPEG Audio
*/
class CMpegAudio
{
    MAUDS m_mauds; // current state
    /* todo: define struct
    SpuStreamPreface m_ssp; */
    CByteQueue m_bqSsp;
    CByteQueue m_bq;
    CQueueOutputIop m_qoi;
    int m_nvolDialogRestore;
    int m_nvolGlobalRestore;

    // todo: class methods
};

/**
 * MPEG video
*/
class CMpeg
{
public:
    char* m_pchzPss;
    OID oid_1;
    OID oid_2;
    int m_odev;
    sceMpeg m_scempeg;
    CBinaryAsyncStream* m_pbas;
    BYTE* m_pbWork;
    CByteQueue m_bqVideo;
    CMpegAudio m_maud;
    unsigned int m_aaqwGifs[2]; // todo: fix type
    uint32_t m_chsyncIdleReading;
    /* todo: define data type
    tGS_DISPFB2 m_dispfb1;
    tGS_DISPFB2 m_dispfb2; */
    BYTE field_0x12e;
    BYTE field_0x12f;

    /**
     * @brief Executes the mpegs stored as OIDs on the mpeg struct.
     *
     * @note Unofficial name
    */
    void ExecuteOids();

    /**
     * @brief Executes the mpeg with the given oid.
     *
     * @param oid Pointer to the oid
     *
     * @todo Function is only partially implemented.
     * @todo Double check whether oid is supposed to be a pointer.
    */
    void Execute(OID* oid); //  todo

    /**
     * @brief Starts the mpeg.
     *
     * @todo Implement this function.
    */
    void Start(); // todo

    /**
     * @brief Updates the mpeg.
     *
     * @todo Implement this function.
    */
    void Update(); // todo

    /**
     * @brief Finishes the mpeg.
     *
     * @todo Implement this function.
    */
    void Finish(); // todo
};

// Global variables
static CMpeg g_mpeg;
