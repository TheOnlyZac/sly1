#pragma once

struct CLOCK
{
	int fEnabled; // bool?
	float t;
	float dt; // time since last frame
	float dtPrev;
	float tReal;
	float dtReal;
	long tickFrame; // todo: type shuld be TICK
};

extern CLOCK g_clock;
extern float g_rtClock;

void SetClockEnabled(CLOCK* pclock, int fEnabled);
void ResetClock(CLOCK* pclock, float t);
void MarkClockTick(CLOCK* pclock);
void SetClockRate(float rt);

//void MarkClockTickRealOnly(CLOCK* pclock);
//void SetClockDebugRate(int nParam);
//void StartupClock();
//TICK TickNow();