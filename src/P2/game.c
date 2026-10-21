#include <game.h>
#include <joy.h>
#include <wipe.h>
#include <chkpnt.h>
#include <rumble.h>
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

extern WORLDLEVEL g_worldlevelPrev;
extern LevelLoadData D_00247AF0[46];
extern char *chz_none; // NOTE: This is in .data probably due to PchzFriendlyFromWid returning a mutable pointer.
extern GAME g_game;

void StartupGame()
{
    StartGame();
}

JUNK_NOP();
JUNK_WORD(0x00E0102D);
JUNK_WORD(0x0000102D);

INCLUDE_ASM("asm/nonmatchings/P2/game", search_level_by_load_data__FP13LevelLoadData);

LevelLoadData *search_level_by_id(WID wid)
{
    for (uint i = 0; i < sizeof(D_00247AF0) / sizeof(LevelLoadData); i++)
    {
        LevelLoadData *level = &D_00247AF0[i];
        if (wid == level->wid)
        {
            return level;
        }
    }

    return NULL;
}

/**
 * @todo 95% match.
 */
INCLUDE_ASM("asm/nonmatchings/P2/game", PchzFriendlyFromWid__F3WID);
#ifdef SKIP_ASM
char *PchzFriendlyFromWid(WID wid)
{
    LevelLoadData *level = search_level_by_id(wid);
    return level ? (char *)level->pchzFriendly : chz_none;
}
#endif // SKIP_ASM

JUNK_WORD(0x24420010);

INCLUDE_ASM("asm/nonmatchings/P2/game", call_search_level_by_id);

INCLUDE_ASM("asm/nonmatchings/P2/game", FFindLevel);

JUNK_WORD(0x24420010);

FLS GetLevelCompletionById(WID wid)
{
    LevelLoadData *plevel = search_level_by_id(wid);
    return plevel ? plevel->completionState : (FLS)0;
}

INCLUDE_ASM("asm/nonmatchings/P2/game", tally_world_completion);

INCLUDE_ASM("asm/nonmatchings/P2/game", get_game_completion__Fv);

INCLUDE_ASM("asm/nonmatchings/P2/game", UnlockIntroCutsceneFromWid__F9GAMEWORLD);
#ifdef SKIP_ASM
/**
 * @todo Migrate .rodata.
 */
void UnlockIntroCutsceneFromWid(GAMEWORLD gameworld)
{
    /* Check the unlocked cutscene by setting the corresponding
       flag on the unlocked_cutscenes in the game state */
    switch (gameworld)
    {
        case GAMEWORLD_Underwater:
        {
            /* Unlock cutscene "Tide of Terror" */
            g_pgsCur->unlocked_cutscenes |= 0x10;
            break;
        }
        case GAMEWORLD_Muggshot:
        {
            /* Unlock cutscene "Sunset Snake Eyes" */
            g_pgsCur->unlocked_cutscenes |= 0x40;
            break;
        }
        case GAMEWORLD_Voodoo:
        {
            /* Unlock cutscene "Vicious Voodoo" */
            g_pgsCur->unlocked_cutscenes |= 0x100;
            break;
        }
        case GAMEWORLD_Snow:
        {
            /* Unlock cutscene "Fire in the Sky" */
            g_pgsCur->unlocked_cutscenes |= 0x400;
            break;
        }
        case GAMEWORLD_Clockwerk:
        {
            /* Unlock cutscene "The Cold Heart of Hate" */
            g_pgsCur->unlocked_cutscenes |= 0x1000;
            break;
        }
    }
}
#endif // SKIP_ASM

INCLUDE_ASM("asm/nonmatchings/P2/game", DefeatBossFromWorld__F9GAMEWORLD);
#ifdef SKIP_ASM
/**
 * @todo 99.65% match. Migrate .rodata.
 */
void DefeatBossFromWorld(GAMEWORLD gameworld)
{
    g_pgsCur->aws[gameworld].fws |= 0x20;

    switch (gameworld)
    {
        case GAMEWORLD_Underwater:
        {
            g_pgsCur->unlocked_cutscenes |= 0x20;
            break;
        }
        case GAMEWORLD_Muggshot:
        {
            g_pgsCur->unlocked_cutscenes |= 0x80;
            break;
        }
        case GAMEWORLD_Voodoo:
        {
            g_pgsCur->unlocked_cutscenes |= 0x200;
            g_pgsCur->grfvault |= 0x10000;
            break;
        }
        case GAMEWORLD_Snow:
        {
            g_pgsCur->unlocked_cutscenes |= 0x800;
            break;
        }
        case GAMEWORLD_Clockwerk:
        {
            UnlockEndgameCutscenesFromFgs(FGS_HalfClues);
            break;
        }
    }
}
#endif // SKIP_ASM

INCLUDE_ASM("asm/nonmatchings/P2/game", UnlockEndgameCutscenesFromFgs);

INCLUDE_ASM("asm/nonmatchings/P2/game", PlayEndingFromCompletionFlags);

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
    RumbleUnknown2(pgs);
}

