#include <game.h>
#include <joy.h>
#include <gs.h>

#include <test/test.h>

int main()
{
	g_pgsCur->ccoin = 1; // set coins to 1
	g_grfcht &= ~((int)FCHT_InfiniteCharms); // disable infinite charms

	// Confirm max charm count is 2
	JtAssert(CcharmMost() == 2);

	// Test checking if a charm is available
	g_pgsCur->ccharm = 0;
	JtAssert(FCharmAvailable() == false);

	g_pgsCur->ccharm = 1;
	JtAssert(FCharmAvailable() == true);

	g_pgsCur->ccharm = -1;
	JtAssert(FCharmAvailable() == false);

	g_pgsCur->ccharm = 0;
	g_grfcht |= (int)FCHT_InfiniteCharms; // enable infinite charms cheat
	JtAssert(FCharmAvailable() == true);

	// Test setting charm count
	SetCcharm(0);
	JtAssert(g_pgsCur->ccharm == 0);

	SetCcharm(1);
	JtAssert(g_pgsCur->ccharm == 1);

	SetCcharm(3);
	JtAssert(g_pgsCur->ccharm == 3);

	SetCcharm(-1);
	JtAssert(g_pgsCur->ccharm == -1);

	return 0;
}
