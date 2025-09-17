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
    DLE dleSm;
    DLE dleSw;
    SM *psm;
    ALO *paloRoot;
    int grfapl;
    ASEGA *pasegaCur;
    int ismsCur;
    int ismsNext;
    int ismsGoal;
    SMT *psmtCur;
    float svtLocal;
    MQ *pmqFirst;
};

/**
 * @brief State machine transition.
 */
struct SMT
{
    undefined4 unk_0;
    int ismsFrom; // From state
    int ismsTo; // To state
    GRFSMT grfsmt; // Unknown
    float gProbability; // Probability of transition
};

/**
 * @brief State machine state.
 */
struct SMS
{
    OID oid;
    undefined4 unk_0;
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
