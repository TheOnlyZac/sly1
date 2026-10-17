/**
 * @file cplcy.h
 *
 * @brief Camera policy.
 */
#ifndef CPLCY_H
#define CPLCY_H

#include "common.h"
#include <vec.h>
#include <util.h>

// Forward declarations.
struct TN;
struct CM;
struct ALO;
struct AMB;
struct PNT;
struct CAMERA;

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
 * @todo Move to tn.h?
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
    /* 0x30 */ float radHome;
    /* 0x34 */ float sAdjust;
    float tMoveLast;
    CFK cfk;
    VECTOR posAdjust;
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
    // ALO *paloOrbit; // TODO: Likely doesn't exist.
    // int cframeStatus; // TODO: Likely doesn't exist.
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
 * @brief Camera policy: (?).
 */
struct CPR
{
    CPP cpp;
    CPLCY *pcplcy;
    SO *psoFocus;
    void *pv;
};

void InitCplcy(CPLCY *pcplcy, CM *pcm);

int FActiveCplcy(CPLCY *pcplcy);

void SetCpmanCpmt(CPMAN *pcpman, CPMT cpmt);

void PushCplookLookk(CPLOOK *pcplook, LOOKK lookk);

LOOKK LookkPopCplook(CPLOOK *pcplook);

LOOKK LookkCurCplook(CPLOOK *pcplook);

#endif // CPLCY_H
