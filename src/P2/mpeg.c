/**
 * @file mpeg.c
 *
 * @brief MPEG video and audio playback subsystem for cutscenes.
 */

#include <mpeg.h>
#include <gifs.h>
#include <gs.h>
#include <sdk/ee/eekernel.h>
#include <sce/memset.h>
#include <clock.h>
#include <joy.h>
#include <wipe.h>
#include <cd.h>
#include <sound.h>
#include <cat.h>
#include <game.h>
#include <phasemem.h>
extern int SemaCreate(int initCount, int maxCount);
// Cutscene OID tables and metadata
extern char D_00248490[];   // Intro cutscene OID key
extern char D_002484B0[];   // Table of cutscene OID keys (16 entries, 32 bytes each)
extern void *D_002699C0[];  // Table of cutscene display name strings (16 entries)
extern char D_0024B580[];   // Fallback string for index -1 (empty string)
extern char D_0024B588[];   // Fallback string for invalid index
extern char *D_00269A08;    // Currently queued secondary cutscene OID key
extern void *D_0024B5B8;    // Static destructor vtable/function pointer
extern void *D_00269AEC;    // Global pointer initialized by static init
extern char D_00269B4C[];   // Intro cutscene played flag (1 = played)
extern char D_002C3B00[];   // Buffer for MPEG binary async stream
extern char D_002CBB40[];   // Audio stream intermediate buffer (0xC000 bytes)
struct SW;
extern SW *g_psw;
extern char D_0024B598[];   // Vtable pointer for CQueueOutputIpu
extern char D_002C2B00[];   // Stack buffer for MPEG background display thread (0x1000 bytes)
extern int D_00275964;      // Background display thread ID
void RestoreGsBuffers(void);
void SwapGsBuffers(void);

extern "C" int func_0020B0B0(sceMpeg *);
extern "C" void FUN_0018f0e8(CMpeg *mpeg, void *key);
extern "C" int func_0020ADA0(void);
extern "C" int func_0020AE40(sceMpeg *, void *, int);
extern "C" int func_0020A538(sceMpeg *, int, int, void *, void *);
extern "C" int func_0020B168(sceMpeg *, int, void *, void *);
extern "C" int func_0020B058(sceMpeg *, void *, int);
extern "C" int func_0020B0C0(sceMpeg *);
extern "C" int func_0020B048(sceMpeg *);
extern "C" int func_0020A518(sceMpeg *, void *, int);

// Hardware and decoder work buffers
extern char D_0045AAC0;     // Macroblock decoded RGB32 image buffer
extern char D_0042AAC0;     // Video bitstream input buffer (0x30000 bytes)
extern char D_002D7B40;     // Work buffer for sceMpeg decoder (0x152F68 bytes)
extern char D_005A2D40;     // Display packet GIF buffer 1
extern char D_00586AC0;     // Display packet GIF buffer 0

// Anti-tamper verification symbols
extern char D_00148D68;     // Length of executable text segment to checksum
extern uint D_005A2E60[256];// CRC32 table calculated at MPEG start
extern int g_vbact;

extern "C" void FlushCache(int);
extern "C" int func_001F6CA0(void *, int);
extern "C" int func_001F6C90(int);
extern "C" int snd_GetTransStatus(void);

extern "C" void snd_PauseAllSoundsInGroup(unsigned int);
struct SW;
enum REVERBK
{
    REVERBK_None = 0,
    REVERBK_StudioA = 1,
    REVERBK_StudioB = 2,
    REVERBK_StudioC = 3,
    REVERBK_Pipe = 4,
    REVERBK_Room = 5,
    REVERBK_Max = 6,
    REVERBK_Nil = -1
};
void PushSwReverb(SW *psw, REVERBK reverb, const int k);
extern "C" void snd_StopAllStreams(void);
extern "C" int snd_FlushSoundCommands(void);
extern "C" void snd_StreamSafeCheckCDIdle(int);
extern "C" void snd_StreamSafeCdSync(int);
extern "C" int snd_GetMasterVolume(int);
extern "C" void snd_SetMasterVolume(int, int);
extern "C" int snd_InitMovieSound(int, int, int, int, int);

