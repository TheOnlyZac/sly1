#include <clock.h>

/* Initialize global values */
CLOCK g_clock;
float g_rtClock = 1.0;

/* Set the fEnabled flag on the clock to the given value */
void SetClockEnabled(CLOCK * pclock, int fEnabled)
{
	pclock->fEnabled = fEnabled;
}

/* Reset the real time on the clock to the given t value */
void ResetClock(CLOCK * pclock, float t)
{
	pclock->t = t;
}

/* Calculate and update clock values according to time passed */
void MarkClockTick(CLOCK *pclock)
{
	float dt;

	const long tickFrame = /* TickNow() */ 0; // todo: implement TickNow
	const long deltaFrame = tickFrame - pclock->tickFrame;

	if (deltaFrame < 0) {
		/* todo: implement function
		FUN_001fb6b0(deltaFrame & 1 | deltaFrame >> 1); */
		dt += dt;
	}
	else {
		/* todo: implement function
		FUN_001fb6b0(deltaFrame); */
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

	/* todo: add global variables
	dtFinal = dtFinal * g_rtClockPowerUp * g_rtClock; */

	if (0.01666667 <= dtFinal) {
		pclock->dtReal = dtFinal;
	}

	pclock->tickFrame = tickFrame;
	pclock->t = pclock->t + dtFinal;
	pclock->dtPrev = pclock->dt;
	pclock->dt = dtFinal;
	pclock->tReal = pclock->tReal + pclock->dtReal;
}

/* Set the tick rate of the global clock */
void SetClockRate(float rt)
{
	g_rtClock = rt;
	SetClockEnabled(&g_clock, (int)(0.0 < rt));
	return;
}