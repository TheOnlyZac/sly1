/**
 * @file prog.h
 */
#ifndef PROG_H
#define PROG_H

#include "common.h"
#include "binoc.h"

class CProg
{
    int m_fActive;
    int m_nMax;
    int m_nTarget;
    int m_nRemain;
    int m_cRetry;
    
    RGBA m_rgbaComplete;
    RGBA m_rgbaRemain;
    RGBA m_rgbaWarning;
    RGBA m_rgbaTrouble;

public:

/**
 * @brief Initializes CProg with RGBA values
 *
 * @param rgbaComplete Unknown
 * @param rgbaRemain Unknown
 * @param rgbaWarning Unknown
 * @param rgbaTrouble Unknown
 */
    CProg(RGBA *rgbaComplete, RGBA *rgbaRemain, RGBA *rgbaWarning, RGBA *rgbaTrouble);
    
/**
 * @brief Zeroes out the variables
 *
 */
    void Begin();
    
/**
 * @brief Clear's Frame Buffers, Updates Remain and calls Draw
 *
 * @param nRemain new Remain value
 */
    void SetRemain(int nRemain);
    
/**
 * @brief Zeroes out the variables
 *
 */
    void End();

/**
 * @brief Unknown
 */
    void Draw();
};

#endif // PROG_H
