/**
 * @file include/sdk/libcdvd.h
 *
 * @brief DVD handler.
 */
#ifndef EEDVD_H
#define EEDVD_H

#include "common.h"

extern "C"
{
    struct sceCdRMode {
        uchar trycount;
        uchar spindlctrl;
        uchar datapattern;
        uchar pad;
    };


    int sceCdBreak(void);
    int sceCdGetError(void);
    int sceCdRead(u_int lbn, u_int sectors, void *buf, sceCdRMode *mode);
    int sceCdSync(int mode);
};

#endif // EEDVD_H
