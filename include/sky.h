/**
 * @file sky.h
 *
 * @brief Skyboxes.
 */
#ifndef SKY_H
#define SKY_H

#include "common.h"

/**
 * @brief Skybox structure.
 *
 * @todo Fill out the structure.
 */
struct SKY
{
    // ...
};

/**
 * @brief Initializes the sky with default values.
 * Calls super function PostAloLoad().
 *
 * @param psky Pointer to the sky.
 */
void PostSkyLoad(SKY *psky);

/**
 * @brief Updates the given sky.
 *
 * @param psky Pointer to the sky.
 * @param dt Delta time.
 */
void UpdateSky(SKY *psky, float dt);

#endif // SKY_H
