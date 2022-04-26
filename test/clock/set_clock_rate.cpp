#include <clock.h>
#include "../assert.h"

int main()
{
	SetClockRate(1.0);
	assert(g_rtClock == 1.0f);
	assert(g_clock.fEnabled == true);

	SetClockRate(0.5);
	assert(g_rtClock == 0.5f);
	assert(g_clock.fEnabled == true);

	SetClockRate(0);
	assert(g_rtClock == 0.f);
	assert(g_clock.fEnabled == false);

	SetClockRate(-1);
	assert(g_rtClock == -1.f);
	assert(g_clock.fEnabled == false);

	return 0;
}
