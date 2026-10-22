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
#include <sdk/ee/libipu.h>
#include <sdk/ee/libmpeg.h>
#include <sdk/ee/spustrm.h>

/**
 * @brief MPEG Audio State.
 */
enum MAUDS
{
    MAUDS_Nil = -1,
    MAUDS_Dead = 0,
    MAUDS_FillPreface = 1,
    MAUDS_FillIop = 2,
    MAUDS_Play = 3,
    MAUDS_Pmaudse = 4,
    MAUDS_Max = 5,
};

/**
 * @brief Base interface for draining demuxed data to an output destination.
 */
class CQueueOutput
{
public:
    void *m_vtable;

    /**
     * @brief Writes data to the queue output destination.
     */
    int CbWrite(int cb, void *pv);

    /**
     * @brief Checks if queue output has drained asynchronously.
     */
    int FAsyncDrain();
};

/**
 * @brief Queue output implementation streaming audio data to IOP sound memory.
 */
class CQueueOutputIop : public CQueueOutput
{
public:
    /* 0x04 */ int m_pbIop;
    /* 0x08 */ int m_cb;
    /* 0x0c */ int m_ibFree;
    /* 0x10 */ int m_ibAlloc;
    /* 0x14 */ int m_cbFree;
    /* 0x18 */ int m_cbAlloc;
    /* 0x1c */ int m_cbTotal;

    /**
     * @brief Initializes the IOP output queue with buffer capacity and destination address.
     *
     * @param a1 Queue capacity in bytes.
     * @param a2 Destination memory address on IOP.
     */
    void Init(int a1, int a2);

    /**
     * @brief Resets IOP output queue pointers and byte counters.
     */
    void Reset();

    /**
     * @brief Clamps and transfers audio stream data to IOP memory in 1KB chunks.
     *
     * @param cb Number of bytes to write.
     * @param pv Source buffer containing audio stream data.
     * @return Total number of bytes sent to IOP.
     */
    int CbWrite(int cb, void *pv);

    /**
     * @brief Sends an audio buffer chunk to IOP sound memory via SIF DMA.
     *
     * @param cb Number of bytes to transfer.
     * @param pv Pointer to data buffer.
     * @return Number of bytes transferred.
     */
    int CbSend(int cb, void *pv);

    /**
     * @brief Updates IOP audio stream buffer state and available free space.
     */
    void Update();

    /**
     * @brief Checks if IOP output queue has drained asynchronously.
     *
     * @return Always 0 (synchronous transfers).
     */
    int FAsyncDrain();
};

/**
 * @brief Queue output implementation streaming compressed video bitstream to IPU via DMA.
 */
class CQueueOutputIpu : public CQueueOutput
{
public:
    /**
     * @brief Transmits compressed video macroblock bitstream to IPU via DMA.
     *
     * @param cb Number of bytes to send (max 4KB, 16-byte aligned).
     * @param pv Source bitstream buffer.
     * @return Bytes transferred.
     */
    int CbWrite(int cb, void *pv);

    /**
     * @brief Checks if IPU output queue drain operation is asynchronous.
     *
     * @return Always 1 (asynchronous DMA to IPU).
     */
    int FAsyncDrain();
};

/**
 * @brief Circular byte buffer queue used for intermediate streaming data.
 */
class CByteQueue
{
public:
    /* 0x00 */ void *m_ab;
    /* 0x04 */ int m_cb;
    /* 0x08 */ int m_ibFree;
    /* 0x0c */ int m_ibAlloc;
    /* 0x10 */ int m_cbFree;
    /* 0x14 */ int m_cbAlloc;
    /* 0x18 */ int m_cbDrain;
    /* 0x1c */ int m_cbTotal;

    /**
     * @brief Initializes byte queue storage buffer and capacity.
     *
     * @param cb Buffer capacity in bytes.
     * @param pv Buffer pointer.
     */
    void Init(int cb, void *pv);

