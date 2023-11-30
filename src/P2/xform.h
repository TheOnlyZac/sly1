#pragma once
#include <game.h>
#include <aseg.h>
#include <wipe.h>

/**
 * @brief EXIT State
*/
enum EXITS
{
	EXITS_Blocked = 0,
	EXITS_Unblocked = 1,
	EXITS_Disabled = 2,
	EXITS_Enabled = 3,
	EXITS_Totals = 4,
	EXITS_Exiting = 5,
	EXITS_Max = 6
};

/**
 * @brief Exit
 *
 * An invisible warp triugger in the world that brings you to a new level.
*/
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

/**
 * @brief Sets the EXIT state.
 *
 * @param pexit Pointer to the EXIT
 * @param exits EXIT state
*/
void SetExitExits(EXIT* pexit, EXITS exits);
