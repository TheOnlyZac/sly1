/**
 * @file include/sdk/ee/libpad.h
 *
 * @brief Joypad (controller) library.
 */
#ifndef PAD_H
#define PAD_H

typedef unsigned char u_char;

extern "C"
{
    int scePadInit(int mode);
    int scePadPortOpen(int port, int slot, void* data);
    int scePadGetState(int port, int slot);
    int scePadInfoAct(int port, int slot, int actno, int term);
    int scePadInfoMode(int port, int slow, int term, int offs);
    int scePadSetMainMode(int port, int slow, int offs, int lock);
    int scePadSetActAlign(int port, int slow, const u_char* data);
    int scePadInfoPressMode(int port, int slot);
    int scePadEnterPressMode(int port, int slot);
    int scePadExitPressMode(int port, int slot);
}

#endif // PAD_H
