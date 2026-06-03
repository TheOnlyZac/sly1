/**
 * @file crv.h
 */
#ifndef CRV_H
#define CRV_H

#include "common.h"
#include <vec.h>
#include <mat.h>
#include <bis.h>
#include <cm.h>

/**
 * @brief (?) kind.
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
struct CRV
{
    undefined4 unknown;
    CRVK crvk;
    int fClosed;
    int ccv;
    float *mpicvu;
    float *mpicvs;
    VECTOR *mpicvpos;
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
    // ...
};

/**
 * @todo Implement.
 */
struct CRVL
{
    // ...
};

/**
 * @todo Implement.
 */
struct CRVC
{
    // ...
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
