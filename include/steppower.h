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
    FSP_Ball = 1,
    FSP_SlowDownClock = 2,
    FSP_Mine = 3,
    FSP_SpeedUpClock = 4,
    FSP_Decoy = 5,
    FSP_Stun = 6,
    FSP_Max = 7
};

extern FSP g_fsp;

/*static const char *s_mpfspachz[] = {
    "&2T&.: Dive",
    "&2T&.: Roll",
    "&2T&.: Slow",
    "&2T&.: Mine",
    "&2T&.: Fast",
    "&2T&.: Decoy",
    "&2T&.: Stun"
};*/
extern const char *s_mpfspachz[];

extern float RT_JtSpeedUpClock;
extern float RT_JtSlowDownClock;

/**
 * @brief Set the selected powerup.
 *
 * @param fsp Bitflags representing a certain powerup.
 */
void SetFsp(FSP fsp);

/**
 * @brief Update the currently selected powerup.
 *
 * @param pjt Pointer to the jt to update.
 * @param pjoy Pointer to the joypad input.
 */
void UpdateJtActivePowerUp(JT *pjt, JOY *pjoy);

/**
 * @brief Rotate the selected powerup, making the next one in the cycle active.
 *
 * @param pjoy Pointer to the joypad input.
 * @param iCur Current powerup index.
 * @param iMax Maximum powerup index.
 * @param mpigrfvault Array of integer bitflags representing which powerups are available.
 *
 * @return Index of the newly active powerup.
 */
int IRotatePowerUp(JOY *pjoy, int iCur, int iMax, int *mpigrfvault);

#endif // STEPPOWER_H
