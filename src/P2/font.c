#include <font.h>
#include <memory.h>
#include <gs.h>
#include <binoc.h>
#include <frm.h>
#include <shd.h>
#include <bis.h>

extern int g_cfontBrx;
extern CFontBrx *g_afontBrx;
extern BMP *g_abmp;
extern CLUT *g_aclut;

// Header read by CFontBrx::LoadFromBrx (guessed name).
struct FONTB
{
    ushort ibmp;
    ushort iclut;
    uchar dxChar;
    uchar dxSpace;
    uchar dy;
    uchar ifont;
    float rScale;
    ushort cglyff;
    ushort pad;
};

void StartupFont()
{
    g_pfont = NULL;
}

/**
 * @todo 85% matched (8 differing lines of 16), guessed name FFontLoaded.
 */
INCLUDE_ASM("asm/nonmatchings/P2/font", FUN_0015c188);
#ifdef SKIP_ASM
int FFontLoaded(int ifont)
{
    if (ifont == -1)
        return 0;
    if (g_apfont[ifont] != NULL)
        return 1;
    return 0;
}
#endif // SKIP_ASM

CFont *PfontFromIfont(int ifont) // guessed name
{
    if (ifont == -1)
        return NULL;
    CFont *pfont = g_apfont[ifont];
    if (pfont != NULL)
        return pfont;
    return g_pfont;
}

CFont *PfontFromCh(char ch) // guessed name
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if (ch == g_achFont[i])
            break;
    }
    if (i < 5)
        return g_apfont[i];
    return NULL;
}

void CFont::CopyTo(CFont *pfontDest)
{
    pfontDest->m_dxCharUnscaled = this->m_dxCharUnscaled;
    pfontDest->m_dxSpaceUnscaled = this->m_dxSpaceUnscaled;
    pfontDest->m_dyUnscaled = this->m_dyUnscaled;
    pfontDest->m_rxScale = this->m_rxScale;
    pfontDest->m_ryScale = this->m_ryScale;
    pfontDest->m_csfr = this->m_csfr;
    CopyAb(&pfontDest->m_asfr, &this->m_asfr, this->m_csfr * 8);
    pfontDest->m_fGstest = this->m_fGstest;
    pfontDest->m_gstest = this->m_gstest;
    pfontDest->m_z = this->m_z;
}

void CFont::SetupDraw(CTextBox *ptbxClip, GIFS *pgifs)
{
    if (ptbxClip)
    {
        float x = ptbxClip->m_x;
        float y = ptbxClip->m_y;
        float x1 = x + ptbxClip->m_dx;
        float y1 = y + ptbxClip->m_dy;
        int xMax = (int)x1 - 1;
        int yMax = (int)(y1 * 0.45454547f) - 1;
        int yMin = (int)(y * 0.45454547f);
        int xMin = (int)x;
        pgifs->AddPrimPack(0, 1, 0xE);
        pgifs->PackAD(0x40, (long)xMin | ((long)xMax << 16) | ((long)yMin << 32) | ((long)yMax << 48));
    }
}

void CFont::CleanupDraw(CTextBox *ptbxClip, GIFS *pgifs)
{
    if (ptbxClip)
    {
        pgifs->AddPrimPack(0, 1, 0xE);
        pgifs->PackAD(0x40, 0xDF0000027F0000L);
    }
}

float CFont::DxFromPchz(char *pchz)
{
    if (pchz == 0)
        return 0.0f;
    char *pch = pchz;
    float dx = 0.0f;
    while (*pch)
    {
        dx += DxFromCh(*pch++);
    }
    return dx;
}

float CFont::DyWrapPchz(char *pchz, float dx)
{
    float dy = (float)m_dyUnscaled * m_ryScale;
    return dy * (float)ClineWrapPchz(pchz, dx);
}

