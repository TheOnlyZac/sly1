#include <shadow.h>

INCLUDE_ASM(const s32, "P2/shadow", InitShadow__FP6SHADOW);

INCLUDE_ASM(const s32, "P2/shadow", PostShadowLoad__FP6SHADOW);

INCLUDE_ASM(const s32, "P2/shadow", InvalidateShadowVifs__FP6SHADOW);

INCLUDE_ASM(const s32, "P2/shadow", RebuildShadowRegion__FP6SHADOW);

INCLUDE_ASM(const s32, "P2/shadow", SetShadowShader__FP6SHADOW3OID);

INCLUDE_ASM(const s32, "P2/shadow", FShadowRadiusSet__FP6SHADOW);

INCLUDE_ASM(const s32, "P2/shadow", SetShadowNearRadius__FP6SHADOWf);

INCLUDE_ASM(const s32, "P2/shadow", SetShadowFarRadius__FP6SHADOWf);

INCLUDE_ASM(const s32, "P2/shadow", SetShadowCastPosition__FP6SHADOWP6VECTOR);

INCLUDE_ASM(const s32, "P2/shadow", SetShadowCastNormal__FP6SHADOWP6VECTOR);

INCLUDE_ASM(const s32, "P2/shadow", SetShadowNearCast__FP6SHADOWf);

INCLUDE_ASM(const s32, "P2/shadow", SetShadowFarCast__FP6SHADOWf);

INCLUDE_ASM(const s32, "P2/shadow", SetShadowConeAngle__FP6SHADOWf);

INCLUDE_ASM(const s32, "P2/shadow", SetShadowFrustrumUp__FP6SHADOWP6VECTOR);

INCLUDE_ASM(const s32, "P2/shadow", FShadowValid__FP6SHADOWi);

INCLUDE_ASM(const s32, "P2/shadow", FFilterFastShadows__FPvP2SO);

INCLUDE_ASM(const s32, "P2/shadow", UpdateShadow__FP6SHADOWf);

INCLUDE_ASM(const s32, "P2/shadow", RebuildShadowVifs__FP6SHADOW);

INCLUDE_ASM(const s32, "P2/shadow", DrawShadow__FP6SHADOW);

INCLUDE_ASM(const s32, "P2/shadow", FShadowIntersectsSphere__FP6SHADOWP6VECTORf);

INCLUDE_ASM(const s32, "P2/shadow", FindSwShadows__FP2SWP6VECTORfiPiPP6SHADOW);
