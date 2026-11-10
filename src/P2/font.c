#include <font.h>
#include <memory.h>
#include <gs.h>
#include <binoc.h>
#include <frm.h>
#include <shd.h>
#include <screen.h>
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

int FFontLoaded(int ifont) // guessed name
{
    if (ifont == -1)
        goto no;
    ifont = (int)g_apfont[ifont];
    if (ifont != 0)
        goto yes;
no:
    return 0;
yes:
    return 1;
}

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

/**
 * @todo 97% matched (6 differing lines of 181). Only the jh == JH_Right compare register swap remains.
 */
INCLUDE_ASM("asm/nonmatchings/P2/font", DrawPchz__5CFontPcP8CTextBoxT2P4GIFS);
#ifdef SKIP_ASM
void CFont::DrawPchz(char *pchz, CTextBox *ptbx, CTextBox *ptbxClip, GIFS *pgifs)
{
    int fNewLine = 1;
    float x;
    float y;
    char *pch;
    SetupDraw(ptbxClip, pgifs);
    if (ptbx->m_jv == JV_Top)
    {
        y = ptbx->m_y;
    }
    else
    {
        float dyLine = (float)m_dyUnscaled * m_ryScale;
        float dyTotal = dyLine;
        char *p = pchz;
        while (*p)
        {
            if (*p++ == '\n')
                dyTotal += (float)m_dyUnscaled * m_ryScale;
        }
        if (ptbx->m_jv == JV_Bottom)
            y = (ptbx->m_y + ptbx->m_dy) - dyTotal;
        else
            y = ptbx->m_y + (ptbx->m_dy - dyTotal) * 0.5f;
    }
    pch = pchz;
    float half;
    if (*pch)
    {
    half = 0.5f;
    while (*pch)
    {
        char ch = *pch;
        char *pchNext = pch + 1;
        if (ch == '\n')
        {
            y += (float)m_dyUnscaled * m_ryScale;
            fNewLine = 1;
        }
        else
        {
            if (fNewLine)
            {
                if (ptbx->m_jh == JH_Left)
                {
                    x = ptbx->m_x;
                }
                else
                {
                    float dxLine = 0.0f;
                    char *p = pch;
                    while (*p != 0 && *p != '\n')
                        dxLine += DxFromCh(*p++);
                    if (ptbx->m_jh == JH_Right)
                        x = ptbx->m_x + ptbx->m_dx - dxLine;
                    else
                        x = ptbx->m_x + (ptbx->m_dx - dxLine) * half;
                }
                fNewLine = 0;
            }
            x += DxDrawCh(*pch, x, y, *(uint *)&ptbx->m_rgba, pgifs);
        }
        pch = pchNext;
    }
    }
    CleanupDraw(ptbxClip, pgifs);
}
#endif // SKIP_ASM

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

CFont *CFontBrx::PfontClone(float rx, float ry)
{
    CFontBrx *pfontDest = new CFontBrx();
    CopyTo(pfontDest);
    pfontDest->m_rxScale = pfontDest->m_rxScale * rx;
    pfontDest->m_ryScale = pfontDest->m_ryScale * ry;
    return (CFont *)pfontDest;
}

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

float CFontBrx::DxDrawCh(char ch, float xChar, float yChar, uint rgba, GIFS *pgifs)
{
    GLYFF *pglyff = PglyffFromCh(ch);
    if (pglyff)
    {
        int dTexH = 1 << (int)((*(ulong *)&m_tex0 >> 30) & 0xF);
        float dxGlyph = (float)pglyff->dx * m_rxScale;
        float dyGlyph = (float)m_dyUnscaled * m_ryScale;
        float xRight = xChar + dxGlyph;
        float yBottom = yChar + dyGlyph;
        if (xRight >= 0.0f && xChar <= 640.0f && yBottom >= 0.0f && yChar <= 492.80002f)
        {
            rgba = (rgba & 0xFFFFFF) | ((((rgba >> 24) + 1) & 0x1FE) << 23);
            pgifs->ListRGBAQ(rgba, 0.0f);
            pgifs->ListUV(pglyff->x << 4, (dTexH - pglyff->y) << 4);
            pgifs->ListXYZF((int)((xChar + 1728.0f) * 16.0f), (int)((yChar * 0.45454547f + 1936.0f) * 16.0f), m_z, 0);
            pgifs->ListUV((pglyff->x + pglyff->dx) << 4, (dTexH - (pglyff->y + m_dyUnscaled)) << 4);
            pgifs->ListXYZF((int)((xRight + 1728.0f) * 16.0f), (int)((yBottom * 0.45454547f + 1936.0f) * 16.0f), m_z, 0);
        }
        return (float)(pglyff->dx + 1) * m_rxScale;
    }
    return (float)m_dxSpaceUnscaled * m_rxScale;
}

