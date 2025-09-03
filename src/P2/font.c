#include <font.h>

void StartupFont()
{
    g_pfont = 0;
}

INCLUDE_ASM(const s32, "P2/font", FUN_0015c188);

INCLUDE_ASM(const s32, "P2/font", FUN_0015c1c0);

INCLUDE_ASM(const s32, "P2/font", FUN_0015c200);

INCLUDE_ASM(const s32, "P2/font", CopyTo__5CFontP5CFont);

INCLUDE_ASM(const s32, "P2/font", SetupDraw__5CFontP8CTextBoxP4GIFS);

INCLUDE_ASM(const s32, "P2/font", CleanupDraw__5CFontP8CTextBoxP4GIFS);

INCLUDE_ASM(const s32, "P2/font", DxFromPchz__5CFontPc);

INCLUDE_ASM(const s32, "P2/font", DyWrapPchz__5CFontPcf);

INCLUDE_ASM(const s32, "P2/font", ClineWrapPchz__5CFontPcf);

INCLUDE_ASM(const s32, "P2/font", junk_0015C630);

INCLUDE_ASM(const s32, "P2/font", DrawPchz__5CFontPcP8CTextBoxT2P4GIFS);

INCLUDE_ASM(const s32, "P2/font", PushScaling__5CFontff);

INCLUDE_ASM(const s32, "P2/font", PopScaling__5CFont);

INCLUDE_ASM(const s32, "P2/font", PfontClone__8CFontBrxff);

INCLUDE_ASM(const s32, "P2/font", CopyTo__8CFontBrxP8CFontBrx);

INCLUDE_ASM(const s32, "P2/font", FValid__8CFontBrxc);

INCLUDE_ASM(const s32, "P2/font", DxFromCh__8CFontBrxc);

INCLUDE_ASM(const s32, "P2/font", FEnsureLoaded__8CFontBrxP4GIFS);

INCLUDE_ASM(const s32, "P2/font", SetupDraw__8CFontBrxP8CTextBoxP4GIFS);

INCLUDE_ASM(const s32, "P2/font", SwitchTex0__8CFontBrxP4GIFS);

INCLUDE_ASM(const s32, "P2/font", DxDrawCh__8CFontBrxcffUiP4GIFS);

INCLUDE_ASM(const s32, "P2/font", FUN_0015cf70);

INCLUDE_ASM(const s32, "P2/font", DrawPart__8CFontBrxffffffffUiP4GIFS);

INCLUDE_ASM(const s32, "P2/font", EdgeRect__8CFontBrxP9CTextEdgeP8CTextBoxP4GIFS);

INCLUDE_ASM(const s32, "P2/font", LoadFromBrx__8CFontBrxP18CBinaryInputStream);

INCLUDE_ASM(const s32, "P2/font", PostLoad__8CFontBrxP3GSB);

INCLUDE_ASM(const s32, "P2/font", PglyffFromCh__8CFontBrxc);

INCLUDE_ASM(const s32, "P2/font", __9CRichTextPcP5CFont);

INCLUDE_ASM(const s32, "P2/font", Reset__9CRichText);

INCLUDE_ASM(const s32, "P2/font", SetBaseColor__9CRichTextG4RGBA);

INCLUDE_ASM(const s32, "P2/font", ChNext__9CRichText);

INCLUDE_ASM(const s32, "P2/font", Cch__9CRichText);

INCLUDE_ASM(const s32, "P2/font", Trim__9CRichTexti);

INCLUDE_ASM(const s32, "P2/font", Dx__9CRichText);

INCLUDE_ASM(const s32, "P2/font", ClineWrap__9CRichTextf);

INCLUDE_ASM(const s32, "P2/font", FUN_0015e1b0);

INCLUDE_ASM(const s32, "P2/font", DxMaxLine__9CRichText);

INCLUDE_ASM(const s32, "P2/font", GetExtents__9CRichTextPfT1f);

INCLUDE_ASM(const s32, "P2/font", Draw__9CRichTextP8CTextBoxT1P4GIFS);

INCLUDE_ASM(const s32, "P2/font", PostFontsLoad__Fv);

INCLUDE_ASM(const s32, "P2/font", junk_0015E678);
