/**
 * @file include/sdk/ee/libdma.h
 *
 * @brief Direct Memory Access library.
 */
#ifndef SCE_DMA_H
#define SCE_DMA_H

typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;

extern "C"
{
    struct tD_CHCR
    {
        unsigned DIR : 1;   /* Direction */
        unsigned pad0: 1;
        unsigned MOD : 2;   /* Mode */
        unsigned ASP : 2;   /* Address stack pointer */
        unsigned TTE : 1;   /* Tag trasfer enable */
        unsigned TIE : 1;   /* Tag interrupt enable */
        unsigned STR : 1;   /* start */
        unsigned pad1: 7;
        unsigned TAG :16;   /* DMAtag */
    };

    struct _sceDmaTag
    {
        u_short qwc;       /* transfer count */
        u_char mark;       /* mark */
        u_char id;         /* tag */
        _sceDmaTag *next;  /* next tag */
        u_int p[2];        /* padding */
    } __attribute__ ((aligned(16)));

    struct sceDmaChan
    {
        tD_CHCR chcr; // Channel control
        u_int p0[3];

        volatile void *madr; // Transfer memory address
        u_int p1[3];

        volatile u_int qwc;  // Transfer count
        u_int p2[3];

        volatile _sceDmaTag *tadr; // Transfer tag address
        u_int p3[3];

        volatile void *as0; // Address stack 0
        u_int p4[3];

        volatile void *as1; // Address stack Dn_ASR1
        u_int p5[3];

        u_int p6[4]; // pad
        u_int p7[4]; // pad

        void* sadr; // SPR address
        u_int p8[3];
    };

    /**
     * @brief Reset the DMA controller
     *
     * @param mode 0 = disable, 1 = enable
     * @return Previous mode before reset
     */
    int sceDmaReset(int mode);

    /**
     * @brief Start DMA transfer from memory to a device using Source Chain Mode.
     *
     * @param chan DMA channel for performing the transfer
     * @param tag Starting address of the transfer list
     */
    void sceDmaSend(sceDmaChan *chan, void *tag);

    /**
     * @brief Get a DMA channel structure by ID
     *
     * @param id Channel number
     * @return sceDmaChan*
     */
    sceDmaChan *sceDmaGetChan(int id);
}

#endif // SCE_DMA_H
