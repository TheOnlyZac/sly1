#include <cassert>
#include <iostream>

#include <cheats.h>
#include <savegame.h>

int main()
{
	// Test chetkido string output
	g_pgsCur->gameworld = GAMEWORLD::Snow;
	g_pgsCur->worldlevel = WORLDLEVEL::Approach;
	g_pgsCur->c_coins = 99;
	g_pgsCur->c_lives = 0;

	showChetkido();
	assert(strstr(&chetkido_buffer[0], "The password is: chetkido") != NULL);

	g_pgsCur->c_coins = 98;

	showChetkido();
	assert(strstr(&chetkido_buffer[0], "The password is: chetkido") == NULL);

	return 0;
}
