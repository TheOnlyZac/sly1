/**
 * @file gomer.h
 */
#ifndef GOMER_H
#define GOMER_H

#include "common.h"
#include <stepguard.h>

/**
 * @brief Gomer state.
 *
 * @todo Populate enum values.
 */
enum GOMERS
{
    GOMERS_Nil = -1
    // ...
};

/**
 * @class GOMER
 * @brief Unknown, related to bosses.
 * @todo Implement the struct.
 */
struct GOMER : public STEPGUARD
{
    // ...
    /* 0xc40 */ int fAbandonExternal;
};

void PostGomerLoad(GOMER *pgomer);

#endif // GOMER_H
