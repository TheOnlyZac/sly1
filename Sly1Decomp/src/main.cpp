#include <Cheats/cheats.h>
#include <Savegame/savegame.h>
#include <Difficulty/difficulty.h>

#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[])
{
    // Cheats
    activate_code_chetkido();

    // Savegame
    //populatePchzLevelTable();
    //int percent = calculate_percent_completion(g_pgsCur);
    //std::cout << percent << "\n";

    // Difficulty


    getchar();
    return 1;
}
