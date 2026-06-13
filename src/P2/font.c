#include <font.h>
#include <memory.h>
#include <gs.h>

void StartupFont()
{
    g_pfont = NULL;
}

INCLUDE_ASM("asm/nonmatchings/P2/font", FUN_0015c188);

extern "C" {
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
}

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

INCLUDE_ASM("asm/nonmatchings/P2/font", PushScaling__5CFontff);

INCLUDE_ASM("asm/nonmatchings/P2/font", PopScaling__5CFont);

INCLUDE_ASM("asm/nonmatchings/P2/font", PfontClone__8CFontBrxff);

void CopyTo_CFontBrx(CFontBrx *self, CFontBrx *pfontDest) __asm__("CopyTo__8CFontBrxP8CFontBrx");
void CopyTo_CFontBrx(CFontBrx *self, CFontBrx *pfontDest)
{
    self->CopyTo(pfontDest);
    STRUCT_OFFSET(pfontDest, 0x50, int) = STRUCT_OFFSET(self, 0x50, int);
    STRUCT_OFFSET(pfontDest, 0x54, int) = STRUCT_OFFSET(self, 0x54, int);
    STRUCT_OFFSET(pfontDest, 0x58, int) = STRUCT_OFFSET(self, 0x58, int);
    STRUCT_OFFSET(pfontDest, 0x60, uint64_t) = STRUCT_OFFSET(self, 0x60, uint64_t);
    STRUCT_OFFSET(pfontDest, 0x68, int) = STRUCT_OFFSET(self, 0x68, int);
    STRUCT_OFFSET(pfontDest, 0x6C, int) = STRUCT_OFFSET(self, 0x6C, int);
    STRUCT_OFFSET(pfontDest, 0x70, int) = STRUCT_OFFSET(self, 0x70, int);
    STRUCT_OFFSET(pfontDest, 0x74, int) = STRUCT_OFFSET(self, 0x74, int);
    STRUCT_OFFSET(pfontDest, 0x78, int) = STRUCT_OFFSET(self, 0x78, int);
    STRUCT_OFFSET(pfontDest, 0x7C, int) = STRUCT_OFFSET(self, 0x7C, int);
    STRUCT_OFFSET(pfontDest, 0x80, int) = STRUCT_OFFSET(self, 0x80, int);
}

bool CFontBrx::FValid(char ch)
{
    return PglyffFromCh(ch) != 0;
}

float DxFromCh_CFontBrx(CFontBrx *self, char ch) __asm__("DxFromCh__8CFontBrxc");
float DxFromCh_CFontBrx(CFontBrx *self, char ch)
{
    unsigned short *pglyff = (unsigned short *)self->PglyffFromCh(ch);

    if (pglyff != 0)
    {
        return (float)(int)(pglyff[3] + 1) * STRUCT_OFFSET(self, 0x44, float);
    }

    return (float)STRUCT_OFFSET(self, 0x4, int) * STRUCT_OFFSET(self, 0x44, float);
}

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

extern "C" void Reset__9CRichText(CRichText *self);
extern "C" int ChNext__9CRichText(CRichText *self);

extern "C" float Dx__9CRichText(CRichText *self)
{
    Reset__9CRichText(self);

    float dx = 0.0f;
    int ch;
    while ((ch = ChNext__9CRichText(self)) != 0)
    {
        CFont *pfont = STRUCT_OFFSET(self, 0x8, CFont *);
        void *pv = STRUCT_OFFSET(pfont, 0x4c, void *);
        dx += (*(float (**)(void *, int))((char *)pv + 0x1c))(
            (char *)pfont + STRUCT_OFFSET(pv, 0x18, short), ch);
    }

    return dx;
}

INCLUDE_ASM("asm/nonmatchings/P2/font", ClineWrap__9CRichTextf);

INCLUDE_ASM("asm/nonmatchings/P2/font", FUN_0015e1b0);

INCLUDE_ASM("asm/nonmatchings/P2/font", DxMaxLine__9CRichText);

extern "C" int ClineWrap__9CRichTextf(CRichText *self, float dyMax);
extern "C" float DxMaxLine__9CRichText(CRichText *self);

extern "C" void GetExtents__9CRichTextPfT1f(CRichText *self, float *pdx, float *pdy, float dyMax)
{
    int cline = ClineWrap__9CRichTextf(self, dyMax);
    float dxMax = DxMaxLine__9CRichText(self);
    CFont *pfont = STRUCT_OFFSET(self, 0xC, CFont *);
    float dyLine = (float)STRUCT_OFFSET(pfont, 0x8, int) * STRUCT_OFFSET(pfont, 0x48, float);
    float dyTotal = (float)cline * dyLine;
    if (pdx)
        *pdx = dxMax;
    if (pdy)
        *pdy = dyTotal;
}

INCLUDE_ASM("asm/nonmatchings/P2/font", Draw__9CRichTextP8CTextBoxT1P4GIFS);

extern int D_00262260;
extern CFontBrx *D_00262264;
extern "C" void PostLoad__8CFontBrxP3GSB(CFontBrx *self, GSB *pgsb);

void PostFontsLoad()
{
    GSB gsb;
    int i;

    InitGsb(&gsb, 0x1400, 0x1E00);
    for (i = 0; i < D_00262260; i++)
    {
        PostLoad__8CFontBrxP3GSB(D_00262264 + i, &gsb);
    }
}

JUNK_WORD(0x46000802);
JUNK_WORD(0x46000802);
JUNK_WORD(0x46000802);
JUNK_ADDIU(10);
JUNK_WORD(0x0002102A);
JUNK_WORD(0xAC850030);
