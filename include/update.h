/**
 * @file update.h
 */
#ifndef UPDATE_H
#define UPDATE_H

#include "common.h"
#include <sw.h>

/**
 * @brief Updates all objects in the given SW.
 *
 * @param psw The SW to update.
 * @param dt Delta time.
 */
void UpdateSwObjects(SW *psw, float dt);

void UpdateSwPosWorldPrev(SW *psw);

void UpdateSwRealClock(SW *psw, float dt);

void UpdateSwDarkening(SW *psw, float dt);

/**
 * @brief Updates the given SW.
 *
 * @param psw The SW to update.
 * @param dt Delta time.
 */
void UpdateSw(SW *psw, float dt);

#endif // UPDATE_H
