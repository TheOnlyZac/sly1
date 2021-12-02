#include <game.h>
#include <joy.h>
#include <gs.h>

#include <cassert>

int main()
{
	g_pgsCur->ccoin = 1; // set coins to 1
	g_grfcht &= ~((int)FCHT::InfiniteCharms); // disable infinite charms

	// Confirm max charm count is 2
	assert(CcharmMost() == 2);

	// Test checking if a charm is available
	g_pgsCur->ccharm = 0;
	assert(FCharmAvailable() == false);

	g_pgsCur->ccharm = 1;
	assert(FCharmAvailable() == true);

	g_pgsCur->ccharm = -1;
	assert(FCharmAvailable() == false);

	g_pgsCur->ccharm = 0;
	g_grfcht |= (int)FCHT::InfiniteCharms; // enable infinite charms cheat
	assert(FCharmAvailable() == true);

	// Test setting charm count
	SetCcharm(0);
	assert(g_pgsCur->ccharm == 0);

	SetCcharm(1);
	assert(g_pgsCur->ccharm == 1);

	SetCcharm(3);
	assert(g_pgsCur->ccharm == 3);

	SetCcharm(-1);
	assert(g_pgsCur->ccharm == -1);

	return 0;
}
