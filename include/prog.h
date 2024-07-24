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
    CProg(RGBA *rgbaComplete, RGBA *rgbaRemain, RGBA *rgbaWarning, RGBA *rgbaTrouble);
    void Begin();
    void SetRemain(int nRemain);
    void End();
    void Draw();
};

#endif // PROG_H
