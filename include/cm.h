/**
 * @file cm.h
 *
 * @brief Game camera.
 */
#ifndef CM_H
#define CM_H

#include "common.h"
#include <lo.h>
#include <util.h>
#include <binoc.h> // only for RGBA
#include <xform.h>
#include <sound.h>
#include <clock.h>

struct CM; // Forward declaration

/**
 * @brief Unknown Kind.
 */
enum CFK
{
    CFK_Nil = -1,
    CFK_Behind = 0,
    CFK_Side = 1,
    CFK_Max = 2
};

/**
 * @brief Unknown, may be wrong.
 */
enum CPP
{
    CPP_Nil = -1,
    CPP_Base = 0,
    CPP_Default = 1,
    CPP_Tunnel_Pri0 = 2,
    CPP_Tunnel_Pri1 = 3,
    CPP_Tunnel_Pri2 = 4,
    CPP_Tunnel_Pri3 = 5,
    CPP_LookAround = 6,
    CPP_Animated = 7,
    CPP_ManualOverride = 8,
    CPP_UserTestWalkthrough = 9,
    CPP_Max = 10
};

/**
 * @brief Unknown.
 */
enum CPMT
{
    CPMT_Truck = 0,
    CPMT_Pan = 1,
    CPMT_Slide = 2,
    CPMT_Orbit = 3,
    CPMT_Align = 4,
    CPMT_Walkthrough = 5,
    CPMT_Max = 6
};

/**
 * @brief Look kind.
 */
enum LOOKK
{
    LOOKK_Nil = -1,
    LOOKK_User = 0,
    LOOKK_Sniper = 1,
    LOOKK_Dialog = 2,
    LOOKK_Confront = 3,
    LOOKK_Max = 4
};

/**
 * @brief Unknown.
 */
enum FTND
{
    FTND_Nil = -1,
    FTND_Forward = 1,
    FTND_Reverse = 2,
    FTND_Manual = 4,
    FTND_Max = 5
};

/**
 * @brief Fog parameters.
 */
struct FGFN
{
    float duFogBias;
    float ruFog;
    float sNearFog;
    float duFogPlusClipBias;
};

/**
 * @brief Unknown.
 */
struct CPDEFI
{
    int grfcpd;
    undefined4 field1_0x4;
    undefined4 field2_0x8;
    undefined4 field3_0xc;
    VECTOR posBase;
    VECTOR vBase;
    float radHome;
    float sAdjust;
    float tMoveLast;
    CFK cfk;
    VECTOR posAdjust;
};

/**
 * @brief Unknown.
 *
 * @todo Implement.
 */
struct TN : public ALO
{
    // ...
};

/**
 * @brief Camera policy.
 */
struct CPLCY
{
    undefined4 vtable; // TODO: implement methods on this struct
    CM *pcm;
};

/**
 * @brief Camera policy: manual.
 *
 * Normal orbit camera.
 */
struct CPMAN : public CPLCY
{
    CPMT cpmt;
    ALO *paloOrbit;
    int cframeStatus;
};

/**
 * @brief Camera policy: look.
 *
 * Used for binoc-u-com, and probably sniper mode.
 */
struct CPLOOK : public CPLCY
{
    float radPan;
    float swPan;
    float radTilt;
    float swTilt;
    float uZoom;
    float svuZoom;
    float rZoomMax;
    LM lmFOV;
    LOOKK alookk[4];
    int clookk;
    int fSoundPaused;
    AMB *pambBinoc;
    AMB *pambAmbient;
    ALO *paloFocusSniper;
    PNT *ppntAnchor;
    float sRadiusSniper;
    float rScreenSniper;
};

/**
 * @brief Camera policy: align
 *
 * Unknown usage.
 */
struct CPALIGN : public CPLCY
{
    undefined4 field_1_0x0;
    undefined4 field_2_0x4;
    VECTOR posLocal;
    undefined4 field_4_0xc;
    undefined4 field_5_0x10;
    undefined4 field_6_0x14;
    float field_7_0x18;
    float field_8_0x1c;
};

/**
 * @brief Camera policy: animation segment(?)
 *
 * Unknown usage.
 */
struct CPASEG : public CPLCY
{
    CAMERA *pcamera;
};

/**
 * @brief Camera policy: tunnel.
 *
 * Unknown usage.
 *
 * @note Might be unused in release build, based on the name.
 */
struct CPTN : public CPLCY
{
    TN *ptn;
    float radManual;
    float xyManual;
    float zManual;
    int fHome;
    float radHome;
    FTND ftnd;
    int fActivate;
    int fPanOnEntryDone;
    float swOrbit;
    float tLastOrbit;
    float radCur;
    float radFwdPrev;
    float radRevPrev;
    float tMoveLast;
    float uFollowCur;
    float vxy;
    float vz;
    VECTOR posEyePrev;
};

/**
 * @brief Camera something.
 */
struct CPR
{
    CPP cpp;
    CPLCY *pcplcy;
    SO *psoFocus;
    void *pv;
};

/**
 * @brief Game camera.
 */
