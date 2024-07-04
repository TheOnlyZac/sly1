/**
 * @file steppower.h
 */
#ifndef STEPPOWER_H
#define STEPPOWER_H

#include "common.h"
#include <jt.h>
#include <joy.h>

/**
 * @brief Selected powerup flags.
 */
enum FSP
{
    FSP_Nil = -1,
    FSP_Dive = 0,
    FSP_SpeedUpClock = 1,
    FSP_SlowDownClock = 2,
    FSP_Ball = 3,
    FSP_Max = 4
};

/**
 * @brief Set the selected powerup.
 */
void SetFsp(FSP fsp);

/**
 * @brief Update the currently selected powerup.
 */
void UpdateJtActivePowerUp(JT *pjt, JOY *pjoy);

/**
 * @brief Rotate the selected powerup.
 */
int IRotatePowerUp(JOY *pjoy, int iCur, int iMax, int *mpigrfvault);

#endif // STEPPOWER_H
