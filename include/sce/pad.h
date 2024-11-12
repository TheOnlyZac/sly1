/**
 * @file pad.h
 *
 * @brief Joypad/Controller Library
 */
#ifndef PAD_H
#define PAD_H

#include "common.h"

extern "C"
{
    int scePadInit(int mode);
    int scePadPortOpen(int port, int slot, void* data);
    int scePadGetState(int port, int slot);
    int scePadInfoAct(int port, int slot, int actno, int term);
    int scePadInfoMode(int port, int slow, int term, int offs);
    int scePadSetMainMode(int port, int slow, int offs, int lock);
    int scePadSetActAlign(int port, int slow, const uchar* data);
    int scePadInfoPressMode(int port, int slot);
    int scePadEnterPressMode(int port, int slot);
    int scePadExitPressMode(int port, int slot);
}

#endif // PAD_H
