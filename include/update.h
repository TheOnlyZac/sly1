/**
 * @file update.h
 */
#ifndef UPDATE_H
#define UPDATE_H

#include "common.h"
#include <sw.h>

// ...

/**
 * @brief Updates all objects in the given SW.
 *
 * @param psw The SW to update.
 * @param dt Delta time.
 */
void UpdateSwObjects(SW *psw, float dt);

// ...

#endif // UPDATE_H
