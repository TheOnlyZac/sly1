#pragma once
#include <game.h>
#include <aseg.h>
#include <wipe.h>

/* EXIT State */
enum class EXITS : int
{
	Blocked = 0x0,
	Unblocked = 0x1,
	Disabled = 0x2,
	Enabled = 0x3,
	Totals = 0x4,
	Exiting = 0x5,
	Max = 0x6
};

/* Warps placed in the world to move from one level to another */
struct EXIT
{
	int padding[183];

	int fDefault;
	EXITS fKeyed;
	float fFollowDefault;
	int fTotals;
	EXITS exits;
	float tExits;
	int ctsurf;
	//TSURF* atsurf;
	int ctbsp;
	//TBSP* atbsp;
	WID widWarp;
	OID oidWarp;
	int edkAlt;
	WID widAlt;
	OID oidAlt;
	int cpaseg;
	ASEG* apaseg;
	WIPEK wipek;
	float tWipe;
	float dtUnblock;
	float dtTriggerWipe;
};

void SetExitExits(EXIT* pexit, EXITS exits);
