#pragma once

enum FGS
{
    FGS_FirstClue = 0x1,
    FGS_HalfClues = 0x2,
    FGS_AllClues = 0x4,
    FGS_FirstVault = 0x8,
    FGS_SecondVault = 0x10
};

enum FWS
{
    FWS_Visited = 0x1,
    FWS_Lock_0 = 0x2,
    FWS_Lock_1 = 0x4,
    FWS_Lock_2 = 0x8,
    FWS_Lock_3 = 0x10,
    GRFWS_Lock_All = 0x1e
};

enum FLS
{
    FLS_Visited = 0x1,
    FLS_KeyCollected = 0x2,
    FLS_Secondary = 0x4,
    FLS_Tertiary = 0x8,
    FLS_BossDefeated = 0x10
};

enum GAMEWORLD
{
    GAMEWORLD_Intro = 0x0,
    GAMEWORLD_Underwater = 0x1,
    GAMEWORLD_Muggshot = 0x2,
    GAMEWORLD_Voodoo = 0x3,
    GAMEWORLD_Snow = 0x4,
    GAMEWORLD_Clockwerk = 0x5,
    GAMEWORLD_Max = 0x6 
};

enum WORLDLEVEL
{
    WORLDLEVEL_Approach = 0x0,
    WORLDLEVEL_Hub = 0x1,
    WORLDLEVEL_1 = 0x2,
    WORLDLEVEL_2 = 0x3,
    WORLDLEVEL_3 = 0x4,
    WORLDLEVEL_4 = 0x5,
    WORLDLEVEL_5 = 0x6,
    WORLDLEVEL_6 = 0x7,
    WORLDLEVEL_Boss = 0x8,
    WORLDLEVEL_Max = 0x9
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
PchzLevel pchzLevelTable[];

void populatePchzLevelTable();
int check_game_completion();
int calculate_percent_completion(GameSave* pgs);