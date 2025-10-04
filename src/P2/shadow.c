#include <shadow.h>
#include <shd.h>
#include <gcc/math.h>

INCLUDE_ASM("asm/nonmatchings/P2/shadow", InitShadow__FP6SHADOW);

INCLUDE_ASM("asm/nonmatchings/P2/shadow", PostShadowLoad__FP6SHADOW);

void InvalidateShadowVifs(SHADOW *pshadow)
{
    pshadow->cqwVifs = 0;
}

INCLUDE_ASM("asm/nonmatchings/P2/shadow", RebuildShadowRegion__FP6SHADOW);

void SetShadowShader(SHADOW *pshadow, OID oidShdShadow)
{
    OID oid = (oidShdShadow != OID_Nil) ? oidShdShadow : OID_shd_stock_shadow;
    pshadow->pshd = PshdFindShader(oid);
    if (pshadow->pshd)
    {
        InvalidateShadowVifs(pshadow);
    }
}

int FShadowRadiusSet(SHADOW *pshadow)
{
    return (pshadow->sNearRadius >= 0.0f && pshadow->sFarRadius >= 0.0f);
}

void SetShadowNearRadius(SHADOW *pshadow, float sNearRadius)
{
    pshadow->sNearRadius = sNearRadius;
    if (pshadow->sFarRadius < 0.0f)
    {
        pshadow->sFarRadius = sNearRadius;
    }

    InvalidateShadowVifs(pshadow);
}

void SetShadowFarRadius(SHADOW *pshadow, float sFarRadius)
{
    pshadow->sFarRadius = sFarRadius;
    if (pshadow->sNearRadius < 0.0f)
    {
        pshadow->sNearRadius = sFarRadius;
    }

    InvalidateShadowVifs(pshadow);
}

INCLUDE_ASM("asm/nonmatchings/P2/shadow", SetShadowCastPosition__FP6SHADOWP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/shadow", SetShadowCastNormal__FP6SHADOWP6VECTOR);

void SetShadowNearCast(SHADOW *pshadow, float sNearCast)
{
    pshadow->sNearCast = sNearCast;
    RebuildShadowRegion(pshadow);
    InvalidateShadowVifs(pshadow);
}

void SetShadowFarCast(SHADOW *pshadow, float sFarCast)
{
    pshadow->sFarCast = sFarCast;
    RebuildShadowRegion(pshadow);
    InvalidateShadowVifs(pshadow);
}

void SetShadowConeAngle(SHADOW *pshadow, float degConeAngle)
{
    float fAngleTan = tanf(degConeAngle * 0.008726647f);
    pshadow->sNearRadius = fAngleTan * pshadow->sNearCast;
    pshadow->sFarRadius = fAngleTan * pshadow->sFarCast;
    InvalidateShadowVifs(pshadow);
}

INCLUDE_ASM("asm/nonmatchings/P2/shadow", SetShadowFrustrumUp__FP6SHADOWP6VECTOR);

INCLUDE_ASM("asm/nonmatchings/P2/shadow", FShadowValid__FP6SHADOWi);

INCLUDE_ASM("asm/nonmatchings/P2/shadow", FFilterFastShadows__FPvP2SO);

INCLUDE_ASM("asm/nonmatchings/P2/shadow", UpdateShadow__FP6SHADOWf);

INCLUDE_ASM("asm/nonmatchings/P2/shadow", RebuildShadowVifs__FP6SHADOW);

INCLUDE_ASM("asm/nonmatchings/P2/shadow", DrawShadow__FP6SHADOW);

INCLUDE_ASM("asm/nonmatchings/P2/shadow", FShadowIntersectsSphere__FP6SHADOWP6VECTORf);

INCLUDE_ASM("asm/nonmatchings/P2/shadow", FindSwShadows__FP2SWP6VECTORfiPiPP6SHADOW);
