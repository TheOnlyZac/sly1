#pragma once
#include <util.h>
#include <chkpnt.h>

enum DPS
{
	DPS_Normal = 0x0,
	DPS_GivenCharms = 0x1,
	DPS_Max = 0x2
};

/* Tracks values related to the current difficulty level
 * (easy, medium, or hard) */
struct DIFFICULTYLEVEL // made-up name
{
	LM suckLm;
	LM* unk_lm_0x8;
	float field_0xc;
	float duSuckDeath; // Suck increase on player death
	float duSuckCheckpntTrigger; // Suck decrease on first checkpoint trigger
	float duSuckCheckpntRetrigger; // Suck decrease on repeated checkpoint trigger
	float field_0x1c;
	float field_0x20;
	float field_0x24;
	float field_0x28;
	float uSuckCharmLow; // Suck threshold to get low charms
	int ccharmLow; // Low charms count
	float uSuckCharmHigh; // Suck threshold to get high charms
	int ccharmHigh; // High charms count
	float field_0x3c;
	float field_0x40;
	float field_0x44;
	float field_0x48;
	int field_0x4c; // Count of lives for something
	float field_0x50;
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
	DIFFICULTYLEVEL* pdifficultyLevel;
	DPS dps;
};

static DIFFICULTY g_difficulty;
static DIFFICULTYLEVEL g_difficultyEasy, g_difficultyMedium, g_difficultyHard;

//Difficulty* PdifficultyEnsureSw(SW* psw, ENSK ensk);
void OnDifficultyGameLoad(DIFFICULTY* pdifficulty);
void OnDifficultyWorldPreLoad(DIFFICULTY* pdifficulty);
void OnDifficultyWorldPostLoad(DIFFICULTY* pdifficulty);
void OnDifficultyInitialTeleport(DIFFICULTY* pdifficulty);
void OnDifficultyPlayerDeath(float scalar, DIFFICULTY* pdifficulty);
void OnDifficultyTriggerCheckpoint(DIFFICULTY* pdifficulty, CHKPNT* pchkpnt);
void OnDifficultyCollectKey(DIFFICULTY* pdifficulty);
//void OnDifficultyAward(Difficulty* pdifficulty, int ccoinMin, int ccoinMax, Vector* ppos);
//void OnDifficultyBreak(Difficulty* pdifficulty, VECTOR* ppos, int ccoin);
//void OnDifficultyNpc(DIFFICULTY* pdifficulty, VECTOR* ppos, int ccoin)
//void OnDifficultyMiniNpc(Difficulty* pdifficulty, VECTOR* ppos, int ccoin);
void ChangeSuck(float nParam, DIFFICULTY* pdifficulty);
//void ResetSuckChkpnts(int nParam);
//void SetSuckChkpnts(int nParam);
