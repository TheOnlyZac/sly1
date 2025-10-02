/**
 * @file barrier.h
 */
#ifndef BARRIER_H
#define BARRIER_H

#include "common.h"
#include <so.h>

// Forward.
struct XP;

/**
 * @brief Barrier.
 * @todo Implement the struct.
 */
struct BARRIER : public SO
{
    // ...
    /* 0x554 */ int coid;
    /* 0x558 */ OID aoid[4];
    /* 0x568 */ int ccid;
    /* 0x56c */ CID acid[4];
    // ...
};

void InitBarrier(BARRIER *pbarrier);

void CloneBarrier(BARRIER *pbarrier, BARRIER *pbarrierBase);

void PostBarrierLoad(BARRIER *pbarrier);

void UpdateBarrier(BARRIER *pbarrier, float dt);

int FIgnoreBarrierIntersection(BARRIER *pbarrier, SO *psoOther);

void NotifyBarrierImpact(BARRIER *pbarrier, XP *pxp, int ixpd);

void AddBarrierObject(BARRIER *pbarrier, OID oid);

void AddBarrierClass(BARRIER *pbarrier, CID cid);

#endif // BARRIER_H
