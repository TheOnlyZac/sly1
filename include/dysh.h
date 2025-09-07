/**
 * @file dysh.h
 *
 * @brief Dynamic shader(?)
 */
#ifndef DYSH_H
#define DYSH_H

#include "common.h"
#include <shadow.h>
#include <flash.h>
#include <mat.h>
#include <cm.h>

// Forward.
struct RPL;

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct DYSH
{
	// ...
};

void InitDysh(DYSH *pdysh);

void SetDyshShadow(DYSH *pdysh, SHADOW *pshadow);

void RenderDyshSelf(DYSH *pdysh, CM *pcm, RO *pro);

void DrawDysh(RPL *prpl);

extern MATRIX4 s_matUvToClip;

#endif // DYSH_H
