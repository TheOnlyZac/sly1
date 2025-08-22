/**
 * @file frm.h
 *
 * @brief Frame manager.
 */
#ifndef FRM_H
#define FRM_H

#include "common.h"

void StartupFrame();
void OpenFrame();

// ...

void CloseFrame();

// ...

void FrameRenderLoop(void*);

// ...

void FlushFrames(int i); // todo fix signature

extern uchar g_abRenderLoopStack[0x20000];
extern int g_cframe;

#endif // FRM_H
