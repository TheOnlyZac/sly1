/**
 * @file ac.h
 * @brief Animation curve?
 */
#ifndef AC_H
#define AC_H

#include "common.h"
#include <vec.h>
#include <mat.h>
#include <bis.h>
#include <alo.h>

// Forward declarations.
struct ACP;
struct ACR;
struct ACS;
struct ACG;

typedef int GRFEVAL;

/**
 * @brief Animation Curve Variant Kind.
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
 * @brief Animation Curve Graph Kind.
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
 * @brief Key Graph Bezier Tangent Kind.
 */
enum KGBTK
{
    KGBTK_Nil = -1,
    KGBTK_Global = 0,
    KGBTK_Fixed = 1,
    KGBTK_Linear = 2,
    KGBTK_Flat = 3,
    KGBTK_Smooth = 4,
    KGBTK_Step = 5,
    KGBTK_Slow = 6,
    KGBTK_Fast = 7,
    KGBTK_Clamped = 8,
    KGBTK_Max = 9,
};

/**
 * @brief Key Vector Bezier.
 */
struct KVB
{
    /* 0x00 */ float t;
    /* 0x04 */ STRUCT_PADDING(3);
    /* 0x10 */ VECTOR vec;
    /* 0x1c */ STRUCT_PADDING(1); // TODO: Remove once VECTOR is 16 bytes long.
    /* 0x20 */ VECTOR dvecIn;
    /* 0x2c */ STRUCT_PADDING(1); // TODO: Remove once VECTOR is 16 bytes long.
    /* 0x30 */ VECTOR dvecOut;
    /* 0x3c */ STRUCT_PADDING(1); // TODO: Remove once VECTOR is 16 bytes long.
};

/**
 * @brief Key Graph Linear.
 */
struct KGL
{
    /* 0x00 */ float t;
    /* 0x04 */ float g;
};

/**
 * @brief Key Graph Bezier Tangent.
 */
struct KGBT
{
    /* 0x00 */ KGBTK kgbtk;
    /* 0x04 */ float gSlope;
};

/**
 * @brief Key Graph Bezier.
 */
struct KGB
{
    /* 0x00 */ float t;
    /* 0x04 */ float g;
    /* 0x08 */ KGBT kgbtIn;
    /* 0x10 */ KGBT kgbtOut;
};

/**
 * @brief Key Graph Bezier Weighted Tangent.
 */
struct KGBWT
{
    /* 0x00 */ KGBTK kgbtk;
    /* 0x04 */ float dt;
    /* 0x08 */ float g;
};

/**
 * @brief Key Graph Bezier Weighted.
 */
struct KGBW
{
    /* 0x00 */ float t;
    /* 0x04 */ float g;
    /* 0x08 */ KGBWT kgbwtIn;
    /* 0x14 */ KGBWT kgbwtOut;
};

/**
 * @brief Animation Curve Position.
 */
struct ACP
{
    /* 0x00 */ STRUCT_PADDING(1); // TODO: Add vtables.
    /* 0x04 */ ACVK acvk;
    /* 0x08 */ int fContiguous;
};

/**
 * @brief Animation Curve Position Component.
 */
struct ACPC : public ACP
{
    /* 0x0c */ STRUCT_PADDING(1);
    /* 0x10 */ VECTOR posDefault;
    /* 0x1c */ STRUCT_PADDING(1); // TODO: Remove once VECTOR is 16 bytes long.
    /* 0x20 */ ACG *apacg[3];
    /* 0x2c */ STRUCT_PADDING(1);
};

/**
 * @brief Animation Curve Position Bezier.
 */
struct ACPB : public ACP
{
    /* 0x0c */ int ckvb;
    /* 0x10 */ KVB *akvb;
};

/**
 * @brief Animation Curve Position Blend.
 * @todo Implement the struct.
 */
struct ACPBL : public ACP
{
    /* 0x0c */ STRUCT_PADDING(3);
};

/**
 * @brief Animation Curve Rotation.
 */
struct ACR
{
    /* 0x00 */ STRUCT_PADDING(1); // TODO: Add vtables.
    /* 0x04 */ ACVK acvk;
    /* 0x08 */ int fContiguous;
};

/**
 * @brief Animation Curve Rotation Component.
 */
struct ACRC : public ACR
{
    /* 0x0c */ STRUCT_PADDING(1);
    /* 0x10 */ VECTOR eulDefault;
    /* 0x1c */ STRUCT_PADDING(1); // TODO: Remove once VECTOR is 16 bytes long.
    /* 0x20 */ ACG *apacg[3];
    /* 0x2c */ STRUCT_PADDING(1);
};

/**
 * @brief Animation Curve Rotation Bezier.
 */
struct ACRB : public ACR
{
    /* 0x0c */ int ckvb;
    /* 0x10 */ KVB *akvb;
};

/**
 * @brief Animation Curve Rotation Blend.
 * @todo Implement the struct.
 */
struct ACRBL : public ACR
{
    /* 0x0c */ STRUCT_PADDING(4);
};

/**
 * @brief Animation Curve Scale.
 */
struct ACS
{
    /* 0x00 */ STRUCT_PADDING(1); // TODO: Add vtables.
    /* 0x04 */ ACVK acvk;
};

/**
 * @brief Animation Curve Scale Component.
 */
struct ACSC : public ACS
{
    /* 0x08 */ STRUCT_PADDING(2);
    /* 0x10 */ VECTOR vecDefault;
    /* 0x1c */ STRUCT_PADDING(1); // TODO: Remove once VECTOR is 16 bytes long.
    /* 0x20 */ ACG *apacg[3];
    /* 0x2c */ STRUCT_PADDING(1);
};

/**
 * @brief Animation Curve Scale Bezier.
 */
struct ACSB : public ACS
{
    /* 0x08 */ int ckvb;
    /* 0x0c */ KVB *akvb;
};

/**
 * @brief Animation Curve Graph.
 */
struct ACG
{
    /* 0x00 */ STRUCT_PADDING(1); // TODO: Add vtables.
    /* 0x04 */ ACGK acgk;
};

/**
 * @brief Animation Curve Graph Bezier.
 */
struct ACGB : public ACG
{
    /* 0x08 */ int ckgb;
    /* 0x0c */ KGB *akgb;
};

/**
 * @brief Animation Curve Graph Bezier Weighted.
 */
struct ACGBW : public ACG
{
    /* 0x08 */ int ckgbw;
    /* 0x0c */ KGBW *akgbw;
};

/**
 * @brief Animation Curve Graph Linear.
 */
struct ACGL : public ACG
{
    /* 0x08 */ int ckgl;
    /* 0x0c */ KGL *akgl;
};

/**
 * @brief Animation Curve Graph Blend Twist.
 * @todo Implement the struct.
 */
struct ACGBLT : public ACG
{
    /* 0x08 */ STRUCT_PADDING(3);
};

/**
 * @brief Animation Curve Graph Blend Pose.
 * @todo Implement the struct.
 */
struct ACGBLP : public ACG
{
    /* 0x08 */ STRUCT_PADDING(4);
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
