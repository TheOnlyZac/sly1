/**
 * @file splicemap.h
 *
 * @brief Splice maps.
 */
#ifndef SPLICEMAP_H
#define SPLICEMAP_H

#include "common.h"
#include <splice/ref.h>
#include <splice/pair.h>
#include <splice/frame.h>
#include <bis.h>
#include <sw.h>

/**
 * @brief A splice instance, containing a compiled CPair and a context frame.
 */
struct SPLC
{
    CPair *ppairCompile;
    CFrame *pframe;
};

/**
 * @brief Loads and initializes the Splice instances for a world.
 * A single world may have an array of separate Splice instances;
 * these are each indexed in functions by the argument "isplice".
 *
 * @param psw World object.
 * @param pbis Current input loading stream.
 */
void LoadSwSpliceFromBrx(SW *psw, CBinaryInputStream *pbis);

/**
 * @brief Looks up a context frame for a Splice instance (which may be NULL).
 * If it is non-null, will automatically add the global frame as a parent.
 *
 * @param isplice Splice instance.
 * @param psw World object.
 * @return Context frame, if it exists.
 */
CFrame *PframeFromIsplice(int isplice, SW *psw);

/**
 * @brief Evaluates a Splice instance.
 *
 * @param isplice Splice instance.
 * @param psw World object.
 * @return Evaluated (void) reference.
 */
CRef RefEvalModule(int isplice, SW *psw);

#endif // SPLICEMAP_H
