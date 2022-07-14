#pragma once

#include <util.h>

enum class DPS
{
	Normal = 0x0,
	GivenCharms = 0x1,
	Max = 0x2
};

struct DIFFICULTYPROPS // made-up name
{
	LM suckLm;
	LM* unk_lm_0x8;
	float field_0xc;
	float suckModifier;
	float field_0x14;
	float field_0x18;
	float field_0x1c;
	float field_0x20;
	float field_0x24;
	float field_0x28;
	float uSuckCharmLow;
	int ccharmLow;
	float uSuckCharmHigh;
	int ccharmHigh;
};

struct DIFFICULTY
{
	int field_0x0;
	int ccoinRichMin;
	int ccoinRichMax;
	int ccoinPoorMin;
	int ccoinPoorMax;
	int uRichLow;
	int uRichHigh;
	DIFFICULTYPROPS* props;
	DPS dps;
};

static DIFFICULTY g_difficulty;
static DIFFICULTYPROPS g_difficultyEasy, g_difficultyMedium, g_difficultyHard;

//Difficulty* PdifficultyEnsureSw(SW* psw, ENSK ensk);
void OnDifficultyGameLoad(DIFFICULTY* pdifficulty);
void OnDifficultyWorldPreLoad(DIFFICULTY* pdifficulty);
void OnDifficultyWorldPostLoad(DIFFICULTY* pdifficulty);
void OnDifficultyInitialTeleport(DIFFICULTY* pdifficulty);
//void OnDifficultyPlayerDeath(Difficulty* pdifficulty);
//void OnDifficultyTriggerCheckpoint(Difficulty* pdifficulty, Chkpnt* pchkpnt);
void OnDifficultyCollectKey(DIFFICULTY* pdifficulty);
//void OnDifficultyAward(Difficulty* pdifficulty, int ccoinMin, int ccoinMax, Vector* ppos);
//void OnDifficultyBreak(Difficulty* pdifficulty, VECTOR* ppos, int ccoin);
//void OnDifficultyNpc(DIFFICULTY* pdifficulty, VECTOR* ppos, int ccoin)
//void OnDifficultyMiniNpc(Difficulty* pdifficulty, VECTOR* ppos, int ccoin);
void ChangeSuck(float nParam, DIFFICULTY* pdifficulty);
//void ResetSuckChkpnts(int nParam);
//void SetSuckChkpnts(int nParam);
