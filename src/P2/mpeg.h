#pragma once
#include <bis.h>
#include <bq.h>
#include <difficulty.h>
#include <game.h>
#include <iostream>
#include <util.h>

/* Mpeg Audio State */
enum class MAUDS : int
{
    FillPreface = 1,
    FillIop = 2,
    Dead = 0,
    Pmaudse = 4,
    Play = 3,
    Max = 5
};

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

/* Todo: Derive from CQueueOutput class once that exists */
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

    void ExecuteOids();
    void Execute(OID* oid);
    void Start(); // todo
    void Update(); // todo
    void Finish(); // todo
};

static CMpeg g_mpeg;
