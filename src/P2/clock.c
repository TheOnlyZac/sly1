#include <clock.h>

/*float g_rtClock = 1.0f;
float g_rtClockPowerUp = 1.0f;
struct CLOCK g_clock;
TICK s_tickLastRaw;*/

INCLUDE_ASM(const s32, "P2/clock", SetClockRate);

INCLUDE_ASM(const s32, "P2/clock", MarkClockTick);

INCLUDE_ASM(const s32, "P2/clock", MarkClockTickRealOnly);

void ResetClock(struct CLOCK *pclock, float t)
{
	pclock->t = t;
}

void SetClockEnabled(struct CLOCK *pclock, int fEnabled)
{
	pclock->fEnabled = fEnabled;
}

INCLUDE_ASM(const s32, "P2/clock", StartupClock);

INCLUDE_ASM(const s32, "P2/clock", TickNow);

void func_00143140(void)
{
}