extern "C" void snd_ResetMovieSound(void);
extern "C" void snd_StartMovieSound(int id1, int vol, int id2, int zero1, int zero2);

extern "C" void snd_CloseMovieSound(void);
void PopSwReverb(SW *psw);
extern "C" void snd_ContinueAllSoundsInGroup(unsigned int);


/**
 * @brief Static initialization helper for MPEG global state.
 */
extern "C" void mpeg__static_initialization_and_destruction_0(int a1, int a2);

/**
 * @brief Looks up the cutscene index (0-15) corresponding to an OID key descriptor.
 *
 * @param key Pointer to cutscene OID entry.
 * @return Cutscene index in [0, 15], or -1 if not found.
 */
extern "C" int FUN_0018e410(void *key)
{
    char *entry = D_002484B0;
    int index = 0;

    while (index < 0x10)
    {
        int match;

        if (entry == key)
            match = 1;

        else if (!entry)
            match = 0;

        else if (!key)
            match = 0;

        else
        {
            int e8  = *(int *)(entry + 8);
            int e18 = *(int *)(entry + 0x18);
            int k8  = *(int *)((char *)key + 8);
            int k18 = *(int *)((char *)key + 0x18);
            match = ((e8 ^ e18) ^ (k8 ^ k18)) == 0;
        }

        if (match)
            return index;

        entry += 0x20;
        index++;
    }
    return -1;
}

/**
 * @brief Retrieves the display name string for a cutscene by index.
 *
 * @param index Cutscene index.
 * @return Pointer to cutscene name string, or fallback string if index is out of bounds.
 */
extern "C" void *FUN_0018e480(int index)
{
    if ((unsigned)index < 0x10)
        return D_002699C0[index];

    if (index == -1)
        return &D_0024B580;

    return &D_0024B588;
}

/**
 * @brief Sets the next cutscene to play and marks it unlocked in the game state.
 *
 * @param index Cutscene index to unlock and queue.
 */
extern "C" void FUN_0018e4c0(int index)
{
    FUN_0018f0e8(&g_mpeg, D_002484B0 + (index << 5));
}

/**
 * @brief Unlocks and queues a primary and secondary cutscene pair.
 *
 * @param index1 Primary cutscene index to queue for playback.
 * @param index2 Secondary cutscene index to mark unlocked in game state.
 */
extern "C" void FUN_0018e4f0(int index1, int index2)
{
    FUN_0018e4c0(index1);

    D_00269A08 = D_002484B0 + (index2 << 5);

    int mask;
    if ((unsigned)index2 >= 0x10)
        mask = 0;
    else
        mask = 1 << index2;

    g_pgsCur->unlocked_cutscenes |= mask;
}

/**
 * @brief Background display thread procedure for double-buffered GIF rendering.
 *
 * @details Waits on semaphore field_130, then executes DMA transfers of GIF packets
 *          to present decoded MPEG frames to the GS framebuffer.
 *
 * @param param Unused thread parameter.
 */
extern "C" void FUN_0018e558(void *)
{
    while (true)
    {
        int sema = g_mpeg.field_130;
        g_mpeg.field_134 = 0;
        WaitSema(sema);

        g_mpeg.field_134 = 1;
        SendDmaSyncGsFinish(g_pdcGif, g_mpeg.m_aaqwGifs[0]);

        g_mpeg.field_134 = 2;
        RestoreGsBuffers();

        SendDmaSyncGsFinish(g_pdcGif, g_mpeg.m_aaqwGifs[1]);
        SwapGsBuffers();

        SendDmaSyncGsFinish(g_pdcGif, g_mpeg.m_aaqwGifs[1]);
        SwapGsBuffers();
    }
}

/**
 * @brief Initializes the MPEG playback subsystem and launches background render thread.
 */
void StartupMpeg()
{
    int sema = SemaCreate(0, 1);
    g_mpeg.field_130 = sema;
    g_mpeg.m_pbas = 0;

    ThreadParam param;
    memset(&param, 0, 0x30);
    param.entry = FUN_0018e558;
    param.stack = D_002C2B00;
    param.stackSize = 0x1000;
    param.gpReg = &_gpReg;
    param.initPriority = 2;

    int tid = CreateThread(&param);
    D_00275964 = tid;
    StartThread(tid, 0);
}

