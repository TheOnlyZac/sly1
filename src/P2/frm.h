#pragma once

struct FRM
{
	// todo
	// ...
};

static int g_ifrmMax;
static FRM* g_pfrmOpen;

void OpenFrame();
void CloseFrame();
void ClearPendingFrame(FRM* pfrm);