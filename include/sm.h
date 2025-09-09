/**
 * @file sm.h
 *
 * @brief State machines.
 */
#ifndef SM_H
#define SM_H

#include "common.h"
#include <dl.h>
#include <mq.h>
#include <lo.h>
#include <anim.h>

// Forward declatations.
struct SM;
struct SMA;
struct SMT;
struct SMS;
struct SMP;
struct SMPA; // todo define

typedef int GRFAPL;

/**
 * @brief State machine.
 */
struct SM : public LO
{
    int csms;
    SMS *asms;
    int csmt;
    SMT *asmt;
    int fDefault;
    DL dlSma;
};

/**
 * @brief State machine action.
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
    int ismsFrom;
    int ismsTo;
    int grfsmt;
    float gProbability;
};

/**
 * @brief State machine state(?).
 */
struct SMS
{
    OID oid;
    undefined4 unk_0;
};

/**
 * @brief State machine something(?).
 *
 * @note Used for the fast/slow powerups.
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
