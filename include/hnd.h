/**
 * @file hnd.h
 */
#ifndef HND_H
#define HND_H

#include "common.h"
#include <target.h>
#include <bis.h>

/**
 * @class HANDLE
 * @brief Unknown.
 */
struct HND : public TARGET
{
    /* 0xa0 */ uint hndk;
    /* 0xa4 */ float svzJumpBoost;
    /* 0xa8 */ SFXID sfxidRelease;
    /* 0xac */ SFXID sfxidGrab;
    /* 0xb0 */ STRUCT_PADDING(1);
    /* 0xb4 */ float unk1;
};

void InitHnd(HND *phnd);

void LoadHndFromBrx(HND *phnd, CBinaryInputStream *pbis);

#endif // HND_H
