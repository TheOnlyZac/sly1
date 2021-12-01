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

void SetClockEnabled(CLOCK* pclock, int fEnabled);
void ResetClock(CLOCK* pclock, float t);
void MarkClockTick(CLOCK* pclock);

//void MarkClockTickRealOnly(CLOCK* pclock);
//void SetClockDebugRate(int nParam);
//void SetClockRate(float rt);
//void StartupClock();
//TICK TickNow();