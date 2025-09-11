/**
 * @file hnd.h
 */
#ifndef HND_H
#define HND_H

#include "common.h"
#include <target.h>
#include <bis.h>

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct HND : public TARGET
{
    // ...
};

void InitHnd(HND *phnd);

void LoadHndFromBrx(HND *phnd, CBinaryInputStream *pbis);

#endif // HND_H
