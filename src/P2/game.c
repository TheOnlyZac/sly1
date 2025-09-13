#include <game.h>
#include <joy.h>
#include <wipe.h>
#include <chkpnt.h>
#include <difficulty.h>
#include <sce/memset.h>

// I know these functions are here somewhere but I don't know which one they are. -Zac
// void SetClife(int nParam)
// {
//  g_pgsCur->clife = nParam;
// }
// void ClearLs(LS* pls)
// {
//  memset(pls, 0, sizeof(LS));
// }
// void SetCcoin(int nParam)
// {
//  g_pgsCur->ccoin = nParam;
// }
// void OnGameLoad(GAME* pgame)
// {
//  memset(pgame, 0, sizeof(GAME));
// }

extern WORLDLEVEL g_worldlevelPrev;

void StartupGame()
{
    StartGame();
}

INCLUDE_ASM("asm/nonmatchings/P2/game", junk_00160090);

INCLUDE_ASM("asm/nonmatchings/P2/game", search_level_by_load_data);

INCLUDE_ASM("asm/nonmatchings/P2/game", search_level_by_id);

INCLUDE_ASM("asm/nonmatchings/P2/game", PchzFriendlyFromWid);

INCLUDE_ASM("asm/nonmatchings/P2/game", junk_00160178);

INCLUDE_ASM("asm/nonmatchings/P2/game", call_search_level_by_id);

INCLUDE_ASM("asm/nonmatchings/P2/game", FFindLevel);

INCLUDE_ASM("asm/nonmatchings/P2/game", junk_001601D0);

INCLUDE_ASM("asm/nonmatchings/P2/game", get_level_completion_by_id);

INCLUDE_ASM("asm/nonmatchings/P2/game", tally_world_completion);

INCLUDE_ASM("asm/nonmatchings/P2/game", get_game_completion__Fv);

INCLUDE_ASM("asm/nonmatchings/P2/game", UnlockIntroCutsceneFromWid__Fi);
#ifdef SKIP_ASM
/**
 * @todo Close to matching but there's a problem with the rodata.
 */
void UnlockIntroCutsceneFromWid(int wid)
{
    /* Check the unlocked cutscene by setting the corresponding
       flag on the unlocked_cutscenes in the game state */
    switch (wid)
    {
    case 1:
        /* Unlock cutscene "Tide of Terror" */
        g_pgsCur->unlocked_cutscenes = g_pgsCur->unlocked_cutscenes | 0x10;
        return;
    case 2:
        /* Unlock cutscene "Sunset Snake Eyes" */
        g_pgsCur->unlocked_cutscenes = g_pgsCur->unlocked_cutscenes | 0x40;
        return;
    case 3:
        /* Unlock cutscene "Vicious Voodoo" */
        g_pgsCur->unlocked_cutscenes = g_pgsCur->unlocked_cutscenes | 0x100;
        return;
    case 4:
        /* Unlock cutscene "Fire in the Sky" */
        g_pgsCur->unlocked_cutscenes = g_pgsCur->unlocked_cutscenes | 0x400;
        return;
    case 5:
        /* Unlock cutscene "The Cold Heart of Hate" */
        g_pgsCur->unlocked_cutscenes = g_pgsCur->unlocked_cutscenes | 0x1000;
    }
}
#endif // SKIP_ASM

INCLUDE_ASM("asm/nonmatchings/P2/game", DefeatBossFromWid);

INCLUDE_ASM("asm/nonmatchings/P2/game", UnlockEndgameCutscenesFromFgs);

INCLUDE_ASM("asm/nonmatchings/P2/game", PlayEndingFromCompletionFlags);

INCLUDE_ASM("asm/nonmatchings/P2/game", InitGameState__FP2GS);
/**
 * @todo 86.46% matched.
 */
#ifdef SKIP_ASM
void InitGameState(GS *pgs)
{
    memset(pgs, 0, sizeof(GS));
    pgs->gameworldCur = GAMEWORLD_Intro;
    pgs->grfvault = 0;
    pgs->gsv = 0x12;
    pgs->cbThis = sizeof(GS);
    pgs->worldlevelCur = WORLDLEVEL_Level2;
    pgs->clife = 5;
    pgs->fspLast = -1;
    // todo: implement function (name is wrong)
    // reset_settings(pgs);
}
#endif // SKIP_ASM

