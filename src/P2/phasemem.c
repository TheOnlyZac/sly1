#include <phasemem.h>
#include <sdk/ee/eekernel.h>

PHASE g_phase = PHASE_None;

void SetPhase(PHASE phase) {
    if (g_phase != phase) {
        FlushCache(0);
        g_phase = phase;
    }
}

void ClearPhase() {
    g_phase = PHASE_None;
}
