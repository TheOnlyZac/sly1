#pragma once

/* Game Save Flags */
enum class FGS : int
{
    FirstClue = 0x1,
    HalfClues = 0x2,
    AllClues = 0x4,
    FirstVault = 0x8,
    SecondVault = 0x10
};

/* World Save Flags */
enum class FWS : int
{
    Visited = 0x1,
    Lock_0 = 0x2,
    Lock_1 = 0x4,
    Lock_2 = 0x8,
    Lock_3 = 0x10,
    Lock_All = 0x1e
};

/* Level Save Flags */
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

/* Level Save */
struct LS
{
    FLS fls; // level save flags
    float dt; // time spent in level (secs)
    float dtTimedBest; // best mts time (secs)
    float uSuck; // player suck for this level (0-1)
    float unk_suck_0x10; // unknown, seems suck related
    int afDialogPlayed[10]; // cutscene watched flags
    int cclue; // qty clues collected
    unsigned int fclue; // which clues collected
    unsigned int unk_field_0x6c;
    unsigned int unk_field_0x70;
    unsigned int unk_field_0x74;
};

/* World Save */
struct WS
{
    LS als[9]; // all level saves (0-9)
    int ckey; // qty keys collected
    int cvault; // qty vaults opened
    int ctimed; // qty mts completed
    float dt; // time spent in world (secs)
    FWS fws; // world save flags
};

/* Game Save*/
typedef int GRFGS;
typedef int GRFVAULT;
struct GS
{
    int gsv; // not sure why this isn't caled fgs
    int cbThis; // size (bytes)
    int nChecksum; // expected size (bytes)
    float dt; // time spend playing file (secs)
    WS aws[6]; // all world saves (0-6)
    GAMEWORLD gameworldCur;
    WORLDLEVEL worldlevelCur;
    int clife; // lives count
    int ccharm; // charms count
    int ccoin; // coins count
    GRFGS grfgs; // game settings flags (I think -Zac)
	GRFVAULT grfvault; // unlocked thief moves flags
    unsigned int unlocked_cutscenes;
    unsigned int game_completion_flags;
    int last_thief_move; // todo: fix name
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