/**
 * @brief Initializes the IOP output queue with buffer capacity and destination address.
 *
 * @param a1 Queue capacity in bytes.
 * @param a2 Destination memory address on IOP.
 */
void CQueueOutputIop::Init(int a1, int a2)
{
    m_pbIop = a2;
    m_cb = a1;
    Reset();
}

/**
 * @brief Resets IOP output queue pointers and byte counters.
 */
void CQueueOutputIop::Reset()
{
    m_cbFree = m_cb;
    m_cbAlloc = 0;
    m_ibAlloc = 0;
    m_ibFree = 0;
    m_cbTotal = 0;
}

static inline int Min(int nA, int nB)
{
    return (nA < nB) ? nA : nB;
}

/**
 * @brief Clamps and transfers audio stream data to IOP memory in 1KB chunks.
 *
 * @param cb Number of bytes to write.
 * @param pv Source buffer containing audio stream data.
 * @return Total number of bytes sent to IOP.
 */
int CQueueOutputIop::CbWrite(int cb, void *pv)
{
    int cbSent = 0;
    int cbLeft = cb;

    if (cb <= 0 || cb > m_cbFree)
    {
        cbLeft = m_cbFree;
    }

    cbLeft &= -0x400;

    while (cbLeft)
    {
        int cbCopied = CbSend(Min(cbLeft, m_cb - m_ibFree), (uchar *)pv + cbSent);
        if (cbCopied == 0)
            break;

        cbSent += cbCopied;
        cbLeft -= cbCopied;
        m_ibFree += cbCopied;
        m_ibFree %= m_cb;
        m_cbAlloc += cbCopied;
        m_cbFree -= cbCopied;
        m_cbTotal += cbCopied;

        if (cb <= 0)
            break;
    }

    return cbSent;
}

/**
 * @brief Sends an audio buffer chunk to IOP sound memory via SIF DMA.
 *
 * @param size Number of bytes to transfer.
 * @param buf Pointer to data buffer.
 * @return Number of bytes transferred.
 */
int CQueueOutputIop::CbSend(int size, void *buf)
{
    struct {
        void *buf;
        void *addr;
        int size;
        int pad;
    } pkt;

    pkt.buf = buf;
    pkt.addr = (char *)m_pbIop + m_ibFree;
    pkt.size = size;
    pkt.pad = 0;

    FlushCache(0);
    int handle = func_001F6CA0(&pkt, 1);

    int result;
    do {
        result = func_001F6C90(handle);

    } while (result >= 0);

    return size;
}

/**
 * @brief Updates IOP audio stream buffer state and available free space.
 */
void CQueueOutputIop::Update()
{
    int cb = snd_GetTransStatus() & 0xFFFFFF;
    cb -= m_pbIop;
    cb -= m_ibFree;
    cb -= 0x400;
    cb += m_cb;

    m_cbFree = cb;
    m_cbFree = cb % m_cb;

    int delta = m_cb - m_cbFree;
    m_cbAlloc = delta;

    int ib = (m_ibFree - delta) + m_cb;
    m_ibAlloc = ib;
    m_ibAlloc = ib % m_cb;
}

/**
 * @brief Checks if IOP output queue has drained asynchronously.
 *
 * @return Always 0 (synchronous transfers).
 */
int CQueueOutputIop::FAsyncDrain()
{
    return 0;
}

/**
 * @brief Transmits compressed video macroblock bitstream to IPU via DMA.
 *
 * @param cb Number of bytes to send (max 4KB, 16-byte aligned).
 * @param pv Source bitstream buffer.
 * @return Bytes transferred.
 */
int CQueueOutputIpu::CbWrite(int cb, void *pv)
{
    cb = (unsigned int)cb & 0xFFFFFFF0;
    if (!(cb <= 0x1000))
        cb = 0x1000;

    int old = *(volatile int *)0x1000F590;
    *(volatile int *)0x1000F590 = 0x10000;

    *(volatile int *)0x1000B420 = (unsigned int)cb >> 4;
    unsigned int val = (unsigned int)pv & 0x0FFFFFFF;
    *(volatile int *)0x1000B410 = val;
    *(volatile int *)0x1000B400 = 0x101;
    *(volatile int *)0x1000F590 = old;

    return cb;
}

