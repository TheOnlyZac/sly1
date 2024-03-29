/**
 * @file mpeg.h
 *
 * @brief Declarations for the MPEG system.
*/
#ifndef MPEG_H
#define MPEG_H

#include <game.h>
#include <bas.h>
#include <bq.h>
#include <libmpeg.h>

/**
 * @brief Mpeg Audio State
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
 * @brief QueueOutput IOP
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
 * @brief MPEG Audio
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
 * @brief MPEG video
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
     * @todo Function is only partially implemented, finish it.
     * @todo Double check whether oid is supposed to be a pointer.
    */
    void Execute(OID* oid);

    /**
     * @brief Starts the mpeg.
     *
     * @todo Implement this function.
    */
    void Start();

    /**
     * @brief Updates the mpeg.
     *
     * @todo Implement this function.
    */
    void Update();

    /**
     * @brief Finishes the mpeg.
     *
     * @todo Implement this function.
    */
    void Finish();
};

// Global variables
static CMpeg g_mpeg; // Current MPEG

#endif // MPEG_H
