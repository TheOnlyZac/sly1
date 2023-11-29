#pragma once
#include <iostream>
#include <game.h>
#include <gs.h>

/**
 * Zap
 *
 * A volume that damages the player upon contact.
 */
struct ZAP
{
    // todo
    // ...
};

/**
 * Zap Kind?
 */
enum ZOK
{
    ZOK_Inherit = 0,
    ZOK_Zap = 1,
    ZOK_NoZap = 2,
    ZOK_Ignore = 3,
    ZOK_ZapAndIgnore = 4,
    ZOK_Max = 5
};
