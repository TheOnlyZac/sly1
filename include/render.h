/**
 * @file render.h
 *
 * @brief Rendering system.
 */
#ifndef RENDER_H
#define RENDER_H

#include "common.h"
#include <sw.h>
#include <cm.h>

/**
 * @brief Renders the given SW with the given camera.
 */
void RenderSw(SW *psw, CM *pcm);

/**
 * @brief Draws the given SW with the given camera.
 */
void DrawSw(SW *psw, CM *pcm);

#endif // RENDER_H
