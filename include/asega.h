/**
 * @file asega.h
 */
#ifndef ASEGA_H
#define ASEGA_H

#include "common.h"
#include <basic.h>
#include <aseg.h>
#include <dl.h>
#include <sw.h>

// Forward.
struct ACTSEG;
struct CHN;
struct EA;

/**
 * @class ANIMATION_SEGMENT_APPLICATION
 * @brief Unknown.
 */
struct ASEGA : public BASIC
{
    /* 0x08 */ ASEG *paseg;
    /* 0x0c */ STRUCT_PADDING(2);
    /* 0x14 */ float tLocal;
    /* 0x18 */ float svtLocal;
    /* 0x1c */ STRUCT_PADDING(2);
    /* 0x24 */ char fHandsOff;
    /* 0x25 */ undefined1 unk1;
    /* 0x26 */ undefined1 unk2;
    /* 0x27 */ undefined1 unk3;
    /* 0x28 */ ACTSEG *pactsegError;
    /* 0x2c */ STRUCT_PADDING(6);
    /* 0x44 */ DL dlActseg;
    // ...
};

ASEGA *PasegaNew(SW *psw);

void SetAsegaHandsOff(ASEGA *pasega, int fHandsOff);

void UpdateAsegaIeaCur(ASEGA *pasega);

ACTSEG *PactsegFindAsega(ASEGA *pasega, OID oid);

void HandleAsegaEvent(ASEGA *pasega, EA *pea, int *pfRetracted);

void HandleAsegaEventsFF(ASEGA *pasega, ASEG *paseg, int *pfRetract);

void HandleAsegaEvents(ASEGA *pasega, ASEG *paseg, int *pfRetracted);

void RemoveAsega(ASEGA *pasega);

void RetractAsega(ASEGA *pasega);

float UFromEaErrorFunc(EA *pea, float s);

int FWrapAsegaTime(ASEGA *pasega, float *ptLocal, float *psvtLocal);

void UpdateAsega(ASEGA *pasega, float dt);

void SeekAsega(ASEGA *pasega, SEEK seek, float dtLocal, float svtLocal);

void SnapAsega(ASEGA *pasega, int fForce);

void AdaptAsega(ASEGA *pasega);

void FindChnClosestPointLocal(CHN *pchn, ALO *palo, VECTOR *ppos, float tAsegMax, float sIgnore, float t, float *ptClosest, VECTOR *pposClosest, VECTOR *pvClosest);

void SetAsegaSpeed(ASEGA *pasega, float svt);

void SetAsegaMasterSpeed(ASEGA *pasega, float svtMaster);

void SetAsegaPriority(ASEGA *pasega, int nPriority);

void SendAsegaMessage(ASEGA *pasega, MSGID msgid, void *pv);

void SubscribeAsegaStruct(ASEGA *pasega, PFNMQ pfnmq, void *pvContext);

void SubscribeAsegaObject(ASEGA *pasega, LO *ploTarget);

#endif // ASEGA_H
