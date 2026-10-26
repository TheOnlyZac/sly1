/**
 * @file crv.h
 *
 * @brief Curve.
 */
#ifndef CRV_H
#define CRV_H

#include "common.h"
#include <vec.h>
#include <mat.h>
#include <bis.h>
#include <cm.h>

/**
 * @brief Curve kind.
 */
enum CRVK
{
    CRVK_Nil = -1,
    CRVK_Linear = 0,
    CRVK_Cubic = 1,
    CRVK_Max = 2
};

/**
 * @brief Unknown.
 */
struct CTCE
{
    /* 0x000 */ VECTOR apos[20];
    /* 0x140 */ float mpiposs[20];
};

/**
 * @brief Curve.
 */
struct CRV
{
    union
    {
        /* 0x00 */ VTCRV *pvtcrv;
        /* 0x00 */ VTCRVL *pvtcrvl;
        /* 0x00 */ VTCRVC *pvtcrvc;
    };
    /* 0x04 */ CRVK crvk;
    /* 0x08 */ int fClosed;
    /* 0x0c */ int ccv;
    /* 0x10 */ float *mpicvu;
    /* 0x14 */ float *mpicvs;
    /* 0x18 */ VECTOR *mpicvpos;
};

/**
 * @todo Curve Linear.
 */
struct CRVL : public CRV
{
    // ...
};

/**
 * @brief Curve Cubic.
 */
struct CRVC : public CRV
{
    /* 0x01c */ VECTOR *mpicvdposIn;
    /* 0x020 */ VECTOR *mpicvdposOut;
    /* 0x024 */ STRUCT_PADDING(103); // CTCE ctce;
    /* 0x1c0 */ int icvCache;
};

/**
 * @todo Implement.
 */
struct CRVMC
{
    // ...
};

/**
 * @todo Implement.
 */
struct CRVMS
{
    CRV *pcrv;
    VECTOR *ppos0;
    VECTOR *ppos1;
};

/**
 * @todo Implement and figure out where this belongs to.
 */
struct CONSTR
{
    // ...
};

float SMeasureApos(int cpos, VECTOR *apos, float *mpiposs);

float GWrapApos(float g, int cpos, float *mpiposg, int fClosed);

int IposFindAposG(float g, int cpos, float *mpiposg, int fClosed, float *dg, float *dgSeg);

void EvaluateAposG(float g, int cpos, VECTOR *apos, float *mpiposg, int fClosed, VECTOR *ppos, VECTOR *pnormTangent);

void FindAposClosestPointAll(VECTOR *ppos, CONSTR *pconstr, int cpos, VECTOR *apos, VECTOR *pposClosest, VECTOR *pnormTangentClosest, int *pipos, float *pr);

void FindAposClosestPointSegment(VECTOR *ppos, CONSTR *pconstr, int cpos, VECTOR *apos, int iposStart, int fClosed, VECTOR *pposClosest, VECTOR *pnormTangentClosest, int *pipos, float *pr);

void ConvertApos(int cpos, VECTOR *apos, MATRIX4 *pmatSrc, MATRIX4 *pmatDst);

CRV *PcrvNew(CRVK crvk);

float SFromCrvU(CRV *pcrv, float u);

float UFromCrvS(CRV *pcrv, float s);

int IcvFindCrvU(CRV *pcrv, float u, float *du, float *duSeg);

int IcvFindCrvS(CRV *pcrv, float s, float *ds, float *dsSeg);

float GMeasureCrvU(CRVMC *pcrvmc, float u);

float UMaxCrv(CRV *pcrv);

float SMaxCrv(CRV *pcrv);

float SMeasureCrvSegmentU(CRVMS *pcrvms, float u);

void FindCrvClosestPointOnLineSegmentFromU(CRV *pcrv, VECTOR *ppos0, VECTOR *ppos1, float u, VECTOR *pposClosest, VECTOR *pnormTangentClosest, float *pu, float *ps);

void RenderCrv(CRV *pcrv, MATRIX4 *pmatWorld, CM *pcm, RGBA *rgba, int fDepthTest);

void RenderCrvAxesU(CRV *pcrv, float u, MATRIX4 *pmatWorld, CM *pcm, int fDepthTest);

void RenderCrvAxesS(CRV *pcrv, float s, MATRIX4 *pmatWorld, CM *pcm, int fDepthTest);

float DuGetCrvSearchIncrement(CRV *pcrv);

void LoadCrvlFromBrx(CRVL *pcrvl, CBinaryInputStream *pbis);

void EvaluateCrvlFromU(CRVL *pcrvl, float u, VECTOR *ppos, VECTOR *pnormTangent);

void EvaluateCrvlFromS(CRVL *pcrvl, float s, VECTOR *ppos, VECTOR *pnormTangent);

void RenderCrvlSegment(CRVL *pcrvl, int icv, MATRIX4 *pmatWorld, CM *pcm, RGBA *rgba, int fDepthTest);

void ConvertCrvl(CRVL *pcrvl, MATRIX4 *pmatSrc, MATRIX4 *pmatDst);

float SFromCrvlU(CRVL *pcrvl, float u);

float UFromCrvlS(CRVL *pcrvl, float s);

void MeasureCrvl(CRVL *pcrvl);

void FindCrvlClosestPointAll(CRVL *pcrvl, VECTOR *ppos, CONSTR *pconstr, VECTOR *pposClosest, VECTOR *pnormTangentClosest, float *pu, float *ps);

void FindCrvlClosestPointFromU(CRVL *pcrvl, VECTOR *ppos, float u, CONSTR *pconstr, VECTOR *pposClosest, VECTOR *pnormTangentClosest, float *pu, float *ps);

void FindCrvlClosestPointFromS(CRVL *pcrvl, VECTOR *ppos, float s, CONSTR *pconstr, VECTOR *pposClosest, VECTOR *pnormTangentClosest, float *pu, float *ps);

void LoadCrvcFromBrx(CRVC *pcrvc, CBinaryInputStream *pbis);

void InvalidateCrvcCache(CRVC *pcrvc);

void FillCrvcCache(CRVC *pcrvc, int icv);

void EvaluateCrvcFromU(CRVC *pcrvc, float u, VECTOR *ppos, VECTOR *pnormTangent);

void EvaluateCrvcFromS(CRVC *pcrvc, float s, VECTOR *ppos, VECTOR *pnormTangent);

void RenderCrvcSegment(CRVC *pcrvc, int icv, MATRIX4 *pmatWorld, CM *pcm, RGBA *rgba, int fDepthTest);

void ConvertCrvc(CRVC *pcrvc, MATRIX4 *pmatSrc, MATRIX4 *pmatDst);

float SFromCrvcU(CRVC *pcrvc, float u);

float UFromCrvcS(CRVC *pcrvc, float s);

void MeasureCrvc(CRVC *pcrvc);

void FindCrvcClosestPointAll(CRVC *pcrvc, VECTOR *ppos, CONSTR *pconstr, VECTOR *pposClosest, VECTOR *pnormTangentClosest, float *pu, float *ps);

void FindCrvcClosestPointFromU(CRVC *pcrvc, VECTOR *ppos, float u, CONSTR *pconstr, VECTOR *pposClosest, VECTOR *pnormTangentClosest, float *pu, float *ps);

void FindCrvcClosestPointFromS(CRVC *pcrvc, VECTOR *ppos, float s, CONSTR *pconstr, VECTOR *pposClosest, VECTOR *pnormTangentClosest, float *pu, float *ps);

#endif // CRV_H
