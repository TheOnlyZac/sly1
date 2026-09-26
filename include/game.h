/**
 * @file game.h
 *
 * @brief Game state and level management.
 *
 * @todo Cleanup/update structs and function names/parameters.
 */
#ifndef GAME_H
#define GAME_H

#include "common.h"
#include <oid.h>
#include <cid.h>

/**
 * @brief World ID.
 */
enum WID
{
    // Intro
    WID_stock_objects = 0x0,
    WID_splash = 0x1,
    WID_attract = 0x2,
    WID_jb_intro = 0x3,

    // Underwater
    WID_uw_exterior_approach = 0x4,
    WID_uw_exterior_boat = 0x5,
    WID_uw_bonus_security = 0x6,
    WID_uw_bonus_drivewheels_final = 0x7,
    WID_uw_bonus_library = 0x8,
    WID_uw_t3_final = 0x9,
    WID_uw_rip_off = 0xa,
    WID_uw_c2_final = 0xb,
    WID_uw_boss_blimp = 0xc,

    // Mesa
    WID_ms_approach = 0xd,
    WID_ms_casino = 0xe,
    WID_ms_exterior = 0xf,
    WID_ms_inspector = 0x10,
    WID_ms_rooftop = 0x11,
    WID_ms_vertigo = 0x12,
    WID_ms_sniper = 0x13,
    WID_ms_suv = 0x14,
    WID_ms_boss_battle = 0x15,

    // Voodoo
    WID_v_approach = 0x16,
    WID_v_gomerville = 0x17,
    WID_v_swamp_monster = 0x18,
    WID_v_hub = 0x19,
    WID_v_skinterior = 0x1a,
    WID_v_murray = 0x1b,
    WID_v_chicken = 0x1c,
    WID_v_puffer = 0x1d,
    WID_v_boss = 0x1e,

    // Snow
    WID_s_approach = 0x1f,
    WID_s_barrel = 0x20,
    WID_s_hub = 0x21,
    WID_s_inspector = 0x22,
    WID_s_security = 0x23,
    WID_s_sniper = 0x24,
    WID_s_suv = 0x25,
    WID_s_tank = 0x26,
    WID_s_boss = 0x27,

    // Clockwerk
    WID_cw_suv = 0x28,
    WID_cw_turret = 0x29,
    WID_cw_security = 0x2a,
    WID_cw_bentley = 0x2b,
    WID_cw_reverse_sniper = 0x2c,
    WID_cw_outclimb = 0x2d,
    WID_cw_finish = 0x2e,

    WID_Max = 0x2f
};

/**
 * @brief Hub ID.
 */
enum GAMEWORLD
{
    GAMEWORLD_Nil = -1,
    GAMEWORLD_Intro = 0,
    GAMEWORLD_Underwater = 1,
    GAMEWORLD_Muggshot = 2,
    GAMEWORLD_Voodoo = 3,
    GAMEWORLD_Snow = 4,
    GAMEWORLD_Clockwerk = 5,
    GAMEWORLD_Max = 6
};

/**
 * @brief Hub level ID.
 */
enum WORLDLEVEL
{
    WORLDLEVEL_Nil = -1,
    WORLDLEVEL_Approach = 0,
    WORLDLEVEL_Hub = 1,
    WORLDLEVEL_Level1 = 2,
    WORLDLEVEL_Level2 = 3,
    WORLDLEVEL_Level3 = 4,
    WORLDLEVEL_Level4 = 5,
    WORLDLEVEL_Level5 = 6,
    WORLDLEVEL_Level6 = 7,
    WORLDLEVEL_Boss = 8,
    WORLDLEVEL_Max = 9
};

/**
 * @brief Game state flags.
 */
enum FGS
{
    FGS_FirstClue = 0x1,
    FGS_HalfClues = 0x2,
    FGS_AllClues = 0x4,
    FGS_FirstVault = 0x8,
    FGS_SecondVault = 0x10
};

/**
 * @brief World state flags.
 */
enum FWS
{
    FWS_Visited = 0x1,
    FWS_Lock_0 = 0x2,
    FWS_Lock_1 = 0x4,
    FWS_Lock_2 = 0x8,
    FWS_Lock_3 = 0x10,
    FWS_Lock_All = 0x1e
};

/**
 * @brief Level state flags.
 */
enum FLS
{
    FLS_Visited = 0x1,
    FLS_KeyCollected = 0x2,
    FLS_Secondary = 0x4,
    FLS_Tertiary = 0x8,
    FLS_BossDefeated = 0x10
};

/**
 * @brief Game state flags integer type.
 */
typedef int GRFGS;

/**
 * @brief World state flags integer type.
 */
typedef int GRFWS;

/**
 * @brief Level state flags integer type.
 */
typedef int GRFLS;

/**
 * @brief Vault powerup flags integer type.
 */
