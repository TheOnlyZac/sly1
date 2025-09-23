#include <binoc.h>
#include <alo.h>

INCLUDE_ASM("asm/nonmatchings/P2/binoc", InitBei);

INCLUDE_ASM("asm/nonmatchings/P2/binoc", GEvaluateBei);

void InitBinoc(BINOC *binoc, BLOTK blotk)
{
    binoc->width = 640.0f;
    binoc->height = 492.80001f;
    binoc->unk0 = 15.0f;
    binoc->unk1 = 0x80ffffff;
    InitBlot(binoc, blotk);
}

void ResetBinoc(BINOC *binoc)
{
    binoc->pvtbinoc->pfnSetBinocAchzDraw(binoc, 0);
    SetBinocLookat(binoc, (ALO *)0);
    binoc->dxReticle = 0.0f;
    binoc->dyReticle = 0.0f;
    binoc->uCompassBarOffset = 0.4f;
    binoc->zoom = 0.0f;
}

INCLUDE_ASM("asm/nonmatchings/P2/binoc", PostBinocLoad__FP5BINOC);

INCLUDE_ASM("asm/nonmatchings/P2/binoc", DrawBinocCompass);

INCLUDE_ASM("asm/nonmatchings/P2/binoc", DrawBinocZoom);

INCLUDE_ASM("asm/nonmatchings/P2/binoc", DrawBinocReticle);

INCLUDE_ASM("asm/nonmatchings/P2/binoc", DrawBinocOutline);

INCLUDE_ASM("asm/nonmatchings/P2/binoc", FUN_00134aa0);

INCLUDE_ASM("asm/nonmatchings/P2/binoc", FUN_00134b48);

INCLUDE_ASM("asm/nonmatchings/P2/binoc", DrawBinocFilter);

INCLUDE_ASM("asm/nonmatchings/P2/binoc", FUN_00135550);

INCLUDE_ASM("asm/nonmatchings/P2/binoc", open_close_binoc);

INCLUDE_ASM("asm/nonmatchings/P2/binoc", FUN_001357f0);

INCLUDE_ASM("asm/nonmatchings/P2/binoc", FUN_00135858);

INCLUDE_ASM("asm/nonmatchings/P2/binoc", FUN_001358d0);

JUNK_ADDIU(30);
JUNK_WORD(0xE4C00000);

INCLUDE_ASM("asm/nonmatchings/P2/binoc", FUN_00135E30);

JUNK_ADDIU(A0);

INCLUDE_ASM("asm/nonmatchings/P2/binoc", FUN_00135E48);

JUNK_ADDIU(10);

INCLUDE_ASM("asm/nonmatchings/P2/binoc", SetBinocBfk);

INCLUDE_ASM("asm/nonmatchings/P2/binoc", FUN_00135f48);

INCLUDE_ASM("asm/nonmatchings/P2/binoc", FUN_00136040);

INCLUDE_ASM("asm/nonmatchings/P2/binoc", FUN_00136238);

INCLUDE_ASM("asm/nonmatchings/P2/binoc", FUN_001363d0);

INCLUDE_ASM("asm/nonmatchings/P2/binoc", SetBinocAchzDraw);

INCLUDE_ASM("asm/nonmatchings/P2/binoc", FDoneBinocAchz);

void SetBinocLookat(BINOC *binoc, ALO *paloLookat)
{
    binoc->paloLookat = paloLookat;
}

void SetBinocZoom(BINOC *binoc, float zoom)
{
    float cappedZoom = zoom * 0.01f;
    float one = 1.0f;
    float zero = 0.0f;
    if (cappedZoom < zero)
    {
        cappedZoom = zero;
    }
    else if (cappedZoom > one)
    {
        cappedZoom = one;
    }
    binoc->zoom = cappedZoom;
}

INCLUDE_ASM("asm/nonmatchings/P2/binoc", FUN_001365f0);

INCLUDE_ASM("asm/nonmatchings/P2/binoc", FUN_00136648);

INCLUDE_ASM("asm/nonmatchings/P2/binoc", DrawBinoc);

void GetBinocReticleFocus(BINOC *binoc, float *dxReticle, float *dyReticle)
{
    *dxReticle = binoc->dxReticle + 320.0f;
    *dyReticle = binoc->dyReticle + 180.40001f;
}

INCLUDE_ASM("asm/nonmatchings/P2/binoc", FUN_00136ef8);

INCLUDE_ASM("asm/nonmatchings/P2/binoc", FUN_00136fa8);

INCLUDE_ASM("asm/nonmatchings/P2/binoc", binoc__static_initialization_and_destruction_0);

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

void CTextBox::SetTextColor(RGBA *rgba)
{
    this->m_rgba = *rgba;
}

void CTextBox::SetHorizontalJust(JH jh)
{
    m_jh = jh;
}

void CTextBox::SetVerticalJust(JV jv)
{
    m_jv = jv;
}

INCLUDE_ASM("asm/nonmatchings/P2/binoc", _GLOBAL_$I$InitBei__FP3BEIP3CLQffi);
