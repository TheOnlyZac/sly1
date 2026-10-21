/**
 * @file sm.h
 *
 * @brief Probabilistic finite state machines.
 */
#ifndef SM_H
#define SM_H

#include "common.h"
#include <dl.h>
#include <mq.h>
#include <lo.h>

// Forward declatations.
struct SM;
struct SMA;
struct SMT;
struct SMS;
struct SMP;
struct SMPA; // todo define
struct ASEG;
struct ASEGA;

typedef int GRFAPL;

typedef int GRFSMT; // State machine transition integer type.

/**
 * @class STATE_MACHINE
 * @brief State machine defined by a number of states and transitions.
 */
struct SM : public LO
{
    /* 0x34 */ int csms; // Count of states.
    /* 0x38 */ SMS *asms; // Array of states.
    /* 0x3c */ int csmt; // Count of transitions.
    /* 0x40 */ SMT *asmt; // Array of transitions.
    /* 0x44 */ int fDefault;
    /* 0x48 */ DL dlSma;
};

/**
 * @class STATE_MACHINE_APPLICATION
 * @brief Unknown.
 */
struct SMA : public BASIC
{
    /* 0x08 */ DLE dleSm;
    /* 0x10 */ DLE dleSw;
    /* 0x18 */ SM *psm;
    /* 0x1c */ ALO *paloRoot;
    /* 0x20 */ int grfapl;
    /* 0x24 */ ASEGA *pasegaCur;
    /* 0x28 */ int ismsCur;
    /* 0x2c */ int ismsNext;
    /* 0x30 */ int ismsGoal;
    /* 0x34 */ SMT *psmtCur;
    /* 0x38 */ float svtLocal;
    /* 0x3c */ MQ *pmqFirst;
};

/**
 * @brief State machine transition.
 */
struct SMT
{
    union
    {
        /* 0x00 */ int fAseg;
        /* 0x00 */ ASEG *paseg;
    };
    /* 0x04 */ int ismsFrom; // From state
    /* 0x08 */ int ismsTo; // To state
    /* 0x0c */ GRFSMT grfsmt; // Unknown
    /* 0x10 */ float gProbability; // Probability of transition
};

/**
 * @brief State machine state.
 */
struct SMS
{
    /* 0x00 */ OID oid;
    union
    {
        /* 0x04 */ OID oidNext;
        /* 0x04 */ int ismsNext;
    };
};

/**
 * @brief State machine pace(?).
 *
 * @note Used for the Fast/Slow powerups.
 */
struct SMP
{
    float svFast; // todo check if this is correct
    float svSlow;
    float dtFast;
};

void LoadSmFromBrx(SM *psm, CBinaryInputStream *pbis);

void PostSmLoad(SM *psm);

void PostSmLoadCallback(SM *psm, MSGID msgid, void *pvData);

SMA *PsmaApplySm(SM *psm, ALO *paloRoot, OID oidInitialState, GRFAPL grfapl);

SMA *PsmaFindSm(SM *psm, ALO *paloRoot);

int IsmsFindSmOptional(SM *psm, OID oid);

int IsmsFindSmRequired(SM *psm, OID oid);

OID OidFromSmIsms(SM *psm, int isms);

void RetractSma(SMA *psma);

void SetSmaGoal(SMA *psma, OID oid);

void GetSmaGoal(SMA *psma, OID *poid);

void GetSmaCur(SMA *psma, OID *poid);

void GetSmaNext(SMA *psma, OID *poid);

void SetSmaSvt(SMA *psma, float svt);

void SeekSma(SMA *psma, OID oid);

void ChooseSmaTransition(SMA *psma);

void EndSmaTransition(SMA *psma);

void HandleSmaMessage(SMA *psma, MSGID msgid, void *pv);

void SkipSma(SMA *psma, float dtSkip);

void SendSmaMessage(SMA *psma, MSGID msgid, void *pv);

void NotifySmaSpliceOnEnterState(SMA *psma, int ismsFrom, int ismsTo);

#endif // SM_H
