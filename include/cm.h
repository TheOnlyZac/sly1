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
    float rScreenSniper;
    float sRadiusSniper;
    PNT *ppntAnchor;
};

/**
 * @brief Camera policy: align
 *
 * Unknown usage.
 */
struct CPALIGN : public CPLCY
{
    undefined4 fielf_1_0x0;
    undefined4 field_2_0x4;
    VECTOR posLocal;
    MATRIX3 matLocal;
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
    undefined4 field17_0xb4;
    undefined4 field18_0xb8;
    undefined4 field19_0xbc;
    MATRIX4 matProj;
    MATRIX4 matWorldToClip;
    MATRIX4 matClipToWorld;
    VECTOR anormalFrustrum[4];
    float rMRD;
    float radFOV;
    float rAspect;
    float sNearClip;
    float sFarClip;
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
    int fDisplaced;
    float uPanProgress;
    float uTiltProgress;
    float uSProgress;
    undefined4 field47_0x228;
    undefined4 field48_0x22c;
    VECTOR dposCenter;
    VECTOR vCenter;
    VECTOR dposAdjust;
    VECTOR vAdjust;
    VECTOR dposFocus;
    VECTOR vFocus;
    VECTOR posScreen;
    VECTOR vScreen;
    float swPanPos;
    float swTiltPos;
    float sv;
    float swPanMat;
    float swTiltMat;
    undefined4 field62_0x2c4;
    undefined4 field63_0x2c8;
    undefined4 field64_0x2cc;
    VECTOR posCenterPrev;
    VECTOR posClear;
    MATRIX3 matClear;
    SO *psoFocusPrev;
    undefined4 field69_0x324;
    undefined4 field70_0x328;
    undefined4 field71_0x32c;
    CPDEFI cpdefiPrev;
    int cpaloFade;
    ALO *apaloFade[8];
    float tActivateCplcy;
    undefined4 field76_0x3a8;
    undefined4 field77_0x3ac;
    MATRIX3 matRotateToCam;
    MATRIX3 matRotateTiltToCam;
    int ccpr;
    CPR acpr[8];
    CPMAN cpman;
    CPLOOK cplook;
    undefined4 field84_0x504;
    undefined4 field85_0x508;
    undefined4 field86_0x50c;
    CPALIGN cpalign;
    CPASEG cpaseg;
    undefined4 field89_0x56c;
    CPTN cptn;
};

extern CM *g_pcm;

/**
 * @brief Calls SetCmRgbaFog with the global camera.
 */
void SetSwCameraRgbaFog(SW *psw, RGBA *prgbaFog);

/**
 * @brief Sets the RGBA fog color for the camera.
 */
void SetCmRgbaFog(CM *pcm, RGBA *prgbaFog);

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
