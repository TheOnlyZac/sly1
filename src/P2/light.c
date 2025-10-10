#include <light.h>
#include <gcc/math.h>
#include <shd.h>
#include <frm.h>
#include <sw.h>

INCLUDE_ASM("asm/nonmatchings/P2/light", InitLight__FP5LIGHT);

void UpdateLightXfWorldHierarchy(LIGHT *plight)
{
    UpdateAloXfWorldHierarchy(plight);
    RebuildLightVifs(plight);
    UpdateLightBeamGrfzon(plight);
}

void RemoveLightFromSw(LIGHT *plight)
{
    RemoveDlEntry(&plight->psw->dlLight, plight);
    InvalidateLight(plight);
}

INCLUDE_ASM("asm/nonmatchings/P2/light", AddLightToSw__FP5LIGHT);

void OnLightAdd(LIGHT *plight)
{
    OnAloAdd(plight);
    AddLightToSw(plight);
}

void OnLightRemove(LIGHT *plight)
{
    OnAloRemove(plight);
    RemoveLightFromSw(plight);
}

INCLUDE_ASM("asm/nonmatchings/P2/light", CloneLight__FP5LIGHTT0);

void FitLinearFunction(float x0, float y0, float x1, float y1, float *pdu, float *pru)
{
    if (FFloatsNear(x0, x1, 0.0001f))
    {
        *pru = 0.0f;
        *pdu = y0;
        return;
    }

    float a = (y1 - y0) / (x1 - x0);
    *pru = a;
    *pdu = y0 - a * x0;
}

INCLUDE_ASM("asm/nonmatchings/P2/light", FitRecipFunction__FffffPfT4);

void ConvertFallOff(LM *plm, float *pdu, float *pru)
{
    FitLinearFunction(plm->gMin, 1.0f, plm->gMax, 0.0f, pdu, pru);
}

void ConvertAngleStrength(float deg0, float g0, float deg1, float g1, float *pdu, float *pru)
{
    // NOTE: The constant kDegToHalfRad is (3.1415926f / 180.0f) * 0.5f
    // Putting that here doesn't yield the same output due to precision loss.
    const float kDegToHalfRad = 0.008726647f;
    const float kStrengthScale = 1.0f / 255.0f;

    float strength0 = cosf(deg0 * kDegToHalfRad);
    strength0 += strength0 * strength0 * strength0;

    float strength1 = cosf(deg1 * kDegToHalfRad);
    strength1 += strength1 * strength1 * strength1;

    FitLinearFunction(strength0, g0 * kStrengthScale, strength1, g1 * kStrengthScale, pdu, pru);
}

void InvalidateLight(LIGHT *plight)
{
    if (STRUCT_OFFSET(plight, 0x304, int) == 0) // plight->fDynamic
    {
        g_cframeStaticLightsInvalid = g_cframe;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/light", RebuildLightVifs__FP5LIGHT);

INCLUDE_ASM("asm/nonmatchings/P2/light", SetLightKind__FP5LIGHT6LIGHTK);

INCLUDE_ASM("asm/nonmatchings/P2/light", SetLightHighlightColor__FP5LIGHTP6VECTOR);

void SetLightMidtoneStrength(LIGHT *plight, float gMidtone)
{
    STRUCT_OFFSET(plight, 0x2f0, float) = gMidtone; // plight->gMidtone
    RebuildLightVifs(plight);
}

void SetLightShadowStrength(LIGHT *plight, float gShadow)
{
    STRUCT_OFFSET(plight, 0x2f4, float) = gShadow; // plight->gShadow
    RebuildLightVifs(plight);
}

void SetLightHighlightAngle(LIGHT *plight, float degHighlight)
{
    STRUCT_OFFSET(plight, 0x2f8, float) = degHighlight; // plight->degHighlight
    RebuildLightVifs(plight);
}

void SetLightMidtoneAngle(LIGHT *plight, float degMidtone)
{
    STRUCT_OFFSET(plight, 0x2fc, float) = degMidtone; // plight->degMidtone
    RebuildLightVifs(plight);
}

void SetLightShadowAngle(LIGHT *plight, float degShadow)
{
    STRUCT_OFFSET(plight, 0x300, float) = degShadow; // plight->degShadow
    RebuildLightVifs(plight);
}

INCLUDE_ASM("asm/nonmatchings/P2/light", SetLightDirection__FP5LIGHTP6VECTOR);

void SetLightDynamic(LIGHT *plight, int fDynamic)
{
    if (fDynamic != STRUCT_OFFSET(plight, 0x304, int)) // plight->fDynamic
    {
        STRUCT_OFFSET(plight, 0x304, int) = fDynamic; // plight->fDynamic
        RebuildLightVifs(plight);
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/light", SetLightFallOff__FP5LIGHTP2LM);

void SetLightConeAngle(LIGHT *plight, float degCone)
{
    STRUCT_OFFSET(plight, 0x338, float) = degCone; // plight->degCone
    RebuildLightFrustrum(plight);
    RebuildLightVifs(plight);
    UpdateLightBeamGrfzon(plight);
}

void SetLightHotSpotAngle(LIGHT *plight, float degHotSpot)
{
    STRUCT_OFFSET(plight, 0x33c, float) = degHotSpot; // plight->degHotSpot
    RebuildLightFrustrum(plight);
    RebuildLightVifs(plight);
}

INCLUDE_ASM("asm/nonmatchings/P2/light", SetLightFrustrumUp__FP5LIGHTP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/light", RebuildLightFrustrum__FP5LIGHT);

INCLUDE_ASM("asm/nonmatchings/P2/light", UpdateLightBeamGrfzon__FP5LIGHT);

void SetLightDiffuse_Old(LIGHT *plight, float gDiffuse)
{
    SetLightMidtoneStrength(plight, gDiffuse);
    SetLightShadowStrength(plight, gDiffuse);
}

void GetLightDiffuse_Old(LIGHT *plight, float *pgDiffuse)
{
    *pgDiffuse = STRUCT_OFFSET(plight, 0x2f0, float); // plight->gMidtone
}

void SetLightSaturate_Old(LIGHT *plight, VECTOR *pvecSaturate)
{
    VECTOR vecHsv;
    ConvertUserRgbToUserHsv(pvecSaturate, &vecHsv);
    SetLightHighlightColor(plight, &vecHsv);
}

void GetLightSaturate_Old(LIGHT *plight, VECTOR *pvecSaturate)
{
    ConvertUserHsvToUserRgb(&STRUCT_OFFSET(plight, 0x2e0, VECTOR), pvecSaturate); // plight->vecHighlight
}

INCLUDE_ASM("asm/nonmatchings/P2/light", NCmpFindLight__FPP5LIGHTT0);

INCLUDE_ASM("asm/nonmatchings/P2/light", PrepareSwLightsForDraw__FP2SW);

INCLUDE_ASM("asm/nonmatchings/P2/light", TwpsFindSwLights__FP2SWP6VECTORfiiPiT5PP5LIGHT);
