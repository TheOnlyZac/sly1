#include <joy.h>
#include <gs.h>

#include <cassert>
#include <iostream>
#include <cstring>

int main()
{
	// Test chetkido string output
	g_pgsCur->gameworld = GAMEWORLD::Snow;
	g_pgsCur->worldlevel = WORLDLEVEL::Approach;
	g_pgsCur->c_coins = 99;
	g_pgsCur->c_lives = 0;

	CheatActivateChetkido();
	assert(strstr(chetkido_buffer, "The password is: chetkido") != NULL);

	g_pgsCur->c_coins = 98;

	CheatActivateChetkido();
	assert(strstr(chetkido_buffer, "The password is: chetkido") == NULL);

	return 0;
}
