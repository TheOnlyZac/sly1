/**
 * @file render.h
 *
 * @brief Declarations for the render system.
*/
#ifndef RENDER_H
#define RENDER_H

#include <sw.h>
#include <cm.h>

/**
 * @brief Renders the SW object.
 *
 * @param psw The object to render.
 * @param pcm The camera to render with.
 *
 * @todo Implement this function.
*/
void RenderSw(SW* psw, CM* pcm);

/**
 * @brief Draws the SW object.
 *
 * @param psw The object to draw.
 * @param pcm The camera to draw with.
 *
 * @todo Implement this function.
*/
void DrawSw(SW* psw, CM* pcm);

#endif // RENDER_H
