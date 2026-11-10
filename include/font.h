/**
 * @file font.h
 *
 * @brief Font system.
 */
#ifndef FONT_H
#define FONT_H

#include "common.h"
#include <gifs.h>
#include <dmas.h>
#include <sdk/ee/eestruct.h>

// Forward declaration.
struct GSB;
struct BMP;
struct CLUT;
class CTextBox;
class CTextEdge;

// The CFontBrx vtable is emitted from the data segment, not from font.c.
#pragma interface

/**
 * @brief Scaled font ratio.
 */
struct SFR
{
    float rx, ry;
};

struct GLYFF
{
    uint16_t wch;
    uint16_t x;
    uint16_t y;
    uint16_t dx;
};

class CFont
{
    friend class CRichText;

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

public:
    virtual CFont *PfontClone(float rx, float ry);
    void CopyTo(CFont *pfontDest);
    float DxFromPchz(char *pchz);
    float DyWrapPchz(char *pchz, float dx);
    int ClineWrapPchz(char *pchz, float dx);
    void DrawPchz(char *pchz, CTextBox *ptbx, CTextBox *ptbxClip, GIFS *pgifs);
    void PushScaling(float rx, float ry);
    void PopScaling();
    virtual int FValid(char ch);
    virtual float DxFromCh(char ch);
    virtual void SetupDraw(CTextBox *ptbxClip, GIFS *pgifs);
    virtual void SwitchTex0(GIFS *pgifs);
    virtual float DxDrawCh(char ch, float xChar, float yChar, uint rgba, GIFS *pgifs);
    virtual void CleanupDraw(CTextBox *ptbxClip, GIFS *pgifs);
    virtual void DrawChRotated(char ch, float xChar, float yChar, uint rgba, GIFS *pgifs); // guessed name
    virtual void EdgeRect(CTextEdge *pte, CTextBox *ptbx, GIFS *pgifs);
};

class CFontBrx : public CFont
{
private:
    int m_ifont; // guessed name
    BMP *m_pbmp;
    CLUT *m_pclut;
    STRUCT_PADDING(1);
    sceGsTex0 m_tex0;
    int m_cqwBmpGifs;
    QW *m_aqwBmpGifs;
    int m_cqwClutGifs;
    QW *m_aqwClutGifs;
    int m_cglyff;
    GLYFF *m_aglyff;
    uint32_t m_grffont;
    STRUCT_PADDING(1);

public:
    virtual CFont *PfontClone(float rx, float ry);
    void CopyTo(CFontBrx *pfontDest);
    int FValid(char ch);
    float DxFromCh(char ch);
    int FEnsureLoaded(GIFS *pgifs);
    void SetupDraw(CTextBox *ptbxClip, GIFS *pgifs);
    void SwitchTex0(GIFS *pgifs);
    float DxDrawCh(char ch, float xChar, float yChar, uint rgba, GIFS *pgifs);
    void DrawChRotated(char ch, float xChar, float yChar, uint rgba, GIFS *pgifs); // guessed name
    void DrawPart(float xLeft, float yTop, float xRight, float yBottom, float sLeft, float tTop, float sRight, float tBottom, uint rgba, GIFS *pgifs);
    void EdgeRect(CTextEdge *pte, CTextBox *ptbx, GIFS *pgifs);
    void LoadFromBrx(CBinaryInputStream *pbis);
    void PostLoad(GSB *pgsb);
    GLYFF *PglyffFromCh(char ch);
};

class CRichText
{
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

public:
    CRichText(char *achz, CFont *pfont);
    void Reset();
    void SetBaseColor(RGBA *rgba);
    char ChNext();
    int Cch();
    void Trim(int cch);
    float Dx();
    int ClineWrap(float dx);
    float DyWrap(float dx); // guessed name
    float DxMaxLine();
    void GetExtents(float *pdx, float *pdy, float dxMax);
    void Draw(CTextBox *ptbx, CTextBox *ptbxClip, GIFS *pgifs);
};

extern CFont *g_pfont;
extern int g_duGlyph; // guessed name
extern int g_dvGlyph; // guessed name
extern char g_achFont[5];
extern CFont *g_apfont[5];

void StartupFont();

void PostFontsLoad();

#endif // FONT_H
