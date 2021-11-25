#include <util.h>
#include <game.h>
#include <cheats.h>
#include <savegame.h>
#include <difficulty.h>
#include <coin.h>
#include <aseg.h>
#include <wipe.h>
#include <xform.h>

#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[])
{
	std::cout << "Starting main..." << std::endl;

    // Save tests (todo: fix and move to tests folder)
    //populatePchzLevelTable();
    //int percent = calculate_percent_completion(g_pgsCur);
    //std::cout << percent << "\n";

    std::cout << "Finished main." << std::endl;
    char _ = getchar();
    return 0;
}
