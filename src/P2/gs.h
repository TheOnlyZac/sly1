/**
 * @file gs.h
 *
 * @brief Declarations for the game state manipulation.
 *
 * @note Not to be confused with Graphics Synthesizer, which is also abbreviated GS.
*/
#ifndef GS_H
#define GS_H

/**
 * @brief Game State Flags
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
 * @brief World State Flags
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
 * @brief Level State Flags
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
 * @brief Game World ID
*/
enum GAMEWORLD
{
    GAMEWORLD_Intro = 0,
    GAMEWORLD_Underwater = 1,
    GAMEWORLD_Muggshot = 2,
    GAMEWORLD_Voodoo = 3,
    GAMEWORLD_Snow = 4,
    GAMEWORLD_Clockwerk = 5,
    GAMEWORLD_Max = 6
};

/**
 * @brief World Level ID
*/
enum WORLDLEVEL
{
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
 * @brief Level State
*/
struct LS
{
    FLS fls; // Level state flags
    float dt; // Time spent in level (secs)
    float dtTimedBest; // Best MTS time for level (secs)
    float uSuck; // Current player suck for this level
    float unk_suck_0x10; // unknown, seems suck related
    int afDialogPlayed[12]; // Dialog played flags
	int sceneVars[2][4]; // Scene variables
    int cclue; // Count of clues collected
    unsigned int fclue; // Clue collected flags
    int unk_field_0x6c;
    int unk_field_0x70;
    char* unk_field_0x74;
};

/**
 * @brief World State
*/
struct WS
{
    LS als[9]; // Level states array
    int ckey; // Count of keys collected in world
    int cvault; // Count of vaults opened on worls
    int ctimed; // Count of MTSs completed in world
    float dt; // Time spent in world (secs)
    FWS fws; // World state flags
};

/**
 * @brief Game State
*/
typedef int GRFGS;
typedef int GRFVAULT;
struct GS
{
    int gsv; // not sure why this isn't caled fgs
    int cbThis; // Struct size (bytes)
    int nChecksum; // Expected size (bytes)
    float dt; // Time spent in game (secs)
    WS aws[6]; // World states array
    GAMEWORLD gameworldCur; // Current world
    WORLDLEVEL worldlevelCur; // Current level
    int clife; // Lives count
    int ccharm; // Charm count
    int ccoin; // Coin count
    GRFGS grfgs; // Game settings flags(?)
	GRFVAULT grfvault; // Unlocked powerup flags
    unsigned int unlocked_cutscenes;
    unsigned int fgs;
    int nPowerupLast; // Last selected powerup
};

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

// Global variables
extern GS* g_pgsCur; // Current game state
extern WS* g_pwsCur; // Current world state
extern LS* g_plsCur; // Current level state
extern WORLDLEVEL worldlevelPrev; // Previous level
extern PchzLevel pchzLevelTable[]; // Level table

/**
 * @brief Populate a default pchz table for testing.
 *
 * @note This function is temporary and should be removed when support for loading
 * the actual level data is added.
*/
void PopulatePchzLevelTable();

/**
 * @brief Returns a set of flags indicating what has been completed in the current game state.
 *
 * @return Flags indicating what has been completed on the save file.
 *
 * @todo Implement this function.
*/
int FGameCompletion();

/**
 * @brief Calculates the percent completion on the current save file.
 *
 * @param pgs Pointer to the game state.
 *
 * @return Percent completion as an integer out of 100.
*/
int CalculatePercentCompletion(GS* pgs);

#endif // GS_H
