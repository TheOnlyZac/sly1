#include <clock.h>

/* Magic numbers */
static constexpr int CLOCK_FRAMERATE = 60;
static constexpr float CLOCK_FRAMETIME = 1.f / CLOCK_FRAMERATE;

static constexpr int CLOCK_EE_TICK_RATE = 294912000;
static constexpr float CLOCK_EE_TICK_DURATION = 1.f / CLOCK_EE_TICK_RATE;

/* Global variables */
float g_rtClock = 1.0;
float g_trClockPowerUp = 1.0;
CLOCK g_clock;
long s_tickLastRaw{}; // this name suggests it should be a static class member

void StartupClock()
{
	/* todo: what is Count?
	s_tickLastRaw = (long)Count; */
	g_clock.tickFrame = TickNow();
}

unsigned long TickNow()
{
	/* todo: define globals
	unsigned long mask = (long)Count & 0xffffffff;
	if (mask < s_tickLastRaw) {
		cWrapAround.1014 = cWrapAround.1014 + 1;
	}
	s_tickLastRaw = mask;
	return cWrapAround.1014 << 0x20 | mask; */
	return 1.0; // temp
}

/* Set the fEnabled flag on the clock to the given value */
void SetClockEnabled(CLOCK* pclock, bool fEnabled)
{
	pclock->fEnabled = fEnabled;
}

/* Reset the real time on the clock to the given t value */
void ResetClock(CLOCK* pclock, float t)
{
	pclock->t = t;
}

/* Calculate and update clock values according to time elapsed */
void MarkClockTick(CLOCK* pclock)
{
	float dt{};

	const long tickFrame = TickNow();
	const long deltaFrame = tickFrame - pclock->tickFrame;

	if (deltaFrame < 0) {
		/* todo: implement function
		__floatdisf(deltaFrame & 1 | deltaFrame >> 1); */
		dt += dt;
	}
	else {
		/* todo: implement function
		__floatdisf(deltaFrame); */
	}

	dt *= CLOCK_EE_TICK_DURATION;

	if (dt < CLOCK_FRAMETIME) {
		dt = CLOCK_FRAMETIME;
	}
	else if (CLOCK_FRAMETIME * 2 < dt) {
		dt = CLOCK_FRAMETIME * 2;
	}

	pclock->dtReal = dt;
	float dtFinal{};

	if (pclock->fEnabled) {
		dtFinal = dt;
	}

	/* todo: add global variables
	dtFinal = dtFinal * g_rtClockPowerUp * g_rtClock; */

	if (CLOCK_FRAMETIME <= dtFinal) {
		pclock->dtReal = dtFinal;
	}

	pclock->tickFrame = tickFrame;
	pclock->t = pclock->t + dtFinal;
	pclock->dtPrev = pclock->dt;
	pclock->dt = dtFinal;
	pclock->tReal = pclock->tReal + pclock->dtReal;
}

/* Calculate and update real clock values according to EE cyclerate */
void MarkClockTickRealOnly(CLOCK* pClock)
{
	float dtReal{};

	unsigned long tickNow = TickNow();
	unsigned long deltaTick = tickNow - pClock->tickFrame;

	if (deltaTick < 0)
	{
		/* todo: implement function
		__floatdisf(deltaTick & 1 | deltaTick >> 1); */
		dtReal += dtReal;
	}
	else
	{
		/* todo: implement function
		__floatdisf(deltaTick); */
	}

	pClock->tickFrame = tickNow;
	pClock->dtReal = dtReal * CLOCK_EE_TICK_DURATION;
	pClock->tReal = pClock->tReal + dtReal * CLOCK_EE_TICK_DURATION;
}

/* Set the tick rate of the global clock */
void SetClockRate(float rt)
{
	g_rtClock = rt;
	SetClockEnabled(&g_clock, (0.0 < rt));
	return;
}