/**
 * @brief Checks if IPU output queue drain operation is asynchronous.
 *
 * @return Always 1 (asynchronous DMA to IPU).
 */
int CQueueOutputIpu::FAsyncDrain()
{
    return 1;
}

/**
 * @brief Initializes MPEG streaming audio, pausing game sounds and setting movie volume.
 */
void CMpegAudio::Init()
{
    snd_PauseAllSoundsInGroup(0xFFFFFFFF);
    PushSwReverb(g_psw, REVERBK_None, 0);
    snd_StopAllStreams();
    while (snd_FlushSoundCommands())
        ;
    snd_StreamSafeCheckCDIdle(1);
    snd_StreamSafeCdSync(0);
    m_nvolDialogRestore = snd_GetMasterVolume(2);
    m_nvolGlobalRestore = snd_GetMasterVolume(8);
    snd_SetMasterVolume(2, 0x400);
    snd_SetMasterVolume(8, 0x200);
    int pbIop = snd_InitMovieSound(0x6000, 0x400, 0, 2, 2);
    if (pbIop < 0) {
        m_state = 0;
    } else {
        m_state = 1;
        m_bqSsp.Init(0x28, &m_ssp);
        m_bq.Init(0xC000, D_002CBB40);
        m_qo.Init(0x6000, pbIop);
    }
}

/**
 * @brief Resets movie sound stream and internal byte queues.
 */
void CMpegAudio::Reset()
{
    if (!m_state)
        return;

    snd_ResetMovieSound();
    m_state = 1;

    m_bqSsp.Reset();
    m_bq.Reset();
    m_qo.Reset();
}

/**
 * @brief Closes movie sound and restores global audio volumes and reverb.
 */
void CMpegAudio::Close()
{
    m_state = 0;
    snd_CloseMovieSound();
    snd_SetMasterVolume(2, m_nvolDialogRestore);
    snd_SetMasterVolume(8, m_nvolGlobalRestore);
    PopSwReverb(g_psw);
    snd_ContinueAllSoundsInGroup(0xFFFFFFFF);
}

/**
 * @brief Ingests demuxed audio packets into preface and audio byte queues.
 *
 * @param cb Size of incoming audio packet.
 * @param pb Pointer to audio packet data.
 * @return 1 on success, 0 on failure or insufficient queue space.
 */
int CMpegAudio::FAccept(int cb, unsigned char *pb)
{
    if (m_state == 0)
        return 0;

    cb -= 4;
    pb += 4;

    if (m_state == 1)
    {
        int cbFilled = m_bqSsp.CbFill(cb, pb);
        cb -= cbFilled;
        pb += cbFilled;
        if (m_bqSsp.m_cbFree > 0)
            goto LSuccess;
        m_state = 2;
    }

    if (m_bq.m_cbFree < cb)
        return 0;

    m_bq.CbFill(cb, pb);

LSuccess:
    return 1;
}

/**
 * @brief Drives audio queue playback states and feeds IOP audio ring buffer.
 */
void CMpegAudio::Update()
{
    switch (m_state)
    {
    case 2:

        m_bq.CbDrain(m_qo.m_cbFree, &m_qo);
        if (m_qo.m_cbFree == 0)
        {
            snd_StartMovieSound(m_qo.m_pbIop, m_qo.m_cb, m_qo.m_pbIop, 0, 0);
            m_state = 3;
        }
        break;

    case 3:
        m_qo.Update();
        m_bq.CbDrain(m_qo.m_cbFree, &m_qo);
        break;
    }
}

/**
 * @brief Callback receiving demuxed MPEG video elementary stream data.
 *
 * @param mpeg Pointer to sceMpeg context.
 * @param data Pointer to demuxed stream callback data.
 * @param cmpeg Pointer to CMpeg instance.
 * @return 1 on success, 0 if buffer full.
 */
int FMpegAcceptVideo(sceMpeg *mpeg, sceMpegCbDataStr *data, CMpeg *cmpeg)
{
    int size = data->len;
    if (cmpeg->m_bqVideo.m_cbFree < (unsigned)size)
        return 0;

    cmpeg->m_bqVideo.CbFill(size, (uchar *)data->data);
    return 1;
}

