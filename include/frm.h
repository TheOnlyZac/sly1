/**
 * @file frm.h
 *
 * @brief Frame manager.
 */
#ifndef FRM_H
#define FRM_H

#include "common.h"

// ...

void FrameRenderLoop(void*);

extern u8 g_abRenderLoopStack[0x20000];

#endif // FRM_H