INCLUDE_ASM("asm/nonmatchings/P2/game", FUN_00160650);

INCLUDE_ASM("asm/nonmatchings/P2/game", SetupGame__FPci);

void UpdateGameState(float dt)
{
    g_pgsCur->dt += dt;
    g_pwsCur->dt += dt;
    g_plsCur->dt += dt;
}

INCLUDE_ASM("asm/nonmatchings/P2/game", LsFromWid);

INCLUDE_ASM("asm/nonmatchings/P2/game", GrflsFromWid__F3WID);

INCLUDE_ASM("asm/nonmatchings/P2/game", UnloadGame__Fv);
#ifdef SKIP_ASM
/**
 * @todo 60.42% matched.
 */
void UnloadGame()
{
    InitGameState(g_pgsCur);
    // unk_gs? = NULL;
    OnGameLoad(&g_game);
    OnDifficultyGameLoad(&g_difficulty);
    g_grfcht = (GRFCHT)FCHT_None;
    g_worldlevelPrev = WORLDLEVEL_Nil;
    RetryGame();
}
#endif // SKIP_ASM

void RetryGame()
{
    g_pgsCur->clife = 5; // Set lives to 5
    g_pgsCur->ccharm = 0; // Set charms to 0

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
 * @todo 72.96% matched.
 */
int CalculatePercentCompletion(GS *pgs)
{
    int cTasksChecked = 0;
    int cTasksCompleted = 0;

    // Iterate over all the levels in the PchzLevel table
    for (int i = 0; i < 0x2e; i++)
    {
        int levelId = pchzLevelTable[i].level_id;
        int world = levelId >> 8;

        // if world is part of Intro (ie. Splash, Paris, Hideout), skip it
        if (world != GAMEWORLD_Intro)
        {
            // get all tasks for the current level
            FLS levelTasks = pchzLevelTable[i].tasks;

            // get save data for the current level
            LS *currLs = &pgs->aws[world].als[levelId];
            int currFls = (int)(currLs->fls);

            // check if the level is visited
            cTasksChecked++;
            cTasksCompleted += (currFls & (int)(FLS_Visited));

            /* Loop over the bits in the FLS cmp and count how many are set,
            * but only if those bits are also set in the level_tasks the pchz table */
            GRFLS flsMask = FLS_KeyCollected;
            int tasksToCheck = levelTasks & FLS_KeyCollected;
            while ((flsMask & (FLS_KeyCollected | FLS_Secondary | FLS_Tertiary)) != 0)
            {
                if (tasksToCheck != 0)
                {
                    cTasksChecked++;
                    if ((currFls & flsMask) != 0)
                    {
                        cTasksCompleted++;
                    }
                }
                flsMask <<= 1;
                tasksToCheck = levelTasks & flsMask;
            }
        }
    }

    for (int i = 4; i > -1; i--)
    {
        GRFWS *fws = &pgs->aws[i].fws;
        cTasksChecked++;
        if ((*fws & 0x20) != 0)
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
    if (cTasksCompleted != 0 && (finalPercent = 100, cTasksCompleted != cTasksChecked))
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
        if (cTasksChecked > 0 && (finalPercent = 99, percent < 100))
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

void OnGameLoad(GAME *pgame)
{
    memset(pgame, 0, 8);
}

void OnGameWorldTransition(GAME *pgame)
{
    pgame->cAlarmsTriggered = 0;
}

void OnGameAlarmTriggered(GAME *pgame)
{
    pgame->cAlarmsTriggered++;
}

void OnGameAlarmDisabled(GAME *pgame)
{
    pgame->cAlarmsTriggered--;
}

GRFVAULT GetGrfvault_unknown()
{
    return g_pgsCur->grfvault & STRUCT_OFFSET(g_psw, 0x235c, GRFVAULT);
}

INCLUDE_ASM("asm/nonmatchings/P2/game", GetBlueprintInfo__FP8GRFVAULT);
#ifdef SKIP_ASM
/**
 * @todo Migrate .rodata.
 */
void GetBlueprintInfo(GRFVAULT *pgrfvault)
{
    int value;
    switch (g_pgsCur->gameworldCur)
    {
        case GAMEWORLD_Snow:
        {
            value = 0x10000000;
            break;
        }
        case GAMEWORLD_Underwater:
        {
            value = 0x20000000;
            break;
        }
        case GAMEWORLD_Muggshot:
        {
            value = 0x40000000;
            break;
        }
        case GAMEWORLD_Voodoo:
        {
            value = 0x80000000;
            break;
        }
        case GAMEWORLD_Intro:
        case GAMEWORLD_Clockwerk:
        {
            value = 0;
            break;
        }
    }

    if (pgrfvault)
    {
        *pgrfvault = value;
    }
}
#endif // SKIP_ASM

int CcharmMost()
{
    // Leftover from when there was a powerup that increased the charm limit.
    return 2;
}

INCLUDE_ASM("asm/nonmatchings/P2/game", reload_post_death__Fv);