/**
 * @brief Callback receiving demuxed MPEG audio elementary stream data.
 *
 * @param mpeg Pointer to sceMpeg context.
 * @param data Pointer to demuxed stream callback data.
 * @param cmpeg Pointer to CMpeg instance.
 * @return Result of CMpegAudio::FAccept.
 */
int FMpegAcceptAudio(sceMpeg *mpeg, sceMpegCbDataStr *data, CMpeg *cmpeg)
{
    return cmpeg->m_maud.FAccept(data->len, (uchar *)data->data);
}

/**
 * @brief Callback invoked when video decoder needs to supply bitstream to IPU.
 *
 * @param pscempeg Pointer to sceMpeg context.
 * @param pmcd Pointer to callback data.
 * @param pmpeg Pointer to CMpeg instance.
 * @return 1 on success.
 */
int FMpegDecodeVideo(sceMpeg *pscempeg, sceMpegCbData *pmcd, CMpeg *pmpeg)
{
    char ab[64];

    while (pmpeg->m_bqVideo.m_cbAlloc < 0x1000)
    {
        if (!pmpeg->CbDemuxed(1))
        {
            memset(ab, 0, sizeof(ab));
            pmpeg->m_bqVideo.CbFill(64 - (pmpeg->m_bqVideo.m_cbAlloc % 32), (unsigned char *)ab);
            break;
        }
    }

    CQueueOutputIpu *pqoipu = (CQueueOutputIpu *)ab;
    pqoipu->m_vtable = &D_0024B598;
    pmpeg->m_bqVideo.FreeDrain(0);
    pmpeg->m_bqVideo.CbDrain(0, pqoipu);
    return 1;
}

/**
 * @brief Callback invoked when MPEG demuxer is idle.
 *
 * @param mpeg Pointer to sceMpeg context.
 * @param data Pointer to callback data.
 * @param cmpeg Pointer to CMpeg instance.
 * @return 1.
 */
int FMpegDecoderIdle(sceMpeg *mpeg, sceMpegCbData *data, CMpeg *cmpeg)
{
    cmpeg->CbDemuxed(0);
    return 1;
}

/**
 * @brief Callback invoked on MPEG decoder error.
 *
 * @param mpeg Pointer to sceMpeg context.
 * @param data Pointer to callback data.
 * @param cmpeg Pointer to CMpeg instance.
 * @return 1.
 */
int FMpegDecoderError(sceMpeg *mpeg, sceMpegCbData *data, CMpeg *cmpeg)
{
    return 1;
}

/**
 * @brief Generates DMA/GIF display packet sending decoded macroblocks to GS framebuffer.
 *
 * @param aqwMpegGifs Output packet buffer.
 * @param ambImage Decoded macroblock pixel data.
 * @param dx Video frame width.
 * @param dy Video frame height.
 * @param igs GS context index.
 * @param x Frame X display coordinate.
 * @param y Frame Y display coordinate.
 */
void BuildMpegGifs(
    QW *aqwMpegGifs,
    sceIpuRGB32 *ambImage,
    int dx,
    int dy,
    int igs,
    int x,
    int y)
{
    int cmbx = dx / 16;
    int cmby = dy / 16;

    GIFS gifs;
    gifs.AllocStatic(0x1C28, aqwMpegGifs);
    gifs.AddDmaCnt();

    gifs.AddPrimPack(0, 1, 0xE);
    gifs.PackAD(0x50, ((long long)0xA1E0 << 36));
    gifs.PackAD(0x52, (long long)0x10 << 32 | 0x10);

    for (int imbx = 0; imbx < cmbx; imbx++)
    {
        for (int imby = 0; imby < cmby; imby++)
        {
            gifs.AddPrimPack(0, 1, 0xE);
            gifs.PackAD(0x51, (long long)imbx << 36 | ((long long)(imby << 4) << 48));
            gifs.PackAD(0x53, 0);
            gifs.AddImage(0x40);
            gifs.AddDmaRefs(0x40, (QW *)((uint)ambImage & 0x0FFFFFFF));
            ambImage++;
        }
    }

    gifs.AddPrimPack(0, 1, 0xE);
    gifs.PackAD(0x3F, 0);
    gifs.PackAD(0x61, 0);
    gifs.AddPrimEnd();
    gifs.AddDmaEnd();
    gifs.Detach(0, 0);
}