    /**
     * @brief Resets byte queue pointers and byte counters.
     */
    void Reset();

    /**
     * @brief Copies data into the byte queue ring buffer.
     *
     * @param cb Number of bytes to copy.
     * @param pb Source buffer.
     * @return Number of bytes actually written.
     */
    int CbFill(int cb, unsigned char *pb);

    /**
     * @brief Advances alloc pointer without writing.
     *
     * @param cb Number of bytes to advance.
     * @return 1 on success.
     */
    int FreeDrain(int cb);

    /**
     * @brief Drains bytes from queue into specified CQueueOutput sink.
     *
     * @param cb Number of bytes to drain.
     * @param pqo Destination output queue sink.
     * @return Number of bytes transferred.
     */
    int CbDrain(int cb, CQueueOutput *pqo);
};

/**
 * @brief Manages streaming MPEG audio playback, SPU buffering, and sound ducking.
 */
class CMpegAudio
{
public:
    /* 0x00 */ MAUDS m_mauds;
    /* 0x04 */ SpuStreamPreface m_ssp;
    /* 0x2c */ CByteQueue m_bqSsp;
    /* 0x4c */ CByteQueue m_bq;
    /* 0x6c */ CQueueOutputIop m_qoi;
    /* 0x8c */ int m_nvolDialogRestore;
    /* 0x90 */ int m_nvolGlobalRestore;

    /**
     * @brief Initializes MPEG streaming audio, pausing game sounds and setting movie volume.
     */
    void Init();

    /**
     * @brief Resets movie sound stream and internal byte queues.
     */
    void Reset();

    /**
     * @brief Closes movie sound and restores global audio volumes and reverb.
     */
    void Close();

    /**
     * @brief Drives audio queue playback states and feeds IOP audio ring buffer.
     */
    void Update();

    /**
     * @brief Ingests demuxed audio packets into preface and audio byte queues.
     *
     * @param cb Size of incoming audio packet.
     * @param pb Pointer to audio packet data.
     * @return 1 on success, 0 on failure or insufficient queue space.
     */
    int FAccept(int cb, unsigned char *pb);
};

/**
 * @brief Top-level MPEG cutscene playback controller.
 */
class CMpeg
{
public:
    /* 0x000 */ OID oid_1;
    /* 0x004 */ OID oid_2;
    /* 0x008 */ void *m_poidNext;
    /* 0x00c */ CBinaryAsyncStream *m_pbas;
    /* 0x010 */ sceMpeg m_scempeg;
    /* 0x054 */ void *m_pbWork;
    /* 0x058 */ sceIpuRGB32 *m_ambDecoded;
    /* 0x05c */ CByteQueue m_bqVideo;
    /* 0x07c */ CMpegAudio m_maud;
    /* 0x114 */ QW *m_aaqwGifs[2];
    /* 0x11c */ STRUCT_PADDING(5);
    /* 0x130 */ int field_130;
    /* 0x134 */ volatile int field_134;
    /* 0x138 */ uint field_138;
    /* 0x13c */ uchar *field_13C;
    /* 0x140 */ int field_140;

    /**
     * @brief Queues the cutscene specified by key into the MPEG player and marks it unlocked.
     *
     * @param key Pointer to cutscene OID key descriptor.
     */
    void FUN_0018f0e8(void *key);

    /**
     * @brief Plays queued cutscene OIDs sequentially.
     */
    void ExecuteOids();

