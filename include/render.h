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
#include <dmas.h>

struct GIFS : DMAS
{
    undefined4 unk_0x4;
    uint m_creg;
    uint m_cregAll;

    void AddPrimEnd();
};

/**
 * @brief Renders the given SW with the given camera.
 *
 * @param psw Pointer to the SW object.
 * @param pcm Pointer to the camera.
 */
void RenderSw(SW *psw, CM *pcm);

/**
 * @brief Draws the given SW with the given camera.
 *
 * @param psw Pointer to the SW object.
 * @param pcm Pointer to the camera.
 */
void DrawSw(SW *psw, CM *pcm);

// ...

/**
 * @brief Fills a rectangular area of the screen with a specified color and alpha value.
 *
 * @param r The red component of the fill color (0-255).
 * @param g The green component of the fill color (0-255).
 * @param b The blue component of the fill color (0-255).
 * @param alpha The alpha (transparency) value of the fill (0-255).
 * @param xLeft The left x-coordinate of the rectangle.
 * @param yTop The top y-coordinate of the rectangle.
 * @param xRight The right x-coordinate of the rectangle.
 * @param yBottom The bottom y-coordinate of the rectangle.
 * @param pgifs Pointer to a GIFS structure used for rendering.
 */
void FillScreenRect(int r, int g, int b, int alpha, float xLeft, float yTop, float xRight, float yBottom, GIFS *pgifs);

// ...

#endif // RENDER_H
