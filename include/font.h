/**
 * @file font.h
 *
 * @brief Font system.
 */
#ifndef FONT_H
#define FONT_H

#include "common.h"

/**
 * @brief Scaled font ratio.
 */
struct SFR
{
    float rx, ry;
};

class CFont
{
  public:
    void CopyTo(CFont *pfontDest);

  protected:
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

class CFontBrx : public CFont
{
  public:
    void *PglyffFromCh(char ch);
    bool FValid(char ch);

  private:
    undefined1 m_padding[0x33];
};

extern CFont *g_pfont;

class CRichText
{
  public:
    CRichText(char *achz, CFont *pfont);
    int Cch();
    void Reset();
    void SetBaseColor(RGBA *rgba);

  private:
    char *m_achz;
    char *m_pchCur;
    CFont *m_pfontCur;
    CFont *m_pfontBase;
    CFontBrx m_fontOther;
    undefined4 m_unknown; // todo: figure out what this is
    RGBA m_rgbaCur;
    RGBA m_rgbaSet;
    RGBA m_rgbaBase;
    RGBA m_rgbaOther;
};

void StartupFont();

#endif // FONT_H
