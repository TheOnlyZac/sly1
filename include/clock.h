/**
 * @file clock.h
 *
 * @brief Engine clock
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
    float t;
    float dt;	  // time since last frame
    float dtPrev; // dt from previous frame
    float tReal;  // t factoring in EE clock cyclerate
    float dtReal; // dt factoring in EE clock cyclerate
    TICK tickFrame;
};

void SetClockRate(float rt);
void ResetClock(CLOCK *pclock, float t);
void SetClockEnabled(CLOCK *pclock, int fEnabled);

extern float g_rtClock;
extern float g_rtClockPowerUp;
extern struct CLOCK g_clock;
extern TICK s_tickLastRaw;

#endif // CLOCK_H
