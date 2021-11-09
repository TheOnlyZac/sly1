#include "savegame.h"
#include "cheats.h"
#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[])
{
    //activate_code_chetkido();

    populatePchzLevelTable();
    int percent = calculate_percent_completion(g_pgsCur);
    std::cout << percent << "\n";

    getchar();
    return 1;
}