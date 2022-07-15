#pragma once

#include <util.h>

enum class DPS
{
	Normal = 0x0,
	GivenCharms = 0x1,
	Max = 0x2
};

/* Tracks values related to the current difficulty level 
 * (easy, medium, or hard) */
struct DIFFICULTYPROPS // made-up name
{
	LM suckLm;
	LM* unk_lm_0x8;
	float field_0xc;
	float duSuckDeath; // Suck penalty on player death
	float duSuckCheckpntTrigger; // Suck penalty
	float duSuckCheckpntRetrigger; // Suck penalty
	float field_0x1c; // unknown
	float field_0x20; // unknown
	float field_0x24; // unknown
	float field_0x28; // unknown
	float uSuckCharmLow; // Suck threshold to get low charms
	int ccharmLow; // Low charms count
	float uSuckCharmHigh; // Suck threshold to get high charms
	int ccharmHigh; // High charms coutn
};

/* Tracks values that don't change across difficulty levels, 
 * and a pointer to the current difficulty level */
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