typedef int GRFVAULT;

/**
 * @brief Level State.
 */
struct LS
{
    /* 0x00 */ FLS fls;                // Level state flags
    /* 0x04 */ float dt;               // Time spent in level (secs)
    /* 0x08 */ float dtTimedBest;      // Best MTS time for level (secs)
    /* 0x0c */ float uSuck;            // Current player suck for this level
    /* 0x10 */ float unk_suck_0x10;    // unknown, seems suck related
    /* 0x14 */ int afDialogPlayed[12]; // Dialog played flags
    /* 0x44 */ int sceneVars[2][4];    // Scene variables
    /* 0x64 */ int cclue;              // Count of clues collected
    /* 0x68 */ uint fclue;             // Clue collected flags
    /* 0x6c */ int unk_field_0x6c;     // Unknown
    /* 0x70 */ int unk_field_0x70;     // Unknown
    /* 0x74 */ char *unk_field_0x74;   // Unknown
};

/**
 * @brief World State.
 */
struct WS
{
    LS als[9];  // Level states array
    int ckey;   // Count of keys collected in world
    int cvault; // Count of vaults opened on worls
    int ctimed; // Count of MTSs completed in world
    float dt;   // Time spent in world (secs)
    GRFWS fws;    // World state flags
};

/**
 * @brief Game State.
 */
struct GS
{
    /* 0x0000 */ int gsv; // not sure why this isn't caled fgs
    /* 0x0004 */ int cbThis; // Size of the struct in bytes.
    /* 0x0008 */ int nChecksum; // Expected size (bytes)
    /* 0x000c */ float dt; // Time spent in game (secs)
    /* 0x0010 */ WS aws[6]; // Array of world states.
    /* 0x19d8 */ GAMEWORLD gameworldCur; // Current world.
    /* 0x19dc */ WORLDLEVEL worldlevelCur; // Current level.
    /* 0x19e0 */ int clife; // Number of lives.
    /* 0x19e4 */ int ccharm; // Number of charms.
    /* 0x19e8 */ int ccoin; // Number of coins.
    /* 0x19ec */ GRFGS grfgs; // Game settings flags(?)
    /* 0x19f0 */ GRFVAULT grfvault; // Unlocked powerup flags
    /* 0x19f4 */ uint unlocked_cutscenes;
    /* 0x19f8 */ uint fgs;
    /* 0x19fc */ int fspLast; // Last selected powerup
};

/**
 * @brief Game.
 * @todo Verify that the last 3 fields actually exist.
 */
struct GAME
{
    VTGAME *pvtgame;
    int cAlarmsTriggered;
    int fTimedChallenge;
    float dtChallenge;
    int cgoldLatest;
};

/**
 * @brief Used to locate level data by its location on the disc.
 * @todo Verify unknown fields.
 */
struct LevelLoadData
{
    uint unk_00;
    uint unk_04;
    uint unk_08;
    uint unk_0C;
    uint unk_10;
    uint unk_14;
    uint unk_18;
    uint unk_1C;
    WID wid;
    const char *pchzFriendly;
    FLS completionState;
};

extern const LevelLoadData *D_00247AB0[];

/**
 * @brief Calls StartGame.
 */
void StartupGame();

// LevelLoadData * search_level_by_load_data(LevelLoadData *search_level);

/**
 * @brief Finds the level data associated with a world ID.
 * @todo Rename to better fit in with the naming convention.
 *
 * @param wid World ID.
 * 
 * @return Pointer to the matching LevelLoadData, or NULL if no match is found.
 */
LevelLoadData *search_level_by_id(WID wid);

/**
 * @brief Gets the friendly name of a level from its world ID.
 *
 * @param wid World ID.
 */
char *PchzFriendlyFromWid(WID wid);

// LevelLoadData *call_search_level_by_id(int level_id);

// WORLDLEVEL FFindLevel(LevelLoadData *level)

/**
 * @brief Get the completion state of a level based on its ID.
 *
 * @param id ID of the level to get the completion state of.
 *
 * @return The completion state of the level.
 */
FLS GetLevelCompletionById(int id);

/**
 * @brief Tally the completion of a world.
 *
 * @param wid World ID.
 * @param ckey Result of the tally of keys.
 * @param cvault Result of the tally of vaults.
 * @param cmts Result of the tally of Master Thief Sprints
 */
void tally_world_completion(int wid, int *ckey, int *cvault, int *cmts);

/**
 * @brief Get the game completion flags based on the current game state.
 */
FGS get_game_completion();

/**
 * @brief Unlocks the intro cutscene for a world.
 *
 * @param wid World ID.
 */
void UnlockIntroCutsceneFromWid(int wid);

/**
 * @brief Updates game state upon defeating the boss of a world.
 *
 * Unlocks specific reward cutscenes and powerups based on the world ID.
 *
 * @param wid World ID.
 */
