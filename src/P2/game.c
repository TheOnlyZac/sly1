#include <game.h>


void StartupGame(void)
{
  StartGame();
  return;
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

INCLUDE_ASM(const s32, "P2/game", get_game_completion);

INCLUDE_ASM(const s32, "P2/game", UnlockIntroCutsceneFromWid);

INCLUDE_ASM(const s32, "P2/game", DefeatBossFromWid);

INCLUDE_ASM(const s32, "P2/game", UnlockEndgameCutscenesFromFgs);

INCLUDE_ASM(const s32, "P2/game", PlayEndingFromCompletionFlags);

INCLUDE_ASM(const s32, "P2/game", InitGameState__FP2GS);

INCLUDE_ASM(const s32, "P2/game", FUN_00160650);

INCLUDE_ASM(const s32, "P2/game", SetupGame__FPci);

void UpdateGameState(float dt)
{
  WS *wsCur;
  LS *lsCur;
  wsCur = g_pwsCur;
  g_pgsCur->dt = g_pgsCur-> dt + dt;
  lsCur = g_plsCur;
  wsCur->dt = wsCur->dt + dt;
  lsCur->dt = lsCur->dt + dt;
  return;
}

INCLUDE_ASM(const s32, "P2/game", LsFromWid);

INCLUDE_ASM(const s32, "P2/game", GrflsFromWid);

INCLUDE_ASM(const s32, "P2/game", UnloadGame__Fv);

INCLUDE_ASM(const s32, "P2/game", RetryGame__Fv);

INCLUDE_ASM(const s32, "P2/game", StartGame__Fv);

INCLUDE_ASM(const s32, "P2/game", FUN_00160948);

INCLUDE_ASM(const s32, "P2/game", calculate_percent_completion);

void SetCcharm(int nParam)
{
  g_pgsCur->ccharm = nParam;
  return;
}

INCLUDE_ASM(const s32, "P2/game", FCharmAvailable__Fv);

INCLUDE_ASM(const s32, "P2/game", func_00160C90);

int PfLookupDialog(LS *pls, OID oidDialog)
{
  if (((oidDialog) - (0x33bU)) >= 0xc) {
    return 0;
  }
    return  + -0xcd8 + (int)pls + (oidDialog * 4);
}

INCLUDE_ASM(const s32, "P2/game", clr_8_bytes_1);

void FUN_00160ce8(int param_1)
{
  *(undefined4 *)(param_1 + 4) = 0;
  return;
}

void OnGameAlarmTriggered(GAME *pgame)
{
  pgame->cAlarmsTriggered++;
}

void OnGameAlarmDisabled(GAME *pgame)
{
  pgame->cAlarmsTriggered--;
  return;
}

INCLUDE_ASM(const s32, "P2/game", grfvault_something__Fv);

INCLUDE_ASM(const s32, "P2/game", GetBlueprintInfo);

int CcharmMost()
{
    return 2;
}

INCLUDE_ASM(const s32, "P2/game", reload_post_death);
