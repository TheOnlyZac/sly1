#include <phasemem.h>

void SetPhase(PHASE phase)
{
	if (g_phase != phase)
	{
		//FlushCashe(0); // stdlib call
		g_phase = phase;
	}
}

void ClearPhase(PHASE phase)
{
	g_phase = phase;
}
