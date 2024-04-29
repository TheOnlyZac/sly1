/**
 * @file frm.cpp
 *
 * @brief Defines functions for manipulating frames.
*/
#include <frm.h>
#include <phasemem.h>

void OpenFrame()
{
	SetPhase(PHASE_Main);
	//WaitSema(DAT_002623b4);

	int i = g_ifrmMax * 0x48;
	g_ifrmMax += 1;

	// todo
	// ...

	ClearPendingFrame(g_pfrmOpen);

	// ...
}

void CloseFrame()
{
	// todo
	// ...
}

void ClearPendingFrame(FRM* pfrm)
{
	// todo
	// ...
}
