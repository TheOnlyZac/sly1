/**
 * @file wipe.h
 */
#ifndef WIPE_H
#define WIPE_H

#include "common.h"
#include <transition.h>

/**
 * @brief Wipe Kind
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
 * @brief Wipe State
 */
enum WIPES
{
    WIPES_Idle = 0,
    WIPES_WipingOut = 1,
    WIPES_Black = 2,
    WIPES_WipingIn = 3,
    WIPES_Max = 4
};

/**
 * @brief Wipe
 */
struct WIPE
{
    WIPES wipes;
    float tWipes;
    float uBlack;
    TRANS trans;
    WIPEK wipek;
    TRANS transButton;
    WIPEK wipekButton;
};

extern WIPE *g_pwipe;
extern WIPE g_wipe;

#endif // WIPE_H
