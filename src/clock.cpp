#include <clock.h>

void SetClockEnabled(CLOCK * pclock, int fEnabled)
{
	pClock->fEnabled = fEnabled;
}

void ResetClock(CLOCK * pclock, float t)
{
	pclock->t = t;
}