/**
 * @brief Constructs full-screen textured quad GIF packet to present decoded MPEG frame.
 *
 * @param dst Output buffer for DMA/GIF tags.
 * @param u Texture horizontal dimension in macroblocks.
 * @param v Texture vertical dimension in macroblocks.
 */
extern "C" void FUN_0018ef78(void *dst, int u, int v)
{
    GIFS gifs;

    gifs.AllocStatic(0x12, (QW *)dst);
    gifs.AddDmaCnt();

    gifs.AddPrimPack(6, 1, 0xE);

    int n = 0xA;
    long long val = ((long long)n << 16) | 0xA802;
    val = (val << 16) | 0x9E00;
    gifs.PackAD(6, val);

    gifs.PackAD(0x14, 0x61);
    gifs.PackAD(8, 5);
    gifs.PackAD(0x42, 0x44);
    gifs.PackAD(0x47, 0x31001);

    gifs.AddPrimPack(0x116, 5, 0xE4343);
    gifs.PackUV(8, 8);
    gifs.PackXYZF(0x6C00, 0x7900, 0, 0);

    gifs.PackUV((u << 4) | 8, (v << 4) | 8);
    gifs.PackXYZF(0x9400, 0x8700, 0, 0);

    gifs.PackAD(0x61, 0);
    gifs.AddPrimEnd();
    gifs.AddDmaEnd();
    gifs.Detach(0, 0);
}

/**
 * @brief Queues the cutscene specified by key into the MPEG player and marks it unlocked.
 *
 * @param mpeg Pointer to CMpeg instance.
 * @param key Pointer to cutscene OID key descriptor.
 */
extern "C" void FUN_0018f0e8(CMpeg *mpeg, void *key)
{
    if (mpeg->oid_2)
        return;

    mpeg->oid_2 = (OID)(uint)key;

    int index = FUN_0018e410(key);
    int mask;
    if ((unsigned)index >= 0x10)
        mask = 0;
    else
        mask = 1 << index;

    g_pgsCur->unlocked_cutscenes |= mask;
}

/**
 * @brief Plays queued cutscene OIDs sequentially.
 */
void CMpeg::ExecuteOids()
{
    void *oid2 = m_poidNext;
    void *oid1 = (void *)oid_2;
    oid_2 = (OID)0;
    m_poidNext = 0;
    Execute((OID *)oid1);
    if (oid2)
        Execute((OID *)oid2);
}

/**
 * @brief Compares two cutscene OID key descriptors for identity.
 *
 * @param entry Table entry pointer.
 * @param key Candidate key pointer.
 * @return 1 if keys match, 0 otherwise.
 */
static inline int FEqualKey(void *entry, void *key)
{
    if (entry == key)
        return 1;
    if (entry == NULL || key == NULL)
        return 0;
    return (((*(int *)((char *)entry + 8) ^ *(int *)((char *)entry + 0x18)) ^
             (*(int *)((char *)key + 8) ^ *(int *)((char *)key + 0x18)))) == 0;
}

/**
 * @brief Core cutscene playback loop and controller.
 *
 * @param poid Pointer to cutscene OID key descriptor identifying file sector and length.
 */
