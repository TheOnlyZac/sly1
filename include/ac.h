/**
 * @file ac.h
 *
 * @todo Implement the structs.
 */
#ifndef AC_H
#define AC_H

#include "common.h"
#include <vec.h>
#include <mat.h>
#include <bis.h>
#include <alo.h>

typedef int GRFEVAL;

/**
 * @brief (?) kind.
 */
enum ACVK
{
    ACVK_Nil = -1,
    ACVK_Component = 0,
    ACVK_Bezier = 1,
    ACVK_Blend = 2,
    ACVK_Max = 3
};

/**
 * @brief (?) kind.
 */
enum ACGK
{
    ACGK_Nil = -1,
    ACGK_Bezier = 0,
    ACGK_BezierWeighted = 1,
    ACGK_Linear = 2,
    ACGK_BlendTwist = 3,
    ACGK_BlendPose = 4,
    ACGK_Max = 5,
};

/**
 * @brief Unknown.
 */
struct KVB
{
    // ...
};

/**
 * @brief Unknown.
 */
struct ACP
{
    // ...
};

/**
 * @brief Unknown.
 */
struct ACR
{
    // ...
};

/**
 * @brief Unknown.
 */
struct ACS
{
    // ...
};

/**
 * @brief Unknown.
 */
struct ACG
{
    // ...
};

/**
 * @brief Unknown.
 */
struct ACPBL : public ACP
{
    // ...
};

/**
 * @brief Unknown.
 */
struct ACPC : public ACP
{
    // ...
};

/**
 * @brief Unknown.
 */
struct ACPB : public ACP
{
    // ...
};

/**
 * @brief Unknown.
 */
struct ACRC : public ACR
{
    // ...
};

/**
 * @brief Unknown.
 */
struct ACRB : public ACR
{
    // ...
};

/**
 * @brief Unknown.
 */
struct ACRBL : public ACR
{
    // ...
};

/**
 * @brief Unknown.
 */
struct ACSC : public ACS
{
    // ...
};

/**
 * @brief Unknown.
 */
struct ACSB : public ACS
{
    // ...
};

/**
 * @brief Unknown.
 */
struct ACGB : public ACG
{
    // ...
};

/**
 * @brief Unknown.
 */
struct ACGBW : public ACG
{
    // ...
};

/**
 * @brief Unknown.
 */
struct ACGL : public ACG
{
    // ...
};

/**
 * @brief Unknown.
 */
struct ACGBLT : public ACG
{
    // ...
};

/**
 * @brief Unknown.
 */
struct ACGBLP : public ACG
{
    // ...
};

void FindKey(float t, GRFEVAL grfeval, int cbKey, int ckey, char *abKey, float *pdt, float *pdtSeg, void **ppv);

void EvaluateAcp(ACP *pacp, ALO *palo, float t, float svt, GRFEVAL grfeval, VECTOR *ppos, VECTOR *pv);

void GetAcpTimes(ACP *pacp, int *pct, float **pat);

void EvaluateAcr(ACR *pacr, ALO *palo, float t, float svt, GRFEVAL grfeval, MATRIX3 *pmat, VECTOR *pw);

void EvaluateAcrEul(ACR *pacr, ALO *palo, float t, float svt, GRFEVAL grfeval, VECTOR *peul, VECTOR *pdeul);

void GetAcrTimes(ACR *pacr, int *pct, float **pat);

void EvaluateAcs(ACS *pacs, ALO *palo, float t, GRFEVAL grfeval, MATRIX3 *pmat);

void GetAcsTimes(ACS *pacs, int *pct, float **pat);

void EvaluateAcg(ACG *pacg, ALO *palo, float t, float svt, GRFEVAL grfeval, float *pg, float *pdg);

void GetAcgTimes(ACG *pacg, int *pct, float **pat);

void LoadAcgbFromBrx(ACGB *pacgb, CBinaryInputStream *pbis);

void EvaluateAcgb(ACGB *pacgb, ALO *palo, float t, float svt, GRFEVAL grfeval, float *pg, float *pdg);

void GetAcgbTimes(ACGB *pacgb, int *pct, float **pat);

void LoadAcgbwFromBrx(ACGBW *pacgbw, CBinaryInputStream *pbis);

void EvaluateAcgbw(ACGBW *pacgbw, ALO *palo, float t, float svt, GRFEVAL grfeval, float *pg, float *pdg);

