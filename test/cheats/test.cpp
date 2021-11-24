#include <cassert>

#include <cheats.h>
#include <savegame.h>

int main()
{
	g_pgsCur->gameworld = GAMEWORLD::Snow;
	g_pgsCur->worldlevel = WORLDLEVEL::Approach;
	g_pgsCur->c_coins = 99;
	g_pgsCur->c_lives = 0;

	showChetkido(); // todo: assert that the correct string is output
	return 0;
}
