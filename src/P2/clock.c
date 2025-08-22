#include <clock.h>

// constants
static const int CLOCK_FRAMERATE = 60; // 60 FPS
static const float CLOCK_FRAMETIME = 1.f / CLOCK_FRAMERATE; // 1/60th of a second

static const int CLOCK_EE_TICK_RATE = 294912000; // 294.912 MHz
static const float CLOCK_EE_TICK_DURATION = 1.f / CLOCK_EE_TICK_RATE; // 1/294.912 MHz

// data
float g_rtClock = 1.0f;
float g_rtClockPowerUp = 1.0f;
CLOCK g_clock = { 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0 };
TICK s_tickLastRaw; // Should be static?
ulong cWrapAround; // Checksum doesn't like. (tried types: ptr cast, static, extern, uint64, uint64_t, ulong, ulonglong)

// text
void SetClockRate(float rt) {
    g_rtClock = rt;
    SetClockEnabled(&g_clock, rt > 0.0f);
}

void MarkClockTick(CLOCK* pclock)
{
	float dt;
	float t1;

	const TICK tickFrame = TickNow();
	const TICK deltaTick = tickFrame - pclock->tickFrame;

	dt = deltaTick * CLOCK_EE_TICK_DURATION;

    t1 = CLOCK_FRAMETIME * 2;

	if (dt < CLOCK_FRAMETIME) {
		dt = CLOCK_FRAMETIME;
	}
	else if (t1 < dt) {
		dt = t1;
	}

	pclock->dtReal = dt;

	float dtFinal = 0.0f;

	if (pclock->fEnabled) {
		dtFinal = dt;
	}

	dtFinal *= g_rtClockPowerUp * g_rtClock;

	if (CLOCK_FRAMETIME <= dtFinal) {
		pclock->dtReal = dtFinal;
	}

	pclock->t += dtFinal;
	pclock->dtPrev = pclock->dt;
	pclock->dt = dtFinal;
	pclock->tReal += pclock->dtReal;
	pclock->tickFrame = tickFrame;
}

void MarkClockTickRealOnly(CLOCK *pclock)
{
	const TICK tickFrame = TickNow();
	const TICK deltaTick = tickFrame - pclock->tickFrame;
	float dt = deltaTick * CLOCK_EE_TICK_DURATION;

	pclock->dtReal = dt;
	pclock->tReal += pclock->dtReal;
	pclock->tickFrame = tickFrame;
}

void ResetClock(CLOCK *pclock, float t)
{
	pclock->t = t;
}

void SetClockEnabled(CLOCK *pclock, int fEnabled)
{
	pclock->fEnabled = fEnabled;
}

void StartupClock() 
{
    //	Count is the MIPS DeltaTime, its handled in the CP0. "Count increments automatically every EE cycle." 
	// https://psi-rockin.github.io/ps2tek/#eecop0timer:~:text=%2409%20%2D%20COP0.Count,every%20EE%20cycle -Zryu
	ulong ulCountValue;
    __asm__ volatile ("mfc0 %0, $9" : "=r"(ulCountValue)); // Asm function that puts $9 (c0_count) from CP0 into $a0.

    s_tickLastRaw = (TICK)ulCountValue; 
    g_clock.tickFrame = TickNow();
}

/**
 * Matched 100%. Checksum doesn't like cWrapAround variable.
 *
 *
*/
const TICK TickNow()
{
    ulong ulCountLow;  // Lower 32 bits of the tick result.
    ulong ulMask;      // Mask for tick value.
    ulong ulValue;     // MIPS tick in coprocessor 0 (reg 9 Count)

    // Get Count from CP0 reg 9
    __asm__ volatile (
    "mfc0 %0, $9" : "=r"(ulValue)
    );

    // Saving 32b Count value into a 64b var.
    ulCountLow = ulValue;

    // Taking a 32b value and filling the upper 16b with 0xFFFF, 
    // then shifting the entire 32b value into the bottom 32b.
    ulMask = 0xFFFF << 16;
    ulMask >>= 0x20;

    // Convert to Masked value
    ulCountLow = ulValue & ulMask;

    // If the 64b value is less than last tick, inc cWrapAround, as the Count value has overflowed.
    if (ulCountLow < s_tickLastRaw) {
        cWrapAround++; // D_0027C000
    }

    // Set LastTickRaw, which is the masked 32bit value.
    s_tickLastRaw = ulCountLow;

    // Put WrapAround value in the upper 32b and ulCountLow in the lower 32b. 
    //Return the 64b value after preforming an or.
    return (cWrapAround << 0x20) | ulCountLow;
}

INCLUDE_ASM(const s32, "P2/clock", func_00143140); // empty, not really a function


