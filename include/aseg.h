/**
 * @file aseg.h
 */
#ifndef ASEG_H
#define ASEG_H

#include "common.h"
#include <waypoint.h>
#include <util.h>
#include <sm.h>

// Forward.
struct OVR;
struct CHN;
struct ASEGA;

/**
 * @brief Unknown.
 */
enum SEEK
{
    SEEK_Nil = -1,
    SEEK_Start = 0,
    SEEK_Current = 1,
    SEEK_End = 2,
    SEEK_EndDoEvents = 3,
    SEEK_Max = 4
};

/**
 * @brief Unknown.
 */
struct CHN
{
    // ...
};

/**
 * @class ANIMATION_SEGMENT
 * @brief Object representing an animation segment.
 */
struct ASEG : public LO
{
    /* 0x34 */ STRUCT_PADDING(14);
    /* 0x6c */ DL dlAsega;
    /* 0x78 */ STRUCT_PADDING(2);
    /* 0x80 */ CLQ clqMasterSuck;
    /* 0x90 */ LM lmMasterSuck;
    /* 0x98 */ float svtMasterSuck;
    /* 0x9c */ CHN *pchnStrip;
};

/**
 * @brief Animation segment something(?).
 */
struct ASEGD
{
    // ...
};

/**
 * @class ASEGBL
 * @brief Animation segment blend(?).
 */
struct ASEGBL : public ASEG
{
    // ...
};

/**
 * @brief Unknown.
 */
struct EA
{
    float tLocal;
};

/**
 * @brief Supposed to start the ASEG system, but it doesn't do anything.
 */
void StartupAseg();

void InitAseg(ASEG *paseg);

void LoadAsegFromBrx(ASEG *paseg, CBinaryInputStream *pbis);

void LoadAsegEventsFromBrx(ASEG *paseg, CBinaryInputStream *pbis, int fFrame, int *pcea, EA **paea);

void CloneAseg(ASEG *paseg, LO *ploBase);

void PostAsegLoad(ASEG *paseg);

void PostAsegLoadCallback(ASEG *paseg, MSGID msgid, void *pvData);

void ApplyAsegOvr(ASEG *paseg, ALO *paloAsegRoot, int covr, OVR *aovr, float tLocal, float svtLocal, GRFAPL grfapl, ASEGA **ppasega);

void ApplyAseg(ASEG *paseg, ALO *paloAsegRoot, float tLocal, float svtLocal, GRFAPL grfapl, ASEGA **ppasega);

ASEGA *PasegaApplyAseg(ASEG *paseg, ALO *paloAsegRoot, float tLocal, float svtLocal, GRFAPL grfapl);

ASEGA *PasegaFindAseg(ASEG *paseg, ALO *paloRoot);

void EnsureAseg(ASEG *paseg, ALO *paloRoot, SEEK seek, float t, float svt, GRFAPL grfapl, ASEGA **ppasega);

ASEGA *PasegaEnsureAseg(ASEG *paseg, ALO *paloRoot, SEEK seek, float t, float svt, GRFAPL grfapl);

void ApplyAsegCur(ASEG *paseg, ALO *paloRoot, float t, float svt, GRFAPL grfapl, ASEGA **ppasega);

int FWipingAseg(ASEG *paseg);

void FindAsegClosestPoint(ASEG *paseg, ALO *palo, VECTOR *ppos, float t, float *ptClosest, VECTOR *pposClosest, VECTOR *pvClosest);

EA *PeaFindAsegLabel(ASEG *paseg, OID oidLabel);

float TFindAsegLabel(ASEG *paseg, OID oidLabel);

CHN *PchnFindAseg(ASEG *paseg, ALO *palo);

void PredictAsegEffect(ASEG *paseg, float t, float svt, ALO *paloLeaf, ALO *paloBasis, int cpaloPredict, VECTOR *apos, MATRIX3 *amat, VECTOR *av, VECTOR *aw);

void GetAsegWaypoints(ASEG *paseg, ALO *paloContext, int *pcpwaypoint, WAYPOINT ***papwaypoint);

void StripAsegChn(ASEG *paseg, CHN *pchn);

void StripAsegAlo(ASEG *paseg, ALO *palo);

/**
 * @brief Does nothing.
 */
void LoadAsegblFromBrx(ASEGBL *pasegbl, CBinaryInputStream *pbis);

/**
 * @brief Does nothing.
 */
void PostAsegblLoad(ASEGBL *pasegbl);

/**
 * @brief Does nothing.
 */
void CloneAsegbl(ASEGBL *pasegbl, LO *ploBase);

#endif // ASEG_H
