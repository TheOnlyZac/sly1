/**
 * @file dma.h
 * 
 * @brief Direct Memory Access (DMA) module.
 */
#ifndef SCE_DMA_H
#define SCE_DMA_H

#include "common.h"

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

    struct sceDmaTag
    {
        ushort qwc;       /* transfer count */
        uchar mark;       /* mark */
        uchar id;         /* tag */
        sceDmaTag *next;  /* next tag */
        uint p[2];        /* padding */
    } __attribute__ ((aligned(16)));

    struct sceDmaChan
    {
        tD_CHCR chcr; // Channel control Dn_CHCR
        uint p0[3];
        volatile void *madr; // Transfer memory address Dn_MADR
        uint p1[3];
        volatile uint qwc;  // Transfer size Dn_QWC
        uint p2[3];
        volatile sceDmaTag *tadr; // Transfer tag address Dn_TADR
        uint p3[3];
        volatile void *as0; // Address stack 0 Dn_ASR0
        uint p4[3];
        volatile void *as1; // Address stack Dn_ASR1
        uint p5[3];
        uint p6[4];
        uint p7[4];
        void* sadr; // SPR address Dn_SADR
        uint p8[3];
    };

    void FlushCache(int);

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
