#pragma once

/* BLOT state */
enum class BLOTS : int
{
	Hidden = 0x0,
	Appearing = 0x1,
	Visible = 0x2,
	Disappearing = 0x3,
	Max = 0x4
};

/* Used to draw screen objects */
struct BLOT
{
	// todo
	int padding[0x280];
};

void SetBlotBlots(BLOT* pblot, BLOTS blots);
