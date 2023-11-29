#include <gs.h>
#include <cstdio>

GS* g_pgsCur = new GS;
WS* g_pwsCur = &(g_pgsCur->aws[0]);
LS* g_plsCur = &(g_pgsCur->aws[0].als[0]);
PchzLevel pchzLevelTable[0x2e];

/* Temp: Populate default pchz table for testing */
void PopulatePchzLevelTable() // temp
{
    for (int worldId = 0; worldId <= 5; worldId++)
    {
        for (int levelId = 0; levelId <= 9; levelId++)
        {
            int index = worldId + (worldId * 9) + levelId;
            PchzLevel* currLevel = &pchzLevelTable[index];
            int id = (worldId * 100) + levelId;
            currLevel->level_id = id;
            currLevel->tasks = static_cast<FLS>(0xe);
        }
    }
}

int FGameCompletion()
{
    return 0b1111; //! shouldn't always returns full completion, this is just for testing
}

/* Calculates the percent completion on the current save file */
int CalculatePercentCompletion(GS* pgs)
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
