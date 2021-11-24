#include <cassert>
#include <iostream>

#include <game.h>
#include <cheats.h>
#include <savegame.h>

int main()
{
	g_pgsCur->c_coins = 1; // set coins to 1
	g_pgsCur->c_charms = 0; // set charms to 0
	g_grfcht &= ~((int)FCHT::InfiniteCharms); // disable infinite charms

	// Test setting coin count
	SetCcoin(14);
	assert(g_pgsCur->c_coins == 14);

	// Test max charm count is 2
	assert(CcharmMost() == 2);

	// Test checking if a charm is available
	assert(FCharmAvailable() == false);

	g_pgsCur->c_charms = 1;
	assert(FCharmAvailable() == true);

	g_pgsCur->c_charms = 0;
	g_grfcht |= (int)FCHT::InfiniteCharms; // enable infinite charms
	assert(FCharmAvailable() == true);

	// Test setting charm count
	SetCcharm(1);
	assert(g_pgsCur->c_charms == 1);

	return 0;
}