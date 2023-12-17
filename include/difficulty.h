/**
 * @file difficulty.h
 *
 * @brief Declarations for the difficulty scaling system.
*/
#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#include <util.h>
#include <chkpnt.h>

/**
 * @brief Difficulty Prize State.
*/
enum DPS
{
	DPS_Normal = 0x0,
	DPS_GivenCharms = 0x1,
	DPS_Max = 0x2
};

/**
 * @brief Difficulty Level.
 *
 * Stores values related to a particular difficulty level.
 *
 * @note Name is not official
*/
struct DIFFICULTYLEVEL
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

/**
 * @brief Difficulty.
 *
 * Tracks values that don't change across difficulty levels, and a pointer to the current difficulty level
*/
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

// Global variables
static DIFFICULTY g_difficulty; // Current difficulty struct
static DIFFICULTYLEVEL g_difficultyEasy, g_difficultyMedium, g_difficultyHard; // One of three difficulty levels

//Difficulty* PdifficultyEnsureSw(SW* psw, ENSK ensk);

/**
 * @brief Called when game loads, clears the difficulty struct.
 *
 * @param pdifficulty Pointer to the difficulty.
*/
void OnDifficultyGameLoad(DIFFICULTY* pdifficulty);

/**
 * @brief Called before a level is loaded to set up the difficulty system.
 *
 * Sets the difficulty value based on the current level.
 *
 * @param pdifficulty Pointer to the difficulty.
*/
void OnDifficultyWorldPreLoad(DIFFICULTY* pdifficulty);

/**
 * @brief Called after a level is loaded to set up the difficulty system.
 *
 * Gives the player suck charms if they are below the threshold.
 *
 * @param pdifficulty Pointer to the difficulty.
*/
void OnDifficultyWorldPostLoad(DIFFICULTY* pdifficulty);

/**
 * @brief Stubbed, does nothing.
 *
 * @param pdifficulty Pointer to the difficulty.
*/
void OnDifficultyInitialTeleport(DIFFICULTY* pdifficulty);

/**
 * @brief Called when the player dies.
 *
 * Increases the player's suck value, accounting for a game over.
 *
 * @param scalar The amount to increase the suck value by.
 * @param pdifficulty Pointer to the difficulty.
*/
void OnDifficultyPlayerDeath(float scalar, DIFFICULTY* pdifficulty);

/**
 * @brief Called when the player triggers a checkpoint.
 *
 * Decreases the suck value based on the difficulty level.
 *
 * @param pdifficulty Pointer to the difficulty.
 * @param pchkpnt Pointer to the checkpoint.
*/
void OnDifficultyTriggerCheckpoint(DIFFICULTY* pdifficulty, CHKPNT* pchkpnt);

/**
 * @brief Called when the player collects a key.
 *
 * Resets the suck values.
 *
 * @param pdifficulty Pointer to the difficulty.
*/
void OnDifficultyCollectKey(DIFFICULTY* pdifficulty);

//void OnDifficultyAward(Difficulty* pdifficulty, int ccoinMin, int ccoinMax, Vector* ppos);
//void OnDifficultyBreak(Difficulty* pdifficulty, VECTOR* ppos, int ccoin);
//void OnDifficultyNpc(DIFFICULTY* pdifficulty, VECTOR* ppos, int ccoin)
//void OnDifficultyMiniNpc(Difficulty* pdifficulty, VECTOR* ppos, int ccoin);

/**
 * @brief Changes the suck value by the given amount.
 *
 * Clamps the suck between the min and max values for the given difficulty.
 *
 * @param nParam The amount to change the suck value by.
 * @param pdifficulty Pointer to the difficulty.
*/
void ChangeSuck(float nParam, DIFFICULTY* pdifficulty);

//void ResetSuckChkpnts(int nParam);
//void SetSuckChkpnts(int nParam);

#endif // DIFFICULTY_H
