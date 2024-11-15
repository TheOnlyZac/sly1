/**
 * @file clock.h
 *
 * @brief Engine clock.
 */
#ifndef CLOCK_H
#define CLOCK_H

#include "common.h"

typedef unsigned long long TICK;

/**
 * @brief Engine clock.
 */
struct CLOCK
{
    int fEnabled; // clock enabled flag
    float t;      // current time
    float dt;     // time since last frame
    float dtPrev; // dt from previous frame
    float tReal;  // t factoring in EE clock cyclerate
    float dtReal; // dt factoring in EE clock cyclerate
    TICK tickFrame;
};

extern float D_0024CD4C;

extern float g_rtClock;
extern float g_rtClockPowerUp;
extern CLOCK g_clock;
//extern TICK s_tickLastRaw;; // Should be static?

/**
 * @brief Sets the rate of the global clock.
 *
 * @param rt The new tick rate.
 */
void SetClockRate(float rt);

/**
 * @brief Updates clock values based to time elapsed.
 *
 * @param pclock Pointer to the clock.
 */
void MarkClockTick(CLOCK *pclock);

/**
 * @brief Updates clock values based to time elapsed.
 *
 * Only updates the real clock values (those determined by the EE clock cyclerate).
 *
 * @param pclock Pointer to the clock.
 */
void MarkClockTickRealOnly(CLOCK *pClock);

/**
 * @brief Resets the clock to the given time t.
 *
 * @param pclock Pointer to the clock.
 * @param t Time to set.
 */
void ResetClock(CLOCK *pclock, float t);

/**
 * @brief Sets the fEnabled flag on the clock to the given value.
 *
 * @param pclock Pointer to the clock.
 * @param fEnabled 1 to enable, 0 to disable.
 */
void SetClockEnabled(CLOCK *pclock, int fEnabled);

/**
 * @brief Initializes and enables the global clock.
 */
void StartupClock();

/**
 * @brief Gets the current tick.
 *
 * @return The current tick.
 */
const TICK TickNow();

#endif // CLOCK_H
