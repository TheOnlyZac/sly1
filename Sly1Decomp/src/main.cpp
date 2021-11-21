#include <Util/util.h>
#include <Cheats/cheats.h>
#include <Savegame/savegame.h>
#include <Difficulty/difficulty.h>

#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[])
{
    // Util
    std::cout << GLimitLm((LM*)&g_lmZeroOne, 1.3) << "\n"; // 1.0
    std::cout << GLimitLm((LM*)&g_lmZeroOne, -4.3) << "\n"; // 0.0
    std::cout << GLimitLm((LM*)&g_lmZeroOne, 0.7) << "\n"; // 0.7

    // Cheats
    activate_code_chetkido(); // The password is: chetkido

    // Savegame
    //populatePchzLevelTable();
    //int percent = calculate_percent_completion(g_pgsCur);
    //std::cout << percent << "\n";

    // Difficulty
    // todo

    char _ = getchar();
    return 1;
}
