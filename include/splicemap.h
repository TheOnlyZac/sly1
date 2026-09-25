/**
 * @file splicemap.h
 *
 * @brief Splice maps.
 */
#ifndef SPLICEMAP_H
#define SPLICEMAP_H

#include "common.h"
#include <splice/ref.h>
#include <bis.h>
#include <sw.h>

void LoadSwSpliceFromBrx(SW *psw, CBinaryInputStream *pbis);

CFrame *PframeFromIsplice(int isplice, SW *psw);

CRef RefEvalModule(int isplice, SW *psw);

#endif // SPLICEMAP_H
