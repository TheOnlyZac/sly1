/**
 * @file phasemem.h
 */
#ifndef PHASEMEM_H
#define PHASEMEM_H

#include "common.h"

enum PHASE {
    PHASE_Nil = -1,
    PHASE_None = 0x0,
    PHASE_Startup = 0x1,
    PHASE_Load = 0x2,
    PHASE_Main = 0x3,
    PHASE_Mpeg = 0x4,
    PHASE_Max = 0x5
};

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
