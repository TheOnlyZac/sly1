/**
 * @file 989snd.h
 *
 * @brief 989snd sound driver.
 */
#ifndef SND989_H
#define SND989_H

#include "common.h"

extern "C"
{
    struct sceCdRMode
    {
        uchar trycount;
        uchar spindlctrl;
        uchar datapattern;
        uchar pad;
    };

    uint snd_SendIOPCommandAndWait(int command, int data_used, int *in_data);
    uint snd_SendIOPCommandNoWait(int command, int data_used, uchar *done, ulong u_data);
    int snd_StreamSafeCheckCdIdle(int fBlockEeIop);
    int snd_StreamSafeCdRead(uint lbn, uint sectors, void *buf, sceCdRMode *mode);
    int snd_StreamSafeCdSync(int mode);
    int snd_StreamSafeCdBreak();
    int snd_StreamSafeCdGetError();
}

#endif // SND989_H