struct CM : public LO
{
    VECTOR pos;
    VECTOR4 anormalFrustrumTranspose[3];
    MATRIX3 mat;
    float rMRDAdjust;
    undefined4 field5_0x98;
    undefined4 field6_0x9c;
    undefined4 field7_0xa0;
    MATRIX4 matProj;
    MATRIX4 matWorldToClip;
    MATRIX4 matClipToWorld;
    VECTOR anormalFrustrum[4];
    float rMRD;
    float radFOV;
    float rAspect;
    float sRadiusNearClip;
    float xScreenRange;
    float yScreenRange;
    float sNearFog;
    float sFarFog;
    float uFogMax;
    RGBA rgbaFog;
    FGFN fgfn;
    float tJolt;
    int grfzon;
    int fCutNext;
    int fCut;
    int fRadCut;
    float radCut;
    float sNearClip;
    float sFarClip;
    int fDisplaced;
    float uPanProgress;
    float uTiltProgress;
    float uSProgress;
    float field35_0x1fc;
    float field36_0x200;
    VECTOR dposCenter;
    VECTOR vCenter; //NOTE: this might not be a VECTOR... -Kestin
    undefined4 field39_0x21c;
    bool reset_flag;
    int field41_0x224;
    int field42_0x228;
    float field43_0x22c;
    undefined4 field44_0x230;
    //VECTOR vAdjust;
    VECTOR dposFocus;
    VECTOR vFocus;
    VECTOR posScreen;
    VECTOR vScreen;
    float swPanPos;
    float swTiltPos;
    float sv;
    float swPanMat;
    float swTiltMat;
    undefined4 field52_0x278;
    undefined4 field53_0x27c;
    undefined4 field54_0x280;
    VECTOR posCenterPrev;
    VECTOR posClear;
    MATRIX3 matClear;
    SO *psoFocusPrev;
    undefined4 field59_0x2c4;
    undefined4 field60_0x2c8;
    undefined4 field61_0x2cc;
    CPDEFI cpdefiPrev;
    int cpaloFade;
    ALO *apaloFade[8];
    float tActivateCplcy;
    undefined4 field66_0x33c;
    undefined4 field67_0x340;
    MATRIX3 matRotateToCam;
    MATRIX3 matRotateTiltToCam;
    int ccpr;
    CPR acpr[8];
    CPMAN cpman;
    undefined8 field73_0x428;
    undefined8 field74_0x430;
    undefined8 field75_0x438;
    undefined8 field76_0x440;
    undefined8 field77_0x448;
    undefined8 field78_0x450;
    undefined8 field79_0x458;
    CPLOOK cplook;
    CPALIGN cpalign;
    CPASEG cpaseg;
    CPTN cptn;
};

// extern CM g_cm; // Main game camera
extern CM *g_pcm; // Pointer to the main game camera

/**
 * @brief Calls RecalcCmFrustrum on the given camera.
 */
void RecalcCmFrustrum(CM *pcm);

/**
 * @brief Sets far clip plane on the global camera.
 */
void SetSwCameraFarClip(float sFarClip);

/**
 * @brief Sets Fog on the global camera.
 */
void SetSwCameraRgbaFog(SW *psw, RGBA *prgbaFog);

/**
 * @brief Sets position on the given camera.
 */
void SetCmPos(CM *pcm,VECTOR *ppos);

/**
 * @brief Sets matrix on the given camera.
 */
void SetCmMat(CM *pcm, MATRIX3 *pmat);

/**
 * @brief Sets near clip plane on the given camera.
 */
void SetCmNearClip(CM *pcm, float sNearClip);

/**
 * @brief Sets far clip plane on the given camera.
 */
void SetCmFarClip(CM *pcm, float sFarClip);

/**
 * @brief Sets SProgress on the given camera.
 */
void SetCmSProgress(CM *pcm, float uSProgress);

/**
 * @brief Changes the FOV of the camera and then calls RecalcCmFrustrum.
 */
void SetCmFov(float fov, CM *pcm);

/**
 * @brief Sets field35_0x1fc on the given camera.
 */
void FUN_001439c8(CM *pcm, float param_2); //TODO: Rename function

/**
 * @brief Sets field36_0x200 on the given camera.
 */
void FUN_001439e8(CM *pcm,float param_2); //TODO: Rename function

/**
 * @brief Sets the RGBA fog color for the camera.
 */
void SetCmRgbaFog(CM *pcm, RGBA *prgbaFog);

/**
 * @brief Calls SetCmMrdRatio on the given camera.
 */
void SetCmMrdRatio(CM *pcm);

/**
 * @brief Clears fading objects from the given camera.
 */
void ClearCmFadeObjects(CM *pcm);

/**
 * @brief Sets up the given camera.
 */
void SetupCm(CM *pcm);

/**
 * @brief Sets the position matrix on the given camera.
 */
void SetCmPosMat(CM *pcm,VECTOR *ppos,MATRIX3 *pmat);

/**
 * @brief Sets Cut on the given camera.
 */
void SetCmCut(CM *pcm, float cut[]);

/**
 * @brief Sets the reset flag on the given camera.
 */
void SetResetFlag(CM *pcm);

/**
 * @brief Clears cut from the given camera.
 */
void ClearCmCut(CM *pcm);

/**
 * @brief Push lookk on the given camera.
 */
void PushLookkCm(CM *pcm, LOOKK lookk);

/**
 * @brief Calls LookkPopCm on the given camera.
 */
LOOKK LookkPopCm(CM *pcm);

/**
 * @brief Calls LookkCurCm on the given camera.
 */
LOOKK LookkCurCm(CM *pcm);

/**
 * @brief Sets sniper focus on the given camera.
 */
void SetCmSniperFocus(CM *pcm, PNT *ppntAnchor, float sRadiusSniper, float rScreenSniper);

/**
 * @brief Calls FUN_00146028 on the given camera.
 */
void FUN_00146028(CM *pcm); //TODO: Rename function

/**
 * @brief Initializes Camera.
 */
void cm__static_initialization_and_destruction_0(int __initialize_p,int __priority);

/**
 * @brief Startsup Camera.
 */
void _GLOBAL_$I$StartupCm();

// todo fix undefined reference errors
// extern VECTOR4 g_posEyeDefault;
// extern VECTOR4 g_posCenterDefault;
// extern float g_sNearFog;
// extern float g_sFarFog;
// extern float g_uFogMax;
// extern RGBA g_rgbaFog;
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
