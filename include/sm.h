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

#endif // SM_H
