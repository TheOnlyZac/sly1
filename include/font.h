/**
 * @file font.h
 */
#ifndef FONT_H
#define FONT_H

#include "common.h"

struct SFR
{
    float rx, ry;
};

class CFont
{
    int m_dxCharUnscaled;
    int m_dxSpaceUnscaled;
    int m_dyUnscaled;
    int m_csfr;
    SFR m_asfr[4];
    int m_fGstest;
    undefined4 unk_1;
    ulong m_gstest;
    uint m_z;
    float m_rxScale;
    float m_ryScale;
};

extern CFont *g_pfont;

#endif // FONT_H