void CMpeg::Execute(OID *poid)
{
    SetPhase(PHASE_Mpeg);
    oid_1 = (OID)FUN_0018e410(poid);
    CBinaryAsyncStream bas(D_002C3B00);
    CFileLocation fl;
    bool fOk;
    if (poid == NULL)
    {
        fOk = false;
    }
    else
    {
        fl.m_fcl.cb = *(uint *)((char *)poid + 0x4) ^ *(uint *)((char *)poid + 0x1C);
        fl.m_fcl.isector = *(uint *)((char *)poid + 0x0) ^ *(uint *)((char *)poid + 0x14);
        fOk = (bool)fl.m_fcl.cb;
    }

    if (fOk && bas.FOpenFile(&fl))
    {
        Start(&bas);
        while (func_0020B0B0(&m_scempeg) == 0)
        {
            MarkClockTickRealOnly(&g_clock);
            UpdateJoy(&g_joy);

            int fSkip = 0;
            if (FEqualKey(poid, D_00248490))
                fSkip = *(uint *)D_00269B4C > 0;

            int index = oid_1;
            int mask;
            if ((uint)index >= 16)
                mask = 0;
            else
                mask = 1 << index;

            if (g_pgsCur->fgs & mask)
                fSkip = 1;

            if (fSkip)
            {
                if (FCatchWipeButtonTrans(&g_wipe, &g_joy, WIPES_Black))
                    break;
                // Skip button mask: PAD_L2 | PAD_R2 | PAD_L1 | PAD_R1 | PAD_TRIANGLE | PAD_SELECT | PAD_START
                if (g_joy.grfbtnPressed & 0x91F)
                {
                    SetJoyBtnHandled(&g_joy, 0x91F);
                    break;
                }
            }

            UpdateCd();
            if (g_cds != CDS_Ready)
                break;

            Update();
        }

        if (FEqualKey(poid, D_00248490))
            *(int *)D_00269B4C = 1;

        Finish();
        bas.Close();
    }
    else
    {
        StartSound(SFXID_Thud7, NULL, NULL, NULL, 3000.0f, 300.0f, 1.0f, 0.0f, 0.0f, NULL, NULL);
    }

    ClearPhase(PHASE_Mpeg);
}

/**
 * @brief Converts a pointer to an uncached memory address.
 *
 * @param pv Pointer to convert.
 * @return Pointer in uncached KSEG1 address space.
 */
static inline void *PvUncachedFromPv(void *pv)
{
    return (void *)((uint)pv | 0x20000000);
}

/**
 * @brief Initializes MPEG decoder hardware, stream queues, and anti-tamper CRC table.
 *
 * @param pbas Source binary async stream.
 */
void CMpeg::Start(CBinaryAsyncStream *pbas)
{
    m_pbas = pbas;
    m_pbWork = &D_002D7B40;
    m_ambDecoded = (sceIpuRGB32 *)&D_0045AAC0;
    m_bqVideo.Init(0x30000, PvUncachedFromPv(&D_0042AAC0));
    m_maud.Init();

    func_0020ADA0();
    func_0020AE40(&m_scempeg, m_pbWork, 0x152F68);

    func_0020A538(&m_scempeg, 0, 0, (void *)FMpegAcceptVideo, this);
    func_0020A538(&m_scempeg, 2, 0, (void *)FMpegAcceptAudio, this);

    func_0020B168(&m_scempeg, 1, (void *)FMpegDecodeVideo, this);
    func_0020B168(&m_scempeg, 4, (void *)FMpegDecoderIdle, this);
    func_0020B168(&m_scempeg, 0, (void *)FMpegDecoderError, this);

    while (CbDemuxed(1) != 0)
    {
    }

    m_aaqwGifs[0] = (QW *)&D_00586AC0;
    m_aaqwGifs[1] = (QW *)&D_005A2D40;

    g_vbact = 0;
    g_mpeg.field_13C = (uchar *)0x100010;
    g_mpeg.field_140 = (int)&D_00148D68;
    g_mpeg.field_138 = 0xFFFFFFFF;

    // Generate IEEE 802.3 CRC32 lookup table (polynomial 0xEDB88320)
    void *pTable = D_005A2E60;
    for (int i = 0; i < 256; i++)
    {
        uint crc = i;
        for (int j = 7; j >= 0; j--)
        {
            if (crc & 1)
                crc = (crc >> 1) ^ 0xEDB88320;
            else
                crc >>= 1;
        }
        int off = i << 2;
        *(uint *)((int)pTable + off) = crc;
    }
}

/**
 * @brief Anti-tamper verification failure flag (1 = checksum mismatch).
 */
extern int D_00269B48;

/**
 * @brief Progresses background anti-tamper CRC32 calculation over the game executable text segment.
 *
 * @details Checksums 4 bytes per call starting from 0x100010. If the final CRC fails to match
 *          the expected value, flag D_00269B48 is set to trigger anti-tamper countermeasures.
 */
