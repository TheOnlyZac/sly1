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
 * @brief Unknown.
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
