#pragma once

enum class PHASE : int
{
	None = 0x0,
	Startup	= 0x1,
	Load = 0x2,
	Main = 0x3,
	Mpeg = 0x4,
	Max = 0x5
};

static PHASE g_phase;
static void* g_phasemem; // todo: fix type

void SetPhase(PHASE phase);
void ClearPhase(PHASE phase = PHASE::None);
