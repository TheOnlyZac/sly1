#include <clock.h>

/* Set magic numbers */
static constexpr int CLOCK_FRAMERATE = 60;
static constexpr float CLOCK_FRAMETIME = 1.f / CLOCK_FRAMERATE;

static constexpr int CLOCK_EE_TICK_RATE = 294912000;
static constexpr float CLOCK_EE_TICK_DURATION = 1.f / CLOCK_EE_TICK_RATE;

/* Init global/static vars */
float g_rtClock = 1.0;
float g_trClockPowerUp = 1.0;
CLOCK g_clock;
TICK CLOCK::s_tickLastRaw{};

/* Set the tick rate of the global clock */
void SetClockRate(float rt)
{
	g_rtClock = rt;
	SetClockEnabled(&g_clock, (0.0 < rt));
	return;
}

/* Calculate and update clock values according to time elapsed */
void MarkClockTick(CLOCK* pclock)
{
	float dt{};

	const TICK tickFrame = TickNow();
	const TICK deltaFrame = tickFrame - pclock->tickFrame;

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

	/* todo: define global variables
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

	TICK tickNow = TickNow();
	TICK deltaTick = tickNow - pClock->tickFrame;

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

/* Reset the real time on the clock to the given t value */
void ResetClock(CLOCK* pclock, float t)
{
	pclock->t = t;
}

/* Set the fEnabled flag on the clock to the given value */
void SetClockEnabled(CLOCK* pclock, bool fEnabled)
{
	pclock->fEnabled = fEnabled;
}

/* Initialize some clock values */
void StartupClock()
{
	/* todo: what is Count?
	CLOCK::s_tickLastRaw = (long)Count; */
	g_clock.tickFrame = TickNow();
}

TICK TickNow()
{
	/* todo: what is Count and cWrapAround.1014?
	TICK countLow = (long)Count & 0xffffffff;
	if (countLow < CLOCK::s_tickLastRaw) {
		cWrapAround.1014 += 1;
	}
	CLOCK::s_tickLastRaw = countLow;
	return cWrapAround.1014 << 0x20 | countLow; */
	return 1.0; // temp
}
