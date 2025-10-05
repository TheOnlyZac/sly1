/**
 * @file light.h
 *
 * @brief Light and shadow system.
 */
#ifndef LIGHT_H
#define LIGHT_H

#include "common.h"
#include <alo.h>
#include <util.h>

// Forward.
struct SW;

/**
 * @brief Unknown.
 */
enum TWPS
{
    TWPS_Shadow = 0,
    TWPS_ShadowMidtone = 1,
    TWPS_ShadowMidtoneSaturate = 2
};

/**
 * @brief Light kind.
 */
enum LIGHTK
{
    LIGHTK_Nil = -1,
    LIGHTK_Direction = 0,
    LIGHTK_Position = 1,
    LIGHTK_Frustrum = 2,
    LIGHTK_Spot = 3,
    LIGHTK_Max = 4
};

/**
 * @brief Light shadow & midtone.
 */
struct LSM
{
    float uShadow;
    float uMidtone;
};

/**
 * @brief Light.
 * @todo Implement the struct.
 */
struct LIGHT : public ALO
{
    // ...
    /* 0x2e0 */ VECTOR vecHighlight;
    /* 0x2f0 */ float gMidtone;
    /* 0x2f4 */ float gShadow;
    /* 0x2f8 */ float degHighlight;
    /* 0x2fc */ float degMidtone;
    /* 0x300 */ float degShadow;
    /* 0x304 */ int fDynamic;
    STRUCT_PADDING(13);
    /* 0x338 */ float degCone;
    /* 0x33c */ float degHotSpot;
    // ...
};

/**
 * @brief Initializes a light.
 *
 * @param plight Pointer to a light.
 */
void InitLight(LIGHT *plight);

/**
 * @brief TODO.
 */
void UpdateLightXfWorldHierarchy(LIGHT *plight);

/**
 * @brief Removes a light from the SW.
 *
 * @param plight Pointer to a light.
 */
void RemoveLightFromSw(LIGHT *plight);

/**
 * @brief Adds a light to the SW.
 *
 * @param plight Pointer to a light.
 */
void AddLightToSw(LIGHT *plight);

/**
 * @brief Adds a light.
 *
 * @param plight Pointer to a light.
 */
void OnLightAdd(LIGHT *plight);

/**
 * @brief Removes a light.
 *
 * @param plight Pointer to a light.
 */
void OnLightRemove(LIGHT *plight);

/**
 * @brief Clones a light.
 *
 * @param plight Pointer to a light.
 * @param plight Pointer to the light to clone.
 */
void CloneLight(LIGHT *plight, LIGHT *plightBase);

void FitLinearFunction(float x0, float y0, float x1, float y1, float *pdu, float *pru);

void FitRecipFunction(float x0, float y0, float x1, float y1, float *pdu, float *pru);

void ConvertFallOff(LM *plm, float *pdu, float *pru);

void ConvertAngleStrength(float deg0, float g0, float deg1, float g1, float *pdu, float *pru);

void InvalidateLight(LIGHT *plight);

void RebuildLightVifs(LIGHT *plight);

void SetLightKind(LIGHT *plight, LIGHTK lightk);

void SetLightHighlightColor(LIGHT *plight, VECTOR *pvecHighlight);

void SetLightMidtoneStrength(LIGHT *plight, float gMidtone);

void SetLightShadowStrength(LIGHT *plight, float gShadow);

void SetLightHighlightAngle(LIGHT *plight, float degHighlight);

void SetLightMidtoneAngle(LIGHT *plight, float degMidtone);

void SetLightShadowAngle(LIGHT *plight, float degShadow);

void SetLightDirection(LIGHT *plight, VECTOR *pvecDirection);

void SetLightDynamic(LIGHT *plight, int fDynamic);

void SetLightFallOff(LIGHT *plight, LM *plm);

void SetLightConeAngle(LIGHT *plight, float degCone);

void SetLightHotSpotAngle(LIGHT *plight, float degHotSpot);

void SetLightFrustrumUp(LIGHT *plight, VECTOR *pvecUpLocal);

void RebuildLightFrustrum(LIGHT *plight);

void UpdateLightBeamGrfzon(LIGHT *plight);

void SetLightDiffuse_Old(LIGHT *plight, float gDiffuse);

void GetLightDiffuse_Old(LIGHT *plight, float *pgDiffuse);

void SetLightSaturate_Old(LIGHT *plight, VECTOR *pvecSaturate);

void GetLightSaturate_Old(LIGHT *plight, VECTOR *pvecSaturate);

int NCmpFindLight(LIGHT **pplight1, LIGHT **pplight2);

void PrepareSwLightsForDraw(SW *psw);

TWPS TwpsFindSwLights(SW *psw, VECTOR *ppos, float sRadius, int grffindlight, int cplightMax, int *pcplightStatic, int *pcplightAll, LIGHT **aplight);

#endif // LIGHT_H
