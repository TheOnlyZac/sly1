#include <clock.h>

#include <cassert>

int main()
{
	SetClockRate(1.0);
	assert(g_rtClock == 1.0f);
	assert(g_clock.fEnabled == 1);

	SetClockRate(0.5);
	assert(g_rtClock == 0.5f);
	assert(g_clock.fEnabled = 1);

	SetClockRate(0);
	assert(g_rtClock == 0.f);
	assert(g_clock.fEnabled == 0);

	SetClockRate(-1);
	assert(g_rtClock == -1.f);
	assert(g_clock.fEnabled == 0);

	return 0;
}