void CFontBrx::DrawChRotated(char ch, float xChar, float yChar, uint rgba, GIFS *pgifs) // guessed name
{
    GLYFF *pglyff = PglyffFromCh(ch);
    if (pglyff)
    {
        int dTexH = 1 << (int)((*(ulong *)&m_tex0 >> 30) & 0xF);
        float dxGlyph = (float)pglyff->dx * m_rxScale;
        float dyGlyph = (float)m_dyUnscaled * m_ryScale;
        float xRight = xChar + dyGlyph;
        float yBottom = yChar + dxGlyph;
        if (xRight >= 0.0f && xChar <= 640.0f && yBottom >= 0.0f && yChar <= 492.80002f)
        {
            int uLeft = (pglyff->x << 4) + g_duGlyph;
            int uRight = ((pglyff->x + pglyff->dx) << 4) + g_duGlyph;
            int vTop = ((dTexH - pglyff->y) << 4) + g_dvGlyph;
            int vBottom = ((dTexH - (pglyff->y + m_dyUnscaled)) << 4) + g_dvGlyph;
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
            pgifs->PackAD(0, 0x1D4);
            pgifs->AddPrimList(9, 0x434343431L);
            rgba = (rgba & 0xFFFFFF) | ((((rgba >> 24) + 1) & 0x1FE) << 23);
            pgifs->ListRGBAQ(rgba, 0.0f);
            pgifs->ListUV(uLeft, vTop);
            int x0 = (int)((xChar + 1728.0f) * 16.0f);
            int yA = (int)((yBottom * 0.45454547f + 1936.0f) * 16.0f);
            pgifs->ListXYZF(x0, yA, m_z, 0);
            pgifs->ListUV(uRight, vTop);
            int yB = (int)((yChar * 0.45454547f + 1936.0f) * 16.0f);
            pgifs->ListXYZF(x0, yB, m_z, 0);
            pgifs->ListUV(uLeft, vBottom);
            int x1 = (int)((xRight + 1728.0f) * 16.0f);
            pgifs->ListXYZF(x1, yA, m_z, 0);
            pgifs->ListUV(uRight, vBottom);
            pgifs->ListXYZF(x1, yB, m_z, 0);
            CleanupDraw(0, &g_gifs);
        }
    }
}

void CFontBrx::DrawPart(float xLeft, float yTop, float xRight, float yBottom, float sLeft, float tTop, float sRight, float tBottom, uint rgba, GIFS *pgifs)
{
    rgba = (rgba & 0xFFFFFF) | ((((rgba >> 24) + 1) & 0x1FE) << 23);
    pgifs->ListRGBAQ(rgba, 0.0f);
    pgifs->ListUV((int)(sLeft * 16.0f), (int)(tTop * 16.0f));
    pgifs->ListXYZF((int)((xLeft + 1728.0f) * 16.0f), (int)((yTop * 0.45454547f + 1936.0f) * 16.0f), m_z, 0);
    pgifs->ListUV((int)(sRight * 16.0f), (int)(tBottom * 16.0f));
    pgifs->ListXYZF((int)((xRight + 1728.0f) * 16.0f), (int)((yBottom * 0.45454547f + 1936.0f) * 16.0f), m_z, 0);
}

/**
 * @todo 85% matched (38 differing lines of 248). Instruction scheduling and register assignment of the locals.
 */
