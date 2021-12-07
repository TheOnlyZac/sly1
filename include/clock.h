#pragma once

typedef unsigned long long TICK;

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

extern CLOCK g_clock; // global game clock
extern float g_rtClock;

void SetClockRate(float rt);
void MarkClockTick(CLOCK* pclock);
void MarkClockTickRealOnly(CLOCK* pclock);
void ResetClock(CLOCK* pclock, float t);
void SetClockEnabled(CLOCK* pclock, bool fEnabled);
void StartupClock();
TICK TickNow();

//void SetClockDebugRate(int nParam);