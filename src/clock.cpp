#include <clock.h>

/* Magic numbers */
static constexpr int CLOCK_FRAMERATE = 60;
static constexpr float CLOCK_FRAMETIME = 1.f / CLOCK_FRAMERATE;

static constexpr int CLOCK_EE_TICK_RATE = 294912000;
static constexpr float CLOCK_EE_TICK_DURATION = 1.f / CLOCK_EE_TICK_RATE;

/* Global variables */
CLOCK g_clock;
float g_rtClock = 1.0;

/* Set the fEnabled flag on the clock to the given value */
void SetClockEnabled(CLOCK * pclock, bool fEnabled)
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
	float dt{};

	const long tickFrame{}; /* = TickNow(); */ // todo: implement TickNow
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

/* Set the tick rate of the global clock */
void SetClockRate(float rt)
{
	g_rtClock = rt;
	SetClockEnabled(&g_clock, (0.0 < rt));
	return;
}