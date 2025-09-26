/**
 * @file rchm.h
 */
#ifndef RCHM_H
#define RCHM_H

#include "common.h"
#include <target.h>
#include <pipe.h>
#include <vec.h>
#include <bsp.h>
#include <lo.h>
#include <jt.h>

/**
 * @brief Unknown.
 */
struct TWR
{
    int aipos[4];
};

/**
 * @class REACH_MAP
 * @brief Spatial map determining where JT can reach with his cane.
 * @todo Implement the struct.
 */
struct RCHM : public LO
{
    /* 0x34 */ OID oidHost;
    /* 0x38 */ OID oidTouch;
    /* 0x3c */ STRUCT_PADDING(6);
    /* 0x54 */ float rclNatural;
    /* 0x58 */ float ioNatural;
    /* 0x5c */ float lhubNatural;
    /* 0x60 */ STRUCT_PADDING(8);
    /* 0x80 */ int fCenterSet;
    // ...
};

void InitRchm(RCHM *prchm);

void LoadRchmFromBrx(RCHM *prchm, CBinaryInputStream *pbis);

void PostRchmLoad(RCHM *prchm);

void ReblendRchm(RCHM *prchm, TWR *ptwr, VECTOR *ppos);

void BuildRchmCoefficients(RCHM *prch, float rcl, float io, float lhub, float *mpiblu);

void ConvertRchmIposToRclIoLhub(RCHM *prchm, int ipos, float *prcl, float *pio, float *plhub);

void SetRchmNaturalCoefficients(RCHM *prchm, float rcl, float io, float lhub);

void SetRchmCenterCoefficients(RCHM *prchm, float rcl, float io, float lhub);

void PredictRchmTargetPos(RCHM *prchm, TARGET *ptarget, float dt, VECTOR *ppos);

void PredictRchmTargetLocalPos(RCHM *prchm, TARGET *ptarget, float dt, VECTOR *pposLocal);

TWR *PtwrMapRchmSafe(RCHM *prchm, BSP *pbsp, VECTOR *ppos);

void FindRchmClosestPoint(RCHM *prchm, VECTOR *ppos, VECTOR *pposClosest, TWR **pptwr, float *ps);

void TrackJtTarget(JT *pjt, RCHM *prchm, TARGET *ptarget);

void TrackJtPipe(JT *pjt, RCHM *prchm, PIPE *ppipe, float *psPipe);

#endif // RCHM_H
