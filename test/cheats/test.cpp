#include <iostream>
#include <cassert>

#include <savegame.h>
#include <cheats.h>

int main()
{
	std::cout << "Starting tests..." << std::endl;

	g_pgsCur->gameworld = GAMEWORLD::Snow;
	g_pgsCur->worldlevel = WORLDLEVEL::Approach;
	g_pgsCur->c_coins = 99;
	g_pgsCur->c_lives = 0;

	showChetkido(); // todo: assert that the correct string is output

	std::cout << "Tests complete." << std::endl;
	return 0;
}
