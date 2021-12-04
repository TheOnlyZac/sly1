#include <game.h>
#include <joy.h>
#include <gs.h>

#include <cassert>

int main()
{
	g_pgsCur->ccoin = 1; // set coins to 1
	g_pgsCur->ccharm = 0; // set charms to 0

	// Test setting coin count
	SetCcoin(0);
	assert(g_pgsCur->ccoin == 0);

	SetCcoin(14);
	assert(g_pgsCur->ccoin == 14);

	SetCcoin(99);
	assert(g_pgsCur->ccoin == 99);

	SetCcoin(-1);
	assert(g_pgsCur->ccoin == -1);

	SetCcoin(101);
	assert(g_pgsCur->ccoin == 101);

	return 0;
}