int CFont::ClineWrapPchz(char *pchz, float dx)
{
    int cline = 1;
    float dxCur = 0.0f;
    char *pch = pchz;
    while (*pch)
    {
        char ch = *pch;
        if (ch == '\n')
        {
            dxCur = 0.0f;
            cline++;
        }
        else
        {
            dxCur += DxFromCh(ch);
        }
        if (dx != 0.0f && dx < dxCur)
        {
            char *pchT = pch;
            while (pchT >= pchz)
            {
                char c = *pchT;
                if (c == '\n')
                    break;
                if (c == ' ' || c == '\t')
                {
                    pch = pchT;
                    *pch = '\n';
                    dxCur = 0.0f;
                    cline++;
                    break;
                }
                pchT--;
            }
            if (dxCur != 0.0f)
            {
                *pch = '\n';
                cline++;
                dxCur = 0.0f;
            }
        }
        pch++;
    }
    return cline;
}

JUNK_NOP();

JUNK_ADDIU(50);

INCLUDE_ASM("asm/nonmatchings/P2/font", DrawPchz__5CFontPcP8CTextBoxT2P4GIFS);

void CFont::PushScaling(float rx, float ry)
{
    SFR *psfr = &m_asfr[m_csfr++];
    psfr->rx = m_rxScale;
    psfr->ry = m_rxScale;
    m_rxScale = m_asfr[0].rx * rx;
    m_ryScale = m_asfr[0].ry * ry;
}

void CFont::PopScaling()
{
    SFR *psfr = &m_asfr[--m_csfr];
    m_rxScale = psfr->rx;
    m_ryScale = psfr->ry;
}

/**
 * @todo 90.62% match. Issue with the vtable.
 */
INCLUDE_ASM("asm/nonmatchings/P2/font", PfontClone__8CFontBrxff);
#ifdef SKIP_ASM
CFont *CFontBrx::PfontClone(float rx, float ry)
{
    CFontBrx *pfontDest = new CFontBrx();
    CopyTo(pfontDest);
    pfontDest->m_rxScale = pfontDest->m_rxScale * rx;
    pfontDest->m_ryScale = pfontDest->m_ryScale * ry;
    return (CFont *)pfontDest;
}
#endif // SKIP_ASM

void CFontBrx::CopyTo(CFontBrx *pfontDest)
{
    CFont::CopyTo(pfontDest);
    pfontDest->m_ifont = m_ifont;
    pfontDest->m_pbmp = m_pbmp;
    pfontDest->m_pclut = m_pclut;
    *(long *)&pfontDest->m_tex0 = *(long *)&m_tex0;
    pfontDest->m_cqwBmpGifs = m_cqwBmpGifs;
    pfontDest->m_aqwBmpGifs = m_aqwBmpGifs;
    pfontDest->m_cqwClutGifs = m_cqwClutGifs;
    pfontDest->m_aqwClutGifs = m_aqwClutGifs;
    pfontDest->m_cglyff = m_cglyff;
    pfontDest->m_aglyff = m_aglyff;
    pfontDest->m_grffont = m_grffont;
}

int CFontBrx::FValid(char ch)
{
    return PglyffFromCh(ch) != NULL;
}

float CFontBrx::DxFromCh(char ch)
{
    GLYFF *pglyff = PglyffFromCh(ch);
    if (pglyff)
        return (float)(pglyff->dx + 1) * m_rxScale;
    return m_rxScale * (float)m_dxSpaceUnscaled;
}

int CFontBrx::FEnsureLoaded(GIFS *pgifs)
{
    int fLoad = (g_pfrmOpen->grffont & m_grffont) == 0;
    if (fLoad)
    {
        pgifs->EndDmaCnt();
        pgifs->AddDmaRefs(m_cqwBmpGifs, m_aqwBmpGifs);
        pgifs->AddDmaRefs(m_pbmp->cqwPixels, (QW *)m_pbmp->pbPixels);
        if (m_pclut)
        {
            pgifs->AddDmaRefs(m_cqwClutGifs, m_aqwClutGifs);
            pgifs->AddDmaRefs(m_pclut->cqwColors, (QW *)m_pclut->prgba);
        }
        pgifs->AddDmaCnt();
        g_pfrmOpen->grffont |= m_grffont;
    }
    return fLoad;
}

void CFontBrx::SetupDraw(CTextBox *ptbxClip, GIFS *pgifs)
{
    CFont::SetupDraw(ptbxClip, pgifs);
    int fLoad = FEnsureLoaded(pgifs);
    pgifs->AddPrimPack(6, 1, 0xE);
    if (fLoad)
        pgifs->PackAD(0x3F, 0);
    long tex1 = 0x31001;
    if (m_fGstest)
        tex1 = m_gstest;
    pgifs->PackAD(0x47, tex1);
    pgifs->PackAD(0x42, 0x44);
    pgifs->PackAD(6, *(long *)&m_tex0);
    pgifs->PackAD(0x14, 0x60);
    pgifs->PackAD(8, 5);
    pgifs->PackAD(0, 0x1D6);
    pgifs->AddPrimList(5, 0x43431);
}

void CFontBrx::SwitchTex0(GIFS *pgifs)
{
    int fLoad = FEnsureLoaded(pgifs);
    pgifs->AddPrimPack(6, 1, 0xE);
    if (fLoad)
        pgifs->PackAD(0x3F, 0);
    pgifs->PackAD(6, *(long *)&m_tex0);
    pgifs->PackAD(0, 0x1D6);
    pgifs->AddPrimList(5, 0x43431);
}

INCLUDE_ASM("asm/nonmatchings/P2/font", DxDrawCh__8CFontBrxcffUiP4GIFS);

INCLUDE_ASM("asm/nonmatchings/P2/font", FUN_0015cf70);

INCLUDE_ASM("asm/nonmatchings/P2/font", DrawPart__8CFontBrxffffffffUiP4GIFS);

INCLUDE_ASM("asm/nonmatchings/P2/font", EdgeRect__8CFontBrxP9CTextEdgeP8CTextBoxP4GIFS);

void CFontBrx::LoadFromBrx(CBinaryInputStream *pbis)
{
    FONTB fontb;
    pbis->Read(16, &fontb);
    int ifont = fontb.ifont;
    m_ifont = ifont;
    g_apfont[ifont] = this;
    m_pbmp = g_abmp + fontb.ibmp;
    m_pclut = (fontb.iclut != 0xFFFF) ? g_aclut + fontb.iclut : 0;
    m_dxCharUnscaled = fontb.dxChar;
    m_dxSpaceUnscaled = fontb.dxSpace;
    m_dyUnscaled = fontb.dy;
    m_ryScale = m_rxScale = fontb.rScale;
    m_cglyff = fontb.cglyff;
    m_aglyff = (GLYFF *)PvAllocSwImpl(m_cglyff * 8);
    pbis->Read(m_cglyff * 8, m_aglyff);
}

/**
 * @todo 87% matched (10 differing lines of 78). Register choice in the clut tex0 or.
 */
INCLUDE_ASM("asm/nonmatchings/P2/font", PostLoad__8CFontBrxP3GSB);
#ifdef SKIP_ASM
long BuildBmpTex0(BMP *pbmp, int igs);
void BuildBmpGifs(BMP *pbmp, int igs, GIFS *pgifs);
long BuildClutTex2(CLUT *pclut, int igs);
void BuildClutGifs(CLUT *pclut, int igs, GIFS *pgifs);

void CFontBrx::PostLoad(GSB *pgsb)
{
    GIFS gifs;
    QW aqw[16];
    int igs = IgsAllocGsb(pgsb, (ushort)m_pbmp->cgsPixels);
    BuildBmpTex0(m_pbmp, igs);
    *(long *)&m_tex0 = *(long *)&m_pbmp->tex0;
    gifs.AllocStatic(16, aqw);
    BuildBmpGifs(m_pbmp, igs, &gifs);
    gifs.DetachCopySw(&m_cqwBmpGifs, 0, &m_aqwBmpGifs, 7);
    if (m_pclut)
    {
        igs = IgsAllocGsb(pgsb, m_pclut->cgsColors);
        BuildClutTex2(m_pclut, igs);
        *(long *)&m_tex0 = *(long *)&m_tex0 | *(long *)&m_pclut->tex2;
        gifs.AllocStatic(16, aqw);
        BuildClutGifs(m_pclut, igs, &gifs);
        gifs.DetachCopySw(&m_cqwClutGifs, 0, &m_aqwClutGifs, 7);
    }
}
#endif // SKIP_ASM

GLYFF *CFontBrx::PglyffFromCh(char ch)
{
    uchar uch = ch;
    int iglyffMax = m_cglyff - 1;
    int iglyffMin = 0;
    while (iglyffMin <= iglyffMax)
    {
        int iglyff = (iglyffMax + iglyffMin) / 2;
        GLYFF *pglyff = (GLYFF *)(iglyff * 8 + (int)m_aglyff);
        int dwch = uch - pglyff->wch;
        if (dwch == 0)
            return pglyff;
        if (dwch > 0)
            iglyffMin = iglyff + 1;
        else
            iglyffMax = iglyff - 1;
    }
    return NULL;
}

