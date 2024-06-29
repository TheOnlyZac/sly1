#include <clock.h>

void SetClockRate(float rt)
{
	// Set global clock rate
	g_rtClock = rt;

	// Enable clock if rate > 0
	SetClockEnabled(&g_clock, (0.0 < rt));
}

INCLUDE_ASM(const s32, "P2/clock", MarkClockTick);

INCLUDE_ASM(const s32, "P2/clock", MarkClockTickRealOnly);

void ResetClock(struct CLOCK* pclock, float t)
{
	pclock->t = t;
}

void SetClockEnabled(struct CLOCK* pclock, int fEnabled)
{
	pclock->fEnabled = fEnabled;
}

INCLUDE_ASM(const s32, "P2/clock", StartupClock);

INCLUDE_ASM(const s32, "P2/clock", TickNow);

void func_00143140(void) {
}
