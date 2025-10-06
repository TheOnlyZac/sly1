/**
 * @file include/sdk/libcdvd.h
 *
 * @brief DVD handler.
 */
#ifndef EEDVD_H
#define EEDVD_H

typedef unsigned char u_char;
typedef unsigned int u_int;

extern "C"
{
    struct sceCdRMode {
        u_char trycount;
        u_char spindlctrl;
        u_char datapattern;
        u_char pad;
    };

	enum SCECdvdMediaType {
        SCECdGDTFUNCFAIL = -1,
        SCECdNODISC      = 0x00,
        SCECdDETCT,
        SCECdDETCTCD,
        SCECdDETCTDVDS,
        SCECdDETCTDVDD,
        SCECdUNKNOWN,

        SCECdPSCD = 0x10,
        SCECdPSCDDA,
        SCECdPS2CD,
        SCECdPS2CDDA,
        SCECdPS2DVD,

        SCECdDVDVR = 0xFC,
        SCECdCDDA = 0xFD,
        SCECdDVDV,
        SCECdIllegalMedia
    };

    int sceCdSync(int mode);
    int sceCdInit(int mode);
    int sceCdDiskReady(int mode);
    int sceCdMmode(int mode);
    int sceCdRead(u_int lbn, u_int sectors, void *buf, sceCdRMode *mode);
    int sceCdGetDiskType(void);
    int sceCdGetError(void);
    int sceCdBreak(void);
};

#endif // EEDVD_H
