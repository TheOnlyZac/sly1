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
 * @brief Level ID.
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
    FLS fls;                // Level state flags
    float dt;               // Time spent in level (secs)
    float dtTimedBest;      // Best MTS time for level (secs)
    float uSuck;            // Current player suck for this level
    float unk_suck_0x10;    // unknown, seems suck related
    int afDialogPlayed[12]; // Dialog played flags
    int sceneVars[2][4];    // Scene variables
    int cclue;              // Count of clues collected
    uint fclue;             // Clue collected flags
    int unk_field_0x6c;     // Unknown
    int unk_field_0x70;     // Unknown
    char *unk_field_0x74;   // Unknown
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
    FWS fws;    // World state flags
};

/**
 * @brief Game State.
 */
struct GS
{
    int gsv;                  // not sure why this isn't caled fgs
    int cbThis;               // Struct size (bytes)
    int nChecksum;            // Expected size (bytes)
    float dt;                 // Time spent in game (secs)
    WS aws[6];                // World states array
    GAMEWORLD gameworldCur;   // Current world
    WORLDLEVEL worldlevelCur; // Current level
    int clife;                // Lives count
    int ccharm;               // Charm count
    int ccoin;                // Coin count
    GRFGS grfgs;              // Game settings flags(?)
    GRFVAULT grfvault;        // Unlocked powerup flags
    unsigned int unlocked_cutscenes;
    unsigned int fgs;
    int fspLast; // Last selected powerup
};

/**
 * @brief World ID
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
 *
 * @todo implement
 */
struct LevelLoadData
{
    // ...
};

extern const LevelLoadData *D_00247AB0[];

/**
 * @brief Calls StartGame.
 */
void StartupGame();

// LevelLoadData * search_level_by_load_data(LevelLoadData *search_level);

// LevelLoadData * search_level_by_id(int search_id);

/**
 * @brief Gets the friendly name of a level from its world ID.
 *
 * @param wid World ID.
 */
char *PchzFriendlyFromWid(int wid);

// LevelLoadData *call_search_level_by_id(int level_id);

// WORLDLEVEL FFindLevel(LevelLoadData *level)

uint get_level_completion_by_id(int level_id);

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
 * @brief Clears 8 bytes of memory.
 *
 * Used in UnloadGame and FUN_00160948.
 * Probably used to clear a pointer or something.
 *
 * @param pv Pointer to the memory to clear.
 */
extern "C" void *clr_8_bytes_1(void *pv);

/**
 * @brief Unknown function.
 *
 * @param param_1 Unknown parameter.
 */
void FUN_00160ce8(int param_1);

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