void CMpeg::FUN_0018f610()
{
    if (field_140 <= 0)
        return;

    uchar *pb = field_13C;

    field_138 = D_005A2E60[(field_138 ^ pb[0]) & 0xFF] ^ (field_138 >> 8);
    field_138 = D_005A2E60[(field_138 ^ pb[1]) & 0xFF] ^ (field_138 >> 8);
    field_140 -= 4;
    field_138 = D_005A2E60[(field_138 ^ pb[2]) & 0xFF] ^ (field_138 >> 8);
    field_138 = D_005A2E60[(field_138 ^ pb[3]) & 0xFF] ^ (field_138 >> 8);
    field_13C += 4;

    if (field_140 == 0 && field_138 != 0)
    {
        D_00269B48 = 1;
    }
}

/**
 * @brief Advances MPEG playback: demuxes stream, decodes video frame, and syncs display thread.
 */
void CMpeg::Update()
{
    if (field_134 == 1)
    {
        do {
            CbDemuxed(0);
        } while (field_134 == 1);
    }

    if (func_0020B058(&m_scempeg, m_ambDecoded, 1200) < 0)
        return;

    if (m_scempeg.frameCount == 0)
    {
        typedef void (*pfn_build_t)(QW *, sceIpuRGB32 *, int, int);
        ((pfn_build_t)BuildMpegGifs)(m_aaqwGifs[0], m_ambDecoded,
                              m_scempeg.width, m_scempeg.height);
        FUN_0018ef78(m_aaqwGifs[1], m_scempeg.width, m_scempeg.height);
        FlushCache(0);
    }

    if (field_134 != 0)
    {
        do {
            CbDemuxed(0);
            FUN_0018f610();
        } while (field_134 != 0);
    }

    SignalSema(field_130);
    m_maud.Update();
}


void UploadPermShaders();

/**
 * @brief Shuts down MPEG decoding, waits for render thread, restores GS shaders, and marks cutscene played.
 */
void CMpeg::Finish()
{
    m_pbas = 0;
    m_maud.Reset();
    m_maud.Close();
    func_0020B0C0(&m_scempeg);
    func_0020B048(&m_scempeg);

    while (field_134 != 0)
        ;

    g_vbact = 3;
    UploadPermShaders();

    int mask;
    if ((uint)oid_1 >= 0x10)
        mask = 0;
    else
        mask = 1 << oid_1;

    g_pgsCur->fgs |= mask;
}

/**
 * @brief Checks if a binary async stream internal buffer is exhausted.
 *
 * @note Inline needed for matching: prevents gcc from duplicating the loop exit test.
 *
 * @param pbas Pointer to binary async stream.
 * @return 1 if buffer is empty, 0 otherwise.
 */
static inline int FBasEmpty(CBinaryAsyncStream *pbas)
{
    return pbas->m_cb == pbas->m_ibCur;
}

/**
 * @brief Feeds the sceMpeg demuxer with new data from the binary async stream.
 *
 * @param fBlock Whether to wait synchronously if stream buffer needs spooling.
 * @return Number of bytes accepted by the demuxer.
 */
int CMpeg::CbDemuxed(int fBlock)
{
    while (FBasEmpty(m_pbas))
    {
        m_pbas->Spool();
        if (FBasEmpty(m_pbas) && !fBlock)
            return 0;
    }

    FlushCache(0);
    int cbAvail = m_pbas->m_cb - m_pbas->m_ibCur;
    byte *pb = m_pbas->m_pb + m_pbas->m_ibCur;
    int cb = func_0020A518(&m_scempeg, pb, cbAvail);
    m_pbas->Skip(cb);
    return cb;
}

JUNK_WORD(0x0002102B);

/**
 * @brief Static initialization helper for MPEG global state.
 */
extern "C" void mpeg__static_initialization_and_destruction_0(int a1, int a2)
{
    if (a2 == 0xFFFF && a1)
        D_00269AEC = &D_0024B5B8;
}

/**
 * @brief Global constructor calling static initialization for g_mpeg.
 */
extern "C" void _GLOBAL_$I$g_mpeg()
{
    mpeg__static_initialization_and_destruction_0(1, 0xFFFF);
}
