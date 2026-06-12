#include <mpeg.h>

INCLUDE_ASM("asm/nonmatchings/P2/mpeg", FUN_0018e410);

INCLUDE_ASM("asm/nonmatchings/P2/mpeg", FUN_0018e480);

INCLUDE_ASM("asm/nonmatchings/P2/mpeg", FUN_0018e4c0);

INCLUDE_ASM("asm/nonmatchings/P2/mpeg", FUN_0018e4f0);

INCLUDE_ASM("asm/nonmatchings/P2/mpeg", FUN_0018e558);

INCLUDE_ASM("asm/nonmatchings/P2/mpeg", StartupMpeg__Fv);

#ifndef CQUEUEOUTPUTIOP_DEFINED
#define CQUEUEOUTPUTIOP_DEFINED
class CQueueOutputIop
{
public:
    int unk_0x0;
    int unk_0x4;
    int unk_0x8;
    int unk_0xc;
    int unk_0x10;
    int unk_0x14;
    int unk_0x18;
    int unk_0x1c;

    void Init(int nParam1, int nParam2);
    void Reset();
};
#endif // CQUEUEOUTPUTIOP_DEFINED

void CQueueOutputIop::Init(int nParam1, int nParam2)
{
    unk_0x4 = nParam2;
    unk_0x8 = nParam1;
    Reset();
}

#ifndef CQUEUEOUTPUTIOP_DEFINED
#define CQUEUEOUTPUTIOP_DEFINED
class CQueueOutputIop
{
public:
    int unk_0x0;
    int unk_0x4;
    int unk_0x8;
    int unk_0xc;
    int unk_0x10;
    int unk_0x14;
    int unk_0x18;
    int unk_0x1c;

    void Init(int nParam1, int nParam2);
    void Reset();
};
#endif // CQUEUEOUTPUTIOP_DEFINED

void CQueueOutputIop::Reset()
{
    unk_0x14 = unk_0x8;
    unk_0x18 = 0;
    unk_0x10 = 0;
    unk_0xc = 0;
    unk_0x1c = 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/mpeg", CbWrite__15CQueueOutputIopiPv);

INCLUDE_ASM("asm/nonmatchings/P2/mpeg", CbSend__15CQueueOutputIopiPv);

INCLUDE_ASM("asm/nonmatchings/P2/mpeg", Update__15CQueueOutputIop);

extern "C" int FAsyncDrain__15CQueueOutputIop()
{
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/mpeg", CbWrite__15CQueueOutputIpuiPv);

extern "C" int FAsyncDrain__15CQueueOutputIpu()
{
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/P2/mpeg", Init__10CMpegAudio);

INCLUDE_ASM("asm/nonmatchings/P2/mpeg", Reset__10CMpegAudio);

INCLUDE_ASM("asm/nonmatchings/P2/mpeg", Close__10CMpegAudio);

INCLUDE_ASM("asm/nonmatchings/P2/mpeg", FAccept__10CMpegAudioiPUc);

INCLUDE_ASM("asm/nonmatchings/P2/mpeg", Update__10CMpegAudio);

INCLUDE_ASM("asm/nonmatchings/P2/mpeg", FMpegAcceptVideo__FP7sceMpegP16sceMpegCbDataStrP5CMpeg);

struct sceMpeg;
struct sceMpegCbDataStr;
extern "C" int FAccept__10CMpegAudioiPUc(void *pmpega, int cb, uchar *pb);

int FMpegAcceptAudio(sceMpeg *pmp, sceMpegCbDataStr *pcbdata, CMpeg *pmpeg)
{
    return FAccept__10CMpegAudioiPUc((uint8_t *)pmpeg + 0x80, STRUCT_OFFSET(pcbdata, 0xC, int), STRUCT_OFFSET(pcbdata, 0x8, uchar *));
}

INCLUDE_ASM("asm/nonmatchings/P2/mpeg", FMpegDecodeVideo__FP7sceMpegP13sceMpegCbDataP5CMpeg);

struct sceMpeg;
struct sceMpegCbData;
extern "C" void CbDemuxed__5CMpegi(CMpeg *pmpeg, int nParam);

int FMpegDecoderIdle(sceMpeg *pmp, sceMpegCbData *pcbdata, CMpeg *pmpeg)
{
    CbDemuxed__5CMpegi(pmpeg, 0);
    return 1;
}

struct sceMpeg;
struct sceMpegCbData;

int FMpegDecoderError(sceMpeg *pmp, sceMpegCbData *pcbdata, CMpeg *pmpeg)
{
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/P2/mpeg", BuildMpegGifs__FP2QWP11sceIpuRGB32iiiii);

INCLUDE_ASM("asm/nonmatchings/P2/mpeg", FUN_0018ef78);

INCLUDE_ASM("asm/nonmatchings/P2/mpeg", FUN_0018f0e8);

INCLUDE_ASM("asm/nonmatchings/P2/mpeg", ExecuteOids__5CMpeg);

INCLUDE_ASM("asm/nonmatchings/P2/mpeg", Execute__5CMpeg);

INCLUDE_ASM("asm/nonmatchings/P2/mpeg", Start__5CMpegP18CBinaryAsyncStream);

INCLUDE_ASM("asm/nonmatchings/P2/mpeg", FUN_0018f610__5CMpeg);

INCLUDE_ASM("asm/nonmatchings/P2/mpeg", Update__5CMpeg);

INCLUDE_ASM("asm/nonmatchings/P2/mpeg", Finish__5CMpeg);

INCLUDE_ASM("asm/nonmatchings/P2/mpeg", CbDemuxed__5CMpegi);

JUNK_WORD(0x0002102B);

INCLUDE_ASM("asm/nonmatchings/P2/mpeg", mpeg__static_initialization_and_destruction_0);

INCLUDE_ASM("asm/nonmatchings/P2/mpeg", _GLOBAL_$I$g_mpeg);
