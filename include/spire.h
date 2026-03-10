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
    /* 0x50 */ DLE dleSpire;
    /* 0x58 */ float unk1; // TODO: Rename.
};

void InitSpire(SPIRE *pspire);

void OnSpireAdd(SPIRE *pspire);

void OnSpireRemove(SPIRE *pspire);

void CloneSpire(SPIRE *pspire, SPIRE *pspireBase);

#endif // SPIRE_H
