/**
 * @file cm.h
 *
 * @brief Game camera.
 */
#ifndef CM_H
#define CM_H

#include "common.h"
#include <lo.h>
#include <joy.h>
#include <util.h>
#include <cplcy.h>

typedef int GRFRCP;

/**
 * @brief Camera (?) kind?
 */
enum CMK
{
    CMK_Nil = -1,
    CMK_Translucent = 0,
    CMK_Fade = 1,
    CMK_Opaque = 2,
    CMK_Max = 3
};

/**
 * @brief Fog parameters.
 */
struct FGFN
{
    /* 0x00 */ float duFogBias;
    /* 0x04 */ float ruFog;
    /* 0x08 */ float sNearFog;
    /* 0x0c */ float duFogPlusClipBias;
};

/**
 * @class _CAMERA
 * @brief Base class for cameras.
 */
struct CM : public LO
{
    /* 0x040 */ VECTOR pos;
    /* 0x050 */ VECTOR4 anormalFrustrumTranspose[3];
    /* 0x080 */ MATRIX3 mat;
    /* 0x0b0 */ float rMRDAdjust;
    /* 0x0b4 */ STRUCT_PADDING(3);
    /* 0x0c0 */ MATRIX4 matProj;
    /* 0x100 */ MATRIX4 matWorldToClip;
    /* 0x140 */ MATRIX4 matClipToWorld;
    /* 0x180 */ VECTOR anormalFrustrum[4];
    /* 0x1c0 */ float rMRD;
    /* 0x1c4 */ float radFOV;
    /* 0x1c8 */ float radFOV2;
    /* 0x1cc */ int unk;
    /* 0x1d0 */ STRUCT_PADDING(4);
    /* 0x1e0 */ float rAspect;
    /* 0x1e4 */ float sNearClip;
    /* 0x1e8 */ float sFarClip;
    /* 0x1ec */ float sRadiusNearClip;
    /* 0x1f0 */ float xScreenRange;
    /* 0x1f4 */ float yScreenRange;
    /* 0x1f8 */ float sNearFog;
    /* 0x1fc */ float sFarFog;
    /* 0x200 */ float uFogMax;
    /* 0x204 */ RGBA rgbaFog;
    /* 0x208 */ FGFN fgfn;
    /* 0x218 */ float tJolt;
    /* 0x21c */ int grfzon;
    /* 0x220 */ int fCutNext;
    /* 0x224 */ int fCut;
    /* 0x228 */ int fRadCut;
    /* 0x22c */ float radCut;
    /* 0x230 */ VECTOR dposCenter;
    /* 0x240 */ VECTOR vCenter;
    /* 0x250 */ VECTOR dposAdjust;
    /* 0x260 */ VECTOR vAdjust;
    /* 0x270 */ VECTOR dposFocus;
    /* 0x280 */ VECTOR vFocus;
    /* 0x290 */ VECTOR posScreen; // TODO: Unused?
    /* 0x2a0 */ VECTOR vScreen; // TODO: Unused?
    /* 0x2b0 */ float swTiltPos;
    /* 0x2b4 */ float sv;
    /* 0x2b8 */ float swPanMat;
    /* 0x2bc */ float swPanPos;
    /* 0x2c0 */ float swTiltMat;
    /* 0x2c4 */ STRUCT_PADDING(3);
    /* 0x2d0 */ VECTOR posCenterPrev;
    /* 0x2e0 */ SO *psoFocusPrev;
    /* 0x2e4 */ STRUCT_PADDING(3);
    /* 0x2f0 */ CPDEFI cpdefiPrev;
    /* 0x340 */ int cpaloFade;
    /* 0x344 */ ALO *apaloFade[8];
    /* 0x364 */ float tActivateCplcy;
    /* 0x368 */ STRUCT_PADDING(2);
    /* 0x370 */ MATRIX3 matRotateToCam;
    /* 0x3a0 */ MATRIX3 matRotateTiltToCam;
    /* 0x3d0 */ int ccpr;
    /* 0x3d4 */ CPR acpr[8];
    /* 0x454 */ CPMAN cpman;
    /* 0x460 */ CPLOOK cplook;
    /* 0x4c0 */ CPALIGN cpalign;
    /* 0x510 */ CPASEG cpaseg;
    /* 0x520 */ CPTN cptn;
};

// extern CM g_cm; // Main game camera.
extern CM *g_pcm; // Pointer to the main game camera.

/**
 * @brief Starts up the camera system.
 */
void StartupCm();

/**
 * @brief Calculates adjustments on the given camera.
 * @todo Actually find out what this does.
 */
void CalcCmAdjust(CM *pcm, SO *psoFocus, CPDEFI *pcpdefi, VECTOR *pdpos);

/**
 * @brief Calls RecalcCmFrustrum on the given camera.
 */
void RecalcCmFrustrum(CM *pcm);

/**
 * @brief Sets fov on the global camera.
 */
void SetSwCameraFov(float fov);

/**
 * @brief Sets near clip plane on the global camera.
 */
void SetSwCameraNearClip(float sNearClip);

/**
 * @brief Sets far clip plane on the global camera.
 */
void SetSwCameraFarClip(float sFarClip);

