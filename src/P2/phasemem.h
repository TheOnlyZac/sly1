#pragma once

enum PHASE
{
	PHASE_None = 0,
	PHASE_Startup = 0x1,
	PHASE_Load = 1,
	PHASE_Main = 2,
	PHASE_Mpeg = 4,
	PHASE_Max = 5
};

static PHASE g_phase;
static void* g_phasemem; // todo: fix type

void SetPhase(PHASE phase);
void ClearPhase(PHASE phase = PHASE_None);
