#include <clock.h>

#define cWrapAround (*(undefined8 *)0x0027c000)

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
//undefined8 cWrapAround; // Checksum doesn't like this variable. Found at D_0027C000. -Zryu


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

INCLUDE_ASM(const s32, "P2/clock", TickNow__Fv);
#ifdef SKIP_ASM
/* 
 * Matched 91%. Should be functionally identical, but calling two instructions out of order.
 * https://decomp.me/scratch/OLNRt. Checksum doesnt like cWrapAround even if its added as an extern or a poitner (commented out at the top of this file).
 *  -Zryu
 */
const TICK TickNow()
{

    ulong ulCountLow;  // Lower 32 bites of the tick result.
    ulong ulMask;      // Mask for tick value.
    ulong ulValue;     // MIPS tick in coprocessor 0

    // Get Count from CP0 reg 9
    __asm__ volatile (
    "mfc0 %0, $9" : "=r"(ulValue)
    );

    // pre-loading Count like this matches the asm for wahtever reason....doubt they did it like this.
    // Maybe a GCC optimize?
    ulCountLow = ulValue;

    // They use a mask to add FFFF for some reason? DOnt know why
    __asm__ volatile (
    "lui %0, 0xFFFF\n\t"
    "dsrl32 %0, %0, 0"
    : "=r"(ulMask)
    );

    // Actual combining of the bits to get the lower 32 bites
    ulCountLow = ulValue & ulMask;

    // If the lower 32bites are less than last tick, inc cWrapAround.
    if (ulCountLow < s_tickLastRaw) {
        cWrapAround++; // D_0027C000
    }

    // Set LastTick
    s_tickLastRaw = ulCountLow;

    // Combine wrap count (upper 32 bits) with current count (lower 32 bits)
    return (cWrapAround << 32) | ulCountLow;
}
#endif
INCLUDE_ASM(const s32, "P2/clock", func_00143140); // empty, not really a function