void GetAcgbwTimes(ACGBW *pacgbw, int *pct, float **pat);

void EvaluateAcgl(ACGL *pacgl, ALO *palo, float t, float svt, GRFEVAL grfeval, float *pg, float *pdg);

void LoadAcglFromBrx(ACGL *pacgl, CBinaryInputStream *pbis);

void GetAcglTimes(ACGL *pacgl, int *pct, float **pat);

void EvaluateApacg(ACG **apacg, ALO *palo, float t, float svt, GRFEVAL grfeval, VECTOR *pvecDefault, VECTOR *pvec, VECTOR *pdvec);

void LoadApacgFromBrx(ACG **apacg, VECTOR *pvecDefault, CBinaryInputStream *pbis);

void GetApacgTimes(ACG **apacg, int *pct, float **pat);

void EvaluateAkvb(int ckvb, KVB *akvb, float t, float svt, GRFEVAL grfeval, VECTOR *pvec, VECTOR *pdvec);

void LoadAkvbFromBrx(int *pckvb, KVB **pakvb, CBinaryInputStream *pbis);

void GetAkvbTimes(int ckvb, KVB *akvb, int *pct, float **pat);

void EvaluateAcpc(ACPC *pacpc, ALO *palo, float t, float svt, GRFEVAL grfeval, VECTOR *ppos, VECTOR *pv);

void LoadAcpcFromBrx(ACPC *pacpc, CBinaryInputStream *pbis);

void GetAcpcTimes(ACPC *pacpc, int *pct, float **pat);

void EvaluateAcpb(ACPB *pacpb, ALO *palo, float t, float svt, GRFEVAL grfeval, VECTOR *ppos, VECTOR *pv);

void LoadAcpbFromBrx(ACPB *pacpb, CBinaryInputStream *pbis);

void GetAcpbTimes(ACPB *pacpb, int *pct, float **pat);

void EvaluateAcrc(ACRC *pacrc, ALO *palo, float t, float svt, GRFEVAL grfeval, MATRIX3 *pmat, VECTOR *pw);

void EvaluateAcrcEul(ACRC *pacrc, ALO *palo, float t, float svt, GRFEVAL grfeval, VECTOR *peul, VECTOR *pdeul);

void LoadAcrcFromBrx(ACRC *pacrc, CBinaryInputStream *pbis);

void GetAcrcTimes(ACRC *pacrc, int *pct, float **pat);

void EvaluateAcrb(ACRB *pacrb, ALO *palo, float t, float svt, GRFEVAL grfeval, MATRIX3 *pmat, VECTOR *pw);

void EvaluateAcrbEul(ACRB *pacrb, ALO *palo, float t, float svt, GRFEVAL grfeval, VECTOR *peul, VECTOR *pdeul);

void LoadAcrbFromBrx(ACRB *pacrb, CBinaryInputStream *pbis);

void GetAcrbTimes(ACRB *pacrb, int *pct, float **pat);

void EvaluateAcsc(ACSC *pacsc, ALO *palo, float t, GRFEVAL grfeval, MATRIX3 *pmat);

void LoadAcscFromBrx(ACSC *pacsc, CBinaryInputStream *pbis);

void GetAcscTimes(ACSC *pacsc, int *pct, float **pat);

void EvaluateAcsb(ACSB *pacsb, ALO *palo, float t, GRFEVAL grfeval, MATRIX3 *pmat);

void LoadAcsbFromBrx(ACSB *pacsb, CBinaryInputStream *pbis);

void GetAcsbTimes(ACSB *pacsb, int *pct, float **pat);

void EvaluateAcpbl(ACPBL *pacpbl, ALO *palo, float t, float svt, GRFEVAL grfeval, VECTOR *ppos, VECTOR *pv);

void EvaluateAcrbl(ACRBL *pacrbl, ALO *palo, float t, float svt, GRFEVAL grfeval, MATRIX3 *pmat, VECTOR *pw);

void EvaluateAcgblt(ACGBLT *pacgblt, ALO *palo, float t, float svt, GRFEVAL grfeval, float *pg, float *pdg);

void EvaluateAcgblp(ACGBLP *pacgblp, ALO *palo, float t, float svt, GRFEVAL grfeval, float *pg, float *pdg);

ACP *PacpNew(ACVK acvk);

ACR *PacrNew(ACVK acvk);

ACS *PacsNew(ACVK acvk);

ACG *PacgNew(ACGK acgk);

#endif // AC_H
