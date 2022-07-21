#include <phasemem.h>

// Sets the current global phase value
void SetPhase(PHASE phase)
{
	if (g_phase != phase)
	{
		//FlushCashe(0); // stdlib call
		g_phase = phase;
	}
}

// Clears the global phase value
void ClearPhase(PHASE phase)
{
	g_phase = PHASE::None;
}