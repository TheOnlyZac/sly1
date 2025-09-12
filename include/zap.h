/**
 * @file zap.h
 *
 * @brief Zap (damage) system.
 */
#ifndef ZAP_H
#define ZAP_H

#include "common.h"
#include <oid.h>
#include <so.h>
#include <ensure.h>

/**
 * @brief Zap kind.
 */
enum ZPK {
    ZPK_Nil = -1,
    ZPK_Blunt = 0,
    ZPK_Electric = 1,
    ZPK_Fire = 2,
    ZPK_Water = 3,
    ZPK_Crush = 4,
    ZPK_Pit = 5,
    ZPK_Max = 6
};

/**
 * @brief Zap _?_ Kind
 *
 * @todo Figure out what the O stands for.
*/
enum ZOK
{
    ZOK_Nil = -1,
    ZOK_Inherit = 0,
    ZOK_Zap = 1,
    ZOK_NoZap = 2,
    ZOK_Ignore = 3,
    ZOK_ZapAndIgnore = 4,
    ZOK_Max = 5
};

/**
 * @brief Unknown.
 */
struct ZPD
{
    SO *pso;
    ZPK zpk;
    float dzThrow;
    int fThrowCut;
    int coidThrow;
    OID aoidThrow[32];
    int cploThrow;
    LO *aploThrow[32];
};

/**
 * @brief Zap.
 */
struct ZAP
{
    // ...
};

/**
 * @brief TOUCH_ZAPPER
 * @brief Zapper trigger on touching the player.
 *
 * @todo Does it inherit from ZAP?
*/
struct TZP
{
    // ...
};

/**
 * @brief Unknown.
 */
struct ZPR
{
    ZPK zpk;
    LO *ploSource;
    void *pv;
    void *pfnzap; // NOTE: This is a function pointer.
};

#endif // ZAP_H
