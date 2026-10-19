/**
 * @file mpeg.h
 *
 * @brief MPEG video and audio playback stream subsystem.
 */

#ifndef MPEG_H
#define MPEG_H

#include "common.h"
#include <oid.h>
#include <bas.h>

struct sceDmaChan;

/**
 * @brief MPEG callback data structure for demuxed elementary streams (video/audio).
 */
struct sceMpegCbDataStr {
    int type;
    void *header;
    void *data;
    int len;
    long long pts;
    long long dts;
};

/**
 * @brief PS2 sceMpeg library decoder state structure.
 */
struct sceMpeg {
    int width;
    int height;
    int frameCount;
    int pad_0C;
    int pts;
    int dts;
    int flags;
    int pad_1C[11];
};

struct sceMpegCbData;

/**
 * @brief Base interface for draining demuxed data to an output destination.
 */
class CQueueOutput
{
public:
    void *m_vtable;

    int CbWrite(int cb, void *pv);
    int FAsyncDrain();
};

/**
 * @brief Queue output implementation streaming audio data to IOP sound memory.
 */
class CQueueOutputIop : public CQueueOutput
{
public:
    int m_pbIop;    // 0x04: IOP destination memory address
    int m_cb;       // 0x08: Buffer capacity in bytes
    int m_ibFree;   // 0x0C: Offset to next free byte
    int m_ibAlloc;  // 0x10: Offset to next allocated byte
    int m_cbFree;   // 0x14: Available free byte count
    int m_cbAlloc;  // 0x18: Allocated byte count pending transfer
    int m_cbTotal;  // 0x1C: Total bytes transferred

    void Init(int a1, int a2);
    void Reset();
    int CbWrite(int cb, void *pv);
    int CbSend(int size, void *buf);
    void Update();
    int FAsyncDrain();
};

/**
 * @brief Queue output implementation streaming compressed video bitstream to IPU via DMA.
 */
class CQueueOutputIpu : public CQueueOutput
{
public:
    int CbWrite(int cb, void *pv);
    int FAsyncDrain();
};

/**
 * @brief Circular byte buffer queue used for intermediate streaming data.
 */
class CByteQueue
{
public:
    void *m_ab;        // 0x00: Buffer storage pointer
    int m_cb;          // 0x04: Total buffer capacity
    int m_ibFree;      // 0x08: Write index / free offset
    int m_ibAlloc;     // 0x0C: Read index / alloc offset
    int m_cbFree;      // 0x10: Remaining free space
    int m_cbAlloc;     // 0x14: Available readable bytes
    int m_cbDrain;     // 0x18: Bytes drained
    int m_cbTotal;     // 0x1C: Cumulative bytes written

    void Init(int cb, void *pv);
    void Reset();
    int CbFill(int cb, unsigned char *pb);
    int FreeDrain(int cb);
    int CbDrain(int cb, CQueueOutput *pqo);
};

/**
 * @brief Header preface for SPU audio stream chunks.
 */
struct SpuStreamHeaderPreface {
    char achId[4];
    int cbHeader;
};

/**
 * @brief Format parameters and loop points for SPU audio stream.
 */
struct SpuStreamHeader {
    int ssk;
    int hz;
    int cchan;
    int cbInterleave;
    int ibLoopStart;
    int ibLoopEnd;
};

/**
 * @brief Body preface indicating length of SPU audio payload data.
 */
struct SpuStreamBodyPreface {
    char achId[4];
    int cbBody;
};

/**
 * @brief Combined SPU stream header and body prefaces.
 */
struct SpuStreamPreface {
    SpuStreamHeaderPreface sshp;
    SpuStreamHeader ssh;
    SpuStreamBodyPreface ssbp;
};

/**
 * @brief Manages streaming MPEG audio playback, SPU buffering, and sound ducking.
 */
class CMpegAudio
{
public:
    int m_state;             // 0x00: Playback state (0=uninit, 1=header, 2=buffering, 3=playing)
    SpuStreamPreface m_ssp;  // 0x04: SPU stream preface metadata
    CByteQueue m_bqSsp;      // 0x2C: SPU preface byte queue
    CByteQueue m_bq;         // 0x4C: Main audio stream data queue
    CQueueOutputIop m_qo;    // 0x6C: IOP audio output queue
    int m_nvolDialogRestore; // 0x8C: Saved dialog volume to restore after movie
    int m_nvolGlobalRestore; // 0x90: Saved global volume to restore after movie
    void Init();
    void Reset();
    void Close();
    void Update();
    int FAccept(int cb, unsigned char *pb);
};

/**
 * @brief 16x16 macroblock decoded RGB32 pixel buffer (256 pixels).
 */
struct sceIpuRGB32 {
    uint pix[256];
};

/**
 * @brief Top-level MPEG cutscene playback controller.
 */
class CMpeg
{
public:
    OID oid_1;                  // 0x00: Cutscene index / ID currently playing
    OID oid_2;                  // 0x04: Queued cutscene OID key to play next
    void *m_poidNext;           // 0x08: Additional chained cutscene OID
    CBinaryAsyncStream *m_pbas; // 0x0C: Async stream providing MPEG file data from disc/host
    sceMpeg m_scempeg;          // 0x10: Hardware MPEG decoder context
    void *m_pbWork;             // 0x54: Work buffer for sceMpeg
    sceIpuRGB32 *m_ambDecoded;  // 0x58: Decoded macroblock RGB32 image buffer
    CByteQueue m_bqVideo;       // 0x5C: Video bitstream input queue
    CMpegAudio m_maud;          // 0x7C: Audio playback subsystem
    QW *m_aaqwGifs[2];          // 0x114: Double-buffered DMA/GIF display packets
    char pad_11C[0x130 - 0x11C];// 0x11C: Alignment padding
    int field_130;              // 0x130: Rendering thread semaphore ID
    volatile int field_134;     // 0x134: Render thread sync state flag (0=idle, 1=wait gif0, 2=drawing)
    uint field_138;             // 0x138: Anti-tamper rolling CRC32 accumulator
    uchar *field_13C;           // 0x13C: Anti-tamper text segment verification pointer
    int field_140;              // 0x140: Anti-tamper remaining bytes to verify

    /**
     * @brief Plays queued cutscene OIDs sequentially.
     */
    void ExecuteOids();

    /**
     * @brief Initiates MPEG playback for the given cutscene OID.
     *
     * @param poid Pointer to cutscene OID descriptor key.
     */
    void Execute(OID *poid);

    /**
     * @brief Initializes playback and demuxer loop for a cutscene stream.
     *
     * @param pbas Binary async stream source.
     */
    void Start(CBinaryAsyncStream *pbas);

    /**
     * @brief Progresses background anti-tamper text segment CRC32 calculation.
     */
    void FUN_0018f610();

    /**
     * @brief Decodes and presents a video frame, updating audio and sync.
     */
    void Update();

    /**
     * @brief Terminates playback, frees resources, and restores graphics state.
     */
    void Finish();

    /**
     * @brief Demuxes the next packet from the binary async stream.
     *
     * @param fBlock Whether to block waiting for data if stream buffer is empty.
     * @return Number of bytes demuxed.
     */
    int CbDemuxed(int fBlock);
};

/**
 * @brief Spawns the dedicated MPEG background display thread.
 */
void StartupMpeg();

extern CMpeg g_mpeg;

#endif // MPEG_H
