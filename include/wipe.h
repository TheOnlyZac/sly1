/**
 * @file wipe.h
 *
 * @brief Screen wipes.
 *
 * @todo Figure out if the function signatures are correct.
 */
#ifndef WIPE_H
#define WIPE_H

#include "common.h"
#include <transition.h>
#include <oid.h>
#include <joy.h>

/**
 * @brief Wipe Kind.
 */
enum WIPEK
{
    WIPEK_Fade = 0,
    WIPEK_Keyhole = 1,
    WIPEK_WorldMap = 2,
    WIPEK_Frozen = 3,
    WIPEK_Max = 4
};

/**
 * @brief Wipe State.
 */
enum WIPES
{
    WIPES_Nil = -1,
    WIPES_Idle = 0,
    WIPES_WipingOut = 1,
    WIPES_Black = 2,
    WIPES_WipingIn = 3,
    WIPES_Max = 4
};

/**
 * @brief Screen wipe.
 */
struct WIPE
{
    undefined4 unk_0x0;
    WIPES wipes;
    float tWipes;
    float uBlack;
    TRANS transButton;
    WIPEK wipek;
    WIPEK wipekButton;
};

extern WIPE *g_pwipe;
extern WIPE g_wipe;

void InitWipe(WIPE *pwipe);

void UpdateWipe(WIPE *pwipe, JOY *pjoy);

void DrawWipe(WIPE *pwipe);

void ActivateWipe(WIPE *pwipe, TRANS *ptrans, WIPEK wipek);

void SetWipeButtonTrans(WIPE *pwipe, TRANS *ptrans, WIPEK wipek);

int FCatchWipeButtonTrans(WIPE *pwipe, JOY *pjoy, WIPES wipesNew);

void SetWipeWipes(WIPE *pwipe, WIPES wipes);

extern "C" void WipeToWorldWarp(const void *pchzWorld, OID oidWarp, WIPEK wipek);

#endif // WIPE_H
