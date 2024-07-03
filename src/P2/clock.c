#include <clock.h>

/*float g_rtClock = 1.0f;
float g_rtClockPowerUp = 1.0f;
struct CLOCK g_clock;
TICK s_tickLastRaw;*/

static const int CLOCK_FRAMERATE = 60;						// 60 FPS
static const float CLOCK_FRAMETIME = 1.f / CLOCK_FRAMERATE; // 1/60th of a second

static const int CLOCK_EE_TICK_RATE = 294912000;					  // 294.912 MHz
static const float CLOCK_EE_TICK_DURATION = 1.f / CLOCK_EE_TICK_RATE; // 1/294.912 MHz

void SetClockRate(float rt)
{
	g_rtClock = rt;
	SetClockEnabled(&g_clock, rt > 0.0f);
}

void MarkClockTick(CLOCK *pclock)
{
	const TICK tickFrame = TickNow();
	const TICK deltaTick = tickFrame - pclock->tickFrame;

	float dt = deltaTick * CLOCK_EE_TICK_DURATION;
	float t1 = CLOCK_FRAMETIME * 2;

	if (dt < CLOCK_FRAMETIME)
	{
		dt = CLOCK_FRAMETIME;
	}
	else if (t1 < dt)
	{
		dt = t1;
	}

	pclock->dtReal = dt;
	float dtFinal = 0.0f;

	if (pclock->fEnabled)
	{
		dtFinal = dt;
	}

	dtFinal *= g_rtClockPowerUp * g_rtClock;

	if (CLOCK_FRAMETIME <= dtFinal)
	{
		pclock->dtReal = dtFinal;
	}

	pclock->t += dtFinal;
	pclock->dtPrev = pclock->dt;
	pclock->dt = dtFinal;
	pclock->tReal += pclock->dtReal;
	pclock->tickFrame = tickFrame;
}

INCLUDE_ASM(const s32, "P2/clock", MarkClockTickRealOnly);

void ResetClock(CLOCK *pclock, float t)
{
	pclock->t = t;
}

void SetClockEnabled(CLOCK *pclock, int fEnabled)
{
	pclock->fEnabled = fEnabled;
}

INCLUDE_ASM(const s32, "P2/clock", StartupClock);

INCLUDE_ASM(const s32, "P2/clock", TickNow__Fv);
INCLUDE_ASM(const s32, "P2/clock", func_00143140); // empty, not really a function
