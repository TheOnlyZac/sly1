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
#include <gifs.h>

/**
 * @brief Unknown.
 */
enum RP
{
    RP_Nil = -1,
    RP_DynamicTexture = 0,
    RP_Background = 1,
    RP_BlotContext = 2,
    RP_Opaque = 3,
    RP_Cutout = 4,
    RP_CelBorder = 5,
    RP_ProjVolume = 6,
    RP_OpaqueAfterProjVolume = 7,
    RP_CutoutAfterProjVolume = 8,
    RP_CelBorderAfterProjVolume = 9,
    RP_MurkClear = 10,
    RP_MurkOpaque = 11,
    RP_MurkFill = 12,
    RP_Translucent = 13,
    RP_TranslucentCelBorder = 14,
    RP_Blip = 15,
    RP_Foreground = 16,
    RP_WorldMap = 17,
    RP_Max = 18
};

/**
 * @brief Render Primitive List (?)
 * @todo Implement the struct.
 */
struct RPL
{
    undefined4 *pfndraw; // NOTE: This is a function pointer.
    float z;
    RP rp;
    // ...
};

void SubmitRpl(RPL *prpl);

int NCmpPrplReverseZ(RPL **pprpl1, RPL **pprpl2);

int CprplPartitionArpl(int cprpl, RPL *arpl, RPL **aprpl);

/**
 * @brief Renders the given SW with the given camera.
 *
 * @param psw Pointer to the SW object.
 * @param pcm Pointer to the camera.
 */
void RenderSw(SW *psw, CM *pcm);

void EnsureRenderGlobals();

void EnsureCameraGlobals();

void EnsureScreenCleared();

void SetupRpDynamicTexture(RPL *prpl);

void SetupRpBackground(RPL *prpl);

void SetupRpBlotContext(RPL *prpl);

void SetupRpGlob(RPL *prpl);

void SetupRpBlip(RPL *prpl);

void SetupRpWorldMap(RPL *prpl);

/**
 * @brief Draws the given SW with the given camera.
 *
 * @param psw Pointer to the SW object.
 * @param pcm Pointer to the camera.
 */
void DrawSw(SW *psw, CM *pcm);

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

/**
 * @briefs Starts up the rendering system.
 */
void StartupRender();

#endif // RENDER_H
