/**
 * @file update.h
 *
 * @brief Declarations for functions that update game elements.
*/
#ifndef UPDATE_H
#define UPDATE_H

#include <sw.h>

/**
 * @brief Updates the objects in the SW struct.
 *
 * @param psw The SW struct to update
 * @param dt Delta time
*/
void UpdateSwObjects(SW* psw, float dt);

#endif // UPDATE_H
