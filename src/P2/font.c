#include <font.h>
#include <memory.h>

void StartupFont()
{
    g_pfont = NULL;
}

INCLUDE_ASM("asm/nonmatchings/P2/font", FUN_0015c188);

#ifdef SKIP_ASM
extern CFont *D_00262268[5];

CFont *FUN_0015c1c0(int i)
{
    CFont *pfont;

    if (i == -1)
    {
        return NULL;
    }

    pfont = D_00262268[i];
    if (pfont != NULL)
    {
        return pfont;
    }

    return g_pfont;
}
#else
INCLUDE_ASM("asm/nonmatchings/P2/font", FUN_0015c1c0);
#endif

INCLUDE_ASM("asm/nonmatchings/P2/font", FUN_0015c200);

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

INCLUDE_ASM("asm/nonmatchings/P2/font", SetupDraw__5CFontP8CTextBoxP4GIFS);

INCLUDE_ASM("asm/nonmatchings/P2/font", CleanupDraw__5CFontP8CTextBoxP4GIFS);

INCLUDE_ASM("asm/nonmatchings/P2/font", DxFromPchz__5CFontPc);

INCLUDE_ASM("asm/nonmatchings/P2/font", DyWrapPchz__5CFontPcf);

INCLUDE_ASM("asm/nonmatchings/P2/font", ClineWrapPchz__5CFontPcf);

JUNK_ADDIU(50);

INCLUDE_ASM("asm/nonmatchings/P2/font", DrawPchz__5CFontPcP8CTextBoxT2P4GIFS);

#ifdef SKIP_ASM
void CFont::PushScaling(float rx, float ry)
{
    int csfr = m_csfr;

    m_csfr = csfr + 1;
    m_asfr[csfr].rx = m_rxScale;
    m_asfr[csfr].ry = m_rxScale;
    m_rxScale = m_asfr[0].rx * rx;
    m_ryScale = m_asfr[0].ry * ry;
}

void CFont::PopScaling()
{
    int csfr = m_csfr - 1;

    m_csfr = csfr;
    m_rxScale = m_asfr[csfr].rx;
    m_ryScale = m_asfr[csfr].ry;
}
#else
INCLUDE_ASM("asm/nonmatchings/P2/font", PushScaling__5CFontff);

INCLUDE_ASM("asm/nonmatchings/P2/font", PopScaling__5CFont);
#endif

INCLUDE_ASM("asm/nonmatchings/P2/font", PfontClone__8CFontBrxff);

INCLUDE_ASM("asm/nonmatchings/P2/font", CopyTo__8CFontBrxP8CFontBrx);

bool CFontBrx::FValid(char ch)
{
    return PglyffFromCh(ch) != 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/font", DxFromCh__8CFontBrxc);

INCLUDE_ASM("asm/nonmatchings/P2/font", FEnsureLoaded__8CFontBrxP4GIFS);

INCLUDE_ASM("asm/nonmatchings/P2/font", SetupDraw__8CFontBrxP8CTextBoxP4GIFS);

INCLUDE_ASM("asm/nonmatchings/P2/font", SwitchTex0__8CFontBrxP4GIFS);

INCLUDE_ASM("asm/nonmatchings/P2/font", DxDrawCh__8CFontBrxcffUiP4GIFS);

INCLUDE_ASM("asm/nonmatchings/P2/font", FUN_0015cf70);

INCLUDE_ASM("asm/nonmatchings/P2/font", DrawPart__8CFontBrxffffffffUiP4GIFS);

INCLUDE_ASM("asm/nonmatchings/P2/font", EdgeRect__8CFontBrxP9CTextEdgeP8CTextBoxP4GIFS);

INCLUDE_ASM("asm/nonmatchings/P2/font", LoadFromBrx__8CFontBrxP18CBinaryInputStream);

INCLUDE_ASM("asm/nonmatchings/P2/font", PostLoad__8CFontBrxP3GSB);

INCLUDE_ASM("asm/nonmatchings/P2/font", PglyffFromCh__8CFontBrxc);

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

INCLUDE_ASM("asm/nonmatchings/P2/font", Cch__9CRichText);

INCLUDE_ASM("asm/nonmatchings/P2/font", Trim__9CRichTexti);

INCLUDE_ASM("asm/nonmatchings/P2/font", Dx__9CRichText);

INCLUDE_ASM("asm/nonmatchings/P2/font", ClineWrap__9CRichTextf);

#ifdef SKIP_ASM
float FUN_0015e1b0(CRichText *prt)
{
    CFont *pfont = prt->m_pfontBase;
    float dy = (float)pfont->m_dyUnscaled * pfont->m_ryScale;

    return dy * (float)prt->ClineWrap(dy);
}
#else
INCLUDE_ASM("asm/nonmatchings/P2/font", FUN_0015e1b0);
#endif

INCLUDE_ASM("asm/nonmatchings/P2/font", DxMaxLine__9CRichText);

INCLUDE_ASM("asm/nonmatchings/P2/font", GetExtents__9CRichTextPfT1f);

INCLUDE_ASM("asm/nonmatchings/P2/font", Draw__9CRichTextP8CTextBoxT1P4GIFS);

INCLUDE_ASM("asm/nonmatchings/P2/font", PostFontsLoad__Fv);

JUNK_WORD(0x46000802);
JUNK_WORD(0x46000802);
JUNK_WORD(0x46000802);
JUNK_ADDIU(10);
JUNK_WORD(0x0002102A);
JUNK_WORD(0xAC850030);
