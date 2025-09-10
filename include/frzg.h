/**
 * @file frzg.h
 */
#ifndef FRZG_H
#define FRZG_H

#include "common.h"
#include <freeze.h>
#include <oid.h>
#include <lo.h>

/**
 * @class FREEZE_GROUP
 * @brief Group of freeze objects.
 */
struct FRZG : public LO
{
    int coid;
    OID aoid[8];
    MRG mrg;
};

void PostFrzgLoad(FRZG *pfrzg);

void AddFrzgObject(FRZG *pfrzg, OID oid);

#endif // FRZG_H
