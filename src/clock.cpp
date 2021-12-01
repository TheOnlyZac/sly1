#include <clock.h>

void SetClockEnabled(CLOCK * pclock, int fEnabled)
{
	pClock->fEnabled = fEnabled;
}

void ResetClock(CLOCK * pclock, float t)
{
	pclock->t = t;
}

void MarkClockTick(CLOCK *pclock)
{
	float dt;

	const long tickFrame = /* TickNow(); */ 0 // todo: implement TickNow
	const long deltaFrame = tickFrame - pclock->tickFrame;

	if (deltaFrame < 0) {
		//FUN_001fb6b0(deltaFrame & 1 | deltaFrame >> 1); // todo: implement function
		dt += dt;
	}
	else {
		//FUN_001fb6b0(deltaFrame); // todo: implement function
	}

	dt *= 3.390842e-09;

	if (dt < 0.01666667) {
		dt = 0.01666667;
	}
	else if (0.03333334 < dt) {
		dt = 0.03333334;
	}

	pclock->dtReal = dt;
	float dtFinal = 0.0;

	if (pclock->fEnabled) {
		dtFinal = dt;
	}

	dtFinal = dtFinal * g_rtClockPowerUp * g_rtClock;

	if (0.01666667 <= dtFinal) {
		pclock->dtReal = dtFinal;
	}

	pclock->tickFrame = tickFrame;
	pclock->t = pclock->t + dtFinal;
	pclock->dtPrev = pclock->dt;
	pclock->dt = dtFinal;
	pclock->tReal = pclock->tReal + pclock->dtReal;
}


