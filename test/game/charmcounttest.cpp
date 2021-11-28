#include <game.h>
#include <joy.h>
#include <gs.h>

#include <cassert>

int main()
{
	g_pgsCur->c_coins = 1; // set coins to 1

	// Confirm max charm count is 2
	assert(CcharmMost() == 2);

	// Test setting charm count
	SetCcharm(0);
	assert(g_pgsCur->c_charms == 0);

	SetCcharm(1);
	assert(g_pgsCur->c_charms == 1);

	SetCcharm(3);
	assert(g_pgsCur->c_charms == 3);

	SetCcharm(-1);
	assert(g_pgsCur->c_charms == -1);

	return 0;
}
