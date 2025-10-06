/**
 * @file phasemem.h
 */
#ifndef PHASEMEM_H
#define PHASEMEM_H

#include "common.h"

/**
 * @brief Engine phase.
 */
enum PHASE
{
    PHASE_Nil = -1,
    PHASE_None = 0,
    PHASE_Startup = 1,
    PHASE_Load = 2,
    PHASE_Main = 3,
    PHASE_Mpeg = 4,
    PHASE_Max = 5
};

/**
 * @brief Current engine phase.
 */
extern PHASE g_phase;

/**
 * @brief Set the current engine phase.
 */
void SetPhase(PHASE phase);

/**
 * @brief Clear the current engine phase.
 */
void ClearPhase(PHASE phase);

#endif // PHASEMEM_H
