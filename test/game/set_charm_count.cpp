#include <game.h>
#include <joy.h>
#include <gs.h>

#include <test/test.h>

int main()
{
	// Confirm max charm count is 2
	JtAssert(CcharmMost() == 2);

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