INCLUDE_ASM("asm/nonmatchings/P2/game", FUN_00160650);

INCLUDE_ASM("asm/nonmatchings/P2/game", SetupGame__FPci);

void UpdateGameState(float dt)
{
    g_pgsCur->dt += dt;
    g_pwsCur->dt += dt;
    g_plsCur->dt += dt;
}

INCLUDE_ASM("asm/nonmatchings/P2/game", LsFromWid);

INCLUDE_ASM("asm/nonmatchings/P2/game", GrflsFromWid);

INCLUDE_ASM("asm/nonmatchings/P2/game", UnloadGame__Fv);
#ifdef SKIP_ASM
/**
 * @todo 60.42% matched.
 */
void UnloadGame()
{
    InitGameState(g_pgsCur);
    // unk_gs? = NULL;
    // clr_8_bytes_1(&DAT_002623d8);
    OnDifficultyGameLoad(&g_difficulty);
    g_grfcht = (GRFCHT)FCHT_None;
    g_worldlevelPrev = WORLDLEVEL_Nil;
    RetryGame();
}
#endif // SKIP_ASM

void RetryGame()
{
    GS* gsCur = g_pgsCur;

    g_pgsCur->clife = 5; // Set lives to 5
    gsCur->ccharm = 0; // Set charms to 0

    ResetChkmgrCheckpoints(&g_chkmgr);
}

void StartGame()
{
    UnloadGame();
    WipeToWorldWarp(D_00247AB0, OID_Nil, WIPEK_Fade);
}

INCLUDE_ASM("asm/nonmatchings/P2/game", FUN_00160948);

INCLUDE_ASM("asm/nonmatchings/P2/game", CalculatePercentCompletion__FP2GS);

#ifdef SKIP_ASM
PchzLevel pchzLevelTable[0x2e];
/**
 * @todo 59.54% matched.
 */
int CalculatePercentCompletion(GS *pgs)
{
    int cTasksChecked = 0;
    int cTasksCompleted = 0;

    // Iterate over all the levels in the PchzLevel table
    for (int i = 0; i < 0x2e; i++)
    {
        int levelId = *(int*)&((pchzLevelTable[0].level_id)) + i * sizeof(PchzLevel);
        int world = levelId >> 8;

        // if world is part of Intro (ie. Splash, Paris, Hideout), skip it
        if (world != static_cast<int>(GAMEWORLD_Intro))
        {
            // get all tasks for the current level
            int levelTasks = static_cast<int>(pchzLevelTable[0].tasks) + i;

            // get save data for the current level
            LS* currLs = pgs->aws[world].als + (levelId & 0xff);
            int currFls = (int)(currLs->fls);

            // check if the level is visited
            cTasksChecked++;
            cTasksCompleted = cTasksCompleted + (currFls & (int)(FLS_Visited));

            /* Loop over the bits in the FLS cmp and count how many are set,
            * but only if those bits are also set in the level_tasks the pchz table */
            int flsMask = static_cast<int>(FLS_KeyCollected);
            int tasksToCheck = (int)(levelTasks) & (int)(FLS_KeyCollected);
            while ((flsMask & ((int)(FLS_KeyCollected) | (int)(FLS_Secondary) | (int)(FLS_Tertiary))) != 0)
            {
                if (tasksToCheck != 0)
                {
                    cTasksChecked++;
                    if ((currFls & flsMask) != 0)
                    {
                        cTasksCompleted++;
                    }
                }
                flsMask = flsMask << 1;
                tasksToCheck = levelTasks & flsMask;
            }
        }
    }

    FWS* pCurrFws = &pgs->aws[1].fws;
    int i = 4;
    while (i > -1)
    {
        FWS fws_cmp = static_cast<FWS>(*pCurrFws);
        cTasksChecked++;
        pCurrFws += 1;
        i--;
        if (((int)(fws_cmp) & 0x20) != 0)
        {
            cTasksCompleted++;
        }
    }

    /* This check ensures we only calculate the % if we have to.
    *
    * If cTasksCompleted is 0, finalPercent is left as 0 and
    * the if block is skipped.
    *
    * If cTasksCompleted == cTasksChecked (ie. all tasks are completed),
    * finalPercent is set to 100 and the if block is skipped.
    *
    * In all other cases, the if block sets finalPercent to a calculated value.
    */
    int finalPercent = 0;
    if ((cTasksCompleted != 0) &&
        (finalPercent = 100, cTasksCompleted != cTasksChecked))
    {
        // if cTasksChecked is 0 then something has gone wrong
        if (cTasksChecked == 0)
        {
            return -1;
        }

        // convert the number of tasks completed to a value between 1 and 100
        int percent = (cTasksCompleted * 100) / cTasksChecked;

        /* This check accounts for integer division errors.
        *
        * If cTasksChecked is <= 0, finalPercent is left as 1 and the
        * if block is skipped because we already know we have completed at least
        * one task.
        *
        * If the calclated percent is >= 100, finalPercent is set to 99 and the
        * if block is skipped because we already know all tasks are not complete.
        *
        * In all other cases, finalPercent is set to the calculated percent.
        */
        finalPercent = 1;
        if ((cTasksChecked > 0) &&
            (finalPercent = 99, percent < 100))
        {
            finalPercent = percent;
        }
    }

    return finalPercent;
}
#endif // SKIP_ASM

