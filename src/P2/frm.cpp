#include <frm.h>
#include <phasemem.h>

// todo
void OpenFrame()
{
	SetPhase(PHASE_Main);
	//WaitSema(DAT_002623b4);

	int i = g_ifrmMax * 0x48;
	g_ifrmMax += 1;

	// ...

	ClearPendingFrame(g_pfrmOpen);

	// ...
}

// todo
void CloseFrame()
{
	// ...
}

// todo
void ClearPendingFrame(FRM* pfrm)
{
	// ...
}
