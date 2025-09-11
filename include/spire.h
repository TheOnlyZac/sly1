/**
 * @file spire.h
 */
#ifndef SPIRE_H
#define SPIRE_H

#include "common.h"
#include <xform.h>

/**
 * @class SPIRE
 * @brief Spire point that JT can balance on.
 */
struct SPIRE : public PNT
{
    DLE dleSpire;
};

#endif // SPIRE_H