INCLUDE_ASM("asm/nonmatchings/P2/font", EdgeRect__8CFontBrxP9CTextEdgeP8CTextBoxP4GIFS);
#ifdef SKIP_ASM
void CFontBrx::EdgeRect(CTextEdge *pte, CTextBox *ptbx, GIFS *pgifs)
{
    GLYFF *pglyff = PglyffFromCh(pte->m_ch);
    if (pglyff)
    {
        pte->m_pfont->PushScaling(pte->m_rxScaling, pte->m_ryScaling);
        int iuL = pglyff->x;
        int dTexH = 1 << (int)((*(ulong *)&m_tex0 >> 30) & 0xF);
        float dyGlyph = (float)m_dyUnscaled * m_ryScale;
        float dyExtra = pte->m_dyExtra * m_ryScale;
        float yt1 = ptbx->m_y - dyExtra;
        float dxExtra = pte->m_dxExtra * m_rxScale;
        float xr0 = ptbx->m_x + ptbx->m_dx + dxExtra;
        float dxGlyph = (float)pglyff->dx * m_rxScale;
        float yt0 = yt1 - dyGlyph;
        float uL = (float)iuL;
        int iuR = pglyff->x + pglyff->dx;
        float xl1 = ptbx->m_x - dxExtra;
        float yb0 = ptbx->m_y + ptbx->m_dy + dyExtra;
        float uM = (float)((iuL + iuR) / 2);
        float xl0 = xl1 - dxGlyph;
        int ivB = dTexH - (pglyff->y + m_dyUnscaled);
        int ivT = dTexH - pglyff->y;
        float vT = (float)ivT;
        float xr1 = xr0 + dxGlyph;
        float vM = (float)((ivT + ivB) / 2);
        float yb1 = yb0 + dyGlyph;
        SetupDraw(0, pgifs);
        float vB = (float)ivB;
        float uR = (float)iuR;
        DrawPart(xl0, yt0, xl1, yt1, uL, vT, uM, vM, *(uint *)&pte->m_rgba, pgifs);
        DrawPart(xr0, yt0, xr1, yt1, uM, vT, uR, vM, *(uint *)&pte->m_rgba, pgifs);
        DrawPart(xl0, yb0, xl1, yb1, uL, vM, uM, vB, *(uint *)&pte->m_rgba, pgifs);
        DrawPart(xr0, yb0, xr1, yb1, uM, vM, uR, vB, *(uint *)&pte->m_rgba, pgifs);
        DrawPart(xl1, yt0, xr0, yt1, uM, vT, uM, vM, *(uint *)&pte->m_rgba, pgifs);
        DrawPart(xl1, yb0, xr0, yb1, uM, vM, uM, vB, *(uint *)&pte->m_rgba, pgifs);
        DrawPart(xl0, yt1, xl1, yb0, uL, vM, uM, vM, *(uint *)&pte->m_rgba, pgifs);
        DrawPart(xr0, yt1, xr1, yb0, uM, vM, uR, vM, *(uint *)&pte->m_rgba, pgifs);
        DrawPart(xl1, yt1, xr0, yb0, uM, vM, uM, vM, *(uint *)&pte->m_rgba, pgifs);
        pte->m_pfont->PopScaling();
        CleanupDraw(0, pgifs);
    }
}
#endif // SKIP_ASM

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

CRichText::CRichText(char *achz, CFont *pfont)
{
    m_achz = achz;
    m_pfontBase = pfont;
    uint rgba = 0xFF808080;
    *(uint *)&m_rgbaOther = rgba;
    *(uint *)&m_rgbaBase = rgba;
    *(uint *)&m_rgbaSet = rgba;
    *(uint *)&m_rgbaCur = rgba;
    Reset();
}

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

