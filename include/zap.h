/**
 * @file zap.h
 *
 * @brief Damage system.
 */
#ifndef ZAP_H
#define ZAP_H

#include "common.h"
#include <so.h>

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

struct ZPD {
    SO *pso;
    ZPK zpk;
    float dzThrow;
    int fThrowCut;
    int coidThrow;
    OID aoidThrow[32];
    int cploThrow;
    LO *aploThrow[32];
};

#endif // ZAP_H
