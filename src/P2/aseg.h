/**
 * @file aseg.h
 *
 * @brief Declarations for animation segments.
*/
#pragma once
#include <util.h>
#include <game.h>

/**
 * @brief Animation Segment
*/
struct ASEG
{
	int padding[15];

	float tMax;
	int cchn;
	//CHN* achn;
	OID oidRoot;
	//SEGRPT segrpt;
	int fDefault;
	int fHandsOff;
	int fRealClock;
	int ceaApply;
	int field_0x64;
	int ceaframe;
	int field_0x6c;
	int ceaRetract;
	int field_0x74;
	//DL dlAsega;
	int nPriotity;
	float svtMaster;
	int field_0x8c;
	//CLQ clqMasterSuck;
	LM lmMasterSuck;
	float svtMasterSuck;
	//CHN* pchnStrip;
	int coidSearchRoot;
	OID* aoidSearchRoot;
};
