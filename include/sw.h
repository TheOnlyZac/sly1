/**
 * @file sw.h
 *
 * @brief Scene world?
 */
#ifndef SW_H
#define SW_H

#include "common.h"
#include <lo.h>
#include <mq.h>

/**
 * @todo Implement struct.
 */
struct SW : public LO
{
    int cpsoAll;
    int cpsoRoot;
    DL dlRoot;
    DL dlChild;
    DL dlMRD;
    DL dlBusy;
    DL dlBusySo;
    DL dlMRDRealClock;
    DL adlHash[512];
    LO *aploCidHead[162];
    undefined1 padding2[0x148];
    DL dlDprize;

    // MISALIGNED:
    void (*pcbUpdate)(float fDelta);
};

extern SW *g_psw;

MQ *PmqAllocSw(SW *psw);

void IncrementSwHandsOff(SW *psw);

void FreeSwMqList(SW *psw, MQ *pmq);

void DeleteSw(SW *psw); // todo check order of functions

#endif // SW_H
