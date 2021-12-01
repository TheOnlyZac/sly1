#include <game.h>
#include <joy.h>
#include <gs.h>

#include <cassert>

int main()
{
	g_pgsCur->ccoin = 1; // set coins to 1

	// Confirm max charm count is 2
	assert(CcharmMost() == 2);

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
