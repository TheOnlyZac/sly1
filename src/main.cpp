#include <util.h>
#include <game.h>
#include <cheats.h>
#include <savegame.h>
#include <difficulty.h>
#include <coin.h>

#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[])
{
	std::cout << "Starting main..." << std::endl;

    // Savegame
    //populatePchzLevelTable();
    //int percent = calculate_percent_completion(g_pgsCur);
    //std::cout << percent << "\n";

    // Difficulty
    OnDifficultyGameLoad(&g_difficulty);
    OnDifficultyWorldPreLoad(&g_difficulty);
    OnDifficultyWorldPostLoad(&g_difficulty);
    ChangeSuck(0.1, &g_difficulty);
    OnDifficultyInitialTeleport(&g_difficulty);
    OnDifficultyCollectKey(&g_difficulty);

    std::cout << "Finished main." << std::endl;
    char _ = getchar();
    return 0;
}
