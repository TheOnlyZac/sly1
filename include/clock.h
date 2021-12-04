#pragma once

struct CLOCK
{
	bool fEnabled; // clock enabled flag
	float t;
	float dt; // time since last frame
	float dtPrev; // dt from previous frame
	float tReal; // t factoring in EE clock cyclerate
	float dtReal; // dt factoring in EE clock cyclerate
	long tickFrame; // todo: type shuld be TICK
};

extern CLOCK g_clock; // global game clock

void SetClockRate(float rt);
void MarkClockTick(CLOCK* pclock);
void MarkClockTickRealOnly(CLOCK* pclock);
void ResetClock(CLOCK* pclock, float t);
void SetClockEnabled(CLOCK* pclock, bool fEnabled);
void StartupClock();
unsigned long TickNow(); // todo: return type should be TICK

//void SetClockDebugRate(int nParam);