/**
 * @file phasemem.h
 *
 * @brief Declarations for the phase system.
*/
#pragma once

/**
 * @brief Game Phase
*/
enum PHASE
{
	PHASE_None = 0,
	PHASE_Startup = 0x1,
	PHASE_Load = 1,
	PHASE_Main = 2,
	PHASE_Mpeg = 4,
	PHASE_Max = 5
};

// Global variables
static PHASE g_phase; // Current game phase
static void* g_phasemem; // todo: fix type

/**
 * @brief Sets the current game phase.
*/
void SetPhase(PHASE phase);

/**
 * @brief Clears the current game phase.
*/
void ClearPhase(PHASE phase = PHASE_None);
