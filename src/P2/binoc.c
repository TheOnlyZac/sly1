#include <binoc.h>

INCLUDE_ASM(const s32, "P2/binoc", InitBei);

INCLUDE_ASM(const s32, "P2/binoc", GEvaluateBei);

INCLUDE_ASM(const s32, "P2/binoc", FUN_001310f0);

INCLUDE_ASM(const s32, "P2/binoc", FUN_00131140);

INCLUDE_ASM(const s32, "P2/binoc", FUN_00131198);

INCLUDE_ASM(const s32, "P2/binoc", DrawBinocCompass);

INCLUDE_ASM(const s32, "P2/binoc", DrawBinocZoom);

INCLUDE_ASM(const s32, "P2/binoc", DrawBinocReticle);

INCLUDE_ASM(const s32, "P2/binoc", DrawBinocOutline);

INCLUDE_ASM(const s32, "P2/binoc", FUN_00134aa0);

INCLUDE_ASM(const s32, "P2/binoc", FUN_00134b48);

INCLUDE_ASM(const s32, "P2/binoc", DrawBinocFilter);

INCLUDE_ASM(const s32, "P2/binoc", FUN_00135550);

INCLUDE_ASM(const s32, "P2/binoc", open_close_binoc);

INCLUDE_ASM(const s32, "P2/binoc", FUN_001357f0);

INCLUDE_ASM(const s32, "P2/binoc", FUN_00135858);

INCLUDE_ASM(const s32, "P2/binoc", FUN_001358d0);

INCLUDE_ASM(const s32, "P2/binoc", func_00135E20);

INCLUDE_ASM(const s32, "P2/binoc", func_00135E40);

INCLUDE_ASM(const s32, "P2/binoc", func_00135E70);

INCLUDE_ASM(const s32, "P2/binoc", SetBinocBfk);

INCLUDE_ASM(const s32, "P2/binoc", FUN_00135f48);

INCLUDE_ASM(const s32, "P2/binoc", FUN_00136040);

INCLUDE_ASM(const s32, "P2/binoc", FUN_00136238);

INCLUDE_ASM(const s32, "P2/binoc", FUN_001363d0);

INCLUDE_ASM(const s32, "P2/binoc", SetBinocAchzDraw);

INCLUDE_ASM(const s32, "P2/binoc", FDoneBinocAchz);

INCLUDE_ASM(const s32, "P2/binoc", SetBinocLookat);

INCLUDE_ASM(const s32, "P2/binoc", SetBinocZoom);

INCLUDE_ASM(const s32, "P2/binoc", FUN_001365f0);

INCLUDE_ASM(const s32, "P2/binoc", FUN_00136648);

INCLUDE_ASM(const s32, "P2/binoc", DrawBinoc);

INCLUDE_ASM(const s32, "P2/binoc", GetBinocReticleFocus);

INCLUDE_ASM(const s32, "P2/binoc", FUN_00136ef8);

INCLUDE_ASM(const s32, "P2/binoc", FUN_00136fa8);

INCLUDE_ASM(const s32, "P2/binoc", __static_initialization_and_destruction_0);

void CTextBox::SetPos(float x, float y)
{
    m_x = x;
    m_y = y;
}

void CTextBox::SetSize(float dx, float dy)
{
    m_dx = dx;
    m_dy = dy;
}

INCLUDE_ASM(const s32, "P2/binoc", SetTextColor__8CTextBoxG4RGBA);
/*void CTextBox::SetTextColor(RGBA *rgba)
{
    this->m_rgba = *rgba;
}*/

void CTextBox::SetHorizontalJust(JH jh)
{
    m_jh = jh;
}

void CTextBox::SetVerticalJust(JV jv)
{
    m_jv = jv;
}

INCLUDE_ASM(const s32, "P2/binoc", _GLOBAL_$I$InitBei__FP3BEIP3CLQffi);
