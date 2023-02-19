#pragma once

/* Game State Flags */
enum class FGS : int
{
    FirstClue = 0x1,
    HalfClues = 0x2,
    AllClues = 0x4,
    FirstVault = 0x8,
    SecondVault = 0x10
};

/* World State Flags */
enum class FWS : int
{
    Visited = 0x1,
    Lock_0 = 0x2,
    Lock_1 = 0x4,
    Lock_2 = 0x8,
    Lock_3 = 0x10,
    Lock_All = 0x1e
};

/* Level State Flags */
enum class FLS : int
{
    Visited = 0x1,
    KeyCollected = 0x2,
    Secondary = 0x4,
    Tertiary = 0x8,
    BossDefeated = 0x10
};

enum class GAMEWORLD : int
{
    Intro = 0x0,
    Underwater = 0x1,
    Muggshot = 0x2,
    Voodoo = 0x3,
    Snow = 0x4,
    Clockwerk = 0x5,
    Max = 0x6 
};

enum class WORLDLEVEL : int
{
    Approach = 0x0,
    Hub = 0x1,
    Level1 = 0x2,
    Level2 = 0x3,
    Level3 = 0x4,
    Level4 = 0x5,
    Level5 = 0x6,
    Level6 = 0x7,
    Boss = 0x8,
    Max = 0x9
};

/* Level State */
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

/* World State */
struct WS
{
    LS als[9]; // Level states array
    int ckey; // Count of keys collected in world
    int cvault; // Count of vaults opened on worls
    int ctimed; // Count of MTSs completed in world
    float dt; // Time spent in world (secs)
    FWS fws; // World state flags
};

/* Game State */
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
    unsigned int game_completion_flags;
    int nPowerupLast; // Last selected powerup
};

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

extern GS* g_pgsCur;
extern WS* g_pwsCur;
extern LS* g_plsCur;
extern PchzLevel pchzLevelTable[];

void PopulatePchzLevelTable();
int FGameCompletion();
int CalculatePercentCompletion(GS* pgs);
