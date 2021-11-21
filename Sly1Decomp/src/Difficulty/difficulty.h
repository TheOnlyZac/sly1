#pragma once

#include <Util/util.h>

enum DPS
{
	DPS_Normal = 0x0,
	DPS_GivenCharms = 0x1,
	DPS_Max = 0x2
};

struct DifficultyProps
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

struct Difficulty
{
	int field_0x0;
	int ccoinRichMin;
	int ccoinRichMax;
	int ccoinPoorMin;
	int ccoinPoorMax;
	int uRichLow;
	int uRichHigh;
	DifficultyProps* props;
	DPS dps;
};

extern Difficulty* g_difficulty;
extern DifficultyProps g_difficultyEasy;
extern DifficultyProps g_difficultyMedium;
extern DifficultyProps g_difficultyHard;

void ChangeSuck(float nParam, Difficulty* pdifficulty);
void OnDifficultyGameLoad(Difficulty* pdifficulty);
void OnDifficultyWorldPreLoad(Difficulty* pdifficulty);
void OnDifficultyWorldPostLoad(Difficulty* pdifficulty);
void OnDifficultyInitialTeleport(Difficulty* pdifficulty);
void OnDifficultyCollectKey(Difficulty* pdifficulty);

//void OnDifficultyAward(Difficulty* pdifficulty, int ccoinMin, int ccoinMax, Vector* ppos);
//void OnDifficultyBreak(Difficulty* pdifficulty, Vector* ppos, int ccoin);
//void OnDifficultyMiniNpc(Difficulty* pdifficulty, Vector* ppos, int ccoin);
void OnDifficultyPlayerDeath(Difficulty* pdifficulty);
//void OnDifficultyTriggerCheckpoint(Difficulty* pdifficulty, Chkpnt* pchkpnt);
//Difficulty* PdifficultyEnsureSw(SW* psw, ENSK ensk);
void ResetSuckChkpnts(int nParam);
void SetSuckChkpnts(int nParam);
