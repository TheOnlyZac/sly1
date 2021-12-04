#pragma once

struct CLOCK
{
	bool fEnabled; // clock enabled flag
	float t;
	float dt; // time since last frame
	float dtPrev; // dt from previous frame
	float tReal;
	float dtReal;
	long tickFrame; // todo: type shuld be TICK
};

extern CLOCK g_clock; // global game clock
extern float g_rtClock; // global clock rate

void SetClockEnabled(CLOCK* pclock, bool fEnabled);
void ResetClock(CLOCK* pclock, float t);
void MarkClockTick(CLOCK* pclock);
void SetClockRate(float rt);
unsigned long TickNow(); // todo: return type should be TICK

//void MarkClockTickRealOnly(CLOCK* pclock);
//void SetClockDebugRate(int nParam);
//void StartupClock();