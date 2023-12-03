/**
 * @file clock.h
 *
 * @brief Declarations for the game clock.
*/
#ifndef CLOCK_H
#define CLOCK_H

typedef unsigned long long TICK;

/**
 * @brief Game Clock
*/
struct CLOCK
{
	static TICK s_tickLastRaw;

	bool fEnabled; // clock enabled flag
	float t;
	float dt; // time since last frame
	float dtPrev; // dt from previous frame
	float tReal; // t factoring in EE clock cyclerate
	float dtReal; // dt factoring in EE clock cyclerate
	TICK tickFrame;
};

// Global variables
extern CLOCK g_clock; // Main game clock
extern float g_rtClock; // Clock tick rate

/**
 * @brief Sets the tick rate of the global clock.
 *
 * @param rt The new tick rate.
*/
void SetClockRate(float rt);

/**
 * @brief Calculates and updates clock values according to time elapsed.
 *
 * @param pclock Pointer to the clock.
*/
void MarkClockTick(CLOCK* pclock);

/**
 * @brief Calculates and updates clock values according to time elapsed.
 *
 * Only updates the real clock values (those which are determined by the EE clock cyclerate).
 *
 * @param pclock Pointer to the clock.
*/
void MarkClockTickRealOnly(CLOCK* pclock);

/**
 * @brief Resets the clock to the given time.
 *
 * @param pclock Pointer to the clock.
 * @param t The new time.
*/
void ResetClock(CLOCK* pclock, float t);

/**
 * @brief Sets the fEnabled flag on the clock to the given value.
 *
 * @param pclock Pointer to the clock.
 * @param fEnabled The new value of the fEnabled flag.
*/
void SetClockEnabled(CLOCK* pclock, bool fEnabled);

/**
 * @brief Initializes some values and starts the global clock.
*/
void StartupClock();

/**
 * @brief Gets the current tick.
 *
 * @return The current tick.
*/
TICK TickNow();

/**
 * @brief Sets the debug rate of the global clock.
 *
 * @param nParam The new debug rate.
 *
 * @todo Implement this function.
*/
//void SetClockDebugRate(int nParam);

#endif // CLOCK_H
