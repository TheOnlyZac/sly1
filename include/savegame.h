#pragma once

enum class FGS : int
{
    FirstClue = 0x1,
    HalfClues = 0x2,
    AllClues = 0x4,
    FirstVault = 0x8,
    SecondVault = 0x10
};

enum class FWS : int
{
    Visited = 0x1,
    Lock_0 = 0x2,
    Lock_1 = 0x4,
    Lock_2 = 0x8,
    Lock_3 = 0x10,
    Lock_All = 0x1e
};

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

struct TestStruct
{
    int test;
    float test_two;
};

struct LevelSave
{
    FLS fls;
    float playtime;
    float unk_float_0x08;
    float uSuck;
    float unk_suck_0x10;
    unsigned int sceneFlags[20];
    int c_bottles;
    unsigned int f_bottles;
    unsigned int unk_field_0x6c;
    unsigned int unk_field_0x70;
    unsigned int unk_field_0x74;
};

struct WorldSave
{
    LevelSave level_saves[9];
    int c_keys;
    int c_vaults;
    int c_mts;
    float playtime;
    FWS fws;
};

struct GameSave
{
    FGS fgs;
    int size;
    unsigned int unk;
    float playtime;
    WorldSave world_saves[6];
    GAMEWORLD gameworld;
    WORLDLEVEL worldlevel;
    int c_lives;
    int c_charms;
    int c_coins;
    unsigned int settings_flags;
    unsigned int unlocked_thief_moves;
    unsigned int unlocked_cutscenes;
    unsigned int game_completion_flags;
    int last_thief_move;
};

struct PchzLevel
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

extern GameSave* g_pgsCur;
extern WorldSave* g_pwsCur;
extern LevelSave* g_plsCur;
extern PchzLevel pchzLevelTable[];

void PopulatePchzLevelTable();
int FGameCompletion();
int CalculatePercentCompletion(GameSave* pgs);
