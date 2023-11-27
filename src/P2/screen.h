#pragma once

/* BLOT state */
enum BLOTS
{
	BLOTS_Hidden = 0,
	BLOTS_Appearing = 1,
	BLOTS_Visible = 2,
	BLOTS_Disappearing = 3,
	BLOTS_Max = 4
};

/* Used to draw screen objects */
struct BLOT
{
	// todo
	int padding[0x280];
};

void SetBlotBlots(BLOT* pblot, BLOTS blots);
void RenderBlots();
void DrawBlots();
