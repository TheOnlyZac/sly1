/**
 * @file fader.h
 */
#ifndef FADER_H
#define FADER_H

#include "common.h"
#include <alo.h>

/**
 * @todo Implement the struct.
 */
struct FADER
{
    // ...
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