INCLUDE_ASM("asm/nonmatchings/P2/font", __9CRichTextPcP5CFont);

void CRichText::Reset()
{
    this->m_pchCur = this->m_achz;
    this->m_pfontCur = this->m_pfontBase;
    this->m_rgbaSet = this->m_rgbaBase;
    this->m_rgbaCur = this->m_rgbaSet;
    this->m_unknown = 0;
}

void CRichText::SetBaseColor(RGBA *rgba)
{
    this->m_rgbaBase = *rgba;
    this->m_rgbaCur = this->m_rgbaBase;
}

INCLUDE_ASM("asm/nonmatchings/P2/font", ChNext__9CRichText);

int CRichText::Cch()
{
    int cch = 0;
    Reset();
    while (ChNext() != 0)
        cch++;
    return cch;
}

void CRichText::Trim(int cch)
{
    Reset();
    while (ChNext() != 0)
    {
        if (cch == 0)
            break;
        cch--;
    }
    *m_pchCur = 0;
}

float CRichText::Dx()
{
    float dx = 0.0f;
    char ch;
    Reset();
    while ((ch = ChNext()) != 0)
    {
        dx += m_pfontCur->DxFromCh(ch);
    }
    return dx;
}

int CRichText::ClineWrap(float dx)
{
    int cline = 1;
    float dxCur = 0.0f;
    char ch;
    Reset();
    while ((ch = ChNext()) != 0)
    {
        if (ch == '\n')
        {
            dxCur = 0.0f;
            cline++;
        }
        else
        {
            dxCur += m_pfontCur->DxFromCh(ch);
        }
        if (dx != 0.0f && dx < dxCur)
        {
            char *pch = m_pchCur - 1;
            while (pch >= m_achz)
            {
                char c = *pch;
                if (c == '\n')
                    break;
                if (c == ' ' || c == '\t')
                {
                    dxCur = 0.0f;
                    m_pchCur = pch + 1;
                    cline++;
                    *pch = '\n';
                    break;
                }
                pch--;
            }
            if (dxCur != 0.0f)
            {
                *m_pchCur = '\n';
                cline++;
                dxCur = 0.0f;
            }
        }
    }
    return cline;
}

float CRichText::DyWrap(float dx) // guessed name
{
    float dy = (float)m_pfontBase->m_dyUnscaled * m_pfontBase->m_ryScale;
    return dy * (float)ClineWrap(dx);
}

float CRichText::DxMaxLine()
{
    float dxMax = 0.0f;
    float dx = 0.0f;
    char ch;
    Reset();
    while ((ch = ChNext()) != 0)
    {
        if (ch == '\n')
        {
            dxMax = (dxMax > dx) ? dxMax : dx;
            dx = 0.0f;
        }
        else
        {
            dx += m_pfontCur->DxFromCh(ch);
        }
    }
    dxMax = (dxMax > dx) ? dxMax : dx;
    return dxMax;
}

void CRichText::GetExtents(float *pdx, float *pdy, float dxMax)
{
    int cline = ClineWrap(dxMax);
    float dx = DxMaxLine();
    float dy = (float)cline * ((float)m_pfontBase->m_dyUnscaled * m_pfontBase->m_ryScale);
    if (pdx)
        *pdx = dx;
    if (pdy)
        *pdy = dy;
}

INCLUDE_ASM("asm/nonmatchings/P2/font", Draw__9CRichTextP8CTextBoxT1P4GIFS);

void PostFontsLoad()
{
    GSB gsb;
    InitGsb(&gsb, 0x1400, 0x1e00);

    for (int i = 0; i < g_cfontBrx; i++)
    {
        g_afontBrx[i].PostLoad(&gsb);
    }
}

JUNK_WORD(0x46000802);
JUNK_WORD(0x46000802);
JUNK_WORD(0x46000802);
JUNK_ADDIU(10);
JUNK_WORD(0x0002102A);
JUNK_WORD(0xAC850030);