char CRichText::ChNext()
{
    int one = 1; // forces a separate register for the constant 1
    int fDone = 0;
    while (!fDone)
    {
        char ch = *m_pchCur;
        switch (ch)
        {
        case '~':
            if (m_pchCur[1] == ch)
            {
                m_pchCur = m_pchCur + 1;
                fDone = 1;
            }
            else if (m_pchCur[1] == '.')
            {
                m_rgbaSet = m_rgbaBase;
                m_rgbaCur = m_rgbaSet;
                m_pchCur += 2;
            }
            else
            {
                char *p = m_pchCur + 1;
                uint rgb = 0;
                while (*p != 0 && p - m_pchCur < 7)
                {
                    uchar c = *p;
                    int d;
                    if (c - '0' < 10U)
                        d = (char)c - '0';
                    else if (c - 'A' < 6U)
                        d = (char)c - 'A' + 10;
                    else if (c - 'a' < 6U)
                        d = (char)c - 'a' + 10;
                    else
                        break;
                    p++;
                    rgb = rgb * 16 + d;
                }
                if (p - m_pchCur >= 7)
                {
                    m_rgbaSet.bRed = (((rgb >> 16) & 0xFF) + 1) >> 1;
                    m_rgbaSet.bGreen = (((rgb & 0xFF00) >> 8) + 1) >> 1;
                    m_rgbaSet.bBlue = ((rgb & 0xFF) + 1) >> 1;
                    m_rgbaCur = m_rgbaSet;
                    m_pchCur += 7;
                }
                else
                {
                    m_pfontCur = m_pfontBase;
                    m_rgbaCur = m_rgbaBase;
                    fDone = 1;
                }
            }
            break;
        case '&':
        {
            char c1 = m_pchCur[1];
            if (c1 == ch)
            {
                m_pchCur = m_pchCur + 1;
                fDone = 1;
            }
            else if (c1 == '.')
            {
                m_pfontCur = m_pfontBase;
                m_rgbaCur = m_rgbaSet;
                m_unknown = one;
                m_pchCur += 2;
            }
            else
            {
                CFont *pfont = PfontFromCh(c1);
                if (pfont)
                {
                    ((CFontBrx *)pfont)->CopyTo(&m_fontOther);
                    m_pchCur += 2;
                    CFont *pfo = &m_fontOther;
                    float rScale = ((float)m_pfontBase->m_dyUnscaled * m_pfontBase->m_ryScale) / ((float)pfo->m_dyUnscaled * pfo->m_ryScale);
                    m_pfontCur = pfo;
                    m_fontOther.m_rxScale *= rScale;
                    m_fontOther.m_ryScale *= rScale;
                    RGBA rgba = m_rgbaOther;
                    rgba.bAlpha = m_rgbaCur.bAlpha;
                    m_rgbaCur = rgba;
                    m_unknown = one;
                }
                else
                {
                    m_pfontCur = m_pfontBase;
                    fDone = 1;
                    m_rgbaCur = m_rgbaBase;
                    m_unknown = one;
                }
            }
            break;
        }
        case '^':
            if (m_pchCur[1] == ch)
            {
                m_pchCur = m_pchCur + 1;
                fDone = 1;
            }
            else if (m_pchCur[1] == '.')
            {
                m_pfontCur->PopScaling();
                m_pchCur += 2;
            }
            else
            {
                float r = (float)(m_pchCur[1] - '0') + (float)(m_pchCur[2] - '0') * 0.1f;
                m_pfontCur->PushScaling(r * m_pfontCur->m_rxScale, r * m_pfontCur->m_ryScale);
                m_pchCur += 3;
            }
            break;
        default:
            fDone = 1;
            break;
        }
    }
    return *m_pchCur++;
}

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

extern "C" void *memset(void *, int, unsigned int);

void CRichText::Draw(CTextBox *ptbx, CTextBox *ptbxClip, GIFS *pgifs)
{
    float adx[64];
    RGBA rgbaBase;
    int fNewLine = 1;
    int cline = 0;
    char ch;
    float x;
    float y;
    float *pdx;
    CFont *pfontSetup;
    memset(adx, 0, sizeof(adx));
    Reset();
    while ((ch = ChNext()) != 0)
    {
        if (ch == '\n')
            cline++;
        else
            adx[cline] += m_pfontCur->DxFromCh(ch);
    }
    if (ptbx->m_jv == JV_Top)
    {
        y = ptbx->m_y;
    }
    else
    {
        float dyTotal = (float)(cline + 1) * ((float)m_pfontBase->m_dyUnscaled * m_pfontBase->m_ryScale);
        if (ptbx->m_jv == JV_Bottom)
            y = ptbx->m_y + ptbx->m_dy - dyTotal;
        else
            y = ptbx->m_y + (ptbx->m_dy - dyTotal) * 0.5f;
    }
    rgbaBase = ptbx->m_rgba;
    SetBaseColor(&rgbaBase);
    pfontSetup = 0;
    Reset();
    float half = 0.5f;
    JH jhRight = JH_Right;
    pdx = adx;
    while ((ch = ChNext()) != 0)
    {
        if (ch == '\n')
        {
            fNewLine = 1;
            pdx++;
            y += (float)m_pfontBase->m_dyUnscaled * m_pfontBase->m_ryScale;
        }
        else
        {
            if (fNewLine)
            {
                if (ptbx->m_jh == JH_Left)
                {
                    x = ptbx->m_x;
                }
                else
                {
                    float dxLine = *pdx;
                    if (ptbx->m_jh == jhRight)
                        x = ptbx->m_x + ptbx->m_dx - dxLine;
                    else
                        x = ptbx->m_x + (ptbx->m_dx - dxLine) * half;
                }
                fNewLine = 0;
            }
            if (pfontSetup == 0)
            {
                m_pfontCur->SetupDraw(ptbxClip, pgifs);
                pfontSetup = m_pfontCur;
            }
            else if (m_unknown)
            {
                m_pfontCur->SwitchTex0(pgifs);
                m_unknown = 0;
            }
            x += m_pfontCur->DxDrawCh(ch, x, y, *(uint *)&m_rgbaCur, pgifs);
        }
    }
    m_pfontCur->CleanupDraw(ptbxClip, pgifs);
}

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