    /**
     * @brief Initiates MPEG playback for the given cutscene OID.
     *
     * @param poid Pointer to cutscene OID descriptor key.
     */
    void Execute(void *poid);

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
 * @brief Looks up the cutscene index (0-15) corresponding to an OID key descriptor.
 *
 * @param key Pointer to cutscene OID entry.
 * @return Cutscene index in [0, 15], or -1 if not found.
 */
int FUN_0018e410(void *key);

/**
 * @brief Retrieves the display name string for a cutscene by index.
 *
 * @param index Cutscene index.
 * @return Pointer to cutscene name string, or fallback string if index is out of bounds.
 */
void *FUN_0018e480(int index);

/**
 * @brief Sets the next cutscene to play and marks it unlocked in the game state.
 *
 * @param index Cutscene index to unlock and queue.
 */
void FUN_0018e4c0(int index);

/**
 * @brief Unlocks and queues a primary and secondary cutscene pair.
 *
 * @param index1 Primary cutscene index to queue for playback.
 * @param index2 Secondary cutscene index to mark unlocked in game state.
 */
void FUN_0018e4f0(int index1, int index2);

/**
 * @brief Background display thread procedure for double-buffered GIF rendering.
 *
 * @details Waits on semaphore field_130, then executes DMA transfers of GIF packets
 *          to present decoded MPEG frames to the GS framebuffer.
 *
 * @param param Unused thread parameter.
 */
void FUN_0018e558(void *param);

/**
 * @brief Callback receiving demuxed MPEG video elementary stream data.
 *
 * @param mpeg Pointer to sceMpeg context.
 * @param data Pointer to demuxed stream callback data.
 * @param cmpeg Pointer to CMpeg instance.
 * @return 1 on success, 0 if buffer full.
 */
int FMpegAcceptVideo(sceMpeg *mpeg, sceMpegCbDataStr *data, CMpeg *cmpeg);

/**
 * @brief Callback receiving demuxed MPEG audio elementary stream data.
 *
 * @param mpeg Pointer to sceMpeg context.
 * @param data Pointer to demuxed stream callback data.
 * @param cmpeg Pointer to CMpeg instance.
 * @return Result of CMpegAudio::FAccept.
 */
int FMpegAcceptAudio(sceMpeg *mpeg, sceMpegCbDataStr *data, CMpeg *cmpeg);

/**
 * @brief Callback invoked when video decoder needs to supply bitstream to IPU.
 *
 * @param pscempeg Pointer to sceMpeg context.
 * @param pmcd Pointer to callback data.
 * @param pmpeg Pointer to CMpeg instance.
 * @return 1 on success.
 */
int FMpegDecodeVideo(sceMpeg *pscempeg, sceMpegCbData *pmcd, CMpeg *pmpeg);

/**
 * @brief Callback invoked when MPEG demuxer is idle.
 *
 * @param mpeg Pointer to sceMpeg context.
 * @param data Pointer to callback data.
 * @param cmpeg Pointer to CMpeg instance.
 * @return 1.
 */
int FMpegDecoderIdle(sceMpeg *mpeg, sceMpegCbData *data, CMpeg *cmpeg);

/**
 * @brief Callback invoked on MPEG decoder error.
 *
 * @param mpeg Pointer to sceMpeg context.
 * @param data Pointer to callback data.
 * @param cmpeg Pointer to CMpeg instance.
 * @return 1.
 */
int FMpegDecoderError(sceMpeg *mpeg, sceMpegCbData *data, CMpeg *cmpeg);

/**
 * @brief Generates DMA/GIF display packet sending decoded macroblocks to GS framebuffer.
 *
 * @param aqwMpegGifs Output packet buffer.
 * @param ambImage Decoded macroblock pixel data.
 * @param w Video frame width.
 * @param h Video frame height.
 */
void BuildMpegGifs(QW *aqwMpegGifs, sceIpuRGB32 *ambImage, int w, int h);

/**
 * @brief Constructs full-screen textured quad GIF packet to present decoded MPEG frame.
 *
 * @param dst Output buffer for DMA/GIF tags.
 * @param u Texture horizontal dimension in macroblocks.
 * @param v Texture vertical dimension in macroblocks.
 */
void FUN_0018ef78(void *dst, int u, int v);

/**
 * @brief Spawns the dedicated MPEG background display thread.
 */
void StartupMpeg();

extern CMpeg g_mpeg;

#endif // MPEG_H
