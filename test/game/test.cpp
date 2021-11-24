#include <cassert>

#include <game.h>
#include <savegame.h>

int main()
{
	g_pgsCur->c_coins = 1;
	g_pgsCur->c_charms = 0;

	// Test setting coin count
	SetCcoin(14);
	assert(g_pgsCur->c_coins == 14);

	// Test max charm count is 2
	assert(CcharmMost() == 2);

	// Test setting charm count
	SetCcharm(1);
	assert(g_pgsCur->c_charms == 1);

	return 0;
}
