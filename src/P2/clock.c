#include <clock.h>

/*float g_rtClock = 1.0f;
float g_rtClockPowerUp = 1.0f;
struct CLOCK g_clock;
TICK s_tickLastRaw;*/

INCLUDE_ASM(const s32, "P2/clock", SetClockRate__Ff);
/*void SetClockRate(float rt) {
    g_rtClock = rt;
    SetClockEnabled(&g_clock, rt > 0.0f);
}*/

INCLUDE_ASM(const s32, "P2/clock", MarkClockTick);

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

INCLUDE_ASM(const s32, "P2/clock", TickNow);
INCLUDE_ASM(const s32, "P2/clock", func_00143140); // empty, not really a function
