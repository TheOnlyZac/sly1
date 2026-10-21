/**
 * @file fader.h
 */
#ifndef FADER_H
#define FADER_H

#include "common.h"
#include <alo.h>

/**
 * @brief Fader.
 */
struct FADER
{
    /* 0x00 */ ALO *palo;
    /* 0x04 */ float uAlpha;
    /* 0x08 */ float duAlpha;
    /* 0x0c */ DLE dle;
};

/**
 * @brief Update the fader.
 */
void UpdateFader(FADER *pfader, float dt);

/**
 * @brief Create a new fader.
 */
FADER *PfaderNew(ALO *palo);

/**
 * @brief Remove the fader.
 */
void RemoveFader(FADER *pfader);

#endif // FADER_H
