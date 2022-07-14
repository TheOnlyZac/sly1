#include <clock.h>

#include <test/test.h>

int main()
{
	SetClockRate(1.0);
	JtAssert(g_rtClock == 1.0f);
	JtAssert(g_clock.fEnabled);

	SetClockRate(0.5);
	JtAssert(g_rtClock == 0.5f);
	JtAssert(g_clock.fEnabled);

	SetClockRate(0);
	JtAssert(g_rtClock == 0.f);
	JtAssert(!g_clock.fEnabled);

	SetClockRate(-1);
	JtAssert(g_rtClock == -1.f);
	JtAssert(!g_clock.fEnabled);

	return 0;
}
