/**
 * @file difficulty.h
 *
 * Dynamic difficulty system.
 */
#ifndef DIFFICULTY_H
#define DIFFICULTY_H
#include "common.h"
#include <util.h>
#include <chkpnt.h>

/**
 * @brief Difficulty prize state.
 */
enum DPS
{
    DPS_Normal = 0,
    DPS_GivenCharms = 1,
    DPS_Max = 2
};

/**
 * @brief Values for a particular difficulty level.
 */
struct DifficultyLevel {
    struct LM suck_lm; // Clamp the suck to this limit
    undefined4 field1_0x8;
    float field4_0xc;
    float duSuckDeath;
    float duSuckChkpntTrigger; // Suck gain from triggering a checkpoint for the first time
    float duSuckChkpntRetrigger; // Suck gain from retriggering a checkpoint subsequent times
    float rand_low;
    float field10_0x20;
    float field11_0x24;
    float field12_0x28;
    float uSuckCharmLow; // Suck threshold to get a low noob charm
    int ccharmLow; // Low noob charm count
    float uSuckCharmHigh; // Suck threshold to get a high noob charm
    int ccharmHigh; // High noob charm count
    float field17_0x3c;
    float field18_0x40;
    float field19_0x44;
    float field20_0x48;
    int field21_0x4c;
    float field22_0x50;
};


/**
 * @brief Maintains the current difficulty level.
 */
struct DIFFICULTY {
    struct LM * unk_lm;
    int ccoinRichMin;
    int ccoinRichMax;
    int ccoinPoorMin;
    int ccoinPoorMax;
    int uRichLow;
    int uRichHigh;
    struct DifficultyLevel * p_difficulty_level;
    enum DPS dps;
};

 // Current difficulty struct
extern struct DIFFICULTY g_difficulty;

// Each of three difficulty levels
extern struct DIFFICULTYLEVEL g_difficultyEasy;
extern struct DIFFICULTYLEVEL g_difficultyMedium;
extern struct DIFFICULTYLEVEL g_difficultyHard;

/**
 * @brief Clears the difficulty struct.
 *
 * @param pdifficulty Pointer to the difficulty.
*/
void OnDifficultyGameLoad(DIFFICULTY* pdifficulty);

/**
 * @brief Sets up the difficulty system.
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
void OnDifficultyPlayerDeath(float scalar, struct DIFFICULTY* pdifficulty);

/**
 * @brief Called when the player triggers a checkpoint.
 *
 * Decreases the suck value based on the difficulty level.
 *
 * @param pdifficulty Pointer to the difficulty.
 * @param pchkpnt Pointer to the checkpoint.
*/
void OnDifficultyTriggerCheckpoint(DIFFICULTY* pdifficulty, struct CHKPNT* pchkpnt);

/**
 * @brief Called when the player collects a key.
 *
 * Resets the suck values.
 *
 * @param pdifficulty Pointer to the difficulty.
*/
void OnDifficultyCollectKey(DIFFICULTY* pdifficulty);

/**
 * @brief Called when the player breaks something.
 *
 * @param pdifficulty Pointer to the difficulty.
 * @param ppos Pointer to the position of the breakable.
 * @param ccoin The number of coins. (?)
 */
void OnDifficultyBreak(DIFFICULTY* pdifficulty, struct VECTOR* ppos, int ccoin);

/**
 * @brief Changes the suck value by the given amount.
 *
 * Clamps the suck between the min and max values for the given difficulty.
 *
 * @param nParam The amount to change the suck value by.
 * @param pdifficulty Pointer to the difficulty.
*/
void ChangeSuck(float nParam, struct DIFFICULTY* pdifficulty);

//void ResetSuckChkpnts(int nParam);
//void SetSuckChkpnts(int nParam);


/**
 * @brief Stubbed function.
 */
void OnDifficultyInitialTeleport();

#endif // DIFFICULTY_H
