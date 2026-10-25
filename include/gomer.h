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

struct VOL;

/**
 * @class GOMER
 * @brief Boss base character controller (derived from STEPGUARD).
 */
struct GOMER : public STEPGUARD
{
    STRUCT_PADDING(38);
    /* 0xc10 */ float sAbandon;
    /* 0xc14 */ float dzAbandon;
    /* 0xc18 */ OID oidAbandon;
    /* 0xc1c */ VOL *pvolAbandon;
    /* 0xc20 */ LM lmSDetect;
    /* 0xc28 */ LM lmRadDetect;
    /* 0xc30 */ OID oidDetect;
    /* 0xc34 */ VOL *pvolDetect;
    /* 0xc38 */ int fDetectLatch;
    /* 0xc3c */ int fDetectLatchExternal;
    /* 0xc40 */ int fAbandonExternal;
};

void InitGomer(GOMER *pgomer);
void PostGomerLoad(GOMER *pgomer);

#endif // GOMER_H
