/**
 * @file include/sdk/ee/libmpeg.h
 *
 * @brief MPEG video and audio decoding library.
 */
#ifndef SCE_LIBMPEG_H
#define SCE_LIBMPEG_H

#include <sdk/ee/libipu.h>

extern "C"
{
    enum sceMpegStrType
    {
        sceMpegStrM2V = 0,
        sceMpegStrIPU = 1,
        sceMpegStrPCM = 2,
        sceMpegStrADPCM = 3,
        sceMpegStrDATA = 4
    };

    enum sceMpegCbType
    {
        sceMpegCbError = 0,
        sceMpegCbNodata = 1,
        sceMpegCbStopDMA = 2,
        sceMpegCbRestartDMA = 3,
        sceMpegCbBackground = 4,
        sceMpegCbTimeStamp = 5,
        sceMpegCbStr = 6
    };

    /**
     * @brief MPEG callback data structure for demuxed elementary streams (video/audio).
     */
    struct sceMpegCbDataStr
    {
        sceMpegCbType type;
        void *header;
        void *data;
        int len;
        long long pts;
        long long dts;
    };

    /**
     * @brief PS2 sceMpeg library decoder state structure.
     */
    struct sceMpeg
    {
        int width;
        int height;
        int frameCount;
        int pad_0C;
        int pts;
        int dts;
        int flags;
        int pad_1C[11];
    };

    struct sceMpegCbData
    {
        int type;
        int pad[7];
    };

    typedef int (*sceMpegCallback)(sceMpeg *mp, sceMpegCbData *cbData, void *data);

    int sceMpegDemuxPss(sceMpeg *mpeg, void *data, int size);
    int sceMpegAddStrCallback(sceMpeg *mpeg, int strType, int ch, void *cb, void *data);
    int sceMpegAddCallback(sceMpeg *mpeg, int cbType, void *cb, void *data);
    int sceMpegGetPicture(sceMpeg *mpeg, sceIpuRGB32 *rgb, int count);
    int sceMpegReset(sceMpeg *mpeg);
    int sceMpegIsEnd(sceMpeg *mpeg);
    int sceMpegInit();
    int sceMpegCreate(sceMpeg *mpeg, void *work, int workSize);
    int sceMpegDelete(sceMpeg *mpeg);
}

#endif // SCE_LIBMPEG_H
