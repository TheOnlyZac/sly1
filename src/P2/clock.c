/**
 * @file clock.cpp
 *
 * @brief Implements the game clock.
*/
#include <clock.h>

/**
 * Set magic numbers
*/
static const int CLOCK_FRAMERATE = 60; // 60 FPS
static const float CLOCK_FRAMETIME = 1.f / CLOCK_FRAMERATE; // 1/60th of a second

static const int CLOCK_EE_TICK_RATE = 294912000; // 294.912 MHz
static const float CLOCK_EE_TICK_DURATION = 1.f / CLOCK_EE_TICK_RATE; // 1/294.912 MHz

/**
 * Init global/static vars
*/
float g_rtClock = 1.0;
float g_trClockPowerUp = 1.0;
CLOCK g_clock;
TICK CLOCK::s_tickLastRaw = 0;

void SetClockRate(float rt)
{
	// Set global clock rate
	g_rtClock = rt;

	// Enable clock if rate > 0
	SetClockEnabled(&g_clock, (0.0 < rt));
}

void MarkClockTick(CLOCK* pclock)
{
	float dt = 0.0f;

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
	float dtFinal = 0.0f;;

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

void MarkClockTickRealOnly(CLOCK* pClock)
{
	float dtReal = 0.0f;

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

/**
 * @note Matching 100%
*/
void ResetClock(CLOCK* pclock, float t)
{
	pclock->t = t;
}

/**
 * @note Matching 100%
*/
void SetClockEnabled(CLOCK* pclock, int fEnabled)
{
	pclock->fEnabled = fEnabled;
}

/**
 * @todo What is Count?
*/
void StartupClock()
{
	/* todo: what is Count?
	CLOCK::s_tickLastRaw = (long)Count; */
	g_clock.tickFrame = TickNow();
}

/**
 * @todo What is Count? What is cWrapAround.1014?
*/
TICK TickNow()
{
	/*
	TICK countLow = (long)Count & 0xffffffff;
	if (countLow < CLOCK::s_tickLastRaw) {
		cWrapAround.1014 += 1;
	}
	CLOCK::s_tickLastRaw = countLow;
	return cWrapAround.1014 << 0x20 | countLow;
	*/
	return 1.0; // temp
}
