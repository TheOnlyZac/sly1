#include <cassert>
#include <iostream>

#include <game.h>
#include <cheats.h>
#include <savegame.h>

int main()
{
	g_pgsCur->c_coins = 1; // set coins to 1
	g_pgsCur->c_charms = 0; // set charms to 0

	// Test setting coin count
	SetCcoin(0);
	assert(g_pgsCur->c_coins == 0);
	
	SetCcoin(14);
	assert(g_pgsCur->c_coins == 14);

	SetCcoin(99);
	assert(g_pgsCur->c_coins == 99);

	SetCcoin(-1);
	assert(g_pgsCur->c_coins == -1);

	SetCcoin(101);
	assert(g_pgsCur->c_coins == 101);

	return 0;
}
