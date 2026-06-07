#include <binoc.h>
#include <alo.h>
#include <clock.h>
#include <font.h>
#include <rip.h>
#include <vec.h>
#include <dialog.h>

void InitBei(BEI *pbei, CLQ *pclq, float duWidth, float dgHeight, int cseg)
{
    // Copy CLQ
    *(qword *)&pbei->clq = *(qword *)pclq;

    pbei->cseg = cseg;

    // Calculate segment count of half the notch
    float duSegWidth = 1.0f / cseg;
    float csegNotchWidth = duWidth / duSegWidth;
    int csegNotchHalf = (int)csegNotchWidth >> 1; // Simplifies to duWidth * cseg / 2

    pbei->csegNotchHalf = csegNotchHalf;

    // Calculate notch segment indices
    pbei->isegNotchMid = cseg / 2;
    pbei->isegNotchFirst = pbei->isegNotchMid - csegNotchHalf;
    pbei->isegNotchLast = pbei->isegNotchMid + csegNotchHalf;

    // Evaluate curve at notch edges and center
    pbei->gNotchEdge = GEvaluateClq(pclq, pbei->isegNotchFirst / pbei->cseg);
    pbei->gNotchCenter = GEvaluateClq(pclq, 0.5f) + dgHeight;
}

float GEvaluateBei(BEI *pbei, int iseg)
{
    // A more idiomatic structure would check if inside the notch first
    // and use the CLQ evaluation as the default return value.

    // Outside notch region
    if (iseg < pbei->isegNotchFirst || iseg > pbei->isegNotchLast)
    {
        // Evaluate quadratic curve
        float t = iseg / pbei->cseg;
        return GEvaluateClq(&pbei->clq, t);
    }

    // Notch edges
    if (iseg == pbei->isegNotchFirst || iseg == pbei->isegNotchLast)
    {
        // Return edge height
        return pbei->gNotchEdge;
    }

    // Left side of notch
    if (iseg < pbei->isegNotchMid)
    {
        // Interpolate between edge and center
        float t = (iseg - pbei->isegNotchFirst) / pbei->csegNotchHalf;
        return GLerp(pbei->gNotchEdge, pbei->gNotchCenter, t);
    }

    // Right side of notch
    if (iseg > pbei->isegNotchMid)
    {
        // Interpolate between center and edge
        float t = (iseg - pbei->isegNotchMid) / pbei->csegNotchHalf;
        return GLerp(pbei->gNotchCenter, pbei->gNotchEdge, t);
    }

    return pbei->gNotchCenter;
}

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
    SetBinocLookat(binoc, NULL);
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

extern "C" {
void FUN_00135E30(void *a0, void *a1, void *a2)
{
    STRUCT_OFFSET(a1, 0x0, qword) = STRUCT_OFFSET(a0, 0x140, qword);
    STRUCT_OFFSET(a2, 0x0, int) = 0;
}
}

JUNK_ADDIU(A0);

extern "C" {
int FUN_00135E48(void *param_1, int param_2, VECTOR *param_3)
{
    *(qword *)param_3 = *(qword *)((uint8_t *)param_1 + 0x140);
    return ChpBuildConvexHullScreen(param_3, 1, (HP *)param_3);
}
}

JUNK_ADDIU(10);

INCLUDE_ASM("asm/nonmatchings/P2/binoc", SetBinocBfk);

INCLUDE_ASM("asm/nonmatchings/P2/binoc", FUN_00135f48);

INCLUDE_ASM("asm/nonmatchings/P2/binoc", FUN_00136040);

INCLUDE_ASM("asm/nonmatchings/P2/binoc", FUN_00136238);

extern "C" {
void FUN_001363d0(BINOC *pbinoc)
{
    OnBlotReset(pbinoc);
    DIALOG *pdialog = STRUCT_OFFSET(pbinoc, 0x324, DIALOG *);
    if (pdialog)
        SetDialogDialogs(pdialog, DIALOGS_Disabled);
}
}

INCLUDE_ASM("asm/nonmatchings/P2/binoc", SetBinocAchzDraw);

bool FDoneBinocAchz(BINOC *pbinoc)
{
    if (pbinoc->achzDraw[0] == '\0')
    {
        return true;
    }

    CRichText rt(pbinoc->achzDraw, pbinoc->pfont);
    int cchTotal = rt.Cch();

    float tAchzDraw = g_clock.t - STRUCT_OFFSET(pbinoc, 0x268, float); // pbinoc->tAchzSet
    int cchDrawn = (int)(tAchzDraw * STRUCT_OFFSET(pbinoc, 0x2F0, float)); // pbinoc->svch

    return cchDrawn >= cchTotal;
}

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

extern "C" {
void open_close_binoc(BINOC *pbinoc, int state);

void FUN_00136fa8(BINOC *pbinoc)
{
    DIALOG *pdialog = STRUCT_OFFSET(pbinoc, 0x324, DIALOG *);
    if (pdialog)
        SetDialogDialogs(pdialog, DIALOGS_Calling);
    else
        open_close_binoc(pbinoc, 0);
}
}

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