/**
 * @brief Set the near fog distance (?) on the global camera.
 */
void SetSwCameraNearFog(float sNearFog);

/**
 * @brief Set the far fog distance (?) on the global camera.
 */
void SetSwCameraFarFog(float sFarFog);

/**
 * @brief Set the max fog distance (?) on the global camera.
 */
void SetSwCameraUFogMax(float uFogMax);

/**
 * @brief Sets Fog on the global camera.
 */
void SetSwCameraRgbaFog(SW *psw, RGBA *prgbaFog);

/**
 * @brief Sets the minimum render distance ratio (?) on the global camera.
 */
void SetSwCameraMrdRatio(float ratio);

/**
 * @brief Sets position on the given camera.
 */
void SetCmPos(CM *pcm, VECTOR *ppos);

/**
 * @brief Sets matrix on the given camera.
 */
void SetCmMat(CM *pcm, MATRIX3 *pmat);

/**
 * @brief Changes the FOV of the camera and then calls RecalcCmFrustrum.
 */
void SetCmFov(CM *pcm, float fov);

/**
 * @brief Sets near clip plane on the given camera.
 */
void SetCmNearClip(CM *pcm, float sNearClip);

/**
 * @brief Sets far clip plane on the given camera.
 */
void SetCmFarClip(CM *pcm, float sFarClip);

/**
 * @brief Set the near fog distance (?) on the given camera.
 */
void SetCmNearFog(CM *pcm, float sNearFog);

/**
 * @brief Set the far fog distance (?) on the given camera.
 */
void SetCmFarFog(CM *pcm, float sFarFog);

/**
 * @brief Set the maximum fog distance (?) on the given camera.
 */
void SetCmUFogMax(CM *pcm, float uFogMax);

/**
 * @brief Sets the RGBA fog color for the camera.
 */
void SetCmRgbaFog(CM *pcm, RGBA *prgbaFog);

/**
 * @brief Sets the minimum render distance ratio (?) on the given camera.
 */
void SetCmMrdRatio(CM *pcm, float ratio);

/**
 * @brief Clears fading objects from the given camera.
 */
void ClearCmFadeObjects(CM *pcm);

/**
 * @brief Adds a fading objects to the list of the given camera.
 */
void AddCmFadeObject(CM *pcm, ALO *palo);

/**
 * @brief Sets up the given camera.
 */
void SetupCm(CM *pcm);

/**
 * @brief TODO.
 */
void DrawCm(CM *pcm);

/**
 * @brief Sets the position matrix on the given camera.
 */
void SetCmPosMat(CM *pcm, VECTOR *ppos, MATRIX3 *pmat);

void AdjustCmJoy(CM *pcm, JOY *pjoy, JOYID joyid, float *prad);

void SetCmPolicy(CM *pcm, CPP cpp, CPLCY *pcplcy, SO *psoFocus, void *pv);

void RevokeCmPolicy(CM *pcm, GRFRCP grfrcp, CPP cpp, CPLCY *pcplcy, SO *psoFocus, void *pv);

/**
 * @brief Sets Cut on the given camera.
 */
void SetCmCut(CM *pcm, float *pradCut);

/**
 * @brief Enable the next cut on the given camera.
 */
void EnableCmNextCut(CM *pcm);

/**
 * @brief Clears cut from the given camera.
 */
void ClearCmCut(CM *pcm);

/**
 * @brief Push lookk on the given camera.
 */
void PushLookkCm(CM *pcm, LOOKK lookk);

/**
 * @brief Pop the top most look kind of the given camera.
 */
LOOKK LookkPopCm(CM *pcm);

/**
 * @brief Get the current look kind of the given camera.
 */
LOOKK LookkCurCm(CM *pcm);

/**
 * @brief Sets sniper focus on the given camera.
 */
void SetCmSniperFocus(CM *pcm, PNT *ppntAnchor, float sRadiusSniper, float rScreenSniper);

/**
 * @brief Jolt the given camera.
 */
void JoltCm(CM *pcm);

// todo fix undefined reference errors
// extern VECTOR4 g_posEyeDefault;
// extern VECTOR4 g_posCenterDefault;
// extern float g_sNearFog;
// extern float g_sFarFog;
// extern float g_uFogMax;
// extern RGBA g_rgbaFog;
extern int g_rgbaFog; //Just to get the code matching -Kestin
// extern VECTOR4 D_2618b8;
// extern float DT_CmJoltMax;
// extern float SW_CmJolt;
// extern CLQ s_clqUToUJolt;
// extern VECTOR4 s_dposJolt;
// extern VECTOR4 s_rotJolt;
// extern VECTOR4 s_vecRange;
// extern VECTOR4 s_vecOffset;
// extern float R_SetCmSpring;
// extern float R_SetCmDamping;
// extern float D_00261928[9];
// extern float D_0026194c;
// extern float D_00261950;
// extern SMP s_smpSquishEye;
// extern float D_00261970;
// extern float D_00261974;
// extern float D_00261978;
// extern float D_0026197c;
// extern float D_00261980;
// extern float D_00261984;
// extern float D_00261988;
// extern float D_0026198c;
// extern CM* g_pcm;

#endif // CM_H
