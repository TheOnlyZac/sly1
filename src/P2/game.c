#include <game.h>
#include <wipe.h>

void StartupGame()
{
    StartGame();
}

INCLUDE_ASM(const s32, "P2/game", func_00160090);

INCLUDE_ASM(const s32, "P2/game", search_level_by_load_data);

INCLUDE_ASM(const s32, "P2/game", search_level_by_id);

INCLUDE_ASM(const s32, "P2/game", PchzFriendlyFromWid);

INCLUDE_ASM(const s32, "P2/game", func_00160178);

INCLUDE_ASM(const s32, "P2/game", call_search_level_by_id);

INCLUDE_ASM(const s32, "P2/game", FFindLevel);

INCLUDE_ASM(const s32, "P2/game", func_001601D0);

INCLUDE_ASM(const s32, "P2/game", get_level_completion_by_id);

INCLUDE_ASM(const s32, "P2/game", tally_world_completion);

INCLUDE_ASM(const s32, "P2/game", get_game_completion__Fv);

/**
 * @todo Close to matching but there's a problem with the rodata.
 */
INCLUDE_ASM(const s32, "P2/game", UnlockIntroCutsceneFromWid__Fi);
// void UnlockIntroCutsceneFromWid(int wid)
// {
//     /* Check the unlocked cutscene by setting the corresponding
//        flag on the unlocked_cutscenes in the game state */
//     switch (wid)
//     {
//     case 1:
//         /* Unlock cutscene "Tide of Terror" */
//         g_pgsCur->unlocked_cutscenes = g_pgsCur->unlocked_cutscenes | 0x10;
//         return;
//     case 2:
//         /* Unlock cutscene "Sunset Snake Eyes" */
//         g_pgsCur->unlocked_cutscenes = g_pgsCur->unlocked_cutscenes | 0x40;
//         return;
//     case 3:
//         /* Unlock cutscene "Vicious Voodoo" */
//         g_pgsCur->unlocked_cutscenes = g_pgsCur->unlocked_cutscenes | 0x100;
//         return;
//     case 4:
//         /* Unlock cutscene "Fire in the Sky" */
//         g_pgsCur->unlocked_cutscenes = g_pgsCur->unlocked_cutscenes | 0x400;
//         return;
//     case 5:
//         /* Unlock cutscene "The Cold Heart of Hate" */
//         g_pgsCur->unlocked_cutscenes = g_pgsCur->unlocked_cutscenes | 0x1000;
//     }
// }

INCLUDE_ASM(const s32, "P2/game", DefeatBossFromWid);

INCLUDE_ASM(const s32, "P2/game", UnlockEndgameCutscenesFromFgs);

INCLUDE_ASM(const s32, "P2/game", PlayEndingFromCompletionFlags);

INCLUDE_ASM(const s32, "P2/game", InitGameState__FP2GS);

INCLUDE_ASM(const s32, "P2/game", FUN_00160650);

INCLUDE_ASM(const s32, "P2/game", SetupGame__FPci);

void UpdateGameState(float dt)
{
    g_pgsCur->dt += dt;
    g_pwsCur->dt += dt;
    g_plsCur->dt += dt;
}

INCLUDE_ASM(const s32, "P2/game", LsFromWid);

INCLUDE_ASM(const s32, "P2/game", GrflsFromWid);

INCLUDE_ASM(const s32, "P2/game", UnloadGame__Fv);

INCLUDE_ASM(const s32, "P2/game", RetryGame__Fv);

void StartGame()
{
    UnloadGame();
    WipeToWorldWarp(D_00247AB0, OID_Nil, WIPEK_Fade);
}

INCLUDE_ASM(const s32, "P2/game", FUN_00160948);

INCLUDE_ASM(const s32, "P2/game", calculate_percent_completion);

void SetCcharm(int nParam)
{
    g_pgsCur->ccharm = nParam;
}

INCLUDE_ASM(const s32, "P2/game", FCharmAvailable__Fv);

INCLUDE_ASM(const s32, "P2/game", func_00160C90);

int PfLookupDialog(LS *pls, OID oidDialog)
{
    // todo figure out what these magic numbers represent
    if (oidDialog - 0x33bU >= 0xc)
    {
        return 0;
    }
    return -0xcd8 + (int)pls + (oidDialog * 4);
}

INCLUDE_ASM(const s32, "P2/game", clr_8_bytes_1);

void FUN_00160ce8(int param_1)
{
    *(undefined4 *)(param_1 + 4) = 0;
}

void OnGameAlarmTriggered(GAME *pgame)
{
    pgame->cAlarmsTriggered++;
}

void OnGameAlarmDisabled(GAME *pgame)
{
    pgame->cAlarmsTriggered--;
}

INCLUDE_ASM(const s32, "P2/game", grfvault_something__Fv);

INCLUDE_ASM(const s32, "P2/game", GetBlueprintInfo);

int CcharmMost()
{
    // Holdover from when there was a powerup that increased the charm limit
    return 2;
}

INCLUDE_ASM(const s32, "P2/game", reload_post_death);
