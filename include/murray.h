/**
 * @file murray.h
 *
 * @brief "The Murray".
 */
#ifndef MURRAY_H
#define MURRAY_H

#include "common.h"
#include <stepguard.h>
#include <turret.h>
#include <xform.h>

// Forward.
struct WKR;

/**
 * @class MURRAY
 * @brief Used for Murray in Murray's Big Gamble and King of the Hill.
 * @todo Implement the struct.
 */
struct MURRAY : public STEPGUARD
{
    // ...
};

void InitMurray(MURRAY *pmurray);

/** 
 * @brief Postload for "The Murray".
*/
void PostMurrayLoad(MURRAY *pmurray);

void OnMurrayEnteringSgs(MURRAY *pmurray, SGS sgsPrev, ASEG *pasegOverride);

void OnMurrayExitingSgs(MURRAY *pmurray, SGS sgs);

void UpdateMurrayGoal(MURRAY *pmurray, int fEnter);

void UpdateMurraySgs(MURRAY *pmurray);

/**
 * @brief Absorb a WKR into Murray. Not sure exactly what this does, but it seems check if you have a
 *        charm then handle it like other stepguards.
 * @param pmurray Pointer to the Murray instance.
 * @param pwkr Pointer to the WKR to absorb.
 * @return Guessing 1 if the WKR was absorbed and 0 otherwise.
 */
int FAbsorbMurrayWkr(MURRAY *pmurray, WKR *pwkr);

int FDetectMurray(MURRAY *pmurray);

/**
 * @brief Always returns false and never gets called anywhere.
 */
int FCanMurrayAttack(MURRAY *pmurray);

/*
    * @brief Add enemy to array if it's not dying or a stepguard and there's room in the array.
    * @param pmurray Pointer to the Murray instance.
    * @param paloEnemy Pointer to the enemy to potentially add.
    * @return 1 if the enemy was added, 0 otherwise.
*/
int AddMurrayEnemy(MURRAY *pmurray, ALO *paloEnemy);

void SetMurrayPursueXfm(MURRAY *pmurray, XFM *pxfm);

void SetMurrayPatrolXfm(MURRAY *pmurray, XFM *pxfm);

void CollectMurrayPrize(MURRAY *pmurray, PCK pck, ALO *paloOther);

/** 
 * @brief Checks if Murray is stunned or dying.
 * @param pmurray Pointer to the Murray instance.
 * @return 1 if stunned, 2 if dying, 0 otherwise.
 */
int CheckMurrayStunOrDying(MURRAY *pmurray);

/**
 * @brief Message handler for Murray. Passes all messages to the stepguard message handler,
 *        and uniquely handles one message to reload after death.
 */
void HandleMurrayMessage(MURRAY *pmurray, MSGID msgid, void* pv);

/**
 * @brief No idea what this does.
 * @todo Figure out what this actually does and give it a better name.
 * @param pmurray Pointer to the Murray instance.
 * @param i Unused parameter.
 * @return 1 or 0.
 */
int FUN_001903f0(MURRAY *pmurray, int i);

extern SNIP D_00269B60[2];

#endif // MURRAY_H
