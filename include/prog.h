/**
 * @file prog.h
 *
 * @brief Progress bar.
 */
#ifndef PROG_H
#define PROG_H

#include "common.h"
#include <binoc.h>
#include <gs.h>

class CProg
{
    int m_fActive; // 0
    int m_nMax; // 4
    int m_nTarget; // 8
    int m_nRemain; // c
    int m_cRetry; // 10

    RGBA m_rgbaComplete; // 14
    RGBA m_rgbaRemain; // 18
    RGBA m_rgbaWarning; // 1c
    RGBA m_rgbaTrouble; // 20

public:
    /**
     * @brief Initializes CProg with RGBA values.
     *
     * @param rgbaComplete Color of the filled portion of the bar (e.g. blue or green).
     * @param rgbaRemain Color of the unfilled portion of the bar (e.g. gray).
     * @param rgbaWarning Color of the bar if there's a warning (e.g. yellow).
     * @param rgbaTrouble Color of the bar if there's trouble (e.g. red)
     */
    CProg(RGBA *rgbaComplete, RGBA *rgbaRemain, RGBA *rgbaWarning, RGBA *rgbaTrouble);

    /**
     * @brief Zeroes out the variables.
     *
     */
    void Begin();

    /**
     * @brief Clear's Frame Buffers, updates remain and calls draw.
     *
     * @param nRemain new Remain value.
     */
    void SetRemain(int nRemain);

    /**
     * @brief Zeroes out the variables.
     *
     */
    void End();

    /**
     * @brief Draws the progress bar on the screen with the current colors.
     */
    void Draw();
};

#endif // PROG_H
