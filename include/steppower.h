/**
 * @file steppower.h
 */
#ifndef STEPPOWER_H
#define STEPPOWER_H

#include "common.h"
#include <joy.h>

/**
 * @brief Rotate the current powerup.
 */
int IRotatePowerUp(JOY *pjoy,int iCur,int iMax,int *mpigrfvault);

#endif // STEPPOWER_H
