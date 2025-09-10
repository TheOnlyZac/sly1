/**
 * @file step.h
 */
#ifndef STEP_H
#define STEP_H

#include "common.h"
#include <po.h>
#include <sm.h>
#include <util.h>

/**
 * @brief STEP_FIGURE
 * @brief Moving/waking characters.
 */
struct STEP : public PO
{
    ALO *paloLeftFoot;
    ALO *paloRightFoo4t;
    ALO *paloLeftHand;
    ALO *paloRightHand;
    ALO *paloLeftHeel;
    ALO *paloRightHeel;
    ALO *paloLeftBall;
    ALO *paloRightBall;
    float radJoy;
    float uJoyDeflect;
    float radTarget;
    float uTarget;
    VECTOR vTarget;
    float zBaseTarget;
    undefined4 unk_0x614[3];
    MATRIX3 matTarget;
    int fBaseXp;
    float tBaseXp;
    undefined4 unk_0x658[2];
    VECTOR posBaseXp;
    VECTOR normalBaseXp;
    SO *psoBaseXp;
    float uFootFall;
    float tLastFootfall;
    float dzBase;
    int iposBase;
    VECTOR *pposBase;
    VECTOR *pposBumper;
    SO *psoPhys;
    SMP smpSpin;
    undefined4 unk_0x6ac;
    CLQ clqDradToURun;
    float rGravity;
    SMP smpCompress;
    SMP smpExpand;
    undefined4 unk_0x6dc;
};

#endif // STEP_H
