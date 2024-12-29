#include <phasemem.h>

void SetPhase(PHASE phase) {
    if (g_phase != phase) {
        FlushCache(0);
        g_phase = phase;
    }
}

void ClearPhase(void) {
    g_phase = PHASE_None;
}
