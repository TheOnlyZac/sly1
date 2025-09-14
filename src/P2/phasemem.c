#include <phasemem.h>
#include <sdk/ee/eekernel.h>

// PHASE g_phase = PHASE_None; // TODO: There may be other data in this file.

void SetPhase(PHASE phase)
{
    if (g_phase != phase)
    {
        FlushCache(0);
        g_phase = phase;
    }
}

void ClearPhase(PHASE phase)
{
    g_phase = PHASE_None;
}
