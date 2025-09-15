/**
 * @file sqtr.h
 */
#ifndef SQTR_H
#define SQTR_H

#include "common.h"
#include <render.h>
#include <vec.h>
#include <mat.h>
#include <cm.h>

/**
 * @brief Unknown.
 * @todo Implement the struct.
 */
struct SQTRM
{
    // ...
};

void UpdateSqtrm(SQTRM *psqtrm, VECTOR *ppos, MATRIX3 *pmat, float swExtra, float dt);

void RenderSqtrm(SQTRM *psqtrm, CM *pcm);

void DrawSqtrm(RPL *prpl);

#endif SQTR_H