void SetCcharm(int ccharm)
{
    g_pgsCur->ccharm = ccharm;
}

/**
 * @todo 77.50% matched.
 */
bool FCharmAvailable()
{
    return (g_pgsCur->ccharm > 0) || (g_grfcht & (GRFCHT)FCHT_InfiniteCharms);
}

INCLUDE_ASM("asm/nonmatchings/P2/game", FUN_00160C90);

int PfLookupDialog(LS *pls, OID oidDialog)
{
    // todo figure out what these magic numbers represent
    if (oidDialog - 0x33bU >= 0xc)
    {
        return 0;
    }
    return -0xcd8 + (int)pls + (oidDialog * 4);
}

// TODO: Come up with a name and mangle it.
void *clr_8_bytes_1(void *pv)
{
    return memset(pv, 0, 8);
}

void FUN_00160ce8(int param_1)
{
    STRUCT_OFFSET(param_1, 4, undefined4) = 0;
}

void OnGameAlarmTriggered(GAME *pgame)
{
    pgame->cAlarmsTriggered++;
}

void OnGameAlarmDisabled(GAME *pgame)
{
    pgame->cAlarmsTriggered--;
}

uint GetGrfvault_unknown()
{
    GS *pgsCur = g_pgsCur;
    SW *pswCur = g_psw;

    GRFVAULT grfvault = pgsCur->grfvault;
    uint unk = STRUCT_OFFSET(pswCur, 0x235c, uint);

    return grfvault & unk;
}

INCLUDE_ASM("asm/nonmatchings/P2/game", GetBlueprintInfo__FPiT0);
#ifdef SKIP_ASM
/**
 * @todo 97.65% matched
 * https://decomp.me/scratch/l86al
 */
void GetBlueprintInfo(int *pgrfvault, int *pipdialog)
{
    switch (g_pgsCur->gameworldCur)
    {
    case GAMEWORLD_Snow:
        pipdialog = (int *)0x00000000;
        break;
    case GAMEWORLD_Intro:
        pipdialog = (int *)0x10000000;
        break;
    case GAMEWORLD_Clockwerk:
        pipdialog = (int *)0x20000000;
        break;
    case GAMEWORLD_Underwater:
        pipdialog = (int *)0x40000000;
        break;
    case GAMEWORLD_Muggshot:
        pipdialog = (int *)0x60000000;
        break;
    case GAMEWORLD_Voodoo:
        pipdialog = (int *)0x60000000;
        break;
    default:
        pipdialog = (int *)0x00000000;
        break;
    }

    if (pgrfvault != (int *)0x0)
    {
        *pgrfvault = (int)pipdialog;
    }
}
#endif // SKIP_ASM

int CcharmMost()
{
    // Leftover from when there was a powerup that increased the charm limit.
    return 2;
}

INCLUDE_ASM("asm/nonmatchings/P2/game", reload_post_death);