void DefeatBossFromWid(int wid);

/**
 * @brief Unlocks the endgame cutscenes based on the completion flags.
 *
 * E.g. Ten Seconds, Thievius Raccoonus, etc.
 *
 * @param fgs Completion flags.
 */
void UnlockEndgameCutscenesFromFgs(FGS fgs);

/**
 * @brief Plays the ending cutscene based on the completion flags.
 *
 * @param grfgs Completion flags.
 */
void PlayEndingFromCompletionFlags(GRFGS grfgs);

/**
 * @brief Initializes the game state.
 *
 * @param pgs Game state.
 */
void InitGameState(GS *pgs);

/**
 * @brief Unknown function.
 *
 * @param param_1 Unknown parameter.
 */
int FUN_00160650(int param_1);

// void SetupGame(LevelLoadData *search_data,FTRANS transition_flags);

/**
 * @brief Updates the timers on the game state.
 *
 * @param dt Delta time.
 */
void UpdateGameState(float dt);

/**
 * @brief Gets the level state object from a world ID.
 *
 * @param wid World ID.
 */
int *LsFromWid(WID wid);

/**
 * @brief Gets the level state flags from a world ID.
 *
 * @param wid World ID.
 */
GRFLS GrflsFromWid(WID wid);

/**
 * @brief Unloads the game.
 */
void UnloadGame();

/**
 * @brief TBD
 */
void RetryGame();

/**
 * Unloads the game and wipes to the default world warp.
 */
void StartGame();

/**
 * @brief Unknown function.
 */
int FUN_00160948();

/**
 * @brief Calculates the percentage completion of the game.
 *
 * Tallies up the completion of each world and returns the percentage
 * as an int out of 100.
 *
 * @param pgs Game state.
 */
int CalculatePercentCompletion(GS *pgs);

/**
 * @brief Sets the number of charms the player has.
 *
 * @param nParam Number of charms.
 */
void SetCcharm(int nParam);

/**
 * @brief Checks if the player has any charms available.
 *
 * Will return true if the ccharm on the g_gs is > 0, of if the
 * infinite charms cheat is enabled.
 */
bool FCharmAvailable();

/**
 * @brief Unknown function, TBD.
 *
 * @param pls Pointer to level state.
 * @param param_2 OID of the dialog.
 */
//int PfLookupDialog(LS *pls, OID oidDialog);

/**
 * @brief Clear the GAME struct.
 *
 * @param pv Pointer to a GAME struct.
 */
void OnGameLoad(GAME *pgame);

/**
 * @brief Called during level transition. Only resets the amount of alamrs triggered.
 * @note This function used to reset more data in the prototype build.
 *
 * @param pgame Pointer to a GAME struct.
 */
void OnGameWorldTransition(GAME *pgame);

/**
 * @brief Increases the count of alarms triggered in the given GAME.
 *
 * The count is used as a multiplier for the MTS countdown timer.
 */
void OnGameAlarmTriggered(GAME *pgame);

/**
 * @brief Decreases the count of alarms triggered in the given GAME.
 *
 * The count is used as a multiplier for the MTS countdown timer.
 */
void OnGameAlarmDisabled(GAME *pgame);

/**
 * @brief Unknown function.
 */
GRFVAULT GetGrfvault_unknown();

/**
 * @brief Gets the blueprint info for a vault.
 *
 * @param pgrfvault Pointer to the vault flags.
 * @param pipdialog Pointer to the dialog flags.
 *
 * @todo Fix parameter types.
 */
void GetBlueprintInfo(int *pgrfvault, int *pipdialog);

/**
 * @brief Returns the max number of charms the player can hold.
 *
 * @note Always returns 2. This is a holdover from earlier in development where
 * there was a powerup that allowed you to have more than 2 charms.
 */
int CcharmMost();

/**
 * @brief Reloads the game state after the player dies.
 */
void reload_post_death();

// todo these should be somewhere else?
extern GS g_gsCur;
extern WS g_wsCur;
extern LS g_lsCur;

extern GS *g_pgsCur;
extern WS *g_pwsCur;
extern LS *g_plsCur;

#ifdef SKIP_ASM
// For CalculatePercentCompletion

/**
 * @brief Level Info
 *
 * Used by the game to load the level.
*/
struct PchzLevel // maybe wrong name
{
    double lsn_and_unk_ciphers;
    int search_Val;
    unsigned int unk_0xc;
    unsigned int unk_0x10;
    unsigned int unk_0x14;
    unsigned int unk_0x18;
    unsigned int for_lsn;
    int search_cipher;
    unsigned int for_size;
    unsigned int level_id;
    char* level_name;
    FLS tasks;
};

extern PchzLevel pchzLevelTable[]; // Level table
#endif

#endif // GAME_H
