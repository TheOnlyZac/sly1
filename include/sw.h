/**
 * @file sw.h
 *
 * @brief Scene world?
 */
#ifndef SW_H
#define SW_H

#include "common.h"

// todo Implement struct.
struct SW
{
    undefined1 padding[0x1c53];
    DL dlDprize;
};

extern SW *g_psw;

void IncrementSwHandsOff(SW *psw);

#endif // SW_H
