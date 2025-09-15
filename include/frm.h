/**
 * @file frm.h
 *
 * @brief Frame manager.
 */
#ifndef FRM_H
#define FRM_H

#include "common.h"
#include <shd.h>

// Forward.
class VIFS;
struct GIFS;

/**
 * @brief Frame.
 * @todo Add the rest of the fields.
 */
struct FRM
{
    /* 0x00 */ int cqwGifs;
    /* 0x04 */ QW *aqwGifs;
    /* 0x08 */ int cqwVifs;
    /* 0x0c */ QW *aqwVifs;
    /* 0x10 */ SLI *asli;
    /* 0x14 */ int cframe;
    /* 0x18 */ int grffont;
    /* 0x1c */ int fBackgroundUploadRequired;
    STRUCT_PADDING(9);
    /* 0x44 */ GRFZON grfzon;
    // ...
};

void StartupFrame();

void OpenFrame();

void EnsureVu1Code(VIFS *pvifs, void *pvStart, void *pvEnd);

void FinalizeFrameVifs(VIFS *pvifs, int *pcqwVifs, QW **ppqwVifs);

void FinalizeFrameGifs(GIFS *pgifs, int *pcqwGifs, QW **ppqwGifs);

void CloseFrame();

void PrepareGsForFrameRender(FRM *pfrm);

void FrameRenderLoop(void *);

void RenderFrame(FRM *pfrm, int fRenderGifs);

void ClearPendingFrame(FRM *pfrm);

void FlushFrames(int fFreeze);

void BlendPrevFrame();

extern uchar g_abRenderLoopStack[0x20000];
extern int g_cframe;

#endif // FRM_H
