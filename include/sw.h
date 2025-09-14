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
 * @class WORLD
 * @brief Not fully understood, but everything in the game world is owned by
 * an instance of this struct.
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
    STRUCT_PADDING(82);
    DL dlDprize;

    // MISALIGNED:
    void (*pcbUpdate)(float fDelta);
};

extern SW *g_psw;

MQ *PmqAllocSw(SW *psw);

void IncrementSwHandsOff(SW *psw);

void DecrementSwHandsOff(SW *psw);

void FreeSwMqList(SW *psw, MQ *pmq);

void PostSwCallback(SW *psw, PFNMQ pfnmq, void *pvContext, MSGID msgid, void *pvCallbackData);

void DeleteSw(SW *psw); // todo check order of functions

#endif // SW_H